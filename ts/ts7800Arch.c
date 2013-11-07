#include "arch.h"
#include "AggregateDIO.h"
#include "ArchArch.h"
#include "SystemTime.h"
#include "LocalSystem.h"
#include "MMapBus.h"

/*
  Currently support for the TS-7800 is limited solely to libtsctl supported
  PC-104 boards.

  We need to define Bus 2 as the PC-104 bus.  Since this isn't the MuxBus like
  it is on all our TS-SOCKET boards we need to emulate it.

  One assumption made by ArchPC104Init is that address 2 bit 9 must be
  cleared to de-assert ISA reset. It might be better to encapsulate that
  assumption in the Init function of the respective bus.

  This implementation is incomplete.  For instance, you have to run the
  following commands before starting for DIO to work:

  /usr/local/bin/peekpoke 32 0xe8000030 0x55555555
  /usr/local/bin/peekpoke 32 0xe8000034 0x55555555
 */

Arch *ts7800ArchInit();
void *ts7800Function(int class,int inst);
Arch *ts7800ArchNextSubArch();
void ts7800ArchNextSubArchSet(Arch *arch);

Arch ts7800Arch = {
  .Init = ts7800ArchInit,
  .Function = ts7800Function,
  .NextSubArch = ts7800ArchNextSubArch,
  .NextSubArchSet = ts7800ArchNextSubArchSet
};

Arch *ts7800ArchInit() {
  static Arch *ts7800;
  if (ts7800) return ts7800;
  ts7800 = &ts7800Arch;
  ArchPC104Init(&ts7800Arch);
  return ts7800;
}

Arch *ts7800Next;

Arch *ts7800ArchNextSubArch() {
  return ts7800Next;
}

void ts7800ArchNextSubArchSet(Arch *arch) {
  ts7800Next = arch;
}

MMapBus pc104,testbus7800;
SystemTime ts7800Time0;
LocalSystem ts7800sys;
AggregateDIO ts7800DIO0;
char testbusdata7800[4096];

void *ts7800__SystemInit0(void *s,int inst) {
  return LocalSystemInit(&ts7800sys);
}

Bus *ts7800__BusInit0(Bus *bus,int inst) {
  return MMapBusInit3(&pc104,0xEC000000,0xED000000,1);
}

Bus *ts7800__BusInit1(Bus *bus,int inst) {
  return MMapBusInit2(&testbus7800,testbusdata7800,1);
}

Bus *ts7800__BusInit2(Bus *bus,int inst) {
  return MMapBusInit3(&pc104,0xEE000000,0xEF000000,1);
}


Time *ts7800__TimeInit0(Time *t,int inst) {
  return SystemTimeInit(&ts7800Time0);
}

DIO *ts7800__DIOInit0(DIO *dio,int inst) {
  return DIOInit0(&ts7800DIO0);
}

void *ts7800Function(int class,int inst) {
  switch(class) {
  case ClassSystem:
    switch (inst) {
    case 0: return ts7800__SystemInit0;
    default: return 0;
    }
  case ClassBus:
    switch (inst) {
    case 0: return ts7800__BusInit0;
    case 1: return ts7800__BusInit1;
    case 2: return ts7800__BusInit2;
    default: return 0;
    }
  case ClassTime:
    switch (inst) {
    case 0: return ts7800__TimeInit0;
    default: return 0;
    }
  case ClassDIO:
    switch (inst) {
    case 0: return ts7800__DIOInit0;
    default: return 0;
    }
  default: return 0;
  }
}

// Author: Michael Schmidt (michael@embeddedARM.com)
// Copyright (c) 2013, Technologic Systems, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
