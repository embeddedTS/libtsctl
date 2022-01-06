#include "Cavium2132DIORaw.h"
#define LOCK_NOW -1

#define I(x) ( Num<0 ? ~(x) : (x))

#define LOCK_TYPE_SHARED_DEFERRED
#define LOCK_CLASS Cavium2132DIORaw
#include "TSLock.h"

void *Cavium2132DIORawInit(Cavium2132DIORaw *dio,void *bus1) {
  Bus *bus = bus1;

  if (dio->InitStatus > 0) return dio;

  dio->Init = (void *)Cavium2132DIORawInit;
  dio->Fini = (void *)Cavium2132DIORawFini;
  dio->Lock = (void *)Cavium2132DIORawLock;
  dio->Unlock = (void *)Cavium2132DIORawUnlock;
  dio->Preempt = (void *)Cavium2132DIORawPreempt;
  dio->DirSet = (void *)Cavium2132DIORawDirSet;
  dio->DataSet = (void *)Cavium2132DIORawDataSet;
  dio->DirGet = (void *)Cavium2132DIORawDirGet;
  dio->DataGet = (void *)Cavium2132DIORawDataGet;
  dio->Count = (void *)Cavium2132DIORawCount;

  Cavium2132DIORawLockInit(dio);
  dio->sub = bus;
  if (dio->sub->InitStatus <= 0) {
    dio->InitStatus = -1;
    return dio;
  }
  dio->InitStatus = 1;
  return dio;
}

void Cavium2132DIORawFini(Cavium2132DIORaw *dio) {
  dio->sub->Fini(dio->sub);
  if (dio->InitStatus > 0) dio->InitStatus = 0;
}

void Cavium2132DIORawDirSet(Cavium2132DIORaw *dio,int Num,int asOutput) {
  if (I(Num) > 31) return;
  Cavium2132DIORawLockReal(dio,0);
  dio->sub->BitAssign32(dio->sub,I(0x08),I(Num),asOutput);
}

void Cavium2132DIORawDataSet(Cavium2132DIORaw *dio,int Num,int asHigh) {
  if (I(Num) > 31) return;
  Cavium2132DIORawLockReal(dio,0);
  dio->sub->BitAssign32(dio->sub,I(0x00),I(Num),asHigh);
}

int Cavium2132DIORawDirGet(Cavium2132DIORaw *dio,int Num) {
  if (I(Num) > 31) return;
  Cavium2132DIORawLockReal(dio,SHARED);
  return dio->sub->BitGet32(dio->sub,I(0x08),I(Num));
}

int Cavium2132DIORawDataGet(Cavium2132DIORaw *dio,int Num) {
  if (I(Num) > 31) return;
  Cavium2132DIORawLockReal(dio,SHARED);
  return dio->sub->BitGet32(dio->sub,I(0x04),I(Num));
}

unsigned Cavium2132DIORawCount(Cavium2132DIORaw *dio) {
  return 32;
}

// Author: Michael Schmidt (michael@embeddedTS.com)
// Copyright (c) 2011-2022 Technologic Systems, Inc. dba embeddedTS, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
