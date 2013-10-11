#include "Thread.h"
#include "arch.h"
#include "ArchArch.h"
#include "DummyBus.h"
#include "MMapBus.h"
#include "SystemTime.h"
#include "AggregateDIO.h"
#include "DIOTWI.h"
#include "PhysicalDIO.h"
#include "ts4700Pin.h"
#include "ts4700DIORaw.h"
#include "ts7700DIORaw.h"
#include "TSMuxBus.h"
#include "MarvellPXA166DIORaw.h"
#include "CacheBus.h"
#include "SJA1000CAN.h"
#include "LocalSystem.h"
#include "WBSPI.h"
#include "baudtab.h"
#include "Array.h"
extern char *ts4700_dioctl_config[];
extern char *ts7700_dioctl_config[];
#include "ts4700_dioctl_config.c"
#include "ts7700_dioctl_config.c"

Arch *ts4700BBArch;
Arch *ts4700ArchInit();
void *ts4700Function(int class,int inst);
Arch *ts4700ArchNextSubArch();
int ts4700CANBusId(int inst);

Arch ts4700Arch = {
  .Init = ts4700ArchInit,
  .Function = ts4700Function,
  .NextSubArch = ts4700ArchNextSubArch,
  .CANBusId = ts4700CANBusId
};

int is7700;
Arch *ts4700ArchInit(int model) {
  static Arch *ts4700;
  if (ts4700) return ts4700;
  ts4700 = &ts4700Arch;
  is7700 = (model == 0x7700);
  if (is7700) {
    dioctl_config_add2(Xts7700_dioctl_config,Xts7700_dioctl_config_len,Yts7700_dioctl_config_len);
  } else {
    dioctl_config_add2(Xts4700_dioctl_config,Xts4700_dioctl_config_len,Yts4700_dioctl_config_len);
  }
  ts4700BBArch = ArchBBInit();
  return ts4700;
}

Arch *ts4700ArchNextSubArch() {
  return ts4700BBArch;
}

int ts4700CANBusId(int inst) {
  if (inst == 0) return 4;
  if (inst == 1) return 13;
  return -1;
}

DummyBus altmux;
MMapBus MarvellPXA166DIOBus, ts4700DIOBus, ts4700CANBus, testbus, twiregs,
  mfpregs, mux8bus, mux16bus, spi8bus, spi16bus, ts4700CANBus1;
TSMuxBus muxbus;
CacheBus MarvellPXA166DIOCacheBus, ts4700DIOCacheBus;
MarvellPXA166DIORaw MarvellPXA166DIORaw0;
ts4700DIORaw ts4700DIORaw0;
ts7700DIORaw ts7700DIORaw0;
PhysicalDIO MarvellPXA166DIO, ts4700DIO;
AggregateDIO ts4700DIO0;
SystemTime ts4700Time0;
//MarvellPXA166TWI ts4700TWI0;
DIOTWI ts4700TWI0;
SJA1000CAN ts4700CAN0, ts4700CAN1;
ts4700Pin ts4700Pin0;
WBSPI ts4700SPI0;
LocalSystem ts4700sys;

CANConn ts4700CAN0conn[16];
CANConn ts4700CAN1conn[16];

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

System *ts4700__SystemInit0(System *s,int inst) {
  return LocalSystemInit(&ts4700sys);
}

