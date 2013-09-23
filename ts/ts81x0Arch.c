#include "arch.h"
#include "ArchArch.h"
#include "Time.h"
#include "Bus.h"
#include "Pin.h"
#include "CAN.h"
#include "DIORaw.h"
#include "DIO.h"
#include "TWI.h"
#include "ts81x0DIORaw.h"
#include "ts81x0Pin.h"
#include "PhysicalDIO.h"
#include "CacheBus.h"
extern char *ts8100_dioctl_config[];
#include "ts8100_dioctl_config.c"
extern char *ts8160_dioctl_config[];
#include "ts8160_dioctl_config.c"

Arch *ts81x0ArchInit();
void *ts81x0Function(int class,int inst);
Arch *ts81x0ArchNextSubArch();
void ts81x0ArchNextSubArchSet(Arch *arch);

Arch ts81x0Arch = {
  .Init = ts81x0ArchInit,
  .Function = ts81x0Function,
  .NextSubArch = ts81x0ArchNextSubArch,
  .NextSubArchSet = ts81x0ArchNextSubArchSet
};

Arch *ts81x0ArchInit(int model) {
  static Arch *ts81x0;
  if (ts81x0) return ts81x0;
  ts81x0 = &ts81x0Arch;
  switch (model) {
  case 0x8100: 
    dioctl_config_add2(Xts8100_dioctl_config,Xts8100_dioctl_config_len,Yts8100_dioctl_config_len); 
    break;
  case 0x8160: 
    dioctl_config_add2(Xts8160_dioctl_config,Xts8160_dioctl_config_len,Yts8160_dioctl_config_len); 
    break;
  }

  System *sys = SystemInit(0);
  if (!sys) return 0;
  Pin *pin = PinInit(0);
  if (!pin) return 0;
  int CN1_87 = sys->MapLookup(sys,ASCIIZLocal("CN1_87"));
  pin->ModeSet(pin,CN1_87,MODE_CLK);
  ArchPC104Init(&ts81x0Arch);
  return ts81x0;
}

Arch *ts81x0Next;
Arch *ts81x0ArchNextSubArch() {
  return ts81x0Next;
}

void ts81x0ArchNextSubArchSet(Arch *arch) {
  ts81x0Next = arch;
}

ts81x0DIORaw ts81x0dio;
PhysicalDIO ts81x0pdio;
unsigned char ts81x0DIOCapabilities[32];
CacheBus ts81x0DIOCacheBus;
ts81x0Pin ts81x0pin;

unsigned ts81x0DIOCacheBus_WO[8];
unsigned ts81x0DIOCacheBus_IBit[8];
unsigned ts81x0DIOCacheBus_OBit[8];
unsigned ts81x0DIOCacheBus_icache[8];
unsigned ts81x0DIOCacheBus_ocache[8];
unsigned ts81x0DIOCacheBus_ocache0[8];

Bus *ts81x0__BusInit0(Bus *bus,int inst) {
  ts81x0DIOCacheBus_IBit[6] = 0xFFFF;
  ts81x0DIOCacheBus_IBit[7] = 0x03FF;
  ts81x0DIOCacheBus_OBit[2] = 0xFFFF;
  ts81x0DIOCacheBus_OBit[3] = 0x03FF;
  ts81x0DIOCacheBus_OBit[4] = 0xFFFF;
  ts81x0DIOCacheBus_OBit[5] = 0x03FF;
  ts81x0DIOCacheBus.Length = 8;
  ts81x0DIOCacheBus.Width = 16;
  ts81x0DIOCacheBus.Offset = 0;
  ts81x0DIOCacheBus.WO = ts81x0DIOCacheBus_WO;
  ts81x0DIOCacheBus.IBit = ts81x0DIOCacheBus_IBit;
  ts81x0DIOCacheBus.OBit = ts81x0DIOCacheBus_OBit;
  ts81x0DIOCacheBus.icache = ts81x0DIOCacheBus_icache;
  ts81x0DIOCacheBus.ocache = ts81x0DIOCacheBus_ocache;
  ts81x0DIOCacheBus.ocache0 = ts81x0DIOCacheBus_ocache0;
  return CacheBusInit(&ts81x0DIOCacheBus,BusInit(2));
}

Pin *ts81x0__PinInit_1(Pin *pin0,int inst) {
  int CAN_TX1,CAN_TX2,CAN_RX1,CAN_RX2;
  CAN *can0,*can1=0;
  static Pin *ts81x0Pin0;

  if (ts81x0Pin0) return ts81x0Pin0;
  ts81x0Pin0 = pin0;
  pin0 = ts81x0PinInit(&ts81x0pin,pin0,BusInit(2));
  can0 = CANInit(0);
  int model = TSModelGet();
  if (model == 0x4700 || model == 0x4800) {
    // on 47xx where x != 00, the DMA controller is in this address
    // space and we absolutely do not want to mess with that!
    can1 = CANInit(1);
  }
  ts81x0PinPostInit(&ts81x0pin,can0 ? can0->CAN_TX : -1,
		    can1 ? can1->CAN_TX : -1,
		    can0 ? can0->CAN_RX : -1,
		    can1 ? can1->CAN_RX : -1);
  ts81x0Pin0 = pin0;
  return ts81x0Pin0;
}

DIORaw *ts81x0__DIORawInit0(DIORaw *dioraw,int inst) {
  return ts81x0DIORawInit(&ts81x0dio,ts81x0__BusInit0(0,0));
}

DIO *ts81x0__DIOInit0(DIO *dio,int inst) {
  int i;
  for (i=0;i<27;i++) {
    ts81x0DIOCapabilities[i] = DIO_NORMAL;
  }
  ts81x0pdio.Caps = ts81x0DIOCapabilities;
  return PhysicalDIOInit(&ts81x0pdio,ts81x0__BusInit0(0,0),
			 ts81x0__DIORawInit0(0,0));
}

void *ts81x0Function(int class,int inst) {
  if (class == ClassBus && inst == 0) return ts81x0__BusInit0; 
  if (class == ClassPin && inst == -1) return ts81x0__PinInit_1;
  if (class == ClassDIORaw && inst == 0) return ts81x0__DIORawInit0;
  if (class == ClassDIO && inst == 0) return ts81x0__DIOInit0;
  return 0;
}

// Author: Michael Schmidt (michael@embeddedARM.com)
// Copyright (c) 2013, Technologic Systems, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
