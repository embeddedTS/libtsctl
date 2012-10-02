#ifndef __ts8900Pin_H
#define __ts8900Pin_H
#include "Pin.h"
#include "Bus.h"

typedef struct ts8900Pin ts8900Pin;

struct ts8900Pin {
  Pin;
  int deferlockR,deferlockW;
  Pin *parent;
  Bus *bus;
  int start;
};

void *ts8900PinInit(ts8900Pin *,void *parent,void *bus,int start);
void ts8900PinFini(ts8900Pin *);
PinMode ts8900PinModeGet(ts8900Pin *,int pin);
int ts8900PinModeSet(ts8900Pin *,int pin,PinMode mode);
#endif
// Author: Michael Schmidt (michael@embeddedARM.com)
// Copyright (c) 2012, Technologic Systems, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
