#ifndef __EDIO_h
#define __EDIO_h
#undef FUNC
#ifndef SWIGGY
#define FUNC(x) (*x)
#else
#define FUNC(x) x
#endif

typedef struct EDIO EDIO;
typedef enum EDIOType{
  EDIO_PWM=1,EDIO_QUADRATURE=2,EDIO_EDGECOUNT=3,EDIO_GLITCHED=4
}EDIOType;

typedef enum HBState{
  HB_LEFT=1,HB_RIGHT=2,HB_FREE_RUNNING=3,HB_BRAKING=4
}HBState;

enum {
	NetEDIO_Lock=0,
	NetEDIO_Unlock=1,
	NetEDIO_Preempt=2,
	NetEDIO_QueryFunction=3,
	NetEDIO_PWM=4,
	NetEDIO_QueryPWM=5,
	NetEDIO_PWMfd=6,
	NetEDIO_QueryPWMfd=7,
	NetEDIO_QuadratureCount=8,
	NetEDIO_EdgeCount=9,
	NetEDIO_Glitched=10,
	NetEDIO_HBridge=11,
	XEDIO_APICount=12
};
struct EDIO {
	void *FUNC(Init)(void *me,...);
	void FUNC(Fini)(void *me);
	int FUNC(Lock)(void *me,unsigned num,int flags);
	int FUNC(Unlock)(void *me,unsigned num,int flags);
	int FUNC(Preempt)(void *me);
	int *FUNC(QueryFunction)(void *me,EDIOType type);
	int FUNC(PWM)(void *me,int num,unsigned periodHigh,unsigned periodLow);
	int FUNC(QueryPWM)(void *me,int num,unsigned periodHigh[1],unsigned periodLow[1]);
	int FUNC(PWMfd)(void *me,int num,unsigned freq,unsigned DC);
	int FUNC(QueryPWMfd)(void *me,int num,unsigned freq[1],unsigned DC[1]);
	int FUNC(QuadratureCount)(void *me,int num);
	unsigned long long FUNC(EdgeCount)(void *me,int num,int edge);
	int FUNC(Glitched)(void *me,int num);
	int FUNC(HBridge)(void *me,int num,HBState state);
	int InitStatus;
};
#endif

// Author: Michael Schmidt (michael@embeddedTS.com)
// Copyright (c) 2012-2022 Technologic Systems, Inc. dba embeddedTS, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
