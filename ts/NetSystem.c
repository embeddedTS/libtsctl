#include <string.h>
#include "NetSystem.h"

static SystemAPI NetSystemAPI = {
  .Init = (void *)NetSystemInit,
  .Fini = (void *)NetSystemFini,
  .ClassCount = (void *)NetSystemClassCount,
  .InstanceCount = (void *)NetSystemInstanceCount,
  .APICount = (void *)NetSystemAPICount,
  .LockCount = (void *)NetSystemLockCount,
  .LockHolderInfo = (void *)NetSystemLockHolderInfo,
  .ConnWaitInfo = (void *)NetSystemConnWaitInfo,
  .CANBusGet = (void *)NetSystemCANBusGet,
  .BuildInfo = (void *)NetSystemBuildInfo,
  .ModelId = (void *)NetSystemModelId,
  .BaseBoardId = (void *)NetSystemBaseBoardId,
  .MapLength = (void *)NetSystemMapLength,
  .MapGet = (void *)NetSystemMapGet,
  .MapLookup = (void *)NetSystemMapLookup,
  .MapLookupPartial = (void *)NetSystemMapLookupPartial,
  .MapAdd = (void *)NetSystemMapAdd,
  .MapDelete = (void *)NetSystemMapDelete
};

void *NetSystemInit(NetSystem *sys,int socket,int inst,int mode,
		    Packet *q,int *cmds) {
  if (sys->InitStatus > 0) return sys;
  sys->API = &NetSystemAPI;

  sys->inst = inst;
  sys->socket = socket;
  sys->InitStatus = sys->socket >= 0 ? 1 : -1;
  sys->mode = mode;
  sys->q = q;
  sys->cmds = cmds;
  return sys;

}

void NetSystemFini(NetSystem *sys){
  if (sys->InitStatus > 0) sys->InitStatus = 0;
}

int NetSystemClassCount(NetSystem *sys){
  if (sys->InitStatus < 0) return;
  PacketPushCmd(sys->q,NetSystem_ClassCount,sys,NetSystemClass);
  return DoCmd(sys->q,sys,1);
}

int NetSystemInstanceCount(NetSystem *sys,int class){
  if (sys->InitStatus < 0) return;
  PacketPushCmd(sys->q,NetSystem_InstanceCount,sys,NetSystemClass);
  PacketPush32(sys->q,class);
  return DoCmd(sys->q,sys,1);
}

int NetSystemAPICount(NetSystem *sys,int class){
  if (sys->InitStatus < 0) return;
  PacketPushCmd(sys->q,NetSystem_APICount,sys,NetSystemClass);
  PacketPush32(sys->q,class);
  return DoCmd(sys->q,sys,1);
}

int NetSystemLockCount(NetSystem *sys) {
  if (sys->InitStatus < 0) return;
  PacketPushCmd(sys->q,NetSystem_LockCount,sys,NetSystemClass);
  return DoCmd(sys->q,sys,1);  
}

int NetSystemLockHolderInfo(NetSystem *sys,LockHolderInfo *info) {
  int i,count;
  if (sys->InitStatus < 0) return;
  PacketPushCmd(sys->q,NetSystem_LockHolderInfo,sys,NetSystemClass);
  count = DoCmd(sys->q,sys,1);
  for (i=0;i<count;i++) {
    if (PacketPull32(sys->socket,&info[i].pid) != 4) return i;
    if (PacketPull32(sys->socket,&info[i].count) != 4) return i;
  }
  return i;
}

int NetSystemConnWaitInfo(NetSystem *sys,int max,ConnectionWaitInfo *info) {
  int i,count;
  if (sys->InitStatus < 0) return;
  PacketPushCmd(sys->q,NetSystem_ConnWaitInfo,sys,NetSystemClass);
  PacketPush32(sys->q,max);
  count = DoCmd(sys->q,sys,1);
  for (i=0;i<count;i++) {
    if (PacketPull32(sys->socket,&info[i].pid) != 4) return i;
    if (PacketPull32(sys->socket,&info[i].wait) != 4) return i;
  }
  return i;

}

int NetSystemCANBusGet(NetSystem *sys,int CANInst) {
  if (sys->InitStatus < 0) return;
  PacketPushCmd(sys->q,NetSystem_CANBusGet,sys,NetSystemClass);
  PacketPush32(sys->q,CANInst);
  return DoCmd(sys->q,sys,1);
}

