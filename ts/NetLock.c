#include "NetLock.h"
#define __USE_GNU
#include <pthread.h>

static LockAPI NetLockAPI = {
  .Init = (void *)NetLockInit,
  .Fini = (void *)NetLockFini,
  .Lock = (void *)NetLockLock,
};

NetLock *NetLockInit(NetLock *lock,int socket,int inst,int mode,Packet *q,int *cmds) {
  if (lock->InitStatus > 0) return lock;
  lock->API = &NetLockAPI;
  
  lock->inst = inst;
  lock->socket = socket;
  lock->InitStatus = lock->socket >= 0 ? 1 : -1;
  lock->mode = mode;
  lock->q = q;
  lock->cmds = cmds;
  return lock;
}

void NetLockFini(NetLock *lock){
  if (lock->InitStatus > 0) lock->InitStatus = 0;
}

static inline int _NetLockLockTry(NetLock *lock,unsigned num) {
  PacketPushCmd(lock->q,NetLock_Lock,lock,NetLockClass);
  PacketPush32(lock->q,NetLock_LockTry);
  PacketPush32(lock->q,num);
  return DoCmd(lock->q,lock,1); 
}

static inline int _NetLockWaitLock(NetLock *lock,unsigned num) {
  PacketPushCmd(lock->q,NetLock_Lock,lock,NetLockClass);
  PacketPush32(lock->q,NetLock_WaitLock);
  PacketPush32(lock->q,num);
  return DoCmd(lock->q,lock,1); 
}

static inline int _NetLockDoRelease(NetLock *lock,unsigned num) {
  PacketPushCmd(lock->q,NetLock_Lock,lock,NetLockClass);
  PacketPush32(lock->q,NetLock_DoRelease);
  PacketPush32(lock->q,num);
  return DoCmd(lock->q,lock,1); 
}

static inline int _NetLockTmpReleaseAll(NetLock *lock) {
  PacketPushCmd(lock->q,NetLock_Lock,lock,NetLockClass);
  PacketPush32(lock->q,NetLock_TmpReleaseAll);
  return DoCmd(lock->q,lock,1); 
}

static inline int _NetLockReacquireAll(NetLock *lock) {
  PacketPushCmd(lock->q,NetLock_Lock,lock,NetLockClass);
  PacketPush32(lock->q,NetLock_ReacquireAll);
  return DoCmd(lock->q,lock,1); 
}

// release all locks on all connections
static int _NetLockUnlockAll(NetLock *lock) {
  struct ThreadNetLocks *th = pthread_getspecific(lock->tdata);
  int i;

  for (i=0;i<th->count;i++) {
    _NetLockTmpReleaseAll(th->lock[i]);
  }
}

// re-aquire all locks on all connections
static int _NetLockLockAll(NetLock *lock) {
  struct ThreadNetLocks *th = pthread_getspecific(lock->tdata);
  int i;

  for (i=0;i<th->count;i++) {
    _NetLockReacquireAll(th->lock[i]);
  }
}

int NetLockLock(NetLock *lock,int command,unsigned num){
  int i;

  switch (command) {
  case TryLock:
    i = _NetLockLockTry(lock,num);
    return i;
  case WaitLock:
    i = _NetLockWaitLock(lock,num);
    return i;
  case DoRelease:
    return _NetLockDoRelease(lock,num);
  }
}
// Author: Michael Schmidt (michael@embeddedARM.com)
// Copyright (c) 2011, Technologic Systems, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
