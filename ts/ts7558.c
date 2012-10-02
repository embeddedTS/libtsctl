#include "Thread.c"
#include "MMapBus.c"
#include "Cavium2132SBus.c"
#include "Cavium2132SBusWindowBus.c"
#include "WBWindowBus.c"
#include "TSMuxBus.c"
//#include "PThreadLock.c"
#include "CacheBus.c"
#include "ts4500DIORaw.c"
#include "Cavium2132DIORaw.c"
#include "ts4500Pin.c"
#include "PhysicalDIO.c"
#include "AggregateDIO.c"
#include "DIOTWI.c"
#include "SystemTime.c"
#include "Cavium2132Time.c"
#include "SJA1000CAN.c"
#include "LocalSystem.c"
#include "WBSPI.c"
#include "baudtab.h"
#include "ts7558.h"
#include "arch.h"

#ifndef ARCH
int ModelId=0x7558;
#endif

// NOTE: This file is obsolete.  Use ts4500.c instead, as it will detect
// whether a TS-7558 is present or not, and adjust accordingly

// this arch is nearly identical to the TS-4500.
// main difference is Bus 7 is at a different base address
// CAN DIO numbers and IRQ is different as well
MMapBus cpubus,testbus;
CacheBus ts7558DIOCacheBus,Cavium2132DIOCacheBus;
TSMuxBus muxbus;
WBWindowBus wbwin;
ts4500DIORaw ts7558DIORaw0;
Cavium2132DIORaw Cavium2132DIORaw0;
ts4500Pin ts7558Pin0;
PhysicalDIO ts7558DIO,Cavium2132DIO;
AggregateDIO DIO0;
DIOTWI TWI0;
SystemTime Time0;
Cavium2132Time Time1;
unsigned char ts7558DIOCapabilities[56];
CANConn CAN0conn[16];
SJA1000CAN CAN0;
WBSPI SPI0;
System sys;

unsigned Cavium2132DIOCacheBus_WO[12];
unsigned Cavium2132DIOCacheBus_IBit[12];
unsigned Cavium2132DIOCacheBus_OBit[12];
unsigned Cavium2132DIOCacheBus_icache[12];
unsigned Cavium2132DIOCacheBus_ocache[12];
unsigned Cavium2132DIOCacheBus_ocache0[12];
unsigned char Cavium2132DIOCapabilities[32];

// Standard instances
// Bus 0 is whatever bus directly accesses the FPGA "syscon" registers
// For the TS-4500 this is the Cavium2132SBus
// Bus0

MMapBus spibus, gpiobus;
Cavium2132SBus sbus;
Cavium2132SBusWindowBus canbus;

// Bus1
unsigned ts7558DIOCacheBus_WO[15];
unsigned ts7558DIOCacheBus_IBit[15];
unsigned ts7558DIOCacheBus_OBit[15];
unsigned ts7558DIOCacheBus_icache[15];
unsigned ts7558DIOCacheBus_ocache[15];
unsigned ts7558DIOCacheBus_ocache0[15];

char testbusdata[4096];

void ts7558_ArchInit() {
  ThreadInit();
}

System *ts7558__SystemInit0(System *s,int inst) {
  return LocalSystemInit(&sys);
}
#define ts7558SystemInstances 1

