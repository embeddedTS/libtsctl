#include "Thread.h"
#include <string.h>
#include "arch.h"
#include "ArchArch.h"
#include "DummyBus.h"
#include "MMapBus.h"
#include "TSMuxBus.h"
#include "CacheBus.h"
#include "ts4200Pin.h"
#include "AtmelAT91DIORaw.h"
#include "ts4200DIORaw.h"
#include "SystemTime.h"
#include "PhysicalDIO.h"
#include "AggregateDIO.h"
#include "DIOTWI.h"
#include "DIOSPI.h"
#include "LocalSystem.h"
#include "SJA1000CAN.h"
#include "ts4200DIO.h"
extern char *ts4200_dioctl_config[];
#include "ts4200_dioctl_config.c"

/*
 NextSubArch:
ts4200Arch returns its baseboard arch, if any.
the baseboard arch will return the first PC-104 peripheral, if any.
if there are multiple PC-104 peripherals, then the baseboard arch
must chain them together during initialization, so that each peripheral
returns the next one.
*/
Arch *ts4200BBArch;
Arch *ts4200ArchInit();
void *ts4200Function(int class,int inst);
Arch *ts4200ArchNextSubArch();

Arch ts4200Arch = {
  .Init = ts4200ArchInit,
  .Function = ts4200Function,
  .NextSubArch = ts4200ArchNextSubArch
};

Arch *ts4200ArchInit() {
  static Arch *ts4200;
  if (ts4200) return ts4200;
  ts4200 = &ts4200Arch;
  dioctl_config_add2(Xts4200_dioctl_config,Xts4200_dioctl_config_len,Yts4200_dioctl_config_len); 

  ts4200BBArch = ArchBBInit();
  return ts4200;
}

Arch *ts4200ArchNextSubArch() {
  return ts4200BBArch;
}

DummyBus altmux;
MMapBus AtmelAT91DIOBus1,
  AtmelAT91DIOBus2,
  AtmelAT91DIOBus3,
  ts4200SysConBus, testbus, muxbusreg8, muxbusreg16,pmcreg,spibus1;
TSMuxBus muxbus;
CacheBus AtmelAT91DIOCacheBus1,
  AtmelAT91DIOCacheBus2,
  AtmelAT91DIOCacheBus3,
  ts4200DIOCacheBus;
ts4200Pin ts4200Pin0;
AtmelAT91DIORaw AtmelAT91DIORaw1,
  AtmelAT91DIORaw2,
  AtmelAT91DIORaw3;
ts4200DIORaw ts4200DIORaw0;
ts4200DIO allDIO;
PhysicalDIO AtmelAT91DIO1,
  AtmelAT91DIO2,
  AtmelAT91DIO3,
  ts4200DIOA;
unsigned char AtmelAT91DIO1Capabilities[32];
unsigned char AtmelAT91DIO2Capabilities[32];
unsigned char AtmelAT91DIO3Capabilities[32];
unsigned char ts4200DIOCapabilitiesA[34];
AggregateDIO ts4200DIO0;
DIOTWI ts4200TWI0;
DIOSPI ts4200SPI0;
SystemTime ts4200Time0;
LocalSystem ts4200sys;

unsigned AtmelAT91DIOCacheBus_WO[16];
unsigned AtmelAT91DIOCacheBus_IBit[16];
unsigned AtmelAT91DIOCacheBus_OBit[16];
unsigned AtmelAT91DIOCacheBus1_icache[16];
unsigned AtmelAT91DIOCacheBus1_ocache[16];
unsigned AtmelAT91DIOCacheBus1_ocache0[16];
unsigned AtmelAT91DIOCacheBus2_icache[16];
unsigned AtmelAT91DIOCacheBus2_ocache[16];
unsigned AtmelAT91DIOCacheBus2_ocache0[16];
unsigned AtmelAT91DIOCacheBus3_icache[16];
unsigned AtmelAT91DIOCacheBus3_ocache[16];
unsigned AtmelAT91DIOCacheBus3_ocache0[16];  
unsigned ts4200DIOCacheBus_WO[11];
unsigned ts4200DIOCacheBus_IBit[11];
unsigned ts4200DIOCacheBus_OBit[11];
unsigned ts4200DIOCacheBus_icache[11];
unsigned ts4200DIOCacheBus_ocache[11];
unsigned ts4200DIOCacheBus_ocache0[11];

