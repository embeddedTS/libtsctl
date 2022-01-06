#include "ts4500DIORaw.h"

// Not sure why we need this, as we don't have negative DIOs.
// Get rid of it here and in the other DIORaw module(s)!
#define I(x) ( Num<0 ? ~(x) : (x))

#define LOCK_TYPE_SHARED_DEFERRED
#define LOCK_CLASS ts4500DIORaw
#include "TSLock.h"

void *ts4500DIORawInit(ts4500DIORaw *dio,void *bus1) {
  Bus *bus = bus1;

  if (dio->InitStatus > 0) return dio;

  dio->Init = (void *)ts4500DIORawInit;
  dio->Fini = (void *)ts4500DIORawFini;
  dio->Lock = (void *)ts4500DIORawLock;
  dio->Unlock = (void *)ts4500DIORawUnlock;
  dio->Preempt = (void *)ts4500DIORawPreempt;
  dio->DirSet = (void *)ts4500DIORawDirSet;
  dio->DataSet = (void *)ts4500DIORawDataSet;
  dio->DirGet = (void *)ts4500DIORawDirGet;
  dio->DataGet = (void *)ts4500DIORawDataGet;
  dio->Count = (void *)ts4500DIORawCount;

  ts4500DIORawLockInit(dio);
  dio->sub = bus;
  if (dio->sub->InitStatus <= 0) {
    dio->InitStatus = -1;
    return dio;
  }
  dio->InitStatus = 1;
  return dio;
}

void ts4500DIORawFini(ts4500DIORaw *dio) {
  dio->sub->Fini(dio->sub);
  if (dio->InitStatus > 0) dio->InitStatus = 0;
}

void ts4500DIORawDirSet(ts4500DIORaw *dio,int Num,int asOutput) {
  if (I(Num) > 52) return;
  ts4500DIORawLockReal(dio,0);
  if (I(Num) > 48) dio->sub->BitAssign16(dio->sub,I(0x7E),I(Num)-49,asOutput);
  else if (I(Num) > 40) dio->sub->BitAssign16(dio->sub,I(0x7A),I(Num)-41,asOutput);
  else if (I(Num) > 36) dio->sub->BitAssign16(dio->sub,I(0x66),I(Num)-37+4,asOutput);
  else if (I(Num) > 20) dio->sub->BitAssign16(dio->sub,I(0x6C),I(Num)-21,asOutput);
  else if (I(Num) > 4) dio->sub->BitAssign16(dio->sub,I(0x72),I(Num)-5,asOutput);
  else /*if (I(Num) >= 0)*/ dio->sub->BitAssign16(dio->sub,I(0x78),I(Num),asOutput);
}

void ts4500DIORawDataSet(ts4500DIORaw *dio,int Num,int asHigh) {
  if (I(Num) > 52 && I(Num) != 54 && I(Num) != 55) return;
  ts4500DIORawLockReal(dio,0);
  if (I(Num)==55) dio->sub->BitAssign16(dio->sub,I(0x62),14,asHigh);
  else if (I(Num)==54) dio->sub->BitAssign16(dio->sub,I(0x62),15,asHigh);
  else if (I(Num) > 48) dio->sub->BitAssign16(dio->sub,I(0x7E),I(Num)-49+4,asHigh);
  else if (I(Num) > 40) dio->sub->BitAssign16(dio->sub,I(0x7A),I(Num)-41+8,asHigh);
  else if (I(Num) > 36) dio->sub->BitAssign16(dio->sub,I(0x66),I(Num)-37+8,asHigh);
  else if (I(Num) > 20) dio->sub->BitAssign16(dio->sub,I(0x6A),I(Num)-21,asHigh);
  else if (I(Num) > 4) dio->sub->BitAssign16(dio->sub,I(0x70),I(Num)-5,asHigh);
  else /*if (I(Num) >= 0)*/ dio->sub->BitAssign16(dio->sub,I(0x78),I(Num)+5,asHigh);
}

int ts4500DIORawDirGet(ts4500DIORaw *dio,int Num) {
  if (I(Num) == 54) return 1;
  if (I(Num) == 55) return 1;
  if (I(Num) > 52) return 0;
  ts4500DIORawLockReal(dio,SHARED);
  if (I(Num) > 48) return dio->sub->BitGet16(dio->sub,I(0x7E),I(Num)-49);
  else if (I(Num) > 40) return dio->sub->BitGet16(dio->sub,I(0x7A),I(Num)-41);
  else if (I(Num) > 36) return dio->sub->BitGet16(dio->sub,I(0x66),I(Num)-37+4);
  else if (I(Num) > 20) return dio->sub->BitGet16(dio->sub,I(0x6C),I(Num)-21);
  else if (I(Num) > 4) return dio->sub->BitGet16(dio->sub,I(0x72),I(Num)-5);
  else /*if (I(Num) >= 0)*/ return dio->sub->BitGet16(dio->sub,I(0x78),I(Num));
}

int ts4500DIORawDataGet(ts4500DIORaw *dio,int Num) {
  if (I(Num) > 52 && I(Num) != 54 && I(Num) != 55) return 0;
  ts4500DIORawLockReal(dio,SHARED);
  if (I(Num) == 55) return dio->sub->BitGet16(dio->sub,I(0x62),14);
  else if (I(Num) == 54) return dio->sub->BitGet16(dio->sub,I(0x62),15);
  else if (I(Num) > 40) return dio->sub->BitGet16(dio->sub,I(0x7C),I(Num)-41);
  else if (I(Num) > 36) return dio->sub->BitGet16(dio->sub,I(0x66),I(Num)-37+12);
  else if (I(Num) > 20) return dio->sub->BitGet16(dio->sub,I(0x68),I(Num)-21);
  else if (I(Num) > 4) return dio->sub->BitGet16(dio->sub,I(0x6E),I(Num)-5);
  else /*if (I(Num) >= 0)*/ return dio->sub->BitGet16(dio->sub,I(0x78),I(Num)+10);
}

unsigned ts4500DIORawCount(ts4500DIORaw *dio) {
  return 56;
}

// Author: Michael Schmidt (michael@embeddedTS.com)
// Copyright (c) 2012-2022 Technologic Systems, Inc. dba embeddedTS, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
