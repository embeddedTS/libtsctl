#ifndef __ts4500Pin_H
#define __ts4500Pin_H
#include "Pin.h"
#include "Bus.h"

typedef struct ts4500Pin ts4500Pin;

struct ts4500Pin {
  Pin;
  Bus *sbus,*cpubus,*confbus;
  int confadrs;
};

void *ts4500PinInit(ts4500Pin *,void *sbus,void *cpubus,void *confbus,int confadrs);
void ts4500PinFini(ts4500Pin *);
PinMode ts4500PinModeGet(ts4500Pin *,int pin);
int ts4500PinModeSet(ts4500Pin *,int pin,PinMode mode);
#endif
// Author: Michael Schmidt (michael@embeddedARM.com)
// Copyright (c) 2012, Technologic Systems, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
