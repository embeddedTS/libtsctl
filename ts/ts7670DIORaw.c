#include "ts7670DIORaw.h"

// Not sure why we need this, as we don't have negative DIOs.
// Get rid of it here and in the other DIORaw module(s)!
#define I(x) ( Num<0 ? ~(x) : (x))

#define LOCK_TYPE_SHARED_DEFERRED
#define LOCK_CLASS ts7670DIORaw
#include "TSLock.h"

void *ts7670DIORawInit(ts7670DIORaw *dio,void *bus1) {
  Bus *bus = bus1;

  if (dio->InitStatus > 0) return dio;

  dio->Init = (void *)ts7670DIORawInit;
  dio->Fini = (void *)ts7670DIORawFini;
  dio->Lock = (void *)ts7670DIORawLock;
  dio->Unlock = (void *)ts7670DIORawUnlock;
  dio->Preempt = (void *)ts7670DIORawPreempt;
  dio->DirSet = (void *)ts7670DIORawDirSet;
  dio->DataSet = (void *)ts7670DIORawDataSet;
  dio->DirGet = (void *)ts7670DIORawDirGet;
  dio->DataGet = (void *)ts7670DIORawDataGet;
  dio->Count = (void *)ts7670DIORawCount;

  ts7670DIORawLockInit(dio);
  dio->sub = bus;
  if (dio->sub->InitStatus <= 0) {
    dio->InitStatus = -1;
    return dio;
  }
  dio->InitStatus = 1;
  return dio;
}

void ts7670DIORawFini(ts7670DIORaw *dio) {
  dio->sub->Fini(dio->sub);
  if (dio->InitStatus > 0) dio->InitStatus = 0;
}

void ts7670DIORawDirSet(ts7670DIORaw *dio,int Num,int asOutput) {
  if (I(Num) > 160) return;
  int bank = Num >> 5, pin = (Num & 31);
  ts7670DIORawLockReal(dio,0);
  dio->sub->Poke32(dio->sub,0xB00+0x10*bank+(asOutput?4:8),1<<pin);

  // offset = [unsigned index]
  // 0xB04 = [705]
  // 0xB08 = [706]
  // 0xB14 = [709]
  // 0xB18 = [710]
  // 0xB24 = [713]
  // 0xB28 = [714]
  // 0xB34 = [717]
  // 0xB38 = [718]
  // 0xB44 = [721]
  // 0xB48 = [722]
}


void ts7670DIORawDataSet(ts7670DIORaw *dio,int Num,int asHigh) {
  if (I(Num) > 160) return;
  int bank = Num >> 5, pin = (Num & 31);
  ts7670DIORawLockReal(dio,0);
  dio->sub->Poke32(dio->sub,0x700+0x10*bank+(asHigh?4:8),1<<pin);
  // 0x704 = [449]
  // 0x708 = [450]
  // 0x714 = [453]
  // 0x718 = [454]
  // 0x724 = [457]
  // 0x728 = [458]
  // 0x734 = [461]
  // 0x738 = [462]
  // 0x744 = [465]
  // 0x748 = [466]
}

int ts7670DIORawDirGet(ts7670DIORaw *dio,int Num) {
  if (I(Num) > 160) return;
  int bank = Num >> 5, pin = (Num & 31);
  ts7670DIORawLockReal(dio,0);
  return dio->sub->BitGet32(dio->sub,0xB00+0x10*bank,pin);

  // B00 = [704]
  // B10 = [708]
  // B20 = [712]
  // B30 = [716]
  // B40 = [720]
}

int ts7670DIORawDataGet(ts7670DIORaw *dio,int Num) {
  if (I(Num) > 160) return;
  int bank = Num >> 5, pin = (Num & 31);
  ts7670DIORawLockReal(dio,0);
  return dio->sub->BitGet32(dio->sub,0x900+0x10*bank,pin);
  // 900 = [576]
  // 910 = [580]
  // 920 = [584]
  // 930 = [588]
  // 940 = [592]
}

unsigned ts7670DIORawCount(ts7670DIORaw *dio) {
  return 160; // 5*32
}

// Author: Michael Schmidt (michael@embeddedARM.com)
// Copyright (c) 2013, Technologic Systems, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
