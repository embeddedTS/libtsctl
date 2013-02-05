#include "NetSystem.h"

void *NetSystemInit(tsctl *conn,int instance) {
  NetSystem *ret = malloc(sizeof(NetSystem));
  ret->instance = instance;
  ret->conn = conn;
  ret->in = ret->out = conn->st;
  ret->InitStatus = 1;
  ret->Init = (void *)NetSystemInit;
  ret->Fini = (void *)NetSystemFini;
  ret->ClassCount = (void *)NetSystemClassCount;
  ret->InstanceCount = (void *)NetSystemInstanceCount;
  ret->APICount = (void *)NetSystemAPICount;
  ret->LockCount = (void *)NetSystemLockCount;
  ret->LockHolderInfo = (void *)NetSystemLockHolderInfo;
  ret->ConnWaitInfo = (void *)NetSystemConnWaitInfo;
  ret->CANBusGet = (void *)NetSystemCANBusGet;
  ret->BuildTime = (void *)NetSystemBuildTime;
  ret->ModelId = (void *)NetSystemModelId;
  ret->BaseBoardId = (void *)NetSystemBaseBoardId;
  ret->MapLength = (void *)NetSystemMapLength;
  ret->MapGet = (void *)NetSystemMapGet;
  ret->MapLookup = (void *)NetSystemMapLookup;
  ret->MapLookupPartial = (void *)NetSystemMapLookupPartial;
  ret->MapAdd = (void *)NetSystemMapAdd;
  ret->MapDelete = (void *)NetSystemMapDelete;
  ret->Note = (void *)NetSystemNote;
  ret->Version = (void *)NetSystemVersion;
  ret->UptimeServer = (void *)NetSystemUptimeServer;
  ret->UptimeHost = (void *)NetSystemUptimeHost;
  ret->FPGARevision = (void *)NetSystemFPGARevision;
  ret->EchoNumber = (void *)NetSystemEchoNumber;
  return ret;
}

void *NetSystemFini(NetSystem *ob) {
  ob->InitStatus = 0;
}

int32 NetSystemClassCount(NetSystem *ob) {
  Stream *out = ob->out;
  int ret_len;
  int32 ret;
  WriteInt16LE(ob->out,0x0000);
  WriteInt8LE(ob->out,ob->instance);
  WriteInt8LE(ob->out,0x00);
  ob->out->Flush(ob->out);
  if (ob->conn->mode > 0) {
    while (ob->conn->count) {
      ob->conn->count--;
      ReadInt32LE(ob->in);
    }
  }
  if (ReadInt16LE(ob->in) != 0x0000) longjmp(ob->conn->exception,1);
  if (ReadInt8LE(ob->in) != 0x00) longjmp(ob->conn->exception,2);
  if (ReadInt8LE(ob->in) != 0x13) longjmp(ob->conn->exception,3);
  ret = ReadInt32LE(out);
  if (ReadInt8LE(ob->in) != 0x80) longjmp(ob->conn->exception,2);
  return ret;
} 

int32 NetSystemInstanceCount(NetSystem *ob,int32 ClassNumber) {
  Stream *out = ob->out;
  int ret_len;
  int32 ret;
  WriteInt16LE(ob->out,0x0000);
  WriteInt8LE(ob->out,ob->instance);
  WriteInt8LE(ob->out,0x01);
  WriteInt32LE(ob->out,ClassNumber);
  ob->out->Flush(ob->out);
  if (ob->conn->mode > 0) {
    while (ob->conn->count) {
      ob->conn->count--;
      ReadInt32LE(ob->in);
    }
  }
  if (ReadInt16LE(ob->in) != 0x0000) longjmp(ob->conn->exception,1);
  if (ReadInt8LE(ob->in) != 0x01) longjmp(ob->conn->exception,2);
  if (ReadInt8LE(ob->in) != 0x13) longjmp(ob->conn->exception,3);
  ret = ReadInt32LE(out);
  if (ReadInt8LE(ob->in) != 0x80) longjmp(ob->conn->exception,2);
  return ret;
} 

