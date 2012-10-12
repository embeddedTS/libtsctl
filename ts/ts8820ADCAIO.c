#include "ts8820ADCAIO.h"

/*
tsctl Mode Hex \; Bus:2 BitClear16 0x82 1 \; Bus:2 BitSet16 0x82 0 ; Bus:2 BitClear16 0x82 0 \; Bus:2 Peek16 0x82
tsctl AIO Gets16 100                                               

We aren't necessarily reading the right index with Get in all cases.

4. we probably hold the bus too long and should preempt it periodically
however we also don't implement AIO locking, which we should do.

 */

System *SystemInit(int);

void *ts8820ADCAIOInit(ts8820ADCAIO *aio,Bus *bus) {
  int i;

  if (aio->InitStatus > 0) return aio;
  aio->InitStatus = 1;
  aio->Init = (void *)ts8820ADCAIOInit;
  aio->Fini = (void *)ts8820ADCAIOFini;
  aio->Lock = (void *)ts8820ADCAIOLock;
  aio->Unlock = (void *)ts8820ADCAIOUnlock;
  aio->Preempt = (void *)ts8820ADCAIOPreempt;
  aio->Type = (void *)ts8820ADCAIOType;
  aio->VoltageRangeList = (void *)ts8820ADCAIOVoltageRangeList;
  aio->PrecisionList = (void *)ts8820ADCAIOPrecisionList;
  aio->PeriodRangeList = (void *)ts8820ADCAIOPeriodRangeList;
  aio->TriggerList = (void *)ts8820ADCAIOTriggerList;
  aio->Channels = (void *)ts8820ADCAIOChannels;
  aio->Reset = (void *)ts8820ADCAIOReset;
  aio->ChannelEnable = (void *)ts8820ADCAIOChannelEnable;
  aio->ChannelSamplePeriod = (void *)ts8820ADCAIOChannelSamplePeriod;
  aio->ChannelPrecision = (void *)ts8820ADCAIOChannelPrecision;
  aio->ChannelVoltageRange = (void *)ts8820ADCAIOChannelVoltageRange;
  aio->Configuration = (void *)ts8820ADCAIOConfiguration;
  aio->ConfigureTest = (void *)ts8820ADCAIOConfigureTest;
  aio->Configure = (void *)ts8820ADCAIOConfigure;
  aio->Get = (void *)ts8820ADCAIOGet;
  aio->Put = (void *)ts8820ADCAIOPut;
  aio->Ready = (void *)ts8820ADCAIOReady;
  aio->Gets8 = (void *)ts8820ADCAIOGets8;
  aio->Gets16 = (void *)ts8820ADCAIOGets16;
  aio->Gets32 = (void *)ts8820ADCAIOGets32;
  aio->Puts8 = (void *)ts8820ADCAIOPuts8;
  aio->Puts16 = (void *)ts8820ADCAIOPuts16;
  aio->Puts32 = (void *)ts8820ADCAIOPuts32;
  aio->Readys8 = (void *)ts8820ADCAIOReadys8;
  aio->Readys16 = (void *)ts8820ADCAIOReadys16;
  aio->Readys32 = (void *)ts8820ADCAIOReadys32;

  aio->bus = bus;
  System *sys = SystemInit(0);
  aio->dio = DIOInit(0);
  aio->CN2_56 = sys->MapLookup(sys,ASCIIZLocal("CN2_56"));
  aio->CN2_58 = sys->MapLookup(sys,ASCIIZLocal("CN2_58"));
  aio->CN2_60 = sys->MapLookup(sys,ASCIIZLocal("CN2_60"));
  aio->CN2_62 = sys->MapLookup(sys,ASCIIZLocal("CN2_62"));
  aio->CN2_64 = sys->MapLookup(sys,ASCIIZLocal("CN2_64"));

  aio->mask = aio->n = 0;

  aio->dio->Lock(aio->dio,aio->CN2_60,0);
  aio->dio->SetAsync(aio->dio,aio->CN2_60,LOW);
  aio->dio->Unlock(aio->dio,aio->CN2_60,0);
  aio->dio->Lock(aio->dio,aio->CN2_62,0);
  aio->dio->SetAsync(aio->dio,aio->CN2_62,LOW);
  aio->dio->Unlock(aio->dio,aio->CN2_62,0);
  aio->dio->Lock(aio->dio,aio->CN2_64,0);
  aio->dio->SetAsync(aio->dio,aio->CN2_64,LOW);
  aio->dio->Unlock(aio->dio,aio->CN2_64,0);

  // SetAsync CN2_60 LOW
  // SetAsync CN2_62 LOW
  // SetAsync CN2_64 LOW
  aio->bus->Lock(aio->bus,0,0);
  aio->bus->BitClear16(aio->bus,0x82,5); // make sure we aren't in standby
  aio->bus->BitClear16(aio->bus,0x82,4);
  aio->bus->Unlock(aio->bus,0,0);

  for (i=0;i<16;i++) {
    aio->period[i] = 0;
    aio->prec[i] = 0;
    aio->low[i] = aio->high[i] = 0;
  }
  return aio;
}
                                                    
