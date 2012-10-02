#include "ts8820EDIO.h"
#include "Array.h"

void *ts8820EDIOInit(ts8820EDIO *me,Bus *bus,Pin *pin,int start){
  if (me->InitStatus > 0) return me;
  me->InitStatus = 1;
  me->Lock = (void *)ts8820EDIOLock;
  me->Unlock = (void *)ts8820EDIOUnlock;
  me->Preempt = (void *)ts8820EDIOPreempt;
  me->QueryFunction = (void *)ts8820EDIOQueryFunction;
  me->PWM = (void *)ts8820EDIOPWM;
  me->QueryPWM = (void *)ts8820EDIOQueryPWM;
  me->PWMfd = (void *)ts8820EDIOPWMfd;
  me->QueryPWMfd = (void *)ts8820EDIOQueryPWMfd;
  me->QuadratureCount = (void *)ts8820EDIOQuadratureCount;
  me->EdgeCount = (void *)ts8820EDIOEdgeCount;
  me->Glitched = (void *)ts8820EDIOGlitched;
  me->HBridge = (void *)ts8820EDIOHBridge;

  me->bus = bus;
  me->pin = pin;
  me->start = start;
  return me;
}

void ts8820EDIOFini(ts8820EDIO *me){
}

int ts8820EDIOLock(ts8820EDIO *me,unsigned num,int flags){
  if (num < me->start + 14 || num > me->start + 21) return -1;
  int ret = me->pin->Lock(me->pin,num,flags);
  if (ret < 0) return ret;
  if (num >= me->start + 14 && num < me->start + 21) {
    me->pin->ModeSet(me->pin,num,MODE_PWM);
  }
  return ret;
}

int ts8820EDIOUnlock(ts8820EDIO *me,unsigned num,int flags){
  return me->pin->Unlock(me->pin,num,flags);
}

int ts8820EDIOPreempt(ts8820EDIO *me){
  return me->pin->Preempt(me->pin);
}

/*
  PWM is present on OUT1-6, HB1, HB2
  DIO14-21 relative to the TS-8820.
 */
int* ts8820EDIOQueryFunction(ts8820EDIO *me,EDIOType type){
  int i;
  int* ret;

  if (type == EDIO_PWM) {
    ret = ArrayAlloc(8,sizeof(int));
    for (i=0;i<8;i++) ret[i] = me->start + 14 + i;
    return ret;
  }
  ret = ArrayAlloc(0,sizeof(int));
  return ret;
}

// PWM:
// f: frequency
// L: low time
// H: high time
// D: duty cycle

// f = 1/(L + H)  , D + H / (L+H)
// L = (1-D) / f  , H = D / f
int ts8820EDIOPWM(ts8820EDIO *me,int num,unsigned periodHigh,unsigned periodLow){
  unsigned f;
  int prescalar, dutycycle;

  num -= me->start;
  if (num < 14 || num > 21) return -1;

  // freq = 12207 / 2^prescalar
  // period = 2^prescalar / 12207
  // duty cycle has 12 bits resolution
  // set bit 14 to make output 100% high
  // effective duty cycle = duty cycle / 4096

  // [15:13] = prescalar
  // [12:0] = duty cycle

  // 000 = 12207Hz
  // 001 = 6104 Hz
  // 010 = 3052 Hz
  // 011 = 1526 Hz
  // 100 = 763 Hz
  // 101 = 381 Hz
  // 110 = 190 Hz
  // 111 = 95 Hz

  // technically the following addition may be undefined according to the C 
  // standard, so extreme values may produce nonsensical results
  if (periodHigh + periodLow < periodHigh) {
    f = 95; // minimum
  } else {
    f = 1000000000 / (periodHigh + periodLow);
  }
  // round to the nearest power of two
  if (f < (95+190)/2) { // 95
    prescalar = 7;
  } else if (f < (190+381)/2) { // 190
    prescalar = 6;
  } else if (f < (381+763)/2) { // 381
    prescalar = 5;
  } else if (f < (763+1526)/2) { // 763
    prescalar = 4;
  } else if (f < (1526+3052)/2) { // 1526
    prescalar = 3;
  } else if (f < (3052+6104)/2) { // 3052
    prescalar = 2;
  } else if (f < (6104+12207)/2) { // 6104
    prescalar = 1;
  } else {
    prescalar = 0;
  }
  // even if a frequency is specified that we don't exactly support, we use
  // as close to the implied duty cycle as possible
  dutycycle = 4096LL * periodHigh / (periodHigh + periodLow);
  // set PWM parameters
  me->bus->Lock(me->bus,0,0);
  me->bus->Poke16(me->bus,0x10 + (2*(num-14)), (prescalar<<13) + dutycycle);
  me->bus->Unlock(me->bus,0,0);

  return 1;
}

