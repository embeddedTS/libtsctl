#include "ts4500Pin.h"
#include "Bus.h"
#include "Thread.h"

unsigned DIOCount();

#define LOCK_TYPE_SHARED
#define LOCK_CLASS ts4500Pin
#include "TSLock.h"

static PinAPI ts4500PinAPI = {
  .Init = (void *)ts4500PinInit,
  .Fini = (void *)ts4500PinFini,
  .Lock = (void *)ts4500PinLock,
  .Unlock = (void *)ts4500PinUnlock,
  .Preempt = (void *)ts4500PinPreempt,
  .ModeGet = (void *)ts4500PinModeGet,
  .ModeSet = (void *)ts4500PinModeSet
};

void *ts4500PinInit(ts4500Pin *pin,void *sbus0,void *cpubus0,void *confbus,int confadrs) {
  Bus *sbus=sbus0;
  Bus *cpubus=cpubus0;

  if (pin->InitStatus > 0) return pin;
  pin->LockBase = ThreadLockAllocate(DIOCount());

  pin->Init = (void *)ts4500PinInit;
  pin->Fini = (void *)ts4500PinFini;
  pin->Lock = (void *)ts4500PinLock;
  pin->Unlock = (void *)ts4500PinUnlock;
  pin->Preempt = (void *)ts4500PinPreempt;
  pin->ModeGet = (void *)ts4500PinModeGet;
  pin->ModeSet = (void *)ts4500PinModeSet;

  pin->sbus = sbus;
  pin->cpubus = cpubus;
  pin->confbus = confbus;
  pin->confadrs = confadrs;
  if (pin->sbus->InitStatus < 0
      ||pin->confbus->InitStatus < 0
      ||pin->cpubus->InitStatus < 0) {
    pin->Fini(pin);
    pin->InitStatus = -1;
    return pin;
  }
  pin->InitStatus = 1;
  return pin;
}

void ts4500PinFini(ts4500Pin *pin) { 
  pin->sbus->Fini(pin->sbus);
  pin->cpubus->Fini(pin->cpubus);
  if (pin->InitStatus > 0) pin->InitStatus = 0;
}

static int XUartStatus(ts4500Pin *pin,int xnum) {
  int status;

  pin->sbus->Lock(pin->sbus,0,0);
  status = pin->sbus->BitGet16(pin->sbus,0x32,xnum+8);
  pin->sbus->Unlock(pin->sbus,0,0);
  return status;
}

PinMode ts4500PinModeGet(ts4500Pin *pin,int npin) {
  /* MODE_SPI
     CS0 = DIO17
     CS1 = DIO48
     CS2 = DIO18
     CS3 = DIO19
   */
  int ret;

  if (npin >= 23 && npin <= 34) {
    if (pin->confbus->BitGet16(pin->confbus,pin->confadrs,0)) {
      return MODE_BUS;
    }
  }
  switch (npin) {
  case 12: case 36: return XUartStatus(pin,0) ? MODE_UART : MODE_DIO;
  case 38: case 39: return XUartStatus(pin,1) ? MODE_UART : MODE_DIO;
  case 14: case 44: case 22: return XUartStatus(pin,2) ? MODE_UART : MODE_DIO;
  case 45: case 46: return XUartStatus(pin,3) ? MODE_UART : MODE_DIO;
  case 40: case 47: return XUartStatus(pin,4) ? MODE_UART : MODE_DIO;
  case 41: case 42: return XUartStatus(pin,5) ? MODE_UART : MODE_DIO;
  case 10: case 11: return XUartStatus(pin,6) ? MODE_UART : MODE_DIO;
  case 28: case 29: return XUartStatus(pin,7) ? MODE_UART : MODE_DIO;
  case 17: 
    pin->sbus->Lock(pin->sbus,0,0);
    ret = pin->sbus->BitGet16(pin->sbus,0x40,7) ? MODE_SPI : MODE_DIO;
    if (ret == MODE_SPI) {
      if (((pin->sbus->Peek16(pin->sbus,0x40) >> 8) & 3) != 0) {
	ret = MODE_DIO;
      }
    }
    pin->sbus->Unlock(pin->sbus,0,0);
    return ret;
  case 48:
    pin->sbus->Lock(pin->sbus,0,0);
    ret = pin->sbus->BitGet16(pin->sbus,0x40,7) ? MODE_SPI : MODE_DIO;
    if (ret == MODE_SPI) {
      if (((pin->sbus->Peek16(pin->sbus,0x40) >> 8) & 3) != 1) {
	ret = MODE_DIO;
      }
    }
    pin->sbus->Unlock(pin->sbus,0,0);
    return ret;
  case 18:
    pin->sbus->Lock(pin->sbus,0,0);
    ret = pin->sbus->BitGet16(pin->sbus,0x40,7) ? MODE_SPI : MODE_DIO;
    if (ret == MODE_SPI) {
      if (((pin->sbus->Peek16(pin->sbus,0x40) >> 8) & 3) != 2) {
	ret = MODE_DIO;
      }
    }
    pin->sbus->Unlock(pin->sbus,0,0);
    return ret;
  case 19:
    pin->sbus->Lock(pin->sbus,0,0);
    ret = pin->sbus->BitGet16(pin->sbus,0x40,7) ? MODE_SPI : MODE_DIO;
    if (ret == MODE_SPI) {
      if (((pin->sbus->Peek16(pin->sbus,0x40) >> 8) & 3) != 3) {
	ret = MODE_DIO;
      }
    }
    pin->sbus->Unlock(pin->sbus,0,0);
    return ret;
  case 13:
    pin->sbus->Lock(pin->sbus,0,0);
    ret = ((pin->sbus->BitGet16(pin->sbus,0x32,8) // XUART 0 enabled
	 && pin->sbus->BitGet16(pin->sbus,0x76,12)) // en_8510_rs422
	|| (pin->sbus->BitGet16(pin->sbus,0x32,9) // XUART1 enabled
	    && !pin->sbus->BitGet16(pin->sbus,0x76,12) // !en_8510_rs422
	    && !pin->sbus->BitGet16(pin->sbus,0x76,13))) ?
      MODE_UART : MODE_DIO;
    pin->sbus->Unlock(pin->sbus,0,0);
    return ret;
  case 37:
    pin->sbus->Lock(pin->sbus,0,0);
    ret = (pin->sbus->BitGet16(pin->sbus,0x32,8) // XUART 0 enabled
	   && !pin->sbus->BitGet16(pin->sbus,0x76,12)) ? // !en_8510_rs422
      MODE_UART : MODE_DIO;
    pin->sbus->Unlock(pin->sbus,0,0);
    return ret;
  case 15: case 16:
    pin->sbus->Lock(pin->sbus,0,0);
    ret = pin->sbus->BitGet16(pin->sbus,0x76,11) ? 
      MODE_CAN : MODE_DIO;
    pin->sbus->Unlock(pin->sbus,0,0);
    return ret;
  case 13+56: case 14+56:
    return (pin->cpubus->BitGet32(pin->cpubus,0x20,npin-56)) ? 
      MODE_TWI : MODE_DIO;
  default:
    if (npin >= 0 && npin < 56) {
      return MODE_DIO;
    }
  }
  return MODE_UNKNOWN;
}

