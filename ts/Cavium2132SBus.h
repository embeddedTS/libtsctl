#ifndef __Cavium2132SBus_h
#define __Cavium2132SBus_h
#include "Bus.h"
#undef FUNC
#ifndef SWIGGY
#define FUNC(x) (*x)
#else
#define FUNC(x) x
#endif

typedef struct Cavium2132SBus Cavium2132SBus;
typedef enum Cavium2132SBusError{
  Cavium2132SBusErrorMapping=-100
}Cavium2132SBusError;

struct Cavium2132SBus {
	void *FUNC(Init)(Cavium2132SBus *me,void *spibus,void *gpiobus);
	void FUNC(Fini)(Cavium2132SBus *me);
	int FUNC(Lock)(Cavium2132SBus *me,unsigned num,int flags);
	int FUNC(Unlock)(Cavium2132SBus *me,unsigned num,int flags);
	int FUNC(Preempt)(Cavium2132SBus *me);
	unsigned char FUNC(Peek8)(Cavium2132SBus *me,int Address);
	void FUNC(Poke8)(Cavium2132SBus *me,int Address,unsigned char Value);
	unsigned short FUNC(Peek16)(Cavium2132SBus *me,int Address);
	void FUNC(Poke16)(Cavium2132SBus *me,int Address,unsigned short Value);
	unsigned FUNC(Peek32)(Cavium2132SBus *me,int Address);
	void FUNC(Poke32)(Cavium2132SBus *me,int Address,unsigned Value);
	int FUNC(BitGet8)(Cavium2132SBus *me,int Address,int BitNumber);
	void FUNC(BitAssign8)(Cavium2132SBus *me,int Address,int BitNumber,int Value);
	void FUNC(BitSet8)(Cavium2132SBus *me,int Address,int BitNumber);
	void FUNC(BitClear8)(Cavium2132SBus *me,int Address,int BitNumber);
	int FUNC(BitGet16)(Cavium2132SBus *me,int Address,int BitNumber);
	void FUNC(BitAssign16)(Cavium2132SBus *me,int Address,int BitNumber,int Value);
	void FUNC(BitSet16)(Cavium2132SBus *me,int Address,int BitNumber);
	void FUNC(BitClear16)(Cavium2132SBus *me,int Address,int BitNumber);
	int FUNC(BitGet32)(Cavium2132SBus *me,int Address,int BitNumber);
	void FUNC(BitAssign32)(Cavium2132SBus *me,int Address,int BitNumber,int Value);
	void FUNC(BitSet32)(Cavium2132SBus *me,int Address,int BitNumber);
	void FUNC(BitClear32)(Cavium2132SBus *me,int Address,int BitNumber);
	void FUNC(PeekStream)(Cavium2132SBus *me,int address,int direction,char *dest);
	void FUNC(PokeStream)(Cavium2132SBus *me,int address,int direction,const char *data);
	void FUNC(Refresh)(Cavium2132SBus *me);
	void FUNC(Commit)(Cavium2132SBus *me,int ForceAll);
	int FUNC(BitToggle8)(Cavium2132SBus *me,int Address,int BitNumber);
	int FUNC(BitToggle16)(Cavium2132SBus *me,int Address,int BitNumber);
	int FUNC(BitToggle32)(Cavium2132SBus *me,int Address,int BitNumber);
	unsigned char FUNC(Assign8X)(Cavium2132SBus *me,int Address,int BitMSB,int BitLSB,int Value);
	unsigned short FUNC(Assign16X)(Cavium2132SBus *me,int Address,int BitMSB,int BitLSB,int Value);
	unsigned FUNC(Assign32X)(Cavium2132SBus *me,int Address,int BitMSB,int BitLSB,int Value);
	unsigned char FUNC(BitsGet8)(Cavium2132SBus *me,int Address,int BitMSB,int BitLSB);
	unsigned short FUNC(BitsGet16)(Cavium2132SBus *me,int Address,int BitMSB,int BitLSB);
	unsigned FUNC(BitsGet32)(Cavium2132SBus *me,int Address,int BitMSB,int BitLSB);
	int InitStatus;
	unsigned LockBase;
	int deferlockW;
	int deferlockR;
	Bus *spibus;
	Bus *gpiobus;
	int gotHUP;
	int last_gpio_adr;
};

