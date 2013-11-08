#include <assert.h>
#include <errno.h>
#include <fcntl.h>
#include <linux/futex.h>
#include <sched.h>
#include <signal.h>
#include <sys/mman.h>
#include <sys/time.h>
#include <sys/sem.h>
#include <stdio.h>
#include <stdlib.h>                                                                   
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/syscall.h>
#include <unistd.h>
#include <semaphore.h>

#include "peekpoke.h"
#include "Bit.h"
#include "FPGA.h"
#include "NBus.h"
#include "Array.h"

static void NBusLockCallback(NBus *obj,unsigned num);

#define LOCK_TYPE_EXCLUSIVE
#define LOCK_CLASS NBus
#define LOCK_CALLBACK NBusLockCallback
#include "TSLock.h"

static void reservemem(void);
static void NBusReInit(NBus *bus);

void *NBusInit(NBus *bus) {
  int ret;

  if (bus->InitStatus > 0) return bus;
  bus->LockBase = 0;

  bus->mxsgpioregs = MemMap(0x80018000,1);
  //bus->mxsclkregs = MemMap(,1);

  bus->Init = (void *)NBusInit;
  bus->Fini = (void *)NBusFini;
  bus->Lock = (void *)NBusLock;
  bus->Unlock = (void *)NBusUnlock;
  bus->Preempt = (void *)NBusPreempt;
  bus->Peek8 = (void *)NBusPeek8;
  bus->Poke8 = (void *)NBusPoke8;
  bus->Peek16 = (void *)NBusPeek16;
  bus->Poke16 = (void *)NBusPoke16;
  bus->Peek32 = (void *)NBusPeek32;
  bus->Poke32 = (void *)NBusPoke32;
  bus->BitGet8 = (void *)NBusBitGet8;
  bus->BitAssign8 = (void *)NBusBitAssign8;
  bus->BitSet8 = (void *)NBusBitSet8;
  bus->BitClear8 = (void *)NBusBitClear8;
  bus->BitGet16 = (void *)NBusBitGet16;
  bus->BitAssign16 = (void *)NBusBitAssign16;
  bus->BitSet16 = (void *)NBusBitSet16;
  bus->BitClear16 = (void *)NBusBitClear16;
  bus->BitGet32 = (void *)NBusBitGet32;
  bus->BitAssign32 = (void *)NBusBitAssign32;
  bus->BitSet32 = (void *)NBusBitSet32;
  bus->BitClear32 = (void *)NBusBitClear32;
  bus->PeekStream = (void *)NBusPeekStream;
  bus->PokeStream = (void *)NBusPokeStream;
  bus->Refresh = (void *)NBusRefresh;
  bus->Commit = (void *)NBusCommit;
  bus->BitToggle8 = (void *)NBusBitToggle8;
  bus->BitToggle16 = (void *)NBusBitToggle16;
  bus->BitToggle32 = (void *)NBusBitToggle32;
  bus->Assign8X = (void *)NBusAssign8X;
  bus->Assign16X = (void *)NBusAssign16X;
  bus->Assign32X = (void *)NBusAssign32X;
  bus->BitsGet8 = (void *)NBusBitsGet8;
  bus->BitsGet16 = (void *)NBusBitsGet16;
  bus->BitsGet32 = (void *)NBusBitsGet32;

  //  if ((ret=FPGAReloadRegister(&bus->gotHUP,8)) < 0) {
  //    bus->Fini(bus);
  //    bus->InitStatus =ret;
  //    return bus;
  //  }

  NBusLock(bus,0,0);
  //NBusReInit(bus);
  bus->mxsgpioregs[0x100/4] = 0xffffffff; //Set pinmux to GPIO
  bus->mxsgpioregs[0x110/4] = 0xffffffff; //Set pinmux to GPIO
  bus->mxsgpioregs[0x700/4] = 0xffffffff; //Set all to logic high
  bus->mxsgpioregs[0xb00/4] = 0xffdfffff; //Set all to output
  NBusUnlock(bus,0,0);


  bus->InitStatus = 1;
  return bus;
}

void NBusFini(NBus *obj) {
  if (obj->InitStatus > 0) {
    //FPGAReloadUnregister(&obj->gotHUP);
  }
  MemUnmap(obj->mxsgpioregs);
  if (obj->InitStatus > 0) obj->InitStatus = 0;
}


static void NBusLockCallback(NBus *obj,unsigned num) {
  //if (obj->gotHUP) {
  //  NBusReInit(obj);
  //  obj->gotHUP = 0;
  //}
}

