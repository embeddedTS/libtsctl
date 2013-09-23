#include <stdio.h>
#include <sys/sem.h>
#include "Thread.h"
#include "nosig.h"

/*
#ifndef NoThread_c
#define NoThread_c
struct Thread {
  // public, R/W
  void *data;
  // public, RO
  char *name; int instance;
  int pid;
  int socket;
  ThreadFunction f;
};
#endif
*/

static int semid;

int ThreadInit() {
  semid = SemaphoresGet(0x75000000,1);
  return 0;
}

void ThreadFini(void *th) {
}

Thread *ThreadNew(char *name,int inst,ThreadFunction func,int socket,
		  void *data,ThreadDestructor destor) {
  fprintf(stderr,"WARNING: Thread %s:%d cannot be created as this binary does not suppor threads\n",name,inst);
  return 0;
}

int ThreadEnterBlock() {
  return 1;
}

int ThreadLeaveBlock() {
  return 1;
}

unsigned locks,mutexes;
unsigned ThreadMutexAllocate(int n) {
  return mutexes+=n;
}

unsigned ThreadLockAllocate(int n) {
  return locks+=n;
}

unsigned ThreadMutexCount() {
  return mutexes;
}

unsigned ThreadLockCount() {
  return locks;
}

int ThreadMutexLock(unsigned num,int mode) {
  if (num == 0) {
    struct sembuf sop = { 0, -1, SEM_UNDO };
    return 1+2*TEMP_FAILURE_RETRY(semop(semid, &sop, 1));
  } 
  return 1;
}

int ThreadMutexUnlock(unsigned num) {
  if (num == 0) {
    struct sembuf sop = { 0, 1, SEM_UNDO };
    return 1+2*TEMP_FAILURE_RETRY(semop(semid, &sop, 1));
  } 
  return 1;
}

void ThreadUnlockAll(Thread *th) {
}

int ThreadWait(int (*f)(int),unsigned num,int mode) {
  return -1;
}

int ThreadSignalIf(int (*f)(int),unsigned num) {
  return -1;
}

int ThreadLockW(unsigned num,int mode) {
  return 1;
}

int ThreadLockR(unsigned num,int mode) {
  return 1;
}

int ThreadUnlockW(unsigned num) {
  return 1;
}

int ThreadUnlockR(unsigned num) {
  return 1;
}

Thread *ThreadLockHolder(unsigned num) {
  return 0;
}

Thread *ThreadMutexHolder(unsigned num) {
  return 0;
}
