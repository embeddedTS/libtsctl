#ifndef __PThread_h
#define __PThread_h
#include <pthread.h>
#include "Thread.h"

struct Thread {
  // public, R/W
  void *data;
  // public, RO
  char *name; int instance;
  int pid;
  int socket;
  ThreadFunction f;
  // protected
  Thread *next;
  int waitCount; // number of locks this thread is waiting for
  int *wait4; // array of locks this thread is waiting for (0 is none)
  int *wait4n; // array of lock count for each lock we want
  // private, PThread specific
  pthread_t tid;
  ThreadDestructor destor;
  pthread_mutex_t mutex;
  pthread_cond_t condition;
  int *readers; // count of locks held for each read lock
  int rcount; // number of locks we know about (length of readers)
};



/*
  Thread Mutexes and Locks

  The Thread object provides a Mutex abstraction and a Lock abstraction.

  A mutex provides mutually exclusive access to some resource by only
  allowing a single thread to hold it locked at a time.

  A lock is read/write.  At any give time, any number of readers can
  hold the lock, or a single writer can hold the lock.  To prevent
  writer starvation no new read locks are allowed when a write lock
  is pending.

  The MutexLock() function is used to lock a mutex.
  The LockW() function is used to obtain a write lock.
  The LockR() function is used to obtain a read lock.
  All of these functions take a mode argument.  If the mode is LOCK_TRY,
  the function will return failure if the lock would block.  If the mode
  is LOCK_FOD, the function will return failure if the lock would cause
  a deadlock.  If the mode is LOCK_SOD, the function will always return
  success, preventing deadlocks by releasing locks held by the caller
  that would deadlock until the call is complete.

  The MutexUnlock() function releases a mutex.

  The UnlockW() and UnlockR() release the write and read lock,
  respectively.  The caller must call the correct function corresponding
  to how the lock was acquired.

  Recursive locking is allowed.  The caller must release the lock
  as many times as it was locked before it is actually available to
  other threads.

  The UnlockAll() function releases all locks and mutexes held by 
  the thread.

  An arbitrary number of mutexes and locks can be available for a 
  process.  The LocalMutex() function allocates another mutex and
  returns the mutex number to the caller.  The LockAllocate() function 
  allocates another lock and returns the lock number to the caller.  
  All threads are responsible for coordinating to agree on what 
  resource each mutex and lock protects. Except as otherwise documented, 
  locks are not automatically allocated and thus it is up to the program 
  to first allocate what locks are needed before trying to acquire them.  
  The program should not try to lock or unlock mutex or lock numbers that 
  have not been allocated to them. (For instance, locks may use
  mutexes to implement read/write locks.)

  The LockMutex() and LockAllocate() functions are not protected against 
  deadlock.

  Each lock has a condition associated with it.  A thread can wait
  for this condition by calling the Wait() function.  A thread can
  signal this condition if it is true by calling the SignalIf() function.
  All threads are responsible for coordinating to agree on what condition 
  is associated with each lock.
 */

#endif
