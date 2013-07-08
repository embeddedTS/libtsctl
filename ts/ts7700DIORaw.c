#ifndef ts7700DIORaw_c
#define ts7700DIORaw_c
#include "ts7700DIORaw.h"

#define I(x) ( Num<0 ? ~(x) : (x))

#define LOCK_TYPE_SHARED_DEFERRED
#define LOCK_CLASS ts7700DIORaw
#include "TSLock.h"

void *ts7700DIORawInit(ts7700DIORaw *dio,void *bus1) {
  Bus *bus = bus1;

  if (dio->InitStatus > 0) return dio;

  dio->Init = (void *)ts7700DIORawInit;
  dio->Fini = (void *)ts7700DIORawFini;
  dio->Lock = (void *)ts7700DIORawLock;
  dio->Unlock = (void *)ts7700DIORawUnlock;
  dio->Preempt = (void *)ts7700DIORawPreempt;
  dio->DirSet = (void *)ts7700DIORawDirSet;
  dio->DataSet = (void *)ts7700DIORawDataSet;
  dio->DirGet = (void *)ts7700DIORawDirGet;
  dio->DataGet = (void *)ts7700DIORawDataGet;
  dio->Count = (void *)ts7700DIORawCount;

  ts7700DIORawLockInit(dio);
  dio->sub = bus;
  if (dio->sub->InitStatus <= 0) {
    dio->InitStatus = -1;
    return dio;
  }
  dio->InitStatus = 1;
  return dio;
}

void ts7700DIORawFini(ts7700DIORaw *dio) {
  dio->sub->Fini(dio->sub);
  if (dio->InitStatus > 0) dio->InitStatus = 0;
}

/*
  DIO 0-54 = data
  DIO 64-118 = dir-64
 */

void ts7700DIORawDirSet(ts7700DIORaw *dio,int Num,int asOutput) {
  if (I(Num) > 54) return;
  ts7700DIORawLockReal(dio,0);
  dio->sub->Poke16(dio->sub,0x10,(asOutput?0x80:0)+I(Num)+64);
}

void ts7700DIORawDataSet(ts7700DIORaw *dio,int Num,int asHigh) {
  if (I(Num) > 54) return;
  ts7700DIORawLockReal(dio,0);
  dio->sub->Poke16(dio->sub,0x10,(asHigh?0x80:0)+I(Num));
}

int ts7700DIORawDirGet(ts7700DIORaw *dio,int Num) {
  if (I(Num) > 54) return 0;
  return 1; // yech. we have no way of reading back direction bits...
}

int ts7700DIORawDataGet(ts7700DIORaw *dio,int Num) {
  if (I(Num) > 54) return 0;
  ts7700DIORawLockReal(dio,SHARED);
  /*
0x20: DIO group 1 DIO[14:0] input data (bits 14-0)            
0x22: DIO group 2 DIO[26:22] DIO[20:15] input data (bits 10-0)
0x24: DIO group 3 DIO[42:27] input data (bits 15-0)           
0x26: DIO group 4 DIO[59:48] input data (bits 11-0)           
   */
  if (I(Num) <= 14) {
    return dio->sub->BitGet16(dio->sub,I(0x20),I(Num));
  } else if (I(Num) <= 20) {
    return dio->sub->BitGet16(dio->sub,I(0x22),I(Num)-15);
  } else if (I(Num) <= 26) {
    return dio->sub->BitGet16(dio->sub,I(0x22),I(Num)-22+6);
  } else if (I(Num) <= 42) {
    return dio->sub->BitGet16(dio->sub,I(0x24),I(Num)-27);
  } else if (I(Num) <= 59) {
    return dio->sub->BitGet16(dio->sub,I(0x26),I(Num)-48);
  }
}

unsigned ts7700DIORawCount(ts7700DIORaw *dio) {
  return 55;
}

// Author: Michael Schmidt (michael@embeddedARM.com)
// Copyright (c) 2013, Technologic Systems, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.

#endif

