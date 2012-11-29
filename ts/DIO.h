#ifndef __DIO_h
#define __DIO_h
#undef FUNC
#ifndef SWIGGY
#define FUNC(x) (*x)
#else
#define FUNC(x) x
#endif

typedef struct DIO DIO;
typedef enum DIOState{
  INPUT_LOW=-3,INPUT_HIGH=-2,INPUT=-1,LOW=0,HIGH=1
}DIOState;

typedef enum DIOCaps{
  DIO_NOT_PRESENT=0,DIO_CAN_INPUT=1,DIO_CAN_DRIVE_HIGH=2,DIO_HIGH_SIDE=3,DIO_CAN_DRIVE_LOW=4,DIO_LOW_SIDE=5,DIO_OUTPUT_ONLY=6,DIO_NORMAL=7
}DIOCaps;

enum {
	NetDIO_Lock=0,
	NetDIO_Unlock=1,
	NetDIO_Preempt=2,
	NetDIO_Refresh=3,
	NetDIO_Commit=4,
	NetDIO_Set=5,
	NetDIO_Get=6,
	NetDIO_SetAsync=7,
	NetDIO_GetAsync=8,
	NetDIO_Wait=9,
	NetDIO_Count=10,
	NetDIO_Capabilities=11,
	NetDIO_GetMulti=12,
	XDIO_APICount=13
};
struct DIO {
	void *FUNC(Init)(void *me,...);
	void FUNC(Fini)(void *me);
	int FUNC(Lock)(void *me,unsigned num,int flags);
	int FUNC(Unlock)(void *me,unsigned num,int flags);
	int FUNC(Preempt)(void *me);
	void FUNC(Refresh)(void *me);
	void FUNC(Commit)(void *me,int ForceAll);
	void FUNC(Set)(void *me,int DIONum,DIOState State);
	DIOState FUNC(Get)(void *me,int DIONum);
	void FUNC(SetAsync)(void *me,int DIONum,DIOState State);
	DIOState FUNC(GetAsync)(void *me,int DIONum);
	void FUNC(Wait)(void *me,int *match,int min,int max,const int *nh,const int *nl);
	unsigned FUNC(Count)(void *me);
	DIOCaps FUNC(Capabilities)(void *me,unsigned num);
	int FUNC(GetMulti)(void *me,char *state,int offset);
	int InitStatus;
};
#endif

// Author: Michael Schmidt (michael@embeddedARM.com)
// Copyright (c) 2012, Technologic Systems, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
