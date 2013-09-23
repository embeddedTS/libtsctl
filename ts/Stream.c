#include <string.h>
#include <stdarg.h>
#include <errno.h>
#include "Stream.h"
#include "nosig.h"

int DescriptorReadyRead(int desc) {
  fd_set rfd;
  struct timeval tv;

  FD_ZERO(&rfd);
  FD_SET(desc,&rfd);
  tv.tv_sec = 0;
  tv.tv_usec = 0;
  return (select(desc+1,&rfd,0,0,&tv) == 1);
}

void FileStreamFini(Stream *st) {
  free(st);
}

int FileStreamRead(Stream *st0,char *bytes,int len) {
  FileStream *st = (FileStream *)st0;
  return fread(bytes,1,len,st->I);
}
  
int FileStreamUnread(Stream *st0,int ch) {
  FileStream *st = (FileStream *)st0;
  return ungetc(ch,st->I);
}

int FileStreamReadChar(Stream *st0) {
  FileStream *st = (FileStream *)st0;
  return fgetc(st->I);
}

unsigned FileStreamInputReady(Stream *st0) {
  FileStream *st = (FileStream *)st0;
  return feof(st->I) ? 0 : 4096; // HACK
}

int FileStreamWrite(Stream *st0,char *bytes,int len) {
  FileStream *st = (FileStream *)st0;
  st->outputOffset += len;
  return fwrite(bytes,1,len,st->O);
}

int FileStreamWriteChar(Stream *st0,char byte) {
  FileStream *st = (FileStream *)st0;
  st->outputOffset++;
  return fputc(byte,st->O);
}
int FileStreamEOF(Stream *st0) {
  FileStream *st = (FileStream *)st0;
  return feof(st->I);
}
void FileStreamFlush(Stream *st0) {
  FileStream *st = (FileStream *)st0;
  fflush(st->O);
}

void DescriptorStreamFini(Stream *st0) {
  DescriptorStream *st = (DescriptorStream *)st0;
  if (st->obuf) free(st->obuf);
  free(st->ibuf);
  free(st);
}

static int DescriptorStreamFillBuffer(Stream *st0,int block) {
  DescriptorStream *st = (DescriptorStream *)st0;
  int ret;

  if (st->iptr + st->ilen < 4096) {
    if (block <= 0 && !DescriptorReadyRead(st->i)) return 1;
    ret = NOSIG(read(st->i,st->ibuf + st->iptr + st->ilen,4096-st->ilen-st->iptr));
    if (ret > 0) { st->ilen += ret; block -= ret; }
  }
  if (st->iptr + st->ilen >= 4096 && st->ilen < 4096) {
    if (block <= 0 && !DescriptorReadyRead(st->i)) return 1;
    ret = NOSIG(read(st->i,st->ibuf + st->iptr + st->ilen - 4096,4096-st->ilen));
    if (ret > 0) st->ilen += ret;
  }
  return ret;
}

static int DescriptorStreamDrainBytes(Stream *st0,char *buf,int len) {
  DescriptorStream *st = (DescriptorStream *)st0;

  if (len > st->ilen) {
    DescriptorStreamFillBuffer(st0,len);
  }
  if (st->iptr + st->ilen < 4096) {
    if (len > st->ilen) len = st->ilen;
  } else {
    if (len > st->iptr + st->ilen - 4096) len = len > st->iptr + st->ilen - 4096;
  }
  memcpy(buf,st->ibuf+st->iptr,len);
  st->iptr += len;
  st->ilen -= len;
  if (st->iptr == 4096) st->iptr = 0;
  return len;
}

int DescriptorStreamRead(Stream *st0,char *bytes,int len) {
  DescriptorStream *st = (DescriptorStream *)st0;
  int got,total=0;

  while (len > 0) {
    got = DescriptorStreamDrainBytes(st0,bytes+total,len);
    if (got == 0) return total; // FIXME, should be blocking!
    // but, also must handle EOF by returning what was actually available
    // so, no way to determine if an error occured in some functions such
    // as ReadInt32LE?
    total += got;
    len -= got;
  }
  //fprintf(stderr,"read got %d/%d\n",total,len);
  return total;
}
  
