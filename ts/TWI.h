#ifndef __TWI_h
#define __TWI_h
#undef FUNC
#ifndef SWIGGY
#define FUNC(x) (*x)
#else
#define FUNC(x) x
#endif

typedef struct TWI TWI;
typedef enum TWIMode{
  TWIModeSlave=0,TWIModeMaster=1
}TWIMode;

typedef enum TWIError{
  TWIErrorPortInvalid=-1,TWIErrorModeUnsupported=-2,TWIErrorBaudUnconstrained=-3,TWIErrorHardware=-4,TWIErrorHandle=-5,TWIErrorWriteNAck=-6,TWIErrorDataNAck=-7,TWIErrorReadNack=-8,TWIErrorSDALow=-9,TWIErrorSCLLow=-10,TWIErrorAdrsLen=-11,TWIErrorTimeout=-12,TWIErrorOverrun=-13,TWIErrorArbLost=-14,TWIErrorUnknown=-999,TWIErrorOpInvalid=-15
}TWIError;

typedef enum TWIOps{
  TWIOpWrite=0,TWIOpRead=1
}TWIOps;

enum {
	NetTWI_Lock=0,
	NetTWI_Unlock=1,
	NetTWI_Preempt=2,
	NetTWI_Write=3,
	NetTWI_Read=4,
	XTWI_APICount=5
};
struct TWI {
	void *FUNC(Init)(void *me,...);
	void FUNC(Fini)(void *me);
	int FUNC(Lock)(void *me,unsigned num,int flags);
	int FUNC(Unlock)(void *me,unsigned num,int flags);
	int FUNC(Preempt)(void *me);
	int FUNC(Write)(void *me,int devadr,int adrslen,int adrs,const char *bytes);
	int FUNC(Read)(void *me,int devadr,int adrslen,int adrs,char *bytes);
	int InitStatus;
};
#endif

// Author: Michael Schmidt (michael@embeddedARM.com)
// Copyright (c) 2012, Technologic Systems, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
