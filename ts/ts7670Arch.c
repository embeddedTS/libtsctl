#include "Thread.h"
#include <string.h>
#include "arch.h"
#include "ArchArch.h"
#include "DummyBus.h"
#include "MMapBus.h"
#include "LocalSystem.h"
#include "SystemTime.h"
#include "ts7670Pin.h"
#include "ts7670DIORaw.h"
#include "CacheBus.h"
#include "PhysicalDIO.h"
#include "AggregateDIO.h"
#include "DIOTWI.h"

/*
#include "SJA1000CAN.h"
*/
#include "ts4200.h"
//extern char *ts7670_dioctl_config[];
#include "ts7670_dioctl_config.c"

Arch *ts7670ArchInit();
void *ts7670Function(int class,int inst);
Arch *ts7670ArchNextSubArch();

Arch ts7670Arch = {
  .Init = ts7670ArchInit,
  .Function = ts7670Function,
  .NextSubArch = ts7670ArchNextSubArch
};

Arch *ts7670ArchInit() {
  static Arch *ts7670;
  if (ts7670) return ts7670;
  ts7670 = &ts7670Arch;
  dioctl_config_add2(Xts7670_dioctl_config,Xts7670_dioctl_config_len,Yts7670_dioctl_config_len); 

  return ts7670;
}

Arch *ts7670ArchNextSubArch() {
  return 0;
}

DummyBus altmux;
MMapBus ts7670GPIOBus, testbus;
LocalSystem ts7670sys;
SystemTime ts7670Time0;
ts7670Pin ts7670Pin0;
CacheBus ts7670DIOCacheBus;
ts7670DIORaw ts7670DIORaw0;
PhysicalDIO ts7670DIOA;
AggregateDIO ts7670DIO0;
unsigned char ts7670DIOCapabilitiesA[160];
DIOTWI ts7670TWI0;

unsigned ts7670DIOCacheBus_WO[147];
unsigned ts7670DIOCacheBus_IBit[147];
unsigned ts7670DIOCacheBus_OBit[147];
unsigned ts7670DIOCacheBus_icache[147];
unsigned ts7670DIOCacheBus_ocache[147];
unsigned ts7670DIOCacheBus_ocache0[147];

char testbusdata[4096];

void *ts7670__SystemInit0(void *s,int inst) {
  return LocalSystemInit(&ts7670sys);
}

Bus *ts7670__BusInit0(Bus *bus,int inst) {
  return MMapBusInit(&ts7670GPIOBus,0x80018000,1);
}
Bus *ts7670__BusInit1(Bus *bus,int inst) {
  return MMapBusInit2(&testbus,testbusdata,1);
}
Bus *ts7670__BusInit2(Bus *bus,int inst) {
  return DummyBusInit(&altmux);
}

Bus *ts7670__BusInit3(Bus *bus,int inst) {
  ts7670DIOCacheBus_WO[705-576]=0xFFFFFFFF;
  ts7670DIOCacheBus_WO[706-576]=0xFFFFFFFF;
  ts7670DIOCacheBus_WO[709-576]=0xFFFFFFFF;
  ts7670DIOCacheBus_WO[710-576]=0xFFFFFFFF;
  ts7670DIOCacheBus_WO[713-576]=0xFFFFFFFF;
  ts7670DIOCacheBus_WO[714-576]=0xFFFFFFFF;
  ts7670DIOCacheBus_WO[717-576]=0xFFFFFFFF;
  ts7670DIOCacheBus_WO[718-576]=0xFFFFFFFF;
  ts7670DIOCacheBus_WO[721-576]=0xFFFFFFFF;
  ts7670DIOCacheBus_WO[722-576]=0xFFFFFFFF;

  ts7670DIOCacheBus_WO[449-576]=0xFFFFFFFF;
  ts7670DIOCacheBus_WO[450-576]=0xFFFFFFFF;
  ts7670DIOCacheBus_WO[453-576]=0xFFFFFFFF;
  ts7670DIOCacheBus_WO[454-576]=0xFFFFFFFF;
  ts7670DIOCacheBus_WO[457-576]=0xFFFFFFFF;
  ts7670DIOCacheBus_WO[458-576]=0xFFFFFFFF;
  ts7670DIOCacheBus_WO[461-576]=0xFFFFFFFF;
  ts7670DIOCacheBus_WO[462-576]=0xFFFFFFFF;
  ts7670DIOCacheBus_WO[465-576]=0xFFFFFFFF;
  ts7670DIOCacheBus_WO[466-576]=0xFFFFFFFF;

  ts7670DIOCacheBus_IBit[704-576]=0xFFFFFFFF;
  ts7670DIOCacheBus_IBit[708-576]=0xFFFFFFFF;
  ts7670DIOCacheBus_IBit[712-576]=0xFFFFFFFF;
  ts7670DIOCacheBus_IBit[716-576]=0xFFFFFFFF;
  ts7670DIOCacheBus_IBit[720-576]=0xFFFFFFFF;
  ts7670DIOCacheBus_OBit[704-576]=0xFFFFFFFF;
  ts7670DIOCacheBus_OBit[708-576]=0xFFFFFFFF;
  ts7670DIOCacheBus_OBit[712-576]=0xFFFFFFFF;
  ts7670DIOCacheBus_OBit[716-576]=0xFFFFFFFF;
  ts7670DIOCacheBus_OBit[720-576]=0xFFFFFFFF;
  
  ts7670DIOCacheBus_IBit[576-576]=0xFFFFFFFF;
  ts7670DIOCacheBus_IBit[580-576]=0xFFFFFFFF;
  ts7670DIOCacheBus_IBit[584-576]=0xFFFFFFFF;
  ts7670DIOCacheBus_IBit[588-576]=0xFFFFFFFF;
  ts7670DIOCacheBus_IBit[592-576]=0xFFFFFFFF;
  ts7670DIOCacheBus_OBit[576-576]=0xFFFFFFFF;
  ts7670DIOCacheBus_OBit[580-576]=0xFFFFFFFF;
  ts7670DIOCacheBus_OBit[584-576]=0xFFFFFFFF;
  ts7670DIOCacheBus_OBit[588-576]=0xFFFFFFFF;
  ts7670DIOCacheBus_OBit[592-576]=0xFFFFFFFF;

  ts7670DIOCacheBus.Length=147;
  ts7670DIOCacheBus.Width=32;
  ts7670DIOCacheBus.Offset=576;
  ts7670DIOCacheBus.WO = ts7670DIOCacheBus_WO;
  ts7670DIOCacheBus.IBit = ts7670DIOCacheBus_IBit;
  ts7670DIOCacheBus.OBit = ts7670DIOCacheBus_OBit;
  ts7670DIOCacheBus.icache=ts7670DIOCacheBus_icache;
  ts7670DIOCacheBus.ocache=ts7670DIOCacheBus_ocache;
  ts7670DIOCacheBus.ocache0=ts7670DIOCacheBus_ocache0;
  return CacheBusInit(&ts7670DIOCacheBus,ts7670__BusInit0(0,0));
}