char testbusdata[4096];

void *ts4200__SystemInit0(void *s,int inst) {
  return LocalSystemInit(&ts4200sys);
}

static void CacheBusCommonInit() {
  AtmelAT91DIOCacheBus_IBit[6]=0xFFFFFFFF;
  AtmelAT91DIOCacheBus_IBit[15]=0xFFFFFFFF;
  AtmelAT91DIOCacheBus_OBit[0]=0xFFFFFFFF;
  AtmelAT91DIOCacheBus_OBit[4]=0xFFFFFFFF;
  AtmelAT91DIOCacheBus_OBit[5]=0xFFFFFFFF;
  AtmelAT91DIOCacheBus_OBit[12]=0xFFFFFFFF;
  AtmelAT91DIOCacheBus_OBit[13]=0xFFFFFFFF;
  AtmelAT91DIOCacheBus_WO[0]=0xFFFFFFFF;
  AtmelAT91DIOCacheBus_WO[1]=0xFFFFFFFF;
  AtmelAT91DIOCacheBus_WO[4]=0xFFFFFFFF;
  AtmelAT91DIOCacheBus_WO[5]=0xFFFFFFFF;
  AtmelAT91DIOCacheBus_WO[8]=0xFFFFFFFF;
  AtmelAT91DIOCacheBus_WO[9]=0xFFFFFFFF;
}

