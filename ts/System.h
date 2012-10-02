#ifndef __SYSTEM_H
#define __SYSTEM_H
#undef FUNC
#ifndef SWIGGY
#define FUNC(x) (*x) 
#else
#define FUNC(x) x
#endif

#include "Array.h"

typedef struct System System;
typedef struct SystemAPI SystemAPI;

typedef struct LockHolderInfo {
  int pid;
  int count;
} LockHolderInfo;

typedef struct ConnectionWaitInfo {
  int pid;
  int wait; // lock waited for, or -1 if none
} ConnectionWaitInfo;

typedef struct BuildInfo {
  unsigned buildNumber;
  int buildTime;
  unsigned uptime;
  char* hostname;
  char* arch;
} BuildInfo;

typedef struct NameValuePair {
  char* name;
  int value;
} NameValuePair;

struct SystemAPI {
  void *FUNC(Init)(void *me,...);
  void FUNC(Fini)(void *me);
  int FUNC(ClassCount)(void *me);
  int FUNC(InstanceCount)(void *me,int);
  int FUNC(APICount)(void *me,int);
  int FUNC(LockCount)(void *me);
  LockHolderInfo *FUNC(LockHolderInfo)(void *me);
  ConnectionWaitInfo *FUNC(ConnWaitInfo)(void *me);
  int FUNC(CANBusGet)(void *me,int);
  void FUNC(BuildInfo)(void *me,BuildInfo [1]);
  int FUNC(ModelId)(void *me);
  int FUNC(BaseBoardId)(void *me);
  int FUNC(MapLength)(void *me);
  char* FUNC(MapGet)(void *me,int,int [1]);
  int FUNC(MapLookup)(void *me,const char*);
  char* FUNC(MapLookupPartial)(void *me,const char*,int);
  int FUNC(MapAdd)(void *me,const char*,int);
  int FUNC(MapDelete)(void *me,const char*);
};

struct System {
  SystemAPI;
  int InitStatus;
  unsigned maplock;
  NameValuePair *map;
};

enum {
  NetSystem_ClassCount=0,
  NetSystem_InstanceCount=1,
  NetSystem_APICount=2,
  NetSystem_LockCount=3,
  NetSystem_LockHolderInfo=4,
  NetSystem_ConnWaitInfo=5,
  NetSystem_CANBusGet=6,
  NetSystem_BuildInfo=7,
  NetSystem_ModelId=8,
  NetSystem_BaseBoardId=9,
  NetSystem_MapLength=10,
  NetSystem_MapGet=11,
  NetSystem_MapLookup=12,
  NetSystem_MapLookupPartial=13,
  NetSystem_MapAdd=14,
  NetSystem_MapDelete=15
};
#define System_APICount (1+NetSystem_MapDelete)
#endif
// Author: Michael Schmidt (michael@embeddedARM.com)
// Copyright (c) 2011, Technologic Systems, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
