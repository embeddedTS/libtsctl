#ifndef __DIOTWI_H
#define __DIOTWI_H
#include "TWI.h"
#include "DIO.h"
#include "Time.h"

typedef struct DIOTWI DIOTWI;
struct DIOTWI {
  TWI;
  DIO *dio; // DIO module contain the DIO to use as TW_CLK and TS_DAT
  Time *Time;
  int TW_CLK,TW_DAT; // DIO numbers
  int Speed; // baud rate config
  int delay; // microseconds per half clock cycle
  int LockNum;
  unsigned start;
};

void *DIOTWIInit(DIOTWI *,void *dio,void *time);
void DIOTWIFini(DIOTWI *);
int DIOTWILock(DIOTWI *,unsigned num,int);
int DIOTWIUnlock(DIOTWI *,unsigned num,int);
void DIOTWIPreempt(DIOTWI *);
int DIOTWIWrite(DIOTWI *,int devadr,int adrslen,int adrs,const char* bytes);
int DIOTWIRead(DIOTWI *,int devadr,int adrslen,int adrs,char* bytes);

#endif
// Author: Michael Schmidt (michael@embeddedARM.com)
// Copyright (c) 2012, Technologic Systems, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
