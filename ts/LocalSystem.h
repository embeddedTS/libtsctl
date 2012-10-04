#ifndef __LocalSystem_h
#define __LocalSystem_h
#include "System.h"


void *LocalSystemInit(System *sys);
void LocalSystemFini(System *sys);
int LocalSystemClassCount(System *sys);
int LocalSystemInstanceCount(System *sys,int class);
int LocalSystemAPICount(System *sys,int class);
int LocalSystemLockCount(System *sys);
LockHolderInf* LocalSystemLockHolderInfo(System *);
ConnectionWaitInf* LocalSystemConnWaitInfo(System *);
int LocalSystemCANBusGet(System *sys,int CANInst);
void LocalSystemBuildInfo(System *,BuildInf [1]);
int LocalSystemModelId(System *sys);
int LocalSystemBaseBoardId(System *sys);
int LocalSystemMapLength(System *sys);
char *LocalSystemMapGet(System *,int n,int [1]);
int LocalSystemMapLookup(System *,const char *);
char *LocalSystemMapLookupPartial(System *,const char *stem,int value);
int LocalSystemMapAdd(System *,const char *key,int value);
int LocalSystemMapDelete(System *,const char *key);

extern const char copyright[] __attribute__ ((weak)) ;
extern const char build[] __attribute__ ((weak)) ;
extern const char compiledate[] __attribute__ ((weak));
extern const char archstr[] __attribute__ ((weak)) ;
extern const int compiletime __attribute__ ((weak)) ;

#endif
// Author: Michael Schmidt (michael@embeddedARM.com)
// Copyright (c) 2012, Technologic Systems, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
