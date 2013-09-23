#ifndef __ts8820ADCAIO_h
#define __ts8820ADCAIO_h
#include "Bus.h"
#include "DIO.h"
#include "AIO.h"
#undef FUNC
#ifndef SWIGGY
#define FUNC(x) (*x)
#else
#define FUNC(x) x
#endif

typedef struct ts8820ADCAIO ts8820ADCAIO;
struct ts8820ADCAIO {
	void *FUNC(Init)(ts8820ADCAIO *me,Bus *);
	void FUNC(Fini)(ts8820ADCAIO *me);
	int FUNC(Lock)(ts8820ADCAIO *me,unsigned num,int flags);
	int FUNC(Unlock)(ts8820ADCAIO *me,unsigned num,int flags);
	int FUNC(Preempt)(ts8820ADCAIO *me);
	AIOType FUNC(Type)(ts8820ADCAIO *me);
	VoltageRange*FUNC(VoltageRangeList)(ts8820ADCAIO *me);
	int FUNC(PrecisionList)(ts8820ADCAIO *me);
	PeriodRange*FUNC(PeriodRangeList)(ts8820ADCAIO *me);
	int *FUNC(TriggerList)(ts8820ADCAIO *me);
	int FUNC(Channels)(ts8820ADCAIO *me);
	void FUNC(Reset)(ts8820ADCAIO *me);
	int FUNC(ChannelEnable)(ts8820ADCAIO *me,int ch,int flag);
	unsigned FUNC(ChannelSamplePeriod)(ts8820ADCAIO *me,int ch,unsigned ns);
	int FUNC(ChannelPrecision)(ts8820ADCAIO *me,int ch,int prec);
	int FUNC(ChannelVoltageRange)(ts8820ADCAIO *me,int ch,float low,float high);
	int FUNC(Configuration)(ts8820ADCAIO *me,float *low,float *high,int *prec,int *t,int *trigger,int itrig[1]);
	int FUNC(ConfigureTest)(ts8820ADCAIO *me,const float *low,const float *high,const int *prec,const int *rate,const int *trigger,int itrig);
	int FUNC(Configure)(ts8820ADCAIO *me,const float *low,const float *high,const int *prec,const int *rate,const int *trigger,int itrig);
	int FUNC(ITrig)(ts8820ADCAIO *me,int itrig);
	int FUNC(Get)(ts8820ADCAIO *me,int channel);
	int FUNC(Put)(ts8820ADCAIO *me,int channel,int value);
	int FUNC(Ready)(ts8820ADCAIO *me,int channel);
	int FUNC(Gets8)(ts8820ADCAIO *me,char *buf);
	int FUNC(Gets16)(ts8820ADCAIO *me,short *buf);
	int FUNC(Gets32)(ts8820ADCAIO *me,int *buf);
	int FUNC(Puts8)(ts8820ADCAIO *me,const char *buf);
	int FUNC(Puts16)(ts8820ADCAIO *me,const short *buf);
	int FUNC(Puts32)(ts8820ADCAIO *me,const int *buf);
	int FUNC(Readys8)(ts8820ADCAIO *me,const char *buf);
	int FUNC(Readys16)(ts8820ADCAIO *me,const short *buf);
	int FUNC(Readys32)(ts8820ADCAIO *me,const int *buf);
	int InitStatus;
	Bus *bus;
	DIO *dio;
	int CN2_56;
	int CN2_58;
	int CN2_60;
	int CN2_62;
	int CN2_64;
	int mask;
	int ord[16];
	int n;
	unsigned period[16];
	int prec[16];
	float low[16];
	float high[16];
};

void *ts8820ADCAIOInit(ts8820ADCAIO* ob,Bus *);
void ts8820ADCAIOFini(ts8820ADCAIO* ob);
int ts8820ADCAIOLock(ts8820ADCAIO* ob,unsigned num,int flags);
int ts8820ADCAIOUnlock(ts8820ADCAIO* ob,unsigned num,int flags);
int ts8820ADCAIOPreempt(ts8820ADCAIO* ob);
AIOType ts8820ADCAIOType(ts8820ADCAIO* ob);
VoltageRange *ts8820ADCAIOVoltageRangeList(ts8820ADCAIO* ob);
int ts8820ADCAIOPrecisionList(ts8820ADCAIO* ob);
PeriodRange *ts8820ADCAIOPeriodRangeList(ts8820ADCAIO* ob);
int *ts8820ADCAIOTriggerList(ts8820ADCAIO* ob);
int ts8820ADCAIOChannels(ts8820ADCAIO* ob);
void ts8820ADCAIOReset(ts8820ADCAIO* ob);
int ts8820ADCAIOChannelEnable(ts8820ADCAIO* ob,int ch,int flag);
unsigned ts8820ADCAIOChannelSamplePeriod(ts8820ADCAIO* ob,int ch,unsigned ns);
int ts8820ADCAIOChannelPrecision(ts8820ADCAIO* ob,int ch,int prec);
int ts8820ADCAIOChannelVoltageRange(ts8820ADCAIO* ob,int ch,float low,float high);
int ts8820ADCAIOConfiguration(ts8820ADCAIO* ob,float *low,float *high,int *prec,int *t,int *trigger,int itrig[1]);
int ts8820ADCAIOConfigureTest(ts8820ADCAIO* ob,const float *low,const float *high,const int *prec,const int *rate,const int *trigger,int itrig);
int ts8820ADCAIOConfigure(ts8820ADCAIO* ob,const float *low,const float *high,const int *prec,const int *rate,const int *trigger,int itrig);
int ts8820ADCAIOITrig(ts8820ADCAIO* ob,int itrig);
int ts8820ADCAIOGet(ts8820ADCAIO* ob,int channel);
int ts8820ADCAIOPut(ts8820ADCAIO* ob,int channel,int value);
int ts8820ADCAIOReady(ts8820ADCAIO* ob,int channel);
int ts8820ADCAIOGets8(ts8820ADCAIO* ob,char *buf);
int ts8820ADCAIOGets16(ts8820ADCAIO* ob,short *buf);
int ts8820ADCAIOGets32(ts8820ADCAIO* ob,int *buf);
int ts8820ADCAIOPuts8(ts8820ADCAIO* ob,const char *buf);
int ts8820ADCAIOPuts16(ts8820ADCAIO* ob,const short *buf);
int ts8820ADCAIOPuts32(ts8820ADCAIO* ob,const int *buf);
int ts8820ADCAIOReadys8(ts8820ADCAIO* ob,const char *buf);
int ts8820ADCAIOReadys16(ts8820ADCAIO* ob,const short *buf);
int ts8820ADCAIOReadys32(ts8820ADCAIO* ob,const int *buf);
#endif

// Author: Michael Schmidt (michael@embeddedARM.com)
// Copyright (c) 2012, Technologic Systems, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
