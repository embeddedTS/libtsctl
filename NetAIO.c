#include "NetAIO.h"

void *NetAIOInit(tsctl *conn,int instance) {
  NetAIO *ret = malloc(sizeof(NetAIO));
  ret->instance = instance;
  ret->conn = conn;
  ret->in = ret->out = conn->st;
  ret->InitStatus = 1;
  ret->Init = (void *)NetAIOInit;
  ret->Fini = (void *)NetAIOFini;
  ret->Lock = (void *)NetAIOLock;
  ret->Unlock = (void *)NetAIOUnlock;
  ret->Preempt = (void *)NetAIOPreempt;
  ret->Type = (void *)NetAIOType;
  ret->VoltageRangeList = (void *)NetAIOVoltageRangeList;
  ret->PrecisionList = (void *)NetAIOPrecisionList;
  ret->PeriodRangeList = (void *)NetAIOPeriodRangeList;
  ret->TriggerList = (void *)NetAIOTriggerList;
  ret->Channels = (void *)NetAIOChannels;
  ret->Reset = (void *)NetAIOReset;
  ret->ChannelEnable = (void *)NetAIOChannelEnable;
  ret->ChannelSamplePeriod = (void *)NetAIOChannelSamplePeriod;
  ret->ChannelPrecision = (void *)NetAIOChannelPrecision;
  ret->ChannelVoltageRange = (void *)NetAIOChannelVoltageRange;
  ret->Configuration = (void *)NetAIOConfiguration;
  ret->ConfigureTest = (void *)NetAIOConfigureTest;
  ret->Configure = (void *)NetAIOConfigure;
  ret->ITrig = (void *)NetAIOITrig;
  ret->Get = (void *)NetAIOGet;
  ret->Put = (void *)NetAIOPut;
  ret->Ready = (void *)NetAIOReady;
  ret->Gets8 = (void *)NetAIOGets8;
  ret->Gets16 = (void *)NetAIOGets16;
  ret->Gets32 = (void *)NetAIOGets32;
  ret->Puts8 = (void *)NetAIOPuts8;
  ret->Puts16 = (void *)NetAIOPuts16;
  ret->Puts32 = (void *)NetAIOPuts32;
  ret->Readys8 = (void *)NetAIOReadys8;
  ret->Readys16 = (void *)NetAIOReadys16;
  ret->Readys32 = (void *)NetAIOReadys32;
  return ret;
}

void *NetAIOFini(NetAIO *ob) {
  ob->InitStatus = 0;
}

int32 NetAIOLock(NetAIO *ob,uint32 num,int32 flags) {
  Stream *out = ob->out;
  int ret_len;
  int32 ret;
  WriteInt16LE(ob->out,0x0009);
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
  if (ReadInt16LE(ob->in) != 0x0009) longjmp(ob->conn->exception,1);
  if (ReadInt8LE(ob->in) != 0x00) longjmp(ob->conn->exception,2);
  if (ReadInt8LE(ob->in) != 0x13) longjmp(ob->conn->exception,3);
  ret = ReadInt32LE(out);
  if (ReadInt8LE(ob->in) != 0x80) longjmp(ob->conn->exception,2);
  return ret;
} 

int32 NetAIOUnlock(NetAIO *ob,uint32 num,int32 flags) {
  Stream *out = ob->out;
  int ret_len;
  int32 ret;
  WriteInt16LE(ob->out,0x0009);
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
  if (ReadInt16LE(ob->in) != 0x0009) longjmp(ob->conn->exception,1);
  if (ReadInt8LE(ob->in) != 0x01) longjmp(ob->conn->exception,2);
  if (ReadInt8LE(ob->in) != 0x13) longjmp(ob->conn->exception,3);
  ret = ReadInt32LE(out);
  if (ReadInt8LE(ob->in) != 0x80) longjmp(ob->conn->exception,2);
  return ret;
} 

int32 NetAIOPreempt(NetAIO *ob) {
  Stream *out = ob->out;
  int ret_len;
  int32 ret;
  WriteInt16LE(ob->out,0x0009);
  WriteInt8LE(ob->out,ob->instance);
  WriteInt8LE(ob->out,0x02);
  ob->out->Flush(ob->out);
  if (ob->conn->mode > 0) {
    while (ob->conn->count) {
      ob->conn->count--;
      ReadInt32LE(ob->in);
    }
  }
  if (ReadInt16LE(ob->in) != 0x0009) longjmp(ob->conn->exception,1);
  if (ReadInt8LE(ob->in) != 0x02) longjmp(ob->conn->exception,2);
  if (ReadInt8LE(ob->in) != 0x13) longjmp(ob->conn->exception,3);
  ret = ReadInt32LE(out);
  if (ReadInt8LE(ob->in) != 0x80) longjmp(ob->conn->exception,2);
  return ret;
} 

