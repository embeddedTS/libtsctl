#ifndef ts4200Pin_c
#define ts4200Pin_c
#include "ts4200Pin.h"
#include "Bus.h"
#include "Thread.h"
#include "Log.h"

unsigned DIOCount();

#define LOCK_TYPE_SHARED
#define LOCK_CLASS ts4200Pin
#include "TSLock.h"

static PinAPI ts4200PinAPI = {
  .Init = (void *)ts4200PinInit,
  .Fini = (void *)ts4200PinFini,
  .Lock = (void *)ts4200PinLock,
  .Unlock = (void *)ts4200PinUnlock,
  .Preempt = (void *)ts4200PinPreempt,
  .ModeGet = (void *)ts4200PinModeGet,
  .ModeSet = (void *)ts4200PinModeSet
};

void *ts4200PinInit(ts4200Pin *pin,void *syscon,void *busb,void *buspmc,void *busc) {
  if (pin->InitStatus > 0) return pin;
  LogEnter("%p,%p,%p,%p,%p\n",pin,syscon,busb,buspmc,busc);
  unsigned numlocks = DIOCount();
  Log(LOG_PIN,"%d locks\n",numlocks);
  pin->LockBase = ThreadLockAllocate(numlocks); // 129;
  pin->syscon = syscon;
  pin->piob = busb;
  pin->pioc = busc;
  pin->pmc = buspmc;
  if (pin->syscon->InitStatus < 0
      || pin->piob->InitStatus < 0
      || pin->pmc->InitStatus < 0) {
    pin->Fini(pin);
    pin->InitStatus = -1;
    return pin;
  }

  pin->Init = (void *)ts4200PinInit;
  pin->Fini = (void *)ts4200PinFini;
  pin->Lock = (void *)ts4200PinLock;
  pin->Unlock = (void *)ts4200PinUnlock;
  pin->Preempt = (void *)ts4200PinPreempt;
  pin->ModeGet = (void *)ts4200PinModeGet;
  pin->ModeSet = (void *)ts4200PinModeSet;

  pin->InitStatus = 1;
  LogReturn("%p\n",pin);
}

void ts4200PinFini(ts4200Pin *pin) { 
  if (pin->InitStatus > 0) pin->InitStatus = 0;
}

PinMode ts4200PinModeGet(ts4200Pin *pin,int npin) {
  int ret;

  if (npin >= 32 && npin <= 35) {
    if (pin->pmc->BitGet32(pin->pmc,0x18,13) == 0) return MODE_DIO;
    if (pin->piob->BitGet32(pin->piob,8,npin-32) == 1) return MODE_DIO;
    if (pin->piob->BitGet32(pin->piob,0x78,npin-32) == 1) return MODE_UNKNOWN;
    return MODE_SPI;
  } else if (npin >= 67 && npin <= 69) {
    if (pin->pioc->BitGet32(pin->pioc,8,npin-64) == 1) return MODE_DIO;
    if (pin->pioc->BitGet32(pin->pioc,0x78,npin-64)
	== ((npin == 67 || npin == 68) ? 0:1)) return MODE_UNKNOWN;
    return MODE_SPI;
  } else if (npin >= 96+16 && npin <= 96+28) {
    return pin->syscon->BitGet16(pin->syscon,0x20,0) ? MODE_BUS:MODE_DIO;
  }
  return MODE_DIO; // unimplemented
}

/*
  clear sbus + 0x16, bit 11 to disable CAN and enable DIO_15
 */
int ts4200PinModeSet(ts4200Pin *pin,int npin,PinMode mode) {
  if (npin >= 32 && npin <= 35) {
    if (mode == MODE_SPI) {
      pin->pmc->Poke32(pin->pmc,0x10,1<<13); // turn on SPI clock
      pin->piob->Poke32(pin->piob,4,1<<(npin-32)); // disable PIO
      pin->piob->Poke32(pin->piob,0x70,1<<(npin-32)); // set SPI (func A)
      return 1;
    } else if (mode == MODE_DIO) {
      pin->piob->Poke32(pin->piob,0,1<<(npin-32)); // enable PIO
      return 1;
    }
  } else if (npin >= 67 && npin <= 69) {
    if (mode == MODE_SPI) {
      pin->pioc->Poke32(pin->pioc,4,1<<(npin-64)); // disable PIO
      if (npin == 67 || npin == 68 || npin == 69) {
	pin->pioc->Poke32(pin->pioc,0x74,1<<(npin-64)); // set SPI (func B)
      } else {
	pin->pioc->Poke32(pin->pioc,0x70,1<<(npin-64)); // set SPI (func A)
      }
      return 1;
    } else if (mode == MODE_DIO) {
      pin->pioc->Poke32(pin->pioc,0,1<<(npin-64)); // enable PIO
      return 1;
    }
  } else if (npin >= 96+16 && npin <= 96+28) {
    if (mode == MODE_BUS) {
      pin->syscon->BitSet16(pin->syscon,0x20,0);
    } else if (mode == MODE_DIO) {
      pin->syscon->BitClear16(pin->syscon,0x20,0);
    }
  }
  if (mode != MODE_DIO) return -5; // unimplemented
}
/*
FPGA DIO 16-28
when Mux bus is enabled, these are Mux pins
when it is disabled, they are DIO pins
Bus 0, offset 0x20, bit 0 set is MODE_BUS, clear is MODE_DIO
 */
// Author: Michael Schmidt (michael@embeddedARM.com)
// Copyright (c) 2011, Technologic Systems, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
#endif
