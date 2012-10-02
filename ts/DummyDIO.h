#ifndef __DummyDIO_H
#define __DummyDIO_H
#include "DIO.h"
#include "Bus.h"
#include "DIORaw.h"
#include "Pin.h"

typedef struct DummyDIO DummyDIO;

struct DummyDIO {
  DIO;
  unsigned NumLocks;
};

void *DummyDIOInit(DummyDIO *,int count);
void DummyDIOFini(DummyDIO *);
int DummyDIOLock(DummyDIO *dio,unsigned num,int flags);
int DummyDIOUnlock(DummyDIO *dio,unsigned num,int flags);
void DummyDIOPreempt(DummyDIO *dio);
void DummyDIORefresh(DummyDIO *);
void DummyDIOCommit(DummyDIO *,int forceall);
void DummyDIOSet(DummyDIO *,int DIONum,DIOState State);
DIOState DummyDIOGet(DummyDIO *,int DIONum);
void DummyDIOSetAsync(DummyDIO *,int DIONum,DIOState State);
DIOState DummyDIOGetAsync(DummyDIO *,int DIONum);
void DummyDIOWait(DummyDIO *,int* match,int min,int max,
		    int* h,int* l);
unsigned DummyDIOCount(DummyDIO *);
DIOCaps DummyDIOCapabilities(DummyDIO *,unsigned num);
int DummyDIOGetMulti(DummyDIO *dio,char* bits,int);

#endif
// Author: Michael Schmidt (michael@embeddedARM.com)
// Copyright (c) 2012, Technologic Systems, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
