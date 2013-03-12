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

void *ts4200PinInit(ts4200Pin *pin,void *syscon,void *busb,void *buspmc,void *busc,void *busa) {
  if (pin->InitStatus > 0) return pin;
  LogEnter("%p,%p,%p,%p,%p\n",pin,syscon,busb,buspmc,busc);
  unsigned numlocks = DIOCount();
  Log(LOG_PIN,"%d locks\n",numlocks);
  pin->LockBase = ThreadLockAllocate(numlocks); // 129;
  pin->syscon = syscon;
  pin->pioa = busa;
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
/*
30,31 36-45 are CPU UART / DIO
CN2_78=36=PB4
CN2_80=37=PB5
CN2_82=38=PB6
CN2_84=39=PB7
CN2_86=40=PB8
CN2_88=41=PB9
CN2_90=42=PB10
CN2_92=43=PB11
CN2_94=31=PA31
CN2_96=30=PA30
CN2_98=44=PB12
CN2_10=45=PB13

piob=6 @0xFFFFF600
pmc=12 @0xFFFFFC00
pioc=8 @0xFFFFF800
 */

PinResult ts4200PinModeSet(ts4200Pin *pin,int npin,PinMode mode) {
  if (npin == 30 || npin == 31) {
    if (mode == MODE_DIO) {
      pin->pioa->Poke32(pin->pioa,0,1<<(npin-0)); // enable PIO
      return PinSuccess;
    } else if (mode == MODE_UART) {
      pin->pioa->Poke32(pin->pioa,4,1<<(npin-0)); // disable PIO
      return PinSuccess;
    } else {
      return PinErrorModeInvalid;
    }
  } else if (npin >= 36 && npin <= 45) {
    if (mode == MODE_DIO) {
      pin->piob->Poke32(pin->piob,0,1<<(npin-32)); // enable PIO
      return PinSuccess;
    } else if (mode == MODE_UART) {
      pin->piob->Poke32(pin->piob,4,1<<(npin-32)); // disable PIO
      return PinSuccess;
    } else {
      return PinErrorModeInvalid;
    }
  } else if (npin >= 32 && npin <= 35) {
    if (mode == MODE_SPI) {
      pin->pmc->Poke32(pin->pmc,0x10,1<<13); // turn on SPI clock
      pin->piob->Poke32(pin->piob,4,1<<(npin-32)); // disable PIO
      pin->piob->Poke32(pin->piob,0x70,1<<(npin-32)); // set SPI (func A)
      return PinSuccess;
    } else if (mode == MODE_DIO) {
      pin->piob->Poke32(pin->piob,0,1<<(npin-32)); // enable PIO
      return PinSuccess;
    } else return PinErrorModeInvalid;
  } else if (npin >= 67 && npin <= 69) {
    if (mode == MODE_SPI) {
      pin->pioc->Poke32(pin->pioc,4,1<<(npin-64)); // disable PIO
      if (npin == 67 || npin == 68 || npin == 69) {
	pin->pioc->Poke32(pin->pioc,0x74,1<<(npin-64)); // set SPI (func B)
      } else {
	pin->pioc->Poke32(pin->pioc,0x70,1<<(npin-64)); // set SPI (func A)
      }
      return PinSuccess;
    } else if (mode == MODE_DIO) {
      pin->pioc->Poke32(pin->pioc,0,1<<(npin-64)); // enable PIO
      return PinSuccess;
    } else return PinErrorModeInvalid;
  } else if (npin >= 96+16 && npin <= 96+28) {
    if (mode == MODE_BUS) {
      pin->syscon->BitSet16(pin->syscon,0x20,0);
    } else if (mode == MODE_DIO) {
      pin->syscon->BitClear16(pin->syscon,0x20,0);
    } else return PinErrorModeInvalid;
  }
  if (mode != MODE_DIO) return PinErrorModeInvalid;
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
