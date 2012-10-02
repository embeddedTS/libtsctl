#ifndef __FreescaleIMX51TWI_H
#define __FreescaleIMX51TWI_H
#include "TWI.h"
#include "Bus.h"
#include "Lock.h"

typedef struct FreescaleIMX51TWI FreescaleIMX51TWI;
struct FreescaleIMX51TWI {
  TWI;
  Bus *bus;
  int LockNum;
};

void *FreescaleIMX51TWIInit(FreescaleIMX51TWI *,void *bus);
void FreescaleIMX51TWIFini(FreescaleIMX51TWI *);
int FreescaleIMX51TWILock(FreescaleIMX51TWI *,int command,unsigned num);
int FreescaleIMX51TWIWrite(FreescaleIMX51TWI *,int devadr,int adrslen,int adrs,int len,char *bytes);
int FreescaleIMX51TWIRead(FreescaleIMX51TWI *,int devadr,int adrslen,int adrs,int len,char *bytes);

#endif
// Author: Michael Schmidt (michael@embeddedARM.com)
// Copyright (c) 2011, Technologic Systems, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
