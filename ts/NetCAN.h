#ifndef __NetCAN_H
#define __NetCAN_H
#include "Net.h"
#include "CAN.h"
typedef struct NetCAN NetCAN;

struct NetCAN {
  CANAPI;
  int InitStatus;
  int inst;
  int socket;
  int mode;
  Packet *q;
  int *cmds;
};

void *NetCANInit(NetCAN *,int socket,int inst,int mode,Packet *q,int *cmds);
void NetCANFini(NetCAN *);
int NetCANRx(NetCAN *,CANMessage *);
int NetCANTx(NetCAN *,CANMessage *);
unsigned NetCANBaudSet(NetCAN *,unsigned opt_baud);
unsigned NetCANBaudGet(NetCAN *);

#endif
// Author: Michael Schmidt (michael@embeddedARM.com)
// Copyright (c) 2011, Technologic Systems, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
