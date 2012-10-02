#ifndef NetLock_H
#define NetLock_H
#include "Lock.h"
#include "Packet.h"
typedef struct NetLock NetLock;

// each thread has a NetLock object for each server
struct ThreadNetLocks {
  unsigned count, max;
  NetLock **lock;
};

// Each thread gets a unique instance of NetLock
// All NetLocks share a single global PThreadLock
// We must hold a bitmap of locks which we currently hold
/* actually each connection gets a unique instance of NetLock.
   a NetLock instance can only be held by one thread.
   However a single thread can have multiple connections.
   We need to know all our connections on order to safely block on locking
 */
struct NetLock {
  LockAPI *API;
  int InitStatus;
  int inst;
  int socket;
  int mode;
  Packet *q;
  int *cmds;
  pthread_key_t tdata;
};

NetLock *NetLockInit(NetLock *lock,int socket,int inst,int mode,Packet *q,int *cmds);
void NetLockFini(NetLock *);
int NetLockLock(NetLock *,int command,unsigned num);

enum {
  NetLock_Lock=2
};

enum {
  NetLock_LockTry,
  NetLock_WaitLock,
  NetLock_DoRelease,
  NetLock_TmpReleaseAll,
  NetLock_ReacquireAll,
};

#endif
// Author: Michael Schmidt (michael@embeddedARM.com)
// Copyright (c) 2011, Technologic Systems, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
