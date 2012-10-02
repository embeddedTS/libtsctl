#include "NetAIO.h"

static AIOAPI NetAIOAPI = {
  .Init = (void *)NetAIOInit,
  .Fini = (void *)NetAIOFini,
  .Lock = (void *)NetAIOLock,
  .Type = (void *)NetAIOType,
  .VoltageRangeListLength = (void *)NetAIOVoltageRangeListLength,
  .VoltageRange = (void *)NetAIOVoltageRange,
  .PrecisionList = (void *)NetAIOPrecisionList,
  .PeriodRangeListLength = (void *)NetAIOPeriodRangeListLength,
  .PeriodRange = (void *)NetAIOPeriodRange,
  .TriggerListLength = (void *)NetAIOTriggerListLength,
  .TriggerList = (void *)NetAIOTriggerList,
  .Channels = (void *)NetAIOChannels,
  .Configuration = (void *)NetAIOConfiguration,
  .ConfigureTest = (void *)NetAIOConfigureTest,
  .Configure = (void *)NetAIOConfigure,
  .ITrig = (void *)NetAIOITrig,
  .Get = (void *)NetAIOGet,
  .Put = (void *)NetAIOPut,
  .Ready = (void *)NetAIOReady,
  .Gets = (void *)NetAIOGets,
  .Puts = (void *)NetAIOPuts,
  .Readys = (void *)NetAIOReadys
};

void *NetAIOInit(NetAIO *aio,int socket,int inst,int mode,Packet *q,int *cmds){
  if (aio->InitStatus > 0) return aio;
  aio->API = &NetAIOAPI;

  aio->inst = inst;
  aio->socket = socket;
  aio->InitStatus = aio->socket >= 0 ? 1 : -1;
  aio->mode = mode;
  aio->q = q;
  aio->cmds = cmds;
  return aio;
}

void NetAIOFini(NetAIO *aio){
  if (aio->InitStatus > 0) aio->InitStatus = 0;
}

int NetAIOLock(NetAIO *aio,int command,unsigned num) {
  if (aio->InitStatus < 0) return -999;
  PacketPushCmd(aio->q,NetAIO_Lock,aio,NetAIOClass);
  PacketPush32(aio->q,command);
  PacketPush32(aio->q,num);
  return DoCmd(aio->q,aio,1);
}

AIOType NetAIOType(NetAIO *aio) {
  if (aio->InitStatus < 0) return;
  PacketPushCmd(aio->q,NetAIO_Type,aio,NetAIOClass);
  return DoCmd(aio->q,aio,1);
}
                                                 
int NetAIOVoltageRangeListLength(NetAIO *aio) {
  if (aio->InitStatus < 0) return;
  PacketPushCmd(aio->q,NetAIO_VoltageRangeListLength,aio,NetAIOClass);
  return DoCmd(aio->q,aio,1);
}
                                   
int NetAIOVoltageRange(NetAIO *aio,int i,VoltageRange *r) {
  if (aio->InitStatus < 0) return;
  PacketPushCmd(aio->q,NetAIO_VoltageRange,aio,NetAIOClass);
  PacketPush32(aio->q,i);
  int ret = DoCmd(aio->q,aio,1);
  PacketPull32(aio->socket,&r->low.start);
  PacketPull32(aio->socket,&r->low.step);
  PacketPull32(aio->socket,&r->low.count);
  PacketPull32(aio->socket,&r->high.start);
  PacketPull32(aio->socket,&r->high.step);
  PacketPull32(aio->socket,&r->high.count);
  return ret;
}
                        
int NetAIOPrecisionList(NetAIO *aio) {
  if (aio->InitStatus < 0) return;
  PacketPushCmd(aio->q,NetAIO_PrecisionList,aio,NetAIOClass);
  return DoCmd(aio->q,aio,1);
}
                                            
int NetAIOPeriodRangeListLength(NetAIO *aio) {
  if (aio->InitStatus < 0) return;
  PacketPushCmd(aio->q,NetAIO_PeriodRangeListLength,aio,NetAIOClass);
  return DoCmd(aio->q,aio,1);
}
                                      
int NetAIOPeriodRange(NetAIO *aio,int i,PeriodRange *r) {
  if (aio->InitStatus < 0) return;
  PacketPushCmd(aio->q,NetAIO_PeriodRange,aio,NetAIOClass);
  PacketPush32(aio->q,i);
  int ret = DoCmd(aio->q,aio,1);
  PacketPull32(aio->socket,&r->start);
  PacketPull32(aio->socket,&r->step);
  PacketPull32(aio->socket,&r->count);
  return ret;
}
                   
int NetAIOTriggerListLength(NetAIO *aio) {
  if (aio->InitStatus < 0) return;
  PacketPushCmd(aio->q,NetAIO_TriggerListLength,aio,NetAIOClass);
  return DoCmd(aio->q,aio,1);
}
                                        
int NetAIOTriggerList(NetAIO *aio,int *tlist) {
  if (aio->InitStatus < 0) return;
  PacketPushCmd(aio->q,NetAIO_TriggerList,aio,NetAIOClass);
  PacketPush32(aio->q,i);
  int i,ret = DoCmd(aio->q,aio,1);
  for (i=0;i<ret;i++) {
    PacketPull32(aio->socket,tlist+i);
  }
  return ret;
}
                                   