void ts8820ADCAIOFini(ts8820ADCAIO *aio) {
}
                                                   
int ts8820ADCAIOLock(ts8820ADCAIO *aio,unsigned num,int flags) {
}
                           
int ts8820ADCAIOUnlock(ts8820ADCAIO *me,unsigned num,int flags) {
}
int ts8820ADCAIOPreempt(ts8820ADCAIO *me) {
}

AIOType ts8820ADCAIOType(ts8820ADCAIO *aio) {
  return AIO_ADC;
}
                                                 
VoltageRange* ts8820ADCAIOVoltageRangeList(ts8820ADCAIO *aio) {
  VoltageRange* r = ArrayAlloc(2,sizeof(VoltageRange));

  r[0] = AIO_VR(-10.0,0.0,0,10.0,0.0,0);
  r[1] = AIO_VR(-5.0,0.0,0,5.0,0.0,0);
  return r;
}

int ts8820ADCAIOPrecisionList(ts8820ADCAIO *aio) {
  return (1<<16);
}

PeriodRange* ts8820ADCAIOPeriodRangeList(ts8820ADCAIO *aio){
  PeriodRange* r = ArrayAlloc(2,sizeof(PeriodRange));

  r[0] = AIO_PR(10000,10,0xFFFFFFFF);
  r[1] = AIO_PR(0,0,0);
  return r;
}

int* ts8820ADCAIOTriggerList(ts8820ADCAIO *aio) {
  int* tlist = ArrayAlloc(0,sizeof(int));
  return tlist;
}
                                   
int ts8820ADCAIOChannels(ts8820ADCAIO *aio) {
  return 16;
}

// this returns the current configuration           
int ts8820ADCAIOConfiguration(ts8820ADCAIO *aio,float* low,float* high,int* prec,int* t,int* trigger,int itrig[1]) {
  int i,r1,r2,mask,uu;
  unsigned ns;

  aio->dio->Lock(aio->dio,aio->CN2_56,SHARED);
  r1 = aio->dio->GetAsync(aio->dio,aio->CN2_56);
  aio->dio->Unlock(aio->dio,aio->CN2_56,SHARED);

  aio->dio->Lock(aio->dio,aio->CN2_58,SHARED);
  r2 = aio->dio->GetAsync(aio->dio,aio->CN2_58);
  aio->dio->Unlock(aio->dio,aio->CN2_58,SHARED);

  aio->bus->Lock(aio->bus,0,SHARED);
  ns=aio->bus->Peek16(aio->bus,0x88) + (aio->bus->Peek16(aio->bus,0x8a)<<16);
  ns = 10 * ns;
  mask = aio->bus->BitsGet16(aio->bus,0x82,15,8);
  uu = aio->bus->BitsGet16(aio->bus,0x82,7,6);
  aio->bus->Unlock(aio->bus,0,SHARED);
  for (i=0;i<16;i++) {
    if (i < 8) {
      low[i] = r1 ? -10.0 : -5.0;
      high[i] = r1 ? 10.0 : 5.0;
    } else {
      low[i] = r2 ? -10.0 : -5.0;
      high[i] = r2 ? 10.0 : 5.0;
    }
    prec[i] = 16;
    trigger[i] = 0;
    itrig[0] = 0;
  }
  for (i=0;i<8;i++) {
    t[i] = (mask & 1) ? ns : 0;
    t[i+8] = (t[i] && uu) ? ns : 0;
    mask >>= 1;
  }
  return 1;
}

