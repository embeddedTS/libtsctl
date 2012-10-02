#ifndef __NetDIORaw_H
#define __NetDIORaw_H
#include "Net.h"
#include "DIORaw.h"
typedef struct NetDIORaw NetDIORaw;

struct NetDIORaw {
  DIORaw;
  int inst;
  int socket;
  int mode;
  Packet *q;
  int *cmds;
};

void *NetDIORawInit(NetDIORaw *,int socket,int inst,int mode,Packet *q,int *cmds);
void NetDIORawFini(NetDIORaw *);
void NetDIORawDirSet(NetDIORaw *,int num,int asOutput);
void NetDIORawDataSet(NetDIORaw *,int num,int asHigh);
int NetDIORawDirGet(NetDIORaw *,int num);
int NetDIORawDataGet(NetDIORaw *,int num);
int NetDIORawLock(NetDIORaw *dio,int command,unsigned num);
unsigned NetDIORawCount(NetDIORaw *);

#endif
// Author: Michael Schmidt (michael@embeddedARM.com)
// Copyright (c) 2011, Technologic Systems, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