Bus *ts7558__BusInit0(Bus *bus,int inst) {
  MMapBusInit(&spibus,0x71000000,1);
  return Cavium2132SBusInit(&sbus,&spibus,BusInit(6));
}
Bus *ts7558__BusInit1(Bus *bus,int inst) {
  return MMapBusInit2(&testbus,testbusdata,1);
}
Bus *ts7558__BusInit2(Bus *bus,int inst) {
  return TSMuxBusInit(&muxbus,BusInit(8),0x20000,BusInit(8),0x10000,
		      BusInit(8),0);
}
Bus *ts7558__BusInit3(Bus *bus,int inst) {
  ts7558DIOCacheBus_IBit[0] = 0x3000;
  ts7558DIOCacheBus_IBit[2] = 0xF001;
  ts7558DIOCacheBus_IBit[3] = 0xFFFF;
  ts7558DIOCacheBus_IBit[6] = 0xFFFF;
  ts7558DIOCacheBus_IBit[11] = 0xFC00;
  ts7558DIOCacheBus_IBit[13] = 0xFFFF;
  ts7558DIOCacheBus_IBit[14] = 0xFF00;
  ts7558DIOCacheBus_OBit[0] = 0xCF00;
  ts7558DIOCacheBus_OBit[2] = 0x0FFE;
  ts7558DIOCacheBus_OBit[4] = 0xFFFF;
  ts7558DIOCacheBus_OBit[5] = 0xFFFF;
  ts7558DIOCacheBus_OBit[7] = 0xFFFF;
  ts7558DIOCacheBus_OBit[8] = 0xFFFF;
  ts7558DIOCacheBus_OBit[11] = 0x3FFF;
  ts7558DIOCacheBus_OBit[12] = 0xFFFF;
  ts7558DIOCacheBus_OBit[14] = 0x00FF;
  
  ts7558DIOCacheBus.Length=15;
  ts7558DIOCacheBus.Width=16;
  ts7558DIOCacheBus.Offset=0x62;
  ts7558DIOCacheBus.WO = ts7558DIOCacheBus_WO;
  ts7558DIOCacheBus.IBit = ts7558DIOCacheBus_IBit;
  ts7558DIOCacheBus.OBit = ts7558DIOCacheBus_OBit;
  ts7558DIOCacheBus.icache = ts7558DIOCacheBus_icache;
  ts7558DIOCacheBus.ocache = ts7558DIOCacheBus_ocache;
  ts7558DIOCacheBus.ocache0 = ts7558DIOCacheBus_ocache0;
  return CacheBusInit(&ts7558DIOCacheBus,BusInit(0));
}
Bus *ts7558__BusInit4(Bus *bus,int inst) {
  return MMapBusInit(&cpubus,0x76000000,1);
}
Bus *ts7558__BusInit5(Bus *bus,int inst) {
  Cavium2132DIOCacheBus_IBit[1] = 0xFFFFFFFF;
  Cavium2132DIOCacheBus_OBit[0] = 0xFFFFFFFF;
  Cavium2132DIOCacheBus_OBit[2] = 0xFFFFFFFF;
  Cavium2132DIOCacheBus.Length=12;
  Cavium2132DIOCacheBus.Width=32;
  Cavium2132DIOCacheBus.Offset=0;
  Cavium2132DIOCacheBus.IBit = Cavium2132DIOCacheBus_IBit;
  Cavium2132DIOCacheBus.OBit = Cavium2132DIOCacheBus_OBit;
  Cavium2132DIOCacheBus.icache = Cavium2132DIOCacheBus_icache;
  Cavium2132DIOCacheBus.ocache = Cavium2132DIOCacheBus_ocache;
  Cavium2132DIOCacheBus.ocache0 = Cavium2132DIOCacheBus_ocache0;
  return CacheBusInit(&Cavium2132DIOCacheBus,BusInit(6));
}
Bus *ts7558__BusInit6(Bus *bus,int inst) {
  return MMapBusInit(&gpiobus,0x7C000000,1);
}
Bus *ts7558__BusInit7(Bus *bus,int inst) {
  canbus.MemBase = 0x18;
  return Cavium2132SBusWindowBusInit(&canbus,BusInit(0));
  //return WBWindowBusInit(&wbwin,BusInit(0),0x18,0);
}
Bus *ts7558__BusInit8(Bus *bus,int inst) {
  return WBWindowBusInit(&wbwin,BusInit(0),0x18,0);
}
#define ts7558BusInstances 9

Time *ts7558__TimeInit0(Time *t,int inst) {
  return SystemTimeInit(&Time0);
}
Time *ts7558__TimeInit1(Time *t,int inst) {
  return Cavium2132TimeInit(&Time1);
}
#define ts7558TimeInstances 2