Bus *ts4200__BusInit0(Bus *bus,int inst) {
  return MMapBusInit(&ts4200SysConBus,0x30000000,1);
}
Bus *ts4200__BusInit1(Bus *bus,int inst) {
  return MMapBusInit2(&testbus,testbusdata,1);
}
Bus *ts4200__BusInit10(Bus *bus,int inst);
Bus *ts4200__BusInit11(Bus *bus,int inst);
Bus *ts4200__BusInit2(Bus *bus,int inst) {
  if (!BaseBoardMuxBusSupport()) return DummyBusInit(&altmux);
  return TSMuxBusInit(&muxbus,ts4200__BusInit0(0,0),0x20,ts4200__BusInit10(0,10),
		      0,ts4200__BusInit11(0,11),0);
}
Bus *ts4200__BusInit3(Bus *bus,int inst) {
  ts4200DIOCacheBus_IBit[3]=0xFFFF;
  ts4200DIOCacheBus_IBit[10]=0xFFFF;
  ts4200DIOCacheBus_OBit[0]=0xC000;
  ts4200DIOCacheBus_OBit[1]=0xFFFF;
  ts4200DIOCacheBus_OBit[2]=0xFFFF;
  ts4200DIOCacheBus_OBit[8]=0xFFFF;
  ts4200DIOCacheBus_OBit[9]=0xFFFF;
    
  ts4200DIOCacheBus.Length=11;
  ts4200DIOCacheBus.Width=16;
  ts4200DIOCacheBus.Offset=2;
  ts4200DIOCacheBus.WO = ts4200DIOCacheBus_WO;
  ts4200DIOCacheBus.IBit = ts4200DIOCacheBus_IBit;
  ts4200DIOCacheBus.OBit = ts4200DIOCacheBus_OBit;
  ts4200DIOCacheBus.icache=ts4200DIOCacheBus_icache;
  ts4200DIOCacheBus.ocache=ts4200DIOCacheBus_ocache;
  ts4200DIOCacheBus.ocache0=ts4200DIOCacheBus_ocache0;
  return CacheBusInit(&ts4200DIOCacheBus,ts4200__BusInit0(0,0));
}
Bus *ts4200__BusInit4(Bus *bus,int inst) {
  return MMapBusInit(&AtmelAT91DIOBus1,0xFFFFF400,1);
}
Bus *ts4200__BusInit5(Bus *bus,int inst) {
  CacheBusCommonInit();
  AtmelAT91DIOCacheBus1.Length=16;
  AtmelAT91DIOCacheBus1.Width=32;
  AtmelAT91DIOCacheBus1.Offset=0;
  AtmelAT91DIOCacheBus1.WO = AtmelAT91DIOCacheBus_WO;
  AtmelAT91DIOCacheBus1.IBit = AtmelAT91DIOCacheBus_IBit;
  AtmelAT91DIOCacheBus1.OBit = AtmelAT91DIOCacheBus_OBit;
  AtmelAT91DIOCacheBus1.icache = AtmelAT91DIOCacheBus1_icache;
  AtmelAT91DIOCacheBus1.ocache = AtmelAT91DIOCacheBus1_ocache;
  AtmelAT91DIOCacheBus1.ocache0 = AtmelAT91DIOCacheBus1_ocache0;
  return CacheBusInit(&AtmelAT91DIOCacheBus1,ts4200__BusInit4(0,4));
}
Bus *ts4200__BusInit6(Bus *bus,int inst) {
  return MMapBusInit(&AtmelAT91DIOBus2,0xFFFFF600,1);
}
Bus *ts4200__BusInit7(Bus *bus,int inst) {
  CacheBusCommonInit();
  AtmelAT91DIOCacheBus2.Length=16;
  AtmelAT91DIOCacheBus2.Width=32;
  AtmelAT91DIOCacheBus2.Offset=0;
  AtmelAT91DIOCacheBus2.WO = AtmelAT91DIOCacheBus_WO;
  AtmelAT91DIOCacheBus2.IBit = AtmelAT91DIOCacheBus_IBit;
  AtmelAT91DIOCacheBus2.OBit = AtmelAT91DIOCacheBus_OBit;
  AtmelAT91DIOCacheBus2.icache = AtmelAT91DIOCacheBus2_icache;
  AtmelAT91DIOCacheBus2.ocache = AtmelAT91DIOCacheBus2_ocache;
  AtmelAT91DIOCacheBus2.ocache0 = AtmelAT91DIOCacheBus2_ocache0;
  return CacheBusInit(&AtmelAT91DIOCacheBus2,ts4200__BusInit6(0,6));
}
Bus *ts4200__BusInit8(Bus *bus,int inst) {
  return MMapBusInit(&AtmelAT91DIOBus3,0xFFFFF800,1);
}
Bus *ts4200__BusInit9(Bus *bus,int inst) {
  CacheBusCommonInit();
  AtmelAT91DIOCacheBus3.Length=16;
  AtmelAT91DIOCacheBus3.Width=32;
  AtmelAT91DIOCacheBus3.Offset=0;
  AtmelAT91DIOCacheBus3.WO = AtmelAT91DIOCacheBus_WO;
  AtmelAT91DIOCacheBus3.IBit = AtmelAT91DIOCacheBus_IBit;
  AtmelAT91DIOCacheBus3.OBit = AtmelAT91DIOCacheBus_OBit;
  AtmelAT91DIOCacheBus3.icache = AtmelAT91DIOCacheBus3_icache;
  AtmelAT91DIOCacheBus3.ocache = AtmelAT91DIOCacheBus3_ocache;
  AtmelAT91DIOCacheBus3.ocache0 = AtmelAT91DIOCacheBus3_ocache0;
  return CacheBusInit(&AtmelAT91DIOCacheBus3,ts4200__BusInit8(0,8));
}
Bus *ts4200__BusInit10(Bus *bus,int inst) {
  return MMapBusInit(&muxbusreg8,0x10000400,1);
}
Bus *ts4200__BusInit11(Bus *bus,int inst) {
  return MMapBusInit(&muxbusreg16,0x30000400,1);
}
Bus *ts4200__BusInit12(Bus *bus,int inst) {
  return MMapBusInit(&pmcreg,0xFFFFFC00,1);
}
Bus *ts4200__BusInit13(Bus *bus,int inst) {
  return MMapBusInit(&spibus1,0xFFFCC000,1);
}