int DescriptorStreamUnread(Stream *st0,int ch) {
  DescriptorStream *st = (DescriptorStream *)st0;

  if (st->ilen == 4096) return 0;
  if (--st->iptr < 0) st->iptr = 4095;
  st->ilen++;
}

int DescriptorStreamReadChar(Stream *st0) {
  DescriptorStream *st = (DescriptorStream *)st0;
  char ch;
  int ret;

  ret = DescriptorStreamRead(st0,&ch,1);
  if (ret <= 0) return ret;
  return ch;
}

unsigned DescriptorStreamInputReady(Stream *st0) {
  DescriptorStream *st = (DescriptorStream *)st0;

  DescriptorStreamFillBuffer(st0,0);
  //if (st->ilen == 0) { *((int *)0) = 0; }
  //fprintf(stderr,"ir=%d\n",st->ilen);
  return st->ilen;
}

int surewrite(int h,void *buf,int len) {
  int n,tot=len;

  while (len > 0) {
    n = write(h,buf,len);
    if (n < 0) {
      if (errno == EINTR) continue;
      return n; // assumes blocking, else CPU will be high polling
    }
    buf += n;
    len -= n;
  }
  return tot;
}

int DescriptorStreamBufferedWrite(DescriptorStream *st,char *bytes,int len) {
  int n;
  while (len > st->olen - st->ordy) { // enough to send next buffer
    memcpy(st->obuf + st->ordy,bytes,st->olen - st->ordy);
    n = surewrite(st->o,st->obuf,st->olen);
    if (n < 0) return n;
    len -= (st->olen - st->ordy);
    bytes += (st->olen - st->ordy);
    st->ordy = 0;
  }
  memcpy(st->obuf + st->ordy,bytes,len);
  st->ordy += len;
  return len;
}

int DescriptorStreamWrite(Stream *st0,char *bytes,int len) {
  DescriptorStream *st = (DescriptorStream *)st0;

  st->outputOffset+=len; // if write doesn't write everything, this is wrong
  // but it probably doesn't matter since we won't use this here
  if (st->obuf) {
    return DescriptorStreamBufferedWrite(st,bytes,len);
  }
  return write(st->o,bytes,len); // FIXME: should be blocking!
}

int DescriptorStreamWriteChar(Stream *st0,char byte) {
  DescriptorStream *st = (DescriptorStream *)st0;
  st->outputOffset++;
  if (st->obuf) {
    return DescriptorStreamBufferedWrite(st,&byte,1);
  }
  return write(st->o,&byte,1); // FIXME: should be blocking!
}

int DescriptorStreamEOF(Stream *st0) {
  DescriptorStream *st = (DescriptorStream *)st0;

  int ret = DescriptorStreamFillBuffer(st0,0);
  //fprintf(stderr,"eof@%d\n",ret);
  return ret <= 0;
}

void DescriptorStreamFlush(Stream *st0) {
  DescriptorStream *st = (DescriptorStream *)st0;

  if (st->obuf) {
    surewrite(st->o,st->obuf,st->ordy);
    st->ordy = 0;
  }
}

void StringStreamFini(Stream *st) {
  free(st);
}

int StringStreamRead(Stream *st0,char *bytes,int len) {
  StringStream *st = (StringStream *)st0;
  if (len > ArrayLength(*(st->input)) - st->inputOffset) {
    len = ArrayLength(*(st->input)) - st->inputOffset - 1;
  }
  memcpy(bytes,*(st->input)+st->inputOffset,len);
  st->inputOffset += len;
  return len;
}
  
