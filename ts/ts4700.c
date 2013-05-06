//#include "MarvellPXA166TWI.c"
#include "Thread.c"
#include "ts4700.h"
#include "DummyBus.c"
#include "MMapBus.c"
#include "SystemTime.c"
#include "AggregateDIO.c"
#include "DIOTWI.c"
#include "PhysicalDIO.c"
#include "ts4700Pin.c"
#include "ts4700DIORaw.c"
#include "TSMuxBus.c"
#include "MarvellPXA166DIORaw.c"
#include "CacheBus.c"
#include "SJA1000CAN.c"
#include "LocalSystem.c"
#include "WBSPI.c"
#include "baudtab.h"
#include "arch.h"
#include "Array.h"

// object hierarchy
DummyBus altmux;
MMapBus MarvellPXA166DIOBus, ts4700DIOBus, ts4700CANBus, testbus, twiregs,
  mfpregs, mux8bus, mux16bus, spi8bus, spi16bus;
TSMuxBus muxbus;
CacheBus MarvellPXA166DIOCacheBus, ts4700DIOCacheBus;
MarvellPXA166DIORaw MarvellPXA166DIORaw0;
ts4700DIORaw ts4700DIORaw0;
PhysicalDIO MarvellPXA166DIO, ts4700DIO;
AggregateDIO ts4700DIO0;
SystemTime ts4700Time0;
//MarvellPXA166TWI ts4700TWI0;
DIOTWI ts4700TWI0;
SJA1000CAN ts4700CAN0;
ts4700Pin ts4700Pin0;
WBSPI ts4700SPI0;
LocalSystem ts4700sys;

CANConn ts4700CAN0conn[16];

#define ts4700DIOCacheBusLength 12
unsigned ts4700DIOCacheBus_WO[ts4700DIOCacheBusLength];
unsigned ts4700DIOCacheBus_IBit[ts4700DIOCacheBusLength];
unsigned ts4700DIOCacheBus_OBit[ts4700DIOCacheBusLength];
unsigned ts4700DIOCacheBus_icache[ts4700DIOCacheBusLength];
unsigned ts4700DIOCacheBus_ocache[ts4700DIOCacheBusLength];
unsigned ts4700DIOCacheBus_ocache0[ts4700DIOCacheBusLength];

#define MarvellPXA166DIOCacheBusLength 0x4A
unsigned MarvellPXA166DIOCacheBus_WO[MarvellPXA166DIOCacheBusLength];
unsigned MarvellPXA166DIOCacheBus_IBit[MarvellPXA166DIOCacheBusLength];
unsigned MarvellPXA166DIOCacheBus_OBit[MarvellPXA166DIOCacheBusLength];
unsigned MarvellPXA166DIOCacheBus_icache[MarvellPXA166DIOCacheBusLength];
unsigned MarvellPXA166DIOCacheBus_ocache[MarvellPXA166DIOCacheBusLength];
unsigned MarvellPXA166DIOCacheBus_ocache0[MarvellPXA166DIOCacheBusLength];

unsigned char MarvellPXA166DIOCapabilities[128];
unsigned char ts4700DIOCapabilities[62];

char testbusdata[4096];

int ts4700_ArchInit() {
  LogEnter("");
  static int initialized = 0,value;
  if (initialized) LogReturn("%d",value);
  initialized = 1;
  int model = TSModelGet();
  value = ((model & 0xFF00) == 0x4700);
  if (!value) LogReturn("%d",0);
  ThreadInit();
  dioctl_config_add(ts4700_dioctl_config);
  LogReturn("%d",1);
}

int ts4700_isSubArch(ArchType type) {
  return type == ArchTypeTSSocketBB;
}

System *ts4700__SystemInit0(System *s,int inst) {
  return LocalSystemInit(&ts4700sys);
}
#define ts4700SystemInstances 1

