#include "ts8820Pin.h"
#include "Bus.h"

#define LOCK_TYPE_SHARED
#define LOCK_CLASS ts8820Pin
#include "TSLock.h"

void *ts8820PinInit(ts8820Pin *pin,void *parent,void *bus,int start) {
  if (pin->InitStatus > 0) return pin;

  pin->Init = (void *)ts8820PinInit;
  pin->Fini = (void *)ts8820PinFini;
  pin->Lock = (void *)ts8820PinLock;
  pin->Unlock = (void *)ts8820PinUnlock;
  pin->Preempt = (void *)ts8820PinPreempt;
  pin->ModeGet = (void *)ts8820PinModeGet;
  pin->ModeSet = (void *)ts8820PinModeSet;

  pin->parent = parent;
  pin->bus = bus;
  pin->InitStatus = 1;
  pin->start = start;
  return pin;
}

void ts8820PinFini(ts8820Pin *pin) { 
  if (pin->InitStatus > 0) pin->InitStatus = 0;
}

PinMode ts8820PinModeGet(ts8820Pin *pin,int npin) {
  int npin0;

  npin0 = npin - pin->start;
  if (npin0 >= 0 && npin0 < 14) {
    return MODE_DIO;
  }
  if (npin0 >= 14 && npin0 <= 19) {
    return pin->bus->BitGet16(pin->bus,8,6+(npin0-14)) ? MODE_PWM : MODE_DIO;
  }
  if (npin == 20 || npin == 21) {
    // TO DO: fall back to DIO mode for 0% or 100% duty cycle
    return MODE_PWM;
  }
  return pin->parent->ModeGet(pin->parent,npin);
}

PinResult ts8820PinModeSet(ts8820Pin *pin,int npin,PinMode mode) {
  int npin0;

  npin0 = npin - pin->start;
  if (npin0 >= 0 && npin0 < 14) {
    return (mode == MODE_DIO) ? PinSuccess :  PinErrorModeInvalid;
  }
  if (npin0 >= 14 && npin0 <= 19) {
    if (mode == MODE_DIO) {
      pin->bus->BitClear16(pin->bus,8,6+(npin0-14));
      return PinSuccess;
    } else if (mode == MODE_PWM) {
      pin->bus->BitSet16(pin->bus,8,6+(npin0-14));
      return PinSuccess;
    } else return PinErrorModeInvalid;
  }
  if (npin0 == 20 || npin0 == 21) {
    if (mode == MODE_DIO) {
      return PinErrorModeInvalid;
    } else if (mode == MODE_PWM) {
      pin->bus->BitSet16(pin->bus,2,6+npin0-20);
      return PinSuccess;
    }
    // TO DO: fall back to DIO mode for 0% or 100% duty cycle
    return PinErrorModeInvalid;
  }
  return pin->parent->ModeSet(pin->parent,npin,mode);
}
// Author: Michael Schmidt (michael@embeddedARM.com)
// Copyright (c) 2012, Technologic Systems, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
