#ifndef ts4200DIO_c
#define ts4200DIO_c
#include "ts4200DIO.h"
#include "MMapBus.h"
#include "DIORaw.h"
#include "types.h"
#include "peekpoke.h"
#include "cpp.h"

/*
Atmel Bus 4,6,8,0
 */
volatile 
unsigned *atmel4_30,*atmel4_34,*atmel4_10,*atmel4_14,*atmel4_18,*atmel4_3C;
volatile 
unsigned *atmel6_30,*atmel6_34,*atmel6_10,*atmel6_14,*atmel6_18,*atmel6_3C;
volatile 
unsigned *atmel8_30,*atmel8_34,*atmel8_10,*atmel8_14,*atmel8_18,*atmel8_3C;
volatile
unsigned short *ts42_2,*ts42_4,*ts42_6,*ts42_8,*ts42_12,*ts42_14,*ts42_16;
int dir[128];

#define Reg(name,size) ((volatile TEMPLATE(uint,size) *)(name))[0]
#define RegBitGet(name,size,bit) (1&(((volatile TEMPLATE(uint,size) *)(name))[0])>>bit)
#define RegBitSet(name,size,bit) ((volatile TEMPLATE(uint,size) *)(name))[0] |= (1<<bit)
#define RegBitClr(name,size,bit) ((volatile TEMPLATE(uint,size) *)(name))[0] &= ~(1<<bit)
#define RegBitAssign(name,size,bit,val) if (val) RegBitSet(name,size,bit); else RegBitClr(name,size,bit);

void *ts4200DIOInit(ts4200DIO *dio,...) {
  if (dio->InitStatus > 0) return dio;
  int i;

  volatile char *ptr0 = MemMap(0x30000000,1);
  volatile char *ptr4 = MemMap(0xFFFFF400,1);
  volatile char *ptr6 = MemMap(0xFFFFF600,1);
  volatile char *ptr8 = MemMap(0xFFFFF800,1);

  dio->Init = (void *)ts4200DIOInit;
  dio->Fini = (void *)ts4200DIOFini;
  dio->Lock = (void *)ts4200DIOLock;
  dio->Unlock = (void *)ts4200DIOUnlock;
  dio->Preempt = (void *)ts4200DIOPreempt;
  dio->Refresh = (void *)ts4200DIORefresh;
  dio->Commit = (void *)ts4200DIOCommit;
  dio->Set = (void *)ts4200DIOSet;
  dio->Get = (void *)ts4200DIOGet;
  dio->SetAsync = (void *)ts4200DIOSetAsync;
  dio->GetAsync = (void *)ts4200DIOGetAsync;
  dio->Wait = (void *)ts4200DIOWait;
  dio->Count = (void *)ts4200DIOCount;
  dio->Capabilities = (void *)ts4200DIOCapabilities;
  dio->GetMulti = (void *)ts4200DIOGetMulti;

  atmel4_30 = (volatile unsigned *) (ptr4 + 0x30);
  atmel4_34 = (volatile unsigned *) (ptr4 + 0x34);
  atmel4_10 = (volatile unsigned *) (ptr4 + 0x10);
  atmel4_14 = (volatile unsigned *) (ptr4 + 0x14);
  atmel4_18 = (volatile unsigned *) (ptr4 + 0x18);
  atmel4_3C = (volatile unsigned *) (ptr4 + 0x3C);

  atmel6_30 = (volatile unsigned *) (ptr6 + 0x30);
  atmel6_34 = (volatile unsigned *) (ptr6 + 0x34);
  atmel6_10 = (volatile unsigned *) (ptr6 + 0x10);
  atmel6_14 = (volatile unsigned *) (ptr6 + 0x14);
  atmel6_18 = (volatile unsigned *) (ptr6 + 0x18);
  atmel6_3C = (volatile unsigned *) (ptr6 + 0x3C);

  atmel8_30 = (volatile unsigned *) (ptr8 + 0x30);
  atmel8_34 = (volatile unsigned *) (ptr8 + 0x34);
  atmel8_10 = (volatile unsigned *) (ptr8 + 0x10);
  atmel8_14 = (volatile unsigned *) (ptr8 + 0x14);
  atmel8_18 = (volatile unsigned *) (ptr8 + 0x18);
  atmel8_3C = (volatile unsigned *) (ptr8 + 0x3C);

  ts42_2 = (volatile unsigned short *) (ptr0 + 2);
  ts42_4 = (volatile unsigned short *) (ptr0 + 4);
  ts42_6 = (volatile unsigned short *) (ptr0 + 6);
  ts42_8 = (volatile unsigned short *) (ptr0 + 8);
  ts42_12 = (volatile unsigned short *) (ptr0 + 12);
  ts42_14 = (volatile unsigned short *) (ptr0 + 14);
  ts42_16 = (volatile unsigned short *) (ptr0 + 16);

  for (i=0;i<32;i++) dir[i] = RegBitGet(atmel4_18,32,i);
  for (i=0;i<32;i++) dir[i+32] = RegBitGet(atmel4_18,32,i-32);
  for (i=0;i<32;i++) dir[i+64] = RegBitGet(atmel4_18,32,i-64);
  for (i=0;i<16;i++) dir[i+96] = RegBitGet(ts42_4,16,i);
  for (;i<32;i++) dir[i+96] = RegBitGet(ts42_12,16,i-16);

  dio->InitStatus = 1;
  return dio;
}