int32 NetSystemAPICount(NetSystem *ob,int32 ClassNumber) {
  Stream *out = ob->out;
  int ret_len;
  int32 ret;
  WriteInt16LE(ob->out,0x0000);
  WriteInt8LE(ob->out,ob->instance);
  WriteInt8LE(ob->out,0x02);
  WriteInt32LE(ob->out,ClassNumber);
  ob->out->Flush(ob->out);
  if (ob->conn->mode > 0) {
    while (ob->conn->count) {
      ob->conn->count--;
      ReadInt32LE(ob->in);
    }
  }
  if (ReadInt16LE(ob->in) != 0x0000) longjmp(ob->conn->exception,1);
  if (ReadInt8LE(ob->in) != 0x02) longjmp(ob->conn->exception,2);
  if (ReadInt8LE(ob->in) != 0x13) longjmp(ob->conn->exception,3);
  ret = ReadInt32LE(out);
  if (ReadInt8LE(ob->in) != 0x80) longjmp(ob->conn->exception,2);
  return ret;
} 

int32 NetSystemLockCount(NetSystem *ob) {
  Stream *out = ob->out;
  int ret_len;
  int32 ret;
  WriteInt16LE(ob->out,0x0000);
  WriteInt8LE(ob->out,ob->instance);
  WriteInt8LE(ob->out,0x03);
  ob->out->Flush(ob->out);
  if (ob->conn->mode > 0) {
    while (ob->conn->count) {
      ob->conn->count--;
      ReadInt32LE(ob->in);
    }
  }
  if (ReadInt16LE(ob->in) != 0x0000) longjmp(ob->conn->exception,1);
  if (ReadInt8LE(ob->in) != 0x03) longjmp(ob->conn->exception,2);
  if (ReadInt8LE(ob->in) != 0x13) longjmp(ob->conn->exception,3);
  ret = ReadInt32LE(out);
  if (ReadInt8LE(ob->in) != 0x80) longjmp(ob->conn->exception,2);
  return ret;
} 

LockHolderInf* NetSystemLockHolderInfo(NetSystem *ob) {
  Stream *out = ob->out;
  int ret_len;
  LockHolderInf* ret;
  WriteInt16LE(ob->out,0x0000);
  WriteInt8LE(ob->out,ob->instance);
  WriteInt8LE(ob->out,0x04);
  ob->out->Flush(ob->out);
  if (ob->conn->mode > 0) {
    while (ob->conn->count) {
      ob->conn->count--;
      ReadInt32LE(ob->in);
    }
  }
  if (ReadInt16LE(ob->in) != 0x0000) longjmp(ob->conn->exception,1);
  if (ReadInt8LE(ob->in) != 0x04) longjmp(ob->conn->exception,2);
  if (ReadInt8LE(ob->in) != 0x70) longjmp(ob->conn->exception,3);
  ret_len = ReadInt32LE(ob->in);
  ret = ArrayAlloc(ret_len,8);
  {
    int i;
    for(i=0;i<ret_len;i++) {
      if (ReadInt8LE(ob->in) != 0x13) longjmp(ob->conn->exception,3);
      ret[i].pid = ReadInt32LE(out);
      if (ReadInt8LE(ob->in) != 0x13) longjmp(ob->conn->exception,3);
      ret[i].count = ReadInt32LE(out);
    }
  }
  if (ReadInt8LE(ob->in) != 0x80) longjmp(ob->conn->exception,2);
  return ret;
} 

ConnectionWaitInf* NetSystemConnWaitInfo(NetSystem *ob) {
  Stream *out = ob->out;
  int ret_len;
  ConnectionWaitInf* ret;
  WriteInt16LE(ob->out,0x0000);
  WriteInt8LE(ob->out,ob->instance);
  WriteInt8LE(ob->out,0x05);
  ob->out->Flush(ob->out);
  if (ob->conn->mode > 0) {
    while (ob->conn->count) {
      ob->conn->count--;
      ReadInt32LE(ob->in);
    }
  }
  if (ReadInt16LE(ob->in) != 0x0000) longjmp(ob->conn->exception,1);
  if (ReadInt8LE(ob->in) != 0x05) longjmp(ob->conn->exception,2);
  if (ReadInt8LE(ob->in) != 0x70) longjmp(ob->conn->exception,3);
  ret_len = ReadInt32LE(ob->in);
  ret = ArrayAlloc(ret_len,8);
  {
    int i;
    for(i=0;i<ret_len;i++) {
      if (ReadInt8LE(ob->in) != 0x13) longjmp(ob->conn->exception,3);
      ret[i].pid = ReadInt32LE(out);
      if (ReadInt8LE(ob->in) != 0x13) longjmp(ob->conn->exception,3);
      ret[i].wait = ReadInt32LE(out);
    }
  }
  if (ReadInt8LE(ob->in) != 0x80) longjmp(ob->conn->exception,2);
  return ret;
} 

