#include <assert.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sched.h>
#include <stdlib.h>
#include <limits.h>
#include "peekpoke.h"
#include "Bit.h"
#include "FPGA.h"
#include "Cavium2132SBus.h"
#include "Array.h"

static void Cavium2132SBusLockCallback(Cavium2132SBus *obj,unsigned num);

#define LOCK_TYPE_EXCLUSIVE
#define LOCK_CLASS Cavium2132SBus
#define LOCK_CALLBACK Cavium2132SBusLockCallback
#include "TSLock.h"

static void reservemem(void);
static void Cavium2132SBusReInit(Cavium2132SBus *bus);

void *Cavium2132SBusInit(Cavium2132SBus *bus,void *spibus0,void *gpiobus0) {
  int ret;
  Bus *spibus = spibus0;
  Bus *gpiobus = gpiobus0;

  if (bus->InitStatus > 0) return bus;
  bus->LockBase = 0;

  bus->Init = (void *)Cavium2132SBusInit;
  bus->Fini = (void *)Cavium2132SBusFini;
  bus->Lock = (void *)Cavium2132SBusLock;
  bus->Unlock = (void *)Cavium2132SBusUnlock;
  bus->Preempt = (void *)Cavium2132SBusPreempt;
  bus->Peek8 = (void *)Cavium2132SBusPeek8;
  bus->Poke8 = (void *)Cavium2132SBusPoke8;
  bus->Peek16 = (void *)Cavium2132SBusPeek16;
  bus->Poke16 = (void *)Cavium2132SBusPoke16;
  bus->Peek32 = (void *)Cavium2132SBusPeek32;
  bus->Poke32 = (void *)Cavium2132SBusPoke32;
  bus->BitGet8 = (void *)Cavium2132SBusBitGet8;
  bus->BitAssign8 = (void *)Cavium2132SBusBitAssign8;
  bus->BitSet8 = (void *)Cavium2132SBusBitSet8;
  bus->BitClear8 = (void *)Cavium2132SBusBitClear8;
  bus->BitGet16 = (void *)Cavium2132SBusBitGet16;
  bus->BitAssign16 = (void *)Cavium2132SBusBitAssign16;
  bus->BitSet16 = (void *)Cavium2132SBusBitSet16;
  bus->BitClear16 = (void *)Cavium2132SBusBitClear16;
  bus->BitGet32 = (void *)Cavium2132SBusBitGet32;
  bus->BitAssign32 = (void *)Cavium2132SBusBitAssign32;
  bus->BitSet32 = (void *)Cavium2132SBusBitSet32;
  bus->BitClear32 = (void *)Cavium2132SBusBitClear32;
  bus->PeekStream = (void *)Cavium2132SBusPeekStream;
  bus->PokeStream = (void *)Cavium2132SBusPokeStream;
  bus->Refresh = (void *)Cavium2132SBusRefresh;
  bus->Commit = (void *)Cavium2132SBusCommit;
  bus->BitToggle8 = (void *)Cavium2132SBusBitToggle8;
  bus->BitToggle16 = (void *)Cavium2132SBusBitToggle16;
  bus->BitToggle32 = (void *)Cavium2132SBusBitToggle32;
  bus->Assign8X = (void *)Cavium2132SBusAssign8X;
  bus->Assign16X = (void *)Cavium2132SBusAssign16X;
  bus->Assign32X = (void *)Cavium2132SBusAssign32X;
  bus->BitsGet8 = (void *)Cavium2132SBusBitsGet8;
  bus->BitsGet16 = (void *)Cavium2132SBusBitsGet16;
  bus->BitsGet32 = (void *)Cavium2132SBusBitsGet32;

  bus->last_gpio_adr = -1;

  bus->spibus = spibus;
  bus->gpiobus = gpiobus;
  if (bus->spibus->InitStatus < 0
      ||bus->gpiobus->InitStatus < 0) {
    bus->Fini(bus);
    bus->InitStatus = -1;
    return bus;
  }

  if ((ret=FPGAReloadRegister(&bus->gotHUP,8)) < 0) {
    bus->Fini(bus);
    bus->InitStatus =ret;
    return bus;
  }

  reservemem();
  Cavium2132SBusLock(bus,0,0);
  Cavium2132SBusReInit(bus);
  Cavium2132SBusUnlock(bus,0,0);
  bus->InitStatus = 1;
  return bus;
}

