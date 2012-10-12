#ifndef __WindowBus_h
#define __WindowBus_h
#undef FUNC
#ifndef SWIGGY
#define FUNC(x) (*x)
#else
#define FUNC(x) x
#endif

typedef struct WindowBus WindowBus;
struct WindowBus {
	void *FUNC(Init)(WindowBus *me,void *bus,int adrs,int data);
	void FUNC(Fini)(WindowBus *me);
	int FUNC(Lock)(WindowBus *me,unsigned num,int flags);
	int FUNC(Unlock)(WindowBus *me,unsigned num,int flags);
	int FUNC(Preempt)(WindowBus *me);
	unsigned char FUNC(Peek8)(WindowBus *me,int adrs);
	void FUNC(Poke8)(WindowBus *me,int adrs,unsigned char val);
	unsigned short FUNC(Peek16)(WindowBus *me,int adrs);
	void FUNC(Poke16)(WindowBus *me,int adrs,unsigned short val);
	unsigned FUNC(Peek32)(WindowBus *me,int adrs);
	void FUNC(Poke32)(WindowBus *me,int adrs,unsigned val);
	int FUNC(BitGet8)(WindowBus *me,int adrs,int bit);
	void FUNC(BitAssign8)(WindowBus *me,int adrs,int bit,int val);
	void FUNC(BitSet8)(WindowBus *me,int adrs,int bit);
	void FUNC(BitClear8)(WindowBus *me,int adrs,int bit);
	int FUNC(BitGet16)(WindowBus *me,int adrs,int bit);
	void FUNC(BitAssign16)(WindowBus *me,int adrs,int bit,int val);
	void FUNC(BitSet16)(WindowBus *me,int adrs,int bit);
	void FUNC(BitClear16)(WindowBus *me,int adrs,int bit);
	int FUNC(BitGet32)(WindowBus *me,int adrs,int bit);
	void FUNC(BitAssign32)(WindowBus *me,int adrs,int bit,int val);
	void FUNC(BitSet32)(WindowBus *me,int adrs,int bit);
	void FUNC(BitClear32)(WindowBus *me,int adrs,int bit);
	void FUNC(PeekStream)(WindowBus *me,int address,int direction,char *dest);
	void FUNC(PokeStream)(WindowBus *me,int address,int direction,const char *data);
	void FUNC(Refresh)(WindowBus *me);
	void FUNC(Commit)(WindowBus *me,int forceall);
	int FUNC(BitToggle8)(WindowBus *me,int adrs,int bit);
	int FUNC(BitToggle16)(WindowBus *me,int adrs,int bit);
	int FUNC(BitToggle32)(WindowBus *me,int adrs,int bit);
	unsigned char FUNC(Assign8X)(WindowBus *me,int adrs,int bit1,int bit0,int val);
	unsigned short FUNC(Assign16X)(WindowBus *me,int adrs,int bit1,int bit0,int val);
	unsigned FUNC(Assign32X)(WindowBus *me,int adrs,int bit1,int bit0,int val);
	unsigned char FUNC(BitsGet8)(WindowBus *me,int adrs,int bit1,int bit0);
	unsigned short FUNC(BitsGet16)(WindowBus *me,int adrs,int bit1,int bit0);
	unsigned FUNC(BitsGet32)(WindowBus *me,int adrs,int bit1,int bit0);
	int InitStatus;
	unsigned LockBase;
	int deferlockW;
	int deferlockR;
	Bus *sub;
	int adrs;
	int data;
};

void *WindowBusInit(WindowBus* ob,void *bus,int adrs,int data);
void WindowBusFini(WindowBus* ob);
int WindowBusLock(WindowBus* ob,unsigned num,int flags);
int WindowBusUnlock(WindowBus* ob,unsigned num,int flags);
int WindowBusPreempt(WindowBus* ob);
unsigned char WindowBusPeek8(WindowBus* ob,int adrs);
void WindowBusPoke8(WindowBus* ob,int adrs,unsigned char val);
unsigned short WindowBusPeek16(WindowBus* ob,int adrs);
void WindowBusPoke16(WindowBus* ob,int adrs,unsigned short val);
unsigned WindowBusPeek32(WindowBus* ob,int adrs);
void WindowBusPoke32(WindowBus* ob,int adrs,unsigned val);
int WindowBusBitGet8(WindowBus* ob,int adrs,int bit);
void WindowBusBitAssign8(WindowBus* ob,int adrs,int bit,int val);
void WindowBusBitSet8(WindowBus* ob,int adrs,int bit);
void WindowBusBitClear8(WindowBus* ob,int adrs,int bit);
int WindowBusBitGet16(WindowBus* ob,int adrs,int bit);
void WindowBusBitAssign16(WindowBus* ob,int adrs,int bit,int val);
void WindowBusBitSet16(WindowBus* ob,int adrs,int bit);
void WindowBusBitClear16(WindowBus* ob,int adrs,int bit);
int WindowBusBitGet32(WindowBus* ob,int adrs,int bit);
void WindowBusBitAssign32(WindowBus* ob,int adrs,int bit,int val);
void WindowBusBitSet32(WindowBus* ob,int adrs,int bit);
void WindowBusBitClear32(WindowBus* ob,int adrs,int bit);
void WindowBusPeekStream(WindowBus* ob,int address,int direction,char *dest);
void WindowBusPokeStream(WindowBus* ob,int address,int direction,const char *data);
void WindowBusRefresh(WindowBus* ob);
void WindowBusCommit(WindowBus* ob,int forceall);
int WindowBusBitToggle8(WindowBus* ob,int adrs,int bit);
int WindowBusBitToggle16(WindowBus* ob,int adrs,int bit);
int WindowBusBitToggle32(WindowBus* ob,int adrs,int bit);
unsigned char WindowBusAssign8X(WindowBus* ob,int adrs,int bit1,int bit0,int val);
unsigned short WindowBusAssign16X(WindowBus* ob,int adrs,int bit1,int bit0,int val);
unsigned WindowBusAssign32X(WindowBus* ob,int adrs,int bit1,int bit0,int val);
unsigned char WindowBusBitsGet8(WindowBus* ob,int adrs,int bit1,int bit0);
unsigned short WindowBusBitsGet16(WindowBus* ob,int adrs,int bit1,int bit0);
unsigned WindowBusBitsGet32(WindowBus* ob,int adrs,int bit1,int bit0);
#endif

// Author: Michael Schmidt (michael@embeddedARM.com)
// Copyright (c) 2012, Technologic Systems, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