AIOType NetAIOType(NetAIO *ob) {
  Stream *out = ob->out;
  int ret_len;
  AIOType ret;
  WriteInt16LE(ob->out,0x0009);
  WriteInt8LE(ob->out,ob->instance);
  WriteInt8LE(ob->out,0x03);
  ob->out->Flush(ob->out);
  if (ob->conn->mode > 0) {
    while (ob->conn->count) {
      ob->conn->count--;
      ReadInt32LE(ob->in);
    }
  }
  if (ReadInt16LE(ob->in) != 0x0009) longjmp(ob->conn->exception,1);
  if (ReadInt8LE(ob->in) != 0x03) longjmp(ob->conn->exception,2);
  if (ReadInt8LE(ob->in) != 0xCD) longjmp(ob->conn->exception,3);
  ret = ReadInt32LE(out);
  if (ReadInt8LE(ob->in) != 0x80) longjmp(ob->conn->exception,2);
  return ret;
} 

VoltageRange* NetAIOVoltageRangeList(NetAIO *ob) {
  Stream *out = ob->out;
  int ret_len;
  VoltageRange* ret;
  WriteInt16LE(ob->out,0x0009);
  WriteInt8LE(ob->out,ob->instance);
  WriteInt8LE(ob->out,0x04);
  ob->out->Flush(ob->out);
  if (ob->conn->mode > 0) {
    while (ob->conn->count) {
      ob->conn->count--;
      ReadInt32LE(ob->in);
    }
  }
  if (ReadInt16LE(ob->in) != 0x0009) longjmp(ob->conn->exception,1);
  if (ReadInt8LE(ob->in) != 0x04) longjmp(ob->conn->exception,2);
  if (ReadInt8LE(ob->in) != 0x70) longjmp(ob->conn->exception,3);
  ret_len = ReadInt32LE(ob->in);
  ret = ArrayAlloc(ret_len,24);
  {
    int i;
    for(i=0;i<ret_len;i++) {
      if (ReadInt8LE(ob->in) != 0x31) longjmp(ob->conn->exception,3);
        if (ReadInt8LE(ob->in) != 0x23) longjmp(ob->conn->exception,3);
        ret[i].low.start = ReadReal32LE(out);
        if (ReadInt8LE(ob->in) != 0x23) longjmp(ob->conn->exception,3);
        ret[i].low.step = ReadReal32LE(out);
        if (ReadInt8LE(ob->in) != 0x03) longjmp(ob->conn->exception,3);
        ret[i].low.count = ReadUInt32LE(out);
      if (ReadInt8LE(ob->in) != 0x31) longjmp(ob->conn->exception,3);
        if (ReadInt8LE(ob->in) != 0x23) longjmp(ob->conn->exception,3);
        ret[i].high.start = ReadReal32LE(out);
        if (ReadInt8LE(ob->in) != 0x23) longjmp(ob->conn->exception,3);
        ret[i].high.step = ReadReal32LE(out);
        if (ReadInt8LE(ob->in) != 0x03) longjmp(ob->conn->exception,3);
        ret[i].high.count = ReadUInt32LE(out);
    }
  }
  if (ReadInt8LE(ob->in) != 0x80) longjmp(ob->conn->exception,2);
  return ret;
} 

int32 NetAIOPrecisionList(NetAIO *ob) {
  Stream *out = ob->out;
  int ret_len;
  int32 ret;
  WriteInt16LE(ob->out,0x0009);
  WriteInt8LE(ob->out,ob->instance);
  WriteInt8LE(ob->out,0x05);
  ob->out->Flush(ob->out);
  if (ob->conn->mode > 0) {
    while (ob->conn->count) {
      ob->conn->count--;
      ReadInt32LE(ob->in);
    }
  }
  if (ReadInt16LE(ob->in) != 0x0009) longjmp(ob->conn->exception,1);
  if (ReadInt8LE(ob->in) != 0x05) longjmp(ob->conn->exception,2);
  if (ReadInt8LE(ob->in) != 0x13) longjmp(ob->conn->exception,3);
  ret = ReadInt32LE(out);
  if (ReadInt8LE(ob->in) != 0x80) longjmp(ob->conn->exception,2);
  return ret;
} 

PeriodRange* NetAIOPeriodRangeList(NetAIO *ob) {
  Stream *out = ob->out;
  int ret_len;
  PeriodRange* ret;
  WriteInt16LE(ob->out,0x0009);
  WriteInt8LE(ob->out,ob->instance);
  WriteInt8LE(ob->out,0x06);
  ob->out->Flush(ob->out);
  if (ob->conn->mode > 0) {
    while (ob->conn->count) {
      ob->conn->count--;
      ReadInt32LE(ob->in);
    }
  }
  if (ReadInt16LE(ob->in) != 0x0009) longjmp(ob->conn->exception,1);
  if (ReadInt8LE(ob->in) != 0x06) longjmp(ob->conn->exception,2);
  if (ReadInt8LE(ob->in) != 0x71) longjmp(ob->conn->exception,3);
  ret_len = ReadInt32LE(ob->in);
  ret = ArrayAlloc(ret_len,12);
  {
    int i;
    for(i=0;i<ret_len;i++) {
      if (ReadInt8LE(ob->in) != 0x03) longjmp(ob->conn->exception,3);
      ret[i].start = ReadUInt32LE(out);
      if (ReadInt8LE(ob->in) != 0x03) longjmp(ob->conn->exception,3);
      ret[i].step = ReadUInt32LE(out);
      if (ReadInt8LE(ob->in) != 0x03) longjmp(ob->conn->exception,3);
      ret[i].count = ReadUInt32LE(out);
    }
  }
  if (ReadInt8LE(ob->in) != 0x80) longjmp(ob->conn->exception,2);
  return ret;
} 

