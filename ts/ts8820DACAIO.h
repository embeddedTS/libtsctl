#ifndef __ts8820DACAIO_h
#define __ts8820DACAIO_h
#include "Bus.h"
#include "AIO.h"
#undef FUNC
#ifndef SWIGGY
#define FUNC(x) (*x)
#else
#define FUNC(x) x
#endif

typedef struct ts8820DACAIO ts8820DACAIO;
struct ts8820DACAIO {
	void *FUNC(Init)(ts8820DACAIO *me,Bus *);
	void FUNC(Fini)(ts8820DACAIO *me);
	int FUNC(Lock)(ts8820DACAIO *me,unsigned num,int flags);
	int FUNC(Unlock)(ts8820DACAIO *me,unsigned num,int flags);
	int FUNC(Preempt)(ts8820DACAIO *me);
	AIOType FUNC(Type)(ts8820DACAIO *me);
	VoltageRange*FUNC(VoltageRangeList)(ts8820DACAIO *me);
	int FUNC(PrecisionList)(ts8820DACAIO *me);
	PeriodRange*FUNC(PeriodRangeList)(ts8820DACAIO *me);
	int *FUNC(TriggerList)(ts8820DACAIO *me);
	int FUNC(Channels)(ts8820DACAIO *me);
	void FUNC(Reset)(ts8820DACAIO *me);
	int FUNC(ChannelEnable)(ts8820DACAIO *me,int ch,int flag);
	unsigned FUNC(ChannelSamplePeriod)(ts8820DACAIO *me,int ch,unsigned ns);
	int FUNC(ChannelPrecision)(ts8820DACAIO *me,int ch,int prec);
	int FUNC(ChannelVoltageRange)(ts8820DACAIO *me,int ch,float low,float high);
	int FUNC(Configuration)(ts8820DACAIO *me,float *low,float *high,int *prec,int *t,int *trigger,int itrig[1]);
	int FUNC(ConfigureTest)(ts8820DACAIO *me,const float *low,const float *high,const int *prec,const int *rate,const int *trigger,int itrig);
	int FUNC(Configure)(ts8820DACAIO *me,const float *low,const float *high,const int *prec,const int *rate,const int *trigger,int itrig);
	int FUNC(ITrig)(ts8820DACAIO *me,int itrig);
	int FUNC(Get)(ts8820DACAIO *me,int channel);
	int FUNC(Put)(ts8820DACAIO *me,int channel,int value);
	int FUNC(Ready)(ts8820DACAIO *me,int channel);
	int FUNC(Gets8)(ts8820DACAIO *me,char *buf);
	int FUNC(Gets16)(ts8820DACAIO *me,short *buf);
	int FUNC(Gets32)(ts8820DACAIO *me,int *buf);
	int FUNC(Puts8)(ts8820DACAIO *me,const char *buf);
	int FUNC(Puts16)(ts8820DACAIO *me,const short *buf);
	int FUNC(Puts32)(ts8820DACAIO *me,const int *buf);
	int FUNC(Readys8)(ts8820DACAIO *me,const char *buf);
	int FUNC(Readys16)(ts8820DACAIO *me,const short *buf);
	int FUNC(Readys32)(ts8820DACAIO *me,const int *buf);
	int InitStatus;
	Bus *bus;
};

void *ts8820DACAIOInit(ts8820DACAIO* ob,Bus *);
void ts8820DACAIOFini(ts8820DACAIO* ob);
int ts8820DACAIOLock(ts8820DACAIO* ob,unsigned num,int flags);
int ts8820DACAIOUnlock(ts8820DACAIO* ob,unsigned num,int flags);
int ts8820DACAIOPreempt(ts8820DACAIO* ob);
AIOType ts8820DACAIOType(ts8820DACAIO* ob);
VoltageRange *ts8820DACAIOVoltageRangeList(ts8820DACAIO* ob);
int ts8820DACAIOPrecisionList(ts8820DACAIO* ob);
PeriodRange *ts8820DACAIOPeriodRangeList(ts8820DACAIO* ob);
int *ts8820DACAIOTriggerList(ts8820DACAIO* ob);
int ts8820DACAIOChannels(ts8820DACAIO* ob);
void ts8820DACAIOReset(ts8820DACAIO* ob);
int ts8820DACAIOChannelEnable(ts8820DACAIO* ob,int ch,int flag);
unsigned ts8820DACAIOChannelSamplePeriod(ts8820DACAIO* ob,int ch,unsigned ns);
int ts8820DACAIOChannelPrecision(ts8820DACAIO* ob,int ch,int prec);
int ts8820DACAIOChannelVoltageRange(ts8820DACAIO* ob,int ch,float low,float high);
int ts8820DACAIOConfiguration(ts8820DACAIO* ob,float *low,float *high,int *prec,int *t,int *trigger,int itrig[1]);
int ts8820DACAIOConfigureTest(ts8820DACAIO* ob,const float *low,const float *high,const int *prec,const int *rate,const int *trigger,int itrig);
int ts8820DACAIOConfigure(ts8820DACAIO* ob,const float *low,const float *high,const int *prec,const int *rate,const int *trigger,int itrig);
int ts8820DACAIOITrig(ts8820DACAIO* ob,int itrig);
int ts8820DACAIOGet(ts8820DACAIO* ob,int channel);
int ts8820DACAIOPut(ts8820DACAIO* ob,int channel,int value);
int ts8820DACAIOReady(ts8820DACAIO* ob,int channel);
int ts8820DACAIOGets8(ts8820DACAIO* ob,char *buf);
int ts8820DACAIOGets16(ts8820DACAIO* ob,short *buf);
int ts8820DACAIOGets32(ts8820DACAIO* ob,int *buf);
int ts8820DACAIOPuts8(ts8820DACAIO* ob,const char *buf);
int ts8820DACAIOPuts16(ts8820DACAIO* ob,const short *buf);
int ts8820DACAIOPuts32(ts8820DACAIO* ob,const int *buf);
int ts8820DACAIOReadys8(ts8820DACAIO* ob,const char *buf);
int ts8820DACAIOReadys16(ts8820DACAIO* ob,const short *buf);
int ts8820DACAIOReadys32(ts8820DACAIO* ob,const int *buf);
#endif

// Author: Michael Schmidt (michael@embeddedARM.com)
// Copyright (c) 2012, Technologic Systems, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
