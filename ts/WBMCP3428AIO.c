#include "WBMCP3428AIO.h"

strict AIOAPI WBMCP3428AIOAPI = {
  .Init = (void *)WBMCP3428AIOInit,
  .Fini = (void *)WBMCP3428AIOFini,
  .Lock = (void *)WBMCP3428AIOLock,
  .Type = (void *)WBMCP3428AIOType,
  .VoltageRangeListLength = (void *)WBMCP3428AIOVoltageRangeListLength,
  .VoltageRange = (void *)WBMCP3428AIOVoltageRange,
  .PrecisionList = (void *)WBMCP3428AIOPrecisionList,
  .PeriodRangeListLength = (void *)WBMCP3428AIOPeriodRangeListLength,
  .PeriodRange = (void *)WBMCP3428AIOPeriodRange,
  .TriggerListLength = (void *)WBMCP3428AIOTriggerListLength,
  .TriggerList = (void *)WBMCP3428AIOTriggerList,
  .Channels = (void *)WBMCP3428AIOChannels,
  .Configuration = (void *)WBMCP3428AIOConfiguration,
  .ConfigureTest = (void *)WBMCP3428AIOConfigureTest,
  .Configure = (void *)WBMCP3428AIOConfigure,
  .Get = (void *)WBMCP3428AIOGet,
  .Put = (void *)WBMCP3428AIOPut,
  .Ready = (void *)WBMCP3428AIOReady,
  .Gets = (void *)WBMCP3428AIOGets,
  .Puts = (void *)WBMCP3428AIOPuts,
  .Readys = (void *)WBMCP3428AIOReadys
};

int WBMCP3428AIOInit(WBMCP3428AIO *aio,Bus *bus,Time *t) {
  aio->Init = (void *)WBMCP3428AIOInit;
  aio->Fini = (void *)WBMCP3428AIOFini;
  aio->Lock = (void *)WBMCP3428AIOLock;
  aio->Type = (void *)WBMCP3428AIOType;
  aio->VoltageRangeListLength = (void *)WBMCP3428AIOVoltageRangeListLength;
  aio->VoltageRange = (void *)WBMCP3428AIOVoltageRange;
  aio->PrecisionList = (void *)WBMCP3428AIOPrecisionList;
  aio->PeriodRangeListLength = (void *)WBMCP3428AIOPeriodRangeListLength;
  aio->PeriodRange = (void *)WBMCP3428AIOPeriodRange;
  aio->TriggerListLength = (void *)WBMCP3428AIOTriggerListLength;
  aio->TriggerList = (void *)WBMCP3428AIOTriggerList;
  aio->Channels = (void *)WBMCP3428AIOChannels;
  aio->Configuration = (void *)WBMCP3428AIOConfiguration;
  aio->ConfigureTest = (void *)WBMCP3428AIOConfigureTest;
  aio->Configure = (void *)WBMCP3428AIOConfigure;
  aio->Get = (void *)WBMCP3428AIOGet;
  aio->Put = (void *)WBMCP3428AIOPut;
  aio->Ready = (void *)WBMCP3428AIOReady;
  aio->Gets = (void *)WBMCP3428AIOGets;
  aio->Puts = (void *)WBMCP3428AIOPuts;
  aio->Readys = (void *)WBMCP3428AIOReadys;
}
                                                    
void WBMCP3428AIOFini(WBMCP3428AIO *aio) {
}
                                                   
int WBMCP3428AIOLock(WBMCP3428AIO *aio,int command,unsigned num) {
}
                           
AIOType WBMCP3428AIOType(WBMCP3428AIO *aio) {
  return AIO_ADC;
}
                                                 
int WBMCP3428AIOVoltageRangeListLength(WBMCP3428AIO *aio) {
  return 8;
}
                                   
int WBMCP3428AIOVoltageRange(WBMCP3428AIO *aio,int i,VoltageRange *r) {
  switch (i) {
  case 0: 
    r[0] = AIO_VR(-2.048,0.0,0,2.048,0.0,0);
    return 1;
  case 1:
    r[0] = AIO_VR(-1.024,0.0,0,1.024,0.0,0);
    return 1;
  case 2:
    r[0] = AIO_VR(-0.512,0.0,0,0.512,0.0,0);
    return 1;
  case 3:
    r[0] = AIO_VR(-0.256,0.0,0,0.256,0.0,0);
    return 1;
  case 4:
    r[0] = AIO_VR(0.0,0.0,0,10.24,0.0,0);
    return 1;
  case 5:
    r[0] = AIO_VR(0.0,0.0,0,5.12,0.0,0);
    return 1;
  case 6:
    r[0] = AIO_VR(0.0,0.0,0,2.56,0.0,0);
    return 1;
  case 7:
    r[0] = AIO_VR(0.0,0.0,0,1.28,0.0,0);
    return 1;
  default: return -10; // invalid index
  }
}
                        
