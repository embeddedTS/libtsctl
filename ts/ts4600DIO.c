#ifndef ts4600DIO_c
#define ts4600DIO_c
#include <sched.h>
#include "DIO.h"
#include "ts4600DIO.h"
#include "FPGA.h"
#include "Array.h"
#include "Lock.h"
#include "arch.h"

void *ts4600DIOInit(ts4600DIO *dio,void *bus1) {
  Bus *bus = bus1;
  int err;

  if (dio->InitStatus > 0) return dio;

  dio->Init = (void *)ts4600DIOInit;
  dio->Fini = (void *)ts4600DIOFini;
  dio->Lock = (void *)ts4600DIOLock;
  dio->Unlock = (void *)ts4600DIOUnlock;
  dio->Preempt = (void *)ts4600DIOPreempt;
  dio->Refresh = (void *)ts4600DIORefresh;
  dio->Commit = (void *)ts4600DIOCommit;
  dio->Set = (void *)ts4600DIOSet;
  dio->Get = (void *)ts4600DIOGet;
  dio->SetAsync = (void *)ts4600DIOSetAsync;
  dio->GetAsync = (void *)ts4600DIOGetAsync;
  dio->Wait = (void *)ts4600DIOWait;
  dio->Count = (void *)ts4600DIOCount;
  dio->Capabilities = (void *)ts4600DIOCapabilities;
  dio->GetMulti = (void *)ts4600DIOGetMulti;

  dio->bus = bus;
  dio->NumLocks = 72;
  //if ((err=FPGAReloadRegister(&dio->gotHUP,7)) < 0) {
  //dio->Fini(dio);
  //dio->InitStatus = err;
  //return dio;
  //}
  dio->InitStatus = 1;
  return dio;
}

void ts4600DIOFini(ts4600DIO *dio) {
  //if (dio->InitStatus > 0) {
  //FPGAReloadUnregister(&dio->gotHUP);
  //}
  if (dio->InitStatus > 0) dio->InitStatus = 0;
}

void ts4600DIORefresh(ts4600DIO *dio) {
  dio->bus->Lock(dio->bus,0,0);
  //if (dio->gotHUP) {
  //    dio->bus->Commit(dio->bus,1);
  //    dio->gotHUP = 0;
  //}
  dio->bus->Refresh(dio->bus);
  dio->bus->Unlock(dio->bus,0,0);
}

void ts4600DIOCommit(ts4600DIO *dio,int forceall) {
  //if (dio->gotHUP) {
  //    forceall = 1;
  //    dio->gotHUP = 0;
  //  }
  dio->bus->Lock(dio->bus,0,0);
  dio->bus->Commit(dio->bus,forceall);
  dio->bus->Unlock(dio->bus,0,0);
}

static inline void _DIOSet(ts4600DIO *dio,int Num,DIOState State) {
  if (Num == 70) { // red
    if (State < 0) return;
    dio->bus->BitAssign16(dio->bus,2,14,State == HIGH);
    return;
  }
  if (Num == 71) { // green
    if (State < 0) return;
    dio->bus->BitAssign16(dio->bus,2,15,State == HIGH);
    return;
  }
  if (State < 0) { // INPUT
    dio->bus->Poke16(dio->bus,0x28, Num & ~0x80);
  } else {
    // Set data first to avoid glitch if current state doesn't match new state
    if (State == LOW) {
      dio->bus->Poke16(dio->bus,0x26, Num & ~0x80);
    } else { // State == HIGH
      dio->bus->Poke16(dio->bus,0x26, Num | 0x80);
    }
    dio->bus->Poke16(dio->bus,0x28, Num | 0x80);
  }
}

static inline DIOState _DIOGet(ts4600DIO *dio,int Num) {
  if (Num == 70) return dio->bus->BitGet16(dio->bus,2,14) ? HIGH : LOW;
  if (Num == 71) return dio->bus->BitGet16(dio->bus,2,15) ? HIGH : LOW;
  unsigned short data,dir;
  /* This shift math is a little odd, but it works like so:
   * Reg 0x8 is the start of the GPIO input regs in the syscon
   * Each input reg is 6 bytes away from each other (3 16bit regs)
   * Pin #X divided by 16 will return an int that is how many
   *   input regs the reg needed is away from the first, 0 index
   * Multiply the number of input regs away from 0x8 the needed
   *   reg is by 6 to get the actual reg address
   *
   * For the return, we simply need to return a 1 or 0
   * shift the bits to what pin was requested, & 1
   */
  data = dio->bus->Peek16(dio->bus,0x8+(6*(Num/16)));
  data = ((data >> (Num%16)) & 1);

  dir = dio->bus->Peek16(dio->bus,0xC+(6*(Num/16)));
  dir = ((dir >> (Num%16)) & 1);

  if (dir) {
    return data;
  } else {
    return INPUT_LOW + data;
  }
}

