#ifndef DIOSPI_c
#define DIOSPI_c
#include "DIO.h"
#include "Time.h"
#include "DIOSPI.h"

void *DIOSPIInit(DIOSPI* ob,DIO *cs0,DIO *cs1,DIO *cs2,DIO *cs3,int SPI_CS0,int SPI_CS1,int SPI_CS2,int SPI_CS3,DIO *mosi,int SPI_MOSI,DIO *miso,int SPI_MISO,DIO *clk,int SPI_CLK,Time *t) {
  if (ob->InitStatus > 0) return ob;

  ob->Init = (void *)DIOSPIInit;
  ob->Fini = (void *)DIOSPIFini;
  ob->Lock = (void *)DIOSPILock;
  ob->Unlock = (void *)DIOSPIUnlock;
  ob->Preempt = (void *)DIOSPIPreempt;
  ob->Write = (void *)DIOSPIWrite;
  ob->Read = (void *)DIOSPIRead;
  ob->ReadWrite = (void *)DIOSPIReadWrite;
  ob->ClockSet = (void *)DIOSPIClockSet;
  ob->EdgeSet = (void *)DIOSPIEdgeSet;

  ob->delay = 0; // max speed

  ob->cs[0] = cs0;
  ob->cs[1] = cs1;
  ob->cs[2] = cs2;
  ob->cs[3] = cs3;
  ob->SPI_CS[0] = SPI_CS0;
  ob->SPI_CS[1] = SPI_CS1;
  ob->SPI_CS[2] = SPI_CS2;
  ob->SPI_CS[3] = SPI_CS3;
  ob->mosi = mosi;
  ob->SPI_MOSI = SPI_MOSI;
  ob->miso = miso;
  ob->SPI_MISO = SPI_MISO;
  ob->clk = clk;
  ob->SPI_CLK = SPI_CLK;
  ob->t = t;

  ob->InitStatus = 1;
  return ob;
}

void DIOSPIFini(DIOSPI* ob) {
  if (ob->InitStatus > 0) ob->InitStatus = 0;
}

int DIOSPILock(DIOSPI* ob,unsigned num,int flags) {
  int ret;

  if (flags & SHARED) return -11;
  if ((ret=ob->cs[0]->Lock(ob->cs[0],ob->SPI_CS[0],0)) < 0) {
    goto DoRelease7;
  }
  if ((ret=ob->cs[1]->Lock(ob->cs[1],ob->SPI_CS[0],0)) < 0) {
    goto DoRelease6;
  }
  if ((ret=ob->cs[2]->Lock(ob->cs[2],ob->SPI_CS[0],0)) < 0) {
    goto DoRelease5;
  }
  if ((ret=ob->cs[3]->Lock(ob->cs[3],ob->SPI_CS[0],0)) < 0) {
    goto DoRelease4;
  }
  if ((ret=ob->mosi->Lock(ob->mosi,ob->SPI_MOSI,0)) < 0) {
    goto DoRelease3;
  }
  if ((ret=ob->miso->Lock(ob->miso,ob->SPI_MISO,0)) < 0) {
    goto DoRelease2;
  }
  if ((ret=ob->clk->Lock(ob->clk,ob->SPI_CLK,0)) < 0) {
    goto DoRelease1;
  }
  return 1;
 DoRelease:
   ob->clk->Unlock(ob->clk,ob->SPI_CLK,0);
 DoRelease1:
   ob->miso->Unlock(ob->miso,ob->SPI_MISO,0);
 DoRelease2:
   ob->mosi->Unlock(ob->mosi,ob->SPI_MOSI,0);
 DoRelease3:
   ob->cs[3]->Unlock(ob->cs[3],ob->SPI_CS[3],0);
 DoRelease4:
   ob->cs[2]->Unlock(ob->cs[2],ob->SPI_CS[2],0);
 DoRelease5:
   ob->cs[1]->Unlock(ob->cs[1],ob->SPI_CS[1],0);
 DoRelease6:
   ob->cs[0]->Unlock(ob->cs[0],ob->SPI_CS[0],0);
 DoRelease7:
   return ret;
}

int DIOSPIUnlock(DIOSPI* ob,unsigned num,int flags) {
   ob->clk->Unlock(ob->clk,ob->SPI_CLK,0);
   ob->miso->Unlock(ob->miso,ob->SPI_MISO,0);
   ob->mosi->Unlock(ob->mosi,ob->SPI_MOSI,0);
   ob->cs[3]->Unlock(ob->cs[3],ob->SPI_CS[3],0);
   ob->cs[2]->Unlock(ob->cs[2],ob->SPI_CS[2],0);
   ob->cs[1]->Unlock(ob->cs[1],ob->SPI_CS[1],0);
   ob->cs[0]->Unlock(ob->cs[0],ob->SPI_CS[0],0);
   return 1;
}

int DIOSPIPreempt(DIOSPI* ob) {
}

