#ifndef __linux86_h
#define __linux86_h
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
extern LockInfo globallockinfo[];
extern PThreadLock globallock;
extern Lock *lock;
extern int CANBusNum[];
extern pthread_key_t tdata;

Time *TimeInit(int inst);
Bus *BusInit(int inst);
Pin *PinInit(int inst);
CAN *CANInit(int inst);
DIORaw *DIORawInit(int inst);
DIO *DIOInit(int inst);
TWI *TWIInit(int inst);
SPI *SPIInit(int inst);
AIO *AIOInit(int inst);
#endif
// Author: Michael Schmidt (michael@embeddedARM.com)
// Copyright (c) 2012, Technologic Systems, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
