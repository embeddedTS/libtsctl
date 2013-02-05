#include "NetTime.h"

void *NetTimeInit(tsctl *conn,int instance) {
  NetTime *ret = malloc(sizeof(NetTime));
  ret->instance = instance;
  ret->conn = conn;
  ret->in = ret->out = conn->st;
  ret->InitStatus = 1;
  ret->Init = (void *)NetTimeInit;
  ret->Fini = (void *)NetTimeFini;
  ret->Wait = (void *)NetTimeWait;
  ret->Delay = (void *)NetTimeDelay;
  ret->Tick = (void *)NetTimeTick;
  ret->usElapsed = (void *)NetTimeusElapsed;
  ret->usFuture = (void *)NetTimeusFuture;
  ret->TimeoutQ = (void *)NetTimeTimeoutQ;
  ret->TPS = (void *)NetTimeTPS;
  return ret;
}

void *NetTimeFini(NetTime *ob) {
  ob->InitStatus = 0;
}

uint32 NetTimeWait(NetTime *ob,uint32 microseconds) {
  Stream *out = ob->out;
  int ret_len;
  uint32 ret;
  WriteInt16LE(ob->out,0x0002);
  WriteInt8LE(ob->out,ob->instance);
  WriteInt8LE(ob->out,0x00);
  WriteUInt32LE(ob->out,microseconds);
  ob->out->Flush(ob->out);
  if (ob->conn->mode > 0) {
    while (ob->conn->count) {
      ob->conn->count--;
      ReadInt32LE(ob->in);
    }
  }
  if (ReadInt16LE(ob->in) != 0x0002) longjmp(ob->conn->exception,1);
  if (ReadInt8LE(ob->in) != 0x00) longjmp(ob->conn->exception,2);
  if (ReadInt8LE(ob->in) != 0x03) longjmp(ob->conn->exception,3);
  ret = ReadUInt32LE(out);
  if (ReadInt8LE(ob->in) != 0x80) longjmp(ob->conn->exception,2);
  return ret;
} 

void NetTimeDelay(NetTime *ob,uint32 microseconds) {
  Stream *out = ob->out;
  int ret_len;
  WriteInt16LE(ob->out,0x0002);
  WriteInt8LE(ob->out,ob->instance);
  WriteInt8LE(ob->out,0x01);
  WriteUInt32LE(ob->out,microseconds);
  if (ob->conn->mode > 0) ob->conn->count++;
  if (ob->conn->mode < 2)  ob->out->Flush(ob->out);
  if (ob->conn->mode > 0) return;
  if (ReadInt16LE(ob->in) != 0x0002) longjmp(ob->conn->exception,1);
  if (ReadInt8LE(ob->in) != 0x01) longjmp(ob->conn->exception,2);
  if (ReadInt8LE(ob->in) != 0x80) longjmp(ob->conn->exception,2);
} 

uint32 NetTimeTick(NetTime *ob) {
  Stream *out = ob->out;
  int ret_len;
  uint32 ret;
  WriteInt16LE(ob->out,0x0002);
  WriteInt8LE(ob->out,ob->instance);
  WriteInt8LE(ob->out,0x02);
  ob->out->Flush(ob->out);
  if (ob->conn->mode > 0) {
    while (ob->conn->count) {
      ob->conn->count--;
      ReadInt32LE(ob->in);
    }
  }
  if (ReadInt16LE(ob->in) != 0x0002) longjmp(ob->conn->exception,1);
  if (ReadInt8LE(ob->in) != 0x02) longjmp(ob->conn->exception,2);
  if (ReadInt8LE(ob->in) != 0x03) longjmp(ob->conn->exception,3);
  ret = ReadUInt32LE(out);
  if (ReadInt8LE(ob->in) != 0x80) longjmp(ob->conn->exception,2);
  return ret;
} 