/*
  clear sbus + 0x16, bit 11 to disable CAN and enable DIO_15
 */
int ts4500PinModeSet(ts4500Pin *pin,int npin,PinMode mode) {
  if (npin == 17 && mode == MODE_DIO) { // SPI is automatic with CS#
    pin->sbus->Lock(pin->sbus,0,0);
    if (((pin->sbus->Peek16(pin->sbus,0x40) >> 8) & 3) == 0) {
      pin->sbus->BitClear16(pin->sbus,0x40,7);
    }
    pin->sbus->Unlock(pin->sbus,0,0);
    return 1;
  }
  if (npin == 48 && mode == MODE_DIO) { // SPI is automatic with CS#
    pin->sbus->Lock(pin->sbus,0,0);
    if (((pin->sbus->Peek16(pin->sbus,0x40) >> 8) & 3) == 1) {
      pin->sbus->BitClear16(pin->sbus,0x40,7);
    }
    pin->sbus->Unlock(pin->sbus,0,0);
    return 1;
  }
  if (npin == 18 && mode == MODE_DIO) { // SPI is automatic with CS#
    pin->sbus->Lock(pin->sbus,0,0);
    if (((pin->sbus->Peek16(pin->sbus,0x40) >> 8) & 3) == 2) {
      pin->sbus->BitClear16(pin->sbus,0x40,7);
    }
    pin->sbus->Unlock(pin->sbus,0,0);
    return 1;
  }
  if (npin == 19 && mode == MODE_DIO) { // SPI is automatic with CS#
    pin->sbus->Lock(pin->sbus,0,0);
    if (((pin->sbus->Peek16(pin->sbus,0x40) >> 8) & 3) == 3) {
      pin->sbus->BitClear16(pin->sbus,0x40,7);
    }
    pin->sbus->Unlock(pin->sbus,0,0);
    return 1;
  }
  if (npin >= 23 && npin <= 34) {
    if (mode == MODE_DIO) {
      pin->confbus->BitClear16(pin->confbus,pin->confadrs,0);
    } else if (mode == MODE_BUS) {
      pin->confbus->BitSet16(pin->confbus,pin->confadrs,0);
    }
  }
  if (npin == 13+56 || npin == 14+56) {
    if (mode != MODE_DIO && mode != MODE_TWI) return PinErrorModeInvalid;
    pin->cpubus->BitAssign32(pin->cpubus,0x20,npin-56,mode == MODE_TWI);
    return 1;
  }
  if (npin == 15 || npin == 16) {
    if (mode != MODE_DIO && mode != MODE_CAN) return PinErrorModeInvalid;
    pin->sbus->Lock(pin->sbus,0,0);
    pin->sbus->BitAssign16(pin->sbus,0x76,11,mode==MODE_CAN);
    pin->sbus->Unlock(pin->sbus,0,0);
    return 1;
  }
  return 0;
}
/*
DIO 23-34
when Mux bus is enabled, these are Mux pins
when it is disabled, they are DIO pins
bus config register bit 0 of bus 8, offset 0x20000
 */
// Author: Michael Schmidt (michael@embeddedARM.com)
// Copyright (c) 2012, Technologic Systems, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