int32* NetAIOTriggerList(NetAIO *ob) {
  Stream *out = ob->out;
  int ret_len;
  int32* ret;
  WriteInt16LE(ob->out,0x0009);
  WriteInt8LE(ob->out,ob->instance);
  WriteInt8LE(ob->out,0x07);
  ob->out->Flush(ob->out);
  if (ob->conn->mode > 0) {
    while (ob->conn->count) {
      ob->conn->count--;
      ReadInt32LE(ob->in);
    }
  }
  if (ReadInt16LE(ob->in) != 0x0009) longjmp(ob->conn->exception,1);
  if (ReadInt8LE(ob->in) != 0x07) longjmp(ob->conn->exception,2);
  if (ReadInt8LE(ob->in) != 0x53) longjmp(ob->conn->exception,3);
  ret_len = ReadInt32LE(ob->in);
  ret = ArrayAlloc(ret_len,4);
  {
    int i;
    for(i=0;i<ret_len;i++) {
      ret[i] = ReadInt32LE(out);
    }
  }
  if (ReadInt8LE(ob->in) != 0x80) longjmp(ob->conn->exception,2);
  return ret;
} 

int32 NetAIOChannels(NetAIO *ob) {
  Stream *out = ob->out;
  int ret_len;
  int32 ret;
  WriteInt16LE(ob->out,0x0009);
  WriteInt8LE(ob->out,ob->instance);
  WriteInt8LE(ob->out,0x08);
  ob->out->Flush(ob->out);
  if (ob->conn->mode > 0) {
    while (ob->conn->count) {
      ob->conn->count--;
      ReadInt32LE(ob->in);
    }
  }
  if (ReadInt16LE(ob->in) != 0x0009) longjmp(ob->conn->exception,1);
  if (ReadInt8LE(ob->in) != 0x08) longjmp(ob->conn->exception,2);
  if (ReadInt8LE(ob->in) != 0x13) longjmp(ob->conn->exception,3);
  ret = ReadInt32LE(out);
  if (ReadInt8LE(ob->in) != 0x80) longjmp(ob->conn->exception,2);
  return ret;
} 

void NetAIOReset(NetAIO *ob) {
  Stream *out = ob->out;
  int ret_len;
  WriteInt16LE(ob->out,0x0009);
  WriteInt8LE(ob->out,ob->instance);
  WriteInt8LE(ob->out,0x09);
  if (ob->conn->mode > 0) ob->conn->count++;
  if (ob->conn->mode < 2)  ob->out->Flush(ob->out);
  if (ob->conn->mode > 0) return;
  if (ReadInt16LE(ob->in) != 0x0009) longjmp(ob->conn->exception,1);
  if (ReadInt8LE(ob->in) != 0x09) longjmp(ob->conn->exception,2);
  if (ReadInt8LE(ob->in) != 0x80) longjmp(ob->conn->exception,2);
} 

int32 NetAIOChannelEnable(NetAIO *ob,int32 ch,int32 flag) {
  Stream *out = ob->out;
  int ret_len;
  int32 ret;
  WriteInt16LE(ob->out,0x0009);
  WriteInt8LE(ob->out,ob->instance);
  WriteInt8LE(ob->out,0x0A);
  WriteInt32LE(ob->out,ch);
  WriteInt32LE(ob->out,flag);
  ob->out->Flush(ob->out);
  if (ob->conn->mode > 0) {
    while (ob->conn->count) {
      ob->conn->count--;
      ReadInt32LE(ob->in);
    }
  }
  if (ReadInt16LE(ob->in) != 0x0009) longjmp(ob->conn->exception,1);
  if (ReadInt8LE(ob->in) != 0x0A) longjmp(ob->conn->exception,2);
  if (ReadInt8LE(ob->in) != 0x13) longjmp(ob->conn->exception,3);
  ret = ReadInt32LE(out);
  if (ReadInt8LE(ob->in) != 0x80) longjmp(ob->conn->exception,2);
  return ret;
} 

uint32 NetAIOChannelSamplePeriod(NetAIO *ob,int32 ch,uint32 ns) {
  Stream *out = ob->out;
  int ret_len;
  uint32 ret;
  WriteInt16LE(ob->out,0x0009);
  WriteInt8LE(ob->out,ob->instance);
  WriteInt8LE(ob->out,0x0B);
  WriteInt32LE(ob->out,ch);
  WriteUInt32LE(ob->out,ns);
  ob->out->Flush(ob->out);
  if (ob->conn->mode > 0) {
    while (ob->conn->count) {
      ob->conn->count--;
      ReadInt32LE(ob->in);
    }
  }
  if (ReadInt16LE(ob->in) != 0x0009) longjmp(ob->conn->exception,1);
  if (ReadInt8LE(ob->in) != 0x0B) longjmp(ob->conn->exception,2);
  if (ReadInt8LE(ob->in) != 0x03) longjmp(ob->conn->exception,3);
  ret = ReadUInt32LE(out);
  if (ReadInt8LE(ob->in) != 0x80) longjmp(ob->conn->exception,2);
  return ret;
} 