Time *ts4200__TimeInit0(Time *t,int inst) {
  return SystemTimeInit(&ts4200Time0);
}

Pin *ts4200__PinInit0(Pin *pin,int inst) {
  return ts4200PinInit(&ts4200Pin0,ts4200__BusInit0(0,0),ts4200__BusInit6(0,6),
		       ts4200__BusInit12(0,12),ts4200__BusInit8(0,8),
		       ts4200__BusInit4(0,4));
}

DIORaw *ts4200__DIORawInit0(DIORaw *dioraw,int inst) {
  return AtmelAT91DIORawInit(&AtmelAT91DIORaw1,ts4200__BusInit5(0,5));
}
DIORaw *ts4200__DIORawInit1(DIORaw *dioraw,int inst) {
  return AtmelAT91DIORawInit(&AtmelAT91DIORaw2,ts4200__BusInit7(0,7));
}
DIORaw *ts4200__DIORawInit2(DIORaw *dioraw,int inst) {
  return AtmelAT91DIORawInit(&AtmelAT91DIORaw3,ts4200__BusInit9(0,9));
}
DIORaw *ts4200__DIORawInit3(DIORaw *dioraw,int inst) {
  return ts4200DIORawInit(&ts4200DIORaw0,ts4200__BusInit3(0,3));
}

DIO *ts4200__DIOInit0(DIO *dio,int inst) {
  return DIOInit0(&ts4200DIO0);
}

DIO *ts4200__DIOInit1(DIO *dio,int inst) {
  int i;

  AtmelAT91DIO1Capabilities[6] = DIO_NORMAL;
  AtmelAT91DIO1Capabilities[9] = DIO_NORMAL;
  AtmelAT91DIO1Capabilities[22] = DIO_NORMAL;
  AtmelAT91DIO1Capabilities[23] = DIO_NORMAL;
  AtmelAT91DIO1Capabilities[24] = DIO_NORMAL;
  AtmelAT91DIO1Capabilities[30] = DIO_NORMAL;
  AtmelAT91DIO1Capabilities[31] = DIO_NORMAL;
  AtmelAT91DIO1.Caps = AtmelAT91DIO1Capabilities;
  return PhysicalDIOInit(&AtmelAT91DIO1,ts4200__BusInit5(0,5),
			 ts4200__DIORawInit0(0,0));
}
DIO *ts4200__DIOInit2(DIO *dio,int inst) {
  int i;

  for (i=0;i<=13;i++) {
    AtmelAT91DIO2Capabilities[i] = DIO_NORMAL;
  }
  AtmelAT91DIO2Capabilities[16] = DIO_NORMAL;
  AtmelAT91DIO2Capabilities[17] = DIO_NORMAL;
  AtmelAT91DIO2Capabilities[18] = DIO_NORMAL;
  for (i=20;i<=30;i++) {
    AtmelAT91DIO2Capabilities[i] = DIO_NORMAL;
  }
  AtmelAT91DIO2.Caps = AtmelAT91DIO2Capabilities;
  return PhysicalDIOInit(&AtmelAT91DIO2,ts4200__BusInit7(0,7),
			 ts4200__DIORawInit1(0,1));
}
DIO *ts4200__DIOInit3(DIO *dio,int inst) {
  int i;

  for (i=0;i<=10;i++) {
    AtmelAT91DIO3Capabilities[i] = DIO_NORMAL;
  }
  AtmelAT91DIO3Capabilities[13] = DIO_NORMAL;
  AtmelAT91DIO3Capabilities[14] = DIO_NORMAL;
  AtmelAT91DIO3.Caps = AtmelAT91DIO3Capabilities;
  return PhysicalDIOInit(&AtmelAT91DIO3,ts4200__BusInit9(0,9),
			 ts4200__DIORawInit2(0,2));
}
DIO *ts4200__DIOInit4(DIO *dio,int inst) {
  int i;

  for (i=0;i<=31;i++) {
    ts4200DIOCapabilitiesA[i] = DIO_NORMAL;
  }
  ts4200DIOCapabilitiesA[32] = DIO_OUTPUT_ONLY;
  ts4200DIOCapabilitiesA[33] = DIO_OUTPUT_ONLY;
  ts4200DIOA.Caps = ts4200DIOCapabilitiesA;
  return PhysicalDIOInit(&ts4200DIOA,ts4200__BusInit3(0,3),
			 ts4200__DIORawInit3(0,3));
}
/*
This DIO causes issues with DIO testing and DIO numbering for base board
and PC104 banks due to there not being a corresponding DIORaw object.
Commented out until we can fix the problem.
DIO *ts4200__DIOInit5(DIO *dio,int inst) {
  return ts4200DIOInit(&allDIO);
}
*/
TWI *ts4200__TWIInit0(TWI *twi,int inst) {
  ts4200TWI0.TW_CLK=24;
  ts4200TWI0.TW_DAT=23;
  ts4200TWI0.Speed=1000000;
  if (!ts4200TWI0.LockNum) ts4200TWI0.LockNum = ThreadMutexAllocate(1);
  return DIOTWIInit(&ts4200TWI0,ts4200__DIOInit0(0,0),ts4200__TimeInit0(0,0));
}