// tests whether a new configuration is valid
int ts8820ADCAIOConfigureTest(ts8820ADCAIO *aio,const float* low,const float* high,const int* prec,const int* t,const int* trigger,int itrig) {
  int i,n;

  if (ArrayLength(low) != 16) return -100; // bad count
  if (ArrayLength(high) != 16) return -100; // bad count
  if (ArrayLength(prec) != 16) return -100; // bad count
  if (ArrayLength(t) != 16) return -100; // bad count
  if (ArrayLength(trigger) != 16) return -100; // bad count
  if (itrig != 0) return -50; // bad itrig
  if (low[0] != -10.0 && low[0] != -5.0) return -10-i; // bad voltage range
  if (high[0] != -low[0]) return -10-i; // bad voltage range
  for (i=1;i<8;i++) {
    if (low[i] != low[0]) return -10-i; // bad voltage range
    if (high[i] != high[0]) return -10-i; // bad voltage range
  }
  if (low[8] != -10.0 && low[8] != -5.0) return -10-i; // bad voltage range
  if (high[8] != -low[8]) return -10-i; // bad voltage range
  for (i=9;i<16;i++) {
    if (low[i] != low[8]) return -10-i; // bad voltage range
    if (high[i] != high[8]) return -10-i; // bad voltage range
  }
  for (i=0;i<16;i++) {
    if (trigger[i] != 0) return -60-i; // bad trigger
    if (prec[i] != 16) return -30-i; // bad precision
  }
  if (t[0] != 0 && t[0] < 10000) return -20-i;
  n=0;
  for (i=1;i<8;i++) { // first 8 channels must be disabled or same period
    if (!n && t[i] != 0) n = t[i];
    if (t[i] != n && t[i] != 0) {
      return -20-i; // invalid period
    }
  }
  for (i=8;i<16;i++) {
    if (t[i]) break;
  }
  if (i < 16) { // all upper channels are not disabled
    for (i=8;i<16;i++) { // top 8 channels must match first 8, respectively
      if (t[i] != t[i-8]) {
	return -20-i; // invalid period
      }
    }
  }
  return 1;
}

void ts8820ADCAIOCalc(ts8820ADCAIO *aio,const int* t) {
  static int hw2sw[16]={0, 4, 8, 12, 2, 6, 10, 14, 1, 5, 9, 13, 3, 7, 11, 15};
  int i, ord[16], ord2[16];

  int compare(const void *a,const void *b) {
    const int *a1 = a, *b1 = b;
    return *a1 - *b1;
  }
  int pos(int val,int *arr) {
    int i=0;
    while (arr[i] != val) i++;
    return i;
  }

  if (t) {
    aio->mask = aio->n = 0;
    for (i=0;i<8;i++) {
      aio->mask >>= 1;
      if (t[i]) aio->mask |= 0x200; // highest numbered chip to use in 2 LSB
    }
    for (i=8;i<16;i++) if (t[i]) break;
    if (i < 16) aio->mask |= 1; // enable second chip
  } else {
    aio->mask = aio->bus->BitsGet16(aio->bus,0x82,15,6);
  }

  for (i=0;i<8;i++) {
    if (aio->mask & (1 << (2+i))) {
      ord[aio->n] = ord2[aio->n] = hw2sw[i];
      aio->n++;
    }
  }
  for (i=8;i<16;i++) {
    if (aio->mask & (1 << (2+i-8))) {
      ord[aio->n] = ord2[aio->n] = hw2sw[i];
      aio->n++;
    }
  }
  qsort(ord,aio->n,sizeof(int),compare);
  //fprintf(stderr,"%d\n",aio->n);
  for (i=0;i<aio->n;i++) {
    aio->ord[i] = pos(ord[i],ord2);
    //fprintf(stderr,"%d ",aio->ord[i]);
  }
  //fprintf(stderr,"\n");


}

void ts8820ADCAIOReset(ts8820ADCAIO *aio) {
  ArrayAuto(float,low,ARR(-10.0,-10.0,-10.0,-10.0,-10.0,-10.0,-10.0,-10.0,
			  -10.0,-10.0,-10.0,-10.0,-10.0,-10.0,-10.0,-10.0));
  ArrayAuto(float,high,ARR(10.0,10.0,10.0,10.0,10.0,10.0,10.0,10.0,
			  10.0,10.0,10.0,10.0,10.0,10.0,10.0,10.0));
  ArrayAuto(int,prec,ARR(16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16));
  ArrayAuto(int,t,ARR(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0));
  int i;

  for (i=0;i<16;i++) {
    aio->period[i] = 0;
    aio->prec[i] = 0;
    aio->low[i] = aio->high[i] = 0;
  }
  aio->Configure(aio,low,high,prec,t,t,0);
}

