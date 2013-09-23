#include <stdio.h>
#include <stdlib.h>
#include "arch.h"
#include "ArchArch.h"
#include "ts8820DIORaw.h"
#include "ts8820Pin.h"
#include "ts8820ADCAIO.h"
#include "ts8820DACAIO.h"
#include "ts8820EDIO.h"
#include "PhysicalDIO.h"
#include "CacheBus.h"
extern char *ts8820_dioctl_config[];
#include "ts8820_dioctl_config.c"

Arch *ts8820BBArch;
Arch *ts8820ArchInit();
void *ts8820Function(int class,int inst);
Arch *ts8820ArchNextSubArch();

Arch ts8820Arch = {
  .Init = ts8820ArchInit,
  .Function = ts8820Function,
  .NextSubArch = ts8820ArchNextSubArch
};

Arch *ts8820ArchInit(int model) {
  static Arch *ts8820;
  if (ts8820) return ts8820;
  ts8820 = &ts8820Arch;
  dioctl_config_add2(Xts8820_dioctl_config,Xts8820_dioctl_config_len,Yts8820_dioctl_config_len);

  System *sys = SystemInit(0);
  if (!sys) return 0;
  Pin *pin = PinInit(0);
  if (!pin) return 0;
  int CN1_87 = sys->MapLookup(sys,ASCIIZLocal("CN1_87"));
  pin->ModeSet(pin,CN1_87,MODE_CLK);

  return ts8820;
}

// TO DO
// we must initialize any PC-104 boards to initialize in order, then
// return the first one here
Arch *ts8820ArchNextSubArch() {
  return 0;
}

ts8820DIORaw ts8820dio;
PhysicalDIO ts8820pdio;
unsigned char ts8820DIOCapabilities[32];
CacheBus ts8820DIOCacheBus;
ts8820Pin ts8820pin;
ts8820ADCAIO ts8820adc;
ts8820DACAIO ts8820dac;
ts8820EDIO ts8820edio;

unsigned ts8820DIOCacheBus_WO[3];
unsigned ts8820DIOCacheBus_IBit[3];
unsigned ts8820DIOCacheBus_OBit[3];
unsigned ts8820DIOCacheBus_icache[3];
unsigned ts8820DIOCacheBus_ocache[3];
unsigned ts8820DIOCacheBus_ocache0[3];

Bus *ts8820__BusInit0(Bus *bus,int inst) {
  ts8820DIOCacheBus_IBit[0] = 0x1FFF;
  ts8820DIOCacheBus_OBit[2] = 0x003F;
  ts8820DIOCacheBus.Length = 3;
  ts8820DIOCacheBus.Width = 16;
  ts8820DIOCacheBus.Offset = 4;
  ts8820DIOCacheBus.WO = ts8820DIOCacheBus_WO;
  ts8820DIOCacheBus.IBit = ts8820DIOCacheBus_IBit;
  ts8820DIOCacheBus.OBit = ts8820DIOCacheBus_OBit;
  ts8820DIOCacheBus.icache = ts8820DIOCacheBus_icache;
  ts8820DIOCacheBus.ocache = ts8820DIOCacheBus_ocache;
  ts8820DIOCacheBus.ocache0 = ts8820DIOCacheBus_ocache0;
  return CacheBusInit(&ts8820DIOCacheBus,BusInit(2));
}

int isme8820;
static int dio8820start;

static int dio8820start_calc() {
  DIORaw *dr;
  int i=0;
  if (dio8820start) return dio8820start;

  do {
    dr = DIORawInit(i++);
    if (dr && !isme8820) {
      dio8820start += dr->Count(dr);
    } else isme8820=0;
  } while (dr && !isme8820);
  return dio8820start;
}

Pin *ts8820__PinInit_1(Pin *pin0,int inst) {
  static int entered = 0;
  int i=0,start = 0;
  Pin *ret;
  DIORaw *dr;
  isme8820=0;
  do {
    dr = DIORawInit(i++);
    if (dr && !isme8820) {
      start += dr->Count(dr);
    } else isme8820=0;
  } while (dr && !isme8820);
  
  if (entered) return (Pin *)&ts8820pin;
  entered = 1;
  ret = ts8820PinInit(&ts8820pin,pin0,BusInit(2),start);
  entered = 0;
  return ret;
}

DIORaw *ts8820__DIORawInit0(DIORaw *dioraw,int inst) {
  isme8820=1;
  return ts8820DIORawInit(&ts8820dio,ts8820__BusInit0(0,0));
}

DIO *ts8820__DIOInit0(DIO *dio,int inst) {
  int i;
  for (i=0;i<27;i++) {
    ts8820DIOCapabilities[i] = DIO_NORMAL;
  }
  ts8820pdio.Caps = ts8820DIOCapabilities;
  return PhysicalDIOInit(&ts8820pdio,ts8820__BusInit0(0,0),
			 ts8820__DIORawInit0(0,0));
}

EDIO *ts8820__EDIOInit0(EDIO *edio,int inst) {
  return ts8820EDIOInit(&ts8820edio,BusInit(2),PinInit(0),
			dio8820start_calc());
}

AIO *ts8820__AIOInit0(AIO *dio,int inst) {
  return ts8820ADCAIOInit(&ts8820adc,BusInit(2));
}

AIO *ts8820__AIOInit1(AIO *dio,int inst) {
  return ts8820DACAIOInit(&ts8820dac,BusInit(2));
}

void *ts8820Function(int class,int inst) {
  if (class == ClassBus && inst == 0) return ts8820__BusInit0;
  if (class == ClassPin && inst == -1) return ts8820__PinInit_1;
  if (class == ClassDIORaw && inst == 0) return ts8820__DIORawInit0;
  if (class == ClassDIO && inst == 0) return ts8820__DIOInit0;
  if (class == ClassEDIO && inst == 0) return ts8820__EDIOInit0;
  if (class == ClassAIO && inst == 0) return ts8820__AIOInit0;
  if (class == ClassAIO && inst == 1) return ts8820__AIOInit1;
  return 0;
}

// Author: Michael Schmidt (michael@embeddedARM.com)
// Copyright (c) 2013, Technologic Systems, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
