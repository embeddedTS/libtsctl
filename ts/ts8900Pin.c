#include "ts8900Pin.h"
#include "Bus.h"
#include "Lock.h"

//#define LOCK_TYPE_SHARED
//#define LOCK_CLASS ts8900Pin
//#include "TSLock.h"

void *ts8900PinInit(ts8900Pin *pin,void *parent,void *bus,int start) {
  if (pin->InitStatus > 0) return pin;

  pin->LockBase = ((Pin *)parent)->LockBase;
  pin->Init = (void *)ts8900PinInit;
  pin->Fini = (void *)ts8900PinFini;
  pin->Lock = ((ts8900Pin *)parent)->Lock;
  pin->Unlock = ((ts8900Pin *)parent)->Unlock;
  pin->Preempt = ((ts8900Pin *)parent)->Preempt;
  //pin->Lock = (void *)ts8900PinLock;
  //pin->Unlock = (void *)ts8900PinUnlock;
  //pin->Preempt = (void *)ts8900PinPreempt;
  pin->ModeGet = (void *)ts8900PinModeGet;
  pin->ModeSet = (void *)ts8900PinModeSet;

  pin->parent = parent;
  pin->bus = bus;
  pin->InitStatus = 1;
  pin->start = start;
  return pin;
}

void ts8900PinFini(ts8900Pin *pin) { 
  if (pin->InitStatus > 0) pin->InitStatus = 0;
}

PinMode ts8900PinModeGet(ts8900Pin *pin,int npin) {
  int ret;

  npin -= pin->start;
  if (npin >= 16 && npin <= 31) {
    pin->bus->Lock(pin->bus,0,SHARED);
    ret=pin->bus->BitGet16(pin->bus,0x08,npin-16) ? MODE_DIO:MODE_BUS;
    pin->bus->Unlock(pin->bus,0,SHARED);
    return ret;
  } else if (npin == 32) {
    pin->bus->Lock(pin->bus,0,SHARED);
    ret=pin->bus->BitGet16(pin->bus,0x0A,8) ? MODE_DIO:MODE_BUS;
    pin->bus->Unlock(pin->bus,0,SHARED);
    return ret;
  } else if (npin >= 33 && npin <= 41) {
    pin->bus->Lock(pin->bus,0,SHARED);
    ret=pin->bus->BitGet16(pin->bus,0x0A,npin-33) ? MODE_DIO:MODE_BUS;
    pin->bus->Unlock(pin->bus,0,SHARED);
    return ret;
  }
  npin += pin->start;
  return pin->parent->ModeGet(pin->parent,npin);
}

PinResult ts8900PinModeSet(ts8900Pin *pin,int npin,PinMode mode) {
  int ret;

  npin -= pin->start;
  //fprintf(stderr,"ModeSet:%d,%s\n",npin,mode==MODE_BUS?"Bus":mode==MODE_DIO?"DIO":"?");
  if (npin >= 16 && npin <= 31) {
    pin->bus->Lock(pin->bus,0,0);
    if (mode == MODE_DIO) {
      pin->bus->BitSet16(pin->bus,0x08,npin-16);
      ret=PinSuccess;
    } else if (mode == MODE_BUS) {
      pin->bus->BitClear16(pin->bus,0x08,npin-16);
      ret=PinSuccess;
    } else {
      ret=PinErrorModeInvalid;
    }
    pin->bus->Unlock(pin->bus,0,0);
    return ret;
  } else if (npin == 32) {
    pin->bus->Lock(pin->bus,0,0);
    if (mode == MODE_DIO) {
      pin->bus->BitSet16(pin->bus,0x0A,8);
      ret=PinSuccess;
    } else if (mode == MODE_BUS) {
      pin->bus->BitClear16(pin->bus,0x0A,8);
      ret=PinSuccess;
    } else {
      ret=PinErrorModeInvalid;
    }
    pin->bus->Unlock(pin->bus,0,0);
    return ret;
  } else if (npin >= 33 && npin <= 41) {
    pin->bus->Lock(pin->bus,0,0);
    if (mode == MODE_DIO) {
      pin->bus->BitSet16(pin->bus,0x0A,npin-33);
      ret=PinSuccess;
    } else if (mode == MODE_BUS) {
      pin->bus->BitClear16(pin->bus,0x0A,npin-33);
      ret=PinSuccess;
    } else {
      ret=PinErrorModeInvalid;
    }
    pin->bus->Unlock(pin->bus,0,0);
    return ret;
  }
  npin += pin->start;
  return pin->parent->ModeSet(pin->parent,npin,mode);
}
// Author: Michael Schmidt (michael@embeddedTS.com)
// Copyright (c) 2012-2022 Technologic Systems, Inc. dba embeddedTS, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