// note: synchronous DIO is not really implemented yet!
void ts4600DIOSet(ts4600DIO *dio,int DIONum,DIOState State) {
  if (DIONum < 0 || DIONum > dio->NumLocks 
      || dio->Caps[DIONum] == DIO_NOT_PRESENT) return;
  dio->bus->Lock(dio->bus,0,0);
  _DIOSet(dio,~DIONum,State);
  dio->bus->Unlock(dio->bus,0,0);
}

DIOState ts4600DIOGet(ts4600DIO *dio,int DIONum) {
  DIOState ret;
  if (DIONum < 0 || DIONum > dio->NumLocks 
      || dio->Caps[DIONum] == DIO_NOT_PRESENT) return INPUT;
  dio->bus->Lock(dio->bus,0,SHARED);
  ret =  _DIOGet(dio,~DIONum);
  dio->bus->Unlock(dio->bus,0,SHARED);
  return ret;
}

void ts4600DIOSetAsync(ts4600DIO *dio,int DIONum,DIOState State) {
  if (DIONum < 0 || DIONum > dio->NumLocks 
      || dio->Caps[DIONum] == DIO_NOT_PRESENT) return;
  dio->bus->Lock(dio->bus,0,0);
  _DIOSet(dio,DIONum,State);
  dio->bus->Unlock(dio->bus,0,0);
}

DIOState ts4600DIOGetAsync(ts4600DIO *dio,int DIONum) {
  DIOState ret;

  //printf("%d:%d:%d\n",DIONum,dio->NumLocks,dio->Caps[DIONum] == DIO_NOT_PRESENT);
  if (DIONum < 0 || DIONum > dio->NumLocks 
      || dio->Caps[DIONum] == DIO_NOT_PRESENT) return INPUT;
  dio->bus->Lock(dio->bus,0,SHARED);
  ret = _DIOGet(dio,DIONum);
  dio->bus->Unlock(dio->bus,0,SHARED);
  return ret;
}

int ts4600DIOLock(ts4600DIO *dio,unsigned num,int flags) {
  return 1;
}
int ts4600DIOUnlock(ts4600DIO *dio,unsigned num,int flags) {
  return 1;
}
int ts4600DIOPreempt(ts4600DIO *dio) {
}

void ts4600DIOWait(ts4600DIO *dio,int* match,int min,int max,
		    const int* h,const int* l) {

}

unsigned ts4600DIOCount(ts4600DIO *dio) {
  return 72;
}

DIOCaps ts4600DIOCapabilities(ts4600DIO *dio,unsigned num) {
  if (num < 0 || num >= dio->NumLocks) return DIO_NOT_PRESENT;
  return dio->Caps[num];
}

int ts4600DIOGetMulti(ts4600DIO *dio,char* bits,int offset) {
  int i,n=ArrayLength(bits)*8,j,byte,tmp,max,q;
  max = dio->Count(dio) - offset;

  if (n == 0) {
    tmp = 0;
    q = (max-offset > 32) ? 0 : 32-(max-offset);
    n = (max-offset > 32) ? 32 : max-offset;
    for (i=offset;i<n;i++) {
      tmp = (tmp << 1) + DIOValue(dio->Get(dio,i));
    }
    return tmp << q;
  }
  dio->Refresh(dio);
  for (i=offset,j=0,byte=0;i<n;i++) {
    bits[byte] = (bits[byte] << 1) + DIOValue(dio->Get(dio,i));
    if (i == max) {
      bits[byte] <<= (7-j);
      break;
    }
    if (++j == 8) {
      j = 0;
      byte++;
    }
  }
  return n;
}

// Author: Michael Schmidt (michael@embeddedTS.com)
// Some portions based on code by Kris Bahnsen (kris@embeddedTS.com)
// Copyright (c) 2012-2022 Technologic Systems, Inc. dba embeddedTS, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
#endif