int ts8820ADCAIOChannelEnable(ts8820ADCAIO *aio,int ch,int flag) {
  ArrayAutoOfSize(float,low,16);
  ArrayAutoOfSize(float,high,16);
  ArrayAutoOfSize(int,prec,16);
  ArrayAutoOfSize(int,t,16);
  ArrayAutoOfSize(int,trigger,16);
  int i,itrig,t1=0,prec1=0;
  float low1=-10.0,high1=10.0;

  if (ch < 0 || ch > 15) return -1;
  aio->Configuration(aio,low,high,prec,t,trigger,&itrig);
  if (aio->period[ch]) {
    t1 = aio->period[ch];
  } else for (i=0;i<16;i++) {
      if (t[i]) {
	t1 = t[i];
	break;
      }
    }
  if (!t1) {
    t1 = 10000;
  }
  t[ch] = t1;

  // precision
  if (aio->prec[ch]) {
    prec1 = aio->prec[ch];
  } else for (i=0;i<16;i++) {
      if (t[i]) {
	prec1 = prec[i];
	break;
      }
    }
  if (prec1) {
    prec1 = 16;
  }
  prec[ch] = t1;
  
  // voltage range
  if (aio->low[ch] != 0.0 || aio->high[ch] != 0.0) {
    low1 = aio->low[i];
    high1 = aio->high[i];
  } else for (i=0;i<16;i++) {
      if (t[i]) {
	low1 = low[i];
	high1 = high[i];
	break;
      }
    }
  low[ch] = low1;
  high[ch] = high1;

  return aio->Configure(aio,low,high,prec,t,trigger,0);
}

unsigned ts8820ADCAIOChannelSamplePeriod(ts8820ADCAIO *aio,int ch,unsigned ns) {
  ArrayAutoOfSize(float,low,16);
  ArrayAutoOfSize(float,high,16);
  ArrayAutoOfSize(int,prec,16);
  ArrayAutoOfSize(int,t,16);
  ArrayAutoOfSize(int,trigger,16);
  int i,itrig;
  if (ch < 0 || ch > 15) return 0;

  aio->Configuration(aio,low,high,prec,t,trigger,&itrig);
  if (!ns) {
    return t[ch];
  }
  if (t[ch]) { // channel ch is enabled
    t[ch] = ns;
    return (aio->Configure(aio,low,high,prec,t,trigger,0) < 0) ? 0 : ns;
  } else {
    aio->period[ch] = ns;
    // if any channel is already enabled, the default value must be whatever
    // period the currently enabled channel is at.  otherwise, we will use
    // whateve was just set.  this means that for this module, a return
    // value different from what was set is a hint that the subsequent enable
    // will fail unless the differing channel is first changed.
    for (i=0;i<16;i++) {
      if (t[i]) return t[i];
    }
    return 10000;
  }
}

int ts8820ADCAIOChannelPrecision(ts8820ADCAIO *aio,int ch,int prec1) {
  ArrayAutoOfSize(float,low,16);
  ArrayAutoOfSize(float,high,16);
  ArrayAutoOfSize(int,prec,16);
  ArrayAutoOfSize(int,t,16);
  ArrayAutoOfSize(int,trigger,16);
  int i,itrig;
  if (ch < 0 || ch > 15) return 0;

  aio->Configuration(aio,low,high,prec,t,trigger,&itrig);
  if (!prec1) {
    return prec[ch];
  }
  if (t[ch]) { // channel ch is enabled
    prec[ch] = prec1;
    return (aio->Configure(aio,low,high,prec,t,trigger,0) < 0) ? 0 : prec1;
  } else {
    aio->prec[ch] = prec1;
    return 16;
  }
}

