#ifndef __TSCAN1Bus_h
#define __TSCAN1Bus_h
#include "Bus.h"
#undef FUNC
#ifndef SWIGGY
#define FUNC(x) (*x)
#else
#define FUNC(x) x
#endif

typedef struct TSCAN1Bus TSCAN1Bus;
struct TSCAN1Bus {
        void *FUNC(Init)(TSCAN1Bus *bus,void *sub,int base);
	void FUNC(Fini)(TSCAN1Bus *me);
	int FUNC(Lock)(TSCAN1Bus *me,unsigned num,int flags);
	int FUNC(Unlock)(TSCAN1Bus *me,unsigned num,int flags);
	int FUNC(Preempt)(TSCAN1Bus *me);
	unsigned char FUNC(Peek8)(TSCAN1Bus *me,int Address);
	void FUNC(Poke8)(TSCAN1Bus *me,int Address,unsigned char Value);
	unsigned short FUNC(Peek16)(TSCAN1Bus *me,int Address);
	void FUNC(Poke16)(TSCAN1Bus *me,int Address,unsigned short Value);
	unsigned FUNC(Peek32)(TSCAN1Bus *me,int Address);
	void FUNC(Poke32)(TSCAN1Bus *me,int Address,unsigned Value);
	int FUNC(BitGet8)(TSCAN1Bus *me,int Address,int BitNumber);
	void FUNC(BitAssign8)(TSCAN1Bus *me,int Address,int BitNumber,int Value);
	void FUNC(BitSet8)(TSCAN1Bus *me,int Address,int BitNumber);
	void FUNC(BitClear8)(TSCAN1Bus *me,int Address,int BitNumber);
	int FUNC(BitGet16)(TSCAN1Bus *me,int Address,int BitNumber);
	void FUNC(BitAssign16)(TSCAN1Bus *me,int Address,int BitNumber,int Value);
	void FUNC(BitSet16)(TSCAN1Bus *me,int Address,int BitNumber);
	void FUNC(BitClear16)(TSCAN1Bus *me,int Address,int BitNumber);
	int FUNC(BitGet32)(TSCAN1Bus *me,int Address,int BitNumber);
	void FUNC(BitAssign32)(TSCAN1Bus *me,int Address,int BitNumber,int Value);
	void FUNC(BitSet32)(TSCAN1Bus *me,int Address,int BitNumber);
	void FUNC(BitClear32)(TSCAN1Bus *me,int Address,int BitNumber);
	void FUNC(PeekStream)(TSCAN1Bus *me,int address,int direction,char *dest);
	void FUNC(PokeStream)(TSCAN1Bus *me,int address,int direction,const char *data);
	void FUNC(Refresh)(TSCAN1Bus *me);
	void FUNC(Commit)(TSCAN1Bus *me,int ForceAll);
	int FUNC(BitToggle8)(TSCAN1Bus *me,int Address,int BitNumber);
	int FUNC(BitToggle16)(TSCAN1Bus *me,int Address,int BitNumber);
	int FUNC(BitToggle32)(TSCAN1Bus *me,int Address,int BitNumber);
	unsigned char FUNC(Assign8X)(TSCAN1Bus *me,int Address,int BitMSB,int BitLSB,int Value);
	unsigned short FUNC(Assign16X)(TSCAN1Bus *me,int Address,int BitMSB,int BitLSB,int Value);
	unsigned FUNC(Assign32X)(TSCAN1Bus *me,int Address,int BitMSB,int BitLSB,int Value);
	unsigned char FUNC(BitsGet8)(TSCAN1Bus *me,int Address,int BitMSB,int BitLSB);
	unsigned short FUNC(BitsGet16)(TSCAN1Bus *me,int Address,int BitMSB,int BitLSB);
	unsigned FUNC(BitsGet32)(TSCAN1Bus *me,int Address,int BitMSB,int BitLSB);
	int InitStatus;
	unsigned LockBase;
	int deferlockW;
	int deferlockR;
	Bus *sub;
        int base0; // PC-104 (muxbus) offset to PLD registers
        int base1; // PC-104 (muxbus) offset to CAN registers
        int bank;
};

