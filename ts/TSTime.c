#ifndef TSTime_c
#define TSTime_c
#include "TSTime.h"
#include "peekpoke.h"

// Generic TS syscon 16-bit access to 32-bit 1Mhz timer

void *TSTimeInit(TSTime *me,void *bus,int adrsMSB,int adrsLSB,int Hz) {

  if (me->InitStatus > 0) return me;

  me->Init = (void *)TSTimeInit;
  me->Fini = (void *)TSTimeFini;
  me->Wait = (void *)TSTimeWait;
  me->Delay = (void *)TSTimeDelay;
  me->Tick = (void *)TSTimeTick;
  me->usElapsed = (void *)TSUSElapsed;
  me->usFuture = (void *)TSUSFuture;
  me->TimeoutQ = (void *)TSTimeoutQ;
  me->TPS = (void *)TSTimeTPS;

  me->bus = bus;
  if (me->bus->InitStatus < 0) {
    me->bus->Fini(bus);
    me->InitStatus = -1;
    return me;
  }
  me->bus = bus;
  me->adrsMSB = adrsMSB;
  me->adrsLSB = adrsLSB;
  me->Hz = Hz; // not used, assumed to be 1,000,000
  me->InitStatus = 1;
  return me;
}

void TSTimeFini(TSTime *me) {
  if (me->InitStatus > 0) {
    me->bus->Fini(me->bus);
    me->InitStatus = 0;
  }
}

unsigned TSTimeWait(TSTime *me,unsigned us) {
  return SystemMicroSecondWait(me,us);
}

void TSTimeDelay(TSTime *me,unsigned us) {
  SystemMicroSecondWait(me,us);
}

static inline unsigned _TSTimeTick(TSTime *me) {
  unsigned short lsb,msb,msb2;

  msb = me->bus->Peek16(me->bus,me->adrsMSB);
  lsb = me->bus->Peek16(me->bus,me->adrsLSB);
  msb2 = me->bus->Peek16(me->bus,me->adrsMSB);
  if (msb == msb2) return (((unsigned)msb)<<16) + lsb;
  lsb = me->bus->Peek16(me->bus,me->adrsLSB);
  return (((unsigned)msb2)<<16) + lsb;
}

unsigned TSTimeTick(TSTime *me) {
  return _TSTimeTick(me);
}

unsigned TSUSElapsed(TSTime *time,unsigned start) {
  unsigned now = _TSTimeTick(time);
  if (now < start) {
    return 1 * ((unsigned)(-start) + now);
  } else {
    return 1 * (now - start);
  }
}

unsigned TSUSFuture(TSTime *time,unsigned start,unsigned us) {
  //if (us == 0) return start;
  return start + us;
  //return start + us/1 + ((us % 1) ? 1 : 0);
}

unsigned TSTimeoutQ(TSTime *time,unsigned start,unsigned end) {
  unsigned now = _TSTimeTick(time);
  if (end > start) {
    return now >= end || now < start;
  } else if (end == start) {
    return 1;
  } else {
    return !(now >= start || now < end);
  }
}

unsigned TSTimeTPS(TSTime *me) {
  return me->Hz;
}
// Author: Michael Schmidt (michael@embeddedARM.com)
// Copyright (c) 2011, Technologic Systems, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
#endif
