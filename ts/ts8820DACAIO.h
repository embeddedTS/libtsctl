#ifndef __ts8820DACAIO_H
#define __ts8820DACAIO_H
#include "AIO.h"
#include "Bus.h"
#include "Time.h"

typedef struct ts8820DACAIO ts8820DACAIO;

struct ts8820DACAIO {
  AIO;
  Bus *bus;
};

void *ts8820DACAIOInit(ts8820DACAIO *,Bus *);
void ts8820DACAIOFini(ts8820DACAIO *);
int ts8820DACAIOLock(ts8820DACAIO *,unsigned num,int flags);
int ts8820DACAIOUnlock(void *me,unsigned num,int flags);
int ts8820DACAIOPreempt(void *me);
AIOType ts8820DACAIOType(ts8820DACAIO *);
VoltageRange* ts8820DACAIOVoltageRangeList(ts8820DACAIO *);
int ts8820DACAIOPrecisionList(ts8820DACAIO *);
PeriodRange* ts8820DACAIOPeriodRangeList(ts8820DACAIO *);
int* ts8820DACAIOTriggerList(ts8820DACAIO *);
int ts8820DACAIOChannels(ts8820DACAIO *);
int ts8820DACAIOConfiguration(ts8820DACAIO *,float* low,float* high,int* prec,int* t,int* trigger,int itrig[1]);
int ts8820DACAIOConfigureTest(ts8820DACAIO *,const float* low,const float* high,const int* prec,const int* t,const int* trigger,int itrig);
int ts8820DACAIOConfigure(ts8820DACAIO *,const float* low,const float* high,const int* prec,const int* t,const int* trigger,int itrig);
int ts8820DACAIOITrig(ts8820DACAIO *aio,int itrig);
int ts8820DACAIOGet(ts8820DACAIO *,int channel);
int ts8820DACAIOPut(ts8820DACAIO *,int channel,int value);
int ts8820DACAIOReady(ts8820DACAIO *,int channel);
int ts8820DACAIOGets8(ts8820DACAIO *,char* buf);
int ts8820DACAIOGets16(ts8820DACAIO *,short* buf);
int ts8820DACAIOGets32(ts8820DACAIO *,int* buf);
int ts8820DACAIOPuts8(ts8820DACAIO *,const char* buf);
int ts8820DACAIOPuts16(ts8820DACAIO *,const short* buf);
int ts8820DACAIOPuts32(ts8820DACAIO *,const int* buf);
int ts8820DACAIOReadys8(ts8820DACAIO *,char* buf);
int ts8820DACAIOReadys16(ts8820DACAIO *,short* buf);
int ts8820DACAIOReadys32(ts8820DACAIO *,int* buf);

#endif
// Author: Michael Schmidt (michael@embeddedARM.com)
// Copyright (c) 2012, Technologic Systems, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.

