#ifndef __libtsctl_h
#define __libtsctl_h
#include "System.h"
#include "LocalSystem.h"
#include "Bus.h"
#include "CAN.h"
#include "DIORaw.h"
#include "DIO.h"
#include "Pin.h"
#include "Time.h"
#include "TWI.h"
#include "SPI.h"
#include "AIO.h"
#include "EDIO.h"
#include "ts.h"
#include "Thread.h"
#include "arch.h"
//#include "Lock.h"
//#include "Net.h"

extern int ModelId;
extern int CANBusNum[];

#ifdef __cplusplus
extern "C" {
#endif
  System *SystemInit(int inst);
  Time *TimeInit(int inst);
  Bus *BusInit(int inst);
  Pin *PinInit(int inst);
  CAN *CANInit(int inst);
  DIORaw *DIORawInit(int inst);
  DIO *DIOInit(int inst);
  TWI *TWIInit(int inst);
  SPI *SPIInit(int inst);
  AIO *AIOInit(int inst);
  EDIO *EDIOInit(int inst);
#ifdef __cplusplus
}
#endif

#if 0
Time *Net_TimeInit(int inst,char *host,int mode);
Bus *Net_BusInit(int inst,char *host,int mode);
Pin *Net_PinInit(int inst,char *host,int mode);
CAN *Net_CANInit(int inst,char *host,int mode);
DIORaw *Net_DIORawInit(int inst,char *host,int mode);
DIO *Net_DIOInit(int inst,char *host,int mode);
TWI *Net_TWIInit(int inst,char *host,int mode);
SPI *Net_SPIInit(int inst,char *host,int mode);
AIO *Net_AIOInit(int inst,char *host,int mode);

#ifdef __cplusplus
extern "C" {
#endif
  void Net_TimeFini(void *);
  void Net_BusFini(void *);
  void Net_PinFini(void *);
  void Net_CANFini(void *);
  void Net_DIORawFini(void *);
  void Net_DIOFini(void *);
  void Net_TWIFini(void *);
  void Net_SPIFini(void *);
  void Net_AIOFini(void *);
#ifdef __cplusplus
}
#endif
#endif

#endif
// Author: Michael Schmidt (michael@embeddedARM.com)
// Copyright (c) 2012, Technologic Systems, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
