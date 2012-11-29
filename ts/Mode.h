#ifndef __Mode_h
#define __Mode_h
#undef FUNC
#ifndef SWIGGY
#define FUNC(x) (*x)
#else
#define FUNC(x) x
#endif

typedef struct Mode Mode;
enum {
	NetMode_JSON=0,
	NetMode_Assign=1,
	NetMode_NoAssign=2,
	NetMode_Hex=3,
	NetMode_Dec=4,
	NetMode_Oct=5,
	NetMode_AStr=6,
	NetMode_AHex=7,
	NetMode_ADec=8,
	NetMode_AOct=9,
	NetMode_ABinOct=10,
	NetMode_ABinHex=11,
	NetMode_ABinUni=12,
	XMode_APICount=13
};
struct Mode {
	void *FUNC(Init)(void *me,...);
	void FUNC(Fini)(void *me);
	void FUNC(JSON)(void *me);
	void FUNC(Assign)(void *me);
	void FUNC(NoAssign)(void *me);
	void FUNC(Hex)(void *me);
	void FUNC(Dec)(void *me);
	void FUNC(Oct)(void *me);
	void FUNC(AStr)(void *me);
	void FUNC(AHex)(void *me);
	void FUNC(ADec)(void *me);
	void FUNC(AOct)(void *me);
	void FUNC(ABinOct)(void *me);
	void FUNC(ABinHex)(void *me);
	void FUNC(ABinUni)(void *me);
};
#endif

// Author: Michael Schmidt (michael@embeddedARM.com)
// Copyright (c) 2012, Technologic Systems, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
