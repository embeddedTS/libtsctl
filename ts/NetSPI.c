#include "NetSPI.h"

static SPIAPI NetSPIAPI =  {
  .Init = (void *)NetSPIInit,
  .Fini = (void *)NetSPIFini,
  .Lock = (void *)NetSPILock,
  .Write = (void *)NetSPIWrite,
  .Read = (void *)NetSPIRead,
  .ReadWrite = (void *)NetSPIReadWrite,
  .ClockSet = (void *)NetSPIClockSet,
  .EdgeSet = (void *)NetSPIEdgeSet
};

void *NetSPIInit(NetSPI *spi,int socket,int inst,int mode,Packet *q,int *cmds){
  if (spi->InitStatus > 0) return spi;
  spi->API = &NetSPIAPI;

  spi->inst = inst;
  spi->socket = socket;
  spi->InitStatus = spi->socket >= 0 ? 1 : -1;
  spi->mode = mode;
  spi->q = q;
  spi->cmds = cmds;
  return spi;
}

void NetSPIFini(NetSPI *spi){
  if (spi->InitStatus > 0) spi->InitStatus = 0;
}

int NetSPILock(NetSPI *spi,int command,unsigned num){
  if (spi->InitStatus < 0) return -999;
  PacketPushCmd(spi->q,NetSPI_Lock,spi,NetSPIClass);
  PacketPush32(spi->q,command);
  PacketPush32(spi->q,num);
  return DoCmd(spi->q,spi,1);
}


int NetSPIWrite(NetSPI *spi,int adrs,unsigned char *buf,int len) {
  if (spi->InitStatus < 0) return -99;
  if (len > 500) return -5;
  PacketPushCmd(spi->q,NetSPI_Write,spi,NetSPIClass);
  PacketPush32(spi->q,adrs);
  PacketPush32(spi->q,len);
  PacketPushBytes(spi->q,len,buf);
  return DoCmd(spi->q,spi,1);
}

int NetSPIRead(NetSPI *spi,int adrs,unsigned char *buf,int len) {
  int ret;
  if (spi->InitStatus < 0) return -99;
  if (len > 500) return -5;
  PacketPushCmd(spi->q,NetSPI_Read,spi,NetSPIClass);
  PacketPush32(spi->q,adrs);
  PacketPush32(spi->q,len);
  ret = DoCmd(spi->q,spi,1);
  if (ret > 0) {
    PacketPullBytes(spi->socket,len,buf);
  }
  return ret;
}

int NetSPIReadWrite(NetSPI *spi,int adrs,unsigned char *wbuf,unsigned char *rbuf, int len) {
  int ret;
  if (spi->InitStatus < 0) return -99;
  if (len > 500) return -5;
  PacketPushCmd(spi->q,NetSPI_ReadWrite,spi,NetSPIClass);
  PacketPush32(spi->q,adrs);
  PacketPush32(spi->q,len);
  PacketPushBytes(spi->q,len,wbuf);
  ret = DoCmd(spi->q,spi,1);
  if (ret > 0) {
    PacketPullBytes(spi->socket,len,rbuf);
  }
  return ret;
}

int NetSPIClockSet(NetSPI *spi,unsigned hz) {
  if (spi->InitStatus < 0) return -99;
  PacketPushCmd(spi->q,NetSPI_ClockSet,spi,NetSPIClass);
  PacketPush32(spi->q,hz);
  return DoCmd(spi->q,spi,1);
}

int NetSPIEdgeSet(NetSPI *spi,int posedge) {
  if (spi->InitStatus < 0) return -99;
  PacketPushCmd(spi->q,NetSPI_EdgeSet,spi,NetSPIClass);
  PacketPush32(spi->q,posedge);
  return DoCmd(spi->q,spi,1);
}

// Author: Michael Schmidt (michael@embeddedARM.com)
// Copyright (c) 2011, Technologic Systems, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
