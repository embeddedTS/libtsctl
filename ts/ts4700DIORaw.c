#ifndef ts4700DIORaw_c
#define ts4700DIORaw_c
#include "ts4700DIORaw.h"

// Not sure why we need this, as we don't have negative DIOs.
// Get rid of it here and in the other DIORaw module(s)!
#define I(x) ( Num<0 ? ~(x) : (x))

#define LOCK_TYPE_SHARED_DEFERRED
#define LOCK_CLASS ts4700DIORaw
#include "TSLock.h"

static DIORawAPI ts4700DIORawAPI = {
  .Init = (void *)ts4700DIORawInit,
  .Fini = (void *)ts4700DIORawFini,
  .Lock = (void *)ts4700DIORawLock,
  .Unlock = (void *)ts4700DIORawUnlock,
  .Preempt = (void *)ts4700DIORawPreempt,
  .DirSet = (void *)ts4700DIORawDirSet,
  .DataSet = (void *)ts4700DIORawDataSet,
  .DirGet = (void *)ts4700DIORawDirGet,
  .DataGet = (void *)ts4700DIORawDataGet,
  .Count = (void *)ts4700DIORawCount
};

void *ts4700DIORawInit(ts4700DIORaw *dio,void *bus1) {
  Bus *bus = bus1;

  if (dio->InitStatus > 0) return dio;

  dio->Init = (void *)ts4700DIORawInit;
  dio->Fini = (void *)ts4700DIORawFini;
  dio->Lock = (void *)ts4700DIORawLock;
  dio->Unlock = (void *)ts4700DIORawUnlock;
  dio->Preempt = (void *)ts4700DIORawPreempt;
  dio->DirSet = (void *)ts4700DIORawDirSet;
  dio->DataSet = (void *)ts4700DIORawDataSet;
  dio->DirGet = (void *)ts4700DIORawDirGet;
  dio->DataGet = (void *)ts4700DIORawDataGet;
  dio->Count = (void *)ts4700DIORawCount;

  ts4700DIORawLockInit(dio);
  dio->sub = bus;
  if (dio->sub->InitStatus <= 0) {
    dio->InitStatus = -1;
    return dio;
  }
  dio->InitStatus = 1;
  return dio;
}

void ts4700DIORawFini(ts4700DIORaw *dio) {
  dio->sub->Fini(dio->sub);
  if (dio->InitStatus > 0) dio->InitStatus = 0;
}

void ts4700DIORawDirSet(ts4700DIORaw *dio,int Num,int asOutput) {
  if (I(Num) > 59) return;
  ts4700DIORawLockReal(dio,0);
  if (I(Num) <= 14) {
    dio->sub->BitAssign16(dio->sub,I(0x18),I(Num),asOutput);
  } else if (I(Num) <= 20) {
    dio->sub->BitAssign16(dio->sub,I(0x1A),I(Num)-15,asOutput);
  } else if (I(Num) <= 26) {
    dio->sub->BitAssign16(dio->sub,I(0x1A),I(Num)-22+6,asOutput);
  } else if (I(Num) <= 42) {
    dio->sub->BitAssign16(dio->sub,I(0x1C),I(Num)-27,asOutput);
  } else if (I(Num) <= 59) {
    dio->sub->BitAssign16(dio->sub,I(0x1E),I(Num)-48,asOutput);
  }
}

void ts4700DIORawDataSet(ts4700DIORaw *dio,int Num,int asHigh) {
  if (I(Num) > 61) return;
  ts4700DIORawLockReal(dio,0);
  if (I(Num) <= 14) {
    dio->sub->BitAssign16(dio->sub,I(0x10),I(Num),asHigh);
  } else if (I(Num) <= 20) {
    dio->sub->BitAssign16(dio->sub,I(0x12),I(Num)-15,asHigh);
  } else if (I(Num) <= 26) {
    dio->sub->BitAssign16(dio->sub,I(0x12),I(Num)-22+6,asHigh);
  } else if (I(Num) <= 42) {
    dio->sub->BitAssign16(dio->sub,I(0x14),I(Num)-27,asHigh);
  } else if (I(Num) <= 59) {
    dio->sub->BitAssign16(dio->sub,I(0x16),I(Num)-48,asHigh);
  } else { // I(Num) <= 61
    dio->sub->BitAssign16(dio->sub,I(0x12),I(Num)-60+11,asHigh);
  }
}

int ts4700DIORawDirGet(ts4700DIORaw *dio,int Num) {
  if (I(Num) > 61) return 0;
  if (I(Num) == 60 || I(Num) == 61) return 1;
  ts4700DIORawLockReal(dio,SHARED);
  if (I(Num) <= 14) {
    return dio->sub->BitGet16(dio->sub,I(0x18),I(Num));
  } else if (I(Num) <= 20) {
    return dio->sub->BitGet16(dio->sub,I(0x1A),I(Num)-15);
  } else if (I(Num) <= 26) {
    return dio->sub->BitGet16(dio->sub,I(0x1A),I(Num)-22+6);
  } else if (I(Num) <= 42) {
    return dio->sub->BitGet16(dio->sub,I(0x1C),I(Num)-27);
  } else if (I(Num) <= 59) {
    return dio->sub->BitGet16(dio->sub,I(0x1E),I(Num)-48);
  }
}

int ts4700DIORawDataGet(ts4700DIORaw *dio,int Num) {
  if (I(Num) > 61) return 0;
  ts4700DIORawLockReal(dio,SHARED);
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
  } else { // I(Num) <= 61
    return dio->sub->BitGet16(dio->sub,I(0x22),I(Num)-60+11);
  }
}

unsigned ts4700DIORawCount(ts4700DIORaw *dio) {
  return 62;
}

// Author: Michael Schmidt (michael@embeddedARM.com)
// Copyright (c) 2011, Technologic Systems, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.

//-----------------------------------------------------------------------------
/*
* group 1: 0-14
* group 2: 15-20, 22-26
* group 3: 27-42
* group 4: 48-59

* 0x10: DIO group 1 output data (bits 14-0)
* 0x12: DIO group 2 output data (bits 10-0) 11: Green LED. 12: Red LED.
* 0x14: DIO group 3 output data (bits 15-0)
* 0x16: DIO group 4 output data (bits 11-0)
* 0x18: DIO group 1 data direction (bits 14-0)
* 0x1a: DIO group 2 data direction (bits 10-0)
* 0x1c: DIO group 3 data direction (bits 15-0)
* 0x1e: DIO group 4 data direction (bits 11-0)
* 0x20: DIO group 1 input data (bits 14-0)
* 0x22: DIO group 2 input data (bits 10-0)
* 0x24: DIO group 3 input data (bits 15-0)
* 0x26: DIO group 4 input data (bits 11-0)
 */
#endif

