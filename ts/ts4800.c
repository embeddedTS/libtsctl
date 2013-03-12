#include "Thread.c"
#include "LinuxTWI.c"
#include "SystemTime.c"
#include "AggregateDIO.c"
#include "MMapBus.c"
#include "PhysicalDIO.c"
#include "ts4800Pin.c"
#include "ts4800DIORaw.c"
#include "TSMuxBus.c"
#include "FreescaleIMX51DIORaw.c"
#include "CacheBus.c"
#include "SJA1000CAN.c"
#include "WBSPI.c"
#include "baudtab.h"
#include "TSTime.c"
#include "WindowBus.c"
#include "DummyBus.c"
#include "WBWindowBus.c"
#include "LocalSystem.c"
#include "ts4800.h"
#include "arch.h"

DummyBus altmux;
MMapBus ts4800DIOBus, FreescaleIMX51DIOBus0, FreescaleIMX51DIOBus1, testbus,
  FreescaleIMX51DIOBus2, FreescaleIMX51DIOBus3, ts4800CANBus0, ts4800CANBus1,
  SPIBus,WBWindowBus0;
TSMuxBus muxbus;
CacheBus ts4800DIOCacheBus, FreescaleIMX51DIOCacheBus0, 
  FreescaleIMX51DIOCacheBus1, FreescaleIMX51DIOCacheBus2,
  FreescaleIMX51DIOCacheBus3;
WindowBus WindowBus0, WindowBus1;
WBWindowBus WBWindow0;
ts4800DIORaw ts4800DIORaw0;
FreescaleIMX51DIORaw FreescaleIMX51DIORaw0,FreescaleIMX51DIORaw1,
  FreescaleIMX51DIORaw2, FreescaleIMX51DIORaw3;
PhysicalDIO ts4800DIO, FreescaleIMX51DIO0, FreescaleIMX51DIO1,
  FreescaleIMX51DIO2,FreescaleIMX51DIO3;
AggregateDIO ts4800DIO0;
SystemTime ts4800Time0;
TSTime ts4800Time1;
LinuxTWI ts4800TWI0;
SJA1000CAN ts4800CAN0, ts4800CAN1;
ts4800Pin ts4800Pin0;
WBSPI ts4800SPI0;
LocalSystem ts4800sys;

CANConn ts4800CAN0conn[16];
CANConn ts4800CAN1conn[16];

#define ts4800DIOCacheBusLength 23
unsigned ts4800DIOCacheBus_WO[ts4800DIOCacheBusLength];
unsigned ts4800DIOCacheBus_IBit[ts4800DIOCacheBusLength];
unsigned ts4800DIOCacheBus_OBit[ts4800DIOCacheBusLength];
unsigned ts4800DIOCacheBus_icache[ts4800DIOCacheBusLength];
unsigned ts4800DIOCacheBus_ocache[ts4800DIOCacheBusLength];
unsigned ts4800DIOCacheBus_ocache0[ts4800DIOCacheBusLength];

#define FreescaleIMX51DIOCacheBusLength 3
unsigned FreescaleIMX51DIOCacheBus_WO[FreescaleIMX51DIOCacheBusLength];
unsigned FreescaleIMX51DIOCacheBus_IBit[FreescaleIMX51DIOCacheBusLength];
unsigned FreescaleIMX51DIOCacheBus_OBit[FreescaleIMX51DIOCacheBusLength];
unsigned FreescaleIMX51DIOCacheBus_icache[FreescaleIMX51DIOCacheBusLength];
unsigned FreescaleIMX51DIOCacheBus_ocache[FreescaleIMX51DIOCacheBusLength];
unsigned FreescaleIMX51DIOCacheBus_ocache0[FreescaleIMX51DIOCacheBusLength];

unsigned char ts4800DIOCapabilities[66];
unsigned char FreescaleIMX51DIOCapabilities0[16];
unsigned char FreescaleIMX51DIOCapabilities1[16];
unsigned char FreescaleIMX51DIOCapabilities2[16];
unsigned char FreescaleIMX51DIOCapabilities3[16];