SystemResult NetSystemCANBusGet(NetSystem *ob,int32 CANInstance) {
  Stream *out = ob->out;
  int ret_len;
  SystemResult ret;
  WriteInt16LE(ob->out,0x0000);
  WriteInt8LE(ob->out,ob->instance);
  WriteInt8LE(ob->out,0x06);
  WriteInt32LE(ob->out,CANInstance);
  ob->out->Flush(ob->out);
  if (ob->conn->mode > 0) {
    while (ob->conn->count) {
      ob->conn->count--;
      ReadInt32LE(ob->in);
    }
  }
  if (ReadInt16LE(ob->in) != 0x0000) longjmp(ob->conn->exception,1);
  if (ReadInt8LE(ob->in) != 0x06) longjmp(ob->conn->exception,2);
  if (ReadInt8LE(ob->in) != 0xC0) longjmp(ob->conn->exception,3);
  ret = ReadInt32LE(out);
  if (ReadInt8LE(ob->in) != 0x80) longjmp(ob->conn->exception,2);
  return ret;
} 

uint32 NetSystemBuildTime(NetSystem *ob) {
  Stream *out = ob->out;
  int ret_len;
  uint32 ret;
  WriteInt16LE(ob->out,0x0000);
  WriteInt8LE(ob->out,ob->instance);
  WriteInt8LE(ob->out,0x07);
  ob->out->Flush(ob->out);
  if (ob->conn->mode > 0) {
    while (ob->conn->count) {
      ob->conn->count--;
      ReadInt32LE(ob->in);
    }
  }
  if (ReadInt16LE(ob->in) != 0x0000) longjmp(ob->conn->exception,1);
  if (ReadInt8LE(ob->in) != 0x07) longjmp(ob->conn->exception,2);
  if (ReadInt8LE(ob->in) != 0x03) longjmp(ob->conn->exception,3);
  ret = ReadUInt32LE(out);
  if (ReadInt8LE(ob->in) != 0x80) longjmp(ob->conn->exception,2);
  return ret;
} 

int32 NetSystemModelId(NetSystem *ob) {
  Stream *out = ob->out;
  int ret_len;
  int32 ret;
  WriteInt16LE(ob->out,0x0000);
  WriteInt8LE(ob->out,ob->instance);
  WriteInt8LE(ob->out,0x08);
  ob->out->Flush(ob->out);
  if (ob->conn->mode > 0) {
    while (ob->conn->count) {
      ob->conn->count--;
      ReadInt32LE(ob->in);
    }
  }
  if (ReadInt16LE(ob->in) != 0x0000) longjmp(ob->conn->exception,1);
  if (ReadInt8LE(ob->in) != 0x08) longjmp(ob->conn->exception,2);
  if (ReadInt8LE(ob->in) != 0x13) longjmp(ob->conn->exception,3);
  ret = ReadInt32LE(out);
  if (ReadInt8LE(ob->in) != 0x80) longjmp(ob->conn->exception,2);
  return ret;
} 

int32 NetSystemBaseBoardId(NetSystem *ob) {
  Stream *out = ob->out;
  int ret_len;
  int32 ret;
  WriteInt16LE(ob->out,0x0000);
  WriteInt8LE(ob->out,ob->instance);
  WriteInt8LE(ob->out,0x09);
  ob->out->Flush(ob->out);
  if (ob->conn->mode > 0) {
    while (ob->conn->count) {
      ob->conn->count--;
      ReadInt32LE(ob->in);
    }
  }
  if (ReadInt16LE(ob->in) != 0x0000) longjmp(ob->conn->exception,1);
  if (ReadInt8LE(ob->in) != 0x09) longjmp(ob->conn->exception,2);
  if (ReadInt8LE(ob->in) != 0x13) longjmp(ob->conn->exception,3);
  ret = ReadInt32LE(out);
  if (ReadInt8LE(ob->in) != 0x80) longjmp(ob->conn->exception,2);
  return ret;
} 

int32 NetSystemMapLength(NetSystem *ob) {
  Stream *out = ob->out;
  int ret_len;
  int32 ret;
  WriteInt16LE(ob->out,0x0000);
  WriteInt8LE(ob->out,ob->instance);
  WriteInt8LE(ob->out,0x0A);
  ob->out->Flush(ob->out);
  if (ob->conn->mode > 0) {
    while (ob->conn->count) {
      ob->conn->count--;
      ReadInt32LE(ob->in);
    }
  }
  if (ReadInt16LE(ob->in) != 0x0000) longjmp(ob->conn->exception,1);
  if (ReadInt8LE(ob->in) != 0x0A) longjmp(ob->conn->exception,2);
  if (ReadInt8LE(ob->in) != 0x13) longjmp(ob->conn->exception,3);
  ret = ReadInt32LE(out);
  if (ReadInt8LE(ob->in) != 0x80) longjmp(ob->conn->exception,2);
  return ret;
} 