void Cavium2132SBusFini(Cavium2132SBus *obj) {
  if (obj->InitStatus > 0) {
    FPGAReloadUnregister(&obj->gotHUP);
  }
  obj->spibus->Fini(obj->spibus);
  obj->gpiobus->Fini(obj->gpiobus);
  if (obj->InitStatus > 0) obj->InitStatus = 0;
}


static void Cavium2132SBusLockCallback(Cavium2132SBus *obj,unsigned num) {
  obj->gpiobus->Poke32(obj->gpiobus,0,(2<<15|1<<17|1<<3));
  if (obj->gotHUP) {
    Cavium2132SBusReInit(obj);
    obj->gotHUP = 0;
  }
  obj->gpiobus->Poke32(obj->gpiobus,0,obj->gpiobus->Peek32(obj->gpiobus,0)
			    & ~(0x3<<15)|(obj->last_gpio_adr<<15));
}

static void Cavium2132SBusReInit(Cavium2132SBus *obj) {
  int i;
  obj->spibus->Poke32(obj->spibus,0x64,0);
  obj->spibus->Poke32(obj->spibus,0x40,0x80000c02);
  obj->spibus->Poke32(obj->spibus,0x60,0);
  obj->spibus->Poke32(obj->spibus,0x6c,0);
  obj->spibus->Poke32(obj->spibus,0x4c,4);
  for (i = 0; i < 8; i++) {
    obj->spibus->Peek32(obj->spibus,0x58);
  }
  obj->last_gpio_adr = 3;
  int tmp = obj->spibus->Peek32(obj->spibus,0);
  obj->spibus->Poke32(obj->spibus,0,tmp & ~(0x3<<15)|(obj->last_gpio_adr<<15));
  obj->spibus->Poke32(obj->spibus,0,(2<<15|1<<17|1<<3));
}

void Cavium2132SBusRefresh(Cavium2132SBus *obj) {
  // Since we still hard-code to bus to access the SPI/GPIO registers,
  // we don't have a real bus we can pass Refresh and Commit to...
}

void Cavium2132SBusCommit(Cavium2132SBus *obj,int forceall) {
}

static unsigned short _Cavium2132SBusPeek16(Cavium2132SBus *obj,unsigned int adr) {
  unsigned short ret;
  unsigned int adr0 = adr;

  /*
    This is an ugly hack!  The assembly code below is hard-coding what it
    expects to be a pointer to the SPI registers.  This means that it will
    break things to try to (e.g.) put a bus logger in between this module
    and the underlying spibus due to this assumption.
   */
  struct HACK { Bus f; volatile unsigned *data; };
  volatile unsigned int *spi = ((struct HACK *)(obj->spibus))->data;

  //fprintf(stderr,"pre:%08X\n",obj->gpiobus->Peek32(obj->gpiobus,0));
  if (obj->last_gpio_adr != adr >> 5) {
    obj->last_gpio_adr = adr >> 5;
    obj->gpiobus->Poke32(obj->gpiobus,0,((adr>>5)<<15|1<<17|1<<3));
    //fprintf(stderr,"pst:%08X\n",obj->gpiobus->Peek32(obj->gpiobus,0));
  }
  adr &= 0x1f;

  asm volatile (
		"mov %0, %1, lsl #18\n"
		"2: str %0, [%2, #0x50]\n"
		"1: ldr r1, [%2, #0x64]\n"
		"cmp r1, #0x0\n"
		"beq 1b\n"
		"ldr %0, [%2, #0x58]\n"
		"ands r1, %0, #0x10000\n"
		"bicne %0, %0, #0xff0000\n"
		"moveq %0, #0x0\n"
		"beq 2b\n" 
		: "+r"(ret) : "r"(adr), "r"(spi) : "r1", "cc"
		);
  return ret;
}