int32 NetAIOChannelPrecision(NetAIO *ob,int32 ch,int32 prec) {
  Stream *out = ob->out;
  int ret_len;
  int32 ret;
  WriteInt16LE(ob->out,0x0009);
  WriteInt8LE(ob->out,ob->instance);
  WriteInt8LE(ob->out,0x0C);
  WriteInt32LE(ob->out,ch);
  WriteInt32LE(ob->out,prec);
  ob->out->Flush(ob->out);
  if (ob->conn->mode > 0) {
    while (ob->conn->count) {
      ob->conn->count--;
      ReadInt32LE(ob->in);
    }
  }
  if (ReadInt16LE(ob->in) != 0x0009) longjmp(ob->conn->exception,1);
  if (ReadInt8LE(ob->in) != 0x0C) longjmp(ob->conn->exception,2);
  if (ReadInt8LE(ob->in) != 0x13) longjmp(ob->conn->exception,3);
  ret = ReadInt32LE(out);
  if (ReadInt8LE(ob->in) != 0x80) longjmp(ob->conn->exception,2);
  return ret;
} 

int32 NetAIOChannelVoltageRange(NetAIO *ob,int32 ch,real32 low,real32 high) {
  Stream *out = ob->out;
  int ret_len;
  int32 ret;
  WriteInt16LE(ob->out,0x0009);
  WriteInt8LE(ob->out,ob->instance);
  WriteInt8LE(ob->out,0x0D);
  WriteInt32LE(ob->out,ch);
  WriteReal32LE(ob->out,low);
  WriteReal32LE(ob->out,high);
  ob->out->Flush(ob->out);
  if (ob->conn->mode > 0) {
    while (ob->conn->count) {
      ob->conn->count--;
      ReadInt32LE(ob->in);
    }
  }
  if (ReadInt16LE(ob->in) != 0x0009) longjmp(ob->conn->exception,1);
  if (ReadInt8LE(ob->in) != 0x0D) longjmp(ob->conn->exception,2);
  if (ReadInt8LE(ob->in) != 0x13) longjmp(ob->conn->exception,3);
  ret = ReadInt32LE(out);
  if (ReadInt8LE(ob->in) != 0x80) longjmp(ob->conn->exception,2);
  return ret;
} 

int32 NetAIOConfiguration(NetAIO *ob,real32* low,real32* high,int32* prec,int32* t,int32* trigger,int32 itrig[1]) {
  Stream *out = ob->out;
  int ret_len;
  int32 ret;
  WriteInt16LE(ob->out,0x0009);
  WriteInt8LE(ob->out,ob->instance);
  WriteInt8LE(ob->out,0x0E);
  WriteInt32LE(ob->out,ArrayLength(low));
  WriteInt32LE(ob->out,ArrayLength(high));
  WriteInt32LE(ob->out,ArrayLength(prec));
  WriteInt32LE(ob->out,ArrayLength(t));
  WriteInt32LE(ob->out,ArrayLength(trigger));
  ob->out->Flush(ob->out);
  if (ob->conn->mode > 0) {
    while (ob->conn->count) {
      ob->conn->count--;
      ReadInt32LE(ob->in);
    }
  }
  if (ReadInt16LE(ob->in) != 0x0009) longjmp(ob->conn->exception,1);
  if (ReadInt8LE(ob->in) != 0x0E) longjmp(ob->conn->exception,2);
  if (ReadInt8LE(ob->in) != 0x13) longjmp(ob->conn->exception,3);
  ret = ReadInt32LE(out);
  if (ReadInt8LE(ob->in) != 0x63) longjmp(ob->conn->exception,3);
  if (ReadInt32LE(ob->in)!=ArrayLength(low)) longjmp(ob->conn->exception,5);
  {
    int i;
    for(i=0;i<ArrayLength(low);i++) {
      low[i] = ReadReal32LE(out);
    }
  }
  if (ReadInt8LE(ob->in) != 0x63) longjmp(ob->conn->exception,3);
  if (ReadInt32LE(ob->in)!=ArrayLength(high)) longjmp(ob->conn->exception,5);
  {
    int i;
    for(i=0;i<ArrayLength(high);i++) {
      high[i] = ReadReal32LE(out);
    }
  }
  if (ReadInt8LE(ob->in) != 0x53) longjmp(ob->conn->exception,3);
  if (ReadInt32LE(ob->in)!=ArrayLength(prec)) longjmp(ob->conn->exception,5);
  {
    int i;
    for(i=0;i<ArrayLength(prec);i++) {
      prec[i] = ReadInt32LE(out);
    }
  }
  if (ReadInt8LE(ob->in) != 0x53) longjmp(ob->conn->exception,3);
  if (ReadInt32LE(ob->in)!=ArrayLength(t)) longjmp(ob->conn->exception,5);
  {
    int i;
    for(i=0;i<ArrayLength(t);i++) {
      t[i] = ReadInt32LE(out);
    }
  }
  if (ReadInt8LE(ob->in) != 0x53) longjmp(ob->conn->exception,3);
  if (ReadInt32LE(ob->in)!=ArrayLength(trigger)) longjmp(ob->conn->exception,5);
  {
    int i;
    for(i=0;i<ArrayLength(trigger);i++) {
      trigger[i] = ReadInt32LE(out);
    }
  }
  if (ReadInt8LE(ob->in) != 0x53) longjmp(ob->conn->exception,3);
  ReadInt32LE(out);
  {
    int i;
    for(i=0;i<1;i++) {
      itrig[i] = ReadInt32LE(out);
    }
  }
  if (ReadInt8LE(ob->in) != 0x80) longjmp(ob->conn->exception,2);
  return ret;
} 