int8* NetSystemMapGet(NetSystem *ob,int32 MapIndex,int32 Value[1]) {
  Stream *out = ob->out;
  int ret_len;
  int8* ret;
  WriteInt16LE(ob->out,0x0000);
  WriteInt8LE(ob->out,ob->instance);
  WriteInt8LE(ob->out,0x0B);
  WriteInt32LE(ob->out,MapIndex);
  ob->out->Flush(ob->out);
  if (ob->conn->mode > 0) {
    while (ob->conn->count) {
      ob->conn->count--;
      ReadInt32LE(ob->in);
    }
  }
  if (ReadInt16LE(ob->in) != 0x0000) longjmp(ob->conn->exception,1);
  if (ReadInt8LE(ob->in) != 0x0B) longjmp(ob->conn->exception,2);
  if (ReadInt8LE(ob->in) != 0x50) longjmp(ob->conn->exception,3);
  ret_len = ReadInt32LE(ob->in);
  ret = ArrayAlloc(ret_len,1);
  {
    int i;
    for(i=0;i<ret_len;i++) {
      ret[i] = ReadInt8LE(out);
    }
  }
  if (ReadInt8LE(ob->in) != 0x53) longjmp(ob->conn->exception,3);
  ReadInt32LE(out);
  {
    int i;
    for(i=0;i<1;i++) {
      Value[i] = ReadInt32LE(out);
    }
  }
  if (ReadInt8LE(ob->in) != 0x80) longjmp(ob->conn->exception,2);
  return ret;
} 

int32 NetSystemMapLookup(NetSystem *ob,const int8* String) {
  Stream *out = ob->out;
  int ret_len;
  int32 ret;
  WriteInt16LE(ob->out,0x0000);
  WriteInt8LE(ob->out,ob->instance);
  WriteInt8LE(ob->out,0x0C);
  int i;
  WriteInt32LE(ob->out,ArrayLength(String));
  for (i=0;i<ArrayLength(String);i++) {
    WriteInt8LE(ob->out,String[i]);
  }
  ob->out->Flush(ob->out);
  if (ob->conn->mode > 0) {
    while (ob->conn->count) {
      ob->conn->count--;
      ReadInt32LE(ob->in);
    }
  }
  if (ReadInt16LE(ob->in) != 0x0000) longjmp(ob->conn->exception,1);
  if (ReadInt8LE(ob->in) != 0x0C) longjmp(ob->conn->exception,2);
  if (ReadInt8LE(ob->in) != 0x13) longjmp(ob->conn->exception,3);
  ret = ReadInt32LE(out);
  if (ReadInt8LE(ob->in) != 0x80) longjmp(ob->conn->exception,2);
  return ret;
} 

int8* NetSystemMapLookupPartial(NetSystem *ob,const int8* StringPrefix,int32 Value) {
  Stream *out = ob->out;
  int ret_len;
  int8* ret;
  WriteInt16LE(ob->out,0x0000);
  WriteInt8LE(ob->out,ob->instance);
  WriteInt8LE(ob->out,0x0D);
  int i;
  WriteInt32LE(ob->out,ArrayLength(StringPrefix));
  for (i=0;i<ArrayLength(StringPrefix);i++) {
    WriteInt8LE(ob->out,StringPrefix[i]);
  }
  WriteInt32LE(ob->out,Value);
  ob->out->Flush(ob->out);
  if (ob->conn->mode > 0) {
    while (ob->conn->count) {
      ob->conn->count--;
      ReadInt32LE(ob->in);
    }
  }
  if (ReadInt16LE(ob->in) != 0x0000) longjmp(ob->conn->exception,1);
  if (ReadInt8LE(ob->in) != 0x0D) longjmp(ob->conn->exception,2);
  if (ReadInt8LE(ob->in) != 0x50) longjmp(ob->conn->exception,3);
  ret_len = ReadInt32LE(ob->in);
  ret = ArrayAlloc(ret_len,1);
  {
    int i;
    for(i=0;i<ret_len;i++) {
      ret[i] = ReadInt8LE(out);
    }
  }
  if (ReadInt8LE(ob->in) != 0x80) longjmp(ob->conn->exception,2);
  return ret;
} 