int StringStreamUnread(Stream *st0,int ch) {
  StringStream *st = (StringStream *)st0;
  if (st->inputOffset > 0) {
    st->inputOffset--;
    return ch;
  }
  return -1;
}

int StringStreamReadChar(Stream *st0) {
  StringStream *st = (StringStream *)st0;
  if (1 > ArrayLength(*(st->input)) - st->inputOffset) return -1;
  return (*(st->input))[st->inputOffset++];
}

unsigned StringStreamInputReady(Stream *st0) {
  StringStream *st = (StringStream *)st0;
  return ArrayLength(*(st->input)) - st->inputOffset;
}

int StringStreamWrite(Stream *st0,char *bytes,int len) {
  StringStream *st = (StringStream *)st0;
  st->outputOffset += len;
  int olen = ArrayLength(*(st->output));
  *(st->output) = ArraySize(*(st->output),olen+len);
  memcpy(*(st->output)+olen,bytes,len);
  (*(st->output))[olen+len]=0;
  return len;
}

int StringStreamWriteChar(Stream *st0,char byte) {
  StringStream *st = (StringStream *)st0;
  st->outputOffset++;
  int olen = ArrayLength(*(st->output));
  *(st->output) = ArraySize(*(st->output),olen+1);    
  (*(st->output))[olen]=byte;
  (*(st->output))[olen+1]=0;
  return 1;
}

int StringStreamEOF(Stream *st0) {
  StringStream *st = (StringStream *)st0;
  return (ArrayLength(*(st->input)) - st->inputOffset) == 0;
}

void StringStreamFlush(Stream *st0) {
}

Stream *FileStreamInit(FILE *in,FILE *out) {
  FileStream *st = malloc(sizeof(FileStream));
  st->Fini = FileStreamFini;
  st->Read = FileStreamRead;
  st->Unread = FileStreamUnread;
  st->ReadChar = FileStreamReadChar;
  st->InputReady = FileStreamInputReady;
  st->Write = FileStreamWrite;
  st->WriteChar = FileStreamWriteChar;
  st->isEOF = FileStreamEOF;
  st->Flush = FileStreamFlush;
  st->I = in;
  st->O = out;
  return (Stream *)st;
}

Stream *DescriptorStreamInit(int in,int out) {
  DescriptorStream *st = malloc(sizeof(DescriptorStream));
  st->Fini = DescriptorStreamFini;
  st->Read = DescriptorStreamRead;
  st->Unread = DescriptorStreamUnread;
  st->ReadChar = DescriptorStreamReadChar;
  st->InputReady = DescriptorStreamInputReady;
  st->Write = DescriptorStreamWrite;
  st->WriteChar = DescriptorStreamWriteChar;
  st->isEOF = DescriptorStreamEOF;
  st->Flush = DescriptorStreamFlush;
  st->i = in;
  st->o = out;
  st->ibuf = malloc(4096);
  st->iptr = st->ilen = st->ordy = st->olen = 0;
  st->obuf = 0;
  return (Stream *)st;
}

Stream *DescriptorStreamInit2(int in,int out,int buflen) {
  DescriptorStream *ret= (DescriptorStream *)DescriptorStreamInit(in,out);
  ret->obuf = malloc(buflen);
  ret->olen = buflen;
  return (Stream *)ret;
}

Stream *StringStreamInit(int8** in,int8** out) {
  StringStream *st = malloc(sizeof(StringStream));
  st->Fini = StringStreamFini;
  st->Read = StringStreamRead;
  st->Unread = StringStreamUnread;
  st->ReadChar = StringStreamReadChar;
  st->InputReady = StringStreamInputReady;
  st->Write = StringStreamWrite;
  st->WriteChar = StringStreamWriteChar;
  st->isEOF = StringStreamEOF;
  st->Flush = StringStreamFlush;
  st->input = in;
  st->output = out;
  st->inputOffset = st->outputOffset = 0;
  return (Stream *)st;
}

// vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv

