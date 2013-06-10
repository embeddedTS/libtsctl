#ifndef __tscan1_c
#define __tscan1_c
#include "TSCAN1Bus.c"
#include "arch.h"
#include "baudtab16.h"

TSCAN1Bus tsCAN1Bus150,tsCAN1Bus158;
SJA1000CAN tscan1CAN0,tscan1CAN1;
CANConn tscan1CAN0conn[16],tscan1CAN1conn[16];

#define tscan1SystemInstances 0
Bus *tscan1__BusInit0(Bus *bus,int inst) {
  return TSCAN1BusInit(&tsCAN1Bus150,BusInit(2),0x150);
}
Bus *tscan1__BusInit1(Bus *bus,int inst) {
  return TSCAN1BusInit(&tsCAN1Bus158,BusInit(2),0x158);
}

#define tscan1BusInstances 1
#define tscan1TimeInstances 0
#define tscan1PinInstances 0
#define tscan1DIORawInstances 0
#define tscan1DIOInstances 0
#define tscan1TWIInstances 0
int tscan1_CANBusNum[2]; // how do we initialize this???

CAN *tscan1__CANInit0(CAN *can,int inst) {
  tscan1CAN0.LockBase = 2;
  tscan1CAN0.status = 0;
  tscan1CAN0.CAN_TX = -1;
  tscan1CAN0.CAN_RX = -1;
  tscan1CAN0.D.conn = tscan1CAN0conn;
  tscan1CAN0.D.maxconn = 16;
  tscan1CAN0.D.nconn = 0;
  tscan1CAN0.D.txc = 0;
  tscan1CAN0.baud = 1000000;
  tscan1CAN0.baudparms = baudparms16;
  tscan1CAN0.irq = 194;
  Bus *bus = tscan1__BusInit0(0,0);
  if (!bus) return 0;
  return SJA1000CANInit(&tscan1CAN0,bus,PinInit(0),TimeInit(0));
}

CAN *tscan1__CANInit1(CAN *can,int inst) {
  tscan1CAN0.LockBase = 2;
  tscan1CAN0.status = 0;
  tscan1CAN0.CAN_TX = -1;
  tscan1CAN0.CAN_RX = -1;
  tscan1CAN0.D.conn = tscan1CAN1conn;
  tscan1CAN0.D.maxconn = 16;
  tscan1CAN0.D.nconn = 0;
  tscan1CAN0.D.txc = 0;
  tscan1CAN0.baud = 1000000;
  tscan1CAN0.baudparms = baudparms16;
  tscan1CAN0.irq = 191;
  Bus *bus = tscan1__BusInit1(0,1);
  if (!bus) return 0;
  return SJA1000CANInit(&tscan1CAN0,bus,PinInit(0),TimeInit(0));
}


#define tscan1CANInstances 1
#define tscan1SPIInstances 0
#define tscan1EDIOInstances 0
#define tscan1AIOInstances 0

int tscan1_ArchInit() {
  LogEnter("");
  int i;
  static int found = 1;
  if (found) LogReturn("%d",1);
  if (!tscan1_ArchInfo.parent) return 0;
  LogReturn("%d",0);
}

#define ARCH tscan1
#define ARCHTYPE ArchTypePC104
#define ARCHSUBTYPE ArchTypeNone

#define CLASS_INC "classinit2.h"
#include "classeach.h"

#include "archinit.h"
#define ARCH_LAST tscan1


// Author: Michael Schmidt (michael@embeddedARM.com)
// Copyright (c) 2012, Technologic Systems, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
#endif