void *TSCAN1BusInit(TSCAN1Bus *bus,void *sub,int base);
void TSCAN1BusFini(TSCAN1Bus* ob);
int TSCAN1BusLock(TSCAN1Bus* ob,unsigned num,int flags);
int TSCAN1BusUnlock(TSCAN1Bus* ob,unsigned num,int flags);
int TSCAN1BusPreempt(TSCAN1Bus* ob);
unsigned char TSCAN1BusPeek8(TSCAN1Bus* ob,int Address);
void TSCAN1BusPoke8(TSCAN1Bus* ob,int Address,unsigned char Value);
unsigned short TSCAN1BusPeek16(TSCAN1Bus* ob,int Address);
void TSCAN1BusPoke16(TSCAN1Bus* ob,int Address,unsigned short Value);
unsigned TSCAN1BusPeek32(TSCAN1Bus* ob,int Address);
void TSCAN1BusPoke32(TSCAN1Bus* ob,int Address,unsigned Value);
int TSCAN1BusBitGet8(TSCAN1Bus* ob,int Address,int BitNumber);
void TSCAN1BusBitAssign8(TSCAN1Bus* ob,int Address,int BitNumber,int Value);
void TSCAN1BusBitSet8(TSCAN1Bus* ob,int Address,int BitNumber);
void TSCAN1BusBitClear8(TSCAN1Bus* ob,int Address,int BitNumber);
int TSCAN1BusBitGet16(TSCAN1Bus* ob,int Address,int BitNumber);
void TSCAN1BusBitAssign16(TSCAN1Bus* ob,int Address,int BitNumber,int Value);
void TSCAN1BusBitSet16(TSCAN1Bus* ob,int Address,int BitNumber);
void TSCAN1BusBitClear16(TSCAN1Bus* ob,int Address,int BitNumber);
int TSCAN1BusBitGet32(TSCAN1Bus* ob,int Address,int BitNumber);
void TSCAN1BusBitAssign32(TSCAN1Bus* ob,int Address,int BitNumber,int Value);
void TSCAN1BusBitSet32(TSCAN1Bus* ob,int Address,int BitNumber);
void TSCAN1BusBitClear32(TSCAN1Bus* ob,int Address,int BitNumber);
void TSCAN1BusPeekStream(TSCAN1Bus* ob,int address,int direction,char *dest);
void TSCAN1BusPokeStream(TSCAN1Bus* ob,int address,int direction,const char *data);
void TSCAN1BusRefresh(TSCAN1Bus* ob);
void TSCAN1BusCommit(TSCAN1Bus* ob,int ForceAll);
int TSCAN1BusBitToggle8(TSCAN1Bus* ob,int Address,int BitNumber);
int TSCAN1BusBitToggle16(TSCAN1Bus* ob,int Address,int BitNumber);
int TSCAN1BusBitToggle32(TSCAN1Bus* ob,int Address,int BitNumber);
unsigned char TSCAN1BusAssign8X(TSCAN1Bus* ob,int Address,int BitMSB,int BitLSB,int Value);
unsigned short TSCAN1BusAssign16X(TSCAN1Bus* ob,int Address,int BitMSB,int BitLSB,int Value);
unsigned TSCAN1BusAssign32X(TSCAN1Bus* ob,int Address,int BitMSB,int BitLSB,int Value);
unsigned char TSCAN1BusBitsGet8(TSCAN1Bus* ob,int Address,int BitMSB,int BitLSB);
unsigned short TSCAN1BusBitsGet16(TSCAN1Bus* ob,int Address,int BitMSB,int BitLSB);
unsigned TSCAN1BusBitsGet32(TSCAN1Bus* ob,int Address,int BitMSB,int BitLSB);
#endif

// Author: Michael Schmidt (michael@embeddedARM.com)
// Copyright (c) 2013, Technologic Systems, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