int ts8820ADCAIOChannelVoltageRange(ts8820ADCAIO *aio,int ch,
				    float low1,float high1) {
  ArrayAutoOfSize(float,low,16);
  ArrayAutoOfSize(float,high,16);
  ArrayAutoOfSize(int,prec,16);
  ArrayAutoOfSize(int,t,16);
  ArrayAutoOfSize(int,trigger,16);
  int i,itrig;
  if (ch < 0 || ch > 15) return 0;

  aio->Configuration(aio,low,high,prec,t,trigger,&itrig);

  if (t[ch]) { // channel ch is enabled
    low[ch] = low1;
    high[ch] = high1;
    return aio->Configure(aio,low,high,prec,t,trigger,0);
  } else {
    aio->low[ch] = low1;
    aio->high[ch] = high1;
    return 1;
  }
  
}

int ts8820ADCAIOConfigure(ts8820ADCAIO *aio,const float* low,const float* high,const int* prec,const int* t,const int* trigger,int itrig) {
  int ret,ns;

  if ((ret=ts8820ADCAIOConfigureTest(aio,low,high,prec,t,trigger,itrig))<0) {
    return ret;
  }  
  ts8820ADCAIOCalc(aio,t);

  aio->bus->Lock(aio->bus,0,0);
  aio->bus->Assign16X(aio->bus,0x82,15,6,aio->mask); // set mask and max chip
  aio->bus->BitClear16(aio->bus,0x82,5); // disable force standby
  aio->bus->BitClear16(aio->bus,0x82,4); // disable standby
  aio->bus->BitClear16(aio->bus,0x82,1); // disable collection
  aio->bus->BitSet16(aio->bus,0x82,0); // enter reset
  usleep(10000);
  aio->bus->BitClear16(aio->bus,0x82,0); // leave reset
  aio->bus->Unlock(aio->bus,0,0);

  aio->dio->Lock(aio->dio,aio->CN2_56,0);
  if (low[0] == -10.0) { // -10.0V to +10.0V
    aio->dio->SetAsync(aio->dio,aio->CN2_56,HIGH);
  } else { // -5.0V to +5.0V
    aio->dio->SetAsync(aio->dio,aio->CN2_56,LOW);
  }
  aio->dio->Unlock(aio->dio,aio->CN2_56,0);

  aio->dio->Lock(aio->dio,aio->CN2_58,0);
  if (low[8] == -10.0) { // -10.0V to +10.0V
    aio->dio->SetAsync(aio->dio,aio->CN2_58,HIGH);
  } else { // -5.0V to +5.0V
    aio->dio->SetAsync(aio->dio,aio->CN2_58,LOW);
  }
  aio->dio->Unlock(aio->dio,aio->CN2_58,0);

  ns = t[0] / 10;
  aio->bus->Lock(aio->bus,0,0);
  aio->bus->Poke16(aio->bus,0x88,ns&0xFFFF);
  aio->bus->Poke16(aio->bus,0x8a,ns>>16);
  aio->bus->Unlock(aio->bus,0,0);

  return 1;
}
 
int ts8820ADCAIOITrig(ts8820ADCAIO *aio,int itrig) {
  return (itrig == 0) ? 1 : -1;
}

// wait for at least n samples to be available, then return
// returns actual number of samples available
// assumes:
// aio->bus lock held
// n is not larger than the number of samples that can be available
//
// notes:
// hmm, is there a way to determine if we have stopped collecting?
// if we have an overflow, we need to be able to call this function
// and have it return an error if we can't get any more data because
// we overflowed, then read off enough data that we can no longer
// get n elements.
static inline int ts8820ADCWait4(ts8820ADCAIO *aio,int n) {
  int count;
  
  count = aio->bus->Peek16(aio->bus,0x84);
  if ((count&0x7FFF) < n && (count&0x8000)) {
    return -1; // overflow with insufficient data left to drain
  }
  count &= 0x7FFF;
  while (count < n) {
    count = aio->bus->Peek16(aio->bus,0x84);
  }
  return count;
}

// get a line of samples from the ADC, where a line is one sample
// for each enabled channel
// assume aio->n channels are enabled
// assume length of buf is aio->n elements
// this function is needed because the ordering of the samples as
// read from the FIFO is out of order.
// this function re-orders them correctly.
// it also rejects any partial line on overflow, since in most
// cases we would miss intervening samples.
// if samples not available, polls until they are
// assumes:
// collect is set
// aio->ord contains order of channels
// aio->n contains number of channels enabled
// aio->bus lock held
static int ts8820ADCLineGet16(ts8820ADCAIO *aio,short *buf) {
  int i,count = ts8820ADCWait4(aio,aio->n);
  if (count < 0) return -1; // can't get line due to overflow

  for (i=0;i<aio->n;i++) {
    buf[aio->ord[i]] = aio->bus->Peek16(aio->bus,0x86);
    //printf("%d:%d:%04X\n",i,aio->ord[i],buf[aio->ord[i]]);
  }
  return 1;
}

