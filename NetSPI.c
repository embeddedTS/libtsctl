#include "NetSPI.h"

void *NetSPIInit(tsctl *conn,int instance) {
  NetSPI *ret = malloc(sizeof(NetSPI));
  ret->instance = instance;
  ret->conn = conn;
  ret->in = ret->out = conn->st;
  ret->InitStatus = 1;
  ret->Init = (void *)NetSPIInit;
  ret->Fini = (void *)NetSPIFini;
  ret->Lock = (void *)NetSPILock;
  ret->Unlock = (void *)NetSPIUnlock;
  ret->Preempt = (void *)NetSPIPreempt;
  ret->Write = (void *)NetSPIWrite;
  ret->Read = (void *)NetSPIRead;
  ret->ReadWrite = (void *)NetSPIReadWrite;
  ret->ClockSet = (void *)NetSPIClockSet;
  ret->EdgeSet = (void *)NetSPIEdgeSet;
  return ret;
}

void *NetSPIFini(NetSPI *ob) {
  ob->InitStatus = 0;
}

int32 NetSPILock(NetSPI *ob,uint32 num,int32 flags) {
  Stream *out = ob->out;
  int ret_len;
  int32 ret;
  WriteInt16LE(ob->out,0x0008);
  WriteInt8LE(ob->out,ob->instance);
  WriteInt8LE(ob->out,0x00);
  WriteUInt32LE(ob->out,num);
  WriteInt32LE(ob->out,flags);
  ob->out->Flush(ob->out);
  if (ob->conn->mode > 0) {
    while (ob->conn->count) {
      ob->conn->count--;
      ReadInt32LE(ob->in);
    }
  }
  if (ReadInt16LE(ob->in) != 0x0008) longjmp(ob->conn->exception,1);
  if (ReadInt8LE(ob->in) != 0x00) longjmp(ob->conn->exception,2);
  if (ReadInt8LE(ob->in) != 0x13) longjmp(ob->conn->exception,3);
  ret = ReadInt32LE(out);
  if (ReadInt8LE(ob->in) != 0x80) longjmp(ob->conn->exception,2);
  return ret;
} 

int32 NetSPIUnlock(NetSPI *ob,uint32 num,int32 flags) {
  Stream *out = ob->out;
  int ret_len;
  int32 ret;
  WriteInt16LE(ob->out,0x0008);
  WriteInt8LE(ob->out,ob->instance);
  WriteInt8LE(ob->out,0x01);
  WriteUInt32LE(ob->out,num);
  WriteInt32LE(ob->out,flags);
  ob->out->Flush(ob->out);
  if (ob->conn->mode > 0) {
    while (ob->conn->count) {
      ob->conn->count--;
      ReadInt32LE(ob->in);
    }
  }
  if (ReadInt16LE(ob->in) != 0x0008) longjmp(ob->conn->exception,1);
  if (ReadInt8LE(ob->in) != 0x01) longjmp(ob->conn->exception,2);
  if (ReadInt8LE(ob->in) != 0x13) longjmp(ob->conn->exception,3);
  ret = ReadInt32LE(out);
  if (ReadInt8LE(ob->in) != 0x80) longjmp(ob->conn->exception,2);
  return ret;
} 

int32 NetSPIPreempt(NetSPI *ob) {
  Stream *out = ob->out;
  int ret_len;
  int32 ret;
  WriteInt16LE(ob->out,0x0008);
  WriteInt8LE(ob->out,ob->instance);
  WriteInt8LE(ob->out,0x02);
  ob->out->Flush(ob->out);
  if (ob->conn->mode > 0) {
    while (ob->conn->count) {
      ob->conn->count--;
      ReadInt32LE(ob->in);
    }
  }
  if (ReadInt16LE(ob->in) != 0x0008) longjmp(ob->conn->exception,1);
  if (ReadInt8LE(ob->in) != 0x02) longjmp(ob->conn->exception,2);
  if (ReadInt8LE(ob->in) != 0x13) longjmp(ob->conn->exception,3);
  ret = ReadInt32LE(out);
  if (ReadInt8LE(ob->in) != 0x80) longjmp(ob->conn->exception,2);
  return ret;
} 

SPIResult NetSPIWrite(NetSPI *ob,int32 adrs,const uint8* buf) {
  Stream *out = ob->out;
  int ret_len;
  SPIResult ret;
  WriteInt16LE(ob->out,0x0008);
  WriteInt8LE(ob->out,ob->instance);
  WriteInt8LE(ob->out,0x03);
  WriteInt32LE(ob->out,adrs);
  int i;
  WriteInt32LE(ob->out,ArrayLength(buf));
  for (i=0;i<ArrayLength(buf);i++) {
    WriteUInt8LE(ob->out,buf[i]);
  }
  ob->out->Flush(ob->out);
  if (ob->conn->mode > 0) {
    while (ob->conn->count) {
      ob->conn->count--;
      ReadInt32LE(ob->in);
    }
  }
  if (ReadInt16LE(ob->in) != 0x0008) longjmp(ob->conn->exception,1);
  if (ReadInt8LE(ob->in) != 0x03) longjmp(ob->conn->exception,2);
  if (ReadInt8LE(ob->in) != 0xCC) longjmp(ob->conn->exception,3);
  ret = ReadInt32LE(out);
  if (ReadInt8LE(ob->in) != 0x80) longjmp(ob->conn->exception,2);
  return ret;
} 

