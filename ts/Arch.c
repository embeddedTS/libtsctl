#ifndef __Arch_c
#define __Arch_c
#include "IPC.c"
#include "peekpoke.c"
#include "FPGA.c"
#include "HashTable.c"
#include "BaseBoard.c"
#include "ts.h"
#include "Lock.h"
#include "ArchArch.h"

/////////////////////////////////////////////////////////////////////////////
// Arch.c
/*
  ArchPC104Init takes a parameter n, which specifies to return the nth
  board attached to the system.  The way this really needs to be done is
  to enumerate between 0 and PC104_MAX-1.  This maximum
  value represents the total of all possible supported boards.
 */
#define PC104_MAX 9
int ArchPC104Max() {
  return PC104_MAX; // TS-RELAY8 + 4 TS-DIO24 + 4 TS-CAN1
}

Arch *_ArchPC104Init(unsigned n) {
  static int checked[PC104_MAX];
  static Arch *boards[PC104_MAX];
  static Bus *pc104;
  int val;

  if (checked[n]) return boards[n];
  if (n >= PC104_MAX) return 0;
			
  if (!pc104) {
    pc104 = BusInit(2);
    pc104->Lock(pc104,0,0);
    pc104->BitClear16(pc104,2,9); // make sure ISA reset de-asserted
    pc104->Unlock(pc104,0,0);
  }
  checked[n] = 1;

  if (n == 0) {
#ifdef ARCH_relay8
    boards[n] = tsrelay8ArchInit(n);
#endif
  } else if (n < 5) {
#ifdef ARCH_dio24
    pc104->Lock(pc104,0,SHARED);
    val = pc104->Peek8(pc104,0x100+8*(n-4));
    pc104->Unlock(pc104,0,SHARED);
    if (val != 0x54) return 0;
    boards[n] = tsdio24ArchInit(n-4);
#endif
  } else if (n < 9) {
#ifdef ARCH_can1
    pc104->Lock(pc104,0,SHARED);
    val = pc104->Peek8(pc104,0x100+8*(n-8));
    if (val == 0xF6) {
      val = pc104->Peek8(pc104,0x150+8*(n-8)+1);
    } else {
      val = 0;
    }
    pc104->Unlock(pc104,0,SHARED);
    if (val != 0xB9) return 0;    
    boards[n] = tscan1ArchInit(n-8);
#endif
  }
  return boards[n];
}

void ArchPC104Init(Arch *owner) {
  int i,j;
  Arch *arch = owner, *next;
  j = ArchPC104Max();
  for (i=0;i<j;i++) {
    next = _ArchPC104Init(i);
    if (next) {
      arch->NextSubArchSet(next);
      arch = next;
    }
  }
}

#ifdef ARCH_CUSTOM
#include "ArchCustom.h"
#endif

Arch *ArchBBInit() {
  static Arch *baseboard=0;
  if (baseboard) return baseboard;
  int model = BaseBoardIdGet();
#ifdef ARCH_CUSTOM
  baseboard = ArchCustomBBInit(model);
  if (baseboard) return baseboard;
#endif
  switch (model) {
#ifdef ARCH_81x0
  case 0x8100:
  case 0x8160: baseboard = ts81x0ArchInit(model); break;
#endif
#ifdef ARCH_8200
  case 0x8200: baseboard = ts8200ArchInit(); break;
#endif
#ifdef ARCH_8390
  case 0x8390: baseboard = ts8390ArchInit(); break;
#endif
#ifdef ARCH_9490
  case 0x9490: baseboard = ts9490ArchInit(); break;
#endif
#ifdef ARCH_8820
  case 0x8820: baseboard = ts8820ArchInit(); break;
#endif
#ifdef ARCH_8900
  case 0x8900: baseboard = ts8900ArchInit(); break;
#endif
  }
  return baseboard;
}

