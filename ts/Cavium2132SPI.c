#include "Cavium2132SPI.h"

static SPIAPI Cavium2132SPIAPI =  {
  .Init = (void *)Cavium2132SPIInit,
  .Fini = (void *)Cavium2132SPIFini,
  .Lock = (void *)Cavium2132SPILock,
  .Write = (void *)Cavium2132SPIWrite,
  .Read = (void *)Cavium2132SPIRead,
  .ReadWrite = (void *)Cavium2132SPIReadWrite,
  .ClockSet = (void *)Cavium2132SPIClockSet,
  .EdgeSet = (void *)Cavium2132SPIEdgeSet
};

void *Cavium2132SPIInit(Cavium2132SPI *spi,void *bus1) {
  Bus *bus = bus1;

  if (spi->InitStatus > 0) return spi;

  spi->Init = (void *)Cavium2132SPIInit;
  spi->Fini = (void *)Cavium2132SPIFini;
  spi->Lock = (void *)Cavium2132SPILock;
  spi->Write = (void *)Cavium2132SPIWrite;
  spi->Read = (void *)Cavium2132SPIRead;
  spi->ReadWrite = (void *)Cavium2132SPIReadWrite;
  spi->ClockSet = (void *)Cavium2132SPIClockSet;
  spi->EdgeSet = (void *)Cavium2132SPIEdgeSet;

  spi->bus = bus;

  if (spi->bus->InitStatus <= 0) {
    spi->Fini(spi);
    spi->InitStatus = -1;
    return spi;
  }

  spi->InitStatus = 1;
  return spi;
}

void Cavium2132SPIFini(Cavium2132SPI *spi) {
  spi->bus->Fini(spi->bus);
  if (spi->InitStatus > 0) spi->InitStatus = 0;
}

int Cavium2132SPILock(Cavium2132SPI *spi,int command,unsigned num) {
  int ret;

  switch (command) {
  case WaitLock:
  case TryLock:
    if ((ret=lock->Lock(lock,command,spi->LockNum)) < 0) return ret;
    /*
    if ((ret=spi->dio->Lock(spi->dio,command,spi->TW_CLK)) < 0) {
      command = DoRelease;
      goto DoRelease2;
    }
    if ((ret=spi->dio->Lock(spi->dio,command,spi->TW_DAT)) < 0) {
      command = DoRelease;
      goto DoRelease1;
    }
    */
    return 1;
  case DoRelease:
    /*
    ret = 1;
    spi->dio->Lock(spi->dio,command,spi->TW_DAT);
  DoRelease1:
    spi->dio->Lock(spi->dio,command,spi->TW_CLK);
  DoRelease2:
    */
    lock->Lock(lock,command,spi->LockNum); // SPI mutex
    return ret;
  case DoPreempt:
    Cavium2132SPILock(spi,DoRelease,num);
    sched_yield();
    return Cavium2132SPILock(spi,WaitLock,num);
  }
  return 0;
}

/*
0x40 is this reg:
* base + 0x0: LUN register (R/W)
*   bit 15: spi miso state (RO)
*   bit 14: spi clk state (RW)
*   bits 13-10: speed[3:0] (0- highest, 1- 1/2 speed, 2- 1/4, etc..) (RW)
*   bits 9-8: LUN (0-3 representing the 4 CS# signals) (RW)
*   bit 7: CS (1 - CS# is asserted) (RW)
*   bits 6-1: reserved
*   bit 0: speed[4] (RW)
 */
int Cavium2132SPIChipSelect(Cavium2132SPI *ob,unsigned num,int assert) {
  if (num > 3) return -1;
  ob->bus->Lock(ob->bus,WaitLock,0);
  ob->bus->Poke16(ob->bus,0x40,
		  (ob->bus->Peek16(ob->bus,0x40) & 0xFC7F)
		  | (num << 8) | ((assert?1:0) << 7));
  ob->bus->Lock(ob->bus,DoRelease,0);
  return 1;
}

