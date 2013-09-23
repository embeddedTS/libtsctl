#include "arch.h"
#include "ArchArch.h"
#include "TSCAN1Bus.h"
#include "SJA1000CAN.h"
#include "baudtab16.h"

Arch *tscan1ArchInit();
void *tscan1Function(int class,int inst);
Arch *tscan1ArchNextSubArch();
void tscan1NextSubArchSet(Arch *arch);
int tscan1CANBusId(int inst);

Arch tscan1Arch = {
  .Init = tscan1ArchInit,
  .Function = tscan1Function,
  .NextSubArch = tscan1ArchNextSubArch,
  .NextSubArchSet = tscan1NextSubArchSet,
  .CANBusId = tscan1CANBusId
};

Arch *tscan1ArchInit(int model) {
  static Arch *tscan1;
  if (tscan1) return tscan1;
  tscan1 = &tscan1Arch;
  return tscan1;
}

Arch *tscan1Next;

Arch *tscan1ArchNextSubArch() {
  return tscan1Next;
}

void tscan1NextSubArchSet(Arch *arch) {
  tscan1Next = arch;
}

int tscan1CANBusId(int inst) {
  // HOW TO IMPLEMENT THIS???
  return -1;
}

TSCAN1Bus tsCAN1Bus150,tsCAN1Bus158;
SJA1000CAN tscan1CAN0,tscan1CAN1;
CANConn tscan1CAN0conn[16],tscan1CAN1conn[16];

Bus *tscan1__BusInit0(Bus *bus,int inst) {
  return TSCAN1BusInit(&tsCAN1Bus150,BusInit(2),0x150);
}
Bus *tscan1__BusInit1(Bus *bus,int inst) {
  return TSCAN1BusInit(&tsCAN1Bus158,BusInit(2),0x158);
}

CAN *tscan1__CANInit0(CAN *can,int inst) {
  tscan1CAN0.LockBase = 2;
  tscan1CAN0.status = 0;
  tscan1CAN0.CAN_TX = -1;
  tscan1CAN0.CAN_RX = -1;
  tscan1CAN0.D.conn = tscan1CAN0conn;
  tscan1CAN0.D.maxconn = 16;
  tscan1CAN0.D.nconn = 0;
  tscan1CAN0.D.txc = 0;
  tscan1CAN0.baud = 1000000;
  tscan1CAN0.baudparms = baudparms16;
  tscan1CAN0.irq = 194;
  Bus *bus = tscan1__BusInit0(0,0);
  if (!bus) return 0;
  return SJA1000CANInit(&tscan1CAN0,bus,PinInit(0),TimeInit(0));
}

CAN *tscan1__CANInit1(CAN *can,int inst) {
  tscan1CAN0.LockBase = 2;
  tscan1CAN0.status = 0;
  tscan1CAN0.CAN_TX = -1;
  tscan1CAN0.CAN_RX = -1;
  tscan1CAN0.D.conn = tscan1CAN1conn;
  tscan1CAN0.D.maxconn = 16;
  tscan1CAN0.D.nconn = 0;
  tscan1CAN0.D.txc = 0;
  tscan1CAN0.baud = 1000000;
  tscan1CAN0.baudparms = baudparms16;
  tscan1CAN0.irq = 191;
  Bus *bus = tscan1__BusInit1(0,1);
  if (!bus) return 0;
  return SJA1000CANInit(&tscan1CAN0,bus,PinInit(0),TimeInit(0));
}

void *tsdio24Function(int class,int inst) {
  if (class == ClassBus && inst == 0) return tscan1__BusInit0;
  if (class == ClassBus && inst == 1) return tscan1__BusInit1;
  if (class == ClassCAN && inst == 0) return tscan1__CANInit0;
  if (class == ClassCAN && inst == 1) return tscan1__CANInit1;
}