void NetSystemBuildInfo(NetSystem *sys,struct BuildInfo *buildinfo) {
  unsigned char i,len;

  if (sys->InitStatus < 0) return;
  PacketPushCmd(sys->q,NetSystem_BuildInfo,sys,NetSystemClass);
  buildinfo->buildNumber = DoCmd(sys->q,sys,1);
  PacketPull32(sys->socket,&buildinfo->buildTime);
  PacketPull32(sys->socket,&buildinfo->uptime);
  PacketPull8(sys->socket,&len);
  PacketPullBytes(sys->socket,len,buildinfo->hostname);
  buildinfo->hostname[len] = 0;
  PacketPull8(sys->socket,&len);
  PacketPullBytes(sys->socket,len,buildinfo->arch);
  buildinfo->arch[len] = 0;
}

int NetSystemModelId(NetSystem *sys) {
  if (sys->InitStatus < 0) return;
  PacketPushCmd(sys->q,NetSystem_ModelId,sys,NetSystemClass);
  return DoCmd(sys->q,sys,1);
}

int NetSystemBaseBoardId(NetSystem *sys) {
  if (sys->InitStatus < 0) return;
  PacketPushCmd(sys->q,NetSystem_BaseBoardId,sys,NetSystemClass);
  return DoCmd(sys->q,sys,1);
}

int NetSystemMapLength(NetSystem *sys){
  if (sys->InitStatus < 0) return;
  PacketPushCmd(sys->q,NetSystem_MapLength,sys,NetSystemClass);
  return DoCmd(sys->q,sys,1);
}

int NetSystemMapGet(NetSystem *sys,int num,char *dest,int *value){
  unsigned char l;
  if (sys->InitStatus < 0) return;
  PacketPushCmd(sys->q,NetSystem_MapGet,sys,NetSystemClass);
  PacketPush32(sys->q,num);
  *value = DoCmd(sys->q,sys,1);
  PacketPull8(sys->socket,&l);
  PacketPullBytes(sys->socket,l,dest);
  return l;
}

int NetSystemMapLookup(NetSystem *sys,char *name){
  int len = strlen(name);
  if (sys->InitStatus < 0) return;
  PacketPushCmd(sys->q,NetSystem_MapLookup,sys,NetSystemClass);
  PacketPush8(sys->q,len);
  PacketPushBytes(sys->q,len,name);
  return DoCmd(sys->q,sys,1);
}

int NetSystemMapLookupPartial(NetSystem *sys,char *name,int value,char *dest){
  int len = strlen(name);
  if (sys->InitStatus < 0) return;
  PacketPushCmd(sys->q,NetSystem_MapLookupPartial,sys,NetSystemClass);
  PacketPush32(sys->q,value);
  PacketPush8(sys->q,len);
  PacketPushBytes(sys->q,len,name);
  len = DoCmd8(sys->q,sys,1);
  PacketPullBytes(sys->socket,len,dest);
  return len;
}

int NetSystemMapAdd(NetSystem *sys,char *name,int value){
  int len = strlen(name);
  if (sys->InitStatus < 0) return;
  PacketPushCmd(sys->q,NetSystem_MapAdd,sys,NetSystemClass);
  PacketPush32(sys->q,value);
  PacketPush8(sys->q,len);
  PacketPushBytes(sys->q,len,name);
  return DoCmd(sys->q,sys,1);
}

int NetSystemMapDelete(NetSystem *sys,char *name){
  int len = strlen(name);
  if (sys->InitStatus < 0) return;
  PacketPushCmd(sys->q,NetSystem_MapDelete,sys,NetSystemClass);
  PacketPush8(sys->q,len);
  PacketPushBytes(sys->q,len,name);
  return DoCmd(sys->q,sys,1);
}


/*
Tests:
# ClassCount
tsctl System m4500x8200:0 ClassCount
# InstanceCount
tsctl System m4500x8200:0 InstanceCount 1
# APICount
tsctl System m4500x8200:0
tsctl System m4500x8200:0 APICount 1

 */
// Author: Michael Schmidt (michael@embeddedARM.com)
// Copyright (c) 2011, Technologic Systems, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
