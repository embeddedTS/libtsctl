#ifndef __AggregateDIO_H
#define __AggregateDIO_H
#include "DIO.h"
#include "Bus.h"
#include "Pin.h"

typedef struct AggregateDIO AggregateDIO;

struct AggregateDIO {
  DIO;
  DIO **dio;
  Pin *pin;
  int nCount; // number of DIO sub objects
  int *SubCount; // number of DIOs in each sub DIO object
};

/*
AggregateDIO dio0;
DIO *pDIO[4];
int SubCount[4];

AggregateDIOInit(&dio0,4,PinInit(0),SubCount,pDIO,
                 DIOInit(1),DIOInit(1),DIOInit(1),DIOInit(1));
 */
void *AggregateDIOInit(AggregateDIO *ob,unsigned Count,void *pin,
		       int *SubCount,DIO **pDIO);
void AggregateDIOFini(AggregateDIO *);
int AggregateDIOLock(AggregateDIO *dio,unsigned num,int flags);
int AggregateDIOUnlock(AggregateDIO *dio,unsigned num,int flags);
void AggregateDIOPreempt(AggregateDIO *dio);
void AggregateDIORefresh(AggregateDIO *);
void AggregateDIOCommit(AggregateDIO *,int forceall);
void AggregateDIOSet(AggregateDIO *,int DIONum,DIOState State);
DIOState AggregateDIOGet(AggregateDIO *,int DIONum);
void AggregateDIOSetAsync(AggregateDIO *,int DIONum,DIOState State);
DIOState AggregateDIOGetAsync(AggregateDIO *,int DIONum);
void AggregateDIOWait(AggregateDIO *,int* match,int min,int max,
		     int* h,int* l);
unsigned AggregateDIOCount(AggregateDIO *);
DIOCaps AggregateDIOCapabilities(AggregateDIO *,unsigned num);
int AggregateDIOGetMulti(AggregateDIO *dio,char* bits,int offset);

#endif
// Author: Michael Schmidt (michael@embeddedARM.com)
// Copyright (c) 2012, Technologic Systems, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
