#include "ts8900Pin.h"
#include "Bus.h"

//#define LOCK_TYPE_SHARED
//#define LOCK_CLASS ts8900Pin
//#include "TSLock.h"

static PinAPI ts8900PinAPI = {
  .Init = (void *)ts8900PinInit,
  .Fini = (void *)ts8900PinFini,
  //  .Lock = (void *)ts8900PinLock,
  //  .Unlock = (void *)ts8900PinUnlock,
  //  .Preempt = (void *)ts8900PinPreempt,
  .ModeGet = (void *)ts8900PinModeGet,
  .ModeSet = (void *)ts8900PinModeSet
};

void *ts8900PinInit(ts8900Pin *pin,void *parent,void *bus,int start) {
  if (pin->InitStatus > 0) return pin;
  /*
  ArchInfo *cur = ts8900_ArchInfo.parent;
  int i;

  pin->start = 0;
  while (cur) {
    for (i=0;i<cur->Instances[CLASS_DIORaw];i++) {
      DIORaw *raw = cur->DIORawInit(0,i);
      pin->start += raw->Count(raw);
    }
    cur = cur->parent;
  }
  */
  pin->LockBase = ((Pin *)parent)->LockBase;
  pin->Init = (void *)ts8900PinInit;
  pin->Fini = (void *)ts8900PinFini;
  pin->Lock = ((Pin *)parent)->Lock;
  pin->Unlock = ((Pin *)parent)->Unlock;
  pin->Preempt = ((Pin *)parent)->Preempt;
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

int ts8900PinModeSet(ts8900Pin *pin,int npin,PinMode mode) {
  int ret;

  npin -= pin->start;
  //fprintf(stderr,"ModeSet:%d,%s\n",npin,mode==MODE_BUS?"Bus":mode==MODE_DIO?"DIO":"?");
  if (npin >= 16 && npin <= 31) {
    pin->bus->Lock(pin->bus,0,0);
    if (mode == MODE_DIO) {
      pin->bus->BitSet16(pin->bus,0x08,npin-16);
      ret=1;
    } else if (mode == MODE_BUS) {
      pin->bus->BitClear16(pin->bus,0x08,npin-16);
      ret=1;
    } else {
      ret=-1;
    }
    pin->bus->Unlock(pin->bus,0,0);
    return ret;
  } else if (npin == 32) {
    pin->bus->Lock(pin->bus,0,0);
    if (mode == MODE_DIO) {
      pin->bus->BitSet16(pin->bus,0x0A,8);
      ret=1;
    } else if (mode == MODE_BUS) {
      pin->bus->BitClear16(pin->bus,0x0A,8);
      ret=1;
    } else {
      ret=-1;
    }
    pin->bus->Unlock(pin->bus,0,0);
    return ret;
  } else if (npin >= 33 && npin <= 41) {
    pin->bus->Lock(pin->bus,0,0);
    if (mode == MODE_DIO) {
      pin->bus->BitSet16(pin->bus,0x0A,npin-33);
      ret=1;
    } else if (mode == MODE_BUS) {
      pin->bus->BitClear16(pin->bus,0x0A,npin-33);
      ret=1;
    } else {
      ret=-1;
    }
    pin->bus->Unlock(pin->bus,0,0);
    return ret;
  }
  npin += pin->start;
  return pin->parent->ModeSet(pin->parent,npin,mode);
}
// Author: Michael Schmidt (michael@embeddedARM.com)
// Copyright (c) 2012, Technologic Systems, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
