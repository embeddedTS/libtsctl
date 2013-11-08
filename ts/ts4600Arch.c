#include "Thread.h"
#include <string.h>
#include "arch.h"
#include "ArchArch.h"
#include "DummyBus.h"
#include "MMapBus.h"
#include "NBus.h"
#include "AggregateDIO.h"
#include "ts4600DIO.h"
#include "LocalSystem.h"
#include "ts4600_dioctl_config.c"

Arch *ts4600BBArch;
Arch *ts4600ArchInit();
void *ts4600Function(int class,int inst);
Arch *ts4600ArchNextSubArch();

Arch ts4600Arch = {
  .Init = ts4600ArchInit,
  .Function = ts4600Function,
  .NextSubArch = ts4600ArchNextSubArch
};

Arch *ts4600ArchInit() {
  static Arch *ts4600;
  if (ts4600) return ts4600;
  ts4600 = &ts4600Arch;
  dioctl_config_add2(Xts4600_dioctl_config,Xts4600_dioctl_config_len,Yts4600_dioctl_config_len); 

  ts4600BBArch = ArchBBInit();
  return ts4600;
}

Arch *ts4600ArchNextSubArch() {
  return ts4600BBArch;
}

NBus nbus;
LocalSystem ts4600sys;
AggregateDIO ts4600DIO0;
ts4600DIO ts4600DIO1;
unsigned char ts4600DIO1Caps[70];

void *ts4600__SystemInit0(void *s,int inst) {
  return LocalSystemInit(&ts4600sys);
}

Bus *ts4600__BusInit0(Bus *bus,int inst) {
  return NBusInit(&nbus);
}

DIO *ts4600__DIOInit0(DIO *dio,int inst) {
  return DIOInit0(&ts4600DIO0);
}

DIO *ts4600__DIOInit1(DIO *dio,int inst) {
  int i;

  for (i=0;i<70;i++) {
    ts4600DIO1Caps[i] = DIO_NORMAL;
  }
  ts4600DIO1Caps[i++] = DIO_OUTPUT_ONLY;
  ts4600DIO1Caps[i++] = DIO_OUTPUT_ONLY;
  ts4600DIO1.Caps = ts4600DIO1Caps;
  return ts4600DIOInit(&ts4600DIO1,ts4600__BusInit0(0,0));
}

void *ts4600Function(int class,int inst) {
  switch(class) {
  case ClassSystem:
    switch (inst) {
    case 0: return ts4600__SystemInit0;
    default: return 0;
    }
  case ClassBus:
    switch (inst) {
    case 0: return ts4600__BusInit0;
    default: return 0;
    }
  case ClassDIO:
    switch (inst) {
    case 0: return ts4600__DIOInit0;
    case 1: return ts4600__DIOInit1;
    default: return 0;
    }
  default: return 0;
  }
}

// Author: Michael Schmidt (michael@embeddedARM.com)
// Copyright (c) 2013, Technologic Systems, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.

