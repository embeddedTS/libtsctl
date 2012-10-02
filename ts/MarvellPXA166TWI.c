#include "MarvellPXA166TWI.h"

static TWIAPI MarvellPXA166TWIAPI =  {
  .Init = (void *)MarvellPXA166TWIInit,
  .Fini = (void *)MarvellPXA166TWIFini,
  .Lock = (void *)MarvellPXA166TWILock,
  .Write = (void *)MarvellPXA166TWIWrite,
  .Read = (void *)MarvellPXA166TWIRead,
};

void *MarvellPXA166TWIInit(MarvellPXA166TWI *twi,void *bus1) {
  Bus *bus = bus1;

  if (twi->InitStatus > 0) return twi;

  twi->Init = (void *)MarvellPXA166TWIInit;
  twi->Fini = (void *)MarvellPXA166TWIFini;
  twi->Lock = (void *)MarvellPXA166TWILock;
  twi->Write = (void *)MarvellPXA166TWIWrite;
  twi->Read = (void *)MarvellPXA166TWIRead;

  twi->bus = bus;

  if (twi->bus->InitStatus <= 0) {
    twi->Fini(twi);
    twi->InitStatus = -1;
    return twi;
  }

  //twi->dio->SetAsync(twi->dio,twi->TW_CLK,INPUT); // SCL=1
  //twi->dio->SetAsync(twi->dio,twi->TW_DAT,INPUT); // SDA=1
  //usleep(10000); // ample time for them to become stable
  twi->InitStatus = 1;
  return twi;
}

void MarvellPXA166TWIFini(MarvellPXA166TWI *twi){
  twi->bus->Fini(twi->bus);
  if (twi->InitStatus > 0) twi->InitStatus = 0;
}

int MarvellPXA166TWIWrite(MarvellPXA166TWI *twi,int devadrs,int adrslen,int adrs,const char* bytes){
  return 1;
}

int MarvellPXA166TWIRead(MarvellPXA166TWI *twi,int devadrs,int adrslen,int adrs,char* bytes){
  return 1;
}

int MarvellPXA166TWILock(MarvellPXA166TWI *twi,int command,unsigned num) {
  int ret;

  switch (command) {
  case WaitLock:
  case TryLock:
    if ((ret=lock->Lock(lock,command,twi->LockNum)) < 0) return ret;
    /*
    if ((ret=twi->dio->Lock(twi->dio,command,twi->TW_CLK)) < 0) {
      command = DoRelease;
      goto DoRelease2;
    }
    if ((ret=twi->dio->Lock(twi->dio,command,twi->TW_DAT)) < 0) {
      command = DoRelease;
      goto DoRelease1;
    }
    */
    return 1;
  case DoRelease:
    /*
    ret = 1;
    twi->dio->Lock(twi->dio,command,twi->TW_DAT);
  DoRelease1:
    twi->dio->Lock(twi->dio,command,twi->TW_CLK);
  DoRelease2:
    */
    lock->Lock(lock,command,twi->LockNum); // TWI mutex
    return ret;
  case DoPreempt:
    MarvellPXA166TWILock(twi,DoRelease,num);
    sched_yield();
    return MarvellPXA166TWILock(twi,WaitLock,num);
  }
  return 0;
}


// Author: Michael Schmidt (michael@embeddedARM.com)
// Copyright (c) 2011, Technologic Systems, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