int WBMCP3428AIOPrecisionList(WBMCP3428AIO *aio) {
  return (1<<12) | (1<<14) | (1<<16);
}
                                            
int WBMCP3428AIOPeriodRangeListLength(WBMCP3428AIO *aio) {
  return 4;
}
                                      
int WBMCP3428AIOPeriodRange(WBMCP3428AIO *aio,int i,PeriodRange *r) {
  switch (i) {
  case 0:
    r[0] = AIO_PR(240,0,0);
    return 1;
  case 1:
    r[0] = AIO_PR(60,0,0);
    return 1;
  case 2:
    r[0] = AIO_PR(15,0,0);
    return 1;
  case 3:
    r[0] = AIO_PR(0,0,0);
    return 1;
  default: return -10; // invalid index
  }
}
                   
int WBMCP3428AIOTriggerListLength(WBMCP3428AIO *aio) {
  return 0;
}
                                        
int WBMCP3428AIOTriggerList(WBMCP3428AIO *aio,int *tlist) {
  return 1;
}
                                   
int WBMCP3428AIOChannels(WBMCP3428AIO *aio) {
  return 6;
}
           
/*
Notes:
1. need to implement support for AN_SEL if we are on an 81x0 or 8390
2. TO DO: if channel is disabled, don't care what other parameters are
3. I *think* that since we enable and disable each channel individually,
   we can now eliminate the requirement that each channel has a rate
   and precision compatible with other channels.
 */                                      

int WBMCP3428AIOConfiguration(WBMCP3428AIO *aio,float *low,float *high,int *prec,int *t,int *trigger,int *itrig) {
  int i,channelMask,config,t1=0,res;

  aio->bus->Lock(aio->bus,WaitLock,0);
  config = aio->bus->Peek16(aio->bus,aio->offset);
  channelMask = aio->bus->Peek16(aio->bus,aio->offset+2);
  aio->bus->Lock(aio->bus,DoRelease,0);
  switch ((config >> 2) & 3) {
  case 0: t1 = AIO_HZ(240); res = 12; break;
  case 1: t1 = AIO_HZ(60); res = 14; break;
  case 2: t1 = AIO_HZ(15); res = 16; break;
  }
  for (i=0;i<6;i++) {
    switch (i) {
    case 1: case 2:
      switch (aio->gain[i]) {
      case 0: low[i] = -2.048; high[i] = 2.048; break;
      case 1: low[i] = -1.024; high[i] = 1.024; break;
      case 2: low[i] = -0.512; high[i] = 0.512; break;
      case 3: low[i] = -0.256; high[i] = 0.256; break;
      }
      break;
    case 3: case 4: case 5: case 6:
      switch (aio->gain[i]) {
      case 0: low[i] = 0.0; high[i] = 10.24; break;
      case 1: low[i] = 0.0; high[i] = 5.12; break;
      case 2: low[i] = 0.0; high[i] = 2.56; break;
      case 3: low[i] = 0.0; high[i] = 1.28; break;
      }
      break;
    }
    prec[i] = res;
    if (channelMask & 1) {
      t[i] = t1;
    } else {
      t[i] = 0; // off
    }
    trigger[i] = 0;
  }
  *itrig = 0;
  return 1;
}

