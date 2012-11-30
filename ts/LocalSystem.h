#ifndef __LocalSystem_h
#define __LocalSystem_h
#undef FUNC
#ifndef SWIGGY
#define FUNC(x) (*x)
#else
#define FUNC(x) x
#endif

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
	int FUNC(CANBusGet)(LocalSystem *me,int CANInstance);
	void FUNC(BuildInfo)(LocalSystem *me,BuildInf info[1]);
	int FUNC(ModelId)(LocalSystem *me);
	int FUNC(BaseBoardId)(LocalSystem *me);
	int FUNC(MapLength)(LocalSystem *me);
	char *FUNC(MapGet)(LocalSystem *me,int MapIndex,int Value[1]);
	int FUNC(MapLookup)(LocalSystem *me,const char *String);
	char *FUNC(MapLookupPartial)(LocalSystem *me,const char *StringPrefix,int Value);
	int FUNC(MapAdd)(LocalSystem *me,const char *String,int Value);
	int FUNC(MapDelete)(LocalSystem *me,const char *String);
	char *FUNC(Note)(LocalSystem *me,const char *Message);
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
int LocalSystemCANBusGet(LocalSystem* ob,int CANInstance);
void LocalSystemBuildInfo(LocalSystem* ob,BuildInf info[1]);
int LocalSystemModelId(LocalSystem* ob);
int LocalSystemBaseBoardId(LocalSystem* ob);
int LocalSystemMapLength(LocalSystem* ob);
char *LocalSystemMapGet(LocalSystem* ob,int MapIndex,int Value[1]);
int LocalSystemMapLookup(LocalSystem* ob,const char *String);
char *LocalSystemMapLookupPartial(LocalSystem* ob,const char *StringPrefix,int Value);
int LocalSystemMapAdd(LocalSystem* ob,const char *String,int Value);
int LocalSystemMapDelete(LocalSystem* ob,const char *String);
char *LocalSystemNote(LocalSystem* ob,const char *Message);
#endif

// Author: Michael Schmidt (michael@embeddedARM.com)
// Copyright (c) 2012, Technologic Systems, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
