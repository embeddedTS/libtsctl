#include "Thread.c"
#include <string.h>
#include "arch.h"
#include "DummyBus.c"
#include "MMapBus.c"
#include "TSMuxBus.c"
#include "CacheBus.c"
#include "ts4200Pin.c"
#include "AtmelAT91DIORaw.c"
#include "ts4200DIORaw.c"
#include "SystemTime.c"
#include "PhysicalDIO.c"
#include "AggregateDIO.c"
#include "DIOTWI.c"
#include "DIOSPI.c"
#include "LocalSystem.c"
#include "SJA1000CAN.c"
#include "ts4200.h"


extern ArchInfo ts4200_ArchInfo;
extern ArchInfo ts4700_ArchInfo;
extern ArchInfo ts4800_ArchInfo;
extern ArchInfo ts81x0_ArchInfo;
extern ArchInfo ts8820_ArchInfo;
extern ArchInfo ts8900_ArchInfo;
extern ArchInfo tsrelay8_ArchInfo;
extern ArchInfo tsdio24_ArchInfo;

ArrayAuto(ArchInfo*,aArchTypeCPU,ARR(&ts4200_ArchInfo,&ts4700_ArchInfo,
				     &ts4800_ArchInfo));
ArrayAuto(ArchInfo*,aArchTypeTSSocketBB,ARR(&ts81x0_ArchInfo,
					    &ts8820_ArchInfo,&ts8900_ArchInfo));
ArrayAuto(ArchInfo*,aArchTypePC104,ARR(&tsrelay8_ArchInfo,&tsdio24_ArchInfo));
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
PhysicalDIO AtmelAT91DIO1,
  AtmelAT91DIO2,
  AtmelAT91DIO3,
  ts4200DIO;
unsigned char AtmelAT91DIO1Capabilities[32];
unsigned char AtmelAT91DIO2Capabilities[32];
unsigned char AtmelAT91DIO3Capabilities[32];
unsigned char ts4200DIOCapabilities[34];
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
#if 0
TWI *TWIGet(int instance) {
  if (instance == 0) {
    //return (TWI *)&ts4200TWI0;
  }
  return 0;
}
#endif

int ts4200_ArchInit() {
  LogEnter("");
  static int initialized = 0,value;
  if (initialized) LogReturn("%d",value);
  initialized = 1;
  int model = TSModelGet();
  value = (model == 0x4200);
  if (!value) LogReturn("%d",0);
  ThreadInit();
  dioctl_config_add(ts4200_dioctl_config);
  LogReturn("%d",1);
}

System *ts4200__SystemInit0(System *s,int inst) {
  return LocalSystemInit(&ts4200sys);
}
#define ts4200SystemInstances 1

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
#define ts4200BusInstances 14

Time *ts4200__TimeInit0(Time *t,int inst) {
  return SystemTimeInit(&ts4200Time0);
}
#define ts4200TimeInstances 1

Pin *ts4200__PinInit0(Pin *pin,int inst) {
  return ts4200PinInit(&ts4200Pin0,ts4200__BusInit0(0,0),ts4200__BusInit6(0,6),
		       ts4200__BusInit12(0,12),ts4200__BusInit8(0,8));
}
#define ts4200PinInstances 1


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
#define ts4200DIORawInstances 4

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
    ts4200DIOCapabilities[i] = DIO_NORMAL;
  }
  ts4200DIOCapabilities[32] = DIO_OUTPUT_ONLY;
  ts4200DIOCapabilities[33] = DIO_OUTPUT_ONLY;
  ts4200DIO.Caps = ts4200DIOCapabilities;
  return PhysicalDIOInit(&ts4200DIO,ts4200__BusInit3(0,3),
			 ts4200__DIORawInit3(0,3));
}
#define ts4200DIOInstances 5

TWI *ts4200__TWIInit0(TWI *twi,int inst) {
  ts4200TWI0.TW_CLK=24;
  ts4200TWI0.TW_DAT=23;
  ts4200TWI0.Speed=1000000;
  if (!ts4200TWI0.LockNum) ts4200TWI0.LockNum = ThreadMutexAllocate(1);
  return DIOTWIInit(&ts4200TWI0,ts4200__DIOInit0(0,0),ts4200__TimeInit0(0,0));
}
#define ts4200TWIInstances 1

int ts4200_CANBusNum[0];
#define ts4200CANInstances 0

SPI *ts4200__SPIInit0(SPI *spi,int inst) {
  DIO *dio = DIOInit(0);
  DIO *dio2 = DIOInit(2);
  return DIOSPIInit(&ts4200SPI0,dio,dio,dio,dio,35,134,134,134,
		    dio,33,dio,32,dio,34,TimeInit(0));
}
#define ts4200SPIInstances 1

#define ts4200EDIOInstances 0

#define ts4200AIOInstances 0

#define ARCH ts4200
#define ARCHTYPE ArchTypeCPU
#define ARCHSUBTYPE ArchTypeTSSocketBB
#define CLASS_INC "classinit2.h"
#include "classeach.h"

#include "archinit.h"
#define ARCH_LAST ts4200

// Author: Michael Schmidt (michael@embeddedARM.com)
// Copyright (c) 2012, Technologic Systems, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
