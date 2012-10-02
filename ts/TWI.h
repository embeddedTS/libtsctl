#ifndef __TWI_H
#define __TWI_H
#undef FUNC
#ifndef SWIGGY
#define FUNC(x) (*x) 
#else
#define FUNC(x) x
#endif

// TWIOpen modes
static const int TWIModeSlave = 0;
static const int TWIModeMaster = 1;

// TWIOpen error codes
static const int TWIErrorPortInvalid = -1;
static const int TWIErrorModeUnsupported = -2;
static const int TWIErrorBaudUnconstrained = -3;
static const int TWIErrorHardware = -4;

// TWIStart ops
static const int TWIOpWrite = 0;
static const int TWIOpRead = 1;

// TWI error codes for functions other than TWIOpen
static const int TWIErrorHandle =-1;
static const int TWIErrorWriteNAck = -2;
static const int TWIErrorDataNAck = -3;
static const int TWIErrorReadNack = -4;
static const int TWIErrorSDALow = -5;
static const int TWIErrorSCLLow = -6;
static const int TWIErrorAdrsLen = -7;
static const int TWIErrorTimeout = -8;
static const int TWIErrorOverrun = -9;
static const int TWIErrorArbLost = -10;
static const int TWIErrorUnknown = -999;
static const int TWIErrorOpInvalid = -7;

typedef struct TWI TWI;
typedef struct TWIAPI TWIAPI;

struct TWIAPI {
  void *FUNC(Init)(void *me,...);
  void FUNC(Fini)(void *me);
  int FUNC(Lock)(void *me,unsigned num,int flags);
  int FUNC(Unlock)(void *me,unsigned num,int flags);
  int FUNC(Preempt)(void *me);
  int FUNC(Write)(void *me,int devadr,int adrslen,int adrs,const char* bytes);
  int FUNC(Read)(void *me,int devadr,int adrslen,int adrs,char* bytes);
};

struct TWI {
  TWIAPI;
  int InitStatus;
};

enum {
  NetTWI_Lock=0,
  NetTWI_Unlock=1,
  NetTWI_Preempt=2,
  NetTWI_Write=3,
  NetTWI_Read=4
};
#define TWI_APICount (1+NetTWI_Read)

#endif
// Author: Michael Schmidt (michael@embeddedARM.com)
// Copyright (c) 2011, Technologic Systems, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
