/*

need to set oversampling to 0:
CN2_60, CN2_62, CN2_64

16 channels
can enable 0-7 or 0-15
8-bit channel mask applies the nth channel in both chips

Voltage Ranges
-10 to 10V or -5 to 5V
ADC1_RANGE = CN2_56
ADC2_RANGE = CN2_58

Precisions
16-bit

Conversion periods (ns)
1 Hz to 100kHz
10ns per sampling period
10us to ~42.9 seconds in 10ns increments

Trigger
N/A

Interrupt Trigger
N/A


If we get a FIFO overflow we must stop acquiring and return the
data that we were able to acquire before overflow.

doesn't look like we use interrupts anywhere so we have to poll the
number of samples available until we have the number we require.
 */

#ifndef __ts8820ADCAIO_H
#define __ts8820ADCAIO_H
#include "AIO.h"
#include "Bus.h"
#include "Time.h"

typedef struct ts8820ADCAIO ts8820ADCAIO;

struct ts8820ADCAIO {
  AIO;
  Bus *bus;
  DIO *dio;
  int CN2_56,CN2_58,CN2_60,CN2_62,CN2_64;
  int mask,ord[16],n;
  // unenabled stuff
  unsigned period[16];
  int prec[16];
  float low[16], high[16];
};

void *ts8820ADCAIOInit(ts8820ADCAIO *,Bus *);
void ts8820ADCAIOFini(ts8820ADCAIO *);
int ts8820ADCAIOLock(ts8820ADCAIO *,unsigned num,int flags);
int ts8820ADCAIOUnlock(void *me,unsigned num,int flags);
int ts8820ADCAIOPreempt(void *me);
AIOType ts8820ADCAIOType(ts8820ADCAIO *);
VoltageRange* ts8820ADCAIOVoltageRangeList(ts8820ADCAIO *);
int ts8820ADCAIOPrecisionList(ts8820ADCAIO *);
PeriodRange* ts8820ADCAIOPeriodRangeList(ts8820ADCAIO *);
int* ts8820ADCAIOTriggerList(ts8820ADCAIO *);
int ts8820ADCAIOChannels(ts8820ADCAIO *);
void ts8820ADCAIOReset(ts8820ADCAIO *);
int ts8820ADCAIOChannelEnable(ts8820ADCAIO *,int ch,int flag);
unsigned ts8820ADCAIOChannelSamplePeriod(ts8820ADCAIO *,int ch,unsigned ns);
int ts8820ADCAIOChannelPrecision(ts8820ADCAIO *,int ch,int prec);
int ts8820ADCAIOChannelVoltageRange(ts8820ADCAIO *,int ch,float low,float high);
int ts8820ADCAIOConfiguration(ts8820ADCAIO *,float* low,float* high,int* prec,int* t,int* trigger,int itrig[1]);
int ts8820ADCAIOConfigureTest(ts8820ADCAIO *,const float* low,const float* high,const int* prec,const int* t,const int* trigger,int itrig);
int ts8820ADCAIOConfigure(ts8820ADCAIO *,const float* low,const float* high,const int* prec,const int* t,const int* trigger,int itrig);
int ts8820ADCAIOITrig(ts8820ADCAIO *aio,int itrig);
int ts8820ADCAIOGet(ts8820ADCAIO *,int channel);
int ts8820ADCAIOPut(ts8820ADCAIO *,int channel,int value);
int ts8820ADCAIOReady(ts8820ADCAIO *,int channel);
int ts8820ADCAIOGets8(ts8820ADCAIO *,char* buf);
int ts8820ADCAIOGets16(ts8820ADCAIO *,short* buf);
int ts8820ADCAIOGets32(ts8820ADCAIO *,int* buf);
int ts8820ADCAIOPuts8(ts8820ADCAIO *,const char* buf);
int ts8820ADCAIOPuts16(ts8820ADCAIO *,const short* buf);
int ts8820ADCAIOPuts32(ts8820ADCAIO *,const int* buf);
int ts8820ADCAIOReadys8(ts8820ADCAIO *,char* buf);
int ts8820ADCAIOReadys16(ts8820ADCAIO *,short* buf);
int ts8820ADCAIOReadys32(ts8820ADCAIO *,int* buf);

#endif
// Author: Michael Schmidt (michael@embeddedARM.com)
// Copyright (c) 2012, Technologic Systems, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.

