#ifndef AtmelAT91SPI_c
#define AtmelAT91SPI_c
#include "AtmelAT91SPI.h"
#include "Thread.h"
#include "Log.h"

// bus maps the AtmelAT91 SPI registers (p.403) (p.19)
// SPI0: 0xFFFC8000
// SPI1: 0xFFFCC000
//       0xFFFD0000
void *AtmelAT91SPIInit(AtmelAT91SPI *spi,void *bus1,void *pin,
		       DIO *dio1,int cs1,DIO *dio2,int cs2,DIO *dio3,int cs3) {
  Bus *bus = bus1;

  if (spi->InitStatus > 0) return spi;

  spi->Init = (void *)AtmelAT91SPIInit;
  spi->Fini = (void *)AtmelAT91SPIFini;
  spi->Lock = (void *)AtmelAT91SPILock;
  spi->Unlock = (void *)AtmelAT91SPIUnlock;
  spi->Preempt = (void *)AtmelAT91SPIPreempt;
  spi->Write = (void *)AtmelAT91SPIWrite;
  spi->Read = (void *)AtmelAT91SPIRead;
  spi->ReadWrite = (void *)AtmelAT91SPIReadWrite;
  spi->ClockSet = (void *)AtmelAT91SPIClockSet;
  spi->EdgeSet = (void *)AtmelAT91SPIEdgeSet;

  spi->LockNum = ThreadMutexAllocate(1);
  spi->bus = bus;
  spi->pin = pin;
  spi->dio1 = dio1;
  spi->dio2 = dio2;
  spi->dio3 = dio3;
  spi->cs1 = cs1;
  spi->cs2 = cs2;
  spi->cs3 = cs3;

  if (spi->bus->InitStatus <= 0
      || spi->dio1->InitStatus <= 0
      || spi->dio2->InitStatus <= 0
      || spi->dio3->InitStatus <= 0
      || spi->pin->InitStatus <= 0) {
    spi->Fini(spi);
    spi->InitStatus = -1;
    return spi;
  }

  spi->InitStatus = 1;
  return spi;
}

void AtmelAT91SPIReset(AtmelAT91SPI *spi,int reset) {
  spi->bus->Lock(spi->bus,0,0);
  int tmp0 = spi->bus->Peek32(spi->bus,0x30) & 0xFF00;
  int tmp1 = spi->bus->Peek32(spi->bus,0x34) & 0xFF00;
  int tmp2 = spi->bus->Peek32(spi->bus,0x38) & 0xFF00;
  int tmp3 = spi->bus->Peek32(spi->bus,0x3C) & 0xFF00;

  if (tmp0 == 0) tmp0 = 0x3100;
  if (tmp1 == 0) tmp1 = 0x3100;
  if (tmp2 == 0) tmp2 = 0x3100;
  if (tmp3 == 0) tmp3 = 0x3100;

  if (reset) {
    spi->bus->BitSet32(spi->bus,0,7); // SPI_CR.SWRST
    usleep(10000);
  }

  spi->bus->BitSet32(spi->bus,0,0); // SPI_CR.SPIEN = 1, enable SPI
  spi->bus->BitSet32(spi->bus,0,24); // SPI_CR.LASTXFER=1
  spi->bus->BitSet32(spi->bus,4,0); // SPI_MR.MSTR = 1, master mode
  spi->bus->BitSet32(spi->bus,4,1); // SPI_MR.PS = 1, variable peripheral set
  spi->bus->Poke32(spi->bus,0x30, // SPI_CSRn[7:4] = 0, set 8-bit length
			tmp0+8
			|(spi->bus->Peek32(spi->bus,0x30) & 0xFFFFFF07));
  spi->bus->Poke32(spi->bus,0x34, // SPI_CSRn[7:4] = 0, set 8-bit length
			tmp0+8
			|(spi->bus->Peek32(spi->bus,0x34) & 0xFFFFFF07));
  spi->bus->Poke32(spi->bus,0x38, // SPI_CSRn[7:4] = 0, set 8-bit length
			tmp0+8
			|(spi->bus->Peek32(spi->bus,0x38) & 0xFFFFFF07));
  spi->bus->Poke32(spi->bus,0x3C, // SPI_CSRn[7:4] = 0, set 8-bit length
			tmp0+8
			|(spi->bus->Peek32(spi->bus,0x3C) & 0xFFFFFF07));
  spi->bus->Unlock(spi->bus,0,0);
}

void AtmelAT91SPIFini(AtmelAT91SPI *spi) {
  spi->bus->Fini(spi->bus);
  if (spi->InitStatus > 0) spi->InitStatus = 0;
}

