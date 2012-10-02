#ifndef __Time_H
#define __Time_H

#undef FUNC
#ifndef SWIGGY
#define FUNC(x) (*x) 
#else
#define FUNC(x) x
#endif

typedef unsigned long long TimeNS; // nanoseconds

typedef struct Time Time;
typedef struct TimeAPI TimeAPI;

struct TimeAPI {
  void *FUNC(Init)(void *me,...);
  void FUNC(Fini)(void *me);
  unsigned FUNC(Wait)(void *me,unsigned microseconds);
  void FUNC(Delay)(void *me,unsigned microseconds);
  unsigned FUNC(Tick)(void *me);
  unsigned FUNC(usElapsed)(void *me,unsigned start);
  unsigned FUNC(usFuture)(void *me,unsigned start,unsigned us);
  int FUNC(TimeoutQ)(void *me,unsigned start,unsigned end);
  unsigned FUNC(TPS)(void *me);
};

struct Time {
  TimeAPI;
  int InitStatus;
};

enum {
  NetTime_Wait=0,
  NetTime_Delay=1,
  NetTime_Tick=2,
  NetTime_usElapsed=3,
  NetTime_usFuture=4,
  NetTime_TimeoutQ=5,
  NetTime_TPS=6
};
#define Time_APICount (1+NetTime_TPS)
#endif
// Author: Michael Schmidt (michael@embeddedARM.com)
// Copyright (c) 2011, Technologic Systems, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
