#ifndef __Pin_H
#define __Pin_H

#undef FUNC
#ifndef SWIGGY
#define FUNC(x) (*x) 
#else
#define FUNC(x) x
#endif

typedef enum {
  MODE_DIO=0, MODE_CAN=1, MODE_SPI=2, MODE_ADC=3, MODE_TWI=4,
  MODE_UART=5, MODE_TS=6, MODE_BUS=7, MODE_PWM=8,
  MODE_UNKNOWN=-1
} PinMode;

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

typedef struct Pin Pin;
typedef struct PinAPI PinAPI;


struct PinAPI {
  void *FUNC(Init)(void *me,...);
  void FUNC(Fini)(void *me);
  int FUNC(Lock)(void *me,unsigned num,int flags);
  int FUNC(Unlock)(void *me,unsigned num,int flags);
  int FUNC(Preempt)(void *me);
  PinMode FUNC(ModeGet)(void *me,int pin);
  int FUNC(ModeSet)(void *me,int pin,PinMode mode);
};

enum {
  NetPin_Lock=0,
  NetPin_Unlock=1,
  NetPin_Preempt=2,
  NetPin_ModeGet=3,
  NetPin_ModeSet=4
};
#define Pin_APICount (1+NetPin_ModeSet)

struct Pin {
  PinAPI;
  int InitStatus;
  unsigned LockBase;
  int deferlock;
};

enum {
  PinErrorModeInvalid = -100
};

/*
  The "pin" argument must correspond to the logical DIO number
  which is on the pin.  If there is no logical DIO number, then
  the number that would be used if there was one should be used.
 */
#endif
// Author: Michael Schmidt (michael@embeddedARM.com)
// Copyright (c) 2011, Technologic Systems, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