Pin *ts7558__PinInit0(Pin *pin,int inst) {
  return ts4500PinInit(&ts7558Pin0,BusInit(0),BusInit(4),BusInit(8),0x20000);
}
#define ts7558PinInstances 1

DIORaw *ts7558__DIORawInit0(DIORaw *dioraw,int inst) {
  return ts4500DIORawInit(&ts7558DIORaw0,BusInit(3));
}
DIORaw *ts7558__DIORawInit1(DIORaw *dioraw,int inst) {
  return Cavium2132DIORawInit(&Cavium2132DIORaw0,BusInit(5));
}
#define ts7558DIORawInstances 2

DIO *ts7558__DIOInit0(DIO *dio,int inst) {
  return DIOInit0(&DIO0);
}
DIO *ts7558__DIOInit1(DIO *dio,int inst) {
  int i;
  
  ts7558DIO.Caps = ts7558DIOCapabilities;
  for (i=0;i<=52;i++) {
    ts7558DIOCapabilities[i] = DIO_NORMAL;
  }
  ts7558DIOCapabilities[54] = DIO_OUTPUT_ONLY;
  ts7558DIOCapabilities[55] = DIO_OUTPUT_ONLY;
  return PhysicalDIOInit(&ts7558DIO,BusInit(3),DIORawInit(0));
}
DIO *ts7558__DIOInit2(DIO *dio,int inst) {
  Cavium2132DIO.Caps = Cavium2132DIOCapabilities;
  Cavium2132DIOCapabilities[13] = DIO_NORMAL;
  Cavium2132DIOCapabilities[14] = DIO_NORMAL;
  return PhysicalDIOInit(&Cavium2132DIO,BusInit(5),DIORawInit(1));
}
#define ts7558DIOInstances 3

TWI *ts7558__TWIInit0(TWI *twi,int inst) {
  TWI0.TW_CLK=14+56;
  TWI0.TW_DAT=13+56;
  TWI0.Speed=1000000;
  TWI0.LockNum=1;
  return DIOTWIInit(&TWI0,DIOInit(0),TimeInit(0));
}
#define ts7558TWIInstances 1

int CANBusNum[1] = { 7 };

CAN *ts7558__CANInit0(CAN *can,int inst) {
  CAN0.LockBase = 2;
  CAN0.status = 0;
  CAN0.CAN_TX = 61;
  CAN0.CAN_RX = 55;
  CAN0.D.conn = CAN0conn;
  CAN0.D.maxconn = 16;
  CAN0.D.nconn = 0;
  CAN0.D.txc = 0;
  CAN0.baud = 1000000;
  CAN0.baudparms = baudparms25;
  CAN0.irq = 29;
  return SJA1000CANInit(&CAN0,BusInit(7),PinInit(0),TimeInit(1));
}
#define ts7558CANInstances 1

static void ts7558SPIChipSelect(WBSPI *ob,unsigned num,int asserted) {
  if (num > 3) return;
  if (!asserted) return; // core will do this automatically
  if (num == 0) num = 1; else if (num == 1) num = 0;
  ob->bus->Lock(ob->bus,0,0);
  ob->bus->Poke16(ob->bus,ob->offset,
		  (ob->bus->Peek16(ob->bus,ob->offset) & 0xFC7F)
		       | (num << 8) /*| (1 << 7)*/);
  ob->bus->Unlock(ob->bus,0,0);
  return;
}

SPI *ts7558__SPIInit0(SPI *spi,int inst) {
  SPI0.LockNum = 7; // ???
  return WBSPIInit(&SPI0,BusInit(0),BusInit(0),0x40,ts7558SPIChipSelect);
}

#define ts7558SPIInstances 1

//#define ts7558EDIOInstances

#define ts7558AIOInstances 0

#ifndef ARCH
#define ARCH ts7558
#endif

#define CLASS_INC "classinit2.h"
#include "classeach.h"

#include "archinit.h"
#define ARCH_LAST ts7558

// Author: Michael Schmidt (michael@embeddedARM.com)
// Copyright (c) 2012, Technologic Systems, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
