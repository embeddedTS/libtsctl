#ifndef __Cavium2132SBusWindowBus_h
#define __Cavium2132SBusWindowBus_h
#undef FUNC
#ifndef SWIGGY
#define FUNC(x) (*x)
#else
#define FUNC(x) x
#endif

typedef struct Cavium2132SBusWindowBus Cavium2132SBusWindowBus;
struct Cavium2132SBusWindowBus {
	void *FUNC(Init)(Cavium2132SBusWindowBus *me,void *sbus);
	void FUNC(Fini)(Cavium2132SBusWindowBus *me);
	int FUNC(Lock)(Cavium2132SBusWindowBus *me,unsigned num,int flags);
	int FUNC(Unlock)(Cavium2132SBusWindowBus *me,unsigned num,int flags);
	int FUNC(Preempt)(Cavium2132SBusWindowBus *me);
	unsigned char FUNC(Peek8)(Cavium2132SBusWindowBus *me,int adrs);
	void FUNC(Poke8)(Cavium2132SBusWindowBus *me,int adrs,unsigned char val);
	unsigned short FUNC(Peek16)(Cavium2132SBusWindowBus *me,int adrs);
	void FUNC(Poke16)(Cavium2132SBusWindowBus *me,int adrs,unsigned short val);
	unsigned FUNC(Peek32)(Cavium2132SBusWindowBus *me,int adrs);
	void FUNC(Poke32)(Cavium2132SBusWindowBus *me,int adrs,unsigned val);
	int FUNC(BitGet8)(Cavium2132SBusWindowBus *me,int adrs,int bit);
	void FUNC(BitAssign8)(Cavium2132SBusWindowBus *me,int adrs,int bit,int val);
	void FUNC(BitSet8)(Cavium2132SBusWindowBus *me,int adrs,int bit);
	void FUNC(BitClear8)(Cavium2132SBusWindowBus *me,int adrs,int bit);
	int FUNC(BitGet16)(Cavium2132SBusWindowBus *me,int adrs,int bit);
	void FUNC(BitAssign16)(Cavium2132SBusWindowBus *me,int adrs,int bit,int val);
	void FUNC(BitSet16)(Cavium2132SBusWindowBus *me,int adrs,int bit);
	void FUNC(BitClear16)(Cavium2132SBusWindowBus *me,int adrs,int bit);
	int FUNC(BitGet32)(Cavium2132SBusWindowBus *me,int adrs,int bit);
	void FUNC(BitAssign32)(Cavium2132SBusWindowBus *me,int adrs,int bit,int val);
	void FUNC(BitSet32)(Cavium2132SBusWindowBus *me,int adrs,int bit);
	void FUNC(BitClear32)(Cavium2132SBusWindowBus *me,int adrs,int bit);
	void FUNC(PeekStream)(Cavium2132SBusWindowBus *me,int address,int direction,char *dest);
	void FUNC(PokeStream)(Cavium2132SBusWindowBus *me,int address,int direction,const char *data);
	void FUNC(Refresh)(Cavium2132SBusWindowBus *me);
	void FUNC(Commit)(Cavium2132SBusWindowBus *me,int forceall);
	int FUNC(BitToggle8)(Cavium2132SBusWindowBus *me,int adrs,int bit);
	int FUNC(BitToggle16)(Cavium2132SBusWindowBus *me,int adrs,int bit);
	int FUNC(BitToggle32)(Cavium2132SBusWindowBus *me,int adrs,int bit);
	unsigned char FUNC(Assign8X)(Cavium2132SBusWindowBus *me,int adrs,int bit1,int bit0,int val);
	unsigned short FUNC(Assign16X)(Cavium2132SBusWindowBus *me,int adrs,int bit1,int bit0,int val);
	unsigned FUNC(Assign32X)(Cavium2132SBusWindowBus *me,int adrs,int bit1,int bit0,int val);
	unsigned char FUNC(BitsGet8)(Cavium2132SBusWindowBus *me,int adrs,int bit1,int bit0);
	unsigned short FUNC(BitsGet16)(Cavium2132SBusWindowBus *me,int adrs,int bit1,int bit0);
	unsigned FUNC(BitsGet32)(Cavium2132SBusWindowBus *me,int adrs,int bit1,int bit0);
	int InitStatus;
	unsigned LockBase;
	int deferlockW;
	int deferlockR;
	Bus *sbus;
	int AdrsLast;
	int MemBase;
};

