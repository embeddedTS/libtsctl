#ifndef DIOTWI_c
#define DIOTWI_c
#include <string.h>
#include <sched.h>
#include "DIOTWI.h"
#include "Thread.h"
#include "Array.h"
#define IA(x,...) (int[]){x,__VA_ARGS__}

/*
  Generic I2C/TWI bit-banged via DIO.

  The two DIO pins used for TW_CLK and TW_DAT are defined as configuration
 */

static unsigned read_bit(DIOTWI *twi)
{
  unsigned bit;
 
  // Let the slave drive data
  twi->dio->SetAsync(twi->dio,twi->TW_DAT,INPUT); // READSDA();
  twi->t->Delay(twi->t,twi->delay);
  // Clock stretching
  twi->dio->SetAsync(twi->dio,twi->TW_CLK,INPUT); // SCL=1
  while (twi->dio->GetAsync(twi->dio,twi->TW_CLK) == LOW);
  /* SCL is high, now data is valid */
  bit = DIOValue(twi->dio->GetAsync(twi->dio,twi->TW_DAT));
  twi->t->Delay(twi->t,twi->delay);
  twi->dio->SetAsync(twi->dio,twi->TW_CLK,LOW); // CLRSCL();
  return bit;
}
 
static int write_bit(DIOTWI *twi,unsigned bit)
{
  twi->dio->SetAsync(twi->dio,twi->TW_DAT,bit ? INPUT : LOW);
  twi->t->Delay(twi->t,twi->delay);
  // Clock stretching
  twi->dio->SetAsync(twi->dio,twi->TW_CLK,INPUT); // SCL=1
  while (twi->dio->GetAsync(twi->dio,twi->TW_CLK) == LOW);
  /* SCL is high, now data is valid */
  /* If SDA is high, check that nobody else is driving SDA */
  if (bit && DIOValue(twi->dio->GetAsync(twi->dio,twi->TW_DAT)) == LOW) {
      return TWIErrorArbLost;
  }
  twi->t->Delay(twi->t,twi->delay);
  twi->dio->SetAsync(twi->dio,twi->TW_CLK,LOW);
  return 0;
}

static int START(DIOTWI *twi)
{
  // SDA falling edge while SCL "stays high"
  if (twi->start) {
    twi->dio->SetAsync(twi->dio,twi->TW_DAT,INPUT); // SDA=1
    twi->t->Delay(twi->t,twi->delay);
    // Clock stretching
    twi->dio->SetAsync(twi->dio,twi->TW_CLK,INPUT); // SCL=1
    while (DIOValue(twi->dio->GetAsync(twi->dio,twi->TW_CLK)) == LOW);
  }
  twi->dio->SetAsync(twi->dio,twi->TW_DAT,INPUT); // i think we need this but is it fast enough?
  if (DIOValue(twi->dio->GetAsync(twi->dio,twi->TW_DAT)) == LOW) {
    return TWIErrorArbLost;
  }
  // SCL is high, set SDA from 1 to 0
  twi->dio->SetAsync(twi->dio,twi->TW_DAT,LOW);
  twi->t->Delay(twi->t,twi->delay);
  twi->dio->SetAsync(twi->dio,twi->TW_CLK,LOW);
  twi->start = 1;
  return 0;
}
 
static int STOP(DIOTWI *twi)
{
  // SDA rising edge while SCL "stays high"

  twi->dio->SetAsync(twi->dio,twi->TW_DAT,LOW); // SDA=0
  twi->t->Delay(twi->t,twi->delay);
  // Clock stretching
  twi->dio->SetAsync(twi->dio,twi->TW_CLK,INPUT); // SCL=1
  while (DIOValue(twi->dio->GetAsync(twi->dio,twi->TW_CLK)) == LOW);
  // SCL is high, set SDA from 0 to 1
  twi->dio->SetAsync(twi->dio,twi->TW_DAT,INPUT); // i think we need this but is it fast enough?
  if (DIOValue(twi->dio->GetAsync(twi->dio,twi->TW_DAT)) == LOW) {
    return TWIErrorArbLost;
  }
  twi->t->Delay(twi->t,twi->delay);
  twi->start = 0;
  return 0;
}
 
static int tx(DIOTWI *twi,unsigned char byte)
{
  unsigned bit;
  unsigned nack;
  int ret;

  for (bit = 0; bit < 8; bit++) {
    ret = write_bit(twi,byte & 0x80);
    if (ret < 0) return ret;
    byte <<= 1;
  }
  nack = read_bit(twi);
  return nack ? TWIErrorWriteNAck : 0;
}
 
static int rx (DIOTWI *twi,int nak)
{
  unsigned char byte = 0;
  unsigned bit;
  int ret;
 
  for (bit = 0; bit < 8; bit++) {
    byte <<= 1;		
    byte |= read_bit(twi);		
  }
  ret = write_bit(twi,nak);
  if (ret < 0) return ret;
  return byte;
}

