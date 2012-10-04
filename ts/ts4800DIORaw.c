#ifndef ts4800DIORaw_c
#define ts4800DIORaw_c
#include "ts4800DIORaw.h"

// Not sure why we need this, as we don't have negative DIOs.
// Get rid of it here and in the other DIORaw module(s)!
#define I(x) ( Num<0 ? ~(x) : (x))

#define LOCK_TYPE_SHARED_DEFERRED
#define LOCK_CLASS ts4800DIORaw
#include "TSLock.h"

void *ts4800DIORawInit(ts4800DIORaw *dio,void *bus1) {
  Bus *bus = bus1;

  if (dio->InitStatus > 0) return dio;

  dio->Init = (void *)ts4800DIORawInit;
  dio->Fini = (void *)ts4800DIORawFini;
  dio->Lock = (void *)ts4800DIORawLock;
  dio->Unlock = (void *)ts4800DIORawUnlock;
  dio->Preempt = (void *)ts4800DIORawPreempt;
  dio->DirSet = (void *)ts4800DIORawDirSet;
  dio->DataSet = (void *)ts4800DIORawDataSet;
  dio->DirGet = (void *)ts4800DIORawDirGet;
  dio->DataGet = (void *)ts4800DIORawDataGet;
  dio->Count = (void *)ts4800DIORawCount;

  ts4800DIORawLockInit(dio);
  dio->sub = bus;
  if (dio->sub->InitStatus <= 0) {
    dio->InitStatus = -1;
    return dio;
  }
  dio->InitStatus = 1;
  return dio;
}

void ts4800DIORawFini(ts4800DIORaw *dio) {
  dio->sub->Fini(dio->sub);
  if (dio->InitStatus > 0) dio->InitStatus = 0;
}

unsigned ts4800DIORawCount(ts4800DIORaw *dio) {
  return 66;
}

void ts4800DIORawDirSet(ts4800DIORaw *dio,int Num,int asOutput) {
  ts4800DIORawLockReal(dio,0);
  if (I(Num) < 16) {
    dio->sub->BitAssign16(dio->sub,I(0x24),I(Num),asOutput);
  } else if (I(Num) < 32) {
    dio->sub->BitAssign16(dio->sub,I(0x2C),I(Num)-16,asOutput);
  } else if (I(Num) < 48) {
    dio->sub->BitAssign16(dio->sub,I(0x34),I(Num)-32,asOutput);
  } else if (I(Num) < 64) {
    dio->sub->BitAssign16(dio->sub,I(0x3C),I(Num)-48,asOutput);
  } else { 
  }
}

void ts4800DIORawDataSet(ts4800DIORaw *dio,int Num,int asHigh) {
  ts4800DIORawLockReal(dio,0);
  if (I(Num) < 16) {
    dio->sub->BitAssign16(dio->sub,I(0x22),I(Num),asHigh);
  } else if (I(Num) < 32) {
    dio->sub->BitAssign16(dio->sub,I(0x2A),I(Num)-16,asHigh);
  } else if (I(Num) < 48) {
    dio->sub->BitAssign16(dio->sub,I(0x32),I(Num)-32,asHigh);
  } else if (I(Num) < 64) {
    dio->sub->BitAssign16(dio->sub,I(0x3A),I(Num)-48,asHigh);
  } else {
    dio->sub->BitAssign16(dio->sub,I(0x10),15-(I(Num)-64),asHigh);
  }
}

int ts4800DIORawDirGet(ts4800DIORaw *dio,int Num) {
  ts4800DIORawLockReal(dio,SHARED);
  if (I(Num) < 16) {
    return dio->sub->BitGet16(dio->sub,I(0x24),I(Num));
  } else if (I(Num) < 32) {
    return dio->sub->BitGet16(dio->sub,I(0x2C),I(Num)-16);
  } else if (I(Num) < 48) {
    return dio->sub->BitGet16(dio->sub,I(0x34),I(Num)-32);
  } else if (I(Num) < 64) {
    return dio->sub->BitGet16(dio->sub,I(0x3C),I(Num)-48);
  } else { 
    return 1;
  }
}

int ts4800DIORawDataGet(ts4800DIORaw *dio,int Num) {
  ts4800DIORawLockReal(dio,SHARED);
  if (I(Num) < 16) {
    return dio->sub->BitGet16(dio->sub,I(0x20),I(Num));
  } else if (I(Num) < 32) {
    return dio->sub->BitGet16(dio->sub,I(0x28),I(Num)-16);
  } else if (I(Num) < 48) {
    return dio->sub->BitGet16(dio->sub,I(0x30),I(Num)-32);
  } else if (I(Num) < 64) {
    return dio->sub->BitGet16(dio->sub,I(0x38),I(Num)-48);
  } else {
    return dio->sub->BitGet16(dio->sub,I(0x10),15-(I(Num)-64));
  }
}

// Author: Michael Schmidt (michael@embeddedARM.com)
// Copyright (c) 2012, Technologic Systems, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
#endif
