#ifndef __TS4500_h
#define __TS4500_h
#include "Time.h"
#include "Bus.h"
#include "Pin.h"
#include "CAN.h"
#include "DIORaw.h"
#include "DIO.h"
#include "TWI.h"
#include "SPI.h"
#include "AIO.h"

extern int ModelId;
extern int CANBusNum[];

Time *TimeInit1(int inst);
Bus *BusInit1(int inst);
Pin *PinInit1(int inst);
CAN *CANInit1(int inst);
DIORaw *DIORawInit1(int inst);
DIO *DIOInit1(int inst);
TWI *TWIInit1(int inst);
SPI *SPIInit1(int inst);
AIO *AIOInit1(int inst);
#endif
// Author: Michael Schmidt (michael@embeddedARM.com)
// Copyright (c) 2011, Technologic Systems, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
