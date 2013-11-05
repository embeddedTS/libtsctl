#include "NetEDIO.h"

void *NetEDIOInit(tsctl *conn,int instance) {
  NetEDIO *ret = malloc(sizeof(NetEDIO));
  ret->instance = instance;
  ret->conn = conn;
  ret->in = ret->out = conn->st;
  ret->InitStatus = 1;
  ret->Init = (void *)NetEDIOInit;
  ret->Fini = (void *)NetEDIOFini;
  ret->Lock = (void *)NetEDIOLock;
  ret->Unlock = (void *)NetEDIOUnlock;
  ret->Preempt = (void *)NetEDIOPreempt;
  ret->QueryFunction = (void *)NetEDIOQueryFunction;
  ret->PWM = (void *)NetEDIOPWM;
  ret->QueryPWM = (void *)NetEDIOQueryPWM;
  ret->PWMfd = (void *)NetEDIOPWMfd;
  ret->QueryPWMfd = (void *)NetEDIOQueryPWMfd;
  ret->QuadratureCount = (void *)NetEDIOQuadratureCount;
  ret->EdgeCount = (void *)NetEDIOEdgeCount;
  ret->Glitched = (void *)NetEDIOGlitched;
  ret->HBridge = (void *)NetEDIOHBridge;
  return ret;
}

void *NetEDIOFini(NetEDIO *ob) {
  ob->InitStatus = 0;
}

int32 NetEDIOLock(NetEDIO *ob,uint32 num,int32 flags) {
  Stream *out = ob->out;
  int ret_len;
  int32 ret;
  WriteInt16LE(ob->out,0x000A);
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
  if (ReadInt16LE(ob->in) != 0x000A) longjmp(ob->conn->exception,1);
  if (ReadUInt8LE(ob->in) != 0x00) longjmp(ob->conn->exception,2);
  if (ReadUInt8LE(ob->in) != 0x13) longjmp(ob->conn->exception,3);
  ret = ReadInt32LE(out);
  if (ReadUInt8LE(ob->in) != 0x80) longjmp(ob->conn->exception,2);
  return ret;
} 

int32 NetEDIOUnlock(NetEDIO *ob,uint32 num,int32 flags) {
  Stream *out = ob->out;
  int ret_len;
  int32 ret;
  WriteInt16LE(ob->out,0x000A);
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
  if (ReadInt16LE(ob->in) != 0x000A) longjmp(ob->conn->exception,1);
  if (ReadUInt8LE(ob->in) != 0x01) longjmp(ob->conn->exception,2);
  if (ReadUInt8LE(ob->in) != 0x13) longjmp(ob->conn->exception,3);
  ret = ReadInt32LE(out);
  if (ReadUInt8LE(ob->in) != 0x80) longjmp(ob->conn->exception,2);
  return ret;
} 

int32 NetEDIOPreempt(NetEDIO *ob) {
  Stream *out = ob->out;
  int ret_len;
  int32 ret;
  WriteInt16LE(ob->out,0x000A);
  WriteInt8LE(ob->out,ob->instance);
  WriteInt8LE(ob->out,0x02);
  ob->out->Flush(ob->out);
  if (ob->conn->mode > 0) {
    while (ob->conn->count) {
      ob->conn->count--;
      ReadInt32LE(ob->in);
    }
  }
  if (ReadInt16LE(ob->in) != 0x000A) longjmp(ob->conn->exception,1);
  if (ReadUInt8LE(ob->in) != 0x02) longjmp(ob->conn->exception,2);
  if (ReadUInt8LE(ob->in) != 0x13) longjmp(ob->conn->exception,3);
  ret = ReadInt32LE(out);
  if (ReadUInt8LE(ob->in) != 0x80) longjmp(ob->conn->exception,2);
  return ret;
} 

int32* NetEDIOQueryFunction(NetEDIO *ob,EDIOType type) {
  Stream *out = ob->out;
  int ret_len;
  int32* ret;
  WriteInt16LE(ob->out,0x000A);
  WriteInt8LE(ob->out,ob->instance);
  WriteInt8LE(ob->out,0x03);
  WriteInt32LE(ob->out,type);
  ob->out->Flush(ob->out);
  if (ob->conn->mode > 0) {
    while (ob->conn->count) {
      ob->conn->count--;
      ReadInt32LE(ob->in);
    }
  }
  if (ReadInt16LE(ob->in) != 0x000A) longjmp(ob->conn->exception,1);
  if (ReadUInt8LE(ob->in) != 0x03) longjmp(ob->conn->exception,2);
  if (ReadUInt8LE(ob->in) != 0x53) longjmp(ob->conn->exception,3);
  ret_len = ReadInt32LE(ob->in);
  ret = ArrayAlloc(ret_len,4);
  {
    int i;
    for(i=0;i<ret_len;i++) {
      ret[i] = ReadInt32LE(out);
    }
  }
  if (ReadUInt8LE(ob->in) != 0x80) longjmp(ob->conn->exception,2);
  return ret;
} 