int32 NetAIOConfigureTest(NetAIO *ob,const real32* low,const real32* high,const int32* prec,const int32* rate,const int32* trigger,int32 itrig) {
  Stream *out = ob->out;
  int ret_len;
  int32 ret;
  WriteInt16LE(ob->out,0x0009);
  WriteInt8LE(ob->out,ob->instance);
  WriteInt8LE(ob->out,0x0F);
  int i;
  WriteInt32LE(ob->out,ArrayLength(low));
  for (i=0;i<ArrayLength(low);i++) {
    WriteReal32LE(ob->out,low[i]);
  }
  WriteInt32LE(ob->out,ArrayLength(high));
  for (i=0;i<ArrayLength(high);i++) {
    WriteReal32LE(ob->out,high[i]);
  }
  WriteInt32LE(ob->out,ArrayLength(prec));
  for (i=0;i<ArrayLength(prec);i++) {
    WriteInt32LE(ob->out,prec[i]);
  }
  WriteInt32LE(ob->out,ArrayLength(rate));
  for (i=0;i<ArrayLength(rate);i++) {
    WriteInt32LE(ob->out,rate[i]);
  }
  WriteInt32LE(ob->out,ArrayLength(trigger));
  for (i=0;i<ArrayLength(trigger);i++) {
    WriteInt32LE(ob->out,trigger[i]);
  }
  WriteInt32LE(ob->out,itrig);
  ob->out->Flush(ob->out);
  if (ob->conn->mode > 0) {
    while (ob->conn->count) {
      ob->conn->count--;
      ReadInt32LE(ob->in);
    }
  }
  if (ReadInt16LE(ob->in) != 0x0009) longjmp(ob->conn->exception,1);
  if (ReadInt8LE(ob->in) != 0x0F) longjmp(ob->conn->exception,2);
  if (ReadInt8LE(ob->in) != 0x13) longjmp(ob->conn->exception,3);
  ret = ReadInt32LE(out);
  if (ReadInt8LE(ob->in) != 0x80) longjmp(ob->conn->exception,2);
  return ret;
} 

int32 NetAIOConfigure(NetAIO *ob,const real32* low,const real32* high,const int32* prec,const int32* rate,const int32* trigger,int32 itrig) {
  Stream *out = ob->out;
  int ret_len;
  int32 ret;
  WriteInt16LE(ob->out,0x0009);
  WriteInt8LE(ob->out,ob->instance);
  WriteInt8LE(ob->out,0x10);
  int i;
  WriteInt32LE(ob->out,ArrayLength(low));
  for (i=0;i<ArrayLength(low);i++) {
    WriteReal32LE(ob->out,low[i]);
  }
  WriteInt32LE(ob->out,ArrayLength(high));
  for (i=0;i<ArrayLength(high);i++) {
    WriteReal32LE(ob->out,high[i]);
  }
  WriteInt32LE(ob->out,ArrayLength(prec));
  for (i=0;i<ArrayLength(prec);i++) {
    WriteInt32LE(ob->out,prec[i]);
  }
  WriteInt32LE(ob->out,ArrayLength(rate));
  for (i=0;i<ArrayLength(rate);i++) {
    WriteInt32LE(ob->out,rate[i]);
  }
  WriteInt32LE(ob->out,ArrayLength(trigger));
  for (i=0;i<ArrayLength(trigger);i++) {
    WriteInt32LE(ob->out,trigger[i]);
  }
  WriteInt32LE(ob->out,itrig);
  ob->out->Flush(ob->out);
  if (ob->conn->mode > 0) {
    while (ob->conn->count) {
      ob->conn->count--;
      ReadInt32LE(ob->in);
    }
  }
  if (ReadInt16LE(ob->in) != 0x0009) longjmp(ob->conn->exception,1);
  if (ReadInt8LE(ob->in) != 0x10) longjmp(ob->conn->exception,2);
  if (ReadInt8LE(ob->in) != 0x13) longjmp(ob->conn->exception,3);
  ret = ReadInt32LE(out);
  if (ReadInt8LE(ob->in) != 0x80) longjmp(ob->conn->exception,2);
  return ret;
} 

