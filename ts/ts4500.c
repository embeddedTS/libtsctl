#include "Thread.c"
#include "arch.h"
#include "MMapBus.c"
#include "Cavium2132SBus.c"
#include "Cavium2132SBusWindowBus.c"
#include "WBWindowBus.c"
#include "TSMuxBus.c"
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
#include "DummyBus.c"
#include "WBSPI.c"
#include "baudtab.h"
#include "ts4500.h"

extern ArchInfo ts4500_ArchInfo;
extern ArchInfo ts7552_ArchInfo;
extern ArchInfo ts7553_ArchInfo;
extern ArchInfo ts7558_ArchInfo;
extern ArchInfo ts81x0_ArchInfo;
extern ArchInfo ts8820_ArchInfo;
extern ArchInfo ts8900_ArchInfo;
extern ArchInfo tsrelay8_ArchInfo;
extern ArchInfo tsdio24_ArchInfo;

//ArrayAuto(ArchInfo*,aArchTypeCPU,ARR(&ts4500_ArchInfo,&ts7552_ArchInfo,
//				     &ts7553_ArchInfo,&ts7558_ArchInfo));
ArrayAuto(ArchInfo*,aArchTypeCPU,ARR(&ts4500_ArchInfo));
ArrayAuto(ArchInfo*,aArchTypeTSSocketBB,ARR(&ts81x0_ArchInfo,&ts8820_ArchInfo,&ts8900_ArchInfo));
//ArrayAuto(ArchInfo*,aArchTypePC104,ARR(&tsrelay8_ArchInfo,&tsdio24_ArchInfo));
ArrayAuto(ArchInfo*,aArchTypePC104,ARR(&tsrelay8_ArchInfo));
ArrayAuto(ArchInfo*,aArchTypeNone,ARR());

ArchInfo TS_ArchInfo = {
  .Instances= { 0,0,0,0,0,0,0,0,0,0 },
  .name="ts",
  .type=ArchTypeCPU,
  .subarches=ArrayL(aArchTypeCPU),
  .CANBusNum=0,
  .ArchInit=0,
  .SystemInit=0,
  .BusInit=0,
  .TimeInit=0,
  .PinInit=0,
  .DIORawInit=0,
  .DIOInit=0,
  .TWIInit=0,
  .CANInit=0,
  .SPIInit=0,
  //.EDIOInit=0,
  .AIOInit=0
};

DummyBus altmux;
MMapBus cpubus,testbus;
CacheBus ts4500DIOCacheBus,Cavium2132DIOCacheBus;
TSMuxBus muxbus;
WBWindowBus wbwin;
ts4500DIORaw ts4500DIORaw0;
Cavium2132DIORaw Cavium2132DIORaw0;
ts4500Pin ts4500Pin0;
PhysicalDIO ts4500DIO,Cavium2132DIO;
AggregateDIO DIO0;
DIOTWI TWI0;
SystemTime Time0;
Cavium2132Time Time1;
unsigned char ts4500DIOCapabilities[56];
CANConn CAN0conn[16];
SJA1000CAN CAN0;
WBSPI SPI0;
LocalSystem sys;

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
unsigned ts4500DIOCacheBus_WO[15];
unsigned ts4500DIOCacheBus_IBit[15];
unsigned ts4500DIOCacheBus_OBit[15];
unsigned ts4500DIOCacheBus_icache[15];
unsigned ts4500DIOCacheBus_ocache[15];
unsigned ts4500DIOCacheBus_ocache0[15];

char testbusdata[4096];

int ts4500_ArchInit() {
  LogEnter("");
  static int initialized = 0,value;
  if (initialized) LogReturn("%d",value);
  initialized = 1;
  int cpu = TSCPUGet();
  value = (cpu == CPU_CAVIUM);
  if (!value) LogReturn("%d",0);
  ThreadInit();
  dioctl_config_add(ts4500_dioctl_config);
  LogReturn("%d",1);
}

System *ts4500__SystemInit0(System *s,int inst) {
  return LocalSystemInit(&sys);
}
#define ts4500SystemInstances 1

