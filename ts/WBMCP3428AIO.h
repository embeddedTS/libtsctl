#ifndef __WBMCP3428AIO_h
#define __WBMCP3428AIO_h
#undef FUNC
#ifndef SWIGGY
#define FUNC(x) (*x)
#else
#define FUNC(x) x
#endif

typedef struct WBMCP3428AIO WBMCP3428AIO;
struct WBMCP3428AIO {
	void *FUNC(Init)(WBMCP3428AIO *me,Bus *,Time *);
	void FUNC(Fini)(WBMCP3428AIO *me);
	int FUNC(Lock)(WBMCP3428AIO *me,unsigned num,int flags);
	int FUNC(Unlock)(WBMCP3428AIO *me,unsigned num,int flags);
	int FUNC(Preempt)(WBMCP3428AIO *me);
	AIOType FUNC(Type)(WBMCP3428AIO *me);
	VoltageRange*FUNC(VoltageRangeList)(WBMCP3428AIO *me);
	int FUNC(PrecisionList)(WBMCP3428AIO *me);
	PeriodRange*FUNC(PeriodRangeList)(WBMCP3428AIO *me);
	int *FUNC(TriggerList)(WBMCP3428AIO *me);
	int FUNC(Channels)(WBMCP3428AIO *me);
	void FUNC(Reset)(WBMCP3428AIO *me);
	int FUNC(ChannelEnable)(WBMCP3428AIO *me,int ch,int flag);
	unsigned FUNC(ChannelSamplePeriod)(WBMCP3428AIO *me,int ch,unsigned ns);
	int FUNC(ChannelPrecision)(WBMCP3428AIO *me,int ch,int prec);
	int FUNC(ChannelVoltageRange)(WBMCP3428AIO *me,int ch,float low,float high);
	int FUNC(Configuration)(WBMCP3428AIO *me,float *low,float *high,int *prec,int *t,int *trigger,int itrig[1]);
	int FUNC(ConfigureTest)(WBMCP3428AIO *me,const float *low,const float *high,const int *prec,const int *rate,const int *trigger,int itrig);
	int FUNC(Configure)(WBMCP3428AIO *me,const float *low,const float *high,const int *prec,const int *rate,const int *trigger,int itrig);
	int FUNC(ITrig)(WBMCP3428AIO *me,int itrig);
	int FUNC(Get)(WBMCP3428AIO *me,int channel);
	int FUNC(Put)(WBMCP3428AIO *me,int channel,int value);
	int FUNC(Ready)(WBMCP3428AIO *me,int channel);
	int FUNC(Gets8)(WBMCP3428AIO *me,char *buf);
	int FUNC(Gets16)(WBMCP3428AIO *me,short *buf);
	int FUNC(Gets32)(WBMCP3428AIO *me,int *buf);
	int FUNC(Puts8)(WBMCP3428AIO *me,const char *buf);
	int FUNC(Puts16)(WBMCP3428AIO *me,const short *buf);
	int FUNC(Puts32)(WBMCP3428AIO *me,const int *buf);
	int FUNC(Readys8)(WBMCP3428AIO *me,const char *buf);
	int FUNC(Readys16)(WBMCP3428AIO *me,const short *buf);
	int FUNC(Readys32)(WBMCP3428AIO *me,const int *buf);
	int InitStatus;
	Bus *bus;
	int offset;
	int configbits[6];
	int active;
	unsigned t0[6];
	unsigned start;
	Time *t;
};

void *WBMCP3428AIOInit(WBMCP3428AIO* ob,Bus *,Time *);
void WBMCP3428AIOFini(WBMCP3428AIO* ob);
int WBMCP3428AIOLock(WBMCP3428AIO* ob,unsigned num,int flags);
int WBMCP3428AIOUnlock(WBMCP3428AIO* ob,unsigned num,int flags);
int WBMCP3428AIOPreempt(WBMCP3428AIO* ob);
AIOType WBMCP3428AIOType(WBMCP3428AIO* ob);
VoltageRange *WBMCP3428AIOVoltageRangeList(WBMCP3428AIO* ob);
int WBMCP3428AIOPrecisionList(WBMCP3428AIO* ob);
PeriodRange *WBMCP3428AIOPeriodRangeList(WBMCP3428AIO* ob);
int *WBMCP3428AIOTriggerList(WBMCP3428AIO* ob);
int WBMCP3428AIOChannels(WBMCP3428AIO* ob);
void WBMCP3428AIOReset(WBMCP3428AIO* ob);
int WBMCP3428AIOChannelEnable(WBMCP3428AIO* ob,int ch,int flag);
unsigned WBMCP3428AIOChannelSamplePeriod(WBMCP3428AIO* ob,int ch,unsigned ns);
int WBMCP3428AIOChannelPrecision(WBMCP3428AIO* ob,int ch,int prec);
int WBMCP3428AIOChannelVoltageRange(WBMCP3428AIO* ob,int ch,float low,float high);
int WBMCP3428AIOConfiguration(WBMCP3428AIO* ob,float *low,float *high,int *prec,int *t,int *trigger,int itrig[1]);
int WBMCP3428AIOConfigureTest(WBMCP3428AIO* ob,const float *low,const float *high,const int *prec,const int *rate,const int *trigger,int itrig);
int WBMCP3428AIOConfigure(WBMCP3428AIO* ob,const float *low,const float *high,const int *prec,const int *rate,const int *trigger,int itrig);
int WBMCP3428AIOITrig(WBMCP3428AIO* ob,int itrig);
int WBMCP3428AIOGet(WBMCP3428AIO* ob,int channel);
int WBMCP3428AIOPut(WBMCP3428AIO* ob,int channel,int value);
int WBMCP3428AIOReady(WBMCP3428AIO* ob,int channel);
int WBMCP3428AIOGets8(WBMCP3428AIO* ob,char *buf);
int WBMCP3428AIOGets16(WBMCP3428AIO* ob,short *buf);
int WBMCP3428AIOGets32(WBMCP3428AIO* ob,int *buf);
int WBMCP3428AIOPuts8(WBMCP3428AIO* ob,const char *buf);
int WBMCP3428AIOPuts16(WBMCP3428AIO* ob,const short *buf);
int WBMCP3428AIOPuts32(WBMCP3428AIO* ob,const int *buf);
int WBMCP3428AIOReadys8(WBMCP3428AIO* ob,const char *buf);
int WBMCP3428AIOReadys16(WBMCP3428AIO* ob,const short *buf);
int WBMCP3428AIOReadys32(WBMCP3428AIO* ob,const int *buf);
#endif

// Author: Michael Schmidt (michael@embeddedARM.com)
// Copyright (c) 2012, Technologic Systems, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