void *Cavium2132SBusInit(Cavium2132SBus* ob,void *spibus,void *gpiobus);
void Cavium2132SBusFini(Cavium2132SBus* ob);
int Cavium2132SBusLock(Cavium2132SBus* ob,unsigned num,int flags);
int Cavium2132SBusUnlock(Cavium2132SBus* ob,unsigned num,int flags);
int Cavium2132SBusPreempt(Cavium2132SBus* ob);
unsigned char Cavium2132SBusPeek8(Cavium2132SBus* ob,int Address);
void Cavium2132SBusPoke8(Cavium2132SBus* ob,int Address,unsigned char Value);
unsigned short Cavium2132SBusPeek16(Cavium2132SBus* ob,int Address);
void Cavium2132SBusPoke16(Cavium2132SBus* ob,int Address,unsigned short Value);
unsigned Cavium2132SBusPeek32(Cavium2132SBus* ob,int Address);
void Cavium2132SBusPoke32(Cavium2132SBus* ob,int Address,unsigned Value);
int Cavium2132SBusBitGet8(Cavium2132SBus* ob,int Address,int BitNumber);
void Cavium2132SBusBitAssign8(Cavium2132SBus* ob,int Address,int BitNumber,int Value);
void Cavium2132SBusBitSet8(Cavium2132SBus* ob,int Address,int BitNumber);
void Cavium2132SBusBitClear8(Cavium2132SBus* ob,int Address,int BitNumber);
int Cavium2132SBusBitGet16(Cavium2132SBus* ob,int Address,int BitNumber);
void Cavium2132SBusBitAssign16(Cavium2132SBus* ob,int Address,int BitNumber,int Value);
void Cavium2132SBusBitSet16(Cavium2132SBus* ob,int Address,int BitNumber);
void Cavium2132SBusBitClear16(Cavium2132SBus* ob,int Address,int BitNumber);
int Cavium2132SBusBitGet32(Cavium2132SBus* ob,int Address,int BitNumber);
void Cavium2132SBusBitAssign32(Cavium2132SBus* ob,int Address,int BitNumber,int Value);
void Cavium2132SBusBitSet32(Cavium2132SBus* ob,int Address,int BitNumber);
void Cavium2132SBusBitClear32(Cavium2132SBus* ob,int Address,int BitNumber);
void Cavium2132SBusPeekStream(Cavium2132SBus* ob,int address,int direction,char *dest);
void Cavium2132SBusPokeStream(Cavium2132SBus* ob,int address,int direction,const char *data);
void Cavium2132SBusRefresh(Cavium2132SBus* ob);
void Cavium2132SBusCommit(Cavium2132SBus* ob,int ForceAll);
int Cavium2132SBusBitToggle8(Cavium2132SBus* ob,int Address,int BitNumber);
int Cavium2132SBusBitToggle16(Cavium2132SBus* ob,int Address,int BitNumber);
int Cavium2132SBusBitToggle32(Cavium2132SBus* ob,int Address,int BitNumber);
unsigned char Cavium2132SBusAssign8X(Cavium2132SBus* ob,int Address,int BitMSB,int BitLSB,int Value);
unsigned short Cavium2132SBusAssign16X(Cavium2132SBus* ob,int Address,int BitMSB,int BitLSB,int Value);
unsigned Cavium2132SBusAssign32X(Cavium2132SBus* ob,int Address,int BitMSB,int BitLSB,int Value);
unsigned char Cavium2132SBusBitsGet8(Cavium2132SBus* ob,int Address,int BitMSB,int BitLSB);
unsigned short Cavium2132SBusBitsGet16(Cavium2132SBus* ob,int Address,int BitMSB,int BitLSB);
unsigned Cavium2132SBusBitsGet32(Cavium2132SBus* ob,int Address,int BitMSB,int BitLSB);
#endif

// Author: Michael Schmidt (michael@embeddedARM.com)
// Copyright (c) 2012, Technologic Systems, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
