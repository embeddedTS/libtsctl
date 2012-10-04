#ifndef LinuxTWI_c
#define LinuxTWI_c
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "LinuxTWI.h"
#include "TSLock.h"
#include "Array.h"

void *LinuxTWIInit(LinuxTWI *twi,char *devfile) {
  if (twi->InitStatus > 0) return twi;

  twi->Init = (void *)LinuxTWIInit;
  twi->Fini = (void *)LinuxTWIFini;
  twi->Lock = (void *)LinuxTWILock;
  twi->Unlock = (void *)LinuxTWIUnlock;
  twi->Preempt = (void *)LinuxTWIPreempt;
  twi->Write = (void *)LinuxTWIWrite;
  twi->Read = (void *)LinuxTWIRead;

  twi->devfile = devfile;
  twi->InitStatus = 1;
  return twi;
}

void LinuxTWIFini(LinuxTWI *twi){
  twi->bus->Fini(twi->bus);
  if (twi->f) {
    close(twi->f);
    twi->f = 0;
  }
  if (twi->InitStatus > 0) twi->InitStatus = 0;
}

int LinuxTWIWrite(LinuxTWI *twi,int devadrs,int adrslen,int adrs,const char* bytes){
  int len = ArrayLength(bytes);
  ioctl(twi->f,0x0703,devadrs);
  write(twi->f,&adrs,adrslen); // assumes little-endian "adrs"
  write(twi->f,bytes,len);
  return 1;
}

int LinuxTWIRead(LinuxTWI *twi,int devadrs,int adrslen,int adrs,char* bytes){
  int len = ArrayLength(bytes);
  ioctl(twi->f,0x0703,devadrs);
  write(twi->f,&adrs,adrslen); // assumes little-endian "adrs"
  read(twi->f,bytes,len);
  return 1;
}

int LinuxTWILock(LinuxTWI *twi,unsigned num,int flags) {
  int ret,mode;

  if (flags & SHARED) return -11;
  mode = (flags & NONBLOCKING) ? 
    LOCK_TRY :
    (flags & NOUNLOCK) ? LOCK_FOD : LOCK_SOD;
  if ((ret=ThreadMutexLock(twi->LockNum,mode)) < 0) return ret;

  if (!twi->f) {
    twi->f = open(twi->devfile,O_RDWR);
  }
  return 1;
}

int LinuxTWIUnlock(LinuxTWI *twi,unsigned num,int flags) {
  close(twi->f);
  twi->f = 0;
  return ThreadMutexUnlock(twi->LockNum);
}

int LinuxTWIPreempt(LinuxTWI *twi) {
  LinuxTWILock(twi,twi->LockNum,0);
  sched_yield();
  return LinuxTWILock(twi,twi->LockNum,0);
}

// Author: Michael Schmidt (michael@embeddedARM.com)
// Copyright (c) 2012, Technologic Systems, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
#endif
