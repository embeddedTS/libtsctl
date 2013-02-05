#include "NetDIO.h"

void *NetDIOInit(tsctl *conn,int instance) {
  NetDIO *ret = malloc(sizeof(NetDIO));
  ret->instance = instance;
  ret->conn = conn;
  ret->in = ret->out = conn->st;
  ret->InitStatus = 1;
  ret->Init = (void *)NetDIOInit;
  ret->Fini = (void *)NetDIOFini;
  ret->Lock = (void *)NetDIOLock;
  ret->Unlock = (void *)NetDIOUnlock;
  ret->Preempt = (void *)NetDIOPreempt;
  ret->Refresh = (void *)NetDIORefresh;
  ret->Commit = (void *)NetDIOCommit;
  ret->Set = (void *)NetDIOSet;
  ret->Get = (void *)NetDIOGet;
  ret->SetAsync = (void *)NetDIOSetAsync;
  ret->GetAsync = (void *)NetDIOGetAsync;
  ret->Wait = (void *)NetDIOWait;
  ret->Count = (void *)NetDIOCount;
  ret->Capabilities = (void *)NetDIOCapabilities;
  ret->GetMulti = (void *)NetDIOGetMulti;
  return ret;
}

void *NetDIOFini(NetDIO *ob) {
  ob->InitStatus = 0;
}

int32 NetDIOLock(NetDIO *ob,uint32 num,int32 flags) {
  Stream *out = ob->out;
  int ret_len;
  int32 ret;
  WriteInt16LE(ob->out,0x0005);
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
  if (ReadInt16LE(ob->in) != 0x0005) longjmp(ob->conn->exception,1);
  if (ReadInt8LE(ob->in) != 0x00) longjmp(ob->conn->exception,2);
  if (ReadInt8LE(ob->in) != 0x13) longjmp(ob->conn->exception,3);
  ret = ReadInt32LE(out);
  if (ReadInt8LE(ob->in) != 0x80) longjmp(ob->conn->exception,2);
  return ret;
} 

int32 NetDIOUnlock(NetDIO *ob,uint32 num,int32 flags) {
  Stream *out = ob->out;
  int ret_len;
  int32 ret;
  WriteInt16LE(ob->out,0x0005);
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
  if (ReadInt16LE(ob->in) != 0x0005) longjmp(ob->conn->exception,1);
  if (ReadInt8LE(ob->in) != 0x01) longjmp(ob->conn->exception,2);
  if (ReadInt8LE(ob->in) != 0x13) longjmp(ob->conn->exception,3);
  ret = ReadInt32LE(out);
  if (ReadInt8LE(ob->in) != 0x80) longjmp(ob->conn->exception,2);
  return ret;
} 

int32 NetDIOPreempt(NetDIO *ob) {
  Stream *out = ob->out;
  int ret_len;
  int32 ret;
  WriteInt16LE(ob->out,0x0005);
  WriteInt8LE(ob->out,ob->instance);
  WriteInt8LE(ob->out,0x02);
  ob->out->Flush(ob->out);
  if (ob->conn->mode > 0) {
    while (ob->conn->count) {
      ob->conn->count--;
      ReadInt32LE(ob->in);
    }
  }
  if (ReadInt16LE(ob->in) != 0x0005) longjmp(ob->conn->exception,1);
  if (ReadInt8LE(ob->in) != 0x02) longjmp(ob->conn->exception,2);
  if (ReadInt8LE(ob->in) != 0x13) longjmp(ob->conn->exception,3);
  ret = ReadInt32LE(out);
  if (ReadInt8LE(ob->in) != 0x80) longjmp(ob->conn->exception,2);
  return ret;
} 

void NetDIORefresh(NetDIO *ob) {
  Stream *out = ob->out;
  int ret_len;
  WriteInt16LE(ob->out,0x0005);
  WriteInt8LE(ob->out,ob->instance);
  WriteInt8LE(ob->out,0x03);
  if (ob->conn->mode > 0) ob->conn->count++;
  if (ob->conn->mode < 2)  ob->out->Flush(ob->out);
  if (ob->conn->mode > 0) return;
  if (ReadInt16LE(ob->in) != 0x0005) longjmp(ob->conn->exception,1);
  if (ReadInt8LE(ob->in) != 0x03) longjmp(ob->conn->exception,2);
  if (ReadInt8LE(ob->in) != 0x80) longjmp(ob->conn->exception,2);
} 

