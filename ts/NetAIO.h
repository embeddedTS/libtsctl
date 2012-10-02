#ifndef __NetAIO_H
#define __NetAIO_H
#include "Net.h"
#include "AIO.h"
typedef struct NetAIO NetAIO;

struct NetAIO {
  AIO;
  int inst;
  int socket;
  int mode;
  Packet *q;
  int *cmds;
};

void *NetAIOInit(NetAIO *,int socket,int inst,int mode,Packet *q,int *cmds);
void NetAIOFini(NetAIO *);
int NetAIOLock(NetAIO *,int,unsigned);
AIOType NetAIOType(NetAIO *);
int NetAIOVoltageRangeListLength(NetAIO *);
int NetAIOVoltageRange(NetAIO *,int i,VoltageRange *rr);
int NetAIOPrecisionList(NetAIO *);
int NetAIOPeriodRangeListLength(NetAIO *);
int NetAIOPeriodRange(NetAIO *,int i,PeriodRange *r);
int NetAIOTriggerListLength(NetAIO *);
int NetAIOTriggerList(NetAIO *,int *tlist);
int NetAIOChannels(NetAIO *);
int NetAIOConfiguration(NetAIO *,float *low,float *high,int *prec,int *t,int *trigger,int *itrig);
int NetAIOConfigureTest(NetAIO *,int count,float *low,float *high,int *prec,int *t,int *trigger,int itrig);
int NetAIOConfigure(NetAIO *,int count,float *low,float *high,int *prec,int *t,int *trigger,int itrig);
int NetAIOITrig(AIO *,int itrig);
int NetAIOGet(NetAIO *,int channel);
int NetAIOPut(NetAIO *,int channel,int value);
int NetAIOReady(NetAIO *,int channel);
int NetAIOGets(NetAIO *,int samples,void *buf);
int NetAIOPuts(NetAIO *,int samples,void *buf);
int NetAIOReadys(NetAIO *,int samples,int *buf);

#endif
// Author: Michael Schmidt (michael@embeddedARM.com)
// Copyright (c) 2011, Technologic Systems, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