int32 NetEDIOPWM(NetEDIO *ob,int32 num,uint32 periodHigh,uint32 periodLow) {
  Stream *out = ob->out;
  int ret_len;
  int32 ret;
  WriteInt16LE(ob->out,0x000A);
  WriteInt8LE(ob->out,ob->instance);
  WriteInt8LE(ob->out,0x04);
  WriteInt32LE(ob->out,num);
  WriteUInt32LE(ob->out,periodHigh);
  WriteUInt32LE(ob->out,periodLow);
  ob->out->Flush(ob->out);
  if (ob->conn->mode > 0) {
    while (ob->conn->count) {
      ob->conn->count--;
      ReadInt32LE(ob->in);
    }
  }
  if (ReadInt16LE(ob->in) != 0x000A) longjmp(ob->conn->exception,1);
  if (ReadUInt8LE(ob->in) != 0x04) longjmp(ob->conn->exception,2);
  if (ReadUInt8LE(ob->in) != 0x13) longjmp(ob->conn->exception,3);
  ret = ReadInt32LE(out);
  if (ReadUInt8LE(ob->in) != 0x80) longjmp(ob->conn->exception,2);
  return ret;
} 

int32 NetEDIOQueryPWM(NetEDIO *ob,int32 num,uint32 periodHigh[1],uint32 periodLow[1]) {
  Stream *out = ob->out;
  int ret_len;
  int32 ret;
  WriteInt16LE(ob->out,0x000A);
  WriteInt8LE(ob->out,ob->instance);
  WriteInt8LE(ob->out,0x05);
  WriteInt32LE(ob->out,num);
  ob->out->Flush(ob->out);
  if (ob->conn->mode > 0) {
    while (ob->conn->count) {
      ob->conn->count--;
      ReadInt32LE(ob->in);
    }
  }
  if (ReadInt16LE(ob->in) != 0x000A) longjmp(ob->conn->exception,1);
  if (ReadUInt8LE(ob->in) != 0x05) longjmp(ob->conn->exception,2);
  if (ReadUInt8LE(ob->in) != 0x13) longjmp(ob->conn->exception,3);
  ret = ReadInt32LE(out);
  if (ReadUInt8LE(ob->in) != 0x43) longjmp(ob->conn->exception,3);
  ReadInt32LE(out);
  {
    int i;
    for(i=0;i<1;i++) {
      periodHigh[i] = ReadUInt32LE(out);
    }
  }
  if (ReadUInt8LE(ob->in) != 0x43) longjmp(ob->conn->exception,3);
  ReadInt32LE(out);
  {
    int i;
    for(i=0;i<1;i++) {
      periodLow[i] = ReadUInt32LE(out);
    }
  }
  if (ReadUInt8LE(ob->in) != 0x80) longjmp(ob->conn->exception,2);
  return ret;
} 

int32 NetEDIOPWMfd(NetEDIO *ob,int32 num,uint32 freq,uint32 DC) {
  Stream *out = ob->out;
  int ret_len;
  int32 ret;
  WriteInt16LE(ob->out,0x000A);
  WriteInt8LE(ob->out,ob->instance);
  WriteInt8LE(ob->out,0x06);
  WriteInt32LE(ob->out,num);
  WriteUInt32LE(ob->out,freq);
  WriteUInt32LE(ob->out,DC);
  ob->out->Flush(ob->out);
  if (ob->conn->mode > 0) {
    while (ob->conn->count) {
      ob->conn->count--;
      ReadInt32LE(ob->in);
    }
  }
  if (ReadInt16LE(ob->in) != 0x000A) longjmp(ob->conn->exception,1);
  if (ReadUInt8LE(ob->in) != 0x06) longjmp(ob->conn->exception,2);
  if (ReadUInt8LE(ob->in) != 0x13) longjmp(ob->conn->exception,3);
  ret = ReadInt32LE(out);
  if (ReadUInt8LE(ob->in) != 0x80) longjmp(ob->conn->exception,2);
  return ret;
} 

int32 NetEDIOQueryPWMfd(NetEDIO *ob,int32 num,uint32 freq[1],uint32 DC[1]) {
  Stream *out = ob->out;
  int ret_len;
  int32 ret;
  WriteInt16LE(ob->out,0x000A);
  WriteInt8LE(ob->out,ob->instance);
  WriteInt8LE(ob->out,0x07);
  WriteInt32LE(ob->out,num);
  ob->out->Flush(ob->out);
  if (ob->conn->mode > 0) {
    while (ob->conn->count) {
      ob->conn->count--;
      ReadInt32LE(ob->in);
    }
  }
  if (ReadInt16LE(ob->in) != 0x000A) longjmp(ob->conn->exception,1);
  if (ReadUInt8LE(ob->in) != 0x07) longjmp(ob->conn->exception,2);
  if (ReadUInt8LE(ob->in) != 0x13) longjmp(ob->conn->exception,3);
  ret = ReadInt32LE(out);
  if (ReadUInt8LE(ob->in) != 0x43) longjmp(ob->conn->exception,3);
  ReadInt32LE(out);
  {
    int i;
    for(i=0;i<1;i++) {
      freq[i] = ReadUInt32LE(out);
    }
  }
  if (ReadUInt8LE(ob->in) != 0x43) longjmp(ob->conn->exception,3);
  ReadInt32LE(out);
  {
    int i;
    for(i=0;i<1;i++) {
      DC[i] = ReadUInt32LE(out);
    }
  }
  if (ReadUInt8LE(ob->in) != 0x80) longjmp(ob->conn->exception,2);
  return ret;
} 

