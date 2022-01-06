#ifndef __WindowBus_h
#define __WindowBus_h
#include "Bus.h"
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
	unsigned char FUNC(Peek8)(WindowBus *me,int Address);
	void FUNC(Poke8)(WindowBus *me,int Address,unsigned char Value);
	unsigned short FUNC(Peek16)(WindowBus *me,int Address);
	void FUNC(Poke16)(WindowBus *me,int Address,unsigned short Value);
	unsigned FUNC(Peek32)(WindowBus *me,int Address);
	void FUNC(Poke32)(WindowBus *me,int Address,unsigned Value);
	int FUNC(BitGet8)(WindowBus *me,int Address,int BitNumber);
	void FUNC(BitAssign8)(WindowBus *me,int Address,int BitNumber,int Value);
	void FUNC(BitSet8)(WindowBus *me,int Address,int BitNumber);
	void FUNC(BitClear8)(WindowBus *me,int Address,int BitNumber);
	int FUNC(BitGet16)(WindowBus *me,int Address,int BitNumber);
	void FUNC(BitAssign16)(WindowBus *me,int Address,int BitNumber,int Value);
	void FUNC(BitSet16)(WindowBus *me,int Address,int BitNumber);
	void FUNC(BitClear16)(WindowBus *me,int Address,int BitNumber);
	int FUNC(BitGet32)(WindowBus *me,int Address,int BitNumber);
	void FUNC(BitAssign32)(WindowBus *me,int Address,int BitNumber,int Value);
	void FUNC(BitSet32)(WindowBus *me,int Address,int BitNumber);
	void FUNC(BitClear32)(WindowBus *me,int Address,int BitNumber);
	void FUNC(PeekStream)(WindowBus *me,int address,int direction,char *dest);
	void FUNC(PokeStream)(WindowBus *me,int address,int direction,const char *data);
	void FUNC(Refresh)(WindowBus *me);
	void FUNC(Commit)(WindowBus *me,int ForceAll);
	int FUNC(BitToggle8)(WindowBus *me,int Address,int BitNumber);
	int FUNC(BitToggle16)(WindowBus *me,int Address,int BitNumber);
	int FUNC(BitToggle32)(WindowBus *me,int Address,int BitNumber);
	unsigned char FUNC(Assign8X)(WindowBus *me,int Address,int BitMSB,int BitLSB,int Value);
	unsigned short FUNC(Assign16X)(WindowBus *me,int Address,int BitMSB,int BitLSB,int Value);
	unsigned FUNC(Assign32X)(WindowBus *me,int Address,int BitMSB,int BitLSB,int Value);
	unsigned char FUNC(BitsGet8)(WindowBus *me,int Address,int BitMSB,int BitLSB);
	unsigned short FUNC(BitsGet16)(WindowBus *me,int Address,int BitMSB,int BitLSB);
	unsigned FUNC(BitsGet32)(WindowBus *me,int Address,int BitMSB,int BitLSB);
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
unsigned char WindowBusPeek8(WindowBus* ob,int Address);
void WindowBusPoke8(WindowBus* ob,int Address,unsigned char Value);
unsigned short WindowBusPeek16(WindowBus* ob,int Address);
void WindowBusPoke16(WindowBus* ob,int Address,unsigned short Value);
unsigned WindowBusPeek32(WindowBus* ob,int Address);
void WindowBusPoke32(WindowBus* ob,int Address,unsigned Value);
int WindowBusBitGet8(WindowBus* ob,int Address,int BitNumber);
void WindowBusBitAssign8(WindowBus* ob,int Address,int BitNumber,int Value);
void WindowBusBitSet8(WindowBus* ob,int Address,int BitNumber);
void WindowBusBitClear8(WindowBus* ob,int Address,int BitNumber);
int WindowBusBitGet16(WindowBus* ob,int Address,int BitNumber);
void WindowBusBitAssign16(WindowBus* ob,int Address,int BitNumber,int Value);
void WindowBusBitSet16(WindowBus* ob,int Address,int BitNumber);
void WindowBusBitClear16(WindowBus* ob,int Address,int BitNumber);
int WindowBusBitGet32(WindowBus* ob,int Address,int BitNumber);
void WindowBusBitAssign32(WindowBus* ob,int Address,int BitNumber,int Value);
void WindowBusBitSet32(WindowBus* ob,int Address,int BitNumber);
void WindowBusBitClear32(WindowBus* ob,int Address,int BitNumber);
void WindowBusPeekStream(WindowBus* ob,int address,int direction,char *dest);
void WindowBusPokeStream(WindowBus* ob,int address,int direction,const char *data);
void WindowBusRefresh(WindowBus* ob);
void WindowBusCommit(WindowBus* ob,int ForceAll);
int WindowBusBitToggle8(WindowBus* ob,int Address,int BitNumber);
int WindowBusBitToggle16(WindowBus* ob,int Address,int BitNumber);
int WindowBusBitToggle32(WindowBus* ob,int Address,int BitNumber);
unsigned char WindowBusAssign8X(WindowBus* ob,int Address,int BitMSB,int BitLSB,int Value);
unsigned short WindowBusAssign16X(WindowBus* ob,int Address,int BitMSB,int BitLSB,int Value);
unsigned WindowBusAssign32X(WindowBus* ob,int Address,int BitMSB,int BitLSB,int Value);
unsigned char WindowBusBitsGet8(WindowBus* ob,int Address,int BitMSB,int BitLSB);
unsigned short WindowBusBitsGet16(WindowBus* ob,int Address,int BitMSB,int BitLSB);
unsigned WindowBusBitsGet32(WindowBus* ob,int Address,int BitMSB,int BitLSB);
#endif

// Author: Michael Schmidt (michael@embeddedTS.com)
// Copyright (c) 2012-2022 Technologic Systems, Inc. dba embeddedTS, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
