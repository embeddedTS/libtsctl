#ifndef __IPC_H
#define __IPC_H
#include <sys/ipc.h>
#include <sys/sem.h>
#include <signal.h>

union semun {
  int              val;    /* Value for SETVAL */
  struct semid_ds *buf;    /* Buffer for IPC_STAT, IPC_SET */
  unsigned short  *array;  /* Array for GETALL, SETALL */
  struct seminfo  *__buf;  /* Buffer for IPC_INFO
			      (Linux-specific) */
};
enum {
  SemaphoreLock = -1,
  SemaphoreUnlock = 1,
  SemaphoreWaitLock = 0
};

int SemaphoresGet(int key,int count);
int SemaphoresQuery(int semid,unsigned short **arrptr);
int SemaphoresOp(int op,int semid,int len,int *num,int flags,unsigned us);

enum {
  LockErrorSemopBase=-1000,
  LockErrorSemgetBase=-2000,
  LockErrorSemctlBase=-4000,
  IPCErrorShmgetBase=-1000,
  IPCErrorShmdtBase=-2000
};

void *SharedMemoryGet(int key,int len,int *err);

typedef void (*SignalHandler)(int);
int SignalCapture(int signal,SignalHandler h);
int SignalIgnore(int signal);

#endif
// Author: Michael Schmidt (michael@embeddedTS.com)
// Copyright (c) 2011-2022 Technologic Systems, Inc. dba embeddedTS, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