Arch *ArchInit() {
  static Arch *hardware=0;
  if (hardware) return hardware;
  ThreadInit();
  dioctl_config_add2(0,0,0);
  int cpu = TSCPUGet();
#ifdef ARCH_CUSTOM
  hardware = ArchCustomInit(cpu);
  if (hardware) return hardware;
#endif
  if (cpu == CPU_CAVIUM) {
#ifdef ARCH_4500
    hardware = ts4500ArchInit();
#endif
  } else {
    int model = TSModelGet();
    switch (model) {
#ifdef ARCH_4200
    case 0x4200:  hardware = ts4200ArchInit(); break;
#endif
#ifdef ARCH_4700
    case 0x7700:
    case 0x4700: 
    case 0x4710: 
    case 0x4712: 
    case 0x4720: 
    case 0x4740: 
      hardware = ts4700ArchInit(model); break;
#endif
#ifdef ARCH_4800
    case 0x4800: hardware = ts4800ArchInit(); break;
#endif
#ifdef ARCH_7670
    case 0x7670: hardware = ts7670ArchInit(); break;
#endif
#ifdef ARCH_7800
    case 0x7800:  hardware = ts7800ArchInit(); break;
#endif
    }
  }
  if (!hardware) hardware = NoneArchInit();
  return hardware;
}

void *ClassInit(int class,int inst) {
  Arch *hardware = ArchInit();
  void *ob = 0;
  InitFunctionPtr f;

  if (!hardware) return ob;
 ClassInitNextTry:
  f = hardware->Function(class,inst);
  if (f) { // instance exists in the current hardware
    // call the init function 
    ob = f(ob,inst);
    // call the override function in all subsequent hardware
    inst = -1-inst;
    hardware = hardware->NextSubArch();
    while (hardware) {
      f = hardware->Function(class,inst);
      if (f) ob = f(ob,inst);
      hardware = hardware->NextSubArch();
    }
  } else { // instance is past the end of instances present in current hardware
    // subtract off the number of instances in the current hardware, 
    inst -= ArchClassCount(hardware,class,0);
    // try again in the next hardware
    hardware = hardware->NextSubArch();
    if (hardware) goto ClassInitNextTry;
  }
  return ob;
}

int ArchClassCount(Arch *hw,unsigned class,int recurse) {
  int i = 0;

  while (hw) {
    while (hw->Function(class,i)) i++;
    if (!recurse) break;
    hw = hw->NextSubArch();
  }
  return i;
}

System *SystemInit(int inst) { return ClassInit(ClassSystem,inst); }
Bus *BusInit(int inst) { return ClassInit(ClassBus,inst); }
Time *TimeInit(int inst) { return ClassInit(ClassTime,inst); }
Pin *PinInit(int inst) { return ClassInit(ClassPin,inst); }
DIORaw *DIORawInit(int inst) { return ClassInit(ClassDIORaw,inst); }
DIO *DIOInit(int inst) { return ClassInit(ClassDIO,inst); }
TWI *TWIInit(int inst) { return ClassInit(ClassTWI,inst); }
CAN *CANInit(int inst) { return ClassInit(ClassCAN,inst); }
SPI *SPIInit(int inst) { return ClassInit(ClassSPI,inst); }
AIO *AIOInit(int inst) { return ClassInit(ClassAIO,inst); }
EDIO *EDIOInit(int inst) { return ClassInit(ClassEDIO,inst); }

//============================================================================
// DIOCount is designed to be used before DIO is initialized
// it is used by the Pin object, which requires this information
// to determine how many locks to allocate
// we can probably require that the DIORaw Count function work even
// if we have not initialized the object.
unsigned DIOCount() {
  int n=0;
  unsigned num=0;
  DIORaw *dio = DIORawInit(n);
  while (dio) {
    num += dio->Count(dio);
    dio = DIORawInit(++n);
  }
  return num;
}

#include "AggregateDIO.h"
DIO *DIOInit0(AggregateDIO *DIO0) {
  static DIO *ret = 0;
  int i,j,total = 0;
  static DIO **pDIO = 0;
  DIO *dio = 0;
  static int *SubCount=0;
  int n = 0,offset;
  
  //if (ret) return ret;
  dio = DIOInit(1);
  while (dio) {
    total++;
    dio = DIOInit(total+1);
  }
  if (pDIO == 0) {
    pDIO = malloc(sizeof(DIO *) * total);
  } else {
    pDIO = realloc(pDIO,sizeof(DIO *) * total);
  }
  if (SubCount == 0) {
    SubCount = malloc(sizeof(int) * total);
  } else {
    SubCount = realloc(SubCount,sizeof(int) * total);
  }

  for (i=0;i<total;i++) {
    pDIO[i] = DIOInit(1+i);
  }
  return (ret=AggregateDIOInit(DIO0,total,PinInit(0),SubCount,pDIO));
}

#endif
