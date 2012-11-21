#ifndef __Stream_H
#define __Stream_H
#include <stdio.h>
#include "ts/Array.h"
#include "ts/types.h"

typedef struct Stream Stream;

struct Stream {
  void (*Fini)(Stream *);
  int (*Read)(Stream *,char *bytes,int len);  
  int (*Unread)(Stream *st,int ch);
  int (*ReadChar)(Stream *st);
  unsigned (*InputReady)(Stream *st);
  int (*Write)(Stream *,char *bytes,int len);
  int (*WriteChar)(Stream *st,char byte);
  int (*isEOF)(Stream *st);
  int outputOffset;
};

typedef struct {
  void (*Fini)(Stream *);
  int (*Read)(Stream *,char *bytes,int len);  
  int (*Unread)(Stream *st,int ch);
  int (*ReadChar)(Stream *st);
  unsigned (*InputReady)(Stream *st);
  int (*Write)(Stream *,char *bytes,int len);
  int (*WriteChar)(Stream *st,char byte);
  int (*isEOF)(Stream *st);
  int outputOffset;
  FILE *I,*O;
} FileStream;

typedef struct {
  void (*Fini)(Stream *);
  int (*Read)(Stream *,char *bytes,int len);  
  int (*Unread)(Stream *st,int ch);
  int (*ReadChar)(Stream *st);
  unsigned (*InputReady)(Stream *st);
  int (*Write)(Stream *,char *bytes,int len);
  int (*WriteChar)(Stream *st,char byte);
  int (*isEOF)(Stream *st);
  int outputOffset;
  int i,o,iptr,ilen;
  int8 *ibuf;
} DescriptorStream;

typedef struct {
  void (*Fini)(Stream *);
  int (*Read)(Stream *,char *bytes,int len);  
  int (*Unread)(Stream *st,int ch);
  int (*ReadChar)(Stream *st);
  unsigned (*InputReady)(Stream *st);
  int (*Write)(Stream *,char *bytes,int len);
  int (*WriteChar)(Stream *st,char byte);
  int (*isEOF)(Stream *st);
  int outputOffset;
  int inputOffset;
  int8** input;
  int8** output;
} StringStream;

Stream *FileStreamInit(FILE *in,FILE *out);
Stream *DescriptorStreamInit(int in,int out);
Stream *StringStreamInit(int8** in,int8** out);

// static int Skip(Stream *st,int len)
int StreamCopy(Stream *out,Stream *in,unsigned len);

int WriteArray(Stream *,void *);
int WriteASCIIZ(Stream *,char *);
int WriteF(Stream *,char *,...);
int WriteInt(Stream *,int val,int base,int minchars,char pad);
int WriteUInt(Stream *,uint val,int base,int minchars,char pad);
int WriteReal64A(Stream *st,real64 val,int pre,int post);

int8* ReadArrayInt8LE(Stream *st);
uint8* ReadArrayUInt8LE(Stream *st);
int16* ReadArrayInt16LE(Stream *st);
int32* ReadArrayInt32LE(Stream *st);
real32* ReadArrayReal32LE(Stream *st);

int WriteInt8LE(Stream *st,int8 value);
int WriteInt16LE(Stream *st,int16 value);
int WriteInt32LE(Stream *st,int32 value);
int WriteUInt8LE(Stream *st,uint8 value);
int WriteUInt16LE(Stream *st,uint16 value);
int WriteUInt32LE(Stream *st,uint32 value);
int WriteReal32LE(Stream *st,real32 value);

int8 ReadInt8LE(Stream *st);
int16 ReadInt16LE(Stream *st);
int32 ReadInt32LE(Stream *st);
uint8 ReadUInt8LE(Stream *st);
uint16 ReadUInt16LE(Stream *st);
uint32 ReadUInt32LE(Stream *st);
real32 ReadReal32LE(Stream *st);

#endif
