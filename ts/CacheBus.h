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
	unsigned char FUNC(Peek8)(CacheBus *me,int adrs);
	void FUNC(Poke8)(CacheBus *me,int adrs,unsigned char val);
	unsigned short FUNC(Peek16)(CacheBus *me,int adrs);
	void FUNC(Poke16)(CacheBus *me,int adrs,unsigned short val);
	unsigned FUNC(Peek32)(CacheBus *me,int adrs);
	void FUNC(Poke32)(CacheBus *me,int adrs,unsigned val);
	int FUNC(BitGet8)(CacheBus *me,int adrs,int bit);
	void FUNC(BitAssign8)(CacheBus *me,int adrs,int bit,int val);
	void FUNC(BitSet8)(CacheBus *me,int adrs,int bit);
	void FUNC(BitClear8)(CacheBus *me,int adrs,int bit);
	int FUNC(BitGet16)(CacheBus *me,int adrs,int bit);
	void FUNC(BitAssign16)(CacheBus *me,int adrs,int bit,int val);
	void FUNC(BitSet16)(CacheBus *me,int adrs,int bit);
	void FUNC(BitClear16)(CacheBus *me,int adrs,int bit);
	int FUNC(BitGet32)(CacheBus *me,int adrs,int bit);
	void FUNC(BitAssign32)(CacheBus *me,int adrs,int bit,int val);
	void FUNC(BitSet32)(CacheBus *me,int adrs,int bit);
	void FUNC(BitClear32)(CacheBus *me,int adrs,int bit);
	void FUNC(PeekStream)(CacheBus *me,int address,int direction,char *dest);
	void FUNC(PokeStream)(CacheBus *me,int address,int direction,const char *data);
	void FUNC(Refresh)(CacheBus *me);
	void FUNC(Commit)(CacheBus *me,int forceall);
	int FUNC(BitToggle8)(CacheBus *me,int adrs,int bit);
	int FUNC(BitToggle16)(CacheBus *me,int adrs,int bit);
	int FUNC(BitToggle32)(CacheBus *me,int adrs,int bit);
	unsigned char FUNC(Assign8X)(CacheBus *me,int adrs,int bit1,int bit0,int val);
	unsigned short FUNC(Assign16X)(CacheBus *me,int adrs,int bit1,int bit0,int val);
	unsigned FUNC(Assign32X)(CacheBus *me,int adrs,int bit1,int bit0,int val);
	unsigned char FUNC(BitsGet8)(CacheBus *me,int adrs,int bit1,int bit0);
	unsigned short FUNC(BitsGet16)(CacheBus *me,int adrs,int bit1,int bit0);
	unsigned FUNC(BitsGet32)(CacheBus *me,int adrs,int bit1,int bit0);
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
unsigned char CacheBusPeek8(CacheBus* ob,int adrs);
void CacheBusPoke8(CacheBus* ob,int adrs,unsigned char val);
unsigned short CacheBusPeek16(CacheBus* ob,int adrs);
void CacheBusPoke16(CacheBus* ob,int adrs,unsigned short val);
unsigned CacheBusPeek32(CacheBus* ob,int adrs);
void CacheBusPoke32(CacheBus* ob,int adrs,unsigned val);
int CacheBusBitGet8(CacheBus* ob,int adrs,int bit);
void CacheBusBitAssign8(CacheBus* ob,int adrs,int bit,int val);
void CacheBusBitSet8(CacheBus* ob,int adrs,int bit);
void CacheBusBitClear8(CacheBus* ob,int adrs,int bit);
int CacheBusBitGet16(CacheBus* ob,int adrs,int bit);
void CacheBusBitAssign16(CacheBus* ob,int adrs,int bit,int val);
void CacheBusBitSet16(CacheBus* ob,int adrs,int bit);
void CacheBusBitClear16(CacheBus* ob,int adrs,int bit);
int CacheBusBitGet32(CacheBus* ob,int adrs,int bit);
void CacheBusBitAssign32(CacheBus* ob,int adrs,int bit,int val);
void CacheBusBitSet32(CacheBus* ob,int adrs,int bit);
void CacheBusBitClear32(CacheBus* ob,int adrs,int bit);
void CacheBusPeekStream(CacheBus* ob,int address,int direction,char *dest);
void CacheBusPokeStream(CacheBus* ob,int address,int direction,const char *data);
void CacheBusRefresh(CacheBus* ob);
void CacheBusCommit(CacheBus* ob,int forceall);
int CacheBusBitToggle8(CacheBus* ob,int adrs,int bit);
int CacheBusBitToggle16(CacheBus* ob,int adrs,int bit);
int CacheBusBitToggle32(CacheBus* ob,int adrs,int bit);
unsigned char CacheBusAssign8X(CacheBus* ob,int adrs,int bit1,int bit0,int val);
unsigned short CacheBusAssign16X(CacheBus* ob,int adrs,int bit1,int bit0,int val);
unsigned CacheBusAssign32X(CacheBus* ob,int adrs,int bit1,int bit0,int val);
unsigned char CacheBusBitsGet8(CacheBus* ob,int adrs,int bit1,int bit0);
unsigned short CacheBusBitsGet16(CacheBus* ob,int adrs,int bit1,int bit0);
unsigned CacheBusBitsGet32(CacheBus* ob,int adrs,int bit1,int bit0);
#endif

// Author: Michael Schmidt (michael@embeddedARM.com)
// Copyright (c) 2012, Technologic Systems, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
