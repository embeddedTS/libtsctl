#ifndef __ts81x0Pin_H
#define __ts81x0Pin_H
#include "Pin.h"
#include "Bus.h"

typedef struct ts81x0Pin ts81x0Pin;

struct ts81x0Pin {
  Pin;
  int deferlockR,deferlockW;
  Pin *parent;
  Bus *bus;
  int CAN_TX1,CAN_TX2,CAN_RX1,CAN_RX2;
};

void *ts81x0PinInit(ts81x0Pin *,void *parent,void *bus);
void ts81x0PinPostInit(ts81x0Pin *,int CAN_TX1,int CAN_TX2,int CAN_RX1,int CAN_RX2);
void ts81x0PinFini(ts81x0Pin *);
PinMode ts81x0PinModeGet(ts81x0Pin *,int pin);
int ts81x0PinModeSet(ts81x0Pin *,int pin,PinMode mode);
#endif
// Author: Michael Schmidt (michael@embeddedARM.com)
// Copyright (c) 2012, Technologic Systems, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
