#include "ts8820DACAIO.h"

System *SystemInit(int);

void *ts8820DACAIOInit(ts8820DACAIO *aio,Bus *bus) {
  if (aio->InitStatus > 0) return aio;
  aio->InitStatus = 1;
  aio->Init = (void *)ts8820DACAIOInit;
  aio->Fini = (void *)ts8820DACAIOFini;
  aio->Lock = (void *)ts8820DACAIOLock;
  aio->Unlock = (void *)ts8820DACAIOUnlock;
  aio->Preempt = (void *)ts8820DACAIOPreempt;
  aio->Type = (void *)ts8820DACAIOType;
  aio->VoltageRangeList = (void *)ts8820DACAIOVoltageRangeList;
  aio->PrecisionList = (void *)ts8820DACAIOPrecisionList;
  aio->PeriodRangeList = (void *)ts8820DACAIOPeriodRangeList;
  aio->TriggerList = (void *)ts8820DACAIOTriggerList;
  aio->Channels = (void *)ts8820DACAIOChannels;
  aio->Configuration = (void *)ts8820DACAIOConfiguration;
  aio->ConfigureTest = (void *)ts8820DACAIOConfigureTest;
  aio->Configure = (void *)ts8820DACAIOConfigure;
  aio->Get = (void *)ts8820DACAIOGet;
  aio->Put = (void *)ts8820DACAIOPut;
  aio->Ready = (void *)ts8820DACAIOReady;
  aio->Gets8 = (void *)ts8820DACAIOGets8;
  aio->Gets16 = (void *)ts8820DACAIOGets16;
  aio->Gets32 = (void *)ts8820DACAIOGets32;
  aio->Puts8 = (void *)ts8820DACAIOPuts8;
  aio->Puts16 = (void *)ts8820DACAIOPuts16;
  aio->Puts32 = (void *)ts8820DACAIOPuts32;
  aio->Readys8 = (void *)ts8820DACAIOReadys8;
  aio->Readys16 = (void *)ts8820DACAIOReadys16;
  aio->Readys32 = (void *)ts8820DACAIOReadys32;

  aio->bus = bus;
  System *sys = SystemInit(0);

  aio->bus->Lock(aio->bus,0,0);
  aio->bus->BitClear16(aio->bus,0x82,5); // make sure we aren't in standby
  aio->bus->BitClear16(aio->bus,0x82,4);
  aio->bus->Unlock(aio->bus,0,0);

  return aio;
}
                                                    
void ts8820DACAIOFini(ts8820DACAIO *aio) {
}
                                                   
int ts8820DACAIOLock(ts8820DACAIO *aio,unsigned num,int flags) {
}
                           
int ts8820DACAIOUnlock(void *me,unsigned num,int flags) {
}
int ts8820DACAIOPreempt(void *me) {
}

                           
AIOType ts8820DACAIOType(ts8820DACAIO *aio) {
  return AIO_DAC;
}
                                                 
VoltageRange* ts8820DACAIOVoltageRangeList(ts8820DACAIO *aio) {
  VoltageRange* r = ArrayAlloc(1,sizeof(VoltageRange));

  r[0] = AIO_VR(0.0,0.0,0,10.0,0.0,0);
  return r;
}

int ts8820DACAIOPrecisionList(ts8820DACAIO *aio) {
  return (1<<12);
}

PeriodRange* ts8820DACAIOPeriodRangeList(ts8820DACAIO *aio){
  PeriodRange* r = ArrayAlloc(2,sizeof(PeriodRange));

  r[0] = AIO_PR(3000,1,0);
  r[1] = AIO_PR(0,0,0);
  return r;
}

int* ts8820DACAIOTriggerList(ts8820DACAIO *aio) {
  int* tlist = ArrayAlloc(0,sizeof(int));
  return tlist;
}
                                   
int ts8820DACAIOChannels(ts8820DACAIO *aio) {
  return 4;
}

// this returns the current configuration           
int ts8820DACAIOConfiguration(ts8820DACAIO *aio,float* low,float* high,int* prec,int* t,int* trigger,int itrig[1]) {
  int i,r1,r2;
  unsigned ns;

  for (i=0;i<4;i++) {
    low[i] = 0.0;
    high[i] = 10.0;
    prec[i] = 12;
    t[i] = 3000;
    trigger[i] = 0;
  }
  itrig[0] = 0;
  return 1;
}

