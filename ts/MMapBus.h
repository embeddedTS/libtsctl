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
	unsigned char FUNC(Peek8)(MMapBus *me,int Address);
	void FUNC(Poke8)(MMapBus *me,int Address,unsigned char Value);
	unsigned short FUNC(Peek16)(MMapBus *me,int Address);
	void FUNC(Poke16)(MMapBus *me,int Address,unsigned short Value);
	unsigned FUNC(Peek32)(MMapBus *me,int Address);
	void FUNC(Poke32)(MMapBus *me,int Address,unsigned Value);
	int FUNC(BitGet8)(MMapBus *me,int Address,int BitNumber);
	void FUNC(BitAssign8)(MMapBus *me,int Address,int BitNumber,int Value);
	void FUNC(BitSet8)(MMapBus *me,int Address,int BitNumber);
	void FUNC(BitClear8)(MMapBus *me,int Address,int BitNumber);
	int FUNC(BitGet16)(MMapBus *me,int Address,int BitNumber);
	void FUNC(BitAssign16)(MMapBus *me,int Address,int BitNumber,int Value);
	void FUNC(BitSet16)(MMapBus *me,int Address,int BitNumber);
	void FUNC(BitClear16)(MMapBus *me,int Address,int BitNumber);
	int FUNC(BitGet32)(MMapBus *me,int Address,int BitNumber);
	void FUNC(BitAssign32)(MMapBus *me,int Address,int BitNumber,int Value);
	void FUNC(BitSet32)(MMapBus *me,int Address,int BitNumber);
	void FUNC(BitClear32)(MMapBus *me,int Address,int BitNumber);
	void FUNC(PeekStream)(MMapBus *me,int address,int direction,char *dest);
	void FUNC(PokeStream)(MMapBus *me,int address,int direction,const char *data);
	void FUNC(Refresh)(MMapBus *me);
	void FUNC(Commit)(MMapBus *me,int ForceAll);
	int FUNC(BitToggle8)(MMapBus *me,int Address,int BitNumber);
	int FUNC(BitToggle16)(MMapBus *me,int Address,int BitNumber);
	int FUNC(BitToggle32)(MMapBus *me,int Address,int BitNumber);
	unsigned char FUNC(Assign8X)(MMapBus *me,int Address,int BitMSB,int BitLSB,int Value);
	unsigned short FUNC(Assign16X)(MMapBus *me,int Address,int BitMSB,int BitLSB,int Value);
	unsigned FUNC(Assign32X)(MMapBus *me,int Address,int BitMSB,int BitLSB,int Value);
	unsigned char FUNC(BitsGet8)(MMapBus *me,int Address,int BitMSB,int BitLSB);
	unsigned short FUNC(BitsGet16)(MMapBus *me,int Address,int BitMSB,int BitLSB);
	unsigned FUNC(BitsGet32)(MMapBus *me,int Address,int BitMSB,int BitLSB);
	int InitStatus;
	unsigned LockBase;
	int deferlockW;
	int deferlockR;
  volatile char *Mem,*Mem16;
};

void *MMapBusInit(MMapBus* ob,int MMapBase,int Pages);
void *MMapBusInit2(void *bus0,void *mem,int Pages);
void *MMapBusInit3(MMapBus *bus0,int MemBase8,int MemBase16,int Pages);
void MMapBusFini(MMapBus* ob);
int MMapBusLock(MMapBus* ob,unsigned num,int flags);
int MMapBusUnlock(MMapBus* ob,unsigned num,int flags);
int MMapBusPreempt(MMapBus* ob);
unsigned char MMapBusPeek8(MMapBus* ob,int Address);
void MMapBusPoke8(MMapBus* ob,int Address,unsigned char Value);
unsigned short MMapBusPeek16(MMapBus* ob,int Address);
void MMapBusPoke16(MMapBus* ob,int Address,unsigned short Value);
unsigned MMapBusPeek32(MMapBus* ob,int Address);
void MMapBusPoke32(MMapBus* ob,int Address,unsigned Value);
int MMapBusBitGet8(MMapBus* ob,int Address,int BitNumber);
void MMapBusBitAssign8(MMapBus* ob,int Address,int BitNumber,int Value);
void MMapBusBitSet8(MMapBus* ob,int Address,int BitNumber);
void MMapBusBitClear8(MMapBus* ob,int Address,int BitNumber);
int MMapBusBitGet16(MMapBus* ob,int Address,int BitNumber);
void MMapBusBitAssign16(MMapBus* ob,int Address,int BitNumber,int Value);
void MMapBusBitSet16(MMapBus* ob,int Address,int BitNumber);
void MMapBusBitClear16(MMapBus* ob,int Address,int BitNumber);
int MMapBusBitGet32(MMapBus* ob,int Address,int BitNumber);
void MMapBusBitAssign32(MMapBus* ob,int Address,int BitNumber,int Value);
void MMapBusBitSet32(MMapBus* ob,int Address,int BitNumber);
void MMapBusBitClear32(MMapBus* ob,int Address,int BitNumber);
void MMapBusPeekStream(MMapBus* ob,int address,int direction,char *dest);
void MMapBusPokeStream(MMapBus* ob,int address,int direction,const char *data);
void MMapBusRefresh(MMapBus* ob);
void MMapBusCommit(MMapBus* ob,int ForceAll);
int MMapBusBitToggle8(MMapBus* ob,int Address,int BitNumber);
int MMapBusBitToggle16(MMapBus* ob,int Address,int BitNumber);
int MMapBusBitToggle32(MMapBus* ob,int Address,int BitNumber);
unsigned char MMapBusAssign8X(MMapBus* ob,int Address,int BitMSB,int BitLSB,int Value);
unsigned short MMapBusAssign16X(MMapBus* ob,int Address,int BitMSB,int BitLSB,int Value);
unsigned MMapBusAssign32X(MMapBus* ob,int Address,int BitMSB,int BitLSB,int Value);
unsigned char MMapBusBitsGet8(MMapBus* ob,int Address,int BitMSB,int BitLSB);
unsigned short MMapBusBitsGet16(MMapBus* ob,int Address,int BitMSB,int BitLSB);
unsigned MMapBusBitsGet32(MMapBus* ob,int Address,int BitMSB,int BitLSB);
#endif

// Author: Michael Schmidt (michael@embeddedARM.com)
// Copyright (c) 2012, Technologic Systems, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
