#ifndef __MarvellPXA166TWI_H
#define __MarvellPXA166TWI_H
#include "TWI.h"
#include "Bus.h"
#include "Lock.h"

typedef struct MarvellPXA166TWI MarvellPXA166TWI;
struct MarvellPXA166TWI {
  TWI;
  Bus *bus;
  int LockNum;
};

void *MarvellPXA166TWIInit(MarvellPXA166TWI *,void *bus);
void MarvellPXA166TWIFini(MarvellPXA166TWI *);
int MarvellPXA166TWILock(MarvellPXA166TWI *,int command,unsigned num);
int MarvellPXA166TWIWrite(MarvellPXA166TWI *,int devadr,int adrslen,int adrs,
			  const char* bytes);
int MarvellPXA166TWIRead(MarvellPXA166TWI *,int devadr,int adrslen,int adrs,
			 char* bytes);

#endif
// Author: Michael Schmidt (michael@embeddedARM.com)
// Copyright (c) 2011, Technologic Systems, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
