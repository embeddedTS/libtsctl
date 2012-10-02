#ifndef __Bus_H
#define __Bus_H

#undef FUNC
#ifndef SWIGGY
#define FUNC(x) (*x) 
#else
#define FUNC(x) x
#endif

typedef struct Bus Bus;
typedef struct BusAPI BusAPI;

struct BusAPI {
  void *FUNC(Init)(void *me,...);
  void FUNC(Fini)(void *me);
  int FUNC(Lock)(void *me,unsigned num,int flags);
  int FUNC(Unlock)(void *me,unsigned num,int flags);
  int FUNC(Preempt)(void *me);
  unsigned char FUNC(Peek8)(void *me,int adrs);
  void FUNC(Poke8)(void *me,int adrs,unsigned char val);
  unsigned short FUNC(Peek16)(void *me,int adrs);
  void FUNC(Poke16)(void *me,int adrs,unsigned short val);
  unsigned FUNC(Peek32)(void *me,int adrs);
  void FUNC(Poke32)(void *me,int adrs,unsigned val);
  int FUNC(BitGet8)(void *me,int adrs,int bit);
  void FUNC(BitAssign8)(void *me,int adrs,int bit,int val);
  void FUNC(BitSet8)(void *me,int adrs,int bit);
  void FUNC(BitClear8)(void *me,int adrs,int bit);
  int FUNC(BitGet16)(void *me,int adrs,int bit);
  void FUNC(BitAssign16)(void *me,int adrs,int bit,int val);
  void FUNC(BitSet16)(void *me,int adrs,int bit);
  void FUNC(BitClear16)(void *me,int adrs,int bit);
  int FUNC(BitGet32)(void *me,int adrs,int bit);
  void FUNC(BitAssign32)(void *me,int adrs,int bit,int val);
  void FUNC(BitSet32)(void *me,int adrs,int bit);
  void FUNC(BitClear32)(void *me,int adrs,int bit);
  void FUNC(PeekStream)(void *me,int address,int direction,char* dest);
  void FUNC(PokeStream)(void *me,int address,int direction,const char* data);

  void FUNC(Refresh)(void *me);
  void FUNC(Commit)(void *me,int forceall);
  int FUNC(BitToggle8)(void *me,int adrs,int bit);
  int FUNC(BitToggle16)(void *me,int adrs,int bit);
  int FUNC(BitToggle32)(void *me,int adrs,int bit);
  unsigned char FUNC(Assign8X)(void *me,int adrs,int bit1,int bit0,int val);
  unsigned short FUNC(Assign16X)(void *me,int adrs,int bit1,int bit0,int val);
  unsigned FUNC(Assign32X)(void *me,int adrs,int bit1,int bit0,int val);
  unsigned char FUNC(BitsGet8)(void *me,int adrs,int bit1,int bit0);
  unsigned short FUNC(BitsGet16)(void *me,int adrs,int bit1,int bit0);
  unsigned FUNC(BitsGet32)(void *me,int adrs,int bit1,int bit0);
};

enum {
  NetBus_Lock=0,
  NetBus_Unlock,
  NetBus_Preempt,
  NetBus_Peek8,
  NetBus_Poke8,
  NetBus_Peek16,
  NetBus_Poke16,
  NetBus_Peek32,
  NetBus_Poke32,
  NetBus_BitGet8,
  NetBus_BitAssign8,
  NetBus_BitSet8,
  NetBus_BitClear8,
  NetBus_BitGet16,
  NetBus_BitAssign16,
  NetBus_BitSet16,
  NetBus_BitClear16,
  NetBus_BitGet32,
  NetBus_BitAssign32,
  NetBus_BitSet32,
  NetBus_BitClear32,
  NetBus_PeekStream,
  NetBus_PokeStream,
  NetBus_Refresh,
  NetBus_Commit,
  NetBus_BitToggle8,
  NetBus_BitToggle16,
  NetBus_BitToggle32,
  NetBus_Assign8X,
  NetBus_Assign16X,
  NetBus_Assign32X,
  NetBus_BitsGet8,
  NetBus_BitsGet16,
  NetBus_BitsGet32
};

#define Bus_APICount (1+NetBus_BitsGet32)
struct Bus {
  BusAPI;
  int InitStatus;
  unsigned LockBase;
  int deferlockW,deferlockR;
};
#endif
// Author: Michael Schmidt (michael@embeddedARM.com)
// Copyright (c) 2011, Technologic Systems, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
