#ifndef __Pin_h
#define __Pin_h
#undef FUNC
#ifndef SWIGGY
#define FUNC(x) (*x)
#else
#define FUNC(x) x
#endif

typedef struct Pin Pin;
typedef enum PinMode{
  MODE_DIO=0,MODE_CAN=1,MODE_SPI=2,MODE_ADC=3,MODE_TWI=4,MODE_UART=5,MODE_TS=6,MODE_BUS=7,MODE_PWM=8,MODE_UNKNOWN=-1
}PinMode;

typedef enum PinError{
  PinErrorModeInvalid=-100
}PinError;

enum {
	NetPin_Lock=0,
	NetPin_Unlock=1,
	NetPin_Preempt=2,
	NetPin_ModeGet=3,
	NetPin_ModeSet=4,
	XPin_APICount=5
};
struct Pin {
	void *FUNC(Init)(void *me,...);
	void FUNC(Fini)(void *me);
	int FUNC(Lock)(void *me,unsigned num,int flags);
	int FUNC(Unlock)(void *me,unsigned num,int flags);
	int FUNC(Preempt)(void *me);
	PinMode FUNC(ModeGet)(void *me,int pin);
	int FUNC(ModeSet)(void *me,int pin,PinMode mode);
	int InitStatus;
	unsigned LockBase;
	int deferlock;
};
#endif

// Author: Michael Schmidt (michael@embeddedARM.com)
// Copyright (c) 2012, Technologic Systems, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