int32 NetAIOITrig(NetAIO *ob,int32 itrig) {
  Stream *out = ob->out;
  int ret_len;
  int32 ret;
  WriteInt16LE(ob->out,0x0009);
  WriteInt8LE(ob->out,ob->instance);
  WriteInt8LE(ob->out,0x11);
  WriteInt32LE(ob->out,itrig);
  ob->out->Flush(ob->out);
  if (ob->conn->mode > 0) {
    while (ob->conn->count) {
      ob->conn->count--;
      ReadInt32LE(ob->in);
    }
  }
  if (ReadInt16LE(ob->in) != 0x0009) longjmp(ob->conn->exception,1);
  if (ReadInt8LE(ob->in) != 0x11) longjmp(ob->conn->exception,2);
  if (ReadInt8LE(ob->in) != 0x13) longjmp(ob->conn->exception,3);
  ret = ReadInt32LE(out);
  if (ReadInt8LE(ob->in) != 0x80) longjmp(ob->conn->exception,2);
  return ret;
} 

int32 NetAIOGet(NetAIO *ob,int32 channel) {
  Stream *out = ob->out;
  int ret_len;
  int32 ret;
  WriteInt16LE(ob->out,0x0009);
  WriteInt8LE(ob->out,ob->instance);
  WriteInt8LE(ob->out,0x12);
  WriteInt32LE(ob->out,channel);
  ob->out->Flush(ob->out);
  if (ob->conn->mode > 0) {
    while (ob->conn->count) {
      ob->conn->count--;
      ReadInt32LE(ob->in);
    }
  }
  if (ReadInt16LE(ob->in) != 0x0009) longjmp(ob->conn->exception,1);
  if (ReadInt8LE(ob->in) != 0x12) longjmp(ob->conn->exception,2);
  if (ReadInt8LE(ob->in) != 0x13) longjmp(ob->conn->exception,3);
  ret = ReadInt32LE(out);
  if (ReadInt8LE(ob->in) != 0x80) longjmp(ob->conn->exception,2);
  return ret;
} 

int32 NetAIOPut(NetAIO *ob,int32 channel,int32 value) {
  Stream *out = ob->out;
  int ret_len;
  int32 ret;
  WriteInt16LE(ob->out,0x0009);
  WriteInt8LE(ob->out,ob->instance);
  WriteInt8LE(ob->out,0x13);
  WriteInt32LE(ob->out,channel);
  WriteInt32LE(ob->out,value);
  ob->out->Flush(ob->out);
  if (ob->conn->mode > 0) {
    while (ob->conn->count) {
      ob->conn->count--;
      ReadInt32LE(ob->in);
    }
  }
  if (ReadInt16LE(ob->in) != 0x0009) longjmp(ob->conn->exception,1);
  if (ReadInt8LE(ob->in) != 0x13) longjmp(ob->conn->exception,2);
  if (ReadInt8LE(ob->in) != 0x13) longjmp(ob->conn->exception,3);
  ret = ReadInt32LE(out);
  if (ReadInt8LE(ob->in) != 0x80) longjmp(ob->conn->exception,2);
  return ret;
} 

int32 NetAIOReady(NetAIO *ob,int32 channel) {
  Stream *out = ob->out;
  int ret_len;
  int32 ret;
  WriteInt16LE(ob->out,0x0009);
  WriteInt8LE(ob->out,ob->instance);
  WriteInt8LE(ob->out,0x14);
  WriteInt32LE(ob->out,channel);
  ob->out->Flush(ob->out);
  if (ob->conn->mode > 0) {
    while (ob->conn->count) {
      ob->conn->count--;
      ReadInt32LE(ob->in);
    }
  }
  if (ReadInt16LE(ob->in) != 0x0009) longjmp(ob->conn->exception,1);
  if (ReadInt8LE(ob->in) != 0x14) longjmp(ob->conn->exception,2);
  if (ReadInt8LE(ob->in) != 0x13) longjmp(ob->conn->exception,3);
  ret = ReadInt32LE(out);
  if (ReadInt8LE(ob->in) != 0x80) longjmp(ob->conn->exception,2);
  return ret;
} 

int32 NetAIOGets8(NetAIO *ob,int8* buf) {
  Stream *out = ob->out;
  int ret_len;
  int32 ret;
  WriteInt16LE(ob->out,0x0009);
  WriteInt8LE(ob->out,ob->instance);
  WriteInt8LE(ob->out,0x15);
  WriteInt32LE(ob->out,ArrayLength(buf));
  ob->out->Flush(ob->out);
  if (ob->conn->mode > 0) {
    while (ob->conn->count) {
      ob->conn->count--;
      ReadInt32LE(ob->in);
    }
  }
  if (ReadInt16LE(ob->in) != 0x0009) longjmp(ob->conn->exception,1);
  if (ReadInt8LE(ob->in) != 0x15) longjmp(ob->conn->exception,2);
  if (ReadInt8LE(ob->in) != 0x13) longjmp(ob->conn->exception,3);
  ret = ReadInt32LE(out);
  if (ReadInt8LE(ob->in) != 0x50) longjmp(ob->conn->exception,3);
  if (ReadInt32LE(ob->in)!=ArrayLength(buf)) longjmp(ob->conn->exception,5);
  {
    int i;
    for(i=0;i<ArrayLength(buf);i++) {
      buf[i] = ReadInt8LE(out);
    }
  }
  if (ReadInt8LE(ob->in) != 0x80) longjmp(ob->conn->exception,2);
  return ret;
} 