/*
1. Get should work better with Gets, specifically dealing with the fact
that Gets may leave collect enabled whereas Get always resets the chip
before sampling.  it should instead only enable and/or reset if needed.

algorithm:

set the collect bit in case we haven't started acquiring
while 1
  wait for samples
  step through channels until we run out or read the requested channel

 */
int ts8820ADCAIOGet(ts8820ADCAIO *aio,int ch) {
  short val;
  int done=0,n,subch = (ch > 7) ? ch-8 : ch, oldmask;

  if (ch < 0 || ch >= 16) return -1; // invalid channel

  // the AIO API requires that when using trigger 0, Get initiates
  // a conversion and returns what is now the most recent sample.
  // However, Gets leaves conversion running.  Therefore if we are
  // currently acquiring, we must switch from Gets mode to Get mode
  // by disabling acquisition and resetting the FIFO before starting
  // a new acquisition.  This can be costly in terms of time used,
  // depending on how long we really need to wait for the reset to
  // complete.
  aio->bus->Lock(aio->bus,0,0);
  oldmask = aio->bus->BitsGet16(aio->bus,0x82,15,6);
  if (aio->bus->BitGet16(aio->bus,0x82,1)) { // currently acquiring
    aio->bus->BitClear16(aio->bus,0x82,1); // stop
    aio->bus->BitSet16(aio->bus,0x82,0); // reset ADC/FIFO
    aio->bus->BitClear16(aio->bus,0x82,0); // take ADC/FIFO out of reset
  }
  // enable channel we want. if it is on second chip, we can't avoid
  // sampling the first chip's corresponding channel first
  aio->bus->Assign16X(aio->bus,0x82,15,8,(1<<subch));
  aio->bus->Assign16X(aio->bus,0x82,7,6,ch > 7 ? 1 : 0);
  // start collecting samples
  aio->bus->BitSet16(aio->bus,0x82,1);
  aio->bus->Unlock(aio->bus,0,0);
  while (!done) {
    aio->bus->Lock(aio->bus,0,0);
    n = aio->bus->BitsGet16(aio->bus,0x84,14,0);
    if (n > (ch > 7 ? 1 : 0)) {
      done = 1;
      val = aio->bus->Peek16(aio->bus,0x86);
      //aio->next++; if (aio->next >= aio->count) aio->next = 0;
      aio->bus->BitClear16(aio->bus,0x82,1); // stop
      if (ch > 7) val = aio->bus->Peek16(aio->bus,0x86);
      aio->bus->BitSet16(aio->bus,0x82,0); // reset ADC/FIFO
      aio->bus->BitClear16(aio->bus,0x82,0); // take ADC/FIFO out of reset
    }
    aio->bus->Unlock(aio->bus,0,0);
  }
  aio->bus->Lock(aio->bus,0,0);
  aio->bus->Assign16X(aio->bus,0x82,15,6,oldmask);
  aio->bus->Unlock(aio->bus,0,0);
  return val;
}
                                          
int ts8820ADCAIOPut(ts8820ADCAIO *aio,int ch,int value) {
  return -1; // invalid function
}
                                
int ts8820ADCAIOReady(ts8820ADCAIO *aio,int ch) {
  return -1;
}
                 
int ts8820ADCAIOGets8(ts8820ADCAIO *aio,char* buf){
  return -1;
}