int _DIOSPIReadWrite(DIOSPI *ob,int adrs,const unsigned char* buf,unsigned char* wbuf) {
  int n=0,clkval,SPI_CS,bits,nbits=8;
  DIO *cs;
  const char *ptr = buf; char *wptr = wbuf;
  unsigned char ch, wch = 0;

  if (buf) {
    bits = ArrayLength(buf)*8;
    ch = buf[0]; ptr++;
  } else {
    bits = ArrayLength(wbuf)*8;
    ch = 0;
  }

  if (adrs == 0 || adrs > 4 || adrs < -4) return SPIErrorInvalidAddress;
  if (bits == 0) return SPISuccess; // nothing to do!
  if (adrs < 0) {
    cs = ob->cs[-adrs];
    SPI_CS = ob->SPI_CS[-adrs];
  } else {
    cs = ob->cs[adrs-1];
    SPI_CS = ob->SPI_CS[adrs-1];
  }
  clkval = ob->CPOL;
  ob->miso->SetAsync(ob->miso,ob->SPI_MISO,INPUT);
  //printf("initial clock value = %d\n",clkval);
  ob->clk->SetAsync(ob->clk,ob->SPI_CLK,clkval);
  if (ob->delay) ob->t->Delay(ob->t,ob->delay);
  cs->SetAsync(cs,SPI_CS,LOW); // assert CS
  if (ob->CPHA) {
    if (ob->delay) ob->t->Delay(ob->t,ob->delay);
  } else {
    ob->mosi->SetAsync(ob->mosi,ob->SPI_MOSI,(ch & 0x80) ? HIGH : LOW);
    ch <<= 1;
    --bits; --nbits;
    if (ob->delay) ob->t->Delay(ob->t,ob->delay);
    if (wbuf) {
      wch <<= 1;
      wch |= DIOValue(ob->miso->GetAsync(ob->miso,ob->SPI_MISO));
    }
    clkval = (clkval == HIGH) ? LOW:HIGH;
    ob->clk->SetAsync(ob->clk,ob->SPI_CLK,clkval);
  }
  while (bits) {
    clkval = (clkval == HIGH) ? LOW:HIGH;
    ob->clk->SetAsync(ob->clk,ob->SPI_CLK,clkval);
    ob->mosi->SetAsync(ob->mosi,ob->SPI_MOSI,(ch & 0x80) ? HIGH : LOW);
    ch <<= 1;
    --bits;
    if (--nbits == 0) {
      nbits = 8;
      if (ptr) { 
	ch = *(ptr++);
      }
    }
    if (ob->delay) ob->t->Delay(ob->t,ob->delay);
    if (wbuf) {
      wch <<= 1;
      wch |= DIOValue(ob->miso->GetAsync(ob->miso,ob->SPI_MISO));
      if (nbits == 8) {
	*(wptr++) = wch;
	wch = 0;
      }
    }
    clkval = (clkval == HIGH) ? LOW:HIGH;
    ob->clk->SetAsync(ob->clk,ob->SPI_CLK,clkval);
    if (ob->delay) ob->t->Delay(ob->t,ob->delay);
  }
  if (!ob->CPHA) {
    clkval = (clkval == HIGH) ? LOW:HIGH;
    ob->clk->SetAsync(ob->clk,ob->SPI_CLK,clkval);
    if (ob->delay) ob->t->Delay(ob->t,ob->delay);
  }
  ob->mosi->SetAsync(ob->mosi,ob->SPI_MOSI,INPUT);
  cs->SetAsync(cs,SPI_CS,HIGH); // de-assert CS
  return SPISuccess;
}

SPIResult DIOSPIWrite(DIOSPI* ob,int adrs,const unsigned char *buf) {
  return _DIOSPIReadWrite(ob,adrs,buf,0);
}

SPIResult DIOSPIRead(DIOSPI* ob,int adrs,unsigned char *buf) {
  return _DIOSPIReadWrite(ob,adrs,0,buf);
}

SPIResult DIOSPIReadWrite(DIOSPI* ob,int adrs,const unsigned char *wbuf,unsigned char *rbuf) {
  return _DIOSPIReadWrite(ob,adrs,wbuf,rbuf);
}

SPIResult DIOSPIClockSet(DIOSPI* ob,unsigned hz) {
  if (hz == 0) {
    ob->delay = 0;
    return SPISuccess;
  }
  ob->delay = 1000000 / hz;
  return SPISuccess;
}

SPIResult DIOSPIEdgeSet(DIOSPI* ob,int posedge) {
  switch (posedge) {
  case 0: ob->CPOL = 0; ob->CPHA = 0; break;
  case -1: ob->CPOL = 0; ob->CPHA = 1; break;
  case 1:  ob->CPOL = 1; ob->CPHA = 0; break;
  case -2: ob->CPOL = 1; ob->CPHA = 1; break;
  default: return SPIErrorInvalidEdge;
  }
  //ob->clk->SetAsync(ob->clk,ob->SPI_CLK,clkval);
  return SPISuccess;
}

#endif