int32 NetAIOGets16(NetAIO *ob,int16* buf) {
  Stream *out = ob->out;
  int ret_len;
  int32 ret;
  WriteInt16LE(ob->out,0x0009);
  WriteInt8LE(ob->out,ob->instance);
  WriteInt8LE(ob->out,0x16);
  WriteInt32LE(ob->out,ArrayLength(buf));
  ob->out->Flush(ob->out);
  if (ob->conn->mode > 0) {
    while (ob->conn->count) {
      ob->conn->count--;
      ReadInt32LE(ob->in);
    }
  }
  if (ReadInt16LE(ob->in) != 0x0009) longjmp(ob->conn->exception,1);
  if (ReadInt8LE(ob->in) != 0x16) longjmp(ob->conn->exception,2);
  if (ReadInt8LE(ob->in) != 0x13) longjmp(ob->conn->exception,3);
  ret = ReadInt32LE(out);
  if (ReadInt8LE(ob->in) != 0x51) longjmp(ob->conn->exception,3);
  if (ReadInt32LE(ob->in)!=ArrayLength(buf)) longjmp(ob->conn->exception,5);
  {
    int i;
    for(i=0;i<ArrayLength(buf);i++) {
      buf[i] = ReadInt16LE(out);
    }
  }
  if (ReadInt8LE(ob->in) != 0x80) longjmp(ob->conn->exception,2);
  return ret;
} 

int32 NetAIOGets32(NetAIO *ob,int32* buf) {
  Stream *out = ob->out;
  int ret_len;
  int32 ret;
  WriteInt16LE(ob->out,0x0009);
  WriteInt8LE(ob->out,ob->instance);
  WriteInt8LE(ob->out,0x17);
  WriteInt32LE(ob->out,ArrayLength(buf));
  ob->out->Flush(ob->out);
  if (ob->conn->mode > 0) {
    while (ob->conn->count) {
      ob->conn->count--;
      ReadInt32LE(ob->in);
    }
  }
  if (ReadInt16LE(ob->in) != 0x0009) longjmp(ob->conn->exception,1);
  if (ReadInt8LE(ob->in) != 0x17) longjmp(ob->conn->exception,2);
  if (ReadInt8LE(ob->in) != 0x13) longjmp(ob->conn->exception,3);
  ret = ReadInt32LE(out);
  if (ReadInt8LE(ob->in) != 0x53) longjmp(ob->conn->exception,3);
  if (ReadInt32LE(ob->in)!=ArrayLength(buf)) longjmp(ob->conn->exception,5);
  {
    int i;
    for(i=0;i<ArrayLength(buf);i++) {
      buf[i] = ReadInt32LE(out);
    }
  }
  if (ReadInt8LE(ob->in) != 0x80) longjmp(ob->conn->exception,2);
  return ret;
} 

int32 NetAIOPuts8(NetAIO *ob,const int8* buf) {
  Stream *out = ob->out;
  int ret_len;
  int32 ret;
  WriteInt16LE(ob->out,0x0009);
  WriteInt8LE(ob->out,ob->instance);
  WriteInt8LE(ob->out,0x18);
  int i;
  WriteInt32LE(ob->out,ArrayLength(buf));
  for (i=0;i<ArrayLength(buf);i++) {
    WriteInt8LE(ob->out,buf[i]);
  }
  ob->out->Flush(ob->out);
  if (ob->conn->mode > 0) {
    while (ob->conn->count) {
      ob->conn->count--;
      ReadInt32LE(ob->in);
    }
  }
  if (ReadInt16LE(ob->in) != 0x0009) longjmp(ob->conn->exception,1);
  if (ReadInt8LE(ob->in) != 0x18) longjmp(ob->conn->exception,2);
  if (ReadInt8LE(ob->in) != 0x13) longjmp(ob->conn->exception,3);
  ret = ReadInt32LE(out);
  if (ReadInt8LE(ob->in) != 0x80) longjmp(ob->conn->exception,2);
  return ret;
} 

int32 NetAIOPuts16(NetAIO *ob,const int16* buf) {
  Stream *out = ob->out;
  int ret_len;
  int32 ret;
  WriteInt16LE(ob->out,0x0009);
  WriteInt8LE(ob->out,ob->instance);
  WriteInt8LE(ob->out,0x19);
  int i;
  WriteInt32LE(ob->out,ArrayLength(buf));
  for (i=0;i<ArrayLength(buf);i++) {
    WriteInt16LE(ob->out,buf[i]);
  }
  ob->out->Flush(ob->out);
  if (ob->conn->mode > 0) {
    while (ob->conn->count) {
      ob->conn->count--;
      ReadInt32LE(ob->in);
    }
  }
  if (ReadInt16LE(ob->in) != 0x0009) longjmp(ob->conn->exception,1);
  if (ReadInt8LE(ob->in) != 0x19) longjmp(ob->conn->exception,2);
  if (ReadInt8LE(ob->in) != 0x13) longjmp(ob->conn->exception,3);
  ret = ReadInt32LE(out);
  if (ReadInt8LE(ob->in) != 0x80) longjmp(ob->conn->exception,2);
  return ret;
} 

