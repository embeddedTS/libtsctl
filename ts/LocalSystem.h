#ifndef __LocalSystem_h
#define __LocalSystem_h
#undef FUNC
#ifndef SWIGGY
#define FUNC(x) (*x)
#else
#define FUNC(x) x
#endif
#include "cpp.h"

#ifndef LIBTSCTL_VERSION
#define LIBTSCTL_VERSION "1.0pre1"
#endif
#ifndef LIBTSCTL_ORGANIZATION
#define LIBTSCTL_ORGANIZATION customer
#endif
#define LIBTSCTL_FULL_VERSION LIBTSCTL_VERSION "-" STRINGIFY(LIBTSCTL_ORGANIZATION)

typedef struct LocalSystem LocalSystem;
struct LocalSystem {
	void *FUNC(Init)(LocalSystem *me);
	void FUNC(Fini)(LocalSystem *me);
	int FUNC(ClassCount)(LocalSystem *me);
	int FUNC(InstanceCount)(LocalSystem *me,int ClassNumber);
	int FUNC(APICount)(LocalSystem *me,int ClassNumber);
	int FUNC(LockCount)(LocalSystem *me);
	LockHolderInf*FUNC(LockHolderInfo)(LocalSystem *me);
	ConnectionWaitInf*FUNC(ConnWaitInfo)(LocalSystem *me);
	SystemResult FUNC(CANBusGet)(LocalSystem *me,int CANInstance);
	unsigned FUNC(BuildTime)(LocalSystem *me);
	int FUNC(ModelId)(LocalSystem *me);
	int FUNC(BaseBoardId)(LocalSystem *me);
	int FUNC(MapLength)(LocalSystem *me);
	char *FUNC(MapGet)(LocalSystem *me,int MapIndex,int Value[1]);
	int FUNC(MapLookup)(LocalSystem *me,const char *String);
	char *FUNC(MapLookupPartial)(LocalSystem *me,const char *StringPrefix,int Value);
	SystemResult FUNC(MapAdd)(LocalSystem *me,const char *String,int Value);
	SystemResult FUNC(MapDelete)(LocalSystem *me,const char *String);
	char *FUNC(Note)(LocalSystem *me,const char *Message);
	char *FUNC(Version)(LocalSystem *me);
	unsigned FUNC(UptimeServer)(LocalSystem *me);
	unsigned FUNC(UptimeHost)(LocalSystem *me);
	int FUNC(FPGARevision)(LocalSystem *me);
	int FUNC(EchoNumber)(LocalSystem *me,int n);
	int InitStatus;
	unsigned maplock;
	NameValuePair *map;
};

void *LocalSystemInit(LocalSystem* ob);
void LocalSystemFini(LocalSystem* ob);
int LocalSystemClassCount(LocalSystem* ob);
int LocalSystemInstanceCount(LocalSystem* ob,int ClassNumber);
int LocalSystemAPICount(LocalSystem* ob,int ClassNumber);
int LocalSystemLockCount(LocalSystem* ob);
LockHolderInf *LocalSystemLockHolderInfo(LocalSystem* ob);
ConnectionWaitInf *LocalSystemConnWaitInfo(LocalSystem* ob);
SystemResult LocalSystemCANBusGet(LocalSystem* ob,int CANInstance);
unsigned LocalSystemBuildTime(LocalSystem* ob);
int LocalSystemModelId(LocalSystem* ob);
int LocalSystemBaseBoardId(LocalSystem* ob);
int LocalSystemMapLength(LocalSystem* ob);
char *LocalSystemMapGet(LocalSystem* ob,int MapIndex,int Value[1]);
int LocalSystemMapLookup(LocalSystem* ob,const char *String);
char *LocalSystemMapLookupPartial(LocalSystem* ob,const char *StringPrefix,int Value);
SystemResult LocalSystemMapAdd(LocalSystem* ob,const char *String,int Value);
SystemResult LocalSystemMapDelete(LocalSystem* ob,const char *String);
char *LocalSystemNote(LocalSystem* ob,const char *Message);
char *LocalSystemVersion(LocalSystem* ob);
unsigned LocalSystemUptimeServer(LocalSystem* ob);
unsigned LocalSystemUptimeHost(LocalSystem* ob);
int LocalSystemFPGARevision(LocalSystem* ob);
int LocalSystemEchoNumber(LocalSystem* ob,int n);
#endif

// Author: Michael Schmidt (michael@embeddedARM.com)
// Copyright (c) 2012, Technologic Systems, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
