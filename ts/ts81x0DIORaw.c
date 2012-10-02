#include "ts81x0DIORaw.h"

#define I(x) ( Num<0 ? ~(x) : (x))

#define LOCK_TYPE_SHARED_DEFERRED
#define LOCK_CLASS ts81x0DIORaw
#include "TSLock.h"

static DIORawAPI ts81x0DIORawAPI = {
  .Init = (void *)ts81x0DIORawInit,
  .Fini = (void *)ts81x0DIORawFini,
  .Lock = (void *)ts81x0DIORawLock,
  .Unlock = (void *)ts81x0DIORawUnlock,
  .Preempt = (void *)ts81x0DIORawPreempt,
  .DirSet = (void *)ts81x0DIORawDirSet,
  .DataSet = (void *)ts81x0DIORawDataSet,
  .DirGet = (void *)ts81x0DIORawDirGet,
  .DataGet = (void *)ts81x0DIORawDataGet,
  .Count = (void *)ts81x0DIORawCount
};

void *ts81x0DIORawInit(ts81x0DIORaw *dio,void *bus1) {
  if (dio->InitStatus > 0) return dio;

  dio->Init = (void *)ts81x0DIORawInit;
  dio->Fini = (void *)ts81x0DIORawFini;
  dio->Lock = (void *)ts81x0DIORawLock;
  dio->Unlock = (void *)ts81x0DIORawUnlock;
  dio->Preempt = (void *)ts81x0DIORawPreempt;
  dio->DirSet = (void *)ts81x0DIORawDirSet;
  dio->DataSet = (void *)ts81x0DIORawDataSet;
  dio->DirGet = (void *)ts81x0DIORawDirGet;
  dio->DataGet = (void *)ts81x0DIORawDataGet;
  dio->Count = (void *)ts81x0DIORawCount;

  dio->sub = bus1;
  if (dio->sub->InitStatus <= 0) {
    dio->InitStatus = -1;
  }
  dio->InitStatus = 1;
  return dio;
}

void ts81x0DIORawFini(ts81x0DIORaw *dio) {
  dio->sub->Fini(dio->sub);
  if (dio->InitStatus > 0) dio->InitStatus = 0;
}

// DIO 0-7 = DIO header pins 1,3,5,..., 15
// DIO 8-13 = PC/104 pins A16 ... A21
// DIO 14-15 = PC/104 pins B11, B12
// DIO 16-23 = LCD pins 7-14 (data lines)
// DIO 24 = LCD WR (pin 6)
// DIO 25 = LCD RS (pin 3)
// DIO 26 = LCD EN (pin 5)
// DIO 27-31 = reserved
void ts81x0DIORawDirSet(ts81x0DIORaw *dio,int Num,int asOutput) {
  if (I(Num) > 26) return;
  ts81x0DIORawLockReal(dio,0);
  if (I(Num) >= 16) {
    dio->sub->BitAssign16(dio->sub,0xA,I(Num)-16,asOutput);
  } else {
    dio->sub->BitAssign16(dio->sub,0x8,I(Num),asOutput);
  }
}

void ts81x0DIORawDataSet(ts81x0DIORaw *dio,int Num,int asHigh) {
  if (I(Num) > 26) return;
  ts81x0DIORawLockReal(dio,0);
  if (I(Num) >= 16) {
    dio->sub->BitAssign16(dio->sub,0x6,I(Num)-16,asHigh);
  } else {
    dio->sub->BitAssign16(dio->sub,0x4,I(Num),asHigh);
  }
}

int ts81x0DIORawDirGet(ts81x0DIORaw *dio,int Num) {
  if (I(Num) > 26) return 0;
  ts81x0DIORawLockReal(dio,SHARED);
  if (I(Num) >= 16) {
    return dio->sub->BitGet16(dio->sub,0xA,I(Num)-16);
  } else {
    return dio->sub->BitGet16(dio->sub,0x8,I(Num));
  }
}

int ts81x0DIORawDataGet(ts81x0DIORaw *dio,int Num) {
  if (I(Num) > 26) return 0;
  ts81x0DIORawLockReal(dio,SHARED);
  if (I(Num) >= 16) {
    return dio->sub->BitGet16(dio->sub,0xE,I(Num)-16);
  } else {
    return dio->sub->BitGet16(dio->sub,0xC,I(Num));
  }
}

unsigned ts81x0DIORawCount(ts81x0DIORaw *dio) {
  return 32;
}

// Author: Michael Schmidt (michael@embeddedARM.com)
// Copyright (c) 2012, Technologic Systems, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
