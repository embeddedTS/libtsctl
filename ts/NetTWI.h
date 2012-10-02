#ifndef __NetTWI_H
#define __NetTWI_H
#include "Net.h"
#include "TWI.h"
typedef struct NetTWI NetTWI;

struct NetTWI {
  TWIAPI;
  int InitStatus;
  int inst;
  int socket;
  int mode;
  Packet *q;
  int *cmds;
};

void *NetTWIInit(NetTWI *,int socket,int inst,int mode,Packet *q,int *cmds);
void NetTWIFini(NetTWI *);
int NetTWILock(NetTWI *,int,unsigned,void *);
int NetTWIWrite(NetTWI *,int devadr,int adrslen,int adrs,int len,char *bytes);
int NetTWIRead(NetTWI *,int devadr,int adrslen,int adrs,int len,char *bytes);

#endif
// Author: Michael Schmidt (michael@embeddedARM.com)
// Copyright (c) 2011, Technologic Systems, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
