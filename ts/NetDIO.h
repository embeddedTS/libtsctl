#ifndef __NetDIO_H
#define __NetDIO_H
#include "Net.h"
#include "DIO.h"
typedef struct NetDIO NetDIO;

struct NetDIO {
  DIOAPI;
  int InitStatus;
  int inst;
  int socket;
  int mode;
  Packet *q;
  int *cmds;
};

void *NetDIOInit(NetDIO *,int socket,int inst,int mode,Packet *q,int *cmds);
void NetDIOFini(NetDIO *);
int NetDIOLock(NetDIO *,int,unsigned);
void NetDIORefresh(NetDIO *);
void NetDIOCommit(NetDIO *,int forceall);
void NetDIOSet(NetDIO *,int DIONum,DIOState State);
DIOState NetDIOGet(NetDIO *,int DIONum);
void NetDIOSetAsync(NetDIO *,int DIONum,DIOState State);
DIOState NetDIOGetAsync(NetDIO *,int DIONum);
int NetDIOWait(NetDIO *,int *match,int min,int max,int nh,int *h,int nl,int *l);
unsigned NetDIOCount(NetDIO *);
DIOCaps NetDIOCapabilities(NetDIO *,unsigned num);

#endif
// Author: Michael Schmidt (michael@embeddedARM.com)
// Copyright (c) 2011, Technologic Systems, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
