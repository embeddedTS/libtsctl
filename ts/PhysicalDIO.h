#ifndef __PhysicalDIO_H
#define __PhysicalDIO_H
#include "arch.h"
#include "DIO.h"
#include "Bus.h"
#include "DIORaw.h"
#include "Pin.h"

typedef struct PhysicalDIO PhysicalDIO;

struct PhysicalDIO {
  DIO;
  unsigned NumLocks;
  Bus *bus;
  DIORaw *dio;
  int gotHUP;
  unsigned char *Caps; // length = NumLocks
};

void *PhysicalDIOInit(PhysicalDIO *,void *bus,void *dio);
void PhysicalDIOFini(PhysicalDIO *);
int PhysicalDIOLock(PhysicalDIO *dio,unsigned num,int flags);
int PhysicalDIOUnlock(PhysicalDIO *dio,unsigned num,int flags);
void PhysicalDIOPreempt(PhysicalDIO *dio);
void PhysicalDIORefresh(PhysicalDIO *);
void PhysicalDIOCommit(PhysicalDIO *,int forceall);
void PhysicalDIOSet(PhysicalDIO *,int DIONum,DIOState State);
DIOState PhysicalDIOGet(PhysicalDIO *,int DIONum);
void PhysicalDIOSetAsync(PhysicalDIO *,int DIONum,DIOState State);
DIOState PhysicalDIOGetAsync(PhysicalDIO *,int DIONum);
void PhysicalDIOWait(PhysicalDIO *,int* match,int min,int max,
		    int* h,int* l);
unsigned PhysicalDIOCount(PhysicalDIO *);
DIOCaps PhysicalDIOCapabilities(PhysicalDIO *,unsigned num);
int PhysicalDIOGetMulti(PhysicalDIO *,char*,int);

#endif
// Author: Michael Schmidt (michael@embeddedARM.com)
// Copyright (c) 2012, Technologic Systems, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
