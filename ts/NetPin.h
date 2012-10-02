#ifndef __NetPin_H
#define __NetPin_H
#include "Net.h"
#include "Pin.h"

typedef struct NetPin NetPin;

struct NetPin {
  PinAPI;
  int InitStatus;
  int inst;
  int socket;
  int mode;
  Packet *q;
  int *cmds;
};

void *NetPinInit(NetPin *,int socket,int inst,int mode,Packet *q,int *cmds);
void NetPinFini(NetPin *);
int NetPinLock(NetPin *pin,int command,unsigned num,void *ob);
PinMode NetPinModeGet(NetPin *,int pin);
int NetPinModeSet(NetPin *,int pin,PinMode mode);

#endif
// Author: Michael Schmidt (michael@embeddedARM.com)
// Copyright (c) 2011, Technologic Systems, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