int32 NetAIOPuts32(NetAIO *ob,const int32* buf) {
  Stream *out = ob->out;
  int ret_len;
  int32 ret;
  WriteInt16LE(ob->out,0x0009);
  WriteInt8LE(ob->out,ob->instance);
  WriteInt8LE(ob->out,0x1A);
  int i;
  WriteInt32LE(ob->out,ArrayLength(buf));
  for (i=0;i<ArrayLength(buf);i++) {
    WriteInt32LE(ob->out,buf[i]);
  }
  ob->out->Flush(ob->out);
  if (ob->conn->mode > 0) {
    while (ob->conn->count) {
      ob->conn->count--;
      ReadInt32LE(ob->in);
    }
  }
  if (ReadInt16LE(ob->in) != 0x0009) longjmp(ob->conn->exception,1);
  if (ReadInt8LE(ob->in) != 0x1A) longjmp(ob->conn->exception,2);
  if (ReadInt8LE(ob->in) != 0x13) longjmp(ob->conn->exception,3);
  ret = ReadInt32LE(out);
  if (ReadInt8LE(ob->in) != 0x80) longjmp(ob->conn->exception,2);
  return ret;
} 

int32 NetAIOReadys8(NetAIO *ob,const int8* buf) {
  Stream *out = ob->out;
  int ret_len;
  int32 ret;
  WriteInt16LE(ob->out,0x0009);
  WriteInt8LE(ob->out,ob->instance);
  WriteInt8LE(ob->out,0x1B);
  int i;
  WriteInt32LE(ob->out,ArrayLength(buf));
  for (i=0;i<ArrayLength(buf);i++) {
    WriteInt8LE(ob->out,buf[i]);
  }
  ob->out->Flush(ob->out);
  if (ob->conn->mode > 0) {
    while (ob->conn->count) {
      ob->conn->count--;
      ReadInt32LE(ob->in);
    }
  }
  if (ReadInt16LE(ob->in) != 0x0009) longjmp(ob->conn->exception,1);
  if (ReadInt8LE(ob->in) != 0x1B) longjmp(ob->conn->exception,2);
  if (ReadInt8LE(ob->in) != 0x13) longjmp(ob->conn->exception,3);
  ret = ReadInt32LE(out);
  if (ReadInt8LE(ob->in) != 0x80) longjmp(ob->conn->exception,2);
  return ret;
} 

int32 NetAIOReadys16(NetAIO *ob,const int16* buf) {
  Stream *out = ob->out;
  int ret_len;
  int32 ret;
  WriteInt16LE(ob->out,0x0009);
  WriteInt8LE(ob->out,ob->instance);
  WriteInt8LE(ob->out,0x1C);
  int i;
  WriteInt32LE(ob->out,ArrayLength(buf));
  for (i=0;i<ArrayLength(buf);i++) {
    WriteInt16LE(ob->out,buf[i]);
  }
  ob->out->Flush(ob->out);
  if (ob->conn->mode > 0) {
    while (ob->conn->count) {
      ob->conn->count--;
      ReadInt32LE(ob->in);
    }
  }
  if (ReadInt16LE(ob->in) != 0x0009) longjmp(ob->conn->exception,1);
  if (ReadInt8LE(ob->in) != 0x1C) longjmp(ob->conn->exception,2);
  if (ReadInt8LE(ob->in) != 0x13) longjmp(ob->conn->exception,3);
  ret = ReadInt32LE(out);
  if (ReadInt8LE(ob->in) != 0x80) longjmp(ob->conn->exception,2);
  return ret;
} 

int32 NetAIOReadys32(NetAIO *ob,const int32* buf) {
  Stream *out = ob->out;
  int ret_len;
  int32 ret;
  WriteInt16LE(ob->out,0x0009);
  WriteInt8LE(ob->out,ob->instance);
  WriteInt8LE(ob->out,0x1D);
  int i;
  WriteInt32LE(ob->out,ArrayLength(buf));
  for (i=0;i<ArrayLength(buf);i++) {
    WriteInt32LE(ob->out,buf[i]);
  }
  ob->out->Flush(ob->out);
  if (ob->conn->mode > 0) {
    while (ob->conn->count) {
      ob->conn->count--;
      ReadInt32LE(ob->in);
    }
  }
  if (ReadInt16LE(ob->in) != 0x0009) longjmp(ob->conn->exception,1);
  if (ReadInt8LE(ob->in) != 0x1D) longjmp(ob->conn->exception,2);
  if (ReadInt8LE(ob->in) != 0x13) longjmp(ob->conn->exception,3);
  ret = ReadInt32LE(out);
  if (ReadInt8LE(ob->in) != 0x80) longjmp(ob->conn->exception,2);
  return ret;
} 

