#include "NetCANctl.h"
#include "Packet.h"
#include "Array.h"

void *NetCANctlInit(NetCANctl *can,int socket) {
  if (can->InitStatus > 0) return can;

  can->Init = (void *)NetCANctlInit;
  can->Fini = (void *)NetCANctlFini;
  can->Rx = (void *)NetCANctlRx;
  can->Tx = (void *)NetCANctlTx;
  can->BaudSet = (void *)NetCANctlBaudSet;
  can->BaudGet = (void *)NetCANctlBaudGet;
  can->Abort = (void *)NetCANctlAbort;
  can->RxMulti = (void *)NetCANctlRxMulti;
  can->socket = socket;
  can->InitStatus = can->socket >= 0 ? 1 : -1;
  return can;
}

void NetCANctlFini(NetCANctl *can){
  if (can->InitStatus > 0) {
    close(can->socket);
    can->InitStatus = 0;
  }
}

int NetCANctlRx(NetCANctl *can,CANMessage *msg){
  int ret;
  if (can->InitStatus < 0) return -1;
  ret = PacketRecv(can->socket,msg,sizeof(CANMessage));
  return (ret == sizeof(CANMessage)) ? CANSuccess : -7; 
}

int NetCANctlTx(NetCANctl *can,unsigned flags,unsigned id,const char* data) {
  CANMessage msg;
  int ret;
  if (can->InitStatus < 0) return -1;
  msg.flags = flags;
  msg.id = id;
  msg.t_sec = msg.t_usec = 0;
  msg.length = ArrayLength(data);
  memcpy(msg.data,data,msg.length);
  return PacketSend0(can->socket,&msg,sizeof(CANMessage));
}

unsigned NetCANctlBaudSet(NetCANctl *can,unsigned opt_baud) {
  CANMessage msg;
  if (can->InitStatus < 0) return;
  msg.flags = FLAG_CONTROL;
  msg.id = 0;
  msg.length = 1;
  (((unsigned *)msg.data)[0]) = opt_baud;
  PacketSend0(can->socket,&msg,sizeof(CANMessage));
  //while (NetCANctlRx(can,&msg) > 0);
  //re-connect.  wait, how?
}

unsigned NetCANctlBaudGet(NetCANctl *can) {
  if (can->InitStatus < 0) return -1;
  return 1; // unknown
}

void NetCANctlAbort(NetCANctl *me) {
}

int NetCANctlRxMulti(NetCANctl *me,CANMessage* msg,int min) {
}

// Author: Michael Schmidt (michael@embeddedARM.com)
// Copyright (c) 2012, Technologic Systems, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
