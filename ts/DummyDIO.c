#ifndef __DummyDIO_h
#define __DummyDIO_h
#include "DummyDIO.h"

/*
  DIO that does nothing but take up a fixed number of DIOs.
  This is for architectures which support a variable number of
  devices - for instances, the TS-RELAY8.  We allocate this class
  to fill in spots where there could be a device, but isn't, so that
  our DIO numbers will always remain constant for any DIO classes
  instantiated after us.
 */
static DIOAPI DummyDIOAPI = {
  .Init = (void *)DummyDIOInit,
  .Fini = (void *)DummyDIOFini,
  .Lock = (void *)DummyDIOLock,
  .Unlock = (void *)DummyDIOUnlock,
  .Preempt = (void *)DummyDIOPreempt,
  .Refresh = (void *)DummyDIORefresh,
  .Commit = (void *)DummyDIOCommit,
  .Set = (void *)DummyDIOSet,
  .Get = (void *)DummyDIOGet,
  .SetAsync = (void *)DummyDIOSetAsync,
  .GetAsync = (void *)DummyDIOGetAsync,
  .Count = (void *)DummyDIOCount,
  .Capabilities = (void *)DummyDIOCapabilities
};

void *DummyDIOInit(DummyDIO *dio,int count) {
  if (dio->InitStatus > 0) return dio;

  dio->Init = (void *)DummyDIOInit;
  dio->Fini = (void *)DummyDIOFini;
  dio->Lock = (void *)DummyDIOLock;
  dio->Unlock = (void *)DummyDIOUnlock;
  dio->Preempt = (void *)DummyDIOPreempt;
  dio->Refresh = (void *)DummyDIORefresh;
  dio->Commit = (void *)DummyDIOCommit;
  dio->Set = (void *)DummyDIOSet;
  dio->Get = (void *)DummyDIOGet;
  dio->SetAsync = (void *)DummyDIOSetAsync;
  dio->GetAsync = (void *)DummyDIOGetAsync;
  dio->Count = (void *)DummyDIOCount;
  dio->Capabilities = (void *)DummyDIOCapabilities;
  dio->GetMulti = (void *)DummyDIOGetMulti;

  dio->NumLocks = count;
  dio->InitStatus = 1;
  return dio;
}

void DummyDIOFini(DummyDIO *dio) {
  if (dio->InitStatus > 0) dio->InitStatus = 0;
}

void DummyDIORefresh(DummyDIO *dio) {
}

void DummyDIOCommit(DummyDIO *dio,int forceall) {
}

void DummyDIOSet(DummyDIO *dio,int DIONum,DIOState State) {
}

DIOState DummyDIOGet(DummyDIO *dio,int DIONum) {
  return INPUT;
}

void DummyDIOSetAsync(DummyDIO *dio,int DIONum,DIOState State) {
}

DIOState DummyDIOGetAsync(DummyDIO *dio,int DIONum) {
  return INPUT;
}

int DummyDIOLock(DummyDIO *dio,unsigned num,int flags) {
  return 1;
}
int DummyDIOUnlock(DummyDIO *dio,unsigned num,int flags) {
  return 1;
}
void DummyDIOPreempt(DummyDIO *dio) {
}

void DummyDIOWait(DummyDIO *dio,int* match,int min,int max,
		    int* h,int* l) {
  ArraySizeAuto(match,0);
}

unsigned DummyDIOCount(DummyDIO *dio) {
  return dio->NumLocks;
}

DIOCaps DummyDIOCapabilities(DummyDIO *dio,unsigned num) {
  return DIO_NOT_PRESENT;
}

int DummyDIOGetMulti(DummyDIO *dio,char* bits,int offset) {
  return 0;
}

#endif

// Author: Michael Schmidt (michael@embeddedARM.com)
// Copyright (c) 2012, Technologic Systems, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
