#include "arch.h"
#include "ArchArch.h"
#include <stdio.h>
#include <stdlib.h>
#include "ts8900DIORaw.h"
#include "ts8900Pin.h"
#include "PhysicalDIO.h"
#include "CacheBus.h"
#include "PC104Bus.h"
extern char *ts8900_dioctl_config[];
#include "ts8900_dioctl_config.c"

Arch *ts8900ArchInit();
void *ts8900Function(int class,int inst);
Arch *ts8900ArchNextSubArch();
void ts8900ArchNextSubArchSet(Arch *arch);

Arch ts8900Arch = {
  .Init = ts8900ArchInit,
  .Function = ts8900Function,
  .NextSubArch = ts8900ArchNextSubArch,
  .NextSubArchSet = ts8900ArchNextSubArchSet
};

Arch *ts8900ArchInit() {
  static Arch *ts8900;
  if (ts8900) return ts8900;
  ts8900 = &ts8900Arch;
  dioctl_config_add2(Xts8900_dioctl_config,Xts8900_dioctl_config_len,Yts8900_dioctl_config_len);

  System *sys = SystemInit(0);
  if (!sys) return 0;
  Pin *pin = PinInit(0);
  if (!pin) return 0;
  int CN1_87 = sys->MapLookup(sys,ASCIIZLocal("CN1_87"));
  pin->ModeSet(pin,CN1_87,MODE_CLK);
  ArchPC104Init(&ts8900Arch);
  return ts8900;
}

Arch *ts8900Next;
Arch *ts8900ArchNextSubArch() {
  return ts8900Next;
}

void ts8900ArchNextSubArchSet(Arch *arch) {
  ts8900Next = arch;
}


ts8900DIORaw ts8900dio;
PhysicalDIO ts8900pdio;
unsigned char ts8900DIOCapabilities[41];
CacheBus ts8900DIOCacheBus;
ts8900Pin ts8900pin;
PC104Bus ts8900pc104bus;

unsigned ts8900DIOCacheBus_WO[8];
unsigned ts8900DIOCacheBus_IBit[8];
unsigned ts8900DIOCacheBus_OBit[8];
unsigned ts8900DIOCacheBus_icache[8];
unsigned ts8900DIOCacheBus_ocache[8];
unsigned ts8900DIOCacheBus_ocache0[8];

// 0x08 [ 4] [15:0]=GPIOEN[15:0]
// 0x0A [ 5] [8]=GPIOEN[16], [7:0]=ISAEN
// 0x0C [ 6] [15:0]=GPIODATA[15:0]
// 0x0E [ 7] [8]=GPIODATA[16], [7:0]=ISADATA[7:0]
// 0x10 [ 8] [15:0]=GPIODIR[15:0]
// 0x12 [ 9] [8]=GPIODIR[16], [7:0]=ISADIR[7:0]
// 0x14 [10] [15:0]=GPIOIN[15:0]
// 0x16 [11] [8]=GPIOIN[16], [7:0]=ISAIN[7:0]

// IBit
// 0x08 [ 4] 0x0000
// 0x0A [ 5] 0x0000
// 0x0C [ 6] 0x0000
// 0x0E [ 7] 0x0000
// 0x10 [ 8] 0x0000
// 0x12 [ 9] 0x0000
// 0x14 [10] 0xFFFF
// 0x16 [11] 0x01FF
// OBit
// 0x08 [ 4] 0xFFFF
// 0x0A [ 5] 0x01FF
// 0x0C [ 6] 0xFFFF
// 0x0E [ 7] 0x01FF
// 0x10 [ 8] 0xFFFF
// 0x12 [ 9] 0x01FF
// 0x14 [10] 0x0000
// 0x16 [11] 0x0000

static void ts8900PC104Lock(PC104Bus *bus,unsigned num) {
  static Bus *bus2=0;
  if (!bus2) bus2 = BusInit(2);
  //fprintf(stderr,"locked PC104 bus\n");
  bus2->Lock(bus2,0,0);
  bus2->Poke16(bus2,0x8,0);
  bus2->Poke16(bus2,0xA,0);
  bus2->Unlock(bus2,0,0);
}

Bus *ts8900__BusInit_1(Bus *bus,int inst) {
  return PC104BusInit(&ts8900pc104bus,bus,0x0800,bus,0,ts8900PC104Lock);
}

Bus *ts8900__BusInit0(Bus *bus,int inst) {
  ts8900DIOCacheBus_IBit[6] = 0xFFFF;
  ts8900DIOCacheBus_IBit[7] = 0x01FF;
  ts8900DIOCacheBus_OBit[0] = 0xFFFF;
  ts8900DIOCacheBus_OBit[1] = 0x01FF;
  ts8900DIOCacheBus_OBit[2] = 0xFFFF;
  ts8900DIOCacheBus_OBit[3] = 0x01FF;
  ts8900DIOCacheBus_OBit[4] = 0xFFFF;
  ts8900DIOCacheBus_OBit[5] = 0x01FF;
  ts8900DIOCacheBus.Length = 8;
  ts8900DIOCacheBus.Width = 16;
  ts8900DIOCacheBus.Offset = 8;
  ts8900DIOCacheBus.WO = ts8900DIOCacheBus_WO;
  ts8900DIOCacheBus.IBit = ts8900DIOCacheBus_IBit;
  ts8900DIOCacheBus.OBit = ts8900DIOCacheBus_OBit;
  ts8900DIOCacheBus.icache = ts8900DIOCacheBus_icache;
  ts8900DIOCacheBus.ocache = ts8900DIOCacheBus_ocache;
  ts8900DIOCacheBus.ocache0 = ts8900DIOCacheBus_ocache0;
  return CacheBusInit(&ts8900DIOCacheBus,BusInit(2));
}

int isme8900;

Pin *ts8900__PinInit_1(Pin *pin0,int inst) {
  int i=0,start=0;
  DIORaw *dr;
  isme8900=0;
  do {
    dr = DIORawInit(i++);
    if (dr && !isme8900) {
      start += dr->Count(dr);
    } else isme8900=0;
  } while (dr && !isme8900);
  return ts8900PinInit(&ts8900pin,pin0,BusInit(2),start);
}

DIORaw *ts8900__DIORawInit0(DIORaw *dioraw,int inst) {
  isme8900=1;
  return ts8900DIORawInit(&ts8900dio,ts8900__BusInit0(0,1));
}

DIO *ts8900__DIOInit0(DIO *dio,int inst) {
  int i;
  for (i=0;i<=7;i++) {
    ts8900DIOCapabilities[i] = DIO_CAN_INPUT;
  } 
  for (i=8;i<=15;i++) {
    ts8900DIOCapabilities[i] = DIO_OUTPUT_ONLY;
  } 
  for (i=16;i<41;i++) {
    ts8900DIOCapabilities[i] = DIO_NORMAL;
  }
  ts8900pdio.Caps = ts8900DIOCapabilities;
  return PhysicalDIOInit(&ts8900pdio,ts8900__BusInit0(0,1),
			 ts8900__DIORawInit0(0,0));
}

void *ts8900Function(int class,int inst) {
  if (class == ClassBus && inst == -1) return ts8900__BusInit_1;
  if (class == ClassBus && inst == 0) return ts8900__BusInit0;
  if (class == ClassPin && inst == -1) return ts8900__PinInit_1;
  if (class == ClassDIORaw && inst == 0) return ts8900__DIORawInit0;
  if (class == ClassDIO && inst == 0) return ts8900__DIOInit0;
}

// Author: Michael Schmidt (michael@embeddedARM.com)
// Copyright (c) 2013, Technologic Systems, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
