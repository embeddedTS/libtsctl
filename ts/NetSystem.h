#ifndef __NetSystem_H
#define __NetSystem_H
#include "Net.h"
#include "System.h"
typedef struct NetSystem NetSystem;

struct NetSystem {
  SystemAPI;
  int InitStatus;
  int inst;
  int socket;
  int mode;
  Packet *q;
  int *cmds;
};

void *NetSystemInit(NetSystem *,int socket,int inst,int mode,Packet *q,int *cmds);
void NetSystemFini(NetSystem *);
int NetSystemClassCount(NetSystem *);
int NetSystemInstanceCount(NetSystem *,int);
int NetSystemAPICount(NetSystem *,int);
int NetSystemLockCount(NetSystem *sys);
int NetSystemLockHolderInfo(NetSystem *sys,LockHolderInfo *);
int NetSystemConnWaitInfo(NetSystem *sys,int max,ConnectionWaitInfo *info);
int NetSystemCANBusGet(NetSystem *sys,int CANInst);
void NetSystemBuildInfo(NetSystem *sys,struct BuildInfo *buildinfo);
int NetSystemModelId(NetSystem *);
int NetSystemBaseBoardId(NetSystem *);
int NetSystemMapLength(NetSystem *);
int NetSystemMapGet(NetSystem *,int,char *,int *);
int NetSystemMapLookup(NetSystem *,char *);
int NetSystemMapLookupPartial(NetSystem *,char *,int,char *);
int NetSystemMapAdd(NetSystem *,char *,int);
int NetSystemMapDelete(NetSystem *,char *);


#endif
// Author: Michael Schmidt (michael@embeddedARM.com)
// Copyright (c) 2011, Technologic Systems, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
