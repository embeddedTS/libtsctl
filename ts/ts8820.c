#include <stdio.h>
#include <stdlib.h>
#include "Time.h"
#include "Bus.h"
#include "Pin.h"
#include "CAN.h"
#include "DIORaw.h"
#include "DIO.h"
#include "TWI.h"
#include "ts8820DIORaw.c"
#include "ts8820Pin.c"
#include "ts8820ADCAIO.c"
#include "ts8820DACAIO.c"
#include "ts8820EDIO.c"
#include "PhysicalDIO.h"
#include "CacheBus.h"
#include "arch.h"

static ts8820DIORaw ts8820dio;
static PhysicalDIO ts8820pdio;
static unsigned char ts8820DIOCapabilities[32];
static CacheBus ts8820DIOCacheBus;
static ts8820Pin ts8820pin;
static ts8820ADCAIO ts8820adc;
static ts8820DACAIO ts8820dac;
static ts8820EDIO ts8820edio;

unsigned ts8820DIOCacheBus_WO[3];
unsigned ts8820DIOCacheBus_IBit[3];
unsigned ts8820DIOCacheBus_OBit[3];
unsigned ts8820DIOCacheBus_icache[3];
unsigned ts8820DIOCacheBus_ocache[3];
unsigned ts8820DIOCacheBus_ocache0[3];

int ts8820_ArchInit();

int ts8820_isSubArch(ArchType type) {
  return type == ArchTypePC104;
}


#define ts8820SystemInstances 0

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
#define ts8820BusInstances 1

#define ts8820TimeInstances 0

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

Pin *ts8820__PinInit0(Pin *pin0,int inst) {
  if (inst == -1) {
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
  return pin0;
}
#define ts8820PinInstances 1

DIORaw *ts8820__DIORawInit0(DIORaw *dioraw,int inst) {
  isme8820=1;
  return ts8820DIORawInit(&ts8820dio,ts8820__BusInit0(0,0));
}

#define ts8820DIORawInstances 1

DIO *ts8820__DIOInit0(DIO *dio,int inst) {
  int i;
  for (i=0;i<27;i++) {
    ts8820DIOCapabilities[i] = DIO_NORMAL;
  }
  ts8820pdio.Caps = ts8820DIOCapabilities;
  return PhysicalDIOInit(&ts8820pdio,ts8820__BusInit0(0,0),
			 ts8820__DIORawInit0(0,0));
}
#define ts8820DIOInstances 1

#define ts8820TWIInstances 0
int ts8820_CANBusNum[0];
#define ts8820CANInstances 0
#define ts8820SPIInstances 0

EDIO *ts8820__EDIOInit0(EDIO *edio,int inst) {
  return ts8820EDIOInit(&ts8820edio,BusInit(2),PinInit(0),
			dio8820start_calc());
}

#define ts8820EDIOInstances 1

AIO *ts8820__AIOInit0(AIO *dio,int inst) {
  return ts8820ADCAIOInit(&ts8820adc,BusInit(2));
}

AIO *ts8820__AIOInit1(AIO *dio,int inst) {
  return ts8820DACAIOInit(&ts8820dac,BusInit(2));
}

#define ts8820AIOInstances 2

#define ARCH ts8820
#define ARCHTYPE ArchTypeTSSocketBB
#define ARCHSUBTYPE ArchTypePC104
#define CLASS_INC "classinit2.h"
#include "classeach.h"

#include "archinit.h"
#define ARCH_LAST ts8820

int ts8820_ArchInit() {
  LogEnter("");
  static int found = 0, entered=0;
  if (found) LogReturn("%d",1);
  int model,ret;
  if (entered) return 0;
  entered=1;
  model = BaseBoardIdGet();
  entered=0;
  ret = (model == 0x8820);
  //Log(-1,"model=%04X",model);
  //Log(-1,"model=%04X",model);
  //LogReturn("%d",ret);
  found = (model == 0x8820);
  if (found) {
    Bus *bus = BusInit(0);
    if (!bus) return 0;

    dioctl_config_add(ts8820_dioctl_config);
    bus->Lock(bus,0,0);
    bus->BitSet16(bus,2,11); // enable 12.5Mhz base board clock
    // oops, this is TS-4700 only!!!
    // not sure any other TS-SOCKET board will even work, as this is the
    // only one i have found that even offers this functionality!
    bus->Unlock(bus,0,0);
  }
  LogReturn("0x%04X==0x8100?%d",model,found);
}

// Author: Michael Schmidt (michael@embeddedARM.com)
// Copyright (c) 2012, Technologic Systems, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
