#include "ts8900DIORaw.h"

#define I(x) ( Num<0 ? ~(x) : (x))

#define LOCK_TYPE_SHARED_DEFERRED
#define LOCK_CLASS ts8900DIORaw
#include "TSLock.h"

void *ts8900DIORawInit(ts8900DIORaw *dio,void *bus1) {
  if (dio->InitStatus > 0) return dio;

  dio->Init = (void *)ts8900DIORawInit;
  dio->Fini = (void *)ts8900DIORawFini;
  dio->Lock = (void *)ts8900DIORawLock;
  dio->Unlock = (void *)ts8900DIORawUnlock;
  dio->Preempt = (void *)ts8900DIORawPreempt;
  dio->DirSet = (void *)ts8900DIORawDirSet;
  dio->DataSet = (void *)ts8900DIORawDataSet;
  dio->DirGet = (void *)ts8900DIORawDirGet;
  dio->DataGet = (void *)ts8900DIORawDataGet;
  dio->Count = (void *)ts8900DIORawCount;

  dio->sub = bus1;
  if (dio->sub->InitStatus <= 0) {
    dio->InitStatus = -1;
  }
  dio->InitStatus = 1;
  return dio;
}

void ts8900DIORawFini(ts8900DIORaw *dio) {
  dio->sub->Fini(dio->sub);
  if (dio->InitStatus > 0) dio->InitStatus = 0;
}

// DIO  0-7=digital inputs
// DIO 8-15=digital outputs
// DIO 16-32=PC104 pins
// DIO 33-41=ISA pins
void ts8900DIORawDirSet(ts8900DIORaw *dio,int Num,int asOutput) {
  if (I(Num) > 41) return;
  ts8900DIORawLockReal(dio,0);
  if (I(Num) >= 16 && I(Num) <= 31) {
    dio->sub->BitAssign16(dio->sub,0x10,I(Num)-16,asOutput);
  } else if (I(Num) == 32) {
    dio->sub->BitAssign16(dio->sub,0x12,8,asOutput);
  } else if (I(Num) >= 33 && I(Num) <= 41) {
    dio->sub->BitAssign16(dio->sub,0x12,I(Num)-33,asOutput);
  } 
}

void ts8900DIORawDataSet(ts8900DIORaw *dio,int Num,int asHigh) {
  if (I(Num) > 41) return;
  ts8900DIORawLockReal(dio,0);
  if (I(Num) >= 8 && I(Num) <= 15) {
    dio->sub->BitAssign16(dio->sub,0x04,15-(I(Num)-8),asHigh);
  } else if (I(Num) >= 16 && I(Num) <= 31) {
    dio->sub->BitAssign16(dio->sub,0x0C,I(Num)-16,asHigh);
  } else if (I(Num) == 32) {
    dio->sub->BitAssign16(dio->sub,0x0E,8,asHigh);
  } else if (I(Num) >= 33 && I(Num) <= 41) {
    dio->sub->BitAssign16(dio->sub,0x0E,I(Num)-33,asHigh);
  }
}

int ts8900DIORawDirGet(ts8900DIORaw *dio,int Num) {
  if (I(Num) > 41) return 0;
  ts8900DIORawLockReal(dio,SHARED);
  if (I(Num) >= 0 && I(Num) <= 7) {
    return 0;
  } else if (I(Num) >= 8 && I(Num) <= 15) {
    return 1;
  } else if (I(Num) >= 16 && I(Num) <= 31) {
    return dio->sub->BitGet16(dio->sub,0x10,I(Num)-16);
  } else if (I(Num) == 32) {
    return dio->sub->BitGet16(dio->sub,0x12,8);
  } else if (I(Num) >= 33 && I(Num) <= 41) {
    return dio->sub->BitGet16(dio->sub,0x12,I(Num)-33);
  } 
  return 0;
}

int ts8900DIORawDataGet(ts8900DIORaw *dio,int Num) {
  if (I(Num) > 41) return 0;
  ts8900DIORawLockReal(dio,SHARED);
  if (I(Num) >= 0 && I(Num) <= 7) {
    return dio->sub->BitGet16(dio->sub,0x02,I(Num)+8);
  } else if (I(Num) >= 8 && I(Num) <= 15) {
    return dio->sub->BitGet16(dio->sub,0x04,15-(I(Num)-8));
  } else if (I(Num) >= 16 && I(Num) <= 31) {
    return dio->sub->BitGet16(dio->sub,0x14,I(Num)-16);
  } else if (I(Num) == 32) {
    return dio->sub->BitGet16(dio->sub,0x16,8);
  } else if (I(Num) >= 33 && I(Num) <= 41) {
    return dio->sub->BitGet16(dio->sub,0x16,I(Num)-33);
  }
}

unsigned ts8900DIORawCount(ts8900DIORaw *dio) {
  return 42;
}

// Author: Michael Schmidt (michael@embeddedARM.com)
// Copyright (c) 2012, Technologic Systems, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