void NetDIOCommit(NetDIO *ob,int32 ForceAll) {
  Stream *out = ob->out;
  int ret_len;
  WriteInt16LE(ob->out,0x0005);
  WriteInt8LE(ob->out,ob->instance);
  WriteInt8LE(ob->out,0x04);
  WriteInt32LE(ob->out,ForceAll);
  if (ob->conn->mode > 0) ob->conn->count++;
  if (ob->conn->mode < 2)  ob->out->Flush(ob->out);
  if (ob->conn->mode > 0) return;
  if (ReadInt16LE(ob->in) != 0x0005) longjmp(ob->conn->exception,1);
  if (ReadInt8LE(ob->in) != 0x04) longjmp(ob->conn->exception,2);
  if (ReadInt8LE(ob->in) != 0x80) longjmp(ob->conn->exception,2);
} 

void NetDIOSet(NetDIO *ob,int32 DIONum,DIOState State) {
  Stream *out = ob->out;
  int ret_len;
  WriteInt16LE(ob->out,0x0005);
  WriteInt8LE(ob->out,ob->instance);
  WriteInt8LE(ob->out,0x05);
  WriteInt32LE(ob->out,DIONum);
  WriteInt32LE(ob->out,State);
  if (ob->conn->mode > 0) ob->conn->count++;
  if (ob->conn->mode < 2)  ob->out->Flush(ob->out);
  if (ob->conn->mode > 0) return;
  if (ReadInt16LE(ob->in) != 0x0005) longjmp(ob->conn->exception,1);
  if (ReadInt8LE(ob->in) != 0x05) longjmp(ob->conn->exception,2);
  if (ReadInt8LE(ob->in) != 0x80) longjmp(ob->conn->exception,2);
} 

DIOState NetDIOGet(NetDIO *ob,int32 DIONum) {
  Stream *out = ob->out;
  int ret_len;
  DIOState ret;
  WriteInt16LE(ob->out,0x0005);
  WriteInt8LE(ob->out,ob->instance);
  WriteInt8LE(ob->out,0x06);
  WriteInt32LE(ob->out,DIONum);
  ob->out->Flush(ob->out);
  if (ob->conn->mode > 0) {
    while (ob->conn->count) {
      ob->conn->count--;
      ReadInt32LE(ob->in);
    }
  }
  if (ReadInt16LE(ob->in) != 0x0005) longjmp(ob->conn->exception,1);
  if (ReadInt8LE(ob->in) != 0x06) longjmp(ob->conn->exception,2);
  if (ReadInt8LE(ob->in) != 0xC4) longjmp(ob->conn->exception,3);
  ret = ReadInt32LE(out);
  if (ReadInt8LE(ob->in) != 0x80) longjmp(ob->conn->exception,2);
  return ret;
} 

void NetDIOSetAsync(NetDIO *ob,int32 DIONum,DIOState State) {
  Stream *out = ob->out;
  int ret_len;
  WriteInt16LE(ob->out,0x0005);
  WriteInt8LE(ob->out,ob->instance);
  WriteInt8LE(ob->out,0x07);
  WriteInt32LE(ob->out,DIONum);
  WriteInt32LE(ob->out,State);
  if (ob->conn->mode > 0) ob->conn->count++;
  if (ob->conn->mode < 2)  ob->out->Flush(ob->out);
  if (ob->conn->mode > 0) return;
  if (ReadInt16LE(ob->in) != 0x0005) longjmp(ob->conn->exception,1);
  if (ReadInt8LE(ob->in) != 0x07) longjmp(ob->conn->exception,2);
  if (ReadInt8LE(ob->in) != 0x80) longjmp(ob->conn->exception,2);
} 

DIOState NetDIOGetAsync(NetDIO *ob,int32 DIONum) {
  Stream *out = ob->out;
  int ret_len;
  DIOState ret;
  WriteInt16LE(ob->out,0x0005);
  WriteInt8LE(ob->out,ob->instance);
  WriteInt8LE(ob->out,0x08);
  WriteInt32LE(ob->out,DIONum);
  ob->out->Flush(ob->out);
  if (ob->conn->mode > 0) {
    while (ob->conn->count) {
      ob->conn->count--;
      ReadInt32LE(ob->in);
    }
  }
  if (ReadInt16LE(ob->in) != 0x0005) longjmp(ob->conn->exception,1);
  if (ReadInt8LE(ob->in) != 0x08) longjmp(ob->conn->exception,2);
  if (ReadInt8LE(ob->in) != 0xC4) longjmp(ob->conn->exception,3);
  ret = ReadInt32LE(out);
  if (ReadInt8LE(ob->in) != 0x80) longjmp(ob->conn->exception,2);
  return ret;
} 