Bus *ts4500__BusInit6(Bus *bus,int inst);
Bus *ts4500__BusInit0(Bus *bus,int inst) {
  MMapBusInit(&spibus,0x71000000,1);
  return Cavium2132SBusInit(&sbus,&spibus,ts4500__BusInit6(0,6));
}
Bus *ts4500__BusInit1(Bus *bus,int inst) {
  return MMapBusInit2(&testbus,testbusdata,1);
}
Bus *ts4500__BusInit8(Bus *bus,int inst);
Bus *ts4500__BusInit2(Bus *bus,int inst) {
  Bus *bus0 = ts4500__BusInit0(0,0);
  int modelid,fpgarev,muxpresent;
  bus0->Lock(bus0,0,0);
  modelid = bus0->Peek16(bus0,0x60);
  fpgarev = bus0->BitsGet16(bus0,0x62,3,0);
  bus0->Unlock(bus0,0,0);

  if ((modelid & 0x7000)==0x7000) return DummyBusInit(&altmux);
  if (fpgarev < 6) return DummyBusInit(&altmux);

  bus0->Lock(bus0,0,0);
  bus0->Poke16(bus0,0x18,0x55);
  muxpresent = (bus0->Peek16(bus0,0x18) == 0x55);
  bus0->Unlock(bus0,0,0);
  if (!muxpresent) return DummyBusInit(&altmux);

  // Unsupported bitstream present. Min of rev 6 required.
  return TSMuxBusInit(&muxbus,ts4500__BusInit8(0,8),0x20000,ts4500__BusInit8(0,8),
		      0x10000,ts4500__BusInit8(0,8),0);
}
Bus *ts4500__BusInit3(Bus *bus,int inst) {
  ts4500DIOCacheBus_IBit[0] = 0x3000;
  ts4500DIOCacheBus_IBit[2] = 0xF001;
  ts4500DIOCacheBus_IBit[3] = 0xFFFF;
  ts4500DIOCacheBus_IBit[6] = 0xFFFF;
  ts4500DIOCacheBus_IBit[11] = 0xFC00;
  ts4500DIOCacheBus_IBit[13] = 0xFFFF;
  ts4500DIOCacheBus_IBit[14] = 0xFF00;
  ts4500DIOCacheBus_OBit[0] = 0xCF00;
  ts4500DIOCacheBus_OBit[2] = 0x0FFE;
  ts4500DIOCacheBus_OBit[4] = 0xFFFF;
  ts4500DIOCacheBus_OBit[5] = 0xFFFF;
  ts4500DIOCacheBus_OBit[7] = 0xFFFF;
  ts4500DIOCacheBus_OBit[8] = 0xFFFF;
  ts4500DIOCacheBus_OBit[11] = 0x3FFF;
  ts4500DIOCacheBus_OBit[12] = 0xFFFF;
  ts4500DIOCacheBus_OBit[14] = 0x00FF;

  ts4500DIOCacheBus.Length=15;
  ts4500DIOCacheBus.Width=16;
  ts4500DIOCacheBus.Offset=0x62;
  ts4500DIOCacheBus.WO = ts4500DIOCacheBus_WO;
  ts4500DIOCacheBus.IBit = ts4500DIOCacheBus_IBit;
  ts4500DIOCacheBus.OBit = ts4500DIOCacheBus_OBit;
  ts4500DIOCacheBus.icache = ts4500DIOCacheBus_icache;
  ts4500DIOCacheBus.ocache = ts4500DIOCacheBus_ocache;
  ts4500DIOCacheBus.ocache0 = ts4500DIOCacheBus_ocache0;
  return CacheBusInit(&ts4500DIOCacheBus,ts4500__BusInit0(0,0));
}
Bus *ts4500__BusInit4(Bus *bus,int inst) {
  return MMapBusInit(&cpubus,0x76000000,1);
}
Bus *ts4500__BusInit5(Bus *bus,int inst) {
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
  return CacheBusInit(&Cavium2132DIOCacheBus,ts4500__BusInit6(0,6));
}
Bus *ts4500__BusInit6(Bus *bus,int inst) {
  return MMapBusInit(&gpiobus,0x7C000000,1);
}
Bus *ts4500__BusInit7(Bus *bus,int inst) {
  Bus *bus0 = ts4500__BusInit0(0,0);
  int modelid;
  bus0->Lock(bus0,0,0);
  modelid = bus0->Peek16(bus0,0x60);
  bus0->Unlock(bus0,0,0);

  if (modelid == 0x7558) {
    canbus.MemBase = 0x18;
  } else {
    canbus.MemBase = 0x50;
  }
  return Cavium2132SBusWindowBusInit(&canbus,ts4500__BusInit0(0,0));
}
Bus *ts4500__BusInit8(Bus *bus,int inst) {
  Bus *bus0 = ts4500__BusInit0(0,0);
  int modelid,fpgarev,muxpresent;
  bus0->Lock(bus0,0,0);
  modelid = bus0->Peek16(bus0,0x60);
  fpgarev = bus0->BitsGet16(bus0,0x62,3,0);
  bus0->Unlock(bus0,0,0);

  if ((modelid & 0x7000)==0x7000) return DummyBusInit(&altmux);
  if (fpgarev < 6) return DummyBusInit(&altmux);
  bus0->Lock(bus0,0,0);
  bus0->Poke16(bus0,0x18,0x55);
  muxpresent = (bus0->Peek16(bus0,0x18) == 0x55);
  bus0->Unlock(bus0,0,0);
  if (!muxpresent) return DummyBusInit(&altmux);

  return WBWindowBusInit(&wbwin,ts4500__BusInit0(0,0),0x18,0);
}
#define ts4500BusInstances 9

