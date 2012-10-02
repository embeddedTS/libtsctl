#ifndef __Thread_h
#define __Thread_h

typedef struct Thread Thread;

enum {
  LOCK_TRY, LOCK_FOD, LOCK_SOD
};

typedef void *(*ThreadFunction)(void *);
typedef void (*ThreadDestructor)(void *);


#ifdef THREAD_USE_POSIX
#include "PThread.h"
#endif

int ThreadInit();
void ThreadFini(void *);
Thread *ThreadNew(char *name,int inst,ThreadFunction func,int socket,
		  void *data,ThreadDestructor destor);
int ThreadEnterBlock();
int ThreadLeaveBlock();
unsigned ThreadMutexAllocate(int);
unsigned ThreadLockAllocate(int);
unsigned ThreadMutexCount();
unsigned ThreadLockCount();
int ThreadMutexLock(unsigned num,int mode);
int ThreadMutexUnlock(unsigned num);
void ThreadUnlockAll(Thread *);
int ThreadWait(int (*f)(int),unsigned num,int mode);
int ThreadSignalIf(int (*f)(int),unsigned num);
int ThreadLockW(unsigned num,int mode);
int ThreadLockR(unsigned num,int mode);
int ThreadUnlockW(unsigned num);
int ThreadUnlockR(unsigned num);
Thread *ThreadLockHolder(unsigned num);
Thread *ThreadMutexHolder(unsigned num);
#endif
