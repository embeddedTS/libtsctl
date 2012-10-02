#include "linux86.h"

#include "NetLock.h"
#include "arch.h"
#define NO_SERVER
int ModelId = 0x86;

void linux86_ArchInit() {
  ThreadInit();
}

System *ts4200_SystemInit(System *s,int inst) {
  return s;
}

DIORaw *linux86_DIORawInit(DIORaw *dioraw,int inst) {
  return dioraw;
  //if (inst < 0 || inst > 15) return 0;
  //return NetDIORawInit(&Net_dioraw[inst],NetDIORawSocket[inst],NetDIORawInst[inst],NetMode,&q,&cmds);
}

DIO *linux86_DIOInit(DIO *dio,int inst) {
  return dio;
  //if (inst < 0 || inst > 15) return 0;
  //return NetDIOInit(&Net_dio[inst],NetDIOSocket[inst],NetDIOInst[inst],NetMode,&q,&cmds);
}

Bus *linux86_BusInit(Bus *bus,int inst) {
  return bus;
  //if (inst < 0 || inst > 15) return 0;
  //return NetBusInit(&Net_bus[inst],NetBusSocket[inst],NetBusInst[inst],NetMode,&q,&cmds);
}

Time *linux86_TimeInit(Time *t,int inst) {
  return t;
  //if (inst < 0 || inst > 15) return 0;
  //return NetTimeInit(&Net_t[inst],NetTimeSocket[inst],NetTimeInst[inst],NetMode,&q,&cmds);
}

Pin *linux86_PinInit(Pin *pin,int inst) {
  return pin;
  //if (inst < 0 || inst > 15) return 0;
  //return NetPinInit(&Net_pin[inst],NetPinSocket[inst],NetPinInst[inst],NetMode,&q,&cmds);
}

TWI *linux86_TWIInit(TWI *twi,int inst) {
  return twi;
  //if (inst < 0 || inst > 15) return 0;
  //return NetTWIInit(&Net_twi[inst],NetTWISocket[inst],NetTWIInst[inst],NetMode,&q,&cmds);
}

SPI *linux86_SPIInit(SPI *spi,int inst) {
  return spi;
}

int CANBusNum[0];

CAN *linux86_CANInit(CAN *can,int inst) {
  return can;
}

AIO *linux86_AIOInit(AIO *aio,int inst) {
  return aio;
}

int CANMain(CAN *can,int listen,int irqfd,int s) {
  return 6;
}

ArchInfo linux86_ArchInfo = {
  .TimeInstances=0, 
  .BusInstances=0, 
  .PinInstances=0, 
  .CANInstances=0,
  .DIORawInstances=0,
  .DIOInstances=0,
  .SPIInstances=0,
  .TWIInstances=0,
  .AIOInstances=0,
  .EDIOInstances=0,
  .ArchInit=linux86_ArchInit,
  .TimeInit=linux86_TimeInit,
  .BusInit=linux86_BusInit,
  .PinInit=linux86_PinInit,
  .CANInit=linux86_CANInit,
  .DIORawInit=linux86_DIORawInit,
  .DIOInit=linux86_DIOInit,
  .SPIInit=linux86_SPIInit,
  .TWIInit=linux86_TWIInit,
  .AIOInit=linux86_AIOInit
  //.EDIOInit=linux86_EDIOInit
};

#include "arch.c"

// Author: Michael Schmidt (michael@embeddedARM.com)
// Copyright (c) 2012, Technologic Systems, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
