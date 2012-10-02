#ifndef __ts4700Pin_H
#define __ts4700Pin_H
#include "Pin.h"
#include "Bus.h"

typedef struct ts4700Pin ts4700Pin;

struct ts4700Pin {
  Pin;
  Bus *diobus,*mfpbus;
};

void *ts4700PinInit(ts4700Pin *,void *diobus,void *mfpbus);
void ts4700PinFini(ts4700Pin *);
PinMode ts4700PinModeGet(ts4700Pin *,int pin);
int ts4700PinModeSet(ts4700Pin *,int pin,PinMode mode);
#endif
// Author: Michael Schmidt (michael@embeddedARM.com)
// Copyright (c) 2011, Technologic Systems, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