int Cavium2132SPIWrite(Cavium2132SPI *ob,int adrs,char *buf,int len) {
  int n = len,reg;
  int de_cs = 1;
  int maxspeed;

  if (adrs == 0 || adrs > 4 || adrs < -4) return SPIErrorInvalidAddress;
  if (adrs < 0) {
    adrs = -adrs;
    de_cs = 0;
  }
  adrs--;
  if (adrs == 0) adrs=1; else if (adrs == 1) adrs=0;
  Cavium2132SPIChipSelect(ob,adrs,1);
  ob->bus->Lock(ob->bus,WaitLock,0);
  reg = ob->bus->Peek16(ob->bus,0x40);
  maxspeed = ((reg >> 10) & 0xF) == 0 && ((reg & 1) == 0);
  if (n > 16 && maxspeed) {
    if (n % 2 == 0) {
      ob->bus->PokeStream(ob->bus,0x4A,1,buf,(n-2)/2);
      n = 2;
    } else {
      ob->bus->PokeStream(ob->bus,0x4A,1,buf,(n-3)/2);
      n = 3;
    }
  }
  while (n >= 4) {
    ob->bus->Poke16(ob->bus,0x48,buf[1]+(buf[0]<<8));
    buf += 2;
    n -= 2;
  }
  if (n > 2) { // n == 3
    ob->bus->Poke16(ob->bus,0x48,buf[1]+(buf[0]<<8));
    buf += 2;
    n -= 2;
    ob->bus->Poke16(ob->bus,de_cs?0x4C:0x48,buf[0]);
  } else if (n == 2) {
    ob->bus->Poke16(ob->bus,de_cs?0x4C:0x48,buf[1]+(buf[0]<<8));
    buf += 2;
    n -= 2;
  } else if (n == 1) {
    ob->bus->Poke8(ob->bus,de_cs?0x4C:0x48,buf[0]);
  }
  ob->bus->Lock(ob->bus,DoRelease,0);
  return SPISuccess;
}

int Cavium2132SPIRead(Cavium2132SPI *ob,int adrs,char *buf,int len) {
  unsigned s;
  int i,n = len,reg;
  int de_cs = 1, maxspeed;

  if (adrs == 0 || adrs > 4 || adrs < -4) return SPIErrorInvalidAddress;
  if (adrs < 0) {
    adrs = -adrs;
    de_cs = 0;
  }
  adrs--;
  if (adrs == 0) adrs=1; else if (adrs == 1) adrs=0;
  Cavium2132SPIChipSelect(ob,adrs,1);
  ob->bus->Lock(ob->bus,WaitLock,0);
  reg = ob->bus->Peek16(ob->bus,0x40);
  maxspeed = ((reg >> 10) & 0xF) == 0 && ((reg & 1) == 0);
  if (n > 16 && maxspeed) {
    if (n % 2 == 0) {
      ob->bus->PeekStream(ob->bus,0x4A,1,buf,(n-2)/2);
      for (i=0;i<n-2;i+=2) { // swap byte order
	unsigned char b;

	b = buf[i];
	buf[i] = buf[i+1];
	buf[i+1] = b;
      }
      buf += (n-2);
      n = 2;
    } else {
      ob->bus->PeekStream(ob->bus,0x4A,1,buf,(n-3)/2);
      for (i=0;i<n-2;i+=2) { // swap byte order
	unsigned char b;

	b = buf[i];
	buf[i] = buf[i+1];
	buf[i+1] = b;
      }
      buf += (n-3);
      n = 3;
    }
  }
  while (n >= 4) {
    s = ob->bus->Peek16(ob->bus,0x4A); // pipelined read
    *buf++ = s & 0xff;
    *buf++ = s >> 8;
    n -= 2;
  }
  if (n > 2) { // n == 3
    s = ob->bus->Peek16(ob->bus,0x48); // read, leave CS# asserted
    *buf++ = s & 0xff;
    *buf++ = s >> 8;
    n -= 2;
    ob->bus->Poke8(ob->bus,de_cs?0x4C:0x48,0);
    *buf = ob->bus->Peek16(ob->bus,0x42) >> 8;
  } else if (n == 2) {
    s = ob->bus->Peek16(ob->bus,de_cs?0x4C:0x48);
    *buf++ = s & 0xff;
    *buf++ = s >> 8;
    n -= 2;
  } else if (n == 1) {
    ob->bus->Poke8(ob->bus,de_cs?0x4C:0x48,0);
    *buf = ob->bus->Peek16(ob->bus,0x42) >> 8;
  }  
  ob->bus->Lock(ob->bus,DoRelease,0);
  return SPISuccess;
}

