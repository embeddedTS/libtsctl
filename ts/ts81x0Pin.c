#include "ts81x0Pin.h"
#include "Bus.h"

#define LOCK_TYPE_SHARED
#define LOCK_CLASS ts81x0Pin
#include "TSLock.h"

void *ts81x0PinInit(ts81x0Pin *pin,void *parent,void *bus) {
  if (pin->InitStatus > 0) return pin;

  pin->Init = (void *)ts81x0PinInit;
  pin->Fini = (void *)ts81x0PinFini;
  pin->Lock = (void *)ts81x0PinLock;
  pin->Unlock = (void *)ts81x0PinUnlock;
  pin->Preempt = (void *)ts81x0PinPreempt;
  pin->ModeGet = (void *)ts81x0PinModeGet;
  pin->ModeSet = (void *)ts81x0PinModeSet;

  pin->parent = parent;
  pin->bus = bus;
  pin->CAN_TX1 = -1;
  pin->CAN_TX2 = -1;
  pin->CAN_RX1 = -1;
  pin->CAN_RX2 = -1;
  pin->InitStatus = 1;
  return pin;
}

void ts81x0PinPostInit(void *pin0,int CAN_TX1,int CAN_TX2,int CAN_RX1,int CAN_RX2) {
  ts81x0Pin *pin = pin0;
  pin->CAN_TX1 = CAN_TX1;
  pin->CAN_TX2 = CAN_TX2;
  pin->CAN_RX1 = CAN_RX1;
  pin->CAN_RX2 = CAN_RX2;
}

void ts81x0PinFini(ts81x0Pin *pin) { 
  if (pin->InitStatus > 0) pin->InitStatus = 0;
}

PinMode ts81x0PinModeGet(ts81x0Pin *pin,int npin) {
  int ret;

  if (npin == pin->CAN_TX1 || npin == pin->CAN_RX1) {
    pin->bus->Lock(pin->bus,0,SHARED);
    ret = pin->bus->BitGet16(pin->bus,2,13);
    pin->bus->Unlock(pin->bus,0,SHARED);
    if (!ret) {
      return MODE_CAN;
    } else return MODE_DIO;
  }
  if (npin == pin->CAN_TX2 || npin == pin->CAN_RX2) {
    pin->bus->Lock(pin->bus,0,SHARED);
    ret = pin->bus->BitGet16(pin->bus,2,14);
    pin->bus->Unlock(pin->bus,0,SHARED);
    if (!ret) {
      return MODE_CAN;
    } else return MODE_DIO;
  }
  return pin->parent->ModeGet(pin->parent,npin);
}

PinResult ts81x0PinModeSet(ts81x0Pin *pin,int npin,PinMode mode) {
  //log9(LOG_CAN,"npin=%d, pin->CAN_TX1=%d mode!=MODE_CAN=%d\n",npin,pin->CAN_TX1,
  //       mode != MODE_CAN);
  if (npin == pin->CAN_TX1 || npin == pin->CAN_RX1) {
    pin->bus->Lock(pin->bus,0,0);
    pin->bus->BitAssign16(pin->bus,2,13,mode != MODE_CAN);
    pin->bus->Unlock(pin->bus,0,0);
  }
  if (npin == pin->CAN_TX2 || npin == pin->CAN_RX2) {
    pin->bus->Lock(pin->bus,0,0);
    pin->bus->BitAssign16(pin->bus,2,14,mode != MODE_CAN);
    pin->bus->Unlock(pin->bus,0,0);
  }
  return pin->parent->ModeSet(pin->parent,npin,mode);
}
// Author: Michael Schmidt (michael@embeddedTS.com)
// Copyright (c) 2012-2022 Technologic Systems, Inc. dba embeddedTS, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
