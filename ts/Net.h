#ifndef __Net_H
#define __Net_H
#include "Packet.h"

#undef FUNC
#ifndef SWIGGY
#define FUNC(x) (*x) 
#else
#define FUNC(x) x
#endif

enum {
  NetModeBlocking=0, // all calls block until server returns completion
  NetModeNonBlocking=1, // calls to functions return void return immediately
  NetModeQueued=2 // we don't send commands to server until 
  // function returning non-void is called.
  // caller is responsible for making sure it doesn't queue too many
  // commands (and run out of transmit buffer space)
};

enum {
  NetSystemClass = 0,
  NetBusClass = 1,
  NetTimeClass = 2,
  NetPinClass = 3,
  NetDIORawClass = 4,
  NetDIOClass = 5,
  NetTWIClass = 6,
  NetCANClass = 7,
  NetSPIClass = 8,
  NetAIOClass = 9,
  NetEDIOClass = 10
};
#define Net_ClassCount (NetSPIClass+1)

typedef struct Net Net;
typedef struct NetAPI NetAPI;

struct NetAPI {
  void *FUNC(Init)(void *me,...);
  void FUNC(Fini)(void *me);
};

struct Net {
  NetAPI;
  int InitStatus;
  int inst;
  int socket;
  int mode;
  Packet *q;
  int *cmds;
};

static inline void PacketPushCmd(Packet *req,int cmd,void *net0,int theclass) {
  Net *net = net0;
  PacketPush8(req,cmd);
  PacketPush8(req,net->inst);
  PacketPush16(req,theclass);
}

int ClientSocketNew(char *host,int port);

#endif
// Author: Michael Schmidt (michael@embeddedARM.com)
// Copyright (c) 2011, Technologic Systems, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
