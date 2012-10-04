#ifndef __AIO_h
#define __AIO_h
#undef FUNC
#ifndef SWIGGY
#define FUNC(x) (*x)
#else
#define FUNC(x) x
#endif

typedef struct VoltageSubRange VoltageSubRange;
typedef struct VoltageRange VoltageRange;
typedef struct ActualVoltageRange ActualVoltageRange;
typedef struct PeriodRange PeriodRange;
typedef struct AIO AIO;
struct VoltageSubRange {
  float start;
  float step;
  unsigned count;
};

struct VoltageRange {
  VoltageSubRange low;
  VoltageSubRange high;
};

struct ActualVoltageRange {
  float low;
  float high;
};

struct PeriodRange {
  unsigned start;
  unsigned step;
  unsigned count;
};

typedef enum AIOType{
  AIO_ADC=1,AIO_DAC=2
}AIOType;

enum {
	NetAIO_Lock=0,
	NetAIO_Unlock=1,
	NetAIO_Preempt=2,
	NetAIO_Type=3,
	NetAIO_VoltageRangeList=4,
	NetAIO_PrecisionList=5,
	NetAIO_PeriodRangeList=6,
	NetAIO_TriggerList=7,
	NetAIO_Channels=8,
	NetAIO_Reset=9,
	NetAIO_ChannelEnable=10,
	NetAIO_ChannelSamplePeriod=11,
	NetAIO_ChannelPrecision=12,
	NetAIO_ChannelVoltageRange=13,
	NetAIO_Configuration=14,
	NetAIO_ConfigureTest=15,
	NetAIO_Configure=16,
	NetAIO_ITrig=17,
	NetAIO_Get=18,
	NetAIO_Put=19,
	NetAIO_Ready=20,
	NetAIO_Gets8=21,
	NetAIO_Gets16=22,
	NetAIO_Gets32=23,
	NetAIO_Puts8=24,
	NetAIO_Puts16=25,
	NetAIO_Puts32=26,
	NetAIO_Readys8=27,
	NetAIO_Readys16=28,
	NetAIO_Readys32=29,
	XAIO_APICount=30
};
struct AIO {
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
};
#endif

// Author: Michael Schmidt (michael@embeddedARM.com)
// Copyright (c) 2012, Technologic Systems, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
