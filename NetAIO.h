#ifndef __NetAIO_H
#define __NetAIO_H
#include "Net2.h"
#include "Stream.h"
#include "AIO.h"

typedef struct NetAIO NetAIO;

struct NetAIO {
  void *FUNC(Init)(void *me,...);
  void FUNC(Fini)(void *me);
  int FUNC(Lock)(void *me,unsigned num,int flags);
  int FUNC(Unlock)(void *me,unsigned num,int flags);
  int FUNC(Preempt)(void *me);
  AIOType FUNC(Type)(void *me);
  VoltageRange*FUNC(VoltageRangeList)(void *me);
  int FUNC(PrecisionList)(void *me);
  PeriodRange*FUNC(PeriodRangeList)(void *me);
  int *FUNC(TriggerList)(void *me);
  int FUNC(Channels)(void *me);
  void FUNC(Reset)(void *me);
  int FUNC(ChannelEnable)(void *me,int ch,int flag);
  unsigned FUNC(ChannelSamplePeriod)(void *me,int ch,unsigned ns);
  int FUNC(ChannelPrecision)(void *me,int ch,int prec);
  int FUNC(ChannelVoltageRange)(void *me,int ch,float low,float high);
  int FUNC(Configuration)(void *me,float *low,float *high,int *prec,int *t,int *trigger,int itrig[1]);
  int FUNC(ConfigureTest)(void *me,const float *low,const float *high,const int *prec,const int *rate,const int *trigger,int itrig);
  int FUNC(Configure)(void *me,const float *low,const float *high,const int *prec,const int *rate,const int *trigger,int itrig);
  int FUNC(ITrig)(void *me,int itrig);
  int FUNC(Get)(void *me,int channel);
  int FUNC(Put)(void *me,int channel,int value);
  int FUNC(Ready)(void *me,int channel);
  int FUNC(Gets8)(void *me,char *buf);
  int FUNC(Gets16)(void *me,short *buf);
  int FUNC(Gets32)(void *me,int *buf);
  int FUNC(Puts8)(void *me,const char *buf);
  int FUNC(Puts16)(void *me,const short *buf);
  int FUNC(Puts32)(void *me,const int *buf);
  int FUNC(Readys8)(void *me,const char *buf);
  int FUNC(Readys16)(void *me,const short *buf);
  int FUNC(Readys32)(void *me,const int *buf);
  int InitStatus;
  tsctl *conn;
  int instance;
  Stream *in,*out;
};
void *NetAIOInit(tsctl *,int instance);
void *NetAIOFini(NetAIO *);
int32 NetAIOLock(NetAIO *ob,uint32 num,int32 flags);
int32 NetAIOUnlock(NetAIO *ob,uint32 num,int32 flags);
int32 NetAIOPreempt(NetAIO *ob);
AIOType NetAIOType(NetAIO *ob);
VoltageRange* NetAIOVoltageRangeList(NetAIO *ob);
int32 NetAIOPrecisionList(NetAIO *ob);
PeriodRange* NetAIOPeriodRangeList(NetAIO *ob);
int32* NetAIOTriggerList(NetAIO *ob);
int32 NetAIOChannels(NetAIO *ob);
void NetAIOReset(NetAIO *ob);
int32 NetAIOChannelEnable(NetAIO *ob,int32 ch,int32 flag);
uint32 NetAIOChannelSamplePeriod(NetAIO *ob,int32 ch,uint32 ns);
int32 NetAIOChannelPrecision(NetAIO *ob,int32 ch,int32 prec);
int32 NetAIOChannelVoltageRange(NetAIO *ob,int32 ch,real32 low,real32 high);
int32 NetAIOConfiguration(NetAIO *ob,real32* low,real32* high,int32* prec,int32* t,int32* trigger,int32 itrig[1]);
int32 NetAIOConfigureTest(NetAIO *ob,const real32* low,const real32* high,const int32* prec,const int32* rate,const int32* trigger,int32 itrig);
int32 NetAIOConfigure(NetAIO *ob,const real32* low,const real32* high,const int32* prec,const int32* rate,const int32* trigger,int32 itrig);
int32 NetAIOITrig(NetAIO *ob,int32 itrig);
int32 NetAIOGet(NetAIO *ob,int32 channel);
int32 NetAIOPut(NetAIO *ob,int32 channel,int32 value);
int32 NetAIOReady(NetAIO *ob,int32 channel);
int32 NetAIOGets8(NetAIO *ob,int8* buf);
int32 NetAIOGets16(NetAIO *ob,int16* buf);
int32 NetAIOGets32(NetAIO *ob,int32* buf);
int32 NetAIOPuts8(NetAIO *ob,const int8* buf);
int32 NetAIOPuts16(NetAIO *ob,const int16* buf);
int32 NetAIOPuts32(NetAIO *ob,const int32* buf);
int32 NetAIOReadys8(NetAIO *ob,const int8* buf);
int32 NetAIOReadys16(NetAIO *ob,const int16* buf);
int32 NetAIOReadys32(NetAIO *ob,const int32* buf);
#endif
// Author: Michael Schmidt (michael@embeddedARM.com)
// Copyright (c) 2012, Technologic Systems, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
