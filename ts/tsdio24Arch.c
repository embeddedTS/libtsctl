#include "arch.h"
#include "ArchArch.h"
#include "Time.h"
#include "Bus.h"
#include "Pin.h"
#include "CAN.h"
#include "DIORaw.h"
#include "DIO.h"
#include "TWI.h"
#include "System.h"
#include "CacheBus.h"
#include "tsDIO24DIORaw.h"
#include "DummyDIO.h"
#include "PhysicalDIO.h"
#include "Lock.h"
#include "tsdio24_dioctl_config.c"

Arch *tsdio24ArchInit();
void *tsdio24Function(int class,int inst);
Arch *tsdio24ArchNextSubArch();
void tsdio24NextSubArchSet(Arch *arch);

Arch tsdio24Arch = {
  .Init = tsdio24ArchInit,
  .Function = tsdio24Function,
  .NextSubArch = tsdio24ArchNextSubArch,
  .NextSubArchSet = tsdio24NextSubArchSet
};

int dio24present[4];

Arch *tsdio24ArchInit(int model) {
  static Arch *tsdio24;
  Bus *pc104;
  int i,val;

  if (tsdio24) return tsdio24;
  pc104 = BusInit(2);
  pc104->Lock(pc104,0,SHARED);
  for (i=0;i<4;i++) {
    val = pc104->Peek8(pc104,0x100+8*i);
    if (val == 0x54) dio24present[i] = 1;
  }
  pc104->Unlock(pc104,0,SHARED);
  if (dio24present[0] == 0 && dio24present[0] == 0 && dio24present[0] == 0 && dio24present[0] == 0) {
    return 0;
  }
  tsdio24 = &tsdio24Arch;
  dioctl_config_add2(Xtsdio24_dioctl_config,Xtsdio24_dioctl_config_len,Ytsdio24_dioctl_config_len);
  return tsdio24;
}

Arch *tsdio24Next;

Arch *tsdio24ArchNextSubArch() {
  return tsdio24Next;
}

void tsdio24NextSubArchSet(Arch *arch) {
  tsdio24Next = arch;
}

tsDIO24DIORaw dio24[4];
PhysicalDIO pdio24[4];
unsigned char DIO24DIOCapabilities[24];
CacheBus tsDIO24DIOCacheBus;
DummyDIO r8dummyDIO[4];

unsigned tsDIO24DIOCacheBus_WO[4];
unsigned tsDIO24DIOCacheBus_IBit[4];
unsigned tsDIO24DIOCacheBus_OBit[4];
unsigned tsDIO24DIOCacheBus_icache[4];
unsigned tsDIO24DIOCacheBus_ocache[4];
unsigned tsDIO24DIOCacheBus_ocache0[4];

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
  return CacheBusInit(&tsDIO24DIOCacheBus,BusInit(2));
}

DIORaw *tsdio24__DIORawInit3(DIORaw *dioraw0,int inst);
DIORaw *tsdio24__DIORawInit0(DIORaw *dioraw0,int inst) {
  if (!dio24present[0]) {
    return tsdio24__DIORawInit3(dioraw0,inst);
  }
  return tsDIO24DIORawInit(&dio24[inst],tsdio24__BusInit0(0,0),0x100+inst*8);
}
DIORaw *tsdio24__DIORawInit1(DIORaw *dioraw0,int inst) {
  if (!dio24present[1]) {
    return tsdio24__DIORawInit0(dioraw0,inst);
  }
  return tsDIO24DIORawInit(&dio24[inst],tsdio24__BusInit0(0,0),0x100+inst*8);
}
DIORaw *tsdio24__DIORawInit2(DIORaw *dioraw0,int inst) {
  if (!dio24present[2]) {
    return tsdio24__DIORawInit1(dioraw0,inst);
  }
  return tsDIO24DIORawInit(&dio24[inst],tsdio24__BusInit0(0,0),0x100+inst*8);
}
DIORaw *tsdio24__DIORawInit3(DIORaw *dioraw0,int inst) {
  if (!dio24present[3]) {
    return tsdio24__DIORawInit2(dioraw0,inst);
  }
  return tsDIO24DIORawInit(&dio24[inst],tsdio24__BusInit0(0,0),0x100+inst*8);
}

DIO *tsdio24__DIOInit0(DIO *dio,int inst) {
  int i;
  DIORaw *dioraw = tsdio24__DIORawInit0(0,inst);
  if (inst >= 0 && inst <= 3 && dio24present[inst]) {
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
    return PhysicalDIOInit(&pdio24[inst],tsdio24__BusInit0(0,0),dioraw);
  } else {
    return DummyDIOInit(&r8dummyDIO[inst],8);
  }
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

void *tsdio24Function(int class,int inst) {
  if (class == ClassBus && inst == 0) return tsdio24__BusInit0;
  if (class == ClassDIORaw && inst == 0) return tsdio24__DIORawInit0;
  if (class == ClassDIORaw && inst == 1) return tsdio24__DIORawInit1;
  if (class == ClassDIORaw && inst == 2) return tsdio24__DIORawInit2;
  if (class == ClassDIORaw && inst == 3) return tsdio24__DIORawInit3;
  if (class == ClassDIO && inst == 0) return tsdio24__DIOInit0;
  if (class == ClassDIO && inst == 1) return tsdio24__DIOInit1;
  if (class == ClassDIO && inst == 2) return tsdio24__DIOInit2;
  if (class == ClassDIO && inst == 3) return tsdio24__DIOInit3;
  return 0;
}

// Author: Michael Schmidt (michael@embeddedTS.com)
// Copyright (c) 2013-2022 Technologic Systems, Inc. dba embeddedTS, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
