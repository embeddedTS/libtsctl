#include "ts8820DIORaw.h"

#define I(x) ( Num<0 ? ~(x) : (x))

#define LOCK_TYPE_SHARED_DEFERRED
#define LOCK_CLASS ts8820DIORaw
#include "TSLock.h"

static DIORawAPI ts8820DIORawAPI = {
  .Init = (void *)ts8820DIORawInit,
  .Fini = (void *)ts8820DIORawFini,
  .Lock = (void *)ts8820DIORawLock,
  .Unlock = (void *)ts8820DIORawUnlock,
  .Preempt = (void *)ts8820DIORawPreempt,
  .DirSet = (void *)ts8820DIORawDirSet,
  .DataSet = (void *)ts8820DIORawDataSet,
  .DirGet = (void *)ts8820DIORawDirGet,
  .DataGet = (void *)ts8820DIORawDataGet,
  .Count = (void *)ts8820DIORawCount
};

void *ts8820DIORawInit(ts8820DIORaw *dio,void *bus1) {
  if (dio->InitStatus > 0) return dio;

  dio->Init = (void *)ts8820DIORawInit;
  dio->Fini = (void *)ts8820DIORawFini;
  dio->Lock = (void *)ts8820DIORawLock;
  dio->Unlock = (void *)ts8820DIORawUnlock;
  dio->Preempt = (void *)ts8820DIORawPreempt;
  dio->DirSet = (void *)ts8820DIORawDirSet;
  dio->DataSet = (void *)ts8820DIORawDataSet;
  dio->DirGet = (void *)ts8820DIORawDirGet;
  dio->DataGet = (void *)ts8820DIORawDataGet;
  dio->Count = (void *)ts8820DIORawCount;

  dio->sub = bus1;
  if (dio->sub->InitStatus <= 0) {
    dio->InitStatus = -1;
  }
  dio->InitStatus = 1;
  return dio;
}

void ts8820DIORawFini(ts8820DIORaw *dio) {
  dio->sub->Fini(dio->sub);
  if (dio->InitStatus > 0) dio->InitStatus = 0;
}

// DIO 0-13 = digital inputs
// DIO 14-19 = digital outputs
// DIO 20-21 = H-bridges
void ts8820DIORawDirSet(ts8820DIORaw *dio,int Num,int asOutput) {
  if (I(Num) == 20 || I(Num) == 21) {
    ts8820DIORawLockReal(dio,0);
    dio->sub->BitAssign16(dio->sub,2,I(Num)-19+6,asOutput);
  }
  return;
}

void ts8820DIORawDataSet(ts8820DIORaw *dio,int Num,int asHigh) {
  if (I(Num) > 21 || I(Num) < 14) return;
  ts8820DIORawLockReal(dio,0);
  if (I(Num) == 20 || I(Num) == 21) {
    dio->sub->BitAssign16(dio->sub,0x2,I(Num)-19+4,asHigh);
  } else {
    dio->sub->BitAssign16(dio->sub,0x8,I(Num)-14,asHigh);
  }
}

int ts8820DIORawDirGet(ts8820DIORaw *dio,int Num) {
  if (I(Num) > 21 || I(Num) < 14) return 0;
  if (I(Num) == 20 || I(Num) == 21) {
    ts8820DIORawLockReal(dio,0);
    return dio->sub->BitGet16(dio->sub,2,I(Num)-19+6);
  }
  return 1;
}

int ts8820DIORawDataGet(ts8820DIORaw *dio,int Num) {
  if (I(Num) > 21) return 0;
  ts8820DIORawLockReal(dio,SHARED);
  if (I(Num) > 19) {
    return dio->sub->BitGet16(dio->sub,2,I(Num)-19+4);
  }
  if (I(Num) > 13) {
    // we don't have a register bit which tells us the true input value
    // so just return whatever is currently supposed to be output
    return dio->sub->BitGet16(dio->sub,0x8,I(Num)-14);
  }
  return dio->sub->BitGet16(dio->sub,0x4,I(Num));
}

unsigned ts8820DIORawCount(ts8820DIORaw *dio) {
  return 22;
}

// Author: Michael Schmidt (michael@embeddedARM.com)
// Copyright (c) 2012, Technologic Systems, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
