#ifndef __NBus_h
#define __NBus_h
#include "Bus.h"
#undef FUNC
#ifndef SWIGGY
#define FUNC(x) (*x)
#else
#define FUNC(x) x
#endif

typedef struct NBus NBus;
typedef enum NBusError{
  NBusErrorMapping=-100
}NBusError;

struct NBus {
	void *FUNC(Init)(NBus *me);
	void FUNC(Fini)(NBus *me);
	int FUNC(Lock)(NBus *me,unsigned num,int flags);
	int FUNC(Unlock)(NBus *me,unsigned num,int flags);
	int FUNC(Preempt)(NBus *me);
	unsigned char FUNC(Peek8)(NBus *me,int Address);
	void FUNC(Poke8)(NBus *me,int Address,unsigned char Value);
	unsigned short FUNC(Peek16)(NBus *me,int Address);
	void FUNC(Poke16)(NBus *me,int Address,unsigned short Value);
	unsigned FUNC(Peek32)(NBus *me,int Address);
	void FUNC(Poke32)(NBus *me,int Address,unsigned Value);
	int FUNC(BitGet8)(NBus *me,int Address,int BitNumber);
	void FUNC(BitAssign8)(NBus *me,int Address,int BitNumber,int Value);
	void FUNC(BitSet8)(NBus *me,int Address,int BitNumber);
	void FUNC(BitClear8)(NBus *me,int Address,int BitNumber);
	int FUNC(BitGet16)(NBus *me,int Address,int BitNumber);
	void FUNC(BitAssign16)(NBus *me,int Address,int BitNumber,int Value);
	void FUNC(BitSet16)(NBus *me,int Address,int BitNumber);
	void FUNC(BitClear16)(NBus *me,int Address,int BitNumber);
	int FUNC(BitGet32)(NBus *me,int Address,int BitNumber);
	void FUNC(BitAssign32)(NBus *me,int Address,int BitNumber,int Value);
	void FUNC(BitSet32)(NBus *me,int Address,int BitNumber);
	void FUNC(BitClear32)(NBus *me,int Address,int BitNumber);
	void FUNC(PeekStream)(NBus *me,int address,int direction,char *dest);
	void FUNC(PokeStream)(NBus *me,int address,int direction,const char *data);
	void FUNC(Refresh)(NBus *me);
	void FUNC(Commit)(NBus *me,int ForceAll);
	int FUNC(BitToggle8)(NBus *me,int Address,int BitNumber);
	int FUNC(BitToggle16)(NBus *me,int Address,int BitNumber);
	int FUNC(BitToggle32)(NBus *me,int Address,int BitNumber);
	unsigned char FUNC(Assign8X)(NBus *me,int Address,int BitMSB,int BitLSB,int Value);
	unsigned short FUNC(Assign16X)(NBus *me,int Address,int BitMSB,int BitLSB,int Value);
	unsigned FUNC(Assign32X)(NBus *me,int Address,int BitMSB,int BitLSB,int Value);
	unsigned char FUNC(BitsGet8)(NBus *me,int Address,int BitMSB,int BitLSB);
	unsigned short FUNC(BitsGet16)(NBus *me,int Address,int BitMSB,int BitLSB);
	unsigned FUNC(BitsGet32)(NBus *me,int Address,int BitMSB,int BitLSB);
	int InitStatus;
	unsigned LockBase;
	int deferlockW;
	int deferlockR;
        unsigned int * volatile mxsgpioregs;
};

void *NBusInit(NBus* ob);
void NBusFini(NBus* ob);
int NBusLock(NBus* ob,unsigned num,int flags);
int NBusUnlock(NBus* ob,unsigned num,int flags);
int NBusPreempt(NBus* ob);
unsigned char NBusPeek8(NBus* ob,int Address);
void NBusPoke8(NBus* ob,int Address,unsigned char Value);
unsigned short NBusPeek16(NBus* ob,int Address);
void NBusPoke16(NBus* ob,int Address,unsigned short Value);
unsigned NBusPeek32(NBus* ob,int Address);
void NBusPoke32(NBus* ob,int Address,unsigned Value);
int NBusBitGet8(NBus* ob,int Address,int BitNumber);
void NBusBitAssign8(NBus* ob,int Address,int BitNumber,int Value);
void NBusBitSet8(NBus* ob,int Address,int BitNumber);
void NBusBitClear8(NBus* ob,int Address,int BitNumber);
int NBusBitGet16(NBus* ob,int Address,int BitNumber);
void NBusBitAssign16(NBus* ob,int Address,int BitNumber,int Value);
void NBusBitSet16(NBus* ob,int Address,int BitNumber);
void NBusBitClear16(NBus* ob,int Address,int BitNumber);
int NBusBitGet32(NBus* ob,int Address,int BitNumber);
void NBusBitAssign32(NBus* ob,int Address,int BitNumber,int Value);
void NBusBitSet32(NBus* ob,int Address,int BitNumber);
void NBusBitClear32(NBus* ob,int Address,int BitNumber);
void NBusPeekStream(NBus* ob,int address,int direction,char *dest);
void NBusPokeStream(NBus* ob,int address,int direction,const char *data);
void NBusRefresh(NBus* ob);
void NBusCommit(NBus* ob,int ForceAll);
int NBusBitToggle8(NBus* ob,int Address,int BitNumber);
int NBusBitToggle16(NBus* ob,int Address,int BitNumber);
int NBusBitToggle32(NBus* ob,int Address,int BitNumber);
unsigned char NBusAssign8X(NBus* ob,int Address,int BitMSB,int BitLSB,int Value);
unsigned short NBusAssign16X(NBus* ob,int Address,int BitMSB,int BitLSB,int Value);
unsigned NBusAssign32X(NBus* ob,int Address,int BitMSB,int BitLSB,int Value);
unsigned char NBusBitsGet8(NBus* ob,int Address,int BitMSB,int BitLSB);
unsigned short NBusBitsGet16(NBus* ob,int Address,int BitMSB,int BitLSB);
unsigned NBusBitsGet32(NBus* ob,int Address,int BitMSB,int BitLSB);
#endif

// Author: Michael Schmidt (michael@embeddedARM.com)
// Copyright (c) 2012, Technologic Systems, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