static void NBusReInit(NBus *obj) {
}

void NBusRefresh(NBus *obj) {
}

void NBusCommit(NBus *obj,int forceall) {
}

static unsigned short _NBusPeek16(NBus *obj,unsigned int adr) {
  int x;
  unsigned short ret;

  obj->mxsgpioregs[0x708/4] = (1 << 16) | (1 << 25) | (1 << 24) | (1 << 27) | (0xff); //Drop CS, wrn, cle, rdn, and clear dat
  obj->mxsgpioregs[0x704/4] = (1 << 26) | adr; //raise ALE and set adr
  obj->mxsgpioregs[0x704/4] = (1 << 25); //raise wrn
  obj->mxsgpioregs[0xb00/4] = 0xffdfff00; //Set all to output, dat to input
  
  do {
    ret = 0;
    for(x = 1; x >= 0; x--) {
      obj->mxsgpioregs[0x708/4] = (1 << 16) | (1 << 25) | (1 << 24) | (1 << 27) | (0xff); //Drop CS, wrn, cle, rdn, and clear dat
      obj->mxsgpioregs[0x704/4] = (1 << 25); //raise wrn
      ret |= ((obj->mxsgpioregs[0x900/4] & 0xff) << (x*8)); //read dat
    }
    obj->mxsgpioregs[0x704/4] = (1 << 16) | (1 << 24) | (1 << 27); //raise CS, rdn, cle
  } while(obj->mxsgpioregs[0x900/4] & (1 << 21)); 
  
  obj->mxsgpioregs[0xb00/4] = 0xffdfffff; //Set all to output
  
  return ret;
}

static void _NBusPoke16(NBus *obj,unsigned int adr, unsigned short dat) {
  int x;

  obj->mxsgpioregs[0x708/4] = (1 << 16) | (1 << 26) | (1 << 25) | (1 << 27) | (0xff); //Drop CS, CLE, wrn, and clear dat
  obj->mxsgpioregs[0x704/4] = ((1 << 26) | adr ); //set adr and ALE
  obj->mxsgpioregs[0x704/4] = (1 << 25); //raise wrn

  for(x = 1; x >= 0; x--) {
    obj->mxsgpioregs[0x708/4] = (1 << 16) | (1 << 26) | (1 << 25) | (1 << 27) | (0xff); //Drop CS, CLE, wrn, and clear dat
    obj->mxsgpioregs[0x704/4] = (unsigned char)(dat >> (x*8)); //set dat
    obj->mxsgpioregs[0x704/4] = (1 << 25); //raise wrn
  }
  obj->mxsgpioregs[0x704/4] = (1 << 16) | (1 << 27); //raise CS, cle
  
  while(obj->mxsgpioregs[0x900/4] & (1 << 21)) {
    obj->mxsgpioregs[0x708/4] = (1 << 16) | (1 << 26) | (1 << 25) | (1 << 27) | (0xff); //Drop CS, CLE, wrn, and clear dat
    obj->mxsgpioregs[0x704/4] = (1 << 16) | (1 << 27); //raise CS, cle
  }
}

static void _NBusPoke8(NBus *obj,unsigned int adr, unsigned char dat) {
  // unsupported?
}

unsigned char _NBusPeek8(NBus* ob,int Address) {
  // unsupported
}

__attribute__((always_inline)) 
static inline unsigned _NBusPeek32(NBus *obj,unsigned int adr) {
  unsigned int ret;
  unsigned short l, h;
  l = _NBusPeek16(obj,adr);
  h = _NBusPeek16(obj,adr + 2);
  ret = (l|(h<<16));
  return ret;
}

__attribute__((always_inline)) 
static inline void _NBusPoke32(NBus *obj,unsigned int adr, unsigned dat) {
  _NBusPoke16(obj,adr, dat & 0xffff);
  _NBusPoke16(obj,adr + 2, dat >> 16);
}

void NBusPeekStream(NBus *obj,int adr,int dir,char* dat) {
  // unsupported
}

void NBusPokeStream(NBus *obj,int adr,int dir,const char* dat) {
  // unsupported
}

DefinitionFunctionsBit(NBus,unsigned char,8)
DefinitionFunctionsBit(NBus,unsigned short,16)
DefinitionFunctionsBit(NBus,unsigned,32)

// Author: Michael Schmidt (michael@embeddedARM.com)
// Some portions based on code by Kris Bahnsen (kris@embeddedARM.com)
// Copyright (c) 2013, Technologic Systems, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
