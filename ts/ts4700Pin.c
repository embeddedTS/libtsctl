#ifndef ts4700Pin_c
#define ts4700Pin_c
#include "ts4700Pin.h"
#include "Bus.h"
#include "Log.h"
#include "Thread.h"

unsigned DIOCount();

#define LOCK_TYPE_SHARED
#define LOCK_CLASS ts4700Pin
#include "TSLock.h"

/*
syscon[2]: active low to enable DIO
bit 8: DIO 15,16
bit 9: DIO 10,11
bit 10: DIO 17-20
bit 11: DIO 6,7
bit 12: DIO 12
bit 13: DIO 14
bit 14: DIO 30-35
bit 15:
 */

void *ts4700PinInit(ts4700Pin *pin,void *diobus0,void *mfpbus0) {
  Bus *diobus=diobus0;
  Bus *mfpbus=mfpbus0;

  if (pin->InitStatus > 0) return pin;
  pin->LockBase = ThreadLockAllocate(DIOCount());

  pin->Init = (void *)ts4700PinInit;
  pin->Fini = (void *)ts4700PinFini;
  pin->Lock = (void *)ts4700PinLock;
  pin->Unlock = (void *)ts4700PinUnlock;
  pin->Preempt = (void *)ts4700PinPreempt;
  pin->ModeGet = (void *)ts4700PinModeGet;
  pin->ModeSet = (void *)ts4700PinModeSet;

  pin->diobus = diobus;
  pin->mfpbus = mfpbus;
  if (pin->InitStatus < 0
      ||diobus->InitStatus < 0
      || mfpbus->InitStatus < 0) {
    pin->Fini(pin);
    pin->InitStatus = -1;
    return pin;
  }
  pin->InitStatus = 1;
  return pin;
}

void ts4700PinFini(ts4700Pin *pin) { 
  pin->diobus->Fini(pin->diobus);
  if (pin->InitStatus > 0) pin->InitStatus = 0;
}

PinMode ts4700PinModeGet(ts4700Pin *pin,int npin) {
  int ret=MODE_UNKNOWN,tmp;

  //log9(LOG_PIN,"ts4700PinModeGet %d\n",npin);
  if (npin >= 22 && npin <= 42) {
    pin->diobus->Lock(pin->diobus,0,SHARED);
    ret=(tmp=pin->diobus->BitGet16(pin->diobus,4,0)) ? MODE_BUS:MODE_DIO;
    //log9(LOG_PIN,"%d,%d,%d\n",npin,tmp,ret);
    pin->diobus->Unlock(pin->diobus,0,SHARED);
  }
  if (npin == 149) { // PWR_SDA (use DIO 87 for DIO mode)
    pin->mfpbus->Lock(pin->mfpbus,0,SHARED);
    int tmp = pin->mfpbus->Peek32(pin->mfpbus,0x1f0) & 7;
    pin->mfpbus->Unlock(pin->mfpbus,0,SHARED);
    if (tmp == 0) return MODE_TWI;
    if (tmp == 6) return MODE_DIO;
    ret=MODE_UNKNOWN;
  } else if (npin == 150) { // PWR_SCL (use DIO 88 for DIO mode)
    pin->mfpbus->Lock(pin->mfpbus,0,SHARED);
    int tmp = pin->mfpbus->Peek32(pin->mfpbus,0x1ec) & 7;
    pin->mfpbus->Unlock(pin->mfpbus,0,SHARED);
    if (tmp == 0) return MODE_TWI;
    if (tmp == 6) return MODE_DIO;
    ret=MODE_UNKNOWN;
  } else if (npin == 15 || npin == 16) {
    pin->diobus->Lock(pin->diobus,0,SHARED);
    ret=(pin->diobus->BitGet16(pin->diobus,0x2,8)) ? MODE_CAN : MODE_DIO;
    pin->diobus->Unlock(pin->diobus,0,SHARED);
  } else if (npin == 10 || npin == 11) {
    pin->diobus->Lock(pin->diobus,0,SHARED);
    ret=(pin->diobus->BitGet16(pin->diobus,0x2,8)) ? MODE_CAN : MODE_DIO;
    pin->diobus->Unlock(pin->diobus,0,SHARED);
  } else if (npin >=17 && npin <= 20) {
    pin->diobus->Lock(pin->diobus,0,SHARED);
    ret=(pin->diobus->BitGet16(pin->diobus,0x2,10)) ? MODE_SPI : MODE_DIO;
    pin->diobus->Unlock(pin->diobus,0,SHARED);
  } else if (npin == 6 || npin == 7) {
    pin->diobus->Lock(pin->diobus,0,SHARED);
    ret=(pin->diobus->BitGet16(pin->diobus,0x2,11)) ? MODE_ADC : MODE_DIO;
    pin->diobus->Unlock(pin->diobus,0,SHARED);
  } else if (npin == 12) {
    pin->diobus->Lock(pin->diobus,0,SHARED);
    ret=(pin->diobus->BitGet16(pin->diobus,0x2,12)) ? MODE_UART : MODE_DIO;
    pin->diobus->Unlock(pin->diobus,0,SHARED);
  } else if (npin == 14) {
    pin->diobus->Lock(pin->diobus,0,SHARED);
    ret=(pin->diobus->BitGet16(pin->diobus,0x2,13)) ? MODE_UART : MODE_DIO;
    pin->diobus->Unlock(pin->diobus,0,SHARED);
  } else if (npin >=30 && npin <= 35) {
    pin->diobus->Lock(pin->diobus,0,SHARED);
    ret=(pin->diobus->BitGet16(pin->diobus,0x2,14)) ? MODE_TS : MODE_DIO;
    pin->diobus->Unlock(pin->diobus,0,SHARED);
  } else if (npin == 3) {
    return pin->diobus->BitGet16(pin->diobus,2,11) ? MODE_CLK : MODE_DIO;
  } else {
    ret=MODE_DIO;
  }
  return ret;
}