// this could be optimized if both streams are of type String
int StreamCopy(Stream *out,Stream *in,unsigned len) {
  char buf[4096];
  int left;

  while ((left = out->InputReady(in)) > 0) {
    if (left > 4096) left = 4096;
    in->Read(in,buf,left);
    out->Write(out,buf,left);
  }
}

// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

int WriteArray(Stream *st,void *arr) {
  return st->Write(st,arr,ArrayLength(arr)*ArrayElementSize(arr));
}

int WriteASCIIZ(Stream *st,char *arr) {
  return st->Write(st,arr,strlen(arr));
}

char *vstrf(char *format,va_list ap);
/*
#ifndef __vstrf_defined
#define __vstrf_defined
char *vstrf(char *format,va_list ap) {
  int len;
  char *str,dummy[1];

  len = vsnprintf(dummy,0,format,ap);
  str = ArrayAlloc(len,sizeof(char));
  vsprintf(str,format,ap);
  return str;
}
#endif
*/
int WriteF(Stream *st,char *format,...) {
  va_list ap;
  char* str;
  int ret;

  va_start(ap, format);
  str = vstrf(format,ap);
  va_end(ap);
  ret = WriteArray(st,str);
  ArrayFree(str);
  return ret;
}

/*
WriteInt() - Formatted integer output
WriteUInt() - Formatted unsigned output

base: positive yields upper-case characters (base > 10), 
      negative yields lower-case
      absolute value must be between 2 and 36
minchars: minimum number of characters to output
          positive if output is right justified
          negative if output is left justified
pad: character to pad with
     could be an array if we wanted to allow weird pads
 */
void _WriteUInt(unsigned val,int base,char *str,int *len,int point) {
  int n;
  if (val >= base) _WriteUInt(val/base,base,str,len,point);
  n = (val % base);
  if (n < 10) {
    n += '0';
  } else if (base > 0) {
    n += 'A' - 10;
  } else {
    n += 'a' - 10;
  }
  str[*len] = n;
  (*len)++;
  if (val < base && point) {
    str[*len] = '.';
    (*len)++;
  }
}

unsigned _WritePadded(Stream *st,int minchars,char *str,int len,char pad) {
  unsigned n,m;
  int minc = (minchars > 0) ? minchars : -minchars;

  if (minchars > 0 && minchars > len) {
    char padbytes[minchars - len];
    memset(padbytes,pad,minchars-len);
    m = st->Write(st,padbytes,minchars-len);
    n += m; if (m < minc-len) return n;
  }
  m = st->Write(st,str,len);
  n += m; if (m < minc-len) return n;
  if (minchars < 0 && -minchars > len) {
    char padbytes[-minchars - len];
    memset(padbytes,pad,-minchars-len);
    m = st->Write(st,padbytes,-minchars-len);
    n += m;
  }
  return n;
}

int WriteUInt(Stream *st,uint val,int base,int minchars,char pad) {
  char str[32];
  int len=0;
  _WriteUInt(val,base,str,&len,0);
  return _WritePadded(st,minchars,str,len,pad);
}

int WriteInt(Stream *st,int val,int base,int minchars,char pad) {
  char str[32];
  int len=0;

  if (val < 0) {
    str[len++] = '-';
    val = -val;
  }
  _WriteUInt(val,base,str,&len,0);
  return _WritePadded(st,minchars,str,len,pad);
}


/*
WriteFloat32() - Formatted float output
WriteFloat64() - Formatted double output

pre: number of digits before decimal point
post: numbe rof digits after decimal point

note: based on %f, needs more development work
also, unimplemented
 */
#define F_MAX 10000000.0
#define F_MIN 0.000001