char testbusdata[4096];

int ts4800_ArchInit() {
  LogEnter("");
  static int initialized = 0,value;
  if (initialized) LogReturn("%d",value);
  initialized = 1;
  int model = TSModelGet();
  value = (model == 0x4800);
  if (!value) LogReturn("%d",0);
  ThreadInit();
  dioctl_config_add(ts4800_dioctl_config);
  LogReturn("%d",1);
}

System *ts4800__SystemInit0(System *s,int inst) {
  return LocalSystemInit(&ts4800sys);
}
#define ts4800SystemInstances 1

Bus *ts4800__BusInit0(Bus *bus,int inst) {
  return MMapBusInit(&ts4800DIOBus,0xB0010000,2);
}
Bus *ts4800__BusInit1(Bus *bus,int inst) {
  return MMapBusInit2(&testbus,testbusdata,1);
}
Bus *ts4800__BusInit17(Bus *bus,int inst);
Bus *ts4800__BusInit2(Bus *bus,int inst) {
  Bus *bus0 = ts4800__BusInit0(0,0);
  int fpgarev;
  if (!BaseBoardMuxBusSupport()) return DummyBusInit(&altmux);
  bus0->Lock(bus0,0,0);
  fpgarev = bus0->BitsGet16(bus0,2,3,0);
  bus0->Unlock(bus0,0,0);
  if (fpgarev < 6) return DummyBusInit(&altmux);

  return TSMuxBusInit(&muxbus,ts4800__BusInit0(0,0),0x12,
		      ts4800__BusInit17(0,17),0x10000,
		      ts4800__BusInit17(0,17),0);
  //return TSMuxBusInit(&muxbus,BusInit(0),0x12,BusInit(0),0x1000,
  //BusInit(0),0x1000);
}
Bus *ts4800__BusInit3(Bus *bus,int inst) {
  return MMapBusInit(&FreescaleIMX51DIOBus0,0x73F84000,1);
}
Bus *ts4800__BusInit4(Bus *bus,int inst) {
  return MMapBusInit(&FreescaleIMX51DIOBus1,0x73F88000,33); // 33 pp for Pin
}
Bus *ts4800__BusInit5(Bus *bus,int inst) {
  return MMapBusInit(&FreescaleIMX51DIOBus2,0x73F8C000,1);
}
Bus *ts4800__BusInit6(Bus *bus,int inst) {
  return MMapBusInit(&FreescaleIMX51DIOBus3,0x73F90000,1);
}
Bus *ts4800__BusInit7(Bus *bus,int inst) {
  return MMapBusInit(&ts4800CANBus0,0xB001A000,1);
}
Bus *ts4800__BusInit8(Bus *bus,int inst) {
  return MMapBusInit(&ts4800CANBus1,0xB001B000,1);
}
Bus *ts4800__BusInit9(Bus *bus,int inst) {
  ts4800DIOCacheBus_IBit[0] = 0x3F00;
  ts4800DIOCacheBus_IBit[8] = 0xFFFF;
  ts4800DIOCacheBus_IBit[12] = 0xFFFF;
  ts4800DIOCacheBus_IBit[16] = 0xFFFF;
  ts4800DIOCacheBus_IBit[20] = 0xFFFF;
  
  ts4800DIOCacheBus_OBit[0] = 0xC0FF;
  ts4800DIOCacheBus_OBit[9] = 0xFFFF;
  ts4800DIOCacheBus_OBit[10] = 0xFFFF;
  ts4800DIOCacheBus_OBit[13] = 0xFFFF;
  ts4800DIOCacheBus_OBit[14] = 0xFFFF;
  ts4800DIOCacheBus_OBit[17] = 0xFFFF;
  ts4800DIOCacheBus_OBit[18] = 0xFFFF;
  ts4800DIOCacheBus_OBit[21] = 0xFFFF;
  ts4800DIOCacheBus_OBit[22] = 0xFFFF;
  
  ts4800DIOCacheBus.Length=ts4800DIOCacheBusLength;
  ts4800DIOCacheBus.Width=16;
  ts4800DIOCacheBus.Offset=0x10;
  ts4800DIOCacheBus.WO=ts4800DIOCacheBus_WO;
  ts4800DIOCacheBus.IBit=ts4800DIOCacheBus_IBit;
  ts4800DIOCacheBus.OBit=ts4800DIOCacheBus_OBit;
  ts4800DIOCacheBus.icache=ts4800DIOCacheBus_icache;
  ts4800DIOCacheBus.ocache=ts4800DIOCacheBus_ocache;
  ts4800DIOCacheBus.ocache0=ts4800DIOCacheBus_ocache0;
  return CacheBusInit(&ts4800DIOCacheBus,ts4800__BusInit0(0,0));
}
Bus *ts4800__BusInit10(Bus *bus,int inst) {
  FreescaleIMX51DIOCacheBus_IBit[2] = 0xFFFFFFFF;
  FreescaleIMX51DIOCacheBus_OBit[0] = 0xFFFFFFFF;
  FreescaleIMX51DIOCacheBus_OBit[1] = 0xFFFFFFFF;
  
  FreescaleIMX51DIOCacheBus0.Length=FreescaleIMX51DIOCacheBusLength;
  FreescaleIMX51DIOCacheBus0.Width=32;
  FreescaleIMX51DIOCacheBus0.Offset=0;
  
  FreescaleIMX51DIOCacheBus0.WO=FreescaleIMX51DIOCacheBus_WO;
  FreescaleIMX51DIOCacheBus0.IBit=FreescaleIMX51DIOCacheBus_IBit;
  FreescaleIMX51DIOCacheBus0.OBit=FreescaleIMX51DIOCacheBus_OBit;
  FreescaleIMX51DIOCacheBus0.icache=FreescaleIMX51DIOCacheBus_icache;
  FreescaleIMX51DIOCacheBus0.ocache=FreescaleIMX51DIOCacheBus_ocache;
  FreescaleIMX51DIOCacheBus0.ocache0=FreescaleIMX51DIOCacheBus_ocache0;
  return CacheBusInit(&FreescaleIMX51DIOCacheBus0,ts4800__BusInit3(0,3));
}
Bus *ts4800__BusInit11(Bus *bus,int inst) {
  FreescaleIMX51DIOCacheBus_IBit[2] = 0xFFFFFFFF;
  FreescaleIMX51DIOCacheBus_OBit[0] = 0xFFFFFFFF;
  FreescaleIMX51DIOCacheBus_OBit[1] = 0xFFFFFFFF;
  
  FreescaleIMX51DIOCacheBus1.Length=FreescaleIMX51DIOCacheBusLength;
  FreescaleIMX51DIOCacheBus1.Width=32;
  FreescaleIMX51DIOCacheBus1.Offset=0;
  
  FreescaleIMX51DIOCacheBus1.WO=FreescaleIMX51DIOCacheBus_WO;
  FreescaleIMX51DIOCacheBus1.IBit=FreescaleIMX51DIOCacheBus_IBit;
  FreescaleIMX51DIOCacheBus1.OBit=FreescaleIMX51DIOCacheBus_OBit;
  FreescaleIMX51DIOCacheBus1.icache=FreescaleIMX51DIOCacheBus_icache;
  FreescaleIMX51DIOCacheBus1.ocache=FreescaleIMX51DIOCacheBus_ocache;
  FreescaleIMX51DIOCacheBus1.ocache0=FreescaleIMX51DIOCacheBus_ocache0;
  return CacheBusInit(&FreescaleIMX51DIOCacheBus1,ts4800__BusInit4(0,4));
}
Bus *ts4800__BusInit12(Bus *bus,int inst) {
  FreescaleIMX51DIOCacheBus_IBit[2] = 0xFFFFFFFF;
  FreescaleIMX51DIOCacheBus_OBit[0] = 0xFFFFFFFF;
  FreescaleIMX51DIOCacheBus_OBit[1] = 0xFFFFFFFF;
  
  FreescaleIMX51DIOCacheBus2.Length=FreescaleIMX51DIOCacheBusLength;
  FreescaleIMX51DIOCacheBus2.Width=32;
  FreescaleIMX51DIOCacheBus2.Offset=0;
  
  FreescaleIMX51DIOCacheBus2.WO=FreescaleIMX51DIOCacheBus_WO;
  FreescaleIMX51DIOCacheBus2.IBit=FreescaleIMX51DIOCacheBus_IBit;
  FreescaleIMX51DIOCacheBus2.OBit=FreescaleIMX51DIOCacheBus_OBit;
  FreescaleIMX51DIOCacheBus2.icache=FreescaleIMX51DIOCacheBus_icache;
  FreescaleIMX51DIOCacheBus2.ocache=FreescaleIMX51DIOCacheBus_ocache;
  FreescaleIMX51DIOCacheBus2.ocache0=FreescaleIMX51DIOCacheBus_ocache0;
  return CacheBusInit(&FreescaleIMX51DIOCacheBus2,ts4800__BusInit5(0,5));
}
Bus *ts4800__BusInit13(Bus *bus,int inst) {
  FreescaleIMX51DIOCacheBus_IBit[2] = 0xFFFFFFFF;
  FreescaleIMX51DIOCacheBus_OBit[0] = 0xFFFFFFFF;
  FreescaleIMX51DIOCacheBus_OBit[1] = 0xFFFFFFFF;
  
  FreescaleIMX51DIOCacheBus3.Length=FreescaleIMX51DIOCacheBusLength;
  FreescaleIMX51DIOCacheBus3.Width=32;
  FreescaleIMX51DIOCacheBus3.Offset=0;
  
  FreescaleIMX51DIOCacheBus3.WO=FreescaleIMX51DIOCacheBus_WO;
  FreescaleIMX51DIOCacheBus3.IBit=FreescaleIMX51DIOCacheBus_IBit;
  FreescaleIMX51DIOCacheBus3.OBit=FreescaleIMX51DIOCacheBus_OBit;
  FreescaleIMX51DIOCacheBus3.icache=FreescaleIMX51DIOCacheBus_icache;
  FreescaleIMX51DIOCacheBus3.ocache=FreescaleIMX51DIOCacheBus_ocache;
  FreescaleIMX51DIOCacheBus3.ocache0=FreescaleIMX51DIOCacheBus_ocache0;
  return CacheBusInit(&FreescaleIMX51DIOCacheBus3,ts4800__BusInit6(0,6));
}
Bus *ts4800__BusInit14(Bus *bus,int inst) {
  return WindowBusInit(&WindowBus0,ts4800__BusInit7(0,7),0,2);
}
Bus *ts4800__BusInit15(Bus *bus,int inst) {
  return WindowBusInit(&WindowBus1,ts4800__BusInit8(0,8),0,2);
}
Bus *ts4800__BusInit16(Bus *bus,int inst) {
  return MMapBusInit(&SPIBus,0xB0013000,1);
}
Bus *ts4800__BusInit17(Bus *bus,int inst) {
  // (WBWindowBus *bus,void *sub,int adrs,int offset) 
  // 0xB0017000
  return WBWindowBusInit(&WBWindow0,
			 MMapBusInit(&WBWindowBus0,0xB0017000,1),0,0);
}
#define ts4800BusInstances 18