static void _Cavium2132SBusPoke16(Cavium2132SBus *obj,unsigned int adr, unsigned short dat) {
  unsigned int dummy;
  unsigned int d = dat;

  // same ugly hack as above!
  struct HACK { Bus f; volatile unsigned *data; };
  volatile unsigned int *spi = ((struct HACK *)(obj->spibus))->data;

  if (obj->last_gpio_adr != adr >> 5) {
    obj->last_gpio_adr = adr >> 5;
    int tmp = obj->gpiobus->Peek32(obj->gpiobus,0);
    obj->gpiobus->Poke32(obj->gpiobus,0,tmp & ~(0x3<<15)|((adr>>5)<<15));
  }

  adr &= 0x1f;

  asm volatile (
		"mov %0, %1, lsl #18\n"
		"orr %0, %0, #0x800000\n"
		"orr %0, %0, %2, lsl #3\n"
		"3: ldr r1, [%3, #0x64]\n"
		"cmp r1, #0x0\n"
		"bne 3b\n"
		"2: str %0, [%3, #0x50]\n"
		"1: ldr r1, [%3, #0x64]\n"
		"cmp r1, #0x0\n"
		"beq 1b\n"
		"ldr %0, [%3, #0x58]\n"
		"ands r1, %0, #0x1\n"
		"moveq %0, #0x0\n"
		"beq 3b\n"
		: "+r"(dummy) : "r"(adr), "r"(d), "r"(spi) : "r1","cc"
		);
}

static unsigned char _Cavium2132SBusPeek8(Cavium2132SBus *obj,unsigned int adr) {
  unsigned char ret;
  unsigned short x;
  x = _Cavium2132SBusPeek16(obj,adr);
  if (adr & 0x1) ret = x >> 8;
  else ret = x & 0xff;
  return ret;
}

static void _Cavium2132SBusPoke8(Cavium2132SBus *obj,unsigned int adr, unsigned char dat) {
  //assert(obj->last_gpio_adr == 0x3); // unneeded???

  if (adr & 0x1) {
    obj->gpiobus->Poke32(obj->gpiobus,0,0x2<<15|1<<17);
    _Cavium2132SBusPoke16(obj,adr, dat << 8);
  } else {
    obj->gpiobus->Poke32(obj->gpiobus,0,0x2<<15|1<<3);
    _Cavium2132SBusPoke16(obj,adr, dat);
  }
  obj->gpiobus->Poke32(obj->gpiobus,0,0x2<<15|1<<17|1<<3);
}

__attribute__((always_inline)) 
static inline unsigned _Cavium2132SBusPeek32(Cavium2132SBus *obj,unsigned int adr) {
  unsigned int ret;
  unsigned short l, h;
  l = _Cavium2132SBusPeek16(obj,adr);
  h = _Cavium2132SBusPeek16(obj,adr + 2);
  ret = (l|(h<<16));
  return ret;
}

__attribute__((always_inline)) 
static inline void _Cavium2132SBusPoke32(Cavium2132SBus *obj,unsigned int adr, unsigned dat) {
  _Cavium2132SBusPoke16(obj,adr, dat & 0xffff);
  _Cavium2132SBusPoke16(obj,adr + 2, dat >> 16);
}

