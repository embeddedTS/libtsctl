#include "Cavium2132Time.h"
#include "peekpoke.h"

void *Cavium2132TimeInit(Cavium2132Time *me,...) {

  if (me->InitStatus > 0) return me;

  me->Init = (void *)Cavium2132TimeInit;
  me->Fini = (void *)Cavium2132TimeFini;
  me->Wait = (void *)Cavium2132TimeWait;
  me->Delay = (void *)Cavium2132TimeDelay;
  me->Tick = (void *)Cavium2132TimeTick;
  me->usElapsed = (void *)Cavium2132TimeusElapsed;
  me->usFuture = (void *)Cavium2132TimeusFuture;
  me->TimeoutQ = (void *)Cavium2132TimeTimeoutQ;
  me->TPS = (void *)Cavium2132TimeTPS;

  me->timer3 = MemMap(0x79000040,1);
  me->InitStatus = (me->timer3 != 0) ? 1 : -1;
  return me;
}

void Cavium2132TimeFini(Cavium2132Time *me) {
  if (me->InitStatus > 0) {
    MemUnmap(me->timer3);
    me->InitStatus = 0;
  }
}

unsigned Cavium2132TimeWait(Cavium2132Time *me,unsigned us) {
  return SystemMicroSecondWait(me,us);
}

void Cavium2132TimeDelay(Cavium2132Time *me,unsigned us) {
  SystemMicroSecondWait(me,us);
}

__attribute__((always_inline)) 
static inline unsigned _Cavium2132TimeTick(Cavium2132Time *me) {
  return *(me->timer3);
}

unsigned Cavium2132TimeTick(Cavium2132Time *me) {
  return _Cavium2132TimeTick(me);
}

unsigned Cavium2132TimeusElapsed(Cavium2132Time *time,unsigned start) {
  unsigned now = _Cavium2132TimeTick(time);
  if (now < start) {
    return 10 * ((unsigned)(-start) + now);
  } else {
    return 10 * (now - start);
  }
}

unsigned Cavium2132TimeusFuture(Cavium2132Time *time,unsigned start,unsigned us) {
  if (us == 0) return start;
  if (us < 10) return start+1;
  return start + us/10 + ((us % 10) ? 1 : 0);
}

TimeResult Cavium2132TimeTimeoutQ(Cavium2132Time *time,unsigned start,unsigned end) {
  unsigned now = _Cavium2132TimeTick(time);
  if (end > start) {
    return now >= end || now < start;
  } else if (end == start) {
    return 1;
  } else {
    return !(now >= start || now < end);
  }
}

unsigned Cavium2132TimeTPS(Cavium2132Time *me) {
  return 100000;
}
// Author: Michael Schmidt (michael@embeddedARM.com)
// Copyright (c) 2011, Technologic Systems, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