Time *ts4800__TimeInit0(Time *t,int inst) {
  return SystemTimeInit(&ts4800Time0);
}
Time *ts4800__TimeInit1(Time *t,int inst) {
  return TSTimeInit(&ts4800Time1,ts4800__BusInit0(0,0),4,6,1000000);
}
#define ts4800TimeInstances 2

Pin *ts4800__PinInit0(Pin *pin,int inst) {
  return ts4800PinInit(&ts4800Pin0,ts4800__BusInit0(0,0),ts4800__BusInit4(0,4));
}
#define ts4800PinInstances 1

DIORaw *ts4800__DIORawInit0(DIORaw *dioraw,int inst) {
  return ts4800DIORawInit(&ts4800DIORaw0,ts4800__BusInit9(0,9));
}
DIORaw *ts4800__DIORawInit1(DIORaw *dioraw,int inst) {
  return FreescaleIMX51DIORawInit(&FreescaleIMX51DIORaw0,ts4800__BusInit10(0,10));
}
DIORaw *ts4800__DIORawInit2(DIORaw *dioraw,int inst) {
  return FreescaleIMX51DIORawInit(&FreescaleIMX51DIORaw1,ts4800__BusInit11(0,11));
}
DIORaw *ts4800__DIORawInit3(DIORaw *dioraw,int inst) {
  return FreescaleIMX51DIORawInit(&FreescaleIMX51DIORaw2,ts4800__BusInit12(0,12));
}
DIORaw *ts4800__DIORawInit4(DIORaw *dioraw,int inst) {
  return FreescaleIMX51DIORawInit(&FreescaleIMX51DIORaw3,ts4800__BusInit13(0,13));
}
#define ts4800DIORawInstances 5

