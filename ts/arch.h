#ifndef __arch_h
#define __arch_h
#include "cpp.h"
#include "Time.h"
#include "Bus.h"
#include "Pin.h"
#include "CAN.h"
#include "DIORaw.h"
#include "DIO.h"
#include "SPI.h"
#include "TWI.h"
#include "AIO.h"
#include "EDIO.h"
#include "System.h"
#include "Array.h"

enum {
  ClassSystem = 0,
  ClassBus = 1,
  ClassTime = 2,
  ClassPin = 3,
  ClassDIORaw = 4,
  ClassDIO = 5,
  ClassTWI = 6,
  ClassCAN = 7,
  ClassSPI = 8,
  ClassAIO = 9,
  ClassEDIO = 10
};
typedef enum {
  ArchTypeNone = -1,
  ArchTypeCPU = 0,
  ArchTypeTSSocketBB = 1,
  ArchTypePC104 = 2
} ArchType;

#define ClassesCount (ClassEDIO+1)

#define ARCH_C STRINGIFY(ARCH.c)
#define ARCH_H STRINGIFY(ARCH.h)

typedef struct ArchInfo ArchInfo;

struct ArchInfo {
  ArchType type;
  char *name;
  ArchInfo *next,*parent;
  int Instances[ClassesCount];
  int *CANBusNum;
  int (*ArchInit)();
  ArchInfo* *subarches;
  System *(*SystemInit)(System *,int inst);
  Bus *(*BusInit)(Bus *,int inst);
  Time *(*TimeInit)(Time *,int inst);
  Pin *(*PinInit)(Pin *,int inst);
  DIORaw *(*DIORawInit)(DIORaw *,int inst);
  DIO *(*DIOInit)(DIO *,int inst);
  TWI *(*TWIInit)(TWI *,int inst);
  CAN *(*CANInit)(CAN *,int inst);
  SPI *(*SPIInit)(SPI *,int inst);
  EDIO *(*EDIOInit)(EDIO *,int inst);
  AIO *(*AIOInit)(AIO *,int inst);
};

extern ArchInfo *ArchLast, *ArchFirst;

#endif
#ifdef __AggregateDIO_H
DIO *DIOInit0(AggregateDIO *);
#endif
