#include "NetPin.h"

void *NetPinInit(tsctl *conn,int instance) {
  NetPin *ret = malloc(sizeof(NetPin));
  ret->instance = instance;
  ret->conn = conn;
  ret->in = ret->out = conn->st;
  ret->InitStatus = 1;
  ret->Init = (void *)NetPinInit;
  ret->Fini = (void *)NetPinFini;
  ret->Lock = (void *)NetPinLock;
  ret->Unlock = (void *)NetPinUnlock;
  ret->Preempt = (void *)NetPinPreempt;
  ret->ModeGet = (void *)NetPinModeGet;
  ret->ModeSet = (void *)NetPinModeSet;
  return ret;
}

void *NetPinFini(NetPin *ob) {
  ob->InitStatus = 0;
}

int32 NetPinLock(NetPin *ob,uint32 num,int32 flags) {
  Stream *out = ob->out;
  int ret_len;
  int32 ret;
  WriteInt16LE(ob->out,0x0003);
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
  if (ReadInt16LE(ob->in) != 0x0003) longjmp(ob->conn->exception,1);
  if (ReadUInt8LE(ob->in) != 0x00) longjmp(ob->conn->exception,2);
  if (ReadUInt8LE(ob->in) != 0x13) longjmp(ob->conn->exception,3);
  ret = ReadInt32LE(out);
  if (ReadUInt8LE(ob->in) != 0x80) longjmp(ob->conn->exception,2);
  return ret;
} 

int32 NetPinUnlock(NetPin *ob,uint32 num,int32 flags) {
  Stream *out = ob->out;
  int ret_len;
  int32 ret;
  WriteInt16LE(ob->out,0x0003);
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
  if (ReadInt16LE(ob->in) != 0x0003) longjmp(ob->conn->exception,1);
  if (ReadUInt8LE(ob->in) != 0x01) longjmp(ob->conn->exception,2);
  if (ReadUInt8LE(ob->in) != 0x13) longjmp(ob->conn->exception,3);
  ret = ReadInt32LE(out);
  if (ReadUInt8LE(ob->in) != 0x80) longjmp(ob->conn->exception,2);
  return ret;
} 

int32 NetPinPreempt(NetPin *ob) {
  Stream *out = ob->out;
  int ret_len;
  int32 ret;
  WriteInt16LE(ob->out,0x0003);
  WriteInt8LE(ob->out,ob->instance);
  WriteInt8LE(ob->out,0x02);
  ob->out->Flush(ob->out);
  if (ob->conn->mode > 0) {
    while (ob->conn->count) {
      ob->conn->count--;
      ReadInt32LE(ob->in);
    }
  }
  if (ReadInt16LE(ob->in) != 0x0003) longjmp(ob->conn->exception,1);
  if (ReadUInt8LE(ob->in) != 0x02) longjmp(ob->conn->exception,2);
  if (ReadUInt8LE(ob->in) != 0x13) longjmp(ob->conn->exception,3);
  ret = ReadInt32LE(out);
  if (ReadUInt8LE(ob->in) != 0x80) longjmp(ob->conn->exception,2);
  return ret;
} 

PinMode NetPinModeGet(NetPin *ob,int32 PinNumber) {
  Stream *out = ob->out;
  int ret_len;
  PinMode ret;
  WriteInt16LE(ob->out,0x0003);
  WriteInt8LE(ob->out,ob->instance);
  WriteInt8LE(ob->out,0x03);
  WriteInt32LE(ob->out,PinNumber);
  ob->out->Flush(ob->out);
  if (ob->conn->mode > 0) {
    while (ob->conn->count) {
      ob->conn->count--;
      ReadInt32LE(ob->in);
    }
  }
  if (ReadInt16LE(ob->in) != 0x0003) longjmp(ob->conn->exception,1);
  if (ReadUInt8LE(ob->in) != 0x03) longjmp(ob->conn->exception,2);
  if (ReadUInt8LE(ob->in) != 0xC2) longjmp(ob->conn->exception,3);
  ret = ReadInt32LE(out);
  if (ReadUInt8LE(ob->in) != 0x80) longjmp(ob->conn->exception,2);
  return ret;
} 

PinResult NetPinModeSet(NetPin *ob,int32 PinNumber,PinMode Mode) {
  Stream *out = ob->out;
  int ret_len;
  PinResult ret;
  WriteInt16LE(ob->out,0x0003);
  WriteInt8LE(ob->out,ob->instance);
  WriteInt8LE(ob->out,0x04);
  WriteInt32LE(ob->out,PinNumber);
  WriteInt32LE(ob->out,Mode);
  ob->out->Flush(ob->out);
  if (ob->conn->mode > 0) {
    while (ob->conn->count) {
      ob->conn->count--;
      ReadInt32LE(ob->in);
    }
  }
  if (ReadInt16LE(ob->in) != 0x0003) longjmp(ob->conn->exception,1);
  if (ReadUInt8LE(ob->in) != 0x04) longjmp(ob->conn->exception,2);
  if (ReadUInt8LE(ob->in) != 0xC3) longjmp(ob->conn->exception,3);
  ret = ReadInt32LE(out);
  if (ReadUInt8LE(ob->in) != 0x80) longjmp(ob->conn->exception,2);
  return ret;
} 