int ts8820EDIOPWMfd(ts8820EDIO *me,int num,unsigned mfreq,unsigned uDC) {
  unsigned f = mfreq / 1000;
  int prescalar, dutycycle;

  num -= me->start;
  if (num < 14 || num > 21) return -1;

  if (f < (95+190)/2) { // 95
    prescalar = 7;
  } else if (f < (190+381)/2) { // 190
    prescalar = 6;
  } else if (f < (381+763)/2) { // 381
    prescalar = 5;
  } else if (f < (763+1526)/2) { // 763
    prescalar = 4;
  } else if (f < (1526+3052)/2) { // 1526
    prescalar = 3;
  } else if (f < (3052+6104)/2) { // 3052
    prescalar = 2;
  } else if (f < (6104+12207)/2) { // 6104
    prescalar = 1;
  } else {
    prescalar = 0;
  }
  dutycycle = 4096LL * uDC / 1000000;
  me->bus->Lock(me->bus,0,0);
  me->bus->Poke16(me->bus,0x10 + (2*(num-14)), (prescalar<<13) + dutycycle);
  me->bus->Unlock(me->bus,0,0);

  return 1;

}

int ts8820EDIOQueryPWMfd(ts8820EDIO *me,int num,unsigned mfreq[1],unsigned uDC[1]) {
  int reg;
  unsigned T; 
  num -= me->start;
  if (num < 14 || num > 21) return -1;

  me->bus->Lock(me->bus,0,0);
  reg = me->bus->Peek16(me->bus,0x10 + (2*(num-14)));
  me->bus->Unlock(me->bus,0,0);
  // period = 2^prescalar / 12207
  mfreq[0] = 12207000 / (1 << (reg >> 13));
  if (reg & 0x1000) {
    uDC[0] = 1000000;
  } else {
    uDC[0] = 1000000LL * (reg & 0xFFF) / 4096;
  }
  return 1;
}

int ts8820EDIOQueryPWM(ts8820EDIO *me,int num,unsigned periodHigh[1],unsigned periodLow[1]) {
  int reg;
  unsigned T; 
  num -= me->start;
  if (num < 14 || num > 21) return -1;

  me->bus->Lock(me->bus,0,0);
  reg = me->bus->Peek16(me->bus,0x10 + (2*(num-14)));
  me->bus->Unlock(me->bus,0,0);
  // period = 2^prescalar / 12207
  T = 81920 * (1 << (reg >> 13));
  if (reg & 0x1000) {
    periodHigh[0] = T;
    periodLow[0] = 0;
  } else {
    periodHigh[0] = T / 4096 * (reg & 0xFFF);
    periodLow[0] = T - periodHigh[0];
  }
  return 1;
}

int ts8820EDIOQuadratureCount(ts8820EDIO *me,int num){
  return -1;
}

unsigned long long ts8820EDIOEdgeCount(ts8820EDIO *me,int num,int edge){
  unsigned short ret;

  num -= me->start;
  if (num < 0 || num > 13) return 0;

  if (edge <= 0) return 0LL; // only count positive edges

  me->bus->Lock(me->bus,0,0);
  ret = me->bus->Peek16(me->bus,0x20 + (2*num));
  me->bus->Unlock(me->bus,0,0);
  return ret;
}

int ts8820EDIOGlitched(ts8820EDIO *me,int num){
  return -1;
}

int ts8820EDIOHBridge(ts8820EDIO *me,int num, HBState state) {
  num -= me->start;
  if (num < 20 || num > 21) return -1;

  switch (state) {
  case HB_LEFT:
    me->bus->Lock(me->bus,0,0);
    me->bus->BitSet16(me->bus,2,num-20+6);
    me->bus->BitSet16(me->bus,2,num-20+4);
    me->bus->Unlock(me->bus,0,0);
    return 1;
  case HB_RIGHT:
    me->bus->Lock(me->bus,0,0);
    me->bus->BitSet16(me->bus,2,num-20+6);
    me->bus->BitClear16(me->bus,2,num-20+4);
    me->bus->Unlock(me->bus,0,0);
    return 1;
  case HB_FREE_RUNNING:
    me->bus->Lock(me->bus,0,0);
    me->bus->BitClear16(me->bus,2,num-20+6);
    me->bus->Unlock(me->bus,0,0);
    return 1;    
  case HB_BRAKING:
  default:
    return -10; // unsupported
  }
}


// Author: Michael Schmidt (michael@embeddedARM.com)
// Copyright (c) 2012, Technologic Systems, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