// tests whether a new configuration is valid
int ts8820DACAIOConfigureTest(ts8820DACAIO *aio,const float* low,const float* high,const int* prec,const int* t,const int* trigger,int itrig) {
  int i;

  if (ArrayLength(low) != 4) return -100;  // bad count
  if (ArrayLength(high) != 4) return -100;  // bad count
  if (ArrayLength(prec) != 4) return -100;  // bad count
  if (ArrayLength(t) != 4) return -100;  // bad count
  if (ArrayLength(trigger) != 4) return -100;  // bad count
  if (itrig != 0) return -50; // bad itrig

  if (low[0] != 0.0) return -10; // bad voltage range
  if (high[0] != 10.0) return -10; // bad voltage range
  for (i=1;i<4;i++) {
    if (low[i] != low[0]) return -10-i; // bad voltage range
    if (high[i] != high[0]) return -10-i; // bad voltage range
  }
  for (i=0;i<4;i++) {
    if (trigger[i] != 0) return -60-i; // bad trigger
    if (prec[i] != 12) return -30-i; // bad precision
  }
  if (t[0] != 3000) return -20;
  for (i=1;i<4;i++) {
    if (t[i] != t[0]) {
      return -20-i; // invalid period
    }
  }
  return 1;
}

// TO DO: allow channels to be disabled.  how do we denote this?
// no voltage range?  no sampling period?
// configures
int ts8820DACAIOConfigure(ts8820DACAIO *aio,const float* low,const float* high,const int* prec,const int* t,const int* trigger,int itrig) {
  int ret,dns;

  if ((ret=ts8820DACAIOConfigureTest(aio,low,high,prec,t,trigger,itrig)<0)) {
    return ret;
  }  
  return 1;
}
 
int ts8820DACAIOITrig(ts8820DACAIO *aio,int itrig) {
  return (itrig == 0) ? 1 : -1;
}

int ts8820DACAIOGet(ts8820DACAIO *aio,int ch) {
  int val;

  if (ch < 0 || ch > 3) return -1;
  // read back the last value we Put
  aio->bus->Lock(aio->bus,0,0);
  val = aio->bus->Peek16(aio->bus,0xa0+2*ch) & 0xFFF;
  aio->bus->Unlock(aio->bus,0,0);

  return val;
}
                                          
int ts8820DACAIOPut(ts8820DACAIO *aio,int ch,int value) {
  unsigned wait = 65000;

  if (ch < 0 || ch > 3) return -1;
  value = 0x8000 + (value & 0xFFF);
  aio->bus->Lock(aio->bus,0,0);
  while (aio->bus->BitGet16(aio->bus,0xa0,15) && --wait > 0);
  if (wait < 0) return -10;
  aio->bus->Poke16(aio->bus,0xa0+2*ch,value);
  aio->bus->Unlock(aio->bus,0,0);
  return 1;
}
                                
int ts8820DACAIOReady(ts8820DACAIO *aio,int ch) {
  return -1;
}
                 
int ts8820DACAIOGets8(ts8820DACAIO *aio,char* buf){
  return -1;
}

int ts8820DACAIOGets16(ts8820DACAIO *aio,short* buf){
  return -1;
}

int ts8820DACAIOGets32(ts8820DACAIO *aio,int* buf){
  return -1;
}

int ts8820DACAIOPuts8(ts8820DACAIO *aio,const char* buf){
  return -1;
}

int ts8820DACAIOPuts16(ts8820DACAIO *aio,const short* buf){
  return -1;
}

int ts8820DACAIOPuts32(ts8820DACAIO *aio,const int* buf){
  return -1;
}

int ts8820DACAIOReadys8(ts8820DACAIO *aio,char* buf){
  return -1;
}

int ts8820DACAIOReadys16(ts8820DACAIO *aio,short* buf){
  return -1;
}

int ts8820DACAIOReadys32(ts8820DACAIO *aio,int* buf){
  return -1;
}

                       
