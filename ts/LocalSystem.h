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
	int FUNC(InstanceCount)(LocalSystem *me,int );
	int FUNC(APICount)(LocalSystem *me,int );
	int FUNC(LockCount)(LocalSystem *me);
	LockHolderInf*FUNC(LockHolderInfo)(LocalSystem *me);
	ConnectionWaitInf*FUNC(ConnWaitInfo)(LocalSystem *me);
	int FUNC(CANBusGet)(LocalSystem *me,int );
	void FUNC(BuildInfo)(LocalSystem *me,BuildInf [1]);
	int FUNC(ModelId)(LocalSystem *me);
	int FUNC(BaseBoardId)(LocalSystem *me);
	int FUNC(MapLength)(LocalSystem *me);
	char *FUNC(MapGet)(LocalSystem *me,int ,int [1]);
	int FUNC(MapLookup)(LocalSystem *me,const char *);
	char *FUNC(MapLookupPartial)(LocalSystem *me,const char *,int );
	int FUNC(MapAdd)(LocalSystem *me,const char *,int );
	int FUNC(MapDelete)(LocalSystem *me,const char *);
	int InitStatus;
	unsigned maplock;
	NameValuePair *map;
};

void *LocalSystemInit(LocalSystem* ob);
void LocalSystemFini(LocalSystem* ob);
int LocalSystemClassCount(LocalSystem* ob);
int LocalSystemInstanceCount(LocalSystem* ob,int );
int LocalSystemAPICount(LocalSystem* ob,int );
int LocalSystemLockCount(LocalSystem* ob);
LockHolderInf *LocalSystemLockHolderInfo(LocalSystem* ob);
ConnectionWaitInf *LocalSystemConnWaitInfo(LocalSystem* ob);
int LocalSystemCANBusGet(LocalSystem* ob,int );
void LocalSystemBuildInfo(LocalSystem* ob,BuildInf [1]);
int LocalSystemModelId(LocalSystem* ob);
int LocalSystemBaseBoardId(LocalSystem* ob);
int LocalSystemMapLength(LocalSystem* ob);
char *LocalSystemMapGet(LocalSystem* ob,int ,int [1]);
int LocalSystemMapLookup(LocalSystem* ob,const char *);
char *LocalSystemMapLookupPartial(LocalSystem* ob,const char *,int );
int LocalSystemMapAdd(LocalSystem* ob,const char *,int );
int LocalSystemMapDelete(LocalSystem* ob,const char *);
#endif

// Author: Michael Schmidt (michael@embeddedARM.com)
// Copyright (c) 2012, Technologic Systems, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