int ts8820ADCAIOGets16(ts8820ADCAIO *aio,short* buf){
  int i,count,samples=0;
  short *buf1 = buf;

  count = ArrayLength(buf);

  aio->bus->Lock(aio->bus,0,0);
  if (aio->n == 0 && aio->mask == 0) {
    // this allows separate invocations of tsctl to configure and then
    // Gets data
    ts8820ADCAIOCalc(aio,0);
  }
  // To support, "trigger 1", which would start a new acquisition every time
  // we call this function, we must first throw away the results of any
  // previously started acquisition.
  // This is simple if we have even a single bit of storage that we can look
  // at to determine whether or not we are using trigger 1.  But the problem
  // is, how can we retain a single bit dedicated to that purpose across
  // tsctl invocations.  A scratch register would be ideal.
  // I reject a temp file or misappropriating the SRAM page register as
  // unacceptable.
  // It might be possible to force it by means of the comparison against
  // the AIO mask, only I can't figure out a way to make it work.
  // The thing is, we can tell when we need to calculate the mask, but
  // we calculate it from the inferred mask state from the ADC registers.
  // but since we can get a single sample, why can't we leave it in a state
  // as if we just got only a single sample?
  // the problem is, Get does the reverse of this.  It temporarily puts
  // the ADC into single channel mode, then restores it when the sample
  // has been taken.
  // Okay then, what about the collect bit?  Why can't we just shut
  // off the collect bit after we get the requested number of samples?
  // this would work, but how do we know to do this???  the thing is,
  // we can't use this flag on entry.
#if 0
  if (aio->bus->BitGet16(aio->bus,0x82,1)) { // currently acquiring
    aio->bus->BitClear16(aio->bus,0x82,1); // stop
    aio->bus->BitSet16(aio->bus,0x82,0); // reset ADC/FIFO
    aio->bus->BitClear16(aio->bus,0x82,0); // take ADC/FIFO out of reset
  }
#endif
  if (aio->bus->BitsGet16(aio->bus,0x82,15,6) != aio->mask) {
    // if Get is called, then it changes to a single bit set mask
    // if that is the case, then we have to re-configure back to our
    // all channel mask.  This means there will be a delay before we
    // start.  If this cannot be tolerated, then don't call Get
    // after Configure and before Gets.
    aio->bus->Assign16X(aio->bus,0x82,15,6,aio->mask); // set mask, max chip
    aio->bus->BitClear16(aio->bus,0x82,1); // disable collection
    aio->bus->BitSet16(aio->bus,0x82,0); // reset ADC/FIFO
    usleep(10000);
    aio->bus->BitClear16(aio->bus,0x82,0); // take ADC/FIFO out of reset
    usleep(10000);
  }
  aio->bus->BitSet16(aio->bus,0x82,1); // collect, if not already
  while (count >= aio->n) {
    if (ts8820ADCLineGet16(aio,buf1)<0) { // overflow w/ no more data to read
      aio->bus->BitClear16(aio->bus,0x82,1); // stop
      aio->bus->BitSet16(aio->bus,0x82,0); // reset
      usleep(10000);
      aio->bus->BitClear16(aio->bus,0x82,0); // end reset
      usleep(10000);
      if (samples == 0) return -37;
      ArraySizeAuto(buf,samples);
      break;
    }
    buf1 += aio->n;
    count -= aio->n;
    samples += aio->n;
  }
  aio->bus->Unlock(aio->bus,0,0);
  return samples;
}

int ts8820ADCAIOGets32(ts8820ADCAIO *aio,int* buf){
  return -1;
}

int ts8820ADCAIOPuts8(ts8820ADCAIO *aio,const char* buf){
  return -1;
}

int ts8820ADCAIOPuts16(ts8820ADCAIO *aio,const short* buf){
  return -1;
}

int ts8820ADCAIOPuts32(ts8820ADCAIO *aio,const int* buf){
  return -1;
}

int ts8820ADCAIOReadys8(ts8820ADCAIO *aio,const char* buf){
  return -1;
}

int ts8820ADCAIOReadys16(ts8820ADCAIO *aio,const short* buf){
  return -1;
}

int ts8820ADCAIOReadys32(ts8820ADCAIO *aio,const int* buf){
  return -1;
}

                       
/*

need to set oversampling to 0:
CN2_60, CN2_62, CN2_64

16 channels
can enable 0-7 or 0-15
8-bit channel mask applies the nth channel in both chips

Voltage Ranges
-10 to 10V or -5 to 5V
ADC1_RANGE = CN2_56
ADC2_RANGE = CN2_58

Precisions
16-bit

Conversion periods (ns)
1 Hz to 100kHz
10ns per sampling period
10us to ~42.9 seconds in 10ns increments

Trigger
N/A

Interrupt Trigger
N/A


If we get a FIFO overflow we must stop acquiring and return the
data that we were able to acquire before overflow.

doesn't look like we use interrupts anywhere so we have to poll the
number of samples available until we have the number we require.
 */
