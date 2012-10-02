#ifndef __DIORaw_H
#define __DIORaw_H

#undef FUNC
#ifndef SWIGGY
#define FUNC(x) (*x) 
#else
#define FUNC(x) x
#endif

typedef struct DIORaw DIORaw;
typedef struct DIORawAPI DIORawAPI;

struct DIORawAPI {
  void *FUNC(Init)(void *me,...);
  void FUNC(Fini)(void *me);
  int FUNC(Lock)(void *me,unsigned num,int flags);
  int FUNC(Unlock)(void *me,unsigned num,int flags);
  int FUNC(Preempt)(void *me);
  void FUNC(DirSet)(void *me,int num,int asOutput);
  void FUNC(DataSet)(void *me,int num,int asHigh);
  int FUNC(DirGet)(void *me,int num);
  int FUNC(DataGet)(void *me,int num);
  unsigned FUNC(Count)(void *me);
};

struct DIORaw {
  DIORawAPI;
  int InitStatus;
};

enum {
  NetDIORaw_Lock=0,
  NetDIORaw_Unlock=1,
  NetDIORaw_Preempt=2,
  NetDIORaw_DirSet=3,
  NetDIORaw_DataSet=4,
  NetDIORaw_DirGet=5,
  NetDIORaw_DataGet=6,
  NetDIORaw_Count=7
};
#define DIORaw_APICount (1+NetDIORaw_Count)
#endif

// Author: Michael Schmidt (michael@embeddedARM.com)
// Copyright (c) 2011, Technologic Systems, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
