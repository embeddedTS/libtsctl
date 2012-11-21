#ifndef __Bus_h
#define __Bus_h
#undef FUNC
#ifndef SWIGGY
#define FUNC(x) (*x)
#else
#define FUNC(x) x
#endif

typedef struct Bus Bus;
enum {
	NetBus_Lock=0,
	NetBus_Unlock=1,
	NetBus_Preempt=2,
	NetBus_Peek8=3,
	NetBus_Poke8=4,
	NetBus_Peek16=5,
	NetBus_Poke16=6,
	NetBus_Peek32=7,
	NetBus_Poke32=8,
	NetBus_BitGet8=9,
	NetBus_BitAssign8=10,
	NetBus_BitSet8=11,
	NetBus_BitClear8=12,
	NetBus_BitGet16=13,
	NetBus_BitAssign16=14,
	NetBus_BitSet16=15,
	NetBus_BitClear16=16,
	NetBus_BitGet32=17,
	NetBus_BitAssign32=18,
	NetBus_BitSet32=19,
	NetBus_BitClear32=20,
	NetBus_PeekStream=21,
	NetBus_PokeStream=22,
	NetBus_Refresh=23,
	NetBus_Commit=24,
	NetBus_BitToggle8=25,
	NetBus_BitToggle16=26,
	NetBus_BitToggle32=27,
	NetBus_Assign8X=28,
	NetBus_Assign16X=29,
	NetBus_Assign32X=30,
	NetBus_BitsGet8=31,
	NetBus_BitsGet16=32,
	NetBus_BitsGet32=33,
	XBus_APICount=34
};
struct Bus {
	void *FUNC(Init)(void *me,...);
	void FUNC(Fini)(void *me);
	int FUNC(Lock)(void *me,unsigned num,int flags);
	int FUNC(Unlock)(void *me,unsigned num,int flags);
	int FUNC(Preempt)(void *me);
	unsigned char FUNC(Peek8)(void *me,int Address);
	void FUNC(Poke8)(void *me,int Address,unsigned char Value);
	unsigned short FUNC(Peek16)(void *me,int Address);
	void FUNC(Poke16)(void *me,int Address,unsigned short Value);
	unsigned FUNC(Peek32)(void *me,int Address);
	void FUNC(Poke32)(void *me,int Address,unsigned Value);
	int FUNC(BitGet8)(void *me,int Address,int BitNumber);
	void FUNC(BitAssign8)(void *me,int Address,int BitNumber,int Value);
	void FUNC(BitSet8)(void *me,int Address,int BitNumber);
	void FUNC(BitClear8)(void *me,int Address,int BitNumber);
	int FUNC(BitGet16)(void *me,int Address,int BitNumber);
	void FUNC(BitAssign16)(void *me,int Address,int BitNumber,int Value);
	void FUNC(BitSet16)(void *me,int Address,int BitNumber);
	void FUNC(BitClear16)(void *me,int Address,int BitNumber);
	int FUNC(BitGet32)(void *me,int Address,int BitNumber);
	void FUNC(BitAssign32)(void *me,int Address,int BitNumber,int Value);
	void FUNC(BitSet32)(void *me,int Address,int BitNumber);
	void FUNC(BitClear32)(void *me,int Address,int BitNumber);
	void FUNC(PeekStream)(void *me,int address,int direction,char *dest);
	void FUNC(PokeStream)(void *me,int address,int direction,const char *data);
	void FUNC(Refresh)(void *me);
	void FUNC(Commit)(void *me,int ForceAll);
	int FUNC(BitToggle8)(void *me,int Address,int BitNumber);
	int FUNC(BitToggle16)(void *me,int Address,int BitNumber);
	int FUNC(BitToggle32)(void *me,int Address,int BitNumber);
	unsigned char FUNC(Assign8X)(void *me,int Address,int BitMSB,int BitLSB,int Value);
	unsigned short FUNC(Assign16X)(void *me,int Address,int BitMSB,int BitLSB,int Value);
	unsigned FUNC(Assign32X)(void *me,int Address,int BitMSB,int BitLSB,int Value);
	unsigned char FUNC(BitsGet8)(void *me,int Address,int BitMSB,int BitLSB);
	unsigned short FUNC(BitsGet16)(void *me,int Address,int BitMSB,int BitLSB);
	unsigned FUNC(BitsGet32)(void *me,int Address,int BitMSB,int BitLSB);
	int InitStatus;
	unsigned LockBase;
	int deferlockW;
	int deferlockR;
};
#endif

// Author: Michael Schmidt (michael@embeddedARM.com)
// Copyright (c) 2012, Technologic Systems, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