// what DIOs are SPCK, MISO, MOSI, NPCS0/NSS, NPCS1-3?
//   CN2_71 = SPI_CLK = PB2 (SPI1_SPCK)
//   CN2_69 = SPI_MISO = PB0
//   CN2_67 = SPI_MOSI = PB1
//   CN2_64/66 = AD_CS# on TS-8200
//   CN2_65 = SPI_CS0# = PB3
// do we need to implement Pin control to switch them to SPI?
//   probably.  use PIO Disable register. (p.374)
//   ts4200Pin needs 3 addtional busses: 4, 6, and 8.
//   for SPI1 we only need bus 6
//   we want peripheral function A (p.387)
// see p.393 for setting up SPI clock
//   p.301: enable peripheral clock SPI1 = PID 13
//   PMC_PCER bit 13 = 0xFFFFFC00 + 0x10
// SPI_CR = 0
// SPI_MR = 4
// SPI_RDR = 8
// SPI_TDR = 0xC
// SPI_SR = 0x10
// SPI_CSR0 = 0x30
// SPI_CSR1 = 0x34
// SPI_CSR2 = 0x38
// SPI_CSR3 = 0x3C
int AtmelAT91SPILock(AtmelAT91SPI *spi,unsigned num,int flags) {
  int ret;

  if (flags & SHARED) return ErrorInvalidArgument;
  // for CPU SPI,
  // CS0 = PB3
  // CS1 = PC5
  // CS2 = PC4
  // CS3 = PC3
  // but we map the latter 3 to PB25,26, and 27
  // which we currently assume to be DIO anyway
  if (ret=ThreadMutexLock(spi->LockNum,flags) < 0) return ret;
  spi->pin->Lock(spi->pin,32,0);
  spi->pin->Lock(spi->pin,33,0);
  spi->pin->Lock(spi->pin,34,0);
  spi->pin->Lock(spi->pin,35,0);
  spi->pin->ModeSet(spi->pin,32,MODE_SPI);
  spi->pin->ModeSet(spi->pin,33,MODE_SPI);
  spi->pin->ModeSet(spi->pin,34,MODE_SPI);
  spi->pin->ModeSet(spi->pin,35,MODE_SPI);
  AtmelAT91SPIReset(spi,0);
  return 1;
}
int AtmelAT91SPIUnlock(AtmelAT91SPI *spi,unsigned num,int flags) {
  if (flags & SHARED) return ErrorInvalidArgument;
  spi->pin->Unlock(spi->pin,32,0);
  spi->pin->Unlock(spi->pin,33,0);
  spi->pin->Unlock(spi->pin,34,0);
  spi->pin->Unlock(spi->pin,35,0);
  ThreadMutexUnlock(spi->LockNum);
  return 1;
}

int AtmelAT91SPIPreempt(AtmelAT91SPI *spi) {
}

static inline void AtmelAT91SPICSBegin(AtmelAT91SPI *spi,int adrs) {
  if (adrs >= 0) {
    spi->dio1->Lock(spi->dio1,spi->cs1,0);
    if (adrs != 1) spi->dio1->SetAsync(spi->dio1,spi->cs1,INPUT);
    else spi->dio1->SetAsync(spi->dio1,spi->cs1,LOW);
    spi->dio1->Unlock(spi->dio1,spi->cs1,0);

    spi->dio2->Lock(spi->dio2,spi->cs2,0);
    if (adrs != 2) spi->dio2->SetAsync(spi->dio2,spi->cs2,INPUT);
    else spi->dio2->SetAsync(spi->dio2,spi->cs2,LOW);
    spi->dio2->Unlock(spi->dio2,spi->cs2,0);

    spi->dio3->Lock(spi->dio3,spi->cs3,0);
    if (adrs != 3) spi->dio3->SetAsync(spi->dio3,spi->cs3,INPUT);
    else spi->dio3->SetAsync(spi->dio3,spi->cs3,LOW);
    spi->dio3->Unlock(spi->dio3,spi->cs3,0);
  }
}

