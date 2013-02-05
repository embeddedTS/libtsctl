#include "NetTWI.h"

void *NetTWIInit(tsctl *conn,int instance) {
  NetTWI *ret = malloc(sizeof(NetTWI));
  ret->instance = instance;
  ret->conn = conn;
  ret->in = ret->out = conn->st;
  ret->InitStatus = 1;
  ret->Init = (void *)NetTWIInit;
  ret->Fini = (void *)NetTWIFini;
  ret->Lock = (void *)NetTWILock;
  ret->Unlock = (void *)NetTWIUnlock;
  ret->Preempt = (void *)NetTWIPreempt;
  ret->Write = (void *)NetTWIWrite;
  ret->Read = (void *)NetTWIRead;
  return ret;
}

void *NetTWIFini(NetTWI *ob) {
  ob->InitStatus = 0;
}

int32 NetTWILock(NetTWI *ob,uint32 num,int32 flags) {
  Stream *out = ob->out;
  int ret_len;
  int32 ret;
  WriteInt16LE(ob->out,0x0006);
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
  if (ReadInt16LE(ob->in) != 0x0006) longjmp(ob->conn->exception,1);
  if (ReadInt8LE(ob->in) != 0x00) longjmp(ob->conn->exception,2);
  if (ReadInt8LE(ob->in) != 0x13) longjmp(ob->conn->exception,3);
  ret = ReadInt32LE(out);
  if (ReadInt8LE(ob->in) != 0x80) longjmp(ob->conn->exception,2);
  return ret;
} 

int32 NetTWIUnlock(NetTWI *ob,uint32 num,int32 flags) {
  Stream *out = ob->out;
  int ret_len;
  int32 ret;
  WriteInt16LE(ob->out,0x0006);
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
  if (ReadInt16LE(ob->in) != 0x0006) longjmp(ob->conn->exception,1);
  if (ReadInt8LE(ob->in) != 0x01) longjmp(ob->conn->exception,2);
  if (ReadInt8LE(ob->in) != 0x13) longjmp(ob->conn->exception,3);
  ret = ReadInt32LE(out);
  if (ReadInt8LE(ob->in) != 0x80) longjmp(ob->conn->exception,2);
  return ret;
} 

int32 NetTWIPreempt(NetTWI *ob) {
  Stream *out = ob->out;
  int ret_len;
  int32 ret;
  WriteInt16LE(ob->out,0x0006);
  WriteInt8LE(ob->out,ob->instance);
  WriteInt8LE(ob->out,0x02);
  ob->out->Flush(ob->out);
  if (ob->conn->mode > 0) {
    while (ob->conn->count) {
      ob->conn->count--;
      ReadInt32LE(ob->in);
    }
  }
  if (ReadInt16LE(ob->in) != 0x0006) longjmp(ob->conn->exception,1);
  if (ReadInt8LE(ob->in) != 0x02) longjmp(ob->conn->exception,2);
  if (ReadInt8LE(ob->in) != 0x13) longjmp(ob->conn->exception,3);
  ret = ReadInt32LE(out);
  if (ReadInt8LE(ob->in) != 0x80) longjmp(ob->conn->exception,2);
  return ret;
} 

TWIResult NetTWIWrite(NetTWI *ob,int32 devadr,int32 adrslen,int32 adrs,const int8* bytes) {
  Stream *out = ob->out;
  int ret_len;
  TWIResult ret;
  WriteInt16LE(ob->out,0x0006);
  WriteInt8LE(ob->out,ob->instance);
  WriteInt8LE(ob->out,0x03);
  WriteInt32LE(ob->out,devadr);
  WriteInt32LE(ob->out,adrslen);
  WriteInt32LE(ob->out,adrs);
  int i;
  WriteInt32LE(ob->out,ArrayLength(bytes));
  for (i=0;i<ArrayLength(bytes);i++) {
    WriteInt8LE(ob->out,bytes[i]);
  }
  ob->out->Flush(ob->out);
  if (ob->conn->mode > 0) {
    while (ob->conn->count) {
      ob->conn->count--;
      ReadInt32LE(ob->in);
    }
  }
  if (ReadInt16LE(ob->in) != 0x0006) longjmp(ob->conn->exception,1);
  if (ReadInt8LE(ob->in) != 0x03) longjmp(ob->conn->exception,2);
  if (ReadInt8LE(ob->in) != 0xC7) longjmp(ob->conn->exception,3);
  ret = ReadInt32LE(out);
  if (ReadInt8LE(ob->in) != 0x80) longjmp(ob->conn->exception,2);
  return ret;
} 

TWIResult NetTWIRead(NetTWI *ob,int32 devadr,int32 adrslen,int32 adrs,int8* bytes) {
  Stream *out = ob->out;
  int ret_len;
  TWIResult ret;
  WriteInt16LE(ob->out,0x0006);
  WriteInt8LE(ob->out,ob->instance);
  WriteInt8LE(ob->out,0x04);
  WriteInt32LE(ob->out,devadr);
  WriteInt32LE(ob->out,adrslen);
  WriteInt32LE(ob->out,adrs);
  WriteInt32LE(ob->out,ArrayLength(bytes));
  ob->out->Flush(ob->out);
  if (ob->conn->mode > 0) {
    while (ob->conn->count) {
      ob->conn->count--;
      ReadInt32LE(ob->in);
    }
  }
  if (ReadInt16LE(ob->in) != 0x0006) longjmp(ob->conn->exception,1);
  if (ReadInt8LE(ob->in) != 0x04) longjmp(ob->conn->exception,2);
  if (ReadInt8LE(ob->in) != 0xC7) longjmp(ob->conn->exception,3);
  ret = ReadInt32LE(out);
  if (ReadInt8LE(ob->in) != 0x50) longjmp(ob->conn->exception,3);
  if (ReadInt32LE(ob->in)!=ArrayLength(bytes)) longjmp(ob->conn->exception,5);
  {
    int i;
    for(i=0;i<ArrayLength(bytes);i++) {
      bytes[i] = ReadInt8LE(out);
    }
  }
  if (ReadInt8LE(ob->in) != 0x80) longjmp(ob->conn->exception,2);
  return ret;
} 