int Cavium2132SPIReadWrite(Cavium2132SPI *ob,int adrs,unsigned char *wbuf,unsigned char *rbuf, int len) {
  unsigned s;
  int n = len, de_cs=1;

  if (adrs == 0 || adrs > 4 || adrs < -4) return SPIErrorInvalidAddress;
  if (adrs < 0) {
    adrs = -adrs;
    de_cs = 0;
  }
  adrs--;
  if (adrs == 0) adrs=1; else if (adrs == 1) adrs=0;
  Cavium2132SPIChipSelect(ob,adrs,1);
  ob->bus->Lock(ob->bus,WaitLock,0);
  while (n >= 4) {
    ob->bus->Poke16(ob->bus,0x48,wbuf[1]+(wbuf[0]<<8));
    s = ob->bus->Peek16(ob->bus,0x42);
    wbuf += 2;
    *rbuf++ = s & 0xff;
    *rbuf++ = s >> 8;
    n -= 2;
  }
  if (n > 2) { // n == 3
    ob->bus->Poke16(ob->bus,0x48,wbuf[1]+(wbuf[0]<<8));
    s = ob->bus->Peek16(ob->bus,0x48);
    wbuf += 2;
    *rbuf++ = s & 0xff;
    *rbuf++ = s >> 8;
    n -= 2;
    ob->bus->Poke8(ob->bus,de_cs?0x4C:0x48,wbuf[0]);
    *rbuf = ob->bus->Peek8(ob->bus,0x42);
  } else if (n == 2) {
    ob->bus->Poke16(ob->bus,de_cs?0x4C:0x48,wbuf[1]+(wbuf[0]<<8));
    s = ob->bus->Peek16(ob->bus,0x42);
    *rbuf++ = s & 0xff;
    *rbuf++ = s >> 8;
    n -= 2;
  } else if (n == 1) {
    ob->bus->Poke8(ob->bus,de_cs?0x4C:0x48,wbuf[0]);
    *rbuf = ob->bus->Peek8(ob->bus,0x42);
  }
  ob->bus->Lock(ob->bus,DoRelease,0);
  return SPISuccess;
}

static int cavium_spi_f[] = {
  75000000,37500000,18750000,12500000,9375000,
  7500000,6250000,5360000,4680000,4170000,
  3750000,3409090,3125000,2884615,2678571,
  2500000,2343750,2205882,2083333,1973684,
  1875000,1785714,1704545,1630434,1562500,
  1500000,1442307,1388888,1339285,1293103,
  1250000,0 // 1209677
};

int Cavium2132SPIClockSet(Cavium2132SPI *ob,unsigned hz) {
  short reg,reg2;
  int i;
  if (hz == 0) return SPIErrorInvalidHz;
  for (i=0;cavium_spi_f[i]>hz;i++);
  ob->bus->Lock(ob->bus,WaitLock,0);
  reg = reg2 = ob->bus->Peek16(ob->bus,0x40);
  reg2 &= ~(15<<10); // mask out existing speed[3:0] bits
  reg2 |= (i & 15) << 10; // or in new speed[3:0] bits
  reg2 &= ~(1 << 0); // mask out existing speed[4] bit
  reg2 |= ((i >> 4) & 1); // or in new speed[4] bit
  if (reg2 != reg) {
    ob->bus->Poke16(ob->bus,0x40,reg2);
  }
  ob->bus->Lock(ob->bus,DoRelease,0);
  return SPISuccess;
}

SPIResult Cavium2132SPIEdgeSet(Cavium2132SPI *ob,int posedge) {
  short reg,reg2;
  int maxspeed;

  ob->bus->Lock(ob->bus,WaitLock,0);
  reg = reg2 = ob->bus->Peek16(ob->bus,0x40);
  maxspeed = ((reg >> 10) & 0xF) == 0 && ((reg & 1) == 0);
  reg &= ~(1<<14); // mask out existing clock polarity bit
  reg |= (((posedge?1:0)||maxspeed)?0:1) << 14; // or in new clock polarity bit
  if (reg2 != reg) {
    ob->bus->Poke16(ob->bus,0x40,reg2);
  }
  ob->bus->Lock(ob->bus,DoRelease,0);
  return SPISuccess;
}


// Author: Michael Schmidt (michael@embeddedTS.com)
// Copyright (c) 2011-2022 Technologic Systems, Inc. dba embeddedTS, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
