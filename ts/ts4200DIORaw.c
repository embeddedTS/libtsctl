#include "ts4200DIORaw.h"

#define I(x) ( Num<0 ? ~(x) : (x))

#define LOCK_TYPE_SHARED_DEFERRED
#define LOCK_CLASS ts4200DIORaw
#include "TSLock.h"

static DIORawAPI ts4200DIORawAPI = {
  .Init = (void *)ts4200DIORawInit,
  .Fini = (void *)ts4200DIORawFini,
  .Lock = (void *)ts4200DIORawLock,
  .Unlock = (void *)ts4200DIORawUnlock,
  .Preempt = (void *)ts4200DIORawPreempt,
  .DirSet = (void *)ts4200DIORawDirSet,
  .DataSet = (void *)ts4200DIORawDataSet,
  .DirGet = (void *)ts4200DIORawDirGet,
  .DataGet = (void *)ts4200DIORawDataGet,
  .Count = (void *)ts4200DIORawCount
};

void *ts4200DIORawInit(ts4200DIORaw *dio,void *bus1) {
  Bus *bus = bus1;
  if (dio->InitStatus > 0) return dio;

  dio->Init = (void *)ts4200DIORawInit;
  dio->Fini = (void *)ts4200DIORawFini;
  dio->Lock = (void *)ts4200DIORawLock;
  dio->Unlock = (void *)ts4200DIORawUnlock;
  dio->Preempt = (void *)ts4200DIORawPreempt;
  dio->DirSet = (void *)ts4200DIORawDirSet;
  dio->DataSet = (void *)ts4200DIORawDataSet;
  dio->DirGet = (void *)ts4200DIORawDirGet;
  dio->DataGet = (void *)ts4200DIORawDataGet;
  dio->Count = (void *)ts4200DIORawCount;

  ts4200DIORawLockInit(dio);
  dio->sub = bus;
  if (dio->sub->InitStatus <= 0) {
    dio->InitStatus = -1;
    return dio;
  }
  dio->InitStatus = 1;
  return dio;
}

void ts4200DIORawFini(ts4200DIORaw *dio) {
  dio->sub->Fini(dio->sub);
  if (dio->InitStatus > 0) dio->InitStatus = 0;
}

void ts4200DIORawDirSet(ts4200DIORaw *dio,int Num,int asOutput) {
  if (I(Num) >= 32) return;
  ts4200DIORawLockReal(dio,0);
  if (I(Num) < 16) { // FPGA
    dio->sub->BitAssign16(dio->sub,I(4),I(Num)-0,asOutput);
  } else if (I(Num) < 32) {
    dio->sub->BitAssign16(dio->sub,I(0x12),I(Num)-16,asOutput);
  }
}

void ts4200DIORawDataSet(ts4200DIORaw *dio,int Num,int asHigh) {
  if (I(Num) >= 34) return;
  ts4200DIORawLockReal(dio,0);
  if (I(Num) < 16) { // FPGA
    dio->sub->BitAssign16(dio->sub,I(6),I(Num)-0,asHigh);
  } else if (I(Num) < 32) {
    dio->sub->BitAssign16(dio->sub,I(0x14),I(Num)-16,asHigh);
  } else if (I(Num) == 32) {
    dio->sub->BitAssign16(dio->sub,I(2),15,asHigh);
  } else if (I(Num) == 33) {
    dio->sub->BitAssign16(dio->sub,I(2),14,asHigh);
  }
}

int ts4200DIORawDirGet(ts4200DIORaw *dio,int Num) {
  //printf("%d\n",Num);
  if (I(Num) >= 34) return;
  ts4200DIORawLockReal(dio,SHARED);
  if (I(Num) < 16) { // FPGA
    return dio->sub->BitGet16(dio->sub,I(4),I(Num)-0);
  } else if (I(Num) < 32) {
    return dio->sub->BitGet16(dio->sub,I(0x12),I(Num)-16);
  } else if (I(Num) == 32 || I(Num) == 33) {
    return 1;
  }
  return 0;
}

int ts4200DIORawDataGet(ts4200DIORaw *dio,int Num) {
  if (I(Num) >= 34) return;
  ts4200DIORawLockReal(dio,SHARED);
  if (I(Num) < 16) { // FPGA
    return dio->sub->BitGet16(dio->sub,I(8),I(Num)-0);
  } else if (I(Num) < 32) {
    return dio->sub->BitGet16(dio->sub,I(0x16),I(Num)-16);
  } else if (I(Num) == 32) {
    return dio->sub->BitGet16(dio->sub,I(2),15);
  } else if (I(Num) == 33) {
    return dio->sub->BitGet16(dio->sub,I(2),14);
  }
  return 0;
}

unsigned ts4200DIORawCount(ts4200DIORaw *dio) {
  return 34;
}

// Author: Michael Schmidt (michael@embeddedARM.com)
// Copyright (c) 2012, Technologic Systems, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
