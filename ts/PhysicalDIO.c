#ifndef PhysicalDIO_c
#define PhysicalDIO_c
#include <sched.h>
#include "PhysicalDIO.h"
#include "FPGA.h"
#include "Array.h"

void *PhysicalDIOInit(PhysicalDIO *dio,void *bus1,void *sub1) {
  Bus *bus = bus1;
  DIORaw *sub = sub1;
  int err;

  if (dio->InitStatus > 0) return dio;

  dio->Init = (void *)PhysicalDIOInit;
  dio->Fini = (void *)PhysicalDIOFini;
  dio->Lock = (void *)PhysicalDIOLock;
  dio->Unlock = (void *)PhysicalDIOUnlock;
  dio->Preempt = (void *)PhysicalDIOPreempt;
  dio->Refresh = (void *)PhysicalDIORefresh;
  dio->Commit = (void *)PhysicalDIOCommit;
  dio->Set = (void *)PhysicalDIOSet;
  dio->Get = (void *)PhysicalDIOGet;
  dio->SetAsync = (void *)PhysicalDIOSetAsync;
  dio->GetAsync = (void *)PhysicalDIOGetAsync;
  dio->Wait = (void *)PhysicalDIOWait;
  dio->Count = (void *)PhysicalDIOCount;
  dio->Capabilities = (void *)PhysicalDIOCapabilities;
  dio->GetMulti = (void *)PhysicalDIOGetMulti;

  dio->bus = bus;
  dio->dio = sub;
  dio->NumLocks = sub->Count(sub);
  if (dio->bus->InitStatus <= 0
      ||dio->dio->InitStatus <= 0) {
    dio->Fini(dio);
    dio->InitStatus = -1;
    return dio;
  }
  if ((err=FPGAReloadRegister(&dio->gotHUP,7)) < 0) {
    dio->Fini(dio);
    dio->InitStatus = err;
    return dio;
  }
  dio->InitStatus = 1;
  return dio;
}

void PhysicalDIOFini(PhysicalDIO *dio) {
  if (dio->InitStatus > 0) {
    FPGAReloadUnregister(&dio->gotHUP);
  }
  dio->bus->Fini(dio->bus);
  if (dio->InitStatus > 0) dio->InitStatus = 0;
}

void PhysicalDIORefresh(PhysicalDIO *dio) {
  dio->bus->Lock(dio->bus,0,0);
  if (dio->gotHUP) {
    dio->bus->Commit(dio->bus,1);
    dio->gotHUP = 0;
  }
  dio->bus->Refresh(dio->bus);
  dio->bus->Unlock(dio->bus,0,0);
}

void PhysicalDIOCommit(PhysicalDIO *dio,int forceall) {
  if (dio->gotHUP) {
    forceall = 1;
    dio->gotHUP = 0;
  }
  dio->bus->Lock(dio->bus,0,0);
  dio->bus->Commit(dio->bus,forceall);
  dio->bus->Unlock(dio->bus,0,0);
}

static inline void _DIOSet(DIORaw *dio,int Num,DIOState State) {
  if (State < 0) {
    dio->DirSet(dio,Num,0);
  } else {
    // Set data first to avoid glitch if current state doesn't match new state
    dio->DataSet(dio,Num,State==HIGH);
    dio->DirSet(dio,Num,1);
  }
}

static inline DIOState _DIOGet(DIORaw *dio,int Num) {
  if (dio->DirGet(dio,Num)) {
    return dio->DataGet(dio,Num);
  } else {
    return INPUT_LOW + dio->DataGet(dio,Num);    
  }
}

void PhysicalDIOSet(PhysicalDIO *dio,int DIONum,DIOState State) {
  if (DIONum < 0 || DIONum > dio->NumLocks 
      || dio->Caps[DIONum] == DIO_NOT_PRESENT) return;
  dio->bus->Lock(dio->bus,0,0);
  _DIOSet(dio->dio,~DIONum,State);
  dio->bus->Unlock(dio->bus,0,0);
}

DIOState PhysicalDIOGet(PhysicalDIO *dio,int DIONum) {
  DIOState ret;
  if (DIONum < 0 || DIONum > dio->NumLocks 
      || dio->Caps[DIONum] == DIO_NOT_PRESENT) return INPUT;
  dio->bus->Lock(dio->bus,0,SHARED);
  ret =  _DIOGet(dio->dio,~DIONum);
  dio->bus->Unlock(dio->bus,0,SHARED);
  return ret;
}

void PhysicalDIOSetAsync(PhysicalDIO *dio,int DIONum,DIOState State) {
  if (DIONum < 0 || DIONum > dio->NumLocks 
      || dio->Caps[DIONum] == DIO_NOT_PRESENT) return;
  dio->bus->Lock(dio->bus,0,0);
  _DIOSet(dio->dio,DIONum,State);
  dio->bus->Unlock(dio->bus,0,0);
}

DIOState PhysicalDIOGetAsync(PhysicalDIO *dio,int DIONum) {
  DIOState ret;

  //printf("%d:%d:%d\n",DIONum,dio->NumLocks,dio->Caps[DIONum] == DIO_NOT_PRESENT);
  if (DIONum < 0 || DIONum > dio->NumLocks 
      || dio->Caps[DIONum] == DIO_NOT_PRESENT) return INPUT;
  dio->bus->Lock(dio->bus,0,SHARED);
  ret = _DIOGet(dio->dio,DIONum);
  dio->bus->Unlock(dio->bus,0,SHARED);
  return ret;
}

int PhysicalDIOLock(PhysicalDIO *dio,unsigned num,int flags) {
  return 1;
}
int PhysicalDIOUnlock(PhysicalDIO *dio,unsigned num,int flags) {
  return 1;
}
int PhysicalDIOPreempt(PhysicalDIO *dio) {
}

void PhysicalDIOWait(PhysicalDIO *dio,int* match,int min,int max,
		    const int* h,const int* l) {

}

unsigned PhysicalDIOCount(PhysicalDIO *dio) {
  return dio->dio->Count(dio);
}

DIOCaps PhysicalDIOCapabilities(PhysicalDIO *dio,unsigned num) {
  if (num < 0 || num >= dio->NumLocks) return DIO_NOT_PRESENT;
  return dio->Caps[num];
}

int PhysicalDIOGetMulti(PhysicalDIO *dio,char* bits,int offset) {
  int i,n=ArrayLength(bits)*8,j,byte,tmp,max,q;
  max = dio->Count(dio) - offset;

  if (n == 0) {
    tmp = 0;
    q = (max-offset > 32) ? 0 : 32-(max-offset);
    n = (max-offset > 32) ? 32 : max-offset;
    for (i=offset;i<n;i++) {
      tmp = (tmp << 1) + DIOValue(dio->Get(dio,i));
    }
    return tmp << q;
  }
  dio->Refresh(dio);
  for (i=offset,j=0,byte=0;i<n;i++) {
    bits[byte] = (bits[byte] << 1) + DIOValue(dio->Get(dio,i));
    if (i == max) {
      bits[byte] <<= (7-j);
      break;
    }
    if (++j == 8) {
      j = 0;
      byte++;
    }
  }
  return n;
}

// Author: Michael Schmidt (michael@embeddedARM.com)
// Copyright (c) 2012, Technologic Systems, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
#endif