Bus *ts4700__BusInit0(Bus *bus,int inst) {
  return MMapBusInit(&ts4700DIOBus,0x80004000,1);
}
Bus *ts4700__BusInit1(Bus *bus,int inst) {
  return MMapBusInit2(&testbus,testbusdata,1);
}
Bus *ts4700__BusInit9(Bus *bus,int inst);
Bus *ts4700__BusInit10(Bus *bus,int inst);
Bus *ts4700__BusInit2(Bus *bus,int inst) {
  if (!BaseBoardMuxBusSupport()) return DummyBusInit(&altmux);
  return TSMuxBusInit(&muxbus,ts4700__BusInit0(0,0),0x4,
		      ts4700__BusInit9(0,9),0,ts4700__BusInit10(0,10),0);
}
Bus *ts4700__BusInit3(Bus *bus,int inst) {
  return MMapBusInit(&MarvellPXA166DIOBus,0xD4019000,1);
}
Bus *ts4700__BusInit4(Bus *bus,int inst) {
  return MMapBusInit(&ts4700CANBus,0x81004c00,1);
}
Bus *ts4700__BusInit5(Bus *bus,int inst) {
  ts4700DIOCacheBus_IBit[8] = 0x7FFF;
  ts4700DIOCacheBus_IBit[9] = 0x7FF;
  ts4700DIOCacheBus_IBit[10] = 0xFFFF;
  ts4700DIOCacheBus_IBit[11] = 0xFFF;
  ts4700DIOCacheBus_OBit[0] = 0x7FFF;
  ts4700DIOCacheBus_OBit[1] = 0x1FFF;
  ts4700DIOCacheBus_OBit[2] = 0xFFFF;
  ts4700DIOCacheBus_OBit[3] = 0xFFF;
  ts4700DIOCacheBus_OBit[4] = 0x7FFF;
  ts4700DIOCacheBus_OBit[5] = 0x7FF;
  ts4700DIOCacheBus_OBit[6] = 0xFFFF;
  ts4700DIOCacheBus_OBit[7] = 0xFFF;

  ts4700DIOCacheBus.Length=ts4700DIOCacheBusLength;
  ts4700DIOCacheBus.Width=16;
  ts4700DIOCacheBus.Offset=0x10;
  ts4700DIOCacheBus.WO=ts4700DIOCacheBus_WO;
  ts4700DIOCacheBus.IBit=ts4700DIOCacheBus_IBit;
  ts4700DIOCacheBus.OBit=ts4700DIOCacheBus_OBit;
  ts4700DIOCacheBus.icache=ts4700DIOCacheBus_icache;
  ts4700DIOCacheBus.ocache=ts4700DIOCacheBus_ocache;
  ts4700DIOCacheBus.ocache0=ts4700DIOCacheBus_ocache0;
  return CacheBusInit(&ts4700DIOCacheBus,ts4700__BusInit0(0,0));
}
Bus *ts4700__BusInit6(Bus *bus,int inst) {
  MarvellPXA166DIOCacheBus_IBit[0] = 0xFFFFFFFF;
  MarvellPXA166DIOCacheBus_IBit[1] = 0xFFFFFFFF;
  MarvellPXA166DIOCacheBus_IBit[2] = 0xFFFFFFFF;
  MarvellPXA166DIOCacheBus_IBit[64] = 0xFFFFFFFF;
  MarvellPXA166DIOCacheBus_OBit[3] = 0xFFFFFFFF;
  MarvellPXA166DIOCacheBus_OBit[4] = 0xFFFFFFFF;
  MarvellPXA166DIOCacheBus_OBit[5] = 0xFFFFFFFF;
  MarvellPXA166DIOCacheBus_OBit[67] = 0xFFFFFFFF;
  MarvellPXA166DIOCacheBus_WO[6] = 0xFFFFFFFF;
  MarvellPXA166DIOCacheBus_WO[7] = 0xFFFFFFFF;
  MarvellPXA166DIOCacheBus_WO[8] = 0xFFFFFFFF;
  MarvellPXA166DIOCacheBus_WO[70] = 0xFFFFFFFF;
  MarvellPXA166DIOCacheBus_WO[9] = 0xFFFFFFFF;
  MarvellPXA166DIOCacheBus_WO[10] = 0xFFFFFFFF;
  MarvellPXA166DIOCacheBus_WO[11] = 0xFFFFFFFF;
  MarvellPXA166DIOCacheBus_WO[73] = 0xFFFFFFFF;
  
  MarvellPXA166DIOCacheBus.Length=MarvellPXA166DIOCacheBusLength;
  MarvellPXA166DIOCacheBus.Width=32;
  MarvellPXA166DIOCacheBus.Offset=0;
  MarvellPXA166DIOCacheBus.WO=MarvellPXA166DIOCacheBus_WO;
  MarvellPXA166DIOCacheBus.IBit=MarvellPXA166DIOCacheBus_IBit;
  MarvellPXA166DIOCacheBus.OBit=MarvellPXA166DIOCacheBus_OBit;
  MarvellPXA166DIOCacheBus.icache=MarvellPXA166DIOCacheBus_icache;
  MarvellPXA166DIOCacheBus.ocache=MarvellPXA166DIOCacheBus_ocache;
  MarvellPXA166DIOCacheBus.ocache0=MarvellPXA166DIOCacheBus_ocache0;
  
  return CacheBusInit(&MarvellPXA166DIOCacheBus,ts4700__BusInit3(0,3));
}
Bus *ts4700__BusInit7(Bus *bus,int inst) { // CPU TWI regs
  return MMapBusInit(&twiregs,0xD4025008,1); // 0xD4011008
}
Bus *ts4700__BusInit8(Bus *bus,int inst) { // CPU MFP regs
  return MMapBusInit(&mfpregs,0xD401E000,1); // 0xD4011008
}
Bus *ts4700__BusInit9(Bus *bus,int inst) {
  return MMapBusInit(&mux8bus,0x81008000,8);
}
Bus *ts4700__BusInit10(Bus *bus,int inst) {
  return MMapBusInit(&mux16bus,0x80008000,8);
}
Bus *ts4700__BusInit11(Bus *bus,int inst) {
  return MMapBusInit(&spi8bus,0x81004800,1);
}
Bus *ts4700__BusInit12(Bus *bus,int inst) {
  return MMapBusInit(&spi16bus,0x80004800,1);
}
#define ts4700BusInstances 13