SPIResult NetSPIRead(NetSPI *ob,int32 adrs,uint8* buf) {
  Stream *out = ob->out;
  int ret_len;
  SPIResult ret;
  WriteInt16LE(ob->out,0x0008);
  WriteInt8LE(ob->out,ob->instance);
  WriteInt8LE(ob->out,0x04);
  WriteInt32LE(ob->out,adrs);
  WriteInt32LE(ob->out,ArrayLength(buf));
  ob->out->Flush(ob->out);
  if (ob->conn->mode > 0) {
    while (ob->conn->count) {
      ob->conn->count--;
      ReadInt32LE(ob->in);
    }
  }
  if (ReadInt16LE(ob->in) != 0x0008) longjmp(ob->conn->exception,1);
  if (ReadInt8LE(ob->in) != 0x04) longjmp(ob->conn->exception,2);
  if (ReadInt8LE(ob->in) != 0xCC) longjmp(ob->conn->exception,3);
  ret = ReadInt32LE(out);
  if (ReadInt8LE(ob->in) != 0x40) longjmp(ob->conn->exception,3);
  if (ReadInt32LE(ob->in)!=ArrayLength(buf)) longjmp(ob->conn->exception,5);
  {
    int i;
    for(i=0;i<ArrayLength(buf);i++) {
      buf[i] = ReadUInt8LE(out);
    }
  }
  if (ReadInt8LE(ob->in) != 0x80) longjmp(ob->conn->exception,2);
  return ret;
} 

SPIResult NetSPIReadWrite(NetSPI *ob,int32 adrs,const uint8* wbuf,uint8* rbuf) {
  Stream *out = ob->out;
  int ret_len;
  SPIResult ret;
  WriteInt16LE(ob->out,0x0008);
  WriteInt8LE(ob->out,ob->instance);
  WriteInt8LE(ob->out,0x05);
  WriteInt32LE(ob->out,adrs);
  int i;
  WriteInt32LE(ob->out,ArrayLength(wbuf));
  for (i=0;i<ArrayLength(wbuf);i++) {
    WriteUInt8LE(ob->out,wbuf[i]);
  }
  WriteInt32LE(ob->out,ArrayLength(rbuf));
  ob->out->Flush(ob->out);
  if (ob->conn->mode > 0) {
    while (ob->conn->count) {
      ob->conn->count--;
      ReadInt32LE(ob->in);
    }
  }
  if (ReadInt16LE(ob->in) != 0x0008) longjmp(ob->conn->exception,1);
  if (ReadInt8LE(ob->in) != 0x05) longjmp(ob->conn->exception,2);
  if (ReadInt8LE(ob->in) != 0xCC) longjmp(ob->conn->exception,3);
  ret = ReadInt32LE(out);
  if (ReadInt8LE(ob->in) != 0x40) longjmp(ob->conn->exception,3);
  if (ReadInt32LE(ob->in)!=ArrayLength(rbuf)) longjmp(ob->conn->exception,5);
  {
    int i;
    for(i=0;i<ArrayLength(rbuf);i++) {
      rbuf[i] = ReadUInt8LE(out);
    }
  }
  if (ReadInt8LE(ob->in) != 0x80) longjmp(ob->conn->exception,2);
  return ret;
} 

SPIResult NetSPIClockSet(NetSPI *ob,uint32 hz) {
  Stream *out = ob->out;
  int ret_len;
  SPIResult ret;
  WriteInt16LE(ob->out,0x0008);
  WriteInt8LE(ob->out,ob->instance);
  WriteInt8LE(ob->out,0x06);
  WriteUInt32LE(ob->out,hz);
  ob->out->Flush(ob->out);
  if (ob->conn->mode > 0) {
    while (ob->conn->count) {
      ob->conn->count--;
      ReadInt32LE(ob->in);
    }
  }
  if (ReadInt16LE(ob->in) != 0x0008) longjmp(ob->conn->exception,1);
  if (ReadInt8LE(ob->in) != 0x06) longjmp(ob->conn->exception,2);
  if (ReadInt8LE(ob->in) != 0xCC) longjmp(ob->conn->exception,3);
  ret = ReadInt32LE(out);
  if (ReadInt8LE(ob->in) != 0x80) longjmp(ob->conn->exception,2);
  return ret;
} 

SPIResult NetSPIEdgeSet(NetSPI *ob,int32 posedge) {
  Stream *out = ob->out;
  int ret_len;
  SPIResult ret;
  WriteInt16LE(ob->out,0x0008);
  WriteInt8LE(ob->out,ob->instance);
  WriteInt8LE(ob->out,0x07);
  WriteInt32LE(ob->out,posedge);
  ob->out->Flush(ob->out);
  if (ob->conn->mode > 0) {
    while (ob->conn->count) {
      ob->conn->count--;
      ReadInt32LE(ob->in);
    }
  }
  if (ReadInt16LE(ob->in) != 0x0008) longjmp(ob->conn->exception,1);
  if (ReadInt8LE(ob->in) != 0x07) longjmp(ob->conn->exception,2);
  if (ReadInt8LE(ob->in) != 0xCC) longjmp(ob->conn->exception,3);
  ret = ReadInt32LE(out);
  if (ReadInt8LE(ob->in) != 0x80) longjmp(ob->conn->exception,2);
  return ret;
} 

