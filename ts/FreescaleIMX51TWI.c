#include "FreescaleIMX51TWI.h"

static TWIAPI FreescaleIMX51TWIAPI =  {
  .Init = (void *)FreescaleIMX51TWIInit,
  .Fini = (void *)FreescaleIMX51TWIFini,
  .Lock = (void *)FreescaleIMX51TWILock,
  .Write = (void *)FreescaleIMX51TWIWrite,
  .Read = (void *)FreescaleIMX51TWIRead,
};

/*
  p.1126

  IADR=BASE+0
  IFDR=BASE+4
  I2CR=BASE+8
  I2SR=BASE+0xC
  I2DR=BASE+0x10

  IADR[7:1] = slave address 
  IFDR[5:0] = prescaler to set clock frequency
              see p.1129 for divider values
  I2CR[7] = I2C enable (set first)
  I2CR[5] = master mode
  I2CR[4] = transmit/receive mode
  I2CR[3] = transmit acknowledge enable
  I2CR[2] = repeat start

  I2SR = status register (p.1131)
  I2DR = data register

  p.65
  BASE =
  I2C2 0x83FC4000
  I2C1 0x83FC8000

  
 */
void *FreescaleIMX51TWIInit(FreescaleIMX51TWI *twi,void *bus1) {
  Bus *bus = bus1;

  if (twi->InitStatus > 0) return twi;

  twi->Init = (void *)FreescaleIMX51TWIInit;
  twi->Fini = (void *)FreescaleIMX51TWIFini;
  twi->Lock = (void *)FreescaleIMX51TWILock;
  twi->Write = (void *)FreescaleIMX51TWIWrite;
  twi->Read = (void *)FreescaleIMX51TWIRead;

  twi->bus = bus;

  if (twi->bus->InitStatus <= 0) {
    twi->Fini(twi);
    twi->InitStatus = -1;
    return twi;
  }

  //twi->dio->SetAsync(twi->dio,twi->TW_CLK,INPUT); // SCL=1
  //twi->dio->SetAsync(twi->dio,twi->TW_DAT,INPUT); // SDA=1
  //usleep(10000); // ample time for them to become stable
  twi->InitStatus = 1;
  return twi;
}

void FreescaleIMX51TWIFini(FreescaleIMX51TWI *twi){
  twi->bus->Fini(twi->bus);
  if (twi->InitStatus > 0) twi->InitStatus = 0;
}

#define IADR 0
#define IFDR 4
#define I2CR 8
#define I2SR 0xC
#define I2DR 0x10

int FreescaleIMX51TWIWrite(FreescaleIMX51TWI *twi,int devadrs,int adrslen,int adrs,int len,char *bytes){
  twi->bus->Poke16(twi->bus,IADR,devadrs<<1);
  twi->bus->BitSet16(twi->bus,I2CR,7); // enable
  twi->bus->BitSet16(twi->bus,I2CR,5); // master (START)
  twi->bus->BitSet16(twi->bus,I2CR,4); // transmit mode (Write)
  twi->bus->BitClear16(twi->bus,I2CR,3); // transmit ack enable OFF (no STOP?)
  twi->bus->BitClear16(twi->bus,I2CR,2); // repeated start


  return 1;
}

int FreescaleIMX51TWIRead(FreescaleIMX51TWI *twi,int devadrs,int adrslen,int adrs,int len,char *bytes){
  return 1;
}

int FreescaleIMX51TWILock(FreescaleIMX51TWI *twi,int command,unsigned num) {
  int ret;

  switch (command) {
  case WaitLock:
  case TryLock:
    if ((ret=lock->Lock(lock,command,twi->LockNum)) < 0) return ret;
    /*
    if ((ret=twi->dio->Lock(twi->dio,command,twi->TW_CLK)) < 0) {
      command = DoRelease;
      goto DoRelease2;
    }
    if ((ret=twi->dio->Lock(twi->dio,command,twi->TW_DAT)) < 0) {
      command = DoRelease;
      goto DoRelease1;
    }
    */
    return 1;
  case DoRelease:
    /*
    ret = 1;
    twi->dio->Lock(twi->dio,command,twi->TW_DAT);
  DoRelease1:
    twi->dio->Lock(twi->dio,command,twi->TW_CLK);
  DoRelease2:
    */
    lock->Lock(lock,command,twi->LockNum); // TWI mutex
    return ret;
  case DoPreempt:
    FreescaleIMX51TWILock(twi,DoRelease,num);
    sched_yield();
    return FreescaleIMX51TWILock(twi,WaitLock,num);
  }
  return 0;
}


// Author: Michael Schmidt (michael@embeddedTS.com)
// Copyright (c) 2011-2022 Technologic Systems, Inc. dba embeddedTS, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
