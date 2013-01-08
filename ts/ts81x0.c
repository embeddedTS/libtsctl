#include <stdio.h>
#include <stdlib.h>
#include "Time.h"
#include "Bus.h"
#include "Pin.h"
#include "CAN.h"
#include "DIORaw.h"
#include "DIO.h"
#include "TWI.h"
#include "ts81x0DIORaw.c"
#include "ts81x0Pin.c"
#include "PhysicalDIO.h"
#include "CacheBus.h"
#include "arch.h"

static ts81x0DIORaw ts81x0dio;
static PhysicalDIO ts81x0pdio;
static unsigned char ts81x0DIOCapabilities[32];
static CacheBus ts81x0DIOCacheBus;
static ts81x0Pin ts81x0pin;

unsigned ts81x0DIOCacheBus_WO[8];
unsigned ts81x0DIOCacheBus_IBit[8];
unsigned ts81x0DIOCacheBus_OBit[8];
unsigned ts81x0DIOCacheBus_icache[8];
unsigned ts81x0DIOCacheBus_ocache[8];
unsigned ts81x0DIOCacheBus_ocache0[8];

int ts81x0_ArchInit();

int ts81x0_isSubArch(ArchType type) {
  return type == ArchTypePC104;
}


#define ts81x0SystemInstances 0

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
#define ts81x0BusInstances 1

#define ts81x0TimeInstances 0

Pin *ts81x0__PinInit0(Pin *pin0,int inst) {
  if (inst == -1) {
    static int entered = 0;
    int CAN_TX1,CAN_TX2,CAN_RX1,CAN_RX2;
    CAN *can0,*can1;
    Pin *ret;

    if (entered) return (Pin *)&ts81x0pin;
    entered = 1;
    ret = ts81x0PinInit(&ts81x0pin,pin0,BusInit(2));
    can0 = CANInit(0);
    can1 = CANInit(1);
    ts81x0PinPostInit(&ts81x0pin,can0 ? can0->CAN_TX : -1,
			can1 ? can1->CAN_TX : -1,
			can0 ? can0->CAN_RX : -1,
			can1 ? can1->CAN_RX : -1);
    entered = 0;
    return ret;
  }
  return pin0;
}
#define ts81x0PinInstances 1

DIORaw *ts81x0__DIORawInit0(DIORaw *dioraw,int inst) {
  return ts81x0DIORawInit(&ts81x0dio,ts81x0__BusInit0(0,0));
}

#define ts81x0DIORawInstances 1

DIO *ts81x0__DIOInit0(DIO *dio,int inst) {
  int i;
  for (i=0;i<27;i++) {
    ts81x0DIOCapabilities[i] = DIO_NORMAL;
  }
  ts81x0pdio.Caps = ts81x0DIOCapabilities;
  return PhysicalDIOInit(&ts81x0pdio,ts81x0__BusInit0(0,0),
			 ts81x0__DIORawInit0(0,0));
}
#define ts81x0DIOInstances 1

#define ts81x0TWIInstances 0
int ts81x0_CANBusNum[0];
#define ts81x0CANInstances 0
#define ts81x0SPIInstances 0
#define ts81x0EDIOInstances 0
#define ts81x0AIOInstances 0

#define ARCH ts81x0
#define ARCHTYPE ArchTypeTSSocketBB
#define ARCHSUBTYPE ArchTypePC104
#define CLASS_INC "classinit2.h"
#include "classeach.h"

#include "archinit.h"
#define ARCH_LAST ts81x0

int ts81x0_ArchInit() {
  LogEnter("");
  static int found = 0, modded = 0, entered = 0;
  if (found) LogReturn("%d",1);
  int model,ret,mod;
  if (entered) return 0;
  entered=1;
  model = BaseBoardIdGet();
  entered=0;
  found = (model & 0xFF0F) == 0x8100;
  if (!modded) {
    modded = 1;
    mod = BaseBoardIdGet();
    if (mod == 0x8100) {
      dioctl_config_add(ts8100_dioctl_config);
    } else if (mod == 0x8160) {
      dioctl_config_add(ts8160_dioctl_config);
    } else if (mod == 0x8200) {
      dioctl_config_add(ts8200_dioctl_config);
    } else if (mod == 0x8390) {
      dioctl_config_add(ts8390_dioctl_config);
    } else if (mod == 0x9490) {
      dioctl_config_add(ts9490_dioctl_config);
    }
  }
  LogReturn("0x%04X==0x8100?%d",model,found);
}
