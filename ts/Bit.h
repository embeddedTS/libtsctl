#ifdef MUTEX_PROTECT_BITS
#define DefinitionFunctionsBit(BusName,Type,Width)			\
  Type BusName##Peek##Width(BusName *bus,int adrs) { \
    return _##BusName##Peek##Width(bus,adrs);				\
  }									\
									\
  void BusName##Poke##Width(BusName *bus,int adrs,Type val) { \
    MUTEX_LOCK(bus->mutex);						\
    _##BusName##Poke##Width(bus,adrs,val);				\
    MUTEX_UNLOCK(bus->mutex);						\
  }									\
									\
  void BusName##BitAssign##Width(BusName *bus,int adrs,int bit,int val) { \
    MUTEX_LOCK(bus->mutex);						\
    if (val) {								\
      _##BusName##Poke##Width(bus,adrs,_##BusName##Peek##Width(bus,adrs) | (1<<bit));	\
    } else {								\
      _##BusName##Poke##Width(bus,adrs,_##BusName##Peek##Width(bus,adrs) & ~(1<<bit));	\
    }									\
    MUTEX_UNLOCK(bus->mutex);						\
  }									\
									\
  int BusName##BitGet##Width(BusName *bus,int adrs,int bit) { \
    return (_##BusName##Peek##Width(bus,adrs) & (1<<bit)) ? 1 : 0;	\
  }									\
									\
  void BusName##BitSet##Width(BusName *bus,int adrs,int bit) { \
    MUTEX_LOCK(bus->mutex);						\
    _##BusName##Poke##Width(bus,adrs,_##BusName##Peek##Width(bus,adrs) | (1<<bit));	\
    MUTEX_UNLOCK(bus->mutex);						\
  }									\
									\
  int BusName##BitToggle##Width(BusName *bus,int adrs,int bit) {	\
    int val,ret;							\
    MUTEX_LOCK(bus->mutex);						\
    val = _##BusName##Peek##Width(bus,adrs);				\
    if (val & (1<<bit)) {						\
      val &= ~(1<<bit);							\
      ret = 0;								\
    } else {								\
      val |= (1<<bit);							\
      ret = 1;								\
    }									\
    _##BusName##Poke##Width(bus,adrs,val);				\
    MUTEX_UNLOCK(bus->mutex);						\
    return ret;								\
  }									\
									\
  void BusName##BitClear##Width(BusName *bus,int adrs,int bit) {	\
    MUTEX_LOCK(bus->mutex);						\
    _##BusName##Poke##Width(bus,adrs,_##BusName##Peek##Width(bus,adrs) & ~(1<<bit));	\
    MUTEX_UNLOCK(bus->mutex);						\
  }									\
									\
  Type BusName##Assign##Width##X(BusName *bus,int adrs,int bit1,int bit0,int val) {\
    int value,mask;							\
    MUTEX_LOCK(bus->mutex);						\
    value = _##BusName##Peek##Width(bus,adrs);				\
    mask = ((1 << bit1+1) - 1) & ~((1 << bit0) - 1);			\
    value &= ~mask;							\
    value |= (val << bit0) & mask;					\
    _##BusName##Poke##Width(bus,adrs,value);				\
    MUTEX_UNLOCK(bus->mutex);						\
    return value;							\
  }									\
									\
  Type BusName##BitsGet##Width(BusName *bus,int adrs,int bit1,int bit0) { \
    int value,mask;							\
    MUTEX_LOCK(bus->mutex);						\
    value = _##BusName##Peek##Width(bus,adrs);				\
    mask = ((1 << bit1+1) - 1) & ~((1 << bit0) - 1);			\
    MUTEX_UNLOCK(bus->mutex);						\
    value = (value & mask) >> bit0;					\
    return value;							\
  }
#else
#define DefinitionFunctionsBit(BusName,Type,Width)			\
  Type BusName##Peek##Width(BusName *bus,int adrs) { \
    return _##BusName##Peek##Width(bus,adrs);				\
  }									\
									\
  void BusName##Poke##Width(BusName *bus,int adrs,Type val) { \
    _##BusName##Poke##Width(bus,adrs,val);				\
  }									\
									\
  void BusName##BitAssign##Width(BusName *bus,int adrs,int bit,int val) { \
    if (val) {								\
      _##BusName##Poke##Width(bus,adrs,_##BusName##Peek##Width(bus,adrs) | (1<<bit));	\
    } else {								\
      _##BusName##Poke##Width(bus,adrs,_##BusName##Peek##Width(bus,adrs) & ~(1<<bit));	\
    }									\
  }									\
									\
  int BusName##BitGet##Width(BusName *bus,int adrs,int bit) { \
    return (_##BusName##Peek##Width(bus,adrs) & (1<<bit)) ? 1 : 0;	\
  }									\
									\
  void BusName##BitSet##Width(BusName *bus,int adrs,int bit) { \
    _##BusName##Poke##Width(bus,adrs,_##BusName##Peek##Width(bus,adrs) | (1<<bit));	\
  }									\
									\
  int BusName##BitToggle##Width(BusName *bus,int adrs,int bit) {	\
    int val,ret;							\
    val = _##BusName##Peek##Width(bus,adrs);				\
    if (val & (1<<bit)) {						\
      val &= ~(1<<bit);							\
      ret = 0;								\
    } else {								\
      val |= (1<<bit);							\
      ret = 1;								\
    }									\
    _##BusName##Poke##Width(bus,adrs,val);				\
    return ret;								\
  }									\
									\
  void BusName##BitClear##Width(BusName *bus,int adrs,int bit) {	\
    _##BusName##Poke##Width(bus,adrs,_##BusName##Peek##Width(bus,adrs) & ~(1<<bit)); \
  }									\
									\
  Type BusName##Assign##Width##X(BusName *bus,int adrs,int bit1,int bit0,int val) {\
    int value,mask;							\
    value = _##BusName##Peek##Width(bus,adrs);				\
    mask = ((1 << bit1+1) - 1) & ~((1 << bit0) - 1);			\
    value &= ~mask;							\
    value |= (val << bit0) & mask;					\
    _##BusName##Poke##Width(bus,adrs,value);				\
    return value;							\
  }									\
									\
  Type BusName##BitsGet##Width(BusName *bus,int adrs,int bit1,int bit0) {	\
    int value,mask;							\
    value = _##BusName##Peek##Width(bus,adrs);				\
    mask = ((1 << bit1+1) - 1) & ~((1 << bit0) - 1);			\
    return (value & mask) >> bit0;					\
  }

#endif
// Author: Michael Schmidt (michael@embeddedARM.com)
// Copyright (c) 2011, Technologic Systems, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
