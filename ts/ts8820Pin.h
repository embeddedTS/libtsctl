#ifndef __ts8820Pin_H
#define __ts8820Pin_H
#include "Pin.h"
#include "Bus.h"

typedef struct ts8820Pin ts8820Pin;

struct ts8820Pin {
  Pin;
  int deferlockR,deferlockW;
  Pin *parent;
  Bus *bus;
  int start;
};

void *ts8820PinInit(ts8820Pin *,void *parent,void *bus,int start);
void ts8820PinFini(ts8820Pin *);
PinMode ts8820PinModeGet(ts8820Pin *,int pin);
int ts8820PinModeSet(ts8820Pin *,int pin,PinMode mode);
#endif
// Author: Michael Schmidt (michael@embeddedARM.com)
// Copyright (c) 2012, Technologic Systems, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