void NetDIOWait(NetDIO *ob,int32* match,int32 min,int32 max,const int32* nh,const int32* nl) {
  Stream *out = ob->out;
  int ret_len;
  WriteInt16LE(ob->out,0x0005);
  WriteInt8LE(ob->out,ob->instance);
  WriteInt8LE(ob->out,0x09);
  WriteInt32LE(ob->out,ArrayLength(match));
  WriteInt32LE(ob->out,min);
  WriteInt32LE(ob->out,max);
  int i;
  WriteInt32LE(ob->out,ArrayLength(nh));
  for (i=0;i<ArrayLength(nh);i++) {
    WriteInt32LE(ob->out,nh[i]);
  }
  WriteInt32LE(ob->out,ArrayLength(nl));
  for (i=0;i<ArrayLength(nl);i++) {
    WriteInt32LE(ob->out,nl[i]);
  }
  ob->out->Flush(ob->out);
  if (ob->conn->mode > 0) {
    while (ob->conn->count) {
      ob->conn->count--;
      ReadInt32LE(ob->in);
    }
  }
  if (ReadInt16LE(ob->in) != 0x0005) longjmp(ob->conn->exception,1);
  if (ReadInt8LE(ob->in) != 0x09) longjmp(ob->conn->exception,2);
  if (ReadInt8LE(ob->in) != 0x53) longjmp(ob->conn->exception,3);
  if (ReadInt32LE(ob->in)!=ArrayLength(match)) longjmp(ob->conn->exception,5);
  {
    int i;
    for(i=0;i<ArrayLength(match);i++) {
      match[i] = ReadInt32LE(out);
    }
  }
  if (ReadInt8LE(ob->in) != 0x80) longjmp(ob->conn->exception,2);
} 

uint32 NetDIOCount(NetDIO *ob) {
  Stream *out = ob->out;
  int ret_len;
  uint32 ret;
  WriteInt16LE(ob->out,0x0005);
  WriteInt8LE(ob->out,ob->instance);
  WriteInt8LE(ob->out,0x0A);
  ob->out->Flush(ob->out);
  if (ob->conn->mode > 0) {
    while (ob->conn->count) {
      ob->conn->count--;
      ReadInt32LE(ob->in);
    }
  }
  if (ReadInt16LE(ob->in) != 0x0005) longjmp(ob->conn->exception,1);
  if (ReadInt8LE(ob->in) != 0x0A) longjmp(ob->conn->exception,2);
  if (ReadInt8LE(ob->in) != 0x03) longjmp(ob->conn->exception,3);
  ret = ReadUInt32LE(out);
  if (ReadInt8LE(ob->in) != 0x80) longjmp(ob->conn->exception,2);
  return ret;
} 

DIOCaps NetDIOCapabilities(NetDIO *ob,uint32 num) {
  Stream *out = ob->out;
  int ret_len;
  DIOCaps ret;
  WriteInt16LE(ob->out,0x0005);
  WriteInt8LE(ob->out,ob->instance);
  WriteInt8LE(ob->out,0x0B);
  WriteUInt32LE(ob->out,num);
  ob->out->Flush(ob->out);
  if (ob->conn->mode > 0) {
    while (ob->conn->count) {
      ob->conn->count--;
      ReadInt32LE(ob->in);
    }
  }
  if (ReadInt16LE(ob->in) != 0x0005) longjmp(ob->conn->exception,1);
  if (ReadInt8LE(ob->in) != 0x0B) longjmp(ob->conn->exception,2);
  if (ReadInt8LE(ob->in) != 0xC5) longjmp(ob->conn->exception,3);
  ret = ReadInt32LE(out);
  if (ReadInt8LE(ob->in) != 0x80) longjmp(ob->conn->exception,2);
  return ret;
} 

int32 NetDIOGetMulti(NetDIO *ob,int8* state,int32 offset) {
  Stream *out = ob->out;
  int ret_len;
  int32 ret;
  WriteInt16LE(ob->out,0x0005);
  WriteInt8LE(ob->out,ob->instance);
  WriteInt8LE(ob->out,0x0C);
  WriteInt32LE(ob->out,ArrayLength(state));
  WriteInt32LE(ob->out,offset);
  ob->out->Flush(ob->out);
  if (ob->conn->mode > 0) {
    while (ob->conn->count) {
      ob->conn->count--;
      ReadInt32LE(ob->in);
    }
  }
  if (ReadInt16LE(ob->in) != 0x0005) longjmp(ob->conn->exception,1);
  if (ReadInt8LE(ob->in) != 0x0C) longjmp(ob->conn->exception,2);
  if (ReadInt8LE(ob->in) != 0x13) longjmp(ob->conn->exception,3);
  ret = ReadInt32LE(out);
  if (ReadInt8LE(ob->in) != 0x50) longjmp(ob->conn->exception,3);
  if (ReadInt32LE(ob->in)!=ArrayLength(state)) longjmp(ob->conn->exception,5);
  {
    int i;
    for(i=0;i<ArrayLength(state);i++) {
      state[i] = ReadInt8LE(out);
    }
  }
  if (ReadInt8LE(ob->in) != 0x80) longjmp(ob->conn->exception,2);
  return ret;
} 

