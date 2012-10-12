#ifndef __PC104Bus_h
#define __PC104Bus_h
#undef FUNC
#ifndef SWIGGY
#define FUNC(x) (*x)
#else
#define FUNC(x) x
#endif

typedef struct PC104Bus PC104Bus;
struct PC104Bus {
	void *FUNC(Init)(PC104Bus *me,Bus *sub8,int offset8,Bus *sub16,int offset16,void (*LockCallback)(PC104Bus *,unsigned ));
	void FUNC(Fini)(PC104Bus *me);
	int FUNC(Lock)(PC104Bus *me,unsigned num,int flags);
	int FUNC(Unlock)(PC104Bus *me,unsigned num,int flags);
	int FUNC(Preempt)(PC104Bus *me);
	unsigned char FUNC(Peek8)(PC104Bus *me,int adrs);
	void FUNC(Poke8)(PC104Bus *me,int adrs,unsigned char val);
	unsigned short FUNC(Peek16)(PC104Bus *me,int adrs);
	void FUNC(Poke16)(PC104Bus *me,int adrs,unsigned short val);
	unsigned FUNC(Peek32)(PC104Bus *me,int adrs);
	void FUNC(Poke32)(PC104Bus *me,int adrs,unsigned val);
	int FUNC(BitGet8)(PC104Bus *me,int adrs,int bit);
	void FUNC(BitAssign8)(PC104Bus *me,int adrs,int bit,int val);
	void FUNC(BitSet8)(PC104Bus *me,int adrs,int bit);
	void FUNC(BitClear8)(PC104Bus *me,int adrs,int bit);
	int FUNC(BitGet16)(PC104Bus *me,int adrs,int bit);
	void FUNC(BitAssign16)(PC104Bus *me,int adrs,int bit,int val);
	void FUNC(BitSet16)(PC104Bus *me,int adrs,int bit);
	void FUNC(BitClear16)(PC104Bus *me,int adrs,int bit);
	int FUNC(BitGet32)(PC104Bus *me,int adrs,int bit);
	void FUNC(BitAssign32)(PC104Bus *me,int adrs,int bit,int val);
	void FUNC(BitSet32)(PC104Bus *me,int adrs,int bit);
	void FUNC(BitClear32)(PC104Bus *me,int adrs,int bit);
	void FUNC(PeekStream)(PC104Bus *me,int address,int direction,char *dest);
	void FUNC(PokeStream)(PC104Bus *me,int address,int direction,const char *data);
	void FUNC(Refresh)(PC104Bus *me);
	void FUNC(Commit)(PC104Bus *me,int forceall);
	int FUNC(BitToggle8)(PC104Bus *me,int adrs,int bit);
	int FUNC(BitToggle16)(PC104Bus *me,int adrs,int bit);
	int FUNC(BitToggle32)(PC104Bus *me,int adrs,int bit);
	unsigned char FUNC(Assign8X)(PC104Bus *me,int adrs,int bit1,int bit0,int val);
	unsigned short FUNC(Assign16X)(PC104Bus *me,int adrs,int bit1,int bit0,int val);
	unsigned FUNC(Assign32X)(PC104Bus *me,int adrs,int bit1,int bit0,int val);
	unsigned char FUNC(BitsGet8)(PC104Bus *me,int adrs,int bit1,int bit0);
	unsigned short FUNC(BitsGet16)(PC104Bus *me,int adrs,int bit1,int bit0);
	unsigned FUNC(BitsGet32)(PC104Bus *me,int adrs,int bit1,int bit0);
	int InitStatus;
	unsigned LockBase;
	int deferlockW;
	int deferlockR;
	Bus *sub8;
	Bus *sub16;
	int offset8;
	int offset16;
	void (*LockCallback)(PC104Bus *,unsigned );
};

void *PC104BusInit(PC104Bus* ob,Bus *sub8,int offset8,Bus *sub16,int offset16,void (*LockCallback)(PC104Bus *,unsigned ));
void PC104BusFini(PC104Bus* ob);
int PC104BusLock(PC104Bus* ob,unsigned num,int flags);
int PC104BusUnlock(PC104Bus* ob,unsigned num,int flags);
int PC104BusPreempt(PC104Bus* ob);
unsigned char PC104BusPeek8(PC104Bus* ob,int adrs);
void PC104BusPoke8(PC104Bus* ob,int adrs,unsigned char val);
unsigned short PC104BusPeek16(PC104Bus* ob,int adrs);
void PC104BusPoke16(PC104Bus* ob,int adrs,unsigned short val);
unsigned PC104BusPeek32(PC104Bus* ob,int adrs);
void PC104BusPoke32(PC104Bus* ob,int adrs,unsigned val);
int PC104BusBitGet8(PC104Bus* ob,int adrs,int bit);
void PC104BusBitAssign8(PC104Bus* ob,int adrs,int bit,int val);
void PC104BusBitSet8(PC104Bus* ob,int adrs,int bit);
void PC104BusBitClear8(PC104Bus* ob,int adrs,int bit);
int PC104BusBitGet16(PC104Bus* ob,int adrs,int bit);
void PC104BusBitAssign16(PC104Bus* ob,int adrs,int bit,int val);
void PC104BusBitSet16(PC104Bus* ob,int adrs,int bit);
void PC104BusBitClear16(PC104Bus* ob,int adrs,int bit);
int PC104BusBitGet32(PC104Bus* ob,int adrs,int bit);
void PC104BusBitAssign32(PC104Bus* ob,int adrs,int bit,int val);
void PC104BusBitSet32(PC104Bus* ob,int adrs,int bit);
void PC104BusBitClear32(PC104Bus* ob,int adrs,int bit);
void PC104BusPeekStream(PC104Bus* ob,int address,int direction,char *dest);
void PC104BusPokeStream(PC104Bus* ob,int address,int direction,const char *data);
void PC104BusRefresh(PC104Bus* ob);
void PC104BusCommit(PC104Bus* ob,int forceall);
int PC104BusBitToggle8(PC104Bus* ob,int adrs,int bit);
int PC104BusBitToggle16(PC104Bus* ob,int adrs,int bit);
int PC104BusBitToggle32(PC104Bus* ob,int adrs,int bit);
unsigned char PC104BusAssign8X(PC104Bus* ob,int adrs,int bit1,int bit0,int val);
unsigned short PC104BusAssign16X(PC104Bus* ob,int adrs,int bit1,int bit0,int val);
unsigned PC104BusAssign32X(PC104Bus* ob,int adrs,int bit1,int bit0,int val);
unsigned char PC104BusBitsGet8(PC104Bus* ob,int adrs,int bit1,int bit0);
unsigned short PC104BusBitsGet16(PC104Bus* ob,int adrs,int bit1,int bit0);
unsigned PC104BusBitsGet32(PC104Bus* ob,int adrs,int bit1,int bit0);
#endif

// Author: Michael Schmidt (michael@embeddedARM.com)
// Copyright (c) 2012, Technologic Systems, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