void ts4200DIOSetAsync(ts4200DIO* ob,int Num,DIOState State) {
  if (Num >= 0 && Num <= 31) {
    if (State < 0) {
      if (dir[Num] != 1) {
	dir[Num] = 1;
	
	((volatile unsigned *)atmel4_14)[0] = 1<< Num;
      }
    } else {
      // Set data first to avoid glitch if current state doesn't match new state
      ((volatile unsigned *)((State==HIGH)?atmel4_30:atmel4_34))[0] = 1<< Num;
      if (dir[Num] != 0) {
	dir[Num] = 0;
	((volatile unsigned *)atmel4_10)[0] = 1<< Num;
      }
    }
  } else if (Num >= 32 && Num <= 63) {
    if (State < 0) {
      if (dir[Num] != 1) {
	dir[Num] = 1;
	((volatile unsigned *)atmel6_14)[0] = 1<< Num;
      }
    } else {
      // Set data first to avoid glitch if current state doesn't match new state
      ((volatile unsigned *)((State==HIGH)?atmel6_30:atmel6_34))[0] = 1<< (Num-32);
      if (dir[Num] != 0) {
	dir[Num] = 0;
	((volatile unsigned *)atmel6_10)[0] = 1<< Num;
      }
    }
  } else if (Num >= 64 && Num <= 95) {
    if (State < 0) {
      if (dir[Num] != 1) {
	dir[Num] = 1;
	((volatile unsigned *)atmel8_14)[0] = 1<< Num;
      }
    } else {
      // Set data first to avoid glitch if current state doesn't match new state
      ((volatile unsigned *)((State==HIGH)?atmel8_30:atmel8_34))[0] = 1<< (Num-64);
      if (dir[Num] != 0) {
	dir[Num] = 0;
	((volatile unsigned *)atmel8_10)[0] = 1<< Num;
      }
    }
  } else if (Num >= 96 && Num <= 96+16) {
    if (State < 0) {
      if (dir[Num] != 1) {
	dir[Num] = 1;
	RegBitAssign(ts42_4,16,Num-96,State);
      }
    } else {
      // Set data first to avoid glitch if current state doesn't match new state
      ((volatile unsigned *)((State==HIGH)?atmel8_30:atmel8_34))[0] = 1<< (Num-64);
      if (dir[Num] != 0) {
	dir[Num] = 0;
	((volatile unsigned *)atmel8_10)[0] = 1<< Num;
      }
    }

  } else if (Num > 96+16 && Num < 128) {
  } else if (Num == 128) {
  } else if (Num == 129) {
  }
}

DIOState ts4200DIOGetAsync(ts4200DIO* ob,int Num) {
  if (Num >= 0 && Num <= 31) {
    return (dir[Num] ? INPUT_LOW : 0) +
      (1 & (((volatile unsigned *)(atmel4_3C))[0] >> Num));
  } else if (Num >= 32 && Num <= 63) {
    return (dir[Num] ? INPUT_LOW : 0) +
      (1 & (((volatile unsigned *)(atmel6_3C))[0] >> (Num-32)));
  } else if (Num >= 64 && Num <= 95) {
    return (dir[Num] ? INPUT_LOW : 0) +
      (1 & (((volatile unsigned *)(atmel8_3C))[0] >> (Num-64)));
  }
  return INPUT;
}

void ts4200DIOFini(ts4200DIO *dio) {
}

int ts4200DIOLock(ts4200DIO* ob,unsigned num,int flags) {
  return 1;
}

int ts4200DIOUnlock(ts4200DIO* ob,unsigned num,int flags) {
  return 1;
}

int ts4200DIOPreempt(ts4200DIO* ob) {
  return 1;
}

void ts4200DIORefresh(ts4200DIO* ob) {
}

void ts4200DIOCommit(ts4200DIO* ob,int ForceAll) {
}

void ts4200DIOSet(ts4200DIO* ob,int Num,DIOState State) {
}

DIOState ts4200DIOGet(ts4200DIO* ob,int Num) {
}

void ts4200DIOWait(ts4200DIO* ob,int *match,int min,int max,const int *nh,const int *nl) {
}

unsigned ts4200DIOCount(ts4200DIO* ob) {
}

DIOCaps ts4200DIOCapabilities(ts4200DIO* ob,unsigned num) {
}

int ts4200DIOGetMulti(ts4200DIO* ob,char *state,int offset) {
}


#endif
