#include <stdio.h>
#include <stdlib.h>
#include "Time.h"
#include "Bus.h"
#include "Pin.h"
#include "CAN.h"
#include "DIORaw.h"
#include "DIO.h"
#include "TWI.h"
#include "ts8900DIORaw.c"
#include "ts8900Pin.c"
#include "PhysicalDIO.h"
#include "CacheBus.h"
#include "PC104Bus.c"
#include "arch.h"

static ts8900DIORaw ts8900dio;
static PhysicalDIO ts8900pdio;
static unsigned char ts8900DIOCapabilities[41];
static CacheBus ts8900DIOCacheBus;
static ts8900Pin ts8900pin;
static PC104Bus ts8900pc104bus;

unsigned ts8900DIOCacheBus_WO[8];
unsigned ts8900DIOCacheBus_IBit[8];
unsigned ts8900DIOCacheBus_OBit[8];
unsigned ts8900DIOCacheBus_icache[8];
unsigned ts8900DIOCacheBus_ocache[8];
unsigned ts8900DIOCacheBus_ocache0[8];

int ts8900_ArchInit();

#define ts8900SystemInstances 0

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

Bus *ts8900__BusInit0(Bus *bus,int inst) {
  Bus *bus2 = BusInit(2);
  return PC104BusInit(&ts8900pc104bus,bus2,0x0800,bus2,0,ts8900PC104Lock);
}

Bus *ts8900__BusInit1(Bus *bus,int inst) {
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

#define ts8900BusInstances 2

#define ts8900TimeInstances 0

int isme8900;

Pin *ts8900__PinInit0(Pin *pin0,int inst) {
  if (inst == -1) {
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
  return pin0;
}
#define ts8900PinInstances 1

DIORaw *ts8900__DIORawInit0(DIORaw *dioraw,int inst) {
  isme8900=1;
  return ts8900DIORawInit(&ts8900dio,ts8900__BusInit1(0,1));
}
#define ts8900DIORawInstances 1

DIO *ts8900__DIOInit0(DIO *dio,int inst) {
  int i;
  for (i=0;i<=7;i++) {
    ts8900DIOCapabilities[i] = DIO_INPUT_ONLY;
  } 
  for (i=8;i<=15;i++) {
    ts8900DIOCapabilities[i] = DIO_OUTPUT_ONLY;
  } 
  for (i=16;i<41;i++) {
    ts8900DIOCapabilities[i] = DIO_NORMAL;
  }
  ts8900pdio.Caps = ts8900DIOCapabilities;
  return PhysicalDIOInit(&ts8900pdio,ts8900__BusInit1(0,1),
			 ts8900__DIORawInit0(0,0));
}
#define ts8900DIOInstances 1

#define ts8900TWIInstances 0
#define ts8900CANInstances 0
int ts8900_CANBusNum[0];
#define ts8900SPIInstances 0
#define ts8900EDIOInstances 0
#define ts8900AIOInstances 0

#define ARCH ts8900
#define ARCHTYPE ArchTypeTSSocketBB
#define ARCHSUBTYPE ArchTypePC104
#define CLASS_INC "classinit2.h"
#include "classeach.h"

#include "archinit.h"
#define ARCH_LAST ts8900

int ts8900_ArchInit() {
  LogEnter("");
  static int found = 0;
  if (found) LogReturn("%d",1);
  Bus *muxbus = BusInit(2);
  int model;
  muxbus->Lock(muxbus,0,SHARED);
  model = muxbus->Peek16(muxbus,0);
  if (model != 0x8900) { // bug workaround
    model = muxbus->Peek16(muxbus,0);
  }
  muxbus->Unlock(muxbus,0,SHARED);
  found = model == 0x8900;
  if (found) {
    dioctl_config_add(ts8900_dioctl_config);
  }
  LogReturn("0x%04X==0x8900?%d",model,found);
}