int32 NetEDIOQuadratureCount(NetEDIO *ob,int32 num) {
  Stream *out = ob->out;
  int ret_len;
  int32 ret;
  WriteInt16LE(ob->out,0x000A);
  WriteInt8LE(ob->out,ob->instance);
  WriteInt8LE(ob->out,0x08);
  WriteInt32LE(ob->out,num);
  ob->out->Flush(ob->out);
  if (ob->conn->mode > 0) {
    while (ob->conn->count) {
      ob->conn->count--;
      ReadInt32LE(ob->in);
    }
  }
  if (ReadInt16LE(ob->in) != 0x000A) longjmp(ob->conn->exception,1);
  if (ReadUInt8LE(ob->in) != 0x08) longjmp(ob->conn->exception,2);
  if (ReadUInt8LE(ob->in) != 0x13) longjmp(ob->conn->exception,3);
  ret = ReadInt32LE(out);
  if (ReadUInt8LE(ob->in) != 0x80) longjmp(ob->conn->exception,2);
  return ret;
} 

uint32 NetEDIOEdgeCount(NetEDIO *ob,int32 num,int32 edge) {
  Stream *out = ob->out;
  int ret_len;
  uint32 ret;
  WriteInt16LE(ob->out,0x000A);
  WriteInt8LE(ob->out,ob->instance);
  WriteInt8LE(ob->out,0x09);
  WriteInt32LE(ob->out,num);
  WriteInt32LE(ob->out,edge);
  ob->out->Flush(ob->out);
  if (ob->conn->mode > 0) {
    while (ob->conn->count) {
      ob->conn->count--;
      ReadInt32LE(ob->in);
    }
  }
  if (ReadInt16LE(ob->in) != 0x000A) longjmp(ob->conn->exception,1);
  if (ReadUInt8LE(ob->in) != 0x09) longjmp(ob->conn->exception,2);
  if (ReadUInt8LE(ob->in) != 0x03) longjmp(ob->conn->exception,3);
  ret = ReadUInt32LE(out);
  if (ReadUInt8LE(ob->in) != 0x80) longjmp(ob->conn->exception,2);
  return ret;
} 

int32 NetEDIOGlitched(NetEDIO *ob,int32 num) {
  Stream *out = ob->out;
  int ret_len;
  int32 ret;
  WriteInt16LE(ob->out,0x000A);
  WriteInt8LE(ob->out,ob->instance);
  WriteInt8LE(ob->out,0x0A);
  WriteInt32LE(ob->out,num);
  ob->out->Flush(ob->out);
  if (ob->conn->mode > 0) {
    while (ob->conn->count) {
      ob->conn->count--;
      ReadInt32LE(ob->in);
    }
  }
  if (ReadInt16LE(ob->in) != 0x000A) longjmp(ob->conn->exception,1);
  if (ReadUInt8LE(ob->in) != 0x0A) longjmp(ob->conn->exception,2);
  if (ReadUInt8LE(ob->in) != 0x13) longjmp(ob->conn->exception,3);
  ret = ReadInt32LE(out);
  if (ReadUInt8LE(ob->in) != 0x80) longjmp(ob->conn->exception,2);
  return ret;
} 

int32 NetEDIOHBridge(NetEDIO *ob,int32 num,HBState state) {
  Stream *out = ob->out;
  int ret_len;
  int32 ret;
  WriteInt16LE(ob->out,0x000A);
  WriteInt8LE(ob->out,ob->instance);
  WriteInt8LE(ob->out,0x0B);
  WriteInt32LE(ob->out,num);
  WriteInt32LE(ob->out,state);
  ob->out->Flush(ob->out);
  if (ob->conn->mode > 0) {
    while (ob->conn->count) {
      ob->conn->count--;
      ReadInt32LE(ob->in);
    }
  }
  if (ReadInt16LE(ob->in) != 0x000A) longjmp(ob->conn->exception,1);
  if (ReadUInt8LE(ob->in) != 0x0B) longjmp(ob->conn->exception,2);
  if (ReadUInt8LE(ob->in) != 0x13) longjmp(ob->conn->exception,3);
  ret = ReadInt32LE(out);
  if (ReadUInt8LE(ob->in) != 0x80) longjmp(ob->conn->exception,2);
  return ret;
} 