//-----------------------------------------------------------------------------
void *DIOTWIInit(DIOTWI *twi,void *dio1,void *t1) {
  DIO *dio = dio1;
  Time *t = t1;

  if (twi->InitStatus > 0) return twi;

  twi->Init = (void *)DIOTWIInit;
  twi->Fini = (void *)DIOTWIFini;
  twi->Lock = (void *)DIOTWILock;
  twi->Unlock = (void *)DIOTWIUnlock;
  twi->Preempt = (void *)DIOTWIPreempt;
  twi->Write = (void *)DIOTWIWrite;
  twi->Read = (void *)DIOTWIRead;

  twi->LockNum = ThreadMutexAllocate(1);
  twi->dio = dio;
  twi->t= t;
  if (twi->Speed == 0) twi->Speed = 100000;
  twi->delay = 1000000/twi->Speed + (1000000%twi->Speed ? 1 : 0);

  if (twi->dio->InitStatus <= 0
      ||twi->t->InitStatus <= 0) {
    twi->Fini(twi);
    twi->InitStatus = -1;
    return twi;
  }

  twi->dio->SetAsync(twi->dio,twi->TW_CLK,INPUT); // SCL=1
  twi->dio->SetAsync(twi->dio,twi->TW_DAT,INPUT); // SDA=1
  usleep(10000); // ample time for them to become stable
  twi->InitStatus = 1;
  return twi;
}

void DIOTWIFini(DIOTWI *twi){
  twi->dio->Fini(twi->dio);
  twi->t->Fini(twi->t);
  if (twi->InitStatus > 0) twi->InitStatus = 0;
}

TWIResult DIOTWIWrite(DIOTWI *twi,int devadrs,int adrslen,int adrs,const char* bytes){
  int len = ArrayLength(bytes);
  int ret=0;

  // sending a start bit followed by the 7-bit address of the slave 
  // followed by 0 for write
  if (adrslen > 0) {
    if ((ret = START(twi)) < 0) {
      goto WriteDone;
    }
    if ((ret = tx(twi,devadrs << 1)) < 0) { // send address + WRITE
      goto WriteDone;
    }
    // send the address if it exists
    // the address must be such that the first byte to send is in the
    // LSB of the int, the second byte in the next byte up, and so forth,
    // from the perspective of accessing the int, independant of arch endianness
    while (adrslen > 0) {
      if ((ret = tx(twi,adrs&0xFF)) < 0) {
	goto WriteDone;
      }
      adrs >>= 8;
      adrslen--;
    }
  }
  // Now send the actual data
  while (len-- > 0) {
    if (tx(twi,*(bytes)++) < 0) {
      goto WriteDone;
    }
  }
  // Now send a stop bit
  if ((ret = STOP(twi)) < 0) {
    goto WriteDone;
  }
 WriteDone:
  return ret;
}

TWIResult DIOTWIRead(DIOTWI *twi,int devadrs,int adrslen,int adrs,char* bytes){
  int len = ArrayLength(bytes);
  int i,ret=0;

  if (adrslen > 0) {
    // sending a start bit followed by the 7-bit address of the slave 
    // followed by 0 for write
    if ((ret = START(twi)) < 0) {
      goto ReadDone;
    }
    if ((ret = tx(twi,devadrs << 1)) < 0) { // send address + WRITE
      goto ReadDone;
    }
    // send the address if it exists
    // the address must be such that the first byte to send is in the
    // LSB of the int, the second byte in the next byte up, and so forth,
    // from the perspective of accessing the int, independant of arch endianness
    while (adrslen > 0) {
      if ((ret = tx(twi,adrs&0xFF)) < 0) {
	goto ReadDone;
      }
      adrs >>= 8;
      adrslen--;
    }
  }
  // sending a start bit followed by the 7-bit address of the slave 
  // followed by 1 for read
  if ((ret = START(twi)) < 0) {
    goto ReadDone;
  }
  if ((ret = tx(twi,(devadrs << 1)+1)) < 0) { // send address + READ
    goto ReadDone;
  }
// Now read the actual data
  for (i=0;i<len;i++) {
    ret = rx(twi,i == len-1);
    if (ret < 0) {
      goto ReadDone;
    }
    bytes[i] = ret;
  }
  // Now send a stop bit
  if ((ret = STOP(twi)) < 0) {
    goto ReadDone;
  }
 ReadDone:
  return ret;
}

int DIOTWILock(DIOTWI *twi,unsigned num,int flags) {
  int ret,mode;

  if (flags & SHARED) return -11;
  mode = (flags & NONBLOCKING) ? 
    LOCK_TRY :
    (flags & NOUNLOCK) ? LOCK_FOD : LOCK_SOD;
  if ((ret=ThreadMutexLock(twi->LockNum,mode)) < 0) return ret;
  if ((ret=twi->dio->Lock(twi->dio,twi->TW_CLK,0)) < 0) {
    goto DoRelease2;
  }
  if ((ret=twi->dio->Lock(twi->dio,twi->TW_DAT,0)) < 0) {
    goto DoRelease1;
  }
  return 1;
 DoRelease:
   twi->dio->Unlock(twi->dio,twi->TW_DAT,0);
 DoRelease1:
   twi->dio->Unlock(twi->dio,twi->TW_CLK,0);
 DoRelease2:
   ThreadMutexUnlock(twi->LockNum); // TWI mutex
   return ret;
}

int DIOTWIUnlock(DIOTWI *twi,unsigned num,int flags) {
  twi->dio->Unlock(twi->dio,twi->TW_CLK,0);
  twi->dio->Unlock(twi->dio,twi->TW_DAT,0);
  return ThreadMutexUnlock(twi->LockNum);
}

int DIOTWIPreempt(DIOTWI *twi) {
}

// Author: Michael Schmidt (michael@embeddedARM.com)
// Copyright (c) 2011, Technologic Systems, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
#endif