DIO *ts4800__DIOInit0(DIO *dio,int inst) {
  return DIOInit0(&ts4800DIO0);
}
DIO *ts4800__DIOInit1(DIO *dio,int inst) {
  int i,n;
  DIORaw *raw = ts4800__DIORawInit0(0,0);

  n = raw->Count(raw);
  ts4800DIO.Caps = ts4800DIOCapabilities;
  for (i=0;i<n;i++) {
    ts4800DIOCapabilities[i] = DIO_NORMAL;
  }
  ts4800DIOCapabilities[64] = DIO_OUTPUT_ONLY; // GREEN_LED
  ts4800DIOCapabilities[65] = DIO_OUTPUT_ONLY; // RED_LED
  return PhysicalDIOInit(&ts4800DIO,ts4800__BusInit9(0,9),raw);
}
DIO *ts4800__DIOInit2(DIO *dio,int inst) {
  DIORaw *raw = ts4800__DIORawInit1(0,1);

  FreescaleIMX51DIO0.Caps = FreescaleIMX51DIOCapabilities0;
  FreescaleIMX51DIOCapabilities0[3] = DIO_NORMAL;
  FreescaleIMX51DIOCapabilities0[5] = DIO_NORMAL;
  FreescaleIMX51DIOCapabilities0[6] = DIO_NORMAL;
  FreescaleIMX51DIOCapabilities0[7] = DIO_NORMAL;
  return PhysicalDIOInit(&FreescaleIMX51DIO0,ts4800__BusInit10(0,10),raw);
}
DIO *ts4800__DIOInit3(DIO *dio,int inst) {
  DIORaw *raw = ts4800__DIORawInit2(0,2);
  
  FreescaleIMX51DIO1.Caps = FreescaleIMX51DIOCapabilities1;
  return PhysicalDIOInit(&FreescaleIMX51DIO1,ts4800__BusInit11(0,11),raw);
}
DIO *ts4800__DIOInit4(DIO *dio,int inst) {
  DIORaw *raw = ts4800__DIORawInit3(0,3);
  
  FreescaleIMX51DIO2.Caps = FreescaleIMX51DIOCapabilities2;
  return PhysicalDIOInit(&FreescaleIMX51DIO2,ts4800__BusInit12(0,12),raw);
}
DIO *ts4800__DIOInit5(DIO *dio,int inst) {
  DIORaw *raw = ts4800__DIORawInit4(0,4);
  
  FreescaleIMX51DIO3.Caps = FreescaleIMX51DIOCapabilities3;
  FreescaleIMX51DIOCapabilities3[13] = DIO_NORMAL;
  FreescaleIMX51DIOCapabilities3[14] = DIO_NORMAL;
  return PhysicalDIOInit(&FreescaleIMX51DIO3,ts4800__BusInit13(0,13),raw);
}
#define ts4800DIOInstances 6