Time *ts4500__TimeInit0(Time *t,int inst) {
  return SystemTimeInit(&Time0);
}
Time *ts4500__TimeInit1(Time *t,int inst) {
  return Cavium2132TimeInit(&Time1);
}
#define ts4500TimeInstances 2

Pin *ts4500__PinInit0(Pin *pin,int inst) {
  return ts4500PinInit(&ts4500Pin0,ts4500__BusInit0(0,0),ts4500__BusInit4(0,4),
		       ts4500__BusInit8(0,8),0x20000);
}
#define ts4500PinInstances 1

DIORaw *ts4500__DIORawInit0(DIORaw *dioraw,int inst) {
  return ts4500DIORawInit(&ts4500DIORaw0,ts4500__BusInit3(0,3));
}
DIORaw *ts4500__DIORawInit1(DIORaw *dioraw,int inst) {
  return Cavium2132DIORawInit(&Cavium2132DIORaw0,ts4500__BusInit5(0,5));
}
#define ts4500DIORawInstances 2

DIO *ts4500__DIOInit0(DIO *dio,int inst) {
  return DIOInit0(&DIO0);
}
DIO *ts4500__DIOInit1(DIO *dio,int inst) {
  int i;

  ts4500DIO.Caps = ts4500DIOCapabilities;
  for (i=0;i<=52;i++) {
    ts4500DIOCapabilities[i] = DIO_NORMAL;
  }
  ts4500DIOCapabilities[54] = DIO_OUTPUT_ONLY;
  ts4500DIOCapabilities[55] = DIO_OUTPUT_ONLY;
  return PhysicalDIOInit(&ts4500DIO,ts4500__BusInit3(0,3),
			 ts4500__DIORawInit0(0,0));
}
DIO *ts4500__DIOInit2(DIO *dio,int inst) {
  Cavium2132DIO.Caps = Cavium2132DIOCapabilities;
  Cavium2132DIOCapabilities[13] = DIO_NORMAL;
  Cavium2132DIOCapabilities[14] = DIO_NORMAL;
  return PhysicalDIOInit(&Cavium2132DIO,ts4500__BusInit5(0,5),
			 ts4500__DIORawInit1(0,1));
}
#define ts4500DIOInstances 3

TWI *ts4500__TWIInit0(TWI *twi,int inst) {
  TWI0.TW_CLK=14+56;
  TWI0.TW_DAT=13+56;
  TWI0.Speed=1000000;
  TWI0.LockNum=1;
  return DIOTWIInit(&TWI0,ts4500__DIOInit0(0,0),ts4500__TimeInit0(0,0));
}
#define ts4500TWIInstances 1

int ts4500_CANBusNum[1] = { 7 };

CAN *ts4500__CANInit0(CAN *can,int inst) {
  Bus *bus0 = ts4500__BusInit0(0,0);
  int modelid;
  bus0->Lock(bus0,0,0);
  modelid = bus0->Peek16(bus0,0x60);
  bus0->Unlock(bus0,0,0);

  CAN0.LockBase = 2;
  CAN0.status = 0;

  if (modelid == 0x7558) {
    CAN0.CAN_TX = 61;
    CAN0.CAN_RX = 55;
  } else {
    CAN0.CAN_TX = 15;
    CAN0.CAN_RX = 16;
  }
  CAN0.D.conn = CAN0conn;
  CAN0.D.maxconn = 16;
  CAN0.D.nconn = 0;
  CAN0.D.txc = 0;
  CAN0.baud = 1000000;
  CAN0.baudparms = baudparms25;
  if (modelid == 0x7558) {
    CAN0.irq = 29;
  } else {
    CAN0.irq = 30;
  }
  return SJA1000CANInit(&CAN0,ts4500__BusInit7(0,7),PinInit(0),
			ts4500__TimeInit1(0,1));
}
#define ts4500CANInstances 1

static void ts4500SPIChipSelect(WBSPI *ob,unsigned num,int asserted) {
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

SPI *ts4500__SPIInit0(SPI *spi,int inst) {
  SPI0.LockNum = 7; // ???
  return WBSPIInit(&SPI0,ts4500__BusInit0(0,0),ts4500__BusInit0(0,0),
		   0x40,ts4500SPIChipSelect);
}

#define ts4500SPIInstances 1

#define ts4500EDIOInstances 0

#define ts4500AIOInstances 0

#ifndef ARCH
#define ARCH ts4500
#define ARCHTYPE ArchTypeCPU
#define ARCHSUBTYPE ArchTypeTSSocketBB
#endif

#define CLASS_INC "classinit2.h"
#include "classeach.h"

#include "archinit.h"
#define ARCH_LAST ts4500

// Author: Michael Schmidt (michael@embeddedARM.com)
// Copyright (c) 2012, Technologic Systems, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
