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

// AIO
#define AIO_PR(start,step,count) ((PeriodRange){start,step,count});
#define AIO_VR(lowstart,lowstep,lowcount,highstart,highstep,highcount) ((VoltageRange){(VoltageSubRange){lowstart,lowstep,lowcount},(VoltageSubRange){highstart,highstep,highcount}})
#define AIO_HZ(hz) ((int)(1000000000/hz))

// CAN
/*
  Raw Packet Format:

  UINT8    flags:
               control information present (reserved for future use)
               message originates from this node (unused)
               message has extended ID
               remote transmission request (RTR)
               error warning
               data overrun
               error passive
               bus error
  UINT32   id
  UINT32   timestamp_seconds
  UINT32   timestamp_microseconds
  UINT8    bytes
  UINT8[8] data
 */
#include <sys/time.h>
#include <sys/select.h>
/*
  Statistics:
  Tx count
  Rx count
  overruns
  other error counters
 */
typedef struct CANPort {
  CAN *can;
  int port;
} CANPort;


// DIO
static inline DIOState DIOValue(DIOState state) {
  switch (state) {
  case INPUT_LOW:
  case LOW:
    return LOW;
  case INPUT_HIGH:
  case HIGH:
    return HIGH;
  default: return LOW;
  }
}

static inline const char *DIOValueString(DIOState state) {
  switch(state) {
  case INPUT_LOW: return "InputLow";
  case INPUT_HIGH: return "InputHigh";
  case INPUT: return "Input";
  case LOW: return "Low";
  case HIGH: return "High";
  default: return "Invalid";
  }
}

// Pin
static inline const char *PinModeString(PinMode mode) {
  switch (mode) {
  case MODE_DIO: return "DIO";
  case MODE_CAN: return "CAN";
  case MODE_SPI: return "SPI";
  case MODE_ADC: return "ADC";
  case MODE_TWI: return "TWI";
  case MODE_UART: return "UART";
  case MODE_TS: return "TS";
  case MODE_UNKNOWN: return "UNKNOWN";
  default: return "ILLEGAL";
  }
}


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
