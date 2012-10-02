#ifndef __DIO_H
#define __DIO_H
typedef enum { 
  INPUT_LOW=-3,INPUT_HIGH=-2,INPUT=-1,LOW=0, HIGH=1,
} DIOState;
static inline DIOState DIOValue(DIOState state) {
  switch (state) {
  case INPUT_LOW:
  case LOW:
    return LOW;
  case INPUT_HIGH:
  case HIGH:
    return HIGH;
  default: return LOW;
  }
}

static inline const char *DIOValueString(DIOState state) {
  switch(state) {
  case INPUT_LOW: return "InputLow";
  case INPUT_HIGH: return "InputHigh";
  case INPUT: return "Input";
  case LOW: return "Low";
  case HIGH: return "High";
  default: return "Invalid";
  }
}

typedef enum {
  DIO_NOT_PRESENT=0,
  DIO_CAN_INPUT=1,
  DIO_CAN_DRIVE_HIGH=2,
  DIO_CAN_DRIVE_LOW=4,
  DIO_INPUT_ONLY=1, // DIO_CAN_INPUT
  DIO_OUTPUT_ONLY=6, // (DIO_CAN_DRIVE_HIGH | DIO_CAN_DRIVE_LOW)
  DIO_NORMAL=7 // (DIO_CAN_DRIVE_HIGH | DIO_CAN_DRIVE_LOW | DIO_CAN_INPUT)
} DIOCaps;

#undef FUNC
#ifndef SWIGGY
#define FUNC(x) (*x) 
#else
#define FUNC(x) x
#endif
typedef struct DIO DIO;
typedef struct DIOAPI DIOAPI;

struct DIOAPI {
  void *FUNC(Init)(void *me);
  void FUNC(Fini)(void *me);
  int FUNC(Lock)(void *me,unsigned num,int flags);
  int FUNC(Unlock)(void *me,unsigned num,int flags);
  int FUNC(Preempt)(void *me);
  void FUNC(Refresh)(void *me);
  void FUNC(Commit)(void *me,int forceall);
  void FUNC(Set)(void *me,int DIONum,DIOState State);
  DIOState FUNC(Get)(void *me,int DIONum);
  void FUNC(SetAsync)(void *me,int DIONum,DIOState State);
  DIOState FUNC(GetAsync)(void *me,int DIONum);
  void FUNC(Wait)(void *,int* match,int min,int max,const int* nh,const int* nl);
  unsigned FUNC(Count)(void *me);
  DIOCaps FUNC(Capabilities)(void *me,unsigned num);
  int FUNC(GetMulti)(void *me,char*,int offset);
/*
  Additional DIO functions:
  toggle
  void FUNC(ToggleAsync)(void *me,int DIONum);
  void FUNC(Toggle)(void *me,int DIONum);
 */
};

struct DIO {
  DIOAPI;
  int InitStatus;
};

enum {
  NetDIO_Lock=0, 
  NetDIO_Unlock=1, 
  NetDIO_Preempt=2, 
  NetDIO_Refresh=3, 
  NetDIO_Commit=4, 
  NetDIO_Set=5, 
  NetDIO_Get=6, 
  NetDIO_SetAsync=7,
  NetDIO_GetAsync=8,
  NetDIO_Wait=7,
  NetDIO_Count=8,
  NetDIO_Capabilities=9,
  NetDIO_GetMulti=10
};
#define DIO_APICount (1+NetDIO_GetMulti)

#endif
// Author: Michael Schmidt (michael@embeddedARM.com)
// Copyright (c) 2011, Technologic Systems, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
