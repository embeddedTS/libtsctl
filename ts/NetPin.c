#include "NetPin.h"

static PinAPI NetPinAPI = {
  .Init = (void *)NetPinInit,
  .Fini = (void *)NetPinFini,
  .Lock = (void *)NetPinLock,
  .ModeGet = (void *)NetPinModeGet,
  .ModeSet = (void *)NetPinModeSet
};

void *NetPinInit(NetPin *pin,int socket,int inst,int mode,Packet *q,int *cmds){
  if (pin->InitStatus > 0) return pin;
  pin->API = &NetPinAPI;

  pin->inst = inst;
  pin->socket = socket;
  pin->InitStatus = pin->socket >= 0 ? 1 : -1;
  pin->mode = mode;
  pin->q = q;
  pin->cmds = cmds;
  return pin;
}

void NetPinFini(NetPin *pin){
  if (pin->InitStatus > 0) pin->InitStatus = 0;
}

int NetPinLock(NetPin *pin,int command,unsigned num,void *ob) {
  if (pin->InitStatus < 0) return -999;
  PacketPushCmd(pin->q,NetPin_Lock,pin,NetPinClass);
  PacketPush32(pin->q,command);
  PacketPush32(pin->q,num);
  return DoCmd(pin->q,pin,1);
}

PinMode NetPinModeGet(NetPin *pin,int pinnum){
  if (pin->InitStatus < 0) return -1;
  PacketPushCmd(pin->q,NetPin_ModeGet,pin,NetPinClass);
  PacketPush32(pin->q,pinnum);
  return DoCmd(pin->q,pin,1);
}

int NetPinModeSet(NetPin *pin,int pinnum,PinMode mode){
  if (pin->InitStatus < 0) return -1;
  PacketPushCmd(pin->q,NetPin_ModeSet,pin,NetPinClass);
  PacketPush32(pin->q,pinnum);
  PacketPush32(pin->q,mode);
  return DoCmd(pin->q,pin,1);
}

/* Tests:
# ModeGet tested
tsctl Pin m4500x8200:0 ModeGet 13
# ModeSet
tsctl Pin m4500x8200:0 ModeSet 13 DIO
 */
// Author: Michael Schmidt (michael@embeddedARM.com)
// Copyright (c) 2011, Technologic Systems, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
