#ifndef __NetCANctl_H
#define __NetCANctl_H
#include "Net.h"
#include "CAN.h"
typedef struct NetCANctl NetCANctl;

struct NetCANctl {
  CAN;
  int socket;
};

void *NetCANctlInit(NetCANctl *,int socket);
void NetCANctlFini(NetCANctl *);
int NetCANctlRx(NetCANctl *,CANMessage *);
int NetCANctlTx(NetCANctl *can,unsigned flags,unsigned id,const char* data);
unsigned NetCANctlBaudSet(NetCANctl *,unsigned opt_baud);
unsigned NetCANctlBaudGet(NetCANctl *);
void NetCANctlAbort(NetCANctl *me);
int NetCANctlRxMulti(NetCANctl *me,CANMessage*,int min);

#endif
// Author: Michael Schmidt (michael@embeddedARM.com)
// Copyright (c) 2012, Technologic Systems, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