Time *ts4700__TimeInit0(Time *t,int inst) {
  return SystemTimeInit(&ts4700Time0);
}
#define ts4700TimeInstances 1

Pin *ts4700__PinInit0(Pin *pin,int inst) {
  return ts4700PinInit(&ts4700Pin0,ts4700__BusInit0(0,0),ts4700__BusInit8(0,8));
}
#define ts4700PinInstances 1

DIORaw *ts4700__DIORawInit0(DIORaw *dioraw,int inst) {
  return ts4700DIORawInit(&ts4700DIORaw0,ts4700__BusInit5(0,5));
}
DIORaw *ts4700__DIORawInit1(DIORaw *dioraw,int inst) {
  return MarvellPXA166DIORawInit(&MarvellPXA166DIORaw0,ts4700__BusInit6(0,6));
}
#define ts4700DIORawInstances 2

DIO *ts4700__DIOInit0(DIO *dio,int inst) {
  LogEnter("%p,%d",dio,inst);
  DIO *ret = DIOInit0((void *)&ts4700DIO0);
  LogReturn("%p",ret);
}
DIO *ts4700__DIOInit1(DIO *dio,int inst) {
  int i,n;
  DIORaw *raw = ts4700__DIORawInit0(0,0);

  if (raw) {
    n = raw->Count(raw);
    ts4700DIO.Caps = ts4700DIOCapabilities;
    for (i=0;i<n;i++) {
      ts4700DIOCapabilities[i] = DIO_NORMAL;
    }
  }
  return PhysicalDIOInit(&ts4700DIO,ts4700__BusInit5(0,5),raw);
}
DIO *ts4700__DIOInit2(DIO *dio,int inst) {
  int i,n;
  DIORaw *raw = ts4700__DIORawInit1(0,1);

  if (raw) {
    n = raw->Count(raw);
    MarvellPXA166DIO.Caps = MarvellPXA166DIOCapabilities;
    for (i=0;i<n;i++) {
      MarvellPXA166DIOCapabilities[i] = DIO_NORMAL;
    }
    MarvellPXA166DIOCapabilities[51] = 0; // FPGA drives a clock on this pin!
  }
  return PhysicalDIOInit(&MarvellPXA166DIO,ts4700__BusInit6(0,6),raw);
}
#define ts4700DIOInstances 3

