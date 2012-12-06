#ifndef __System_h
#define __System_h
#undef FUNC
#ifndef SWIGGY
#define FUNC(x) (*x)
#else
#define FUNC(x) x
#endif

typedef struct LockHolderInf LockHolderInf;
typedef struct ConnectionWaitInf ConnectionWaitInf;
typedef struct BuildInf BuildInf;
typedef struct NameValuePair NameValuePair;
typedef struct System System;
struct LockHolderInf {
  int pid;
  int count;
};

struct ConnectionWaitInf {
  int pid;
  int wait;
};

struct BuildInf {
  unsigned buildNumber;
  int buildTime;
  unsigned uptime;
  char *hostname;
  char *arch;
};

struct NameValuePair {
  char *name;
  int value;
};

typedef enum SystemResult{
  SystemSuccess=1,SystemErrorNoSuchKey=-1,SystemErrorNoSuchCANInstance=-2
}SystemResult;

enum {
	NetSystem_ClassCount=0,
	NetSystem_InstanceCount=1,
	NetSystem_APICount=2,
	NetSystem_LockCount=3,
	NetSystem_LockHolderInfo=4,
	NetSystem_ConnWaitInfo=5,
	NetSystem_CANBusGet=6,
	NetSystem_BuildTime=7,
	NetSystem_ModelId=8,
	NetSystem_BaseBoardId=9,
	NetSystem_MapLength=10,
	NetSystem_MapGet=11,
	NetSystem_MapLookup=12,
	NetSystem_MapLookupPartial=13,
	NetSystem_MapAdd=14,
	NetSystem_MapDelete=15,
	NetSystem_Note=16,
	NetSystem_Version=17,
	NetSystem_UptimeServer=18,
	NetSystem_UptimeHost=19,
	NetSystem_FPGARevision=20,
	NetSystem_EchoNumber=21,
	XSystem_APICount=22
};
struct System {
	void *FUNC(Init)(void *me,...);
	void FUNC(Fini)(void *me);
	int FUNC(ClassCount)(void *me);
	int FUNC(InstanceCount)(void *me,int ClassNumber);
	int FUNC(APICount)(void *me,int ClassNumber);
	int FUNC(LockCount)(void *me);
	LockHolderInf*FUNC(LockHolderInfo)(void *me);
	ConnectionWaitInf*FUNC(ConnWaitInfo)(void *me);
	SystemResult FUNC(CANBusGet)(void *me,int CANInstance);
	unsigned FUNC(BuildTime)(void *me);
	int FUNC(ModelId)(void *me);
	int FUNC(BaseBoardId)(void *me);
	int FUNC(MapLength)(void *me);
	char *FUNC(MapGet)(void *me,int MapIndex,int Value[1]);
	int FUNC(MapLookup)(void *me,const char *String);
	char *FUNC(MapLookupPartial)(void *me,const char *StringPrefix,int Value);
	SystemResult FUNC(MapAdd)(void *me,const char *String,int Value);
	SystemResult FUNC(MapDelete)(void *me,const char *String);
	char *FUNC(Note)(void *me,const char *Message);
	char *FUNC(Version)(void *me);
	unsigned FUNC(UptimeServer)(void *me);
	unsigned FUNC(UptimeHost)(void *me);
	int FUNC(FPGARevision)(void *me);
	int FUNC(EchoNumber)(void *me,int );
	int InitStatus;
	unsigned maplock;
	NameValuePair *map;
};
#endif

// Author: Michael Schmidt (michael@embeddedARM.com)
// Copyright (c) 2012, Technologic Systems, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