TWI *ts4800__TWIInit0(TWI *twi,int inst) {
  // I2C_CLK = IMX51:F16
  // I2C_DAT = IMX51:C16
  //TWI0.Speed=1000000;
  //TWI0.LockNum=1;
  return LinuxTWIInit(&ts4800TWI0,"/dev/i2c-1");
}
#define ts4800TWIInstances 1

int ts4800_CANBusNum[2] = { 14, 15 };

CAN *ts4800__CANInit0(CAN *can,int inst) {
  ts4800CAN0.LockBase = 2;
  ts4800CAN0.status = 0;
  ts4800CAN0.CAN_TX = 47;
  ts4800CAN0.CAN_RX = 45;
  ts4800CAN0.D.conn = ts4800CAN0conn;
  ts4800CAN0.D.maxconn = 16;
  ts4800CAN0.D.nconn = 0;
  ts4800CAN0.D.txc = 0;
  ts4800CAN0.baud = 1000000;
  ts4800CAN0.baudparms = baudparms25;
  ts4800CAN0.irq = 273;
  return SJA1000CANInit(&ts4800CAN0,ts4800__BusInit14(0,14),PinInit(0),
			ts4800__TimeInit0(0,0));
}
CAN *ts4800__CANInit1(CAN *can,int inst) {
  ts4800CAN1.LockBase = 3;
  ts4800CAN1.status = 0;
  ts4800CAN1.CAN_TX = 10;
  ts4800CAN1.CAN_RX = 11;
  ts4800CAN1.D.conn = ts4800CAN1conn;
  ts4800CAN1.D.maxconn = 16;
  ts4800CAN1.D.nconn = 0;
  ts4800CAN1.D.txc = 0;
  ts4800CAN1.baud = 1000000;
  ts4800CAN1.baudparms = baudparms25;
  ts4800CAN1.irq = 274;
  return SJA1000CANInit(&ts4800CAN1,ts4800__BusInit15(0,15),PinInit(0),
			ts4800__TimeInit0(0,0));
}
#define ts4800CANInstances 2


