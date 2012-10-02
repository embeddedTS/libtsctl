#ifndef __GENERIC
#define __GENERIC
#include "cpp.h"
#ifndef type_null
#define type_null TEMPLATE(Type,Null)
#endif
#define FUNCTION(type,name) type TEMPLATE(MyType,name)

#define ArrayOffsetNormalize(arr,offset) \
  if (offset < 0) offset = ArrayLen0(arr) + offset;	\
  if (offset < 0) offset = 0;\
  if (offset >= ArrayLen0(arr)) offset = ArrayLen0(arr);

#define ArrayLen0(arr) (arr ? ((unsigned *)(arr))[-1] : 0)
#define ArrayLen(arr) (((unsigned *)(arr))[-1])
#define MPtr(arr) (arr ? (((unsigned *)(arr))-1) : 0)
#define APtr(Type,ptr) ((Type *)(((unsigned *)(ptr))+1))

#define NPTR (void *(*)(void *,void *))
#define PPTR (void (*)(void *))
#define CPTR (int (*)(const void *,const void *))

#define New(var,Type,...)  (*(var=(Type *)malloc(sizeof(Type))) =	\
			    (Type){ __VA_ARGS__ }, var)

// conflicts with Init function name
//#define Init(Type,...)  ((Type){ __VA_ARGS__ })

#define Free(ptr) free(MPtr(ptr))

#define S04(x) ((unsigned *)x)
#define S14(x) ((signed *)x)
#define S02(x) ((unsigned short *)x)
#define S12(x) ((short *)x)
#define S01(x) ((unsigned char *)x)
#define S11(x) ((char *)x)

typedef int Boolean;
typedef char Int8;
typedef short Int16;
typedef int Int32;
typedef long long Int64;
typedef unsigned char UInt8;
typedef unsigned short UInt16;
typedef unsigned int UInt32;
typedef unsigned long long UInt64;
static const int True = 1, False = 0;
#endif

// Author: Michael Schmidt (michael@embeddedARM.com)
// Copyright (c) 2011, Technologic Systems, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