SystemResult NetSystemMapAdd(NetSystem *ob,const int8* String,int32 Value) {
  Stream *out = ob->out;
  int ret_len;
  SystemResult ret;
  WriteInt16LE(ob->out,0x0000);
  WriteInt8LE(ob->out,ob->instance);
  WriteInt8LE(ob->out,0x0E);
  int i;
  WriteInt32LE(ob->out,ArrayLength(String));
  for (i=0;i<ArrayLength(String);i++) {
    WriteInt8LE(ob->out,String[i]);
  }
  WriteInt32LE(ob->out,Value);
  ob->out->Flush(ob->out);
  if (ob->conn->mode > 0) {
    while (ob->conn->count) {
      ob->conn->count--;
      ReadInt32LE(ob->in);
    }
  }
  if (ReadInt16LE(ob->in) != 0x0000) longjmp(ob->conn->exception,1);
  if (ReadInt8LE(ob->in) != 0x0E) longjmp(ob->conn->exception,2);
  if (ReadInt8LE(ob->in) != 0xC0) longjmp(ob->conn->exception,3);
  ret = ReadInt32LE(out);
  if (ReadInt8LE(ob->in) != 0x80) longjmp(ob->conn->exception,2);
  return ret;
} 

SystemResult NetSystemMapDelete(NetSystem *ob,const int8* String) {
  Stream *out = ob->out;
  int ret_len;
  SystemResult ret;
  WriteInt16LE(ob->out,0x0000);
  WriteInt8LE(ob->out,ob->instance);
  WriteInt8LE(ob->out,0x0F);
  int i;
  WriteInt32LE(ob->out,ArrayLength(String));
  for (i=0;i<ArrayLength(String);i++) {
    WriteInt8LE(ob->out,String[i]);
  }
  ob->out->Flush(ob->out);
  if (ob->conn->mode > 0) {
    while (ob->conn->count) {
      ob->conn->count--;
      ReadInt32LE(ob->in);
    }
  }
  if (ReadInt16LE(ob->in) != 0x0000) longjmp(ob->conn->exception,1);
  if (ReadInt8LE(ob->in) != 0x0F) longjmp(ob->conn->exception,2);
  if (ReadInt8LE(ob->in) != 0xC0) longjmp(ob->conn->exception,3);
  ret = ReadInt32LE(out);
  if (ReadInt8LE(ob->in) != 0x80) longjmp(ob->conn->exception,2);
  return ret;
} 

int8* NetSystemNote(NetSystem *ob,const int8* Message) {
  Stream *out = ob->out;
  int ret_len;
  int8* ret;
  WriteInt16LE(ob->out,0x0000);
  WriteInt8LE(ob->out,ob->instance);
  WriteInt8LE(ob->out,0x10);
  int i;
  WriteInt32LE(ob->out,ArrayLength(Message));
  for (i=0;i<ArrayLength(Message);i++) {
    WriteInt8LE(ob->out,Message[i]);
  }
  ob->out->Flush(ob->out);
  if (ob->conn->mode > 0) {
    while (ob->conn->count) {
      ob->conn->count--;
      ReadInt32LE(ob->in);
    }
  }
  if (ReadInt16LE(ob->in) != 0x0000) longjmp(ob->conn->exception,1);
  if (ReadInt8LE(ob->in) != 0x10) longjmp(ob->conn->exception,2);
  if (ReadInt8LE(ob->in) != 0x50) longjmp(ob->conn->exception,3);
  ret_len = ReadInt32LE(ob->in);
  ret = ArrayAlloc(ret_len,1);
  {
    int i;
    for(i=0;i<ret_len;i++) {
      ret[i] = ReadInt8LE(out);
    }
  }
  if (ReadInt8LE(ob->in) != 0x80) longjmp(ob->conn->exception,2);
  return ret;
} 

int8* NetSystemVersion(NetSystem *ob) {
  Stream *out = ob->out;
  int ret_len;
  int8* ret;
  WriteInt16LE(ob->out,0x0000);
  WriteInt8LE(ob->out,ob->instance);
  WriteInt8LE(ob->out,0x11);
  ob->out->Flush(ob->out);
  if (ob->conn->mode > 0) {
    while (ob->conn->count) {
      ob->conn->count--;
      ReadInt32LE(ob->in);
    }
  }
  if (ReadInt16LE(ob->in) != 0x0000) longjmp(ob->conn->exception,1);
  if (ReadInt8LE(ob->in) != 0x11) longjmp(ob->conn->exception,2);
  if (ReadInt8LE(ob->in) != 0x50) longjmp(ob->conn->exception,3);
  ret_len = ReadInt32LE(ob->in);
  ret = ArrayAlloc(ret_len,1);
  {
    int i;
    for(i=0;i<ret_len;i++) {
      ret[i] = ReadInt8LE(out);
    }
  }
  if (ReadInt8LE(ob->in) != 0x80) longjmp(ob->conn->exception,2);
  return ret;
} 

