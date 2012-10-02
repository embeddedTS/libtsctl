#include "Time.h"
#include "Bus.h"
#include "Pin.h"
#include "CAN.h"
#include "DIORaw.h"
#include "DIO.h"
#include "TWI.h"
#include "tsRelay8DIORaw.c"
#include "DummyDIO.c"
#include "PhysicalDIO.h"
#include "arch.h"

static tsRelay8DIORaw r8dio[4];
static PhysicalDIO r8pdio[4];
static unsigned char Relay8DIOCapabilities[8];
static DummyDIO r8dummyDIO[4];

#define tsrelay8SystemInstances 0
#define tsrelay8BusInstances 0
#define tsrelay8TimeInstances 0
#define tsrelay8PinInstances 0

#include <stdio.h>
DIORaw *tsrelay8__DIORawInit0(DIORaw *dioraw0,int inst) {
  Bus *muxbus = BusInit(2);
  int i=0;
  DIORaw *dioraw;

  if (inst >= 0 && inst <= 3) {
    muxbus->Lock(muxbus,0,0);
    muxbus->BitClear16(muxbus,2,9); // make sure ISA reset de-asserted
    muxbus->Unlock(muxbus,0,0);
    dioraw = tsRelay8DIORawInit(&r8dio[i],muxbus,0x140 + inst * 0x10);
    if (dioraw) {
      return dioraw;
    } else {
      return 0;
    }
  }
  return dioraw0;
}
DIORaw *tsrelay8__DIORawInit1(DIORaw *dioraw0,int inst) {
  return tsrelay8__DIORawInit0(dioraw0,inst);
}
DIORaw *tsrelay8__DIORawInit2(DIORaw *dioraw0,int inst) {
  return tsrelay8__DIORawInit0(dioraw0,inst);
}
DIORaw *tsrelay8__DIORawInit3(DIORaw *dioraw0,int inst) {
  return tsrelay8__DIORawInit0(dioraw0,inst);
}
#define tsrelay8DIORawInstances 4

DIO *tsrelay8__DIOInit0(DIO *dio,int inst) {
  DIORaw *dioraw;
  int i;
  if (inst >= 0 && inst <= 3) {
    dioraw = tsrelay8__DIORawInit0(0,inst);
    if (dioraw) {
      for (i=0;i<8;i++) {
	Relay8DIOCapabilities[i] = DIO_OUTPUT_ONLY;
      }
      r8pdio[inst].Caps = Relay8DIOCapabilities;
      return PhysicalDIOInit(&r8pdio[inst],BusInit(2),dioraw);
    } else {
      return DummyDIOInit(&r8dummyDIO[inst],8);
    }
  }
  return dio;
}
DIO *tsrelay8__DIOInit1(DIO *dio,int inst) {
  return tsrelay8__DIOInit0(dio,inst);
}
DIO *tsrelay8__DIOInit2(DIO *dio,int inst) {
  return tsrelay8__DIOInit0(dio,inst);
}
DIO *tsrelay8__DIOInit3(DIO *dio,int inst) {
  return tsrelay8__DIOInit0(dio,inst);
}
#define tsrelay8DIOInstances 4

#define tsrelay8TWIInstances 0
int tsrelay8_CANBusNum[0];
#define tsrelay8CANInstances 0
#define tsrelay8SPIInstances 0
#define tsrelay8EDIOInstances 0
#define tsrelay8AIOInstances 0

int tsrelay8_ArchInit() {
  LogEnter("");
  int i;
  static int found = 0;
  if (found) LogReturn("%d",1);
  if (!tsrelay8_ArchInfo.parent) return 0;
  if (tsrelay8__DIORawInit0(0,0)) found=1;
  else if (tsrelay8__DIORawInit1(0,1)) found=1;
  else if (tsrelay8__DIORawInit2(0,2)) found=1;
  else if (tsrelay8__DIORawInit3(0,3)) found=1;
  if (found) dioctl_config_add(tsrelay8_dioctl_config);
  LogReturn("%d",0);
}

#define ARCH tsrelay8
#define ARCHTYPE ArchTypePC104
#define ARCHSUBTYPE ArchTypeNone

#define CLASS_INC "classinit2.h"
#include "classeach.h"

#include "archinit.h"
#define ARCH_LAST tsrelay8


// Author: Michael Schmidt (michael@embeddedARM.com)
// Copyright (c) 2012, Technologic Systems, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
