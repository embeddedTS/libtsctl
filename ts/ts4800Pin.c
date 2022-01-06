#ifndef ts4800Pin_c
#define ts4800Pin_c
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "ts4800Pin.h"
#include "Bus.h"
#include "Thread.h"

unsigned DIOCount();

#define LOCK_TYPE_SHARED
#define LOCK_CLASS ts4800Pin
#include "TSLock.h"

void *ts4800PinInit(ts4800Pin *pin,void *syscon,void *dio1) {
  int h;
  Bus *dio1bus = dio1;

  if (pin->InitStatus > 0) return pin;
  pin->LockBase = ThreadLockAllocate(DIOCount()); 

  pin->Init = (void *)ts4800PinInit;
  pin->Fini = (void *)ts4800PinFini;
  pin->Lock = (void *)ts4800PinLock;
  pin->Unlock = (void *)ts4800PinUnlock;
  pin->Preempt = (void *)ts4800PinPreempt;
  pin->ModeGet = (void *)ts4800PinModeGet;
  pin->ModeSet = (void *)ts4800PinModeSet;

  pin->bus = syscon;
  if (pin->InitStatus < 0
      || pin->bus->InitStatus < 0
      || dio1bus->InitStatus < 0) {
    pin->Fini(pin);
    pin->InitStatus = -1;
    return pin;
  }

  // Set up GPIO2_9 for IRQ 169 or IRQ 272 to 277
  dio1bus->BitClear32(dio1bus,0xC,19); // 0x00080000
  dio1bus->BitSet32(dio1bus,0xC,18);   // 0x00040000
  dio1bus->BitSet32(dio1bus,0x14,9); // 0x200
  dio1bus->Poke32(dio1bus,0x20088,1);
  // Set up GPIO2_31 for IRQ 191 
  dio1bus->BitClear32(dio1bus,0x10,31); // 0x80000000
  dio1bus->BitSet32(dio1bus,0x10,30);   // 0x40000000
  dio1bus->BitSet32(dio1bus,0x14,31);   // 0x80000000
  //dio1bus->Poke32(dio1bus,0x18,0x00000000);
  dio1bus->Poke32(dio1bus,0x200f8,1);

  h = open("/proc/irq/272/irq",O_RDONLY);
  if (h < 0 && errno == ENOENT) {
    // non-existence of IRQ 272 indicates we should switch to fall-back IRQs
    pin->bus->BitSet16(pin->bus,0x02,9);
  } else {
    close(h);
  }

  pin->InitStatus = 1;
  return pin;
}

void ts4800PinFini(ts4800Pin *pin) { 
  pin->bus->Fini(pin->bus);
  if (pin->InitStatus > 0) pin->InitStatus = 0;
}

PinMode ts4800PinModeGet(ts4800Pin *pin,int npin) {
  if (npin == 47 || npin == 45) {
    return pin->bus->BitGet16(pin->bus,0x10,0) ? MODE_CAN : 
      pin->bus->BitGet16(pin->bus,0x12,0) ? MODE_BUS : MODE_DIO;
  }
  if (npin == 10 || npin == 11) {
    return pin->bus->BitGet16(pin->bus,0x10,1) ? MODE_CAN :
      pin->bus->BitGet16(pin->bus,0x12,0) ? MODE_BUS : MODE_DIO;
  }
  if (npin >= 21 && npin <= 55) {
    return pin->bus->BitGet16(pin->bus,0x12,0) ? MODE_BUS : MODE_DIO;
  }
  if (npin == 3) {
    return pin->bus->BitGet16(pin->bus,2,11) ? MODE_CLK : MODE_DIO;
  }
  if (npin == 42 || npin == 43 || npin == 44 || npin == 45 || npin == 18 || npin == 127 || npin == 128) {
    return pin->bus->BitGet16(pin->bus,0x10,7) ? MODE_SPI : MODE_DIO;
  }
  //return (pin->bus->BitGet32(pin->bus,0x30,pin)) ? MODE_TWI : MODE_DIO;
  return MODE_UNKNOWN;
}

PinResult ts4800PinModeSet(ts4800Pin *pin,int npin,PinMode mode) {
  // in the case of CAN, setting either pin of the pair to MODE_CAN
  // automatically sets the other pin as well, so only need to call once.

  if (npin == 42 || npin == 43 || npin == 44 || npin == 45 || npin == 18 || npin == 127 || npin == 128) {
    if (mode != MODE_SPI && mode != MODE_DIO) return MODE_UNKNOWN;
    pin->bus->BitAssign16(pin->bus,0x10,7,(MODE_SPI == mode ? 1 : 0));
  }

  if (npin == 20) {
    if (mode == MODE_DIO) {
      pin->bus->BitClear16(pin->bus,0x10,9);
    }
  }
  if (npin >= 21 && npin <= 55) {
    if (mode == MODE_BUS) {
      pin->bus->BitSet16(pin->bus,0x12,0);
    } else if (mode == MODE_DIO) {
      pin->bus->BitClear16(pin->bus,0x12,0);
    }
  }
  if (npin == 47 || npin == 45) {
    if (mode != MODE_CAN && mode != MODE_DIO) return PinErrorModeInvalid;
    pin->bus->BitAssign16(pin->bus,0x10,0,mode == MODE_CAN);
  } else if (npin == 10 || npin == 11) {
    if (mode != MODE_CAN && mode != MODE_DIO) return PinErrorModeInvalid;
    pin->bus->BitAssign16(pin->bus,0x10,1,mode == MODE_CAN);
  }
  if (npin == 3) {
    pin->bus->Lock(pin->bus,0,0);
    if (mode == MODE_DIO) {
      pin->bus->BitClear16(pin->bus,2,11); // turn off 12.5Mhz clock
    } else if (mode == MODE_CLK) {
      pin->bus->BitSet16(pin->bus,2,11); // turn on 12.5Mhz clock
    } else {
      pin->bus->Unlock(pin->bus,0,0);
      return PinErrorModeInvalid;
    }
    pin->bus->Unlock(pin->bus,0,0);  
  }
  return PinSuccess;
}
/*
DIO 21-55:
when Mux bus is enabled, these are Mux pins
when it is disabled, they are DIO pins
bus adrs 0x12 bit 0 is set for Mux, clear for DIO
 */
// Author: Michael Schmidt (michael@embeddedTS.com)
// Copyright (c) 2011-2022 Technologic Systems, Inc. dba embeddedTS, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
#endif
