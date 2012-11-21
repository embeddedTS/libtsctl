#ifndef __CacheBus_h
#define __CacheBus_h
#undef FUNC
#ifndef SWIGGY
#define FUNC(x) (*x)
#else
#define FUNC(x) x
#endif

typedef struct CacheBus CacheBus;
typedef enum CacheBusError{
  CacheBusErrorWidthInvalid=-100
}CacheBusError;

struct CacheBus {
	void *FUNC(Init)(CacheBus *me,void *bus1);
	void FUNC(Fini)(CacheBus *me);
	int FUNC(Lock)(CacheBus *me,unsigned num,int flags);
	int FUNC(Unlock)(CacheBus *me,unsigned num,int flags);
	int FUNC(Preempt)(CacheBus *me);
	unsigned char FUNC(Peek8)(CacheBus *me,int Address);
	void FUNC(Poke8)(CacheBus *me,int Address,unsigned char Value);
	unsigned short FUNC(Peek16)(CacheBus *me,int Address);
	void FUNC(Poke16)(CacheBus *me,int Address,unsigned short Value);
	unsigned FUNC(Peek32)(CacheBus *me,int Address);
	void FUNC(Poke32)(CacheBus *me,int Address,unsigned Value);
	int FUNC(BitGet8)(CacheBus *me,int Address,int BitNumber);
	void FUNC(BitAssign8)(CacheBus *me,int Address,int BitNumber,int Value);
	void FUNC(BitSet8)(CacheBus *me,int Address,int BitNumber);
	void FUNC(BitClear8)(CacheBus *me,int Address,int BitNumber);
	int FUNC(BitGet16)(CacheBus *me,int Address,int BitNumber);
	void FUNC(BitAssign16)(CacheBus *me,int Address,int BitNumber,int Value);
	void FUNC(BitSet16)(CacheBus *me,int Address,int BitNumber);
	void FUNC(BitClear16)(CacheBus *me,int Address,int BitNumber);
	int FUNC(BitGet32)(CacheBus *me,int Address,int BitNumber);
	void FUNC(BitAssign32)(CacheBus *me,int Address,int BitNumber,int Value);
	void FUNC(BitSet32)(CacheBus *me,int Address,int BitNumber);
	void FUNC(BitClear32)(CacheBus *me,int Address,int BitNumber);
	void FUNC(PeekStream)(CacheBus *me,int address,int direction,char *dest);
	void FUNC(PokeStream)(CacheBus *me,int address,int direction,const char *data);
	void FUNC(Refresh)(CacheBus *me);
	void FUNC(Commit)(CacheBus *me,int ForceAll);
	int FUNC(BitToggle8)(CacheBus *me,int Address,int BitNumber);
	int FUNC(BitToggle16)(CacheBus *me,int Address,int BitNumber);
	int FUNC(BitToggle32)(CacheBus *me,int Address,int BitNumber);
	unsigned char FUNC(Assign8X)(CacheBus *me,int Address,int BitMSB,int BitLSB,int Value);
	unsigned short FUNC(Assign16X)(CacheBus *me,int Address,int BitMSB,int BitLSB,int Value);
	unsigned FUNC(Assign32X)(CacheBus *me,int Address,int BitMSB,int BitLSB,int Value);
	unsigned char FUNC(BitsGet8)(CacheBus *me,int Address,int BitMSB,int BitLSB);
	unsigned short FUNC(BitsGet16)(CacheBus *me,int Address,int BitMSB,int BitLSB);
	unsigned FUNC(BitsGet32)(CacheBus *me,int Address,int BitMSB,int BitLSB);
	int InitStatus;
	unsigned LockBase;
	int deferlockW;
	int deferlockR;
	Bus *sub;
	unsigned Length;
	unsigned Width;
	unsigned Offset;
	unsigned *icache;
	unsigned *ocache;
	unsigned *ocache0;
	unsigned *WO;
	unsigned *IBit;
	unsigned *OBit;
};

void *CacheBusInit(CacheBus* ob,void *bus1);
void CacheBusFini(CacheBus* ob);
int CacheBusLock(CacheBus* ob,unsigned num,int flags);
int CacheBusUnlock(CacheBus* ob,unsigned num,int flags);
int CacheBusPreempt(CacheBus* ob);
unsigned char CacheBusPeek8(CacheBus* ob,int Address);
void CacheBusPoke8(CacheBus* ob,int Address,unsigned char Value);
unsigned short CacheBusPeek16(CacheBus* ob,int Address);
void CacheBusPoke16(CacheBus* ob,int Address,unsigned short Value);
unsigned CacheBusPeek32(CacheBus* ob,int Address);
void CacheBusPoke32(CacheBus* ob,int Address,unsigned Value);
int CacheBusBitGet8(CacheBus* ob,int Address,int BitNumber);
void CacheBusBitAssign8(CacheBus* ob,int Address,int BitNumber,int Value);
void CacheBusBitSet8(CacheBus* ob,int Address,int BitNumber);
void CacheBusBitClear8(CacheBus* ob,int Address,int BitNumber);
int CacheBusBitGet16(CacheBus* ob,int Address,int BitNumber);
void CacheBusBitAssign16(CacheBus* ob,int Address,int BitNumber,int Value);
void CacheBusBitSet16(CacheBus* ob,int Address,int BitNumber);
void CacheBusBitClear16(CacheBus* ob,int Address,int BitNumber);
int CacheBusBitGet32(CacheBus* ob,int Address,int BitNumber);
void CacheBusBitAssign32(CacheBus* ob,int Address,int BitNumber,int Value);
void CacheBusBitSet32(CacheBus* ob,int Address,int BitNumber);
void CacheBusBitClear32(CacheBus* ob,int Address,int BitNumber);
void CacheBusPeekStream(CacheBus* ob,int address,int direction,char *dest);
void CacheBusPokeStream(CacheBus* ob,int address,int direction,const char *data);
void CacheBusRefresh(CacheBus* ob);
void CacheBusCommit(CacheBus* ob,int ForceAll);
int CacheBusBitToggle8(CacheBus* ob,int Address,int BitNumber);
int CacheBusBitToggle16(CacheBus* ob,int Address,int BitNumber);
int CacheBusBitToggle32(CacheBus* ob,int Address,int BitNumber);
unsigned char CacheBusAssign8X(CacheBus* ob,int Address,int BitMSB,int BitLSB,int Value);
unsigned short CacheBusAssign16X(CacheBus* ob,int Address,int BitMSB,int BitLSB,int Value);
unsigned CacheBusAssign32X(CacheBus* ob,int Address,int BitMSB,int BitLSB,int Value);
unsigned char CacheBusBitsGet8(CacheBus* ob,int Address,int BitMSB,int BitLSB);
unsigned short CacheBusBitsGet16(CacheBus* ob,int Address,int BitMSB,int BitLSB);
unsigned CacheBusBitsGet32(CacheBus* ob,int Address,int BitMSB,int BitLSB);
#endif

// Author: Michael Schmidt (michael@embeddedARM.com)
// Copyright (c) 2012, Technologic Systems, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