SPI *ts4200__SPIInit0(SPI *spi,int inst) {
  DIO *dio = DIOInit(0);
  DIO *dio2 = DIOInit(2);
  return DIOSPIInit(&ts4200SPI0,dio,dio,dio,dio,35,57,58,59, // was 134
		    dio,33,dio,32,dio,34,TimeInit(0));
}

void *ts4200Function(int class,int inst) {
  switch(class) {
  case ClassSystem:
    switch (inst) {
    case 0: return ts4200__SystemInit0;
    default: return 0;
    }
  case ClassBus:
    switch (inst) {
    case 0: return ts4200__BusInit0;
    case 1: return ts4200__BusInit1;
    case 2: return ts4200__BusInit2;
    case 3: return ts4200__BusInit3;
    case 4: return ts4200__BusInit4;
    case 5: return ts4200__BusInit5;
    case 6: return ts4200__BusInit6;
    case 7: return ts4200__BusInit7;
    case 8: return ts4200__BusInit8;
    case 9: return ts4200__BusInit9;
    case 10: return ts4200__BusInit10;
    case 11: return ts4200__BusInit11;
    case 12: return ts4200__BusInit12;
    case 13: return ts4200__BusInit13;
    default: return 0;
    }
  case ClassTime:
    switch (inst) {
    case 0: return ts4200__TimeInit0;
    default: return 0;
    }
  case ClassPin:
    switch (inst) {
    case 0: return ts4200__PinInit0;
    default: return 0;
    }
  case ClassDIORaw:
    switch (inst) { 
    case 0: return ts4200__DIORawInit0;
    case 1: return ts4200__DIORawInit1;
    case 2: return ts4200__DIORawInit2;
    case 3: return ts4200__DIORawInit3;
    default: return 0;
    }
  case ClassDIO:
    switch (inst) {
    case 0: return ts4200__DIOInit0;
    case 1: return ts4200__DIOInit1;
    case 2: return ts4200__DIOInit2;
    case 3: return ts4200__DIOInit3;
    case 4: return ts4200__DIOInit4;
      //    case 5: return ts4200__DIOInit5;
    default: return 0;
    }
  case ClassTWI:
    switch (inst) {
    case 0: return ts4200__TWIInit0;
    default: return 0;
    }
  case ClassCAN:
    switch (inst) {
    default: return 0;
    }
  case ClassSPI:
    switch (inst) {
    case 0: return ts4200__SPIInit0;
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

// Author: Michael Schmidt (michael@embeddedTS.com)
// Copyright (c) 2013-2022 Technologic Systems, Inc. dba embeddedTS, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
