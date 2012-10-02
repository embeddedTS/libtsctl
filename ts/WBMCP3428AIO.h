#ifndef __WBMCP3428AIO_H
#define __WBMCP3428AIO_H
#include "AIO.h"
#include "Bus.h"
#include "Time.h"

typedef struct WBMCP3428AIO WBMCP3428AIO;

struct WBMCP3428AIO {
  AIO;
  Bus *bus;
  int offset;
  int configbits[6]; // precision and gain setting for each channel
  int active; // currently active channel (-1 = none)
  unsigned t0[6]; // amount of time to wait for each channel
  unsigned start; // time last channel became active
  Time *t;
};

int WBMCP3428AIOInit(WBMCP3428AIO *,Bus *,Time *);
void WBMCP3428AIOFini(WBMCP3428AIO *);
int WBMCP3428AIOLock(WBMCP3428AIO *,int command,unsigned num);    
AIOType WBMCP3428AIOType(WBMCP3428AIO *);
int WBMCP3428AIOVoltageRangeListLength(WBMCP3428AIO *);
int WBMCP3428AIOVoltageRange(WBMCP3428AIO *,int i,VoltageRange *rr);
int WBMCP3428AIOPrecisionList(WBMCP3428AIO *);
int WBMCP3428AIOPeriodRangeListLength(WBMCP3428AIO *);
int WBMCP3428AIOPeriodRange(WBMCP3428AIO *,int i,PeriodRange *r);
int WBMCP3428AIOTriggerListLength(WBMCP3428AIO *);
int WBMCP3428AIOTriggerList(WBMCP3428AIO *,int *tlist);
int WBMCP3428AIOChannels(WBMCP3428AIO *);
int WBMCP3428AIOConfiguration(WBMCP3428AIO *,float *low,float *high,int *prec,int *t,int *trigger,int *itrig);
int WBMCP3428AIOConfigureTest(WBMCP3428AIO *,int count,float *low,float *high,int *prec,int *t,int *trigger,int itrig);
int WBMCP3428AIOConfigure(WBMCP3428AIO *,int count,float *low,float *high,int *prec,int *t,int *trigger,int itrig);

int WBMCP3428AIOGet(WBMCP3428AIO *,int channel);
int WBMCP3428AIOPut(WBMCP3428AIO *,int channel,int value);
int WBMCP3428AIOReady(WBMCP3428AIO *,int channel);
int WBMCP3428AIOGets(WBMCP3428AIO *,int samples,void *buf);
int WBMCP3428AIOPuts(WBMCP3428AIO *,int samples,void *buf);
int WBMCP3428AIOReadys(WBMCP3428AIO *,int samples,void *buf);

#endif
// Author: Michael Schmidt (michael@embeddedARM.com)
// Copyright (c) 2011, Technologic Systems, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