uint32 NetTimeusElapsed(NetTime *ob,uint32 start) {
  Stream *out = ob->out;
  int ret_len;
  uint32 ret;
  WriteInt16LE(ob->out,0x0002);
  WriteInt8LE(ob->out,ob->instance);
  WriteInt8LE(ob->out,0x03);
  WriteUInt32LE(ob->out,start);
  ob->out->Flush(ob->out);
  if (ob->conn->mode > 0) {
    while (ob->conn->count) {
      ob->conn->count--;
      ReadInt32LE(ob->in);
    }
  }
  if (ReadInt16LE(ob->in) != 0x0002) longjmp(ob->conn->exception,1);
  if (ReadInt8LE(ob->in) != 0x03) longjmp(ob->conn->exception,2);
  if (ReadInt8LE(ob->in) != 0x03) longjmp(ob->conn->exception,3);
  ret = ReadUInt32LE(out);
  if (ReadInt8LE(ob->in) != 0x80) longjmp(ob->conn->exception,2);
  return ret;
} 

uint32 NetTimeusFuture(NetTime *ob,uint32 start,uint32 microseconds) {
  Stream *out = ob->out;
  int ret_len;
  uint32 ret;
  WriteInt16LE(ob->out,0x0002);
  WriteInt8LE(ob->out,ob->instance);
  WriteInt8LE(ob->out,0x04);
  WriteUInt32LE(ob->out,start);
  WriteUInt32LE(ob->out,microseconds);
  ob->out->Flush(ob->out);
  if (ob->conn->mode > 0) {
    while (ob->conn->count) {
      ob->conn->count--;
      ReadInt32LE(ob->in);
    }
  }
  if (ReadInt16LE(ob->in) != 0x0002) longjmp(ob->conn->exception,1);
  if (ReadInt8LE(ob->in) != 0x04) longjmp(ob->conn->exception,2);
  if (ReadInt8LE(ob->in) != 0x03) longjmp(ob->conn->exception,3);
  ret = ReadUInt32LE(out);
  if (ReadInt8LE(ob->in) != 0x80) longjmp(ob->conn->exception,2);
  return ret;
} 

TimeResult NetTimeTimeoutQ(NetTime *ob,uint32 start,uint32 end) {
  Stream *out = ob->out;
  int ret_len;
  TimeResult ret;
  WriteInt16LE(ob->out,0x0002);
  WriteInt8LE(ob->out,ob->instance);
  WriteInt8LE(ob->out,0x05);
  WriteUInt32LE(ob->out,start);
  WriteUInt32LE(ob->out,end);
  ob->out->Flush(ob->out);
  if (ob->conn->mode > 0) {
    while (ob->conn->count) {
      ob->conn->count--;
      ReadInt32LE(ob->in);
    }
  }
  if (ReadInt16LE(ob->in) != 0x0002) longjmp(ob->conn->exception,1);
  if (ReadInt8LE(ob->in) != 0x05) longjmp(ob->conn->exception,2);
  if (ReadInt8LE(ob->in) != 0xC1) longjmp(ob->conn->exception,3);
  ret = ReadInt32LE(out);
  if (ReadInt8LE(ob->in) != 0x80) longjmp(ob->conn->exception,2);
  return ret;
} 

uint32 NetTimeTPS(NetTime *ob) {
  Stream *out = ob->out;
  int ret_len;
  uint32 ret;
  WriteInt16LE(ob->out,0x0002);
  WriteInt8LE(ob->out,ob->instance);
  WriteInt8LE(ob->out,0x06);
  ob->out->Flush(ob->out);
  if (ob->conn->mode > 0) {
    while (ob->conn->count) {
      ob->conn->count--;
      ReadInt32LE(ob->in);
    }
  }
  if (ReadInt16LE(ob->in) != 0x0002) longjmp(ob->conn->exception,1);
  if (ReadInt8LE(ob->in) != 0x06) longjmp(ob->conn->exception,2);
  if (ReadInt8LE(ob->in) != 0x03) longjmp(ob->conn->exception,3);
  ret = ReadUInt32LE(out);
  if (ReadInt8LE(ob->in) != 0x80) longjmp(ob->conn->exception,2);
  return ret;
} 

