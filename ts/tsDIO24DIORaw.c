#include "tsDIO24DIORaw.h"

#define I(x) ( Num<0 ? ~(x) : (x))

#define LOCK_TYPE_SHARED_DEFERRED
#define LOCK_CLASS tsDIO24DIORaw
#include "TSLock.h"

// Return 0 and refuse to initialize 
// if board is not detected at specified address
void *tsDIO24DIORawInit(tsDIO24DIORaw *dio,void *bus1,int adrs) {
  tsDIO24DIORaw *ret = dio;
  if (dio->InitStatus > 0) return dio;

  dio->Init = (void *)tsDIO24DIORawInit;
  dio->Fini = (void *)tsDIO24DIORawFini;
  dio->Lock = (void *)tsDIO24DIORawLock;
  dio->Unlock = (void *)tsDIO24DIORawUnlock;
  dio->Preempt = (void *)tsDIO24DIORawPreempt;
  dio->DirSet = (void *)tsDIO24DIORawDirSet;
  dio->DataSet = (void *)tsDIO24DIORawDataSet;
  dio->DirGet = (void *)tsDIO24DIORawDirGet;
  dio->DataGet = (void *)tsDIO24DIORawDataGet;
  dio->Count = (void *)tsDIO24DIORawCount;

  dio->sub = bus1;
  dio->adrs = adrs;
  if (dio->sub->InitStatus <= 0) {
    dio->InitStatus = -1;
    return dio;
  }
  dio->sub->Lock(dio->sub,0,SHARED);
  if (dio->sub->Peek8(dio->sub,adrs) != 0x54) {
    //int i;
    //for (i=0;i<8;i++) {
    //  printf("%X: %X\n",adrs+i,dio->sub->Peek8(dio->sub,adrs+i));
    //}
    dio->InitStatus = 0;
    ret = 0;
  } else {
    //printf("%X found board\n",adrs);
    dio->InitStatus = 1;
  }
  dio->sub->Unlock(dio->sub,0,SHARED);
  return ret;
}

void tsDIO24DIORawFini(tsDIO24DIORaw *dio) {
  dio->sub->Fini(dio->sub);
  if (dio->InitStatus > 0) dio->InitStatus = 0;
}

void tsDIO24DIORawDirSet(tsDIO24DIORaw *dio,int Num,int asOutput) {
  if (I(Num) > 23) return;
  tsDIO24DIORawLockReal(dio,0);
  if (I(Num) < 8) {
    // open drain, so INPUT == HIGH
    if (!asOutput) {
      dio->sub->BitAssign8(dio->sub,dio->adrs+5,I(Num),1);
    }
  } else if (I(Num) < 16) {
    dio->sub->BitAssign8(dio->sub,dio->adrs+4,1,asOutput);
  } else {
    dio->sub->BitAssign8(dio->sub,dio->adrs+4,0,asOutput);
  }
}

void tsDIO24DIORawDataSet(tsDIO24DIORaw *dio,int Num,int asHigh) {
  if (I(Num) > 23) return;
  tsDIO24DIORawLockReal(dio,0);
  if (I(Num) < 8) {
    dio->sub->BitAssign8(dio->sub,dio->adrs+5,I(Num),asHigh);
  } else if (I(Num) < 16) {
    dio->sub->BitAssign8(dio->sub,dio->adrs+6,I(Num)-8,asHigh);
  } else {
    dio->sub->BitAssign8(dio->sub,dio->adrs+7,I(Num)-16,asHigh);
  }
}

int tsDIO24DIORawDirGet(tsDIO24DIORaw *dio,int Num) {
  if (I(Num) > 3 && I(Num) < 8) return 1;
  if (I(Num) > 23) return 0;
  tsDIO24DIORawLockReal(dio,SHARED);
  if (I(Num) < 8) {
    // open drain, so INPUT == LOW
    return dio->sub->BitGet8(dio->sub,dio->adrs+5,I(Num));
  } else if (I(Num) < 16) {
    return dio->sub->BitGet8(dio->sub,dio->adrs+4,1);
  } else {
    return dio->sub->BitGet8(dio->sub,dio->adrs+4,0);
  }
}

int tsDIO24DIORawDataGet(tsDIO24DIORaw *dio,int Num) {
  if (I(Num) > 23) return;
  tsDIO24DIORawLockReal(dio,SHARED);
  if (I(Num) < 8) {
    return dio->sub->BitGet8(dio->sub,dio->adrs+5,I(Num));
  } else if (I(Num) < 16) {
    return dio->sub->BitGet8(dio->sub,dio->adrs+6,I(Num)-8);
  } else {
    return dio->sub->BitGet8(dio->sub,dio->adrs+7,I(Num)-16);
  }
}

unsigned tsDIO24DIORawCount(tsDIO24DIORaw *dio) {
  return 24;
}

// Author: Michael Schmidt (michael@embeddedARM.com)
// Copyright (c) 2012, Technologic Systems, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