int WriteReal64A(Stream *st,real64 val,int pre,int post) {
  char str[32];
  int n;

  if (val < 0) {
    st->WriteChar(st,'-');
    val = -val;
  }
  if (val < F_MAX && val > F_MAX) {
    if (val-(unsigned)val < F_MIN) {
      return WriteInt(st,(unsigned)val,10,0,0);
    } else {
      n = sprintf(str,"%f",val);
      return st->Write(st,str,n);
    } 
  } else {
    n = sprintf(str,"%g",val);
    return st->Write(st,str,n);
  }
}

int8* ReadArrayInt8LE(Stream *st) {
  unsigned len = ReadInt32LE(st);
  int8 *ret = ArrayAlloc(len,sizeof(int8));
  st->Read(st,ret,len);
  return ret;
}

uint8* ReadArrayUInt8LE(Stream *st) {
  unsigned len = ReadInt32LE(st);
  uint8 *ret = ArrayAlloc(len,sizeof(uint8));
  st->Read(st,ret,len);
  return ret;
}

int16* ReadArrayInt16LE(Stream *st) {
  unsigned len = ReadInt32LE(st);
  int16 *ret = ArrayAlloc(len,sizeof(int16));
  st->Read(st,(int8 *)ret,len*sizeof(int16));
  return ret;
}


int32* ReadArrayInt32LE(Stream *st) {
  unsigned len = ReadInt32LE(st);
  int32 *ret = ArrayAlloc(len,sizeof(int32));
  st->Read(st,(int8 *)ret,len*sizeof(int32));
  return ret;
}

real32* ReadArrayReal32LE(Stream *st) {
  unsigned len = ReadInt32LE(st);
  real32 *ret = ArrayAlloc(len,sizeof(real32));
  st->Read(st,(int8 *)ret,len*sizeof(real32));
  return ret;
}

int WriteInt8LE(Stream *st,int8 value) {
  return st->WriteChar(st,value);
}
int WriteInt16LE(Stream *st,int16 value) {
  return st->Write(st,(char *)&value,2);
}
int WriteInt32LE(Stream *st,int32 value) {
  return st->Write(st,(char *)&value,4);
}
int WriteUInt8LE(Stream *st,uint8 value) {
  return st->WriteChar(st,value);
}
int WriteUInt16LE(Stream *st,uint16 value) {
  return st->Write(st,(char *)&value,2);
}
int WriteUInt32LE(Stream *st,uint32 value) {
  return st->Write(st,(char *)&value,4);
}
int WriteReal32LE(Stream *st,real32 value) {
  return st->Write(st,(char *)&value,4);
}

int8 ReadInt8LE(Stream *st) {
  return st->ReadChar(st);
}

int16 ReadInt16LE(Stream *st) {
  int byte1,byte2;
  byte1 = st->ReadChar(st);
  byte2 = st->ReadChar(st);
  return byte1 + 256*byte2;
}

int32 ReadInt32LE(Stream *st) {
  int byte1,byte2,byte3,byte4;
  byte1 = st->ReadChar(st);
  byte2 = st->ReadChar(st);
  byte3 = st->ReadChar(st);
  byte4 = st->ReadChar(st);
  return byte1 + 256*byte2 + 256*256*byte3 + 256*256*256*byte4;
}

uint8 ReadUInt8LE(Stream *st) {
  return st->ReadChar(st);
}

uint16 ReadUInt16LE(Stream *st) {
  int byte1,byte2;
  byte1 = st->ReadChar(st);
  byte2 = st->ReadChar(st);
  return byte1 + 256*byte2;
}

uint32 ReadUInt32LE(Stream *st) {
  int byte1,byte2,byte3,byte4;
  byte1 = st->ReadChar(st);
  byte2 = st->ReadChar(st);
  byte3 = st->ReadChar(st);
  byte4 = st->ReadChar(st);
  return byte1 + 256*byte2 + 256*256*byte3 + 256*256*256*byte4;
}

real32 ReadReal32LE(Stream *st) {
  union {
    real32 ret;
    uint32 ret0;
  } u;
  u.ret0 = ReadUInt32LE(st);
  return u.ret;
}