DIO *dio0;

static void ts4800SPIChipSelect(WBSPI *ob,unsigned num,int asserted) {
  if (num > 3) return;
  if (num == 0) {
    if (!asserted) return; // core will do this automatically
    ob->bus->Lock(ob->bus,0,0);
    ob->bus->Poke16(ob->bus,ob->offset,
			 (ob->bus->Peek16(ob->bus,ob->offset) & 0xFC7F)
			 | (num << 8) | (1 << 7));
    ob->bus->Unlock(ob->bus,0,0);
    return;
  }
  // Now use DIO
  switch (num) {
  case 1: dio0->SetAsync(dio0,18,asserted?LOW:INPUT); break;
  case 2: dio0->SetAsync(dio0,127,asserted?LOW:INPUT); break;
  case 3: dio0->SetAsync(dio0,128,asserted?LOW:INPUT); break;
  }
}
#include "peekpoke.h"

SPI *ts4800__SPIInit0(SPI *spi,int inst) {
  // write 8 to 0x83fda00c to set up WEIM to use byte selects
  volatile unsigned *reg = MemMap(0x83fda000,1);
  reg[0xC/sizeof(unsigned)] = 8;
  MemUnmap(reg);

  Bus *bus;
  dio0 = ts4800__DIOInit0(0,0); // needed by ts4800SPIChipSelect
  ts4800SPI0.LockNum = 7;
  bus = ts4800__BusInit0(0,0);
  return WBSPIInit(&ts4800SPI0,ts4800__BusInit16(0,16),ts4800__BusInit16(0,16),
		   0,ts4800SPIChipSelect);
}

#define ts4800SPIInstances 1

#define ts4800EDIOInstances 0

#define ts4800AIOInstances 0

#ifndef ARCH
#define ARCH ts4800
#define ARCHTYPE ArchTypeCPU
#define ARCHSUBTYPE ArchTypeTSSocketBB
#endif

#define CLASS_INC "classinit2.h"
#include "classeach.h"

#include "archinit.h"
#define ARCH_LAST ts4800

// Author: Michael Schmidt (michael@embeddedARM.com)
// Copyright (c) 2012, Technologic Systems, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.

