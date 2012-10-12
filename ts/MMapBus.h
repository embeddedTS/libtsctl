#ifndef __MMapBus_h
#define __MMapBus_h
#undef FUNC
#ifndef SWIGGY
#define FUNC(x) (*x)
#else
#define FUNC(x) x
#endif

typedef struct MMapBus MMapBus;
typedef enum MMapBusError{
  MapBusErrorMapping=-100
}MMapBusError;

struct MMapBus {
	void *FUNC(Init)(MMapBus *me,int MMapBase,int Pages);
	void FUNC(Fini)(MMapBus *me);
	int FUNC(Lock)(MMapBus *me,unsigned num,int flags);
	int FUNC(Unlock)(MMapBus *me,unsigned num,int flags);
	int FUNC(Preempt)(MMapBus *me);
	unsigned char FUNC(Peek8)(MMapBus *me,int adrs);
	void FUNC(Poke8)(MMapBus *me,int adrs,unsigned char val);
	unsigned short FUNC(Peek16)(MMapBus *me,int adrs);
	void FUNC(Poke16)(MMapBus *me,int adrs,unsigned short val);
	unsigned FUNC(Peek32)(MMapBus *me,int adrs);
	void FUNC(Poke32)(MMapBus *me,int adrs,unsigned val);
	int FUNC(BitGet8)(MMapBus *me,int adrs,int bit);
	void FUNC(BitAssign8)(MMapBus *me,int adrs,int bit,int val);
	void FUNC(BitSet8)(MMapBus *me,int adrs,int bit);
	void FUNC(BitClear8)(MMapBus *me,int adrs,int bit);
	int FUNC(BitGet16)(MMapBus *me,int adrs,int bit);
	void FUNC(BitAssign16)(MMapBus *me,int adrs,int bit,int val);
	void FUNC(BitSet16)(MMapBus *me,int adrs,int bit);
	void FUNC(BitClear16)(MMapBus *me,int adrs,int bit);
	int FUNC(BitGet32)(MMapBus *me,int adrs,int bit);
	void FUNC(BitAssign32)(MMapBus *me,int adrs,int bit,int val);
	void FUNC(BitSet32)(MMapBus *me,int adrs,int bit);
	void FUNC(BitClear32)(MMapBus *me,int adrs,int bit);
	void FUNC(PeekStream)(MMapBus *me,int address,int direction,char *dest);
	void FUNC(PokeStream)(MMapBus *me,int address,int direction,const char *data);
	void FUNC(Refresh)(MMapBus *me);
	void FUNC(Commit)(MMapBus *me,int forceall);
	int FUNC(BitToggle8)(MMapBus *me,int adrs,int bit);
	int FUNC(BitToggle16)(MMapBus *me,int adrs,int bit);
	int FUNC(BitToggle32)(MMapBus *me,int adrs,int bit);
	unsigned char FUNC(Assign8X)(MMapBus *me,int adrs,int bit1,int bit0,int val);
	unsigned short FUNC(Assign16X)(MMapBus *me,int adrs,int bit1,int bit0,int val);
	unsigned FUNC(Assign32X)(MMapBus *me,int adrs,int bit1,int bit0,int val);
	unsigned char FUNC(BitsGet8)(MMapBus *me,int adrs,int bit1,int bit0);
	unsigned short FUNC(BitsGet16)(MMapBus *me,int adrs,int bit1,int bit0);
	unsigned FUNC(BitsGet32)(MMapBus *me,int adrs,int bit1,int bit0);
	int InitStatus;
	unsigned LockBase;
	int deferlockW;
	int deferlockR;
	volatile char *Mem;
};

void *MMapBusInit(MMapBus* ob,int MMapBase,int Pages);
void MMapBusFini(MMapBus* ob);
int MMapBusLock(MMapBus* ob,unsigned num,int flags);
int MMapBusUnlock(MMapBus* ob,unsigned num,int flags);
int MMapBusPreempt(MMapBus* ob);
unsigned char MMapBusPeek8(MMapBus* ob,int adrs);
void MMapBusPoke8(MMapBus* ob,int adrs,unsigned char val);
unsigned short MMapBusPeek16(MMapBus* ob,int adrs);
void MMapBusPoke16(MMapBus* ob,int adrs,unsigned short val);
unsigned MMapBusPeek32(MMapBus* ob,int adrs);
void MMapBusPoke32(MMapBus* ob,int adrs,unsigned val);
int MMapBusBitGet8(MMapBus* ob,int adrs,int bit);
void MMapBusBitAssign8(MMapBus* ob,int adrs,int bit,int val);
void MMapBusBitSet8(MMapBus* ob,int adrs,int bit);
void MMapBusBitClear8(MMapBus* ob,int adrs,int bit);
int MMapBusBitGet16(MMapBus* ob,int adrs,int bit);
void MMapBusBitAssign16(MMapBus* ob,int adrs,int bit,int val);
void MMapBusBitSet16(MMapBus* ob,int adrs,int bit);
void MMapBusBitClear16(MMapBus* ob,int adrs,int bit);
int MMapBusBitGet32(MMapBus* ob,int adrs,int bit);
void MMapBusBitAssign32(MMapBus* ob,int adrs,int bit,int val);
void MMapBusBitSet32(MMapBus* ob,int adrs,int bit);
void MMapBusBitClear32(MMapBus* ob,int adrs,int bit);
void MMapBusPeekStream(MMapBus* ob,int address,int direction,char *dest);
void MMapBusPokeStream(MMapBus* ob,int address,int direction,const char *data);
void MMapBusRefresh(MMapBus* ob);
void MMapBusCommit(MMapBus* ob,int forceall);
int MMapBusBitToggle8(MMapBus* ob,int adrs,int bit);
int MMapBusBitToggle16(MMapBus* ob,int adrs,int bit);
int MMapBusBitToggle32(MMapBus* ob,int adrs,int bit);
unsigned char MMapBusAssign8X(MMapBus* ob,int adrs,int bit1,int bit0,int val);
unsigned short MMapBusAssign16X(MMapBus* ob,int adrs,int bit1,int bit0,int val);
unsigned MMapBusAssign32X(MMapBus* ob,int adrs,int bit1,int bit0,int val);
unsigned char MMapBusBitsGet8(MMapBus* ob,int adrs,int bit1,int bit0);
unsigned short MMapBusBitsGet16(MMapBus* ob,int adrs,int bit1,int bit0);
unsigned MMapBusBitsGet32(MMapBus* ob,int adrs,int bit1,int bit0);
#endif

// Author: Michael Schmidt (michael@embeddedARM.com)
// Copyright (c) 2012, Technologic Systems, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