TWI *ts4700__TWIInit0(TWI *twi,int inst) {
  ts4700TWI0.TW_CLK=150;
  ts4700TWI0.TW_DAT=149;
  ts4700TWI0.Speed=100000;
  ts4700TWI0.LockNum=1;
  return DIOTWIInit(&ts4700TWI0,ts4700__DIOInit0(0,0),ts4700__TimeInit0(0,0));
}
#define ts4700TWIInstances 1

int ts4700_CANBusNum[1] = { 4 };

CAN *ts4700__CANInit0(CAN *can,int inst) {
  ts4700CAN0.LockBase = 2;
  ts4700CAN0.status = 0;
  ts4700CAN0.CAN_TX = 15;
  ts4700CAN0.CAN_RX = 16;
  ts4700CAN0.D.conn = ts4700CAN0conn;
  ts4700CAN0.D.maxconn = 16;
  ts4700CAN0.D.nconn = 0;
  ts4700CAN0.D.txc = 0;
  ts4700CAN0.baud = 1000000;
  ts4700CAN0.baudparms = baudparms25;
  ts4700CAN0.irq = 65;
  return SJA1000CANInit(&ts4700CAN0,ts4700__BusInit4(0,4),PinInit(0),
			ts4700__TimeInit0(0,0));
}
#define ts4700CANInstances 1

static void ts4700SPIChipSelect(WBSPI *ob,unsigned num,int asserted) {
  if (num > 0) {
    // CS1 = CN2_64 = DIO 101
    // CS2 = CN2_66 = DIO 100
    // CS3 = CN2_68 = DIO 99
    static DIO *dio = 0;
    if (!dio) dio = ts4700__DIOInit0(0,0);
    switch (num) {
    case 1: dio->SetAsync(dio,101,asserted?LOW:INPUT); break;
    case 2: dio->SetAsync(dio,101,asserted?LOW:INPUT); break;
    case 3: dio->SetAsync(dio,101,asserted?LOW:INPUT); break;
    }
    return;
    num = 0;
    // CS1-3# not available, use CS0 instead
  }
  if (!asserted) return; // core will do this automatically
  ob->bus->Lock(ob->bus,0,0);
  ob->bus->Poke16(ob->bus,ob->offset,
		  (ob->bus->Peek16(ob->bus,ob->offset) & 0xFC7F)
		  | (num << 8) | (1 << 7));
  ob->bus->Unlock(ob->bus,0,0);
  return;
}

SPI *ts4700__SPIInit0(SPI *spi,int inst) {
  ts4700SPI0.LockNum = 7; // ???
  return WBSPIInit(&ts4700SPI0,ts4700__BusInit12(0,12),ts4700__BusInit11(0,11),0,
		   ts4700SPIChipSelect);
}
#define ts4700SPIInstances 1

#define ts4700EDIOInstances 0

#define ts4700AIOInstances 0

#define ARCH ts4700
#define ARCHTYPE ArchTypeCPU
#define ARCHSUBTYPE ArchTypeTSSocketBB
#define CLASS_INC "classinit2.h"
#include "classeach.h"

#include "archinit.h"
#define ARCH_LAST ts4700

// Author: Michael Schmidt (michael@embeddedARM.com)
// Copyright (c) 2012, Technologic Systems, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