int NetAIOChannels(NetAIO *aio) {
  if (aio->InitStatus < 0) return;
  PacketPushCmd(aio->q,NetAIO_Channels,aio,NetAIOClass);
  return DoCmd(aio->q,aio,1);
}
           
int NetAIOConfiguration(NetAIO *aio,float *low,float *high,int *prec,int *t,int *trigger,int *itrig) {
  if (aio->InitStatus < 0) return;
  PacketPushCmd(aio->q,NetAIO_Configuration,aio,NetAIOClass);
  PacketPush32(aio->q,i);
  int i,ret = DoCmd(aio->q,aio,1);
  for (i=0;i<ret;i++) {
    PacketPull32(aio->socket,low+i);
  }
  for (i=0;i<ret;i++) {
    PacketPull32(aio->socket,high+i);
  }
  for (i=0;i<ret;i++) {
    PacketPull32(aio->socket,prec+i);
  }
  for (i=0;i<ret;i++) {
    PacketPull32(aio->socket,t+i);
  }
  for (i=0;i<ret;i++) {
    PacketPull32(aio->socket,trigger+i);
  }
  PacketPull32(aio->socket,itrig);
  return ret;
}

int NetAIOConfigureTest(NetAIO *aio,int count,float *low,float *high,int *prec,int *t,int *trigger,int itrig) {
  int i;

  if (aio->InitStatus < 0) return;
  PacketPushCmd(aio->q,NetAIO_ConfigureTest,aio,NetAIOClass);
  PacketPush32(aio->q,count);
  for (i=0;i<count;i++) {
    PacketPush32(aio->q,low[i]);
  }
  for (i=0;i<count;i++) {
    PacketPush32(aio->q,high[i]);
  }
  for (i=0;i<count;i++) {
    PacketPush32(aio->q,prec[i]);
  }
  for (i=0;i<count;i++) {
    PacketPush32(aio->q,t[i]);
  }
  for (i=0;i<count;i++) {
    PacketPush32(aio->q,trigger[i]);
  }
  PacketPush32(aio->q,itrig);
  return DoCmd(aio->q,aio,1);
}

int NetAIOConfigure(NetAIO *aio,int count,float *low,float *high,int *prec,int *t,int *trigger,int itrig) {
  int i;

  if (aio->InitStatus < 0) return;
  PacketPushCmd(aio->q,NetAIO_Configure,aio,NetAIOClass);
  PacketPush32(aio->q,count);
  for (i=0;i<count;i++) {
    PacketPush32(aio->q,low[i]);
  }
  for (i=0;i<count;i++) {
    PacketPush32(aio->q,high[i]);
  }
  for (i=0;i<count;i++) {
    PacketPush32(aio->q,prec[i]);
  }
  for (i=0;i<count;i++) {
    PacketPush32(aio->q,t[i]);
  }
  for (i=0;i<count;i++) {
    PacketPush32(aio->q,trigger[i]);
  }
  PacketPush32(aio->q,itrig);
  return DoCmd(aio->q,aio,1);
}
 
int NetAIOITrig(NetAIO *,int itrig) {
  if (aio->InitStatus < 0) return;
  PacketPushCmd(aio->q,NetAIO_ITrig,aio,NetAIOClass);
  PacketPush32(aio->q,itrig);
  return DoCmd(aio->q,aio,1);
}

int NetAIOGet(NetAIO *aio,int ch) {
  if (aio->InitStatus < 0) return;
  PacketPushCmd(aio->q,NetAIO_Get,aio,NetAIOClass);
  PacketPush32(aio->q,ch);
  return DoCmd(aio->q,aio,1);
}
                                          
int NetAIOPut(NetAIO *aio,int ch,int value) {
  if (aio->InitStatus < 0) return;
  PacketPushCmd(aio->q,NetAIO_Put,aio,NetAIOClass);
  PacketPush32(aio->q,ch);
  PacketPush32(aio->q,value);
  return DoCmd(aio->q,aio,1);
}
                                
int NetAIOReady(NetAIO *aio,int ch) {
  if (aio->InitStatus < 0) return;
  PacketPushCmd(aio->q,NetAIO_Ready,aio,NetAIOClass);
  PacketPush32(aio->q,ch);
  return DoCmd(aio->q,aio,1);
}
                                        
int NetAIOGets(NetAIO *aio,int samples,void *buf) {
  if (aio->InitStatus < 0) return;
  PacketPushCmd(aio->q,NetAIO_Gets,aio,NetAIOClass);
  PacketPush32(aio->q,buffer);
  PacketPush32(aio->q,samples);
  int i,ret = DoCmd(aio->q,aio,1);
  int bps;
  PacketPull32(aio->socket,&bps);
  if (ret > 0) {
    PacketPull32(aio->socket,bps*ret,buf);
  }
  return ret;
}
                
int NetAIOPuts(NetAIO *aio,int samples,int *buf) {
  if (aio->InitStatus < 0) return;
  PacketPushCmd(aio->q,NetAIO_Puts,aio,NetAIOClass);
  PacketPush32(aio->q,buffer);
  PacketPush32(aio->q,samples);
  // bytes per sample
}
                
int NetAIOReadys(NetAIO *aio,int samples,int *buf) {
}
              


// Author: Michael Schmidt (michael@embeddedARM.com)
// Copyright (c) 2011, Technologic Systems, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