void Cavium2132SBusPeekStream(Cavium2132SBus *obj,int adr,int dir,char* dat) {
  unsigned int dummy;
  // same ugly hack as above!
  struct HACK { Bus f; volatile unsigned *data; };
  volatile unsigned int *spi = ((struct HACK *)(obj->spibus))->data;
  int len = ArrayLength(dat);

  if (obj->last_gpio_adr != adr >> 5) {
    obj->last_gpio_adr = adr >> 5;
    int tmp = obj->gpiobus->Peek32(obj->gpiobus,0);
    obj->gpiobus->Poke32(obj->gpiobus,0,tmp & ~(0x3<<15)|((adr>>5)<<15));
  }

  adr &= 0x1f;
  asm volatile(
	       "mov %0, #0x0\n"
	       "str %0, [%4, #0x4c]\n"
	       "mov %1, %1, lsl #18\n"
	       "orr %1, %1, #(1<<15)\n"
	       "2: str %1, [%4, #0x50]\n"
	       "1: ldr %0, [%4, #0x64]\n"
	       "cmp %0, #0x0\n"
	       "beq 1b\n"
	       "ldr %0, [%4, #0x58]\n"
	       "tst %0, #0x10000\n"
	       "beq 2b\n"
	       "\n"
	       "3:\n"
	       "strh %0, [%3], #0x2\n"
	       "mov %0, #0x80000001\n"
	       "orr %0, %0, #0xc00\n"
	       "str %0, [%4, #0x40]\n"
	       "ldr %0, [%4, #0x40]\n"
	       "str %1, [%4, #0x50]\n"
	       "str %1, [%4, #0x50]\n"
	       "sub %2, %2, #0x4\n"
	       "4: str %1, [%4, #0x50]\n"
	       "5: ldr %0, [%4, #0x64]\n"
	       "cmp %0, #0x0\n"
	       "beq 5b\n"
	       "ldr %0, [%4, #0x58]\n"
	       "subs %2, %2, #0x1\n"
	       "strh %0, [%3], #0x2\n"
	       "bne 4b\n"
	       "\n"
	       "mov %0, #0x4\n"
	       "str %0, [%4, #0x4c]\n"
	       "mov %1, #0x0\n"
	       "str %1, [%4, #0x50]\n"
	       "6: ldr %0, [%4, #0x64]\n"
	       "cmp %0, #0x0\n"
	       "beq 6b\n"
	       "ldr %0, [%4, #0x58]\n"
	       "strh %0, [%3], #0x2\n"
	       "\n"
	       "7: ldr %0, [%4, #0x64]\n"
	       "cmp %0, #0x0\n"
	       "beq 7b\n"
	       "ldr %0, [%4, #0x58]\n"
	       "strh %0, [%3], #0x2\n"
	       "\n"
	       "8: ldr %0, [%4, #0x64]\n"
	       "cmp %0, #0x0\n"
	       "beq 8b\n"
	       "ldr %0, [%4, #0x58]\n"
	       "strh %0, [%3], #0x2\n"
	       "\n"
	       "mov %0, #0x80000002\n"
	       "orr %0, %0, #0xc00\n"
	       "str %0, [%4, #0x40]\n"
	       : "+r"(dummy), "+r"(adr), "+r"(len), "+r"(dat)
	       : "r"(spi)
	       : "cc", "memory"
	       );
}

void Cavium2132SBusPokeStream(Cavium2132SBus *obj,int adr,int dir,const char* dat) {
  // same ugly hack as above!
  struct HACK { Bus f; volatile unsigned *data; };
  volatile unsigned int *spi = ((struct HACK *)(obj->spibus))->data;
  unsigned int cmd, ret, i, j;
  int len = ArrayLength(dat);

  if (obj->last_gpio_adr != adr >> 5) {
    obj->last_gpio_adr = adr >> 5;
    int tmp = obj->gpiobus->Peek32(obj->gpiobus,0);
    obj->gpiobus->Poke32(obj->gpiobus,0,tmp & ~(0x3<<15)|((adr>>5)<<15));
  }

  adr &= 0x1f;
  spi[0x4c/4] = 0x0;	/* continuous CS# */
  cmd = (adr<<18) | 0x800000 | (dat[0]<<3) | (dat[1]>>13);
  do {
    spi[0x50/4] = cmd;
    cmd = dat[1]>>13;
    while (spi[0x64/4] == 0);
    ret = spi[0x58/4];
    assert (spi[0x64/4] == 0); /* */
  } while (!(ret & 0x1));
  
  spi[0x40/4] = 0x80000c01; /* 16 bit mode */
  i = len - 1;
  len -= 6;
  dat++;
  
  for (j = 0; j < 4; j++) {
    spi[0x50/4] = (dat[0]<<3) | (dat[1]>>13);
    dat++;
  }
  
  while (len--) {
    spi[0x50/4] = (dat[0]<<3) | (dat[1]>>13);
    dat++;
    while (spi[0x64/4] == 0);
    spi[0x58/4]; 
    i--;
  } 
  
  spi[0x4c/4] = 0x4;	/* deassert CS# */
  spi[0x50/4] = dat[0]<<3;
  
  while (i) {
    while ((spi[0x64/4]) == 0);
    spi[0x58/4];
    i--;
  }
  
  spi[0x40/4] = 0x80000c02; /* 24 bit mode */

}