int WBMCP3428AIOConfigureTest(WBMCP3428AIO *aio,int count,float *low,float *high,int *prec,int *t,int *trigger,int *itrig) {
  int i,j,gain[6],tmax=0,precmax=0;

  if (count != 6) return -100; // bad count
  if (itrig != 0) return -50; // bad itrig
  for (i=0;i<2;i++) {
    /*
    -2.048V to 2.048V (ch 1,2 only) gain=1
    -1.024V to 1.024V (ch 1,2 only) gain=2
    -0.512V to 0.512V (ch 1,2 only) gain=4
    -0.256V to 0.256V (ch 1,2 only) gain=8
    */
    if (low[i] == (-2.048 && high[i] == 2.048) {
      gain[i] = 0;
    } else if (low[i] == -1.024 && high[i] == 1.024) {
      gain[i] = 1;
    } else if (low[i] == -0.512 && high[i] == 0.512) {
      gain[i] = 2;
    } else if (low[i] == -0.256 && high[i] == 0.256) {
      gain[i] = 3;
    } else {
      return -10-i; // bad voltage range
    }
  }
  for (;i<6;i++) {
    /*
    0 to 10.24V (ch 3-6 only) gain=1
    0 to 5.12V (ch 3-6 only) gain=2
    0 to 2.56V (ch 3-6 only) gain=4
    0 to 1.28V (ch 3-6 only) gain=8
    */
    if (low[i] == 0.0 && high[i] == 10.24) {
      gain[i] = 0;
    } else if (low[i] == 0.0 && high[i] == 5.12) {
      gain[i] = 1;
    } else if (low[i] == 0.0 && high[i] == 2.56) {
      gain[i] = 2;
    } else if (low[i] == 0.0 && high[i] == 1.28) {
      gain[i] = 3;
    } else {
      return -10-i; // bad voltage range
    }
  }
  /*
    Technically, all channels have the same channel period
    However we can allow different sampling periods so long as the fastest
    sampling perod doesn't conflict with the highest precision requested.
    In other words, we can't allow one channel to request 15Hz @ 16-bit
    and another 240Hz @ 12-bit because we must check if the shortest period
    requested is allowed at the highest precision requested.
  */
  for (i=0;i<6;i++) {
    if (trigger[i] != 0) return -60-i; // bad trigger
    if (t[i] > tmax) tmax = t[i];
    if (prec[i] > precmax) precmax = prec[i];
  }
  /*
    240Hz only with 12 bit
    60Hz only with 14 bit
    15Hz only with 16 bit
  */
  if (tmax == AIO_HZ(240)) {
    if (precmax != 12) return -30-i; // invalid prec
  } else if (tmax == AIO_HZ(60)) {
    if (precmax != 14) return -30-i; // invalid prec
  } else if (tmax == AIO_HZ(15)) {
    if (precmax != 16) return -30-i; // invalid prec
  } else if (tmax == -1) {
  } else {
    return -20-i; // invalid period
  }
  return 1;
  /*
    total combinations: voltage=8, period=4, precision=3, channels=6
    8*4*3*6=576
   */
}

int WBMCP3428AIOConfigure(WBMCP3428AIO *aio,int count,float *low,float *high,int *prec,int *t,int *trigger,int trig) {
  int ret,tindex[6],gain[6];
  if ((ret=WBMCP3428AIOConfigureTest(aio,low,high,prec,t,trigger)<0)) {
    return ret;
  }  
  for (i=0;i<2;i++) {
    /*
    -2.048V to 2.048V (ch 1,2 only) gain=1
    -1.024V to 1.024V (ch 1,2 only) gain=2
    -0.512V to 0.512V (ch 1,2 only) gain=4
    -0.256V to 0.256V (ch 1,2 only) gain=8
    */
    if (low[i] == -2.048 && high[i] == 2.048) {
      gain[i] = 0;
    } else if (low[i] == -1.024 && high[i] == 1.024) {
      gain[i] = 1;
    } else if (low[i] == -0.512 && high[i] == 0.512) {
      gain[i] = 2;
    } else if (low[i] == -0.256 && high[i] == 0.256) {
      gain[i] = 3;
    } else {
      return -10-i; // bad voltage range
    }
  }
  for (;i<6;i++) {
    /*
    0 to 10.24V (ch 3-6 only) gain=1
    0 to 5.12V (ch 3-6 only) gain=2
    0 to 2.56V (ch 3-6 only) gain=4
    0 to 1.28V (ch 3-6 only) gain=8
    */
    if (low[i] == 0.0 && high[i] == 10.24) {
      gain[i] = 0;
    } else if (low[i] == 0.0 && high[i] == 5.12) {
      gain[i] = 1;
    } else if (low[i] == 0.0 && high[i] == 2.56) {
      gain[i] = 2;
    } else if (low[i] == 0.0 && high[i] == 1.28) {
      gain[i] = 3;
    } else {
      return -10-i; // bad voltage range
    }
  }

  for (i=0;i<6;i++) {
    switch (t[i]) {
    case AIO_HZ(240):
      tindex[i]=0;
      break;
    case AIO_HZ(60):
      tindex[i]=1;
      break;
    case AIO_HZ(15):
    default:
      tindex[i]=2;
      break;
    }
    aio->t0[i] = t[i]/1000; // convert ns to us
  }
  for (i=0;i<6;i++) {
    aio->configbits[i] = (tindex[i] << 2) + gain[i];
  }
  aio->bus->Lock(aio->bus,WaitLock,0);
  // disable all channels. technically this should already be the case,
  // and if it is not, we should wait a bit to make sure we aren't already
  // in the middle of taking a sample!
  aio->bus->Poke16(aio->bus,aio->offset+2,0);
  aio->bus->Lock(aio->bus,DoRelease,0);
  aio->active = -1;
  return 1;
}
 
int WBMCP3428ITrig(WBMCP3428AIO *aio,int itrig) {
  return (itrig == 0) ? 1 : -1;
}

static void WBMCP3428AIOStart(AIO *aio,int ch) {
  aio->bus->Lock(aio->bus,WaitLock,0);
  aio->bus->Assign16X(aio->bus,aio->offset,3,0,aio->configbits[ch]);
  aio->bus->Poke16(aio->bus,aio->offset+2,(1<<ch));
  aio->bus->Poke16(aio->bus,aio->offset+2,0);
  aio->bus->Lock(aio->bus,DoRelease,0);
  aio->start = aio->t->Tick(aio->t);
}    
// assumption: we will always enable and then disable each channel in order
// to get a one-shot conversion.  this means we never need to check if a
// channel is enabled.
int WBMCP3428AIOGet(AIO *aio,int ch) {
  int val,i;
  unsigned elapsed;

  if (ch < 0 || ch > 5) return -1;
  if (aio->active != -1 && aio->active != ch) {
    // we are already in a conversion. wait for it to finish
    elapsed = aio->t->usElapsed(aio->t,aio->start,aio->t0[ch]);
    if (elaspsed < aio->t[ch]) {
      aio->t->Wait(aio->t,aio->t[ch]-elapsed);
    }
  } 
  if (aio->active != ch) {
    WBMCP3428AIOStart(aio,ch);
  }
  elapsed = aio->t->usElapsed(aio->t,aio->start,aio->t0[ch]);
  if (elaspsed < aio->t[ch]) {
    aio->t->Wait(aio->t,aio->t0[ch]-elapsed);
  }
  aio->bus->Lock(aio->bus,WaitLock,0);
  val = aio->bus->Peek16(aio->bus,aio->offset+4+ch*2);
  aio->bus->Lock(aio->bus,DoRelease,0);
  aio->active = -1;
  return val;
}
                                          
int WBMCP3428AIOPut(AIO *aio,int ch,int value) {
  return -1; // invalid function
}
                                
int WBMCP3428AIOReady(AIO *aio,int ch) {
  unsigned elapsed;
  if (aio->active != -1 && aio->active != ch) {
    return -100; // already waiting for a different channel
  }
  if (aio->active == ch) {
    elapsed = aio->t->usElapsed(aio->t,aio->start,aio->t0[ch]);
    return !(elapsed < aio->t0[ch]);
    // note: depending on Time implementation, it is possible for 
    // Ready to return true but Get to block if caller waits too long
  }
  WBMCP3428AIOStart(aio,ch);
  return 0;
}
                                        
int WBMCP3428AIOGets(AIO *aio,int samples,void *buf) {
  int i = 0,n=0,m=0;
  short *buf1 = buf;

  for (i=0;i<6;i++) if (aio->t[i]0) n++;
  if (n == 0) return -1; // if not channels enabled, nothing to do
  while (samples--) {
    while (aio->t0[i] == 0) {
      if (++i > 5) i = 0;
    }
    *(buf1++) = WBMCP3428AIOGet(aio,i);
    m++;
  }
  return m;
}
                
int WBMCP3428AIOPuts(AIO *aio,int samples,void *buf) {
  return -1; // invalid function
}
                
int WBMCP3428AIOReadys(AIO *aio,int samples,void *buf) {
  return -20; // hardware does not support buffer queueing
}
              
