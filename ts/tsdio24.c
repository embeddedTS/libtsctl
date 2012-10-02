#include "Time.h"
#include "Bus.h"
#include "Pin.h"
#include "CAN.h"
#include "DIORaw.h"
#include "DIO.h"
#include "TWI.h"
#include "CacheBus.h"
#include "tsDIO24DIORaw.c"
#include "DummyDIO.c"
#include "PhysicalDIO.h"
#include "arch.h"

static tsDIO24DIORaw dio24[4];
static PhysicalDIO pdio24[4];
static unsigned char DIO24DIOCapabilities[24];
static CacheBus tsDIO24DIOCacheBus;
static DummyDIO r8dummyDIO[4];

unsigned tsDIO24DIOCacheBus_WO[4];
unsigned tsDIO24DIOCacheBus_IBit[4];
unsigned tsDIO24DIOCacheBus_OBit[4];
unsigned tsDIO24DIOCacheBus_icache[4];
unsigned tsDIO24DIOCacheBus_ocache[4];
unsigned tsDIO24DIOCacheBus_ocache0[4];

#define tsdio24SystemInstances 0

Bus *tsdio24__BusInit0(Bus *bus,int inst) {
  tsDIO24DIOCacheBus_IBit[1] = 0xFF;
  tsDIO24DIOCacheBus_IBit[2] = 0xFF;
  tsDIO24DIOCacheBus_IBit[3] = 0xFF;
  tsDIO24DIOCacheBus_OBit[0] = 3;
  tsDIO24DIOCacheBus_OBit[1] = 0xFF;
  tsDIO24DIOCacheBus_OBit[2] = 0xFF;
  tsDIO24DIOCacheBus_OBit[3] = 0xFF;
  tsDIO24DIOCacheBus.Length = 4;
  tsDIO24DIOCacheBus.Width = 8;
  tsDIO24DIOCacheBus.Offset = 4;
  tsDIO24DIOCacheBus.WO = tsDIO24DIOCacheBus_WO;
  tsDIO24DIOCacheBus.IBit = tsDIO24DIOCacheBus_IBit;
  tsDIO24DIOCacheBus.OBit = tsDIO24DIOCacheBus_OBit;
  tsDIO24DIOCacheBus.icache = tsDIO24DIOCacheBus_icache;
  tsDIO24DIOCacheBus.ocache = tsDIO24DIOCacheBus_ocache;
  tsDIO24DIOCacheBus.ocache0 = tsDIO24DIOCacheBus_ocache0;
  return CacheBusInit(&tsDIO24DIOCacheBus,tsdio24_ArchInfo.parent->BusInit(0,0));
}
#define tsdio24BusInstances 1

#define tsdio24TimeInstances 0
#define tsdio24PinInstances 0

DIORaw *tsdio24__DIORawInit0(DIORaw *dioraw0,int inst) {
  Bus *muxbus = BusInit(2);
  int i=0;
  DIORaw *dioraw;

  if (inst >= 0 && inst <= 3) {
    muxbus->Lock(muxbus,0,0);
    muxbus->BitClear16(muxbus,2,9); // make sure ISA reset de-asserted
    muxbus->Unlock(muxbus,0,0);
    dioraw = tsDIO24DIORawInit(&dio24[i],tsdio24__BusInit0(0,0),0x100+inst*8);
    if (dioraw) {
      return dioraw;
    } else {
      return 0;
    }
  }
  return dioraw0;
}
DIORaw *tsdio24__DIORawInit1(DIORaw *dioraw0,int inst) {
  return tsdio24__DIORawInit0(dioraw0,inst);
}
DIORaw *tsdio24__DIORawInit2(DIORaw *dioraw0,int inst) {
  return tsdio24__DIORawInit0(dioraw0,inst);
}
DIORaw *tsdio24__DIORawInit3(DIORaw *dioraw0,int inst) {
  return tsdio24__DIORawInit0(dioraw0,inst);
}
#define tsdio24DIORawInstances 4

DIO *tsdio24__DIOInit0(DIO *dio,int inst) {
  DIORaw *dioraw;
  int i;
  if (inst >= 0 && inst <= 3) {
    dioraw = tsdio24__DIORawInit0(0,inst);
    if (dioraw) {
      for (i=0;i<4;i++) {
	DIO24DIOCapabilities[i] = DIO_OUTPUT_ONLY;
      }
      for (i=4;i<8;i++) {
	DIO24DIOCapabilities[i] = DIO_CAN_DRIVE_LOW;
      }
      for (i=8;i<24;i++) {
	DIO24DIOCapabilities[i] = DIO_NORMAL;
      }
      pdio24[inst].Caps = DIO24DIOCapabilities;
      //return PhysicalDIOInit(&pdio24[inst],BusInit(2),dioraw);
      return PhysicalDIOInit(&pdio24[inst],tsdio24__BusInit0(0,0),dioraw);
    } else {
      return DummyDIOInit(&r8dummyDIO[inst],8);
    }
  }
  return dio;
}
DIO *tsdio24__DIOInit1(DIO *dio,int inst) {
  return tsdio24__DIOInit0(dio,inst);
}
DIO *tsdio24__DIOInit2(DIO *dio,int inst) {
  return tsdio24__DIOInit0(dio,inst);
}
DIO *tsdio24__DIOInit3(DIO *dio,int inst) {
  return tsdio24__DIOInit0(dio,inst);
}
#define tsdio24DIOInstances 4

#define tsdio24TWIInstances 0
int tsdio24_CANBusNum[0];
#define tsdio24CANInstances 0
#define tsdio24SPIInstances 0
#define tsdio24EDIOInstances 0
#define tsdio24AIOInstances 0

int tsdio24_ArchInit() {
  LogEnter("");
  int i;
  static int found = 0;
  if (found) LogReturn("%d",1);
  if (!tsdio24_ArchInfo.parent) return 0;
  if (tsdio24__DIORawInit0(0,0)) found = 1;
  else if (tsdio24__DIORawInit1(0,1)) found = 1;
  else if (tsdio24__DIORawInit2(0,2)) found = 1;
  else if (tsdio24__DIORawInit3(0,3)) found = 1;
  if (found) dioctl_config_add(tsdio24_dioctl_config);
  LogReturn("%d",found);
}

#define ARCH tsdio24
#define ARCHTYPE ArchTypePC104
#define ARCHSUBTYPE ArchTypeNone
#define CLASS_INC "classinit2.h"
#include "classeach.h"

#include "archinit.h"
#define ARCH_LAST tsdio24

// Author: Michael Schmidt (michael@embeddedARM.com)
// Copyright (c) 2012, Technologic Systems, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