/* mux bus DIO pins:
  22-42
 */
PinResult ts4700PinModeSet(ts4700Pin *pin,int npin,PinMode mode) {
  //log9(LOG_PIN,"ts4700PinModeSet %d,%d\n",npin,mode);
  if (npin >= 22 && npin <= 42) {
    if (mode == MODE_BUS) {
      pin->diobus->Lock(pin->diobus,0,0);
      pin->diobus->BitSet16(pin->diobus,4,0);
      pin->diobus->Unlock(pin->diobus,0,0);
    } else if (mode == MODE_DIO) {
      pin->diobus->Lock(pin->diobus,0,0);
      pin->diobus->BitClear16(pin->diobus,4,0);
      pin->diobus->Unlock(pin->diobus,0,0);
    }
  }
  if (npin >= 62+0 && npin <= 62+36) { 
    // 62 to 62+36 = MFP_00 to MFP_36
    pin->mfpbus->Lock(pin->mfpbus,0,SHARED);
    pin->mfpbus->Assign32X(pin->mfpbus,0x4c+(npin-62)*4,2,0,0); // alt fcn = 0
    pin->mfpbus->Unlock(pin->mfpbus,0,SHARED);
  } else if (npin >= 62+37 && npin <= 62+55) { 
    // 62+37 to 62+55 = MFP_37 to MFP_55
    pin->mfpbus->Lock(pin->mfpbus,0,SHARED);
    pin->mfpbus->Assign32X(pin->mfpbus,(npin-99)*4,2,0,0); // alt fcn = 0
    pin->mfpbus->Unlock(pin->mfpbus,0,SHARED);
  } else if (npin >= 62+56 && npin <= 62+122 && npin != 149 && npin != 150) { 
    // 62+56 to 62+122 = MFP_56 to MFP_122
    // TO DO: why does this overlap with 149, 150 (PWR_SDA, PWR_SCL)?
    pin->mfpbus->Lock(pin->mfpbus,0,SHARED);
    pin->mfpbus->Assign32X(pin->mfpbus,0xE0+(npin-118)*4,2,0,0); // alt fcn = 0
    pin->mfpbus->Unlock(pin->mfpbus,0,SHARED);
  }
  if (npin == 149) { // PWR_SDA (use DIO 149 for DIO mode)
    if (mode == MODE_TWI) {
      pin->mfpbus->Lock(pin->mfpbus,0,0);
      pin->mfpbus->Poke32(pin->mfpbus,0x1f0,0x0c00);
      pin->mfpbus->Unlock(pin->mfpbus,0,0);
    } else if (mode == MODE_DIO) {
      pin->mfpbus->Lock(pin->mfpbus,0,0);
      pin->mfpbus->Poke32(pin->mfpbus,0x1f0,0x4c06);
      pin->mfpbus->Unlock(pin->mfpbus,0,0);
    } else return PinErrorModeInvalid;
  } else if (npin == 150) { // PWR_SCL (use DIO 150 for DIO mode)
    if (mode == MODE_TWI) {
      pin->mfpbus->Lock(pin->mfpbus,0,0);
      pin->mfpbus->Poke32(pin->mfpbus,0x1ec,0x0c00);
      pin->mfpbus->Unlock(pin->mfpbus,0,0);
    } else if (mode == MODE_DIO) {
      pin->mfpbus->Lock(pin->mfpbus,0,0);
      pin->mfpbus->Poke32(pin->mfpbus,0x1ec,0x4c06);
      pin->mfpbus->Unlock(pin->mfpbus,0,0);
    } else return PinErrorModeInvalid;
  } else if (npin == 15 || npin == 16) {
    if (mode != MODE_DIO && mode != MODE_CAN) return PinErrorModeInvalid;
    pin->diobus->Lock(pin->diobus,0,0);
    pin->diobus->BitAssign16(pin->diobus,0x2,8,mode == MODE_CAN);
    pin->diobus->Unlock(pin->diobus,0,0);
  } else if (npin == 10 || npin == 11) {
    if (mode != MODE_DIO && mode != MODE_CAN) return PinErrorModeInvalid;
    pin->diobus->Lock(pin->diobus,0,0);
    pin->diobus->BitAssign16(pin->diobus,0x2,9,mode == MODE_CAN);
    pin->diobus->Unlock(pin->diobus,0,0);
  } else if (npin >=17 && npin <= 20) {
    if (mode != MODE_DIO && mode != MODE_SPI) return PinErrorModeInvalid;
    pin->diobus->Lock(pin->diobus,0,0);
    pin->diobus->BitAssign16(pin->diobus,0x2,10,mode == MODE_SPI);
    pin->diobus->Unlock(pin->diobus,0,0);
  } else if (npin == 6 || npin == 7) {
    if (mode != MODE_DIO && mode != MODE_ADC) return PinErrorModeInvalid;
    // apparently this used to be necessary, but got obsoleted. now it
    // breaks base boards that need the 12.5Mhz clock
    //pin->diobus->Lock(pin->diobus,0,0);
    //pin->diobus->BitAssign16(pin->diobus,0x2,11,mode == MODE_ADC);
    //pin->diobus->Unlock(pin->diobus,0,0);
  } else if (npin == 12) {
    if (mode != MODE_DIO && mode != MODE_UART) return PinErrorModeInvalid;
    pin->diobus->Lock(pin->diobus,0,0);
    pin->diobus->BitAssign16(pin->diobus,0x2,12,mode == MODE_UART);
    pin->diobus->Unlock(pin->diobus,0,0);
  } else if (npin == 14) {
    if (mode != MODE_DIO && mode != MODE_UART) return PinErrorModeInvalid;
    pin->diobus->Lock(pin->diobus,0,0);
    pin->diobus->BitAssign16(pin->diobus,0x2,13,mode == MODE_UART);
    pin->diobus->Unlock(pin->diobus,0,0);
  } else if (npin >=30 && npin <= 35) {
    if (mode != MODE_DIO && mode != MODE_TS) return PinErrorModeInvalid;
    pin->diobus->Lock(pin->diobus,0,0);
    pin->diobus->BitAssign16(pin->diobus,0x2,14,mode == MODE_TS);
    pin->diobus->Unlock(pin->diobus,0,0);
  } else if (npin == 3) {
    pin->diobus->Lock(pin->diobus,0,0);
    if (mode == MODE_DIO) {
      pin->diobus->BitClear16(pin->diobus,2,11); // turn off 12.5Mhz clock
    } else if (mode == MODE_CLK) {
      pin->diobus->BitSet16(pin->diobus,2,11); // turn on 12.5Mhz clock
    } else {
      pin->diobus->Unlock(pin->diobus,0,0);
      return PinErrorModeInvalid;
    }
    pin->diobus->Unlock(pin->diobus,0,0);
  } else {
    if (mode != MODE_DIO) return PinErrorModeInvalid;
  }
  return PinSuccess;
}
/*
FPGA DIO 22-42
when Mux bus is enabled, these are Mux pins
when it is disabled, they are DIO pins
Bus 0, offset 4, bit 0 set is MODE_BUS, clear is MODE_DIO
 */
// Author: Michael Schmidt (michael@embeddedTS.com)
// Copyright (c) 2011-2022 Technologic Systems, Inc. dba embeddedTS, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
#endif
