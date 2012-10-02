#ifndef __LinuxTWI_H
#define __LinuxTWI_H
#include "TWI.h"
#include "Bus.h"

typedef struct LinuxTWI LinuxTWI;
struct LinuxTWI {
  TWI;
  Bus *bus;
  int LockNum;
  char *devfile;
  int f;
};

void *LinuxTWIInit(LinuxTWI *,char *devfile);
void LinuxTWIFini(LinuxTWI *);
int LinuxTWILock(LinuxTWI *twi,unsigned num,int flags);
int LinuxTWIUnlock(LinuxTWI *twi,unsigned num,int flags);
int LinuxTWIPreempt(LinuxTWI *twi);
int LinuxTWIWrite(LinuxTWI *,int devadr,int adrslen,int adrs,const char* bytes);
int LinuxTWIRead(LinuxTWI *,int devadr,int adrslen,int adrs,char* bytes);

#endif
// Author: Michael Schmidt (michael@embeddedARM.com)
// Copyright (c) 2011, Technologic Systems, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
