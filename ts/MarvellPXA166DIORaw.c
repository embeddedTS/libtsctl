#ifndef MarvellPXA166DIORaw_c
#define MarvellPXA166DIORaw_c
#include "MarvellPXA166DIORaw.h"

// Not sure why we need this, as we don't have negative DIOs.
// Get rid of it here and in the other DIORaw module(s)!
#define I(x) ( Num<0 ? ~(x) : (x))

#define LOCK_TYPE_SHARED_DEFERRED
#define LOCK_CLASS MarvellPXA166DIORaw
#include "TSLock.h"

void *MarvellPXA166DIORawInit(MarvellPXA166DIORaw *dio,void *bus1) {
  Bus *bus = bus1;

  if (dio->InitStatus > 0) return dio;

  dio->Init = (void *)MarvellPXA166DIORawInit;
  dio->Fini = (void *)MarvellPXA166DIORawFini;
  dio->Lock = (void *)MarvellPXA166DIORawLock;
  dio->Unlock = (void *)MarvellPXA166DIORawUnlock;
  dio->Preempt = (void *)MarvellPXA166DIORawPreempt;
  dio->DirSet = (void *)MarvellPXA166DIORawDirSet;
  dio->DataSet = (void *)MarvellPXA166DIORawDataSet;
  dio->DirGet = (void *)MarvellPXA166DIORawDirGet;
  dio->DataGet = (void *)MarvellPXA166DIORawDataGet;
  dio->Count = (void *)MarvellPXA166DIORawCount;

  MarvellPXA166DIORawLockInit(dio);
  dio->sub = bus;
  if (dio->sub->InitStatus <= 0) {
    dio->InitStatus = -1;
    return dio;
  }
  dio->InitStatus = 1;
  return dio;
}

void MarvellPXA166DIORawFini(MarvellPXA166DIORaw *dio) {
  dio->sub->Fini(dio->sub);
  if (dio->InitStatus > 0) dio->InitStatus = 0;
}

void MarvellPXA166DIORawDirSet(MarvellPXA166DIORaw *dio,int Num,int asOutput) {
  if (I(Num) > 122) return;
  MarvellPXA166DIORawLockReal(dio,0);
  if (I(Num) < 32) {
    dio->sub->BitAssign32(dio->sub,I(0x0C),I(Num),asOutput);
  } else if (I(Num) <= 64) {
    dio->sub->BitAssign32(dio->sub,I(0x10),I(Num)-32,asOutput);
  } else if (I(Num) <= 96) {
    dio->sub->BitAssign32(dio->sub,I(0x14),I(Num)-64,asOutput);
  } else {
    dio->sub->BitAssign32(dio->sub,I(0x10C),I(Num)-96,asOutput);
  }
}

void MarvellPXA166DIORawDataSet(MarvellPXA166DIORaw *dio,int Num,int asHigh) {
  if (I(Num) > 122) return;
  MarvellPXA166DIORawLockReal(dio,0);
  if (asHigh) {
    if (I(Num) < 32) {
      return dio->sub->Poke32(dio->sub,I(0x18),(1<<I(Num)));
    } else if (I(Num) <= 64) {
      return dio->sub->Poke32(dio->sub,I(0x1C),(1<<(I(Num)-32)));
    } else if (I(Num) <= 96) {
      return dio->sub->Poke32(dio->sub,I(0x20),(1<<(I(Num)-64)));
    } else {
      return dio->sub->Poke32(dio->sub,I(0x118),(1<<(I(Num)-96)));
    }
  } else {
    if (I(Num) < 32) {
      return dio->sub->Poke32(dio->sub,I(0x24),(1<<I(Num)));
    } else if (I(Num) <= 64) {
      return dio->sub->Poke32(dio->sub,I(0x28),(1<<(I(Num)-32)));
    } else if (I(Num) <= 96) {
      return dio->sub->Poke32(dio->sub,I(0x2C),(1<<(I(Num)-64)));
    } else {
      return dio->sub->Poke32(dio->sub,I(0x124),(1<<(I(Num)-96)));
    }
  }
}

int MarvellPXA166DIORawDirGet(MarvellPXA166DIORaw *dio,int Num) {
  if (I(Num) > 122) return 0;
  if (I(Num) == 60 || I(Num) == 61) return 1;
  MarvellPXA166DIORawLockReal(dio,SHARED);
  if (I(Num) < 32) {
    return dio->sub->BitGet32(dio->sub,I(0x0C),I(Num));
  } else if (I(Num) <= 64) {
    return dio->sub->BitGet32(dio->sub,I(0x10),I(Num)-32);
  } else if (I(Num) <= 96) {
    return dio->sub->BitGet32(dio->sub,I(0x14),I(Num)-64);
  } else {
    return dio->sub->BitGet32(dio->sub,I(0x10C),I(Num)-96);
  }
}

int MarvellPXA166DIORawDataGet(MarvellPXA166DIORaw *dio,int Num) {
  if (I(Num) > 122) return 0;
  MarvellPXA166DIORawLockReal(dio,SHARED);
  if (I(Num) < 32) {
    return dio->sub->BitGet32(dio->sub,I(0x00),I(Num));
  } else if (I(Num) <= 64) {
    return dio->sub->BitGet32(dio->sub,I(0x04),I(Num)-32);
  } else if (I(Num) <= 96) {
    return dio->sub->BitGet32(dio->sub,I(0x08),I(Num)-64);
  } else {
    return dio->sub->BitGet32(dio->sub,I(0x100),I(Num)-96);
  }
}

unsigned MarvellPXA166DIORawCount(MarvellPXA166DIORaw *dio) {
  return 128;
}

// Author: Michael Schmidt (michael@embeddedTS.com)
// Copyright (c) 2011-2022 Technologic Systems, Inc. dba embeddedTS, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.

/*
  GPLR = data read
  GPDR = dir read/write
  GSDR/GCDR = dir write
  GPSR/GPCR = data write

  reg   hex offset
  GPLR0 000
  GPLR1 004
  GPLR2 008
  GPLR3 100

  GPDR0 00C
  GPDR1 010
  GPDR2 014
  GPDR3 10C

  GPSR0 018
  GPSR1 01C
  GPSR2 020
  GPSR3 118
  GPCR0 024
  GPCR1 028
  GPCR2 02C
  GPCR3 124
 */
#endif