static inline void AtmelAT91SPICSEnd(AtmelAT91SPI *spi,int cs) {
  if (cs > 0) {
    switch (cs) {
    case 1: 
      spi->dio1->Lock(spi->dio1,spi->cs1,0);
      spi->dio1->SetAsync(spi->dio1,spi->cs1,INPUT); 
      spi->dio1->Unlock(spi->dio1,spi->cs1,0);
      break;
    case 2: 
      spi->dio2->Lock(spi->dio2,spi->cs2,0);
      spi->dio2->SetAsync(spi->dio2,spi->cs2,INPUT); 
      spi->dio2->Unlock(spi->dio2,spi->cs2,0);
      break;
    case 3: 
      spi->dio3->Lock(spi->dio3,spi->cs3,0);
      spi->dio3->SetAsync(spi->dio3,spi->cs3,INPUT); 
      spi->dio3->Unlock(spi->dio3,spi->cs3,0);
      break;
    }
  }
}

static inline int AtmelAT91SPIWait(AtmelAT91SPI *spi) {
  unsigned count=0;

  // was bit 9
  while (!spi->bus->BitGet32(spi->bus,0x10,9)) { 
    if (++count > 1000000) {
      //log9(LOG_SPI,"timeout: %08X\n",spi->bus->Peek32(spi->bus,0x10));
      AtmelAT91SPIReset(spi,1);
      spi->bus->Unlock(spi->bus,0,0);
      return 0;
    }
  }
  return 1;
}

static inline int AtmelAT91PCS(int cs) {
  switch (cs) {
  case 0: return 0xE0000;
  case 1: return 0xD0000;
  case 2: return 0xB0000;
  case 3: 
  default: return 0x70000;
  }
}

int AtmelAT91SPIWrite(AtmelAT91SPI *spi,int adrs,const unsigned char* buf) {
  int len = ArrayLength(buf);
  int de_cs = len,tmp;

  if (adrs < 0) {
    adrs = -adrs;
    de_cs = len+1;
  }
  adrs--;
  if (adrs > 3) return -5;
  AtmelAT91SPICSBegin(spi,adrs);
  spi->bus->Lock(spi->bus,0,0);
  while (len--) {
    tmp = ((de_cs>1)?0:(1<<24)) 
      + AtmelAT91PCS(adrs) + *(buf++);
    //log9(LOG_SPI,"tmp=%08X, adrs=%d, len=%d, de_cs=%d\n",tmp,adrs,len,de_cs);
    spi->bus->Poke32(spi->bus,0x0C,tmp);
    de_cs--;
    if (!AtmelAT91SPIWait(spi)) return -9;
    spi->bus->Peek32(spi->bus,0x08); // clear out SPI_RDR
  }
  if (de_cs <= 0) AtmelAT91SPICSEnd(spi,adrs);
  spi->bus->Unlock(spi->bus,0,0);
  return 1;
}

int AtmelAT91SPIRead(AtmelAT91SPI *spi,int adrs,unsigned char* buf) {
  int len = ArrayLength(buf);
  int de_cs = len,tmp;

  if (adrs < 0) {
    adrs = -adrs;
    de_cs = len+1;
  }
  adrs--;
  if (adrs > 3) return -5;
  AtmelAT91SPICSBegin(spi,adrs);
  spi->bus->Lock(spi->bus,0,0);
  while (len--) {
    int tmp;

    tmp = ((de_cs>1)?0:(1<<24)) + AtmelAT91PCS(adrs);
    spi->bus->Poke32(spi->bus,0x0C,tmp);
    de_cs--;
    if (!AtmelAT91SPIWait(spi)) return -9;
    *(buf++) = spi->bus->Peek32(spi->bus,0x08) & 0xFF;
  }

  if (de_cs <= 0) AtmelAT91SPICSEnd(spi,adrs);
  spi->bus->Unlock(spi->bus,0,0);

}

int AtmelAT91SPIReadWrite(AtmelAT91SPI *spi,int adrs,const unsigned char* wbuf,unsigned char* rbuf) {
  int len = ArrayLength(rbuf) > ArrayLength(wbuf) ? ArrayLength(wbuf):ArrayLength(rbuf);;
  int de_cs = len,got,tmp;

  //log9(LOG_SPI,"SPI RW@%d for %d\n",adrs,len);
  if (adrs < 0) {
    adrs = -adrs;
    de_cs = len+1;
  }
  adrs--;
  if (adrs > 3) return -5;
  AtmelAT91SPICSBegin(spi,adrs);
  spi->bus->Lock(spi->bus,0,0);
  //spi->bus->BitSet32(spi->bus,0,24); // SPI_CR.LASTXFER=1, needed
  while (len--) {
    //printf("%08X (%d) ",((de_cs)?0:(1<<24)) 
    // + (adrs << 16) + *wbuf,de_cs); fflush(stdout);
    tmp = ((de_cs>1)?0:(1<<24)) 
      + AtmelAT91PCS(adrs) + *(wbuf++);
    //log9(LOG_SPI,"tmp=%08X, adrs=%d, len=%d, de_cs=%d\n",tmp,adrs,len,de_cs);
    spi->bus->Poke32(spi->bus,0x0C,tmp);
    //printf("?"); fflush(stdout);
    de_cs--;
    if (!AtmelAT91SPIWait(spi)) return -9;
    *(rbuf++) = (got=spi->bus->Peek32(spi->bus,0x08)) & 0xFF;
    //printf(". %08X\n",got); fflush(stdout);
  }
  if (de_cs <= 0) AtmelAT91SPICSEnd(spi,adrs);
  spi->bus->Unlock(spi->bus,0,0);
  return 1;
}