void *Cavium2132SBusWindowBusInit(Cavium2132SBusWindowBus* ob,void *sbus);
void Cavium2132SBusWindowBusFini(Cavium2132SBusWindowBus* ob);
int Cavium2132SBusWindowBusLock(Cavium2132SBusWindowBus* ob,unsigned num,int flags);
int Cavium2132SBusWindowBusUnlock(Cavium2132SBusWindowBus* ob,unsigned num,int flags);
int Cavium2132SBusWindowBusPreempt(Cavium2132SBusWindowBus* ob);
unsigned char Cavium2132SBusWindowBusPeek8(Cavium2132SBusWindowBus* ob,int adrs);
void Cavium2132SBusWindowBusPoke8(Cavium2132SBusWindowBus* ob,int adrs,unsigned char val);
unsigned short Cavium2132SBusWindowBusPeek16(Cavium2132SBusWindowBus* ob,int adrs);
void Cavium2132SBusWindowBusPoke16(Cavium2132SBusWindowBus* ob,int adrs,unsigned short val);
unsigned Cavium2132SBusWindowBusPeek32(Cavium2132SBusWindowBus* ob,int adrs);
void Cavium2132SBusWindowBusPoke32(Cavium2132SBusWindowBus* ob,int adrs,unsigned val);
int Cavium2132SBusWindowBusBitGet8(Cavium2132SBusWindowBus* ob,int adrs,int bit);
void Cavium2132SBusWindowBusBitAssign8(Cavium2132SBusWindowBus* ob,int adrs,int bit,int val);
void Cavium2132SBusWindowBusBitSet8(Cavium2132SBusWindowBus* ob,int adrs,int bit);
void Cavium2132SBusWindowBusBitClear8(Cavium2132SBusWindowBus* ob,int adrs,int bit);
int Cavium2132SBusWindowBusBitGet16(Cavium2132SBusWindowBus* ob,int adrs,int bit);
void Cavium2132SBusWindowBusBitAssign16(Cavium2132SBusWindowBus* ob,int adrs,int bit,int val);
void Cavium2132SBusWindowBusBitSet16(Cavium2132SBusWindowBus* ob,int adrs,int bit);
void Cavium2132SBusWindowBusBitClear16(Cavium2132SBusWindowBus* ob,int adrs,int bit);
int Cavium2132SBusWindowBusBitGet32(Cavium2132SBusWindowBus* ob,int adrs,int bit);
void Cavium2132SBusWindowBusBitAssign32(Cavium2132SBusWindowBus* ob,int adrs,int bit,int val);
void Cavium2132SBusWindowBusBitSet32(Cavium2132SBusWindowBus* ob,int adrs,int bit);
void Cavium2132SBusWindowBusBitClear32(Cavium2132SBusWindowBus* ob,int adrs,int bit);
void Cavium2132SBusWindowBusPeekStream(Cavium2132SBusWindowBus* ob,int address,int direction,char *dest);
void Cavium2132SBusWindowBusPokeStream(Cavium2132SBusWindowBus* ob,int address,int direction,const char *data);
void Cavium2132SBusWindowBusRefresh(Cavium2132SBusWindowBus* ob);
void Cavium2132SBusWindowBusCommit(Cavium2132SBusWindowBus* ob,int forceall);
int Cavium2132SBusWindowBusBitToggle8(Cavium2132SBusWindowBus* ob,int adrs,int bit);
int Cavium2132SBusWindowBusBitToggle16(Cavium2132SBusWindowBus* ob,int adrs,int bit);
int Cavium2132SBusWindowBusBitToggle32(Cavium2132SBusWindowBus* ob,int adrs,int bit);
unsigned char Cavium2132SBusWindowBusAssign8X(Cavium2132SBusWindowBus* ob,int adrs,int bit1,int bit0,int val);
unsigned short Cavium2132SBusWindowBusAssign16X(Cavium2132SBusWindowBus* ob,int adrs,int bit1,int bit0,int val);
unsigned Cavium2132SBusWindowBusAssign32X(Cavium2132SBusWindowBus* ob,int adrs,int bit1,int bit0,int val);
unsigned char Cavium2132SBusWindowBusBitsGet8(Cavium2132SBusWindowBus* ob,int adrs,int bit1,int bit0);
unsigned short Cavium2132SBusWindowBusBitsGet16(Cavium2132SBusWindowBus* ob,int adrs,int bit1,int bit0);
unsigned Cavium2132SBusWindowBusBitsGet32(Cavium2132SBusWindowBus* ob,int adrs,int bit1,int bit0);
#endif

// Author: Michael Schmidt (michael@embeddedARM.com)
// Copyright (c) 2012, Technologic Systems, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
