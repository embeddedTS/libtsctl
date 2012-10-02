#include "NetCAN.h"

static CANAPI NetCANAPI = {
  .Init = (void *)NetCANInit,
  .Fini = (void *)NetCANFini,
  .Rx = (void *)NetCANRx,
  .Tx = (void *)NetCANTx,
  .BaudSet = (void *)NetCANBaudSet,
  .BaudGet = (void *)NetCANBaudGet
};

void *NetCANInit(NetCAN *can,int socket,int inst,int mode,Packet *q,int *cmds){
  if (can->InitStatus > 0) return can;
  can->API = &NetCANAPI;

  can->inst = inst;
  can->socket = socket;
  can->InitStatus = can->socket >= 0 ? 1 : -1;
  can->mode = mode;
  can->q = q;
  can->cmds = cmds;
  return can;
}

void NetCANFini(NetCAN *can){
  if (can->InitStatus > 0) {
    close(can->socket);
    can->InitStatus = 0;
  }
}

int NetCANRx(NetCAN *can,CANMessage *msg){
  int ret;
  if (can->InitStatus < 0) return;
  PacketPushCmd(can->q,NetCAN_Rx,can,NetCANClass);
  ret = DoCmd(can->q,can,1);
  if (ret > 0) {
    PacketPullBytes(can->socket,sizeof(CANMessage),(char *)msg);
  }
  return ret;
}

int NetCANTx(NetCAN *can,CANMessage *msg){
  int ret;
  if (can->InitStatus < 0) return;
  PacketPushCmd(can->q,NetCAN_Tx,can,NetCANClass);
  PacketPushBytes(can->q,sizeof(CANMessage),(char *)msg);
  return DoCmd(can->q,can,1);
}

unsigned NetCANBaudSet(NetCAN *can,unsigned opt_baud) {
  if (can->InitStatus < 0) return;
  PacketPushCmd(can->q,NetCAN_BaudSet,can,NetCANClass);
  PacketPush32(can->q,opt_baud);
  return DoCmd(can->q,can,1);
}

unsigned NetCANBaudGet(NetCAN *can) {
  if (can->InitStatus < 0) return;
  PacketPushCmd(can->q,NetCAN_BaudGet,can,NetCANClass);
  return DoCmd(can->q,can,1);
}

/* Tests:
# Tx
tsctl CAN m4500x8200:0 Tx "0x1234 1:2:1:3"
# Rx
tsctl CAN m4500x9490:0 Rx
# BaudSet
tsctl CAN m4500x8200:0 BaudSet 100000
# BaudGet
tsctl CAN m4500x8200:0 BaudGet
*/
// Author: Michael Schmidt (michael@embeddedARM.com)
// Copyright (c) 2011, Technologic Systems, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