int AtmelAT91SPIClockSet(AtmelAT91SPI *spi,unsigned hz) {
  // SPI_CSRx[15:8] = SCBR
  // SCBR = MCK / baud rate
  // MCK = 99 Mhz
  unsigned SCBR = 99000000/hz;
  int val;
  spi->bus->Lock(spi->bus,0,0);
  spi->bus->Poke32(spi->bus,0x30,
			spi->bus->Peek32(spi->bus,0x30)
			& 0xFFFF00F7
			| ((SCBR << 8) & 0xFF00));
  spi->bus->Poke32(spi->bus,0x34,
			spi->bus->Peek32(spi->bus,0x34)
			& 0xFFFF00F7
			| ((SCBR << 8) & 0xFF00));
  spi->bus->Poke32(spi->bus,0x38,
			spi->bus->Peek32(spi->bus,0x38)
			& 0xFFFF00F7
			| ((SCBR << 8) & 0xFF00));
  spi->bus->Poke32(spi->bus,0x3C,
			spi->bus->Peek32(spi->bus,0x3C)
			& 0xFFFF00F7
			| ((SCBR << 8) & 0xFF00));
  spi->bus->Unlock(spi->bus,0,0);
  return 1;
}

// spi->bus->BitAssign(spi->bus,0x30;0x34,0x38,0x3C,0;1);
// p.395, 414
// CPOL=0 means leading edge is rising edge (active low clock)
// CPOL=1 means leading edge is falling edge (active high clock)
// NCPHA=0 means data captured on the active edge and changed on the next
//         "changed on leading edge and captured on next edge"
// NCPHA=1 means data is changed on the active edge and captured on the next
//         "captured on leading edge and changed on next edge"
//
// CPOL=0,CPHA=0, capture on inactive (rising) edge
// CPOL=0,CPHA=1, data captured on active (falling) edge
// CPOL=1,CPHA=0, data captured on inactive (falling) edge
// CPOL=1,CPHA=1, data captured on active (rising) edge
// http://en.wikipedia.org/wiki/Serial_Peripheral_Interface_Bus
// CPOL is bit 0, CPHA is bit 1

// CPOL seems to correspond to whether the clock is active high or low
// specifically, CPOL = the idle state of the clock
// CPHA seems to correspond to what edge data changes on
// MOSI data changes on the:
// -2: positive edge, active edge
// -1: negative edge, inactive edge
// 0: negative edge, active edge
// 1: positive edge, inactive edge
// CPHA=0 means change data on active edge, 1 means inactive
// data sheet actually calls this signal NCPHA
// MISO data changes on whichever edge the slave thinks it should
// for the 81x0 ADC this appears to be on the negative edge
int AtmelAT91SPIEdgeSet(AtmelAT91SPI *spi,int posedge) {
  int CPOL, CPHA;

  switch (posedge) {
  case 0: CPOL = 0; CPHA = 0; break;
  case -1: CPOL = 0; CPHA = 1; break;
  case 1:  CPOL = 1; CPHA = 0; break;
  case -2: CPOL = 1; CPHA = 1; break;
  default: return -10;
  }
  spi->bus->Lock(spi->bus,0,0);
  spi->bus->BitAssign32(spi->bus,0x30,0,CPOL);
  spi->bus->BitAssign32(spi->bus,0x30,1,CPHA);
  spi->bus->BitAssign32(spi->bus,0x34,0,CPOL);
  spi->bus->BitAssign32(spi->bus,0x34,1,CPHA);
  spi->bus->BitAssign32(spi->bus,0x38,0,CPOL);
  spi->bus->BitAssign32(spi->bus,0x38,1,CPHA);
  spi->bus->BitAssign32(spi->bus,0x3C,0,CPOL);
  spi->bus->BitAssign32(spi->bus,0x3C,1,CPHA);
  spi->bus->Unlock(spi->bus,0,0);
  return 1;
}
#endif
