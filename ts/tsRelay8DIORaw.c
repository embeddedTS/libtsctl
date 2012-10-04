#include "tsRelay8DIORaw.h"

#define I(x) ( Num<0 ? ~(x) : (x))

#define LOCK_TYPE_SHARED_DEFERRED
#define LOCK_CLASS tsRelay8DIORaw
#include "TSLock.h"

// Return 0 and refuse to initialize 
// if board is not detected at specified address
void *tsRelay8DIORawInit(tsRelay8DIORaw *dio,void *bus1,int adrs) {
  tsRelay8DIORaw *ret = dio;
  if (dio->InitStatus > 0) return dio;

  dio->Init = (void *)tsRelay8DIORawInit;
  dio->Fini = (void *)tsRelay8DIORawFini;
  dio->Lock = (void *)tsRelay8DIORawLock;
  dio->Unlock = (void *)tsRelay8DIORawUnlock;
  dio->Preempt = (void *)tsRelay8DIORawPreempt;
  dio->DirSet = (void *)tsRelay8DIORawDirSet;
  dio->DataSet = (void *)tsRelay8DIORawDataSet;
  dio->DirGet = (void *)tsRelay8DIORawDirGet;
  dio->DataGet = (void *)tsRelay8DIORawDataGet;
  dio->Count = (void *)tsRelay8DIORawCount;

  dio->sub = bus1;
  dio->adrs = adrs;
  if (dio->sub->InitStatus <= 0) {
    dio->InitStatus = -1;
    return dio;
  }
  dio->sub->Lock(dio->sub,0,SHARED);
  if (dio->sub->Peek8(dio->sub,adrs) != 0x9B) {
    dio->InitStatus = 0;
    ret = 0;
  } else {
    dio->InitStatus = 1;
  }
  dio->sub->Unlock(dio->sub,0,SHARED);
  return ret;
}

void tsRelay8DIORawFini(tsRelay8DIORaw *dio) {
  dio->sub->Fini(dio->sub);
  if (dio->InitStatus > 0) dio->InitStatus = 0;
}

void tsRelay8DIORawDirSet(tsRelay8DIORaw *dio,int Num,int asOutput) {
  return; // always output
}

void tsRelay8DIORawDataSet(tsRelay8DIORaw *dio,int Num,int asHigh) {
  if (I(Num) >= 8) return;
  tsRelay8DIORawLockReal(dio,0);
  dio->sub->BitAssign8(dio->sub,dio->adrs+2,I(Num),asHigh);
}

int tsRelay8DIORawDirGet(tsRelay8DIORaw *dio,int Num) {
  return 1; // always output
}

int tsRelay8DIORawDataGet(tsRelay8DIORaw *dio,int Num) {
  if (I(Num) >= 8) return;
  tsRelay8DIORawLockReal(dio,SHARED);
  return dio->sub->BitGet8(dio->sub,dio->adrs+2,I(Num));
}

unsigned tsRelay8DIORawCount(tsRelay8DIORaw *dio) {
  return 8;
}

// Author: Michael Schmidt (michael@embeddedARM.com)
// Copyright (c) 2012, Technologic Systems, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