DefinitionFunctionsBit(Cavium2132SBus,unsigned char,8)
DefinitionFunctionsBit(Cavium2132SBus,unsigned short,16)
DefinitionFunctionsBit(Cavium2132SBus,unsigned,32)

static void reservemem(void) {
#ifdef __linux__
	char dummy[32768];
	int i, pgsize,line=1;
	FILE *maps;

	pgsize = getpagesize();
	mlockall(MCL_CURRENT|MCL_FUTURE);
	for (i = 0; i < sizeof(dummy); i += 4096) {
		dummy[i] = 0;
	}

	maps = fopen("/proc/self/maps", "r"); 
	if (maps == NULL) {
		perror("/proc/self/maps");
		exit(1);
	}
	while (!feof(maps)) {
		size_t s, e, x;
		char perms[16];
		char str[256];
		if (!fgets(str,254,maps)) break;
		//printf("%d:%s",line,str);
		//int r = fscanf(maps, "%zx-%zx %s %*x %zx:%*x %*d",
		//&s, &e, perms, &x);
		int r = sscanf(str, "%zx-%zx %s %*x %zx:%*x %*d",
			       &s,&e,perms,&x);
		if (r == EOF) break;
		if (r != 4) {
		  printf("r=%d, line %d\n",r,line);
		  system("cat /proc/self/maps");
		}
		line++;
		assert (r == 4);

		while ((r = fgetc(maps)) != '\n') if (r == EOF) break;
		assert(s <= e && (s & 0xfff) == 0);
		if (perms[0] == 'r' && perms[3] == 'p' && x != 1) 
		  while (s < e) {
			volatile unsigned char *ptr = (unsigned char *)s;
			unsigned char d;
			d = *ptr;
			if (perms[1] == 'w') *ptr = d;
			s += pgsize;
		}
	}
	fclose(maps);
#endif
}
/*
static void reservemem(void) {
	char dummy[32768];
	int i, pgsize;
	FILE *maps;

	pgsize = getpagesize();
	mlockall(MCL_CURRENT|MCL_FUTURE);
	for (i = 0; i < sizeof(dummy); i += 4096) {
		dummy[i] = 0;
	}

	maps = fopen("/proc/self/maps", "r"); 
	if (maps == NULL) {
		perror("/proc/self/maps");
		exit(1);
	}
	while (!feof(maps)) {
		unsigned int s, e, i;
		char m[PATH_MAX + 1];
		char perm[16];
		int r = fscanf(maps, "%x-%x %s %*x %*x:%*x %*d",
		  &s, &e, perm);
		if (r == EOF) break;
		if (r != 3) {
		  printf("r=%d\n",r);
		  system("cat /proc/self/maps");
		}
		assert (r == 3);

		i = 0;
		while ((r = fgetc(maps)) != '\n') {
			if (r == EOF) break;
			m[i++] = r;
		}
		m[i] = '\0';
		assert(s <= e && (s & 0xfff) == 0);
		if (perm[0] == 'r' && perm[3] == 'p') while (s < e) {
		    volatile unsigned char *ptr = (unsigned char *)s;
		    unsigned char d;
		    d = *ptr;
		    if (perm[1] == 'w') *ptr = d;
		    s += pgsize;
		  }
	}
}
*/
// Author: Michael Schmidt (michael@embeddedARM.com)
// Some portions based on code by Jesse Off (joff@embeddedARM.com)
// Copyright (c) 2012, Technologic Systems, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