Time *ts7670__TimeInit0(Time *t,int inst) {
  return SystemTimeInit(&ts7670Time0);
}

Pin *ts7670__PinInit0(Pin *pin,int inst) {
  return ts7670PinInit(&ts7670Pin0,ts7670__BusInit0(0,0));
}

DIORaw *ts7670__DIORawInit0(DIORaw *dioraw,int inst) {
  return ts7670DIORawInit(&ts7670DIORaw0,ts7670__BusInit3(0,3));
}

DIO *ts7670__DIOInit0(DIO *dio,int inst) {
  return DIOInit0(&ts7670DIO0);
}

DIO *ts7670__DIOInit1(DIO *dio,int inst) {
  int i;

  for (i=0;i<160;i++) {
    ts7670DIOCapabilitiesA[i] = DIO_NORMAL;
  }
  ts7670DIOA.Caps = ts7670DIOCapabilitiesA;
  return PhysicalDIOInit(&ts7670DIOA,ts7670__BusInit3(0,3),
			 ts7670__DIORawInit0(0,0));
}

TWI *ts7670__TWIInit0(TWI *twi,int inst) {
  ts7670TWI0.TW_CLK=3*32+24;
  ts7670TWI0.TW_DAT=3*32+25;
  ts7670TWI0.Speed=400000;
  if (!ts7670TWI0.LockNum) ts7670TWI0.LockNum = ThreadMutexAllocate(1);
  return DIOTWIInit(&ts7670TWI0,ts7670__DIOInit0(0,0),ts7670__TimeInit0(0,0));
}

void *ts7670Function(int class,int inst) {
  switch(class) {
  case ClassSystem:
    switch (inst) {
    case 0: return ts7670__SystemInit0;
    default: return 0;
    }
  case ClassBus:
    switch (inst) {
    case 0: return ts7670__BusInit0;
    case 1: return ts7670__BusInit1;
    case 2: return ts7670__BusInit2;
    case 3: return ts7670__BusInit3;
    default: return 0;
    }
  case ClassTime:
    switch (inst) {
    case 0: return ts7670__TimeInit0;
    default: return 0;
    }
  case ClassPin:
    switch (inst) {
    case 0: return ts7670__PinInit0;
    default: return 0;
    }
  case ClassDIORaw:
    switch (inst) { 
    case 0: return ts7670__DIORawInit0;
    default: return 0;
    }
  case ClassDIO:
    switch (inst) {
    case 0: return ts7670__DIOInit0;
    case 1: return ts7670__DIOInit1;
    default: return 0;
    }
  case ClassTWI:
    switch (inst) {
    case 0: return ts7670__TWIInit0;
    default: return 0;
    }
  case ClassCAN:
    switch (inst) {
    default: return 0;
    }
  case ClassSPI:
    switch (inst) {
    default: return 0;
    }
  case ClassAIO:
    switch (inst) {
    default: return 0;
    }
  case ClassEDIO:
    switch (inst) {
    default: return 0;
    }
  default: return 0;
  }
}

// Author: Michael Schmidt (michael@embeddedARM.com)
// Copyright (c) 2013, Technologic Systems, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
