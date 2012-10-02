#include "NetDIO.h"

static DIOAPI NetDIOAPI = {
  .Init = (void *)NetDIOInit,
  .Fini = (void *)NetDIOFini,
  .Lock = (void *)NetDIOLock,
  .Refresh = (void *)NetDIORefresh,
  .Commit = (void *)NetDIOCommit,
  .Set = (void *)NetDIOSet,
  .Get = (void *)NetDIOGet,
  .SetAsync = (void *)NetDIOSetAsync,
  .GetAsync = (void *)NetDIOGetAsync,
  .Count = (void *)NetDIOCount,
  .Capabilities = (void *)NetDIOCapabilities
};

void *NetDIOInit(NetDIO *dio,int socket,int inst,int mode,Packet *q,int *cmds){
  if (dio->InitStatus > 0) return dio;
  dio->API = &NetDIOAPI;

  dio->inst = inst;
  dio->socket = socket;
  dio->InitStatus = dio->socket >= 0 ? 1 : -1;
  dio->mode = mode;
  dio->q = q;
  dio->cmds = cmds;
  return dio;
}

void NetDIOFini(NetDIO *dio){
  if (dio->InitStatus > 0) dio->InitStatus = 0;
}

void NetDIORefresh(NetDIO *dio){
  if (dio->InitStatus < 0) return;
  PacketPushCmd(dio->q,NetDIO_Refresh,dio,NetDIOClass);
  DoCmd(dio->q,dio,0);
}

void NetDIOCommit(NetDIO *dio,int forceall){
  if (dio->InitStatus < 0) return;
  PacketPushCmd(dio->q,NetDIO_Commit,dio,NetDIOClass);
  PacketPush32(dio->q,forceall);
  DoCmd(dio->q,dio,0);
}

void NetDIOSet(NetDIO *dio,int DIONum,DIOState State){
  if (dio->InitStatus < 0) return;
  PacketPushCmd(dio->q,NetDIO_Set,dio,NetDIOClass);
  PacketPush32(dio->q,DIONum);
  PacketPush32(dio->q,State);
  DoCmd(dio->q,dio,0);
}

DIOState NetDIOGet(NetDIO *dio,int DIONum){
  if (dio->InitStatus < 0) return;
  PacketPushCmd(dio->q,NetDIO_Get,dio,NetDIOClass);
  PacketPush32(dio->q,DIONum);
  return (DIOState)DoCmd(dio->q,dio,1);
}

void NetDIOSetAsync(NetDIO *dio,int DIONum,DIOState State){
  if (dio->InitStatus < 0) return;
  PacketPushCmd(dio->q,NetDIO_SetAsync,dio,NetDIOClass);
  PacketPush32(dio->q,DIONum);
  PacketPush32(dio->q,State);
  DoCmd(dio->q,dio,0);
}

DIOState NetDIOGetAsync(NetDIO *dio,int DIONum){
  if (dio->InitStatus < 0) return;
  PacketPushCmd(dio->q,NetDIO_GetAsync,dio,NetDIOClass);
  PacketPush32(dio->q,DIONum);
  return (DIOState)DoCmd(dio->q,dio,1);
}

int NetDIOLock(NetDIO *dio,int command,unsigned num) {
  if (dio->InitStatus < 0) return -999;
  PacketPushCmd(dio->q,NetDIO_Lock,dio,NetDIOClass);
  PacketPush32(dio->q,command);
  PacketPush32(dio->q,num);
  return DoCmd(dio->q,dio,1);
}

int NetDIOWait(NetDIO *dio,int *match,int min,int max,
	       int nh,int *h,int nl,int *l) {
  int i,matched;

  if (dio->InitStatus < 0) return -999;
  PacketPushCmd(dio->q,NetDIO_Wait,dio,NetDIOClass);
  PacketPush32(dio->q,min);
  PacketPush32(dio->q,max);
  PacketPush32(dio->q,nh);
  PacketPush32(dio->q,nl);
  for (i=0;i<nh;i++) {
    PacketPush32(dio->q,h[i]);
  }
  for (i=0;i<nh;i++) {
    PacketPush32(dio->q,l[i]);
  }
  matched = DoCmdBytes(dio->q,dio,1);
  for (i=0;i<matched;i++) {
    PacketPull32(dio->socket,match+i);
  }
  return matched;
}

unsigned NetDIOCount(NetDIO *dio) {
  if (dio->InitStatus < 0) return;
  PacketPushCmd(dio->q,NetDIO_Count,dio,NetDIOClass);
  return (DIOState)DoCmd(dio->q,dio,1);
}

DIOCaps NetDIOCapabilities(NetDIO *dio,unsigned num) {
  if (dio->InitStatus < 0) return;
  PacketPushCmd(dio->q,NetDIO_Capabilities,dio,NetDIOClass);
  PacketPush32(dio->q,num);
  return (DIOCaps)DoCmd8(dio->q,dio,1);
}

/* Tests
# Refresh
# Commit, Get, Set tested
tsctl DIO m4500x8200:1 Set 54 HIGH
tsctl DIO m4500x8200:1 Set 55 HIGH
tsctl DIO m4500x8200:1 Commit 0
# GetAsync tested (get status of red LED)
tsctl DIO m4500x8200:1 GetAsync 55
# SetAsync tested (turn off red LED)
tsctl DIO m4500x8200:1 SetAsync 55 0
# Lock
 */
// Author: Michael Schmidt (michael@embeddedARM.com)
// Copyright (c) 2011, Technologic Systems, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
