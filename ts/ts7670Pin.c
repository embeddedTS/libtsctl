#include "ts7670Pin.h"
#include "Bus.h"
#include "Thread.h"

unsigned DIOCount();

#define LOCK_TYPE_SHARED
#define LOCK_CLASS ts7670Pin
#include "TSLock.h"

void *ts7670PinInit(ts7670Pin *pin,void *sub0) {
  Bus *sub=sub0;

  if (pin->InitStatus > 0) return pin;
  pin->LockBase = ThreadLockAllocate(DIOCount());

  pin->Init = (void *)ts7670PinInit;
  pin->Fini = (void *)ts7670PinFini;
  pin->Lock = (void *)ts7670PinLock;
  pin->Unlock = (void *)ts7670PinUnlock;
  pin->Preempt = (void *)ts7670PinPreempt;
  pin->ModeGet = (void *)ts7670PinModeGet;
  pin->ModeSet = (void *)ts7670PinModeSet;

  pin->sub = sub;
  if (pin->sub->InitStatus < 0) {
    pin->Fini(pin);
    pin->InitStatus = -1;
    return pin;
  }
  pin->InitStatus = 1;
  return pin;
}

void ts7670PinFini(ts7670Pin *pin) { 
  pin->sub->Fini(pin->sub);
  if (pin->InitStatus > 0) pin->InitStatus = 0;
}

/* TO DO:
BANK0_PIN23 01=CAN, 10=ADC
BANK0_PIN22 01=CAN
BANK0_PIN19 01=CAN
BANK0_PIN18 01=CAN
 */
PinMode ts7670PinModeGet(ts7670Pin *ob,int npin) {
  int bank = npin >> 5, pin = (npin & 31), subbank;
  subbank = (pin > 15) ? 1 : 0;
  if (pin > 15) {
    pin -= 16;
  }
  int mode = ob->sub->BitsGet32(ob->sub,0x100+0x20*bank+0x10*subbank+4,pin*2+1,pin*2);
  if (mode == 3) return MODE_DIO;
  return MODE_UNKNOWN;
}

PinResult ts7670PinModeSet(ts7670Pin *ob,int npin,PinMode mode) {
  if (npin < 0 || npin >= 160) return PinErrorModeInvalid;
  if (mode != MODE_DIO) return PinErrorModeInvalid;

  int bank = npin >> 5, pin = (npin & 31), subbank;
  subbank = (pin > 15) ? 1 : 0;
  if (pin > 15) {
    pin -= 16;
  }
  ob->sub->Assign32X(ob->sub,0x100+0x20*bank+0x10*subbank+4,pin*2+1,pin*2,3);
  return PinSuccess;
}
// Author: Michael Schmidt (michael@embeddedTS.com)
// Copyright (c) 2012-2022 Technologic Systems, Inc. dba embeddedTS, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