uint32 NetSystemUptimeServer(NetSystem *ob) {
  Stream *out = ob->out;
  int ret_len;
  uint32 ret;
  WriteInt16LE(ob->out,0x0000);
  WriteInt8LE(ob->out,ob->instance);
  WriteInt8LE(ob->out,0x12);
  ob->out->Flush(ob->out);
  if (ob->conn->mode > 0) {
    while (ob->conn->count) {
      ob->conn->count--;
      ReadInt32LE(ob->in);
    }
  }
  if (ReadInt16LE(ob->in) != 0x0000) longjmp(ob->conn->exception,1);
  if (ReadInt8LE(ob->in) != 0x12) longjmp(ob->conn->exception,2);
  if (ReadInt8LE(ob->in) != 0x03) longjmp(ob->conn->exception,3);
  ret = ReadUInt32LE(out);
  if (ReadInt8LE(ob->in) != 0x80) longjmp(ob->conn->exception,2);
  return ret;
} 

uint32 NetSystemUptimeHost(NetSystem *ob) {
  Stream *out = ob->out;
  int ret_len;
  uint32 ret;
  WriteInt16LE(ob->out,0x0000);
  WriteInt8LE(ob->out,ob->instance);
  WriteInt8LE(ob->out,0x13);
  ob->out->Flush(ob->out);
  if (ob->conn->mode > 0) {
    while (ob->conn->count) {
      ob->conn->count--;
      ReadInt32LE(ob->in);
    }
  }
  if (ReadInt16LE(ob->in) != 0x0000) longjmp(ob->conn->exception,1);
  if (ReadInt8LE(ob->in) != 0x13) longjmp(ob->conn->exception,2);
  if (ReadInt8LE(ob->in) != 0x03) longjmp(ob->conn->exception,3);
  ret = ReadUInt32LE(out);
  if (ReadInt8LE(ob->in) != 0x80) longjmp(ob->conn->exception,2);
  return ret;
} 

int32 NetSystemFPGARevision(NetSystem *ob) {
  Stream *out = ob->out;
  int ret_len;
  int32 ret;
  WriteInt16LE(ob->out,0x0000);
  WriteInt8LE(ob->out,ob->instance);
  WriteInt8LE(ob->out,0x14);
  ob->out->Flush(ob->out);
  if (ob->conn->mode > 0) {
    while (ob->conn->count) {
      ob->conn->count--;
      ReadInt32LE(ob->in);
    }
  }
  if (ReadInt16LE(ob->in) != 0x0000) longjmp(ob->conn->exception,1);
  if (ReadInt8LE(ob->in) != 0x14) longjmp(ob->conn->exception,2);
  if (ReadInt8LE(ob->in) != 0x13) longjmp(ob->conn->exception,3);
  ret = ReadInt32LE(out);
  if (ReadInt8LE(ob->in) != 0x80) longjmp(ob->conn->exception,2);
  return ret;
} 

int32 NetSystemEchoNumber(NetSystem *ob,int32 n) {
  Stream *out = ob->out;
  int ret_len;
  int32 ret;
  WriteInt16LE(ob->out,0x0000);
  WriteInt8LE(ob->out,ob->instance);
  WriteInt8LE(ob->out,0x15);
  WriteInt32LE(ob->out,n);
  ob->out->Flush(ob->out);
  if (ob->conn->mode > 0) {
    while (ob->conn->count) {
      ob->conn->count--;
      ReadInt32LE(ob->in);
    }
  }
  if (ReadInt16LE(ob->in) != 0x0000) longjmp(ob->conn->exception,1);
  if (ReadInt8LE(ob->in) != 0x15) longjmp(ob->conn->exception,2);
  if (ReadInt8LE(ob->in) != 0x13) longjmp(ob->conn->exception,3);
  ret = ReadInt32LE(out);
  if (ReadInt8LE(ob->in) != 0x80) longjmp(ob->conn->exception,2);
  return ret;
} 

