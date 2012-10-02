#include "NetDIORaw.h"

static DIORawAPI NetDIORawAPI = {
  .Init = (void *)NetDIORawInit,
  .Fini = (void *)NetDIORawFini,
  .Lock = (void *)NetDIORawLock,
  .DirSet = (void *)NetDIORawDirSet,
  .DataSet = (void *)NetDIORawDataSet,
  .DirGet = (void *)NetDIORawDirGet,
  .DataGet = (void *)NetDIORawDataGet,
  .Count = (void *)NetDIORawCount
};

void *NetDIORawInit(NetDIORaw *dio,int socket,int inst,int mode,Packet *q,int *cmds){
  if (dio->InitStatus > 0) return dio;
  dio->API = &NetDIORawAPI;

  dio->inst = inst;
  dio->socket = socket;
  dio->InitStatus = dio->socket >= 0 ? 1 : -1;
  dio->mode = mode;
  dio->q = q;
  dio->cmds = cmds;
  return dio;
}

void NetDIORawFini(NetDIORaw *dio){
  if (dio->InitStatus > 0) dio->InitStatus = 0;
}

void NetDIORawDirSet(NetDIORaw *dio,int Num,int asOutput) {
  if (dio->InitStatus < 0) return;
  PacketPushCmd(dio->q,NetDIORaw_DirSet,dio,NetDIORawClass);
  PacketPush32(dio->q,Num);
  PacketPush32(dio->q,asOutput);
  DoCmd(dio->q,dio,0);
}

void NetDIORawDataSet(NetDIORaw *dio,int Num,int asHigh) {
  if (dio->InitStatus < 0) return;
  PacketPushCmd(dio->q,NetDIORaw_DataSet,dio,NetDIORawClass);
  PacketPush32(dio->q,Num);
  PacketPush32(dio->q,asHigh);
  DoCmd(dio->q,dio,0);
}

int NetDIORawDirGet(NetDIORaw *dio,int Num) {
  if (dio->InitStatus < 0) return -1;
  PacketPushCmd(dio->q,NetDIORaw_DirGet,dio,NetDIORawClass);
  PacketPush32(dio->q,Num);
  return DoCmd(dio->q,dio,1);
}

int NetDIORawDataGet(NetDIORaw *dio,int Num) {
  if (dio->InitStatus < 0) return -1;
  PacketPushCmd(dio->q,NetDIORaw_DataGet,dio,NetDIORawClass);
  PacketPush32(dio->q,Num);
  return DoCmd(dio->q,dio,1);
}

int NetDIORawLock(NetDIORaw *dio,int command,unsigned num) {
  if (dio->InitStatus < 0) return -1;
  PacketPushCmd(dio->q,NetDIORaw_Lock,dio,NetDIORawClass);
  PacketPush32(dio->q,command);
  PacketPush32(dio->q,num);
  return DoCmd(dio->q,dio,1);
}

unsigned NetDIORawCount(NetDIORaw *dio) {
  if (dio->InitStatus < 0) return -1;
  PacketPushCmd(dio->q,NetDIORaw_Count,dio,NetDIORawClass);
  return DoCmd(dio->q,dio,1);  
}

/* Tests
# DirSet
tsctl DIORaw m4500x8200:0 DirSet 54 1
# DataSet
tsctl DIORaw m4500x8200:0 DataSet 54 1
# DirGet
tsctl DIORaw m4500x8200:0 DirGet 54
# DataGet
tsctl DIORaw m4500x8200:0 DataGet 54
*/

// Author: Michael Schmidt (michael@embeddedARM.com)
// Copyright (c) 2011, Technologic Systems, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
