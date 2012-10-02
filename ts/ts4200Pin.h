#ifndef __ts4200Pin_H
#define __ts4200Pin_H
#include "Pin.h"
#include "Bus.h"

typedef struct ts4200Pin ts4200Pin;

struct ts4200Pin {
  Pin;
  Bus *syscon,*piob,*pmc,*pioc;
};

void *ts4200PinInit(ts4200Pin *,void *bus,void *busb,void *buspmc,void *busc);
void ts4200PinFini(ts4200Pin *);
PinMode ts4200PinModeGet(ts4200Pin *,int pin);
int ts4200PinModeSet(ts4200Pin *,int pin,PinMode mode);
#endif
// Author: Michael Schmidt (michael@embeddedARM.com)
// Copyright (c) 2012, Technologic Systems, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
