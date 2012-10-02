#ifndef __ts4800Pin_H
#define __ts4800Pin_H
#include "Pin.h"
#include "Bus.h"

typedef struct ts4800Pin ts4800Pin;

struct ts4800Pin {
  Pin;
  Bus *bus;
};

void *ts4800PinInit(ts4800Pin *,void *syscon,void *dio1bus);
void ts4800PinFini(ts4800Pin *);
PinMode ts4800PinModeGet(ts4800Pin *,int pin);
int ts4800PinModeSet(ts4800Pin *,int pin,PinMode mode);
#endif
// Author: Michael Schmidt (michael@embeddedARM.com)
// Copyright (c) 2011, Technologic Systems, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