Bus *ts4700__BusInit0(Bus *bus,int inst) {
  return MMapBusInit(&ts4700DIOBus,0x80004000,1);
}
Bus *ts4700__BusInit1(Bus *bus,int inst) {
  return MMapBusInit2(&testbus,testbusdata,1);
}
Bus *ts4700__BusInit9(Bus *bus,int inst);
Bus *ts4700__BusInit10(Bus *bus,int inst);
Bus *ts4700__BusInit2(Bus *bus,int inst) {
  if (is7700 || !BaseBoardMuxBusSupport()) return DummyBusInit(&altmux);
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
Bus *ts4700__BusInit13(Bus *bus,int inst) {
  return MMapBusInit(&ts4700CANBus1,0x81004f00,1);
}

Time *ts4700__TimeInit0(Time *t,int inst) {
  return SystemTimeInit(&ts4700Time0);
}

Pin *ts4700__PinInit0(Pin *pin,int inst) {
  return ts4700PinInit(&ts4700Pin0,ts4700__BusInit0(0,0),ts4700__BusInit8(0,8));
}

DIORaw *ts4700__DIORawInit0(DIORaw *dioraw,int inst) {
  if (is7700) {
    return ts7700DIORawInit(&ts7700DIORaw0,ts4700__BusInit0(0,0));
  } else {
    return ts4700DIORawInit(&ts4700DIORaw0,ts4700__BusInit5(0,5));
  }
}
DIORaw *ts4700__DIORawInit1(DIORaw *dioraw,int inst) {
  return MarvellPXA166DIORawInit(&MarvellPXA166DIORaw0,ts4700__BusInit6(0,6));
}

DIO *ts4700__DIOInit0(DIO *dio,int inst) {
  return DIOInit0((void *)&ts4700DIO0);
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
  return PhysicalDIOInit(&ts4700DIO,is7700?ts4700__BusInit0(0,0):ts4700__BusInit5(0,5),raw);
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

TWI *ts4700__TWIInit0(TWI *twi,int inst) {
  ts4700TWI0.TW_CLK=150;
  ts4700TWI0.TW_DAT=149;
  ts4700TWI0.Speed=1000000;
  ts4700TWI0.LockNum=1;
  return DIOTWIInit(&ts4700TWI0,ts4700__DIOInit0(0,0),ts4700__TimeInit0(0,0));
}

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

CAN *ts4700__CANInit1(CAN *can,int inst) {
  ts4700CAN1.LockBase = 2;
  ts4700CAN1.status = 0;
  ts4700CAN1.CAN_TX = 10;
  ts4700CAN1.CAN_RX = 11;
  ts4700CAN1.D.conn = ts4700CAN1conn;
  ts4700CAN1.D.maxconn = 16;
  ts4700CAN1.D.nconn = 0;
  ts4700CAN1.D.txc = 0;
  ts4700CAN1.baud = 1000000;
  ts4700CAN1.baudparms = baudparms25;
  ts4700CAN1.irq = 66;
  return SJA1000CANInit(&ts4700CAN1,ts4700__BusInit13(0,13),PinInit(0),
			ts4700__TimeInit0(0,0));
}

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

void *ts4700Function(int class,int inst) {
  switch(class) {
  case ClassSystem:
    switch (inst) {
    case 0: return ts4700__SystemInit0;
    default: return 0;
    }
  case ClassBus:
    switch (inst) {
    case 0: return ts4700__BusInit0;
    case 1: return ts4700__BusInit1;
    case 2: return ts4700__BusInit2;
    case 3: return ts4700__BusInit3;
    case 4: return ts4700__BusInit4;
    case 5: return ts4700__BusInit5;
    case 6: return ts4700__BusInit6;
    case 7: return ts4700__BusInit7;
    case 8: return ts4700__BusInit8;
    case 9: return ts4700__BusInit9;
    case 10: return ts4700__BusInit10;
    case 11: return ts4700__BusInit11;
    case 12: return ts4700__BusInit12;
    case 13: return ts4700__BusInit13;
    default: return 0;
    }
  case ClassTime:
    switch (inst) {
    case 0: return ts4700__TimeInit0;
    default: return 0;
    }
  case ClassPin:
    switch (inst) {
    case 0: return ts4700__PinInit0;
    default: return 0;
    }
  case ClassDIORaw:
    switch (inst) { 
    case 0: return ts4700__DIORawInit0;
    case 1: return ts4700__DIORawInit1;
    default: return 0;
    }
  case ClassDIO:
    switch (inst) {
    case 0: return ts4700__DIOInit0;
    case 1: return ts4700__DIOInit1;
    case 2: return ts4700__DIOInit2;
    default: return 0;
    }
  case ClassTWI:
    switch (inst) {
    case 0: return ts4700__TWIInit0;
    default: return 0;
    }
  case ClassCAN:
    switch (inst) {
    case 0: return ts4700__CANInit0;
    case 1: return ts4700__CANInit1;
    default: return 0;
    }
  case ClassSPI:
    switch (inst) {
    case 0: return ts4700__SPIInit0;
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
