#ifndef __USE_UNIX98
#define __USE_UNIX98
#endif
#ifndef _XOPEN_SOURCE
#define _XOPEN_SOURCE 600
#endif
#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif

#include <pthread.h>
#include <unistd.h>
#include <sys/epoll.h>
#include <sys/sem.h>
#include <stdlib.h>
#include <errno.h> 
#include <stdio.h>                                                            
#include "PThread.h"
#include "Log.h"
#include "nosig.h"

#ifndef EPOLLRDHUP
// Note: WTF cross tools? Y U NO DEFINE THIS, 
// EVEN THOUGH Linux version > 2.6.17???
#define EPOLLRDHUP 0x2000
#endif

pthread_key_t threadKey;

typedef struct LockInfo LockInfo;

#if 0
ThreadAPI PThreadAPI = {
  .Init = (void *)ThreadInit,
  .Fini = (void *)ThreadFini,
  .New = (void *)ThreadNew,
  .EnterBlock = (void *)ThreadEnterBlock,
  .LeaveBlock = (void *)ThreadLeaveBlock,
  .MutexAllocate = (void *)ThreadMutexAllocate,
  .LockAllocate = (void *)ThreadLockAllocate,
  .MutexCount = (void *)ThreadMutexCount,
  .LockCount = (void *)ThreadLockCount,
  .MutexLock = (void *)ThreadMutexLock,
  .MutexUnlock = (void *)ThreadMutexUnlock,
  .UnlockAll = (void *)ThreadUnlockAll,
  .Wait = (void *)ThreadWait,
  .SignalIf = (void *)ThreadSignalIf,
  .LockW = (void *)ThreadLockW,
  .LockR = (void *)ThreadLockR,
  .UnlockW = (void *)ThreadUnlockW,
  .UnlockR = (void *)ThreadUnlockR,
  .MutexHolder = (void *)ThreadMutexHolder,
  .LockHolder = (void *)ThreadLockHolder,
};
#endif

struct LockInfo {
  Thread *threadHolding;
  int count;
};

static int threadsInitialized;
static int epollDescriptor;
static pthread_t epollThread;
static pthread_mutex_t mutex2,mutex3,lock2,watchlock;
// lock2 protects rmuts, wmuts, lockCount, readers
static unsigned *rmuts,*wmuts;
static unsigned lockCount;
static unsigned *readers;
// mutex2 protects:
// mutexCount,mutexes,conditions,lockinfo, thread.mutex, thread.condition;
// mutex3 protects:
// mutexes, conditions
static unsigned mutexCount; // how many mutexes are there?
static pthread_mutex_t *mutexes;
static pthread_cond_t *conditions;
static LockInfo *lockinfo;
// watchlock protects head_thread, Thread->next
static int semid; // SBus lock
Thread *head_thread,*rr_thread;
//static pthread_t** rholders;

static void watchlockremove(Thread *th) {
  Thread *cur = head_thread, *last = 0;

  //fprintf(stderr,"remove %p, head=%p\n",th,head_thread);
  while (cur) {
    //fprintf(stderr,"cur=%p, th=%p, next=%p\n",cur,th,cur->next);
    if (cur == th) {
      if (last == 0) {
	head_thread = cur->next;
	//fprintf(stderr,"head:=%p\n",head_thread);
      } else {
	//fprintf(stderr,"%p->next = %p\n",last,last->next);
	last->next = cur->next;
      }
      if (rr_thread == cur) {
	rr_thread = cur->next;
	if (!rr_thread) rr_thread = head_thread;
      }
      return;
    } else {
      last = cur;
      cur = cur->next; // keep looking
    }
  }
#if 0
  // We will reach this point if our socket dies, because epoll will
  // call us, then the thread descriptor will call again
  fprintf(stderr,"Trying to remove a thread %p not in the chain!\n",th);
   {
    Thread *cur = head_thread;

    fprintf(stderr,"head_thread=%p, rr_thread=%p\n",head_thread,rr_thread);
    while (cur) {
      fprintf(stderr,"%p:%s.%d ",cur,cur->name,cur->instance);
      cur = cur->next;
    }
    fprintf(stderr,"\n");
  }
 
  exit(1);
#endif
}

static void *ThreadEPollLoop(void *arg) {
  Thread *cur;
  int dummy;
  struct epoll_event events;

  while (1) {
    if (epoll_wait(epollDescriptor,&events,1,-1) > 0) {
      cur = events.data.ptr;
      pthread_mutex_lock(&watchlock);
      //close(cur->socket); 
      watchlockremove(cur);
      dummy = pthread_kill(cur->tid,15);
      pthread_mutex_unlock(&watchlock);
    }
  }
}

static void SignalHandle(int signal) {
  LogEnter("%d",signal);
  Log(LOG_SYSTEM,"caught signal %d\n",signal);
  pthread_cancel(pthread_self());
  while (1) sleep(1);
}

int ThreadInit() {
  int err;
 if (!threadsInitialized) {
    assertf(SignalCapture(15,SignalHandle) == 0,"SignalCapture %d:%m",15);
    pthread_mutex_lock(&mutex2);
    threadsInitialized = 1;
    epollDescriptor = epoll_create(8);
    if (epollDescriptor == -1) {
      fprintf(stderr,"epoll_create:%m\n");
      exit(3);
    }
    assertf((err=pthread_key_create(&threadKey, ThreadFini))==0,
	    "pthread_key_create:%m:%d",err);
    pthread_create(&epollThread, NULL, ThreadEPollLoop, 0);
    pthread_detach(epollThread);
    pthread_mutex_init(&mutex2, NULL);
    semid = SemaphoresGet(0x75000000,1);
    pthread_mutex_unlock(&mutex2);
    pthread_mutex_unlock(&watchlock);
    ThreadMutexAllocate(1); // reserve 0 for SBus
 }
 if (!pthread_getspecific(threadKey)) {
   Thread *ob = malloc(sizeof(Thread));

   ob->tid = pthread_self();;
   ob->pid = getpid();
   ob->name = "main()";
   ob->instance = 0;
   ob->socket = 0;
   ob->waitCount = 0;
   ob->wait4 = 0;
   ob->wait4n = 0;
   ob->data = 0;
   ob->destor = 0;
   ob->f = 0;
   pthread_mutex_init(&ob->mutex, NULL);
   pthread_cond_init(&ob->condition, NULL);

   assertf((err=pthread_setspecific(threadKey,ob)) == 0,
	    "pthread_setspecific:%m:%d",err);
   assertf(pthread_getspecific(threadKey),"");

   pthread_mutex_lock(&watchlock);
   ob->next = head_thread;
   head_thread = ob;
   if (!rr_thread) rr_thread = ob;
   pthread_mutex_unlock(&watchlock); 
 }
 return 1;
}

void ThreadFini(void *arg) {
  Thread *ob = arg;
  LogEnter("%p",ob);

  if (!ob) {
    ob = pthread_getspecific(threadKey);
    assertf(ob,"");
  }
  Log(LOG_INFO | LOG_THREAD,"%s:%d\n"
       "tid=%d\n"
       "pid=%d\n"
       "socket=%d\n",
       ob->name,ob->instance,ob->tid,ob->pid,ob->socket);
  //fprintf(stderr,"ThreadFini %p/%d\n",ob,ob->tid);
  ThreadUnlockAll(ob);
  pthread_mutex_lock(&watchlock);
  watchlockremove(ob);
  pthread_mutex_unlock(&watchlock);
  Log(LOG_INFO | LOG_THREAD,"final destructor\n");
  if (ob->wait4) free(ob->wait4);
  if (ob->wait4n) free(ob->wait4n);
  if (ob->readers) free(ob->readers);
  if (ob->destor) ob->destor(ob);
  if (ob->socket >= 0) {
    close(ob->socket);
    ob->socket = -1;
  }
  free(ob);
  LogReturn("");
}

static void *ThreadMain(void *args) {
  Thread *ob = args;
  int err;
  LogEnter("%p",ob);

  ob->pid = getpid();
  assertf((err=pthread_setspecific(threadKey,ob)) == 0,
	  "pthread_setspecific:%m:%d",err);
  assertf(pthread_getspecific(threadKey),"");
  pthread_mutex_lock(&watchlock);
  ob->next = head_thread;
  head_thread = ob;
  if (!rr_thread) rr_thread = ob;
  pthread_mutex_unlock(&watchlock);
  LogReturn("%p",ob->f(ob));
}

Thread *ThreadNew(char *name,int inst,ThreadFunction func,
	      int socket,void *data,ThreadDestructor destor) {
  pthread_t thread_t;
  LogEnter("%s,%d,%p,%d,%p,%p",
	   name,inst,func,socket,data,destor);
  Thread *ob = malloc(sizeof(Thread));

  ob->name = name;
  ob->instance = inst;
  ob->socket = socket;
  ob->waitCount = 0;
  ob->wait4 = 0;
  ob->wait4n = 0;
  ob->readers = 0;
  ob->data = data;
  ob->destor = destor;
  pthread_mutex_init(&ob->mutex, NULL);
  pthread_cond_init(&ob->condition, NULL);
  ob->f = func;
  ob->rcount = 0;

  assertf(pthread_create(&ob->tid, NULL, ThreadMain, ob)==0,"%m");
  if (inst >= 0) pthread_detach(ob->tid);
  LogReturn("%p",ob);
}

int ThreadEnterBlock() {
  Thread *th = pthread_getspecific(threadKey);
  assertf(th,"");
  struct epoll_event event;

  event.events = EPOLLRDHUP;
  event.data.ptr = th;
  if (epoll_ctl(epollDescriptor,EPOLL_CTL_ADD,th->socket,&event) < 0) {
    return -1;
  }
  return 1;
}

int ThreadLeaveBlock() {
  Thread *th = pthread_getspecific(threadKey);
  assertf(th,"");
  if (epoll_ctl(epollDescriptor,EPOLL_CTL_DEL,th->socket,0) < 0) {
    return -1;
  }
  return 1;
}

unsigned ThreadMutexAllocate(int num) {
  int i,n;
  pthread_mutexattr_t attr;

  pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);

  pthread_mutex_lock(&mutex3);
  pthread_mutex_lock(&mutex2);
  n = mutexCount; mutexCount += num;
  mutexes = realloc(mutexes,sizeof(pthread_mutex_t)*mutexCount);
  conditions = realloc(conditions,sizeof(pthread_cond_t)*mutexCount);
  lockinfo = realloc(lockinfo,sizeof(LockInfo)*mutexCount);
  //  if (!rholders) {
  //    rholders = ArrayAlloc(num,sizeof(pthread_t*));
  //} else {
  //rholders = ArraySize(rholders,mutexCount);
  //}
  for (i=n;i<mutexCount;i++) {
    //pthread_mutex_init(mutexes+i, &attr);
    //mutexes[i] = (pthread_mutex_t)PTHREAD_ERRORCHECK_MUTEX_INITIALIZER_NP;
    mutexes[i] = (pthread_mutex_t)PTHREAD_RECURSIVE_MUTEX_INITIALIZER_NP;
    pthread_cond_init(conditions+i, NULL);
    lockinfo[i].threadHolding = 0;
    lockinfo[i].count = 0;
    //rholders[i] = ArrayAlloc(0,sizeof(pthread_t));
  }
  pthread_mutex_unlock(&mutex2);
  pthread_mutex_unlock(&mutex3);
  return n;
}

unsigned ThreadLockAllocate(int num) {
  unsigned k;
  int i,n;

  n = lockCount;
  k = ThreadMutexAllocate(2*num);
  pthread_mutex_lock(&lock2);  
  lockCount  += num;
  rmuts = realloc(rmuts,sizeof(unsigned)*lockCount);
  wmuts = realloc(wmuts,sizeof(unsigned)*lockCount);
  readers = realloc(readers,sizeof(unsigned)*lockCount);


  for (i=n;i<lockCount;i++) {
    rmuts[i] = k++;
    wmuts[i] = k++;
    readers[i] = 0;
  }
  pthread_mutex_unlock(&lock2);
  return n;
}

unsigned ThreadMutexCount() {
  unsigned ret;
  pthread_mutex_lock(&mutex2);
  ret = mutexCount;
  pthread_mutex_unlock(&mutex2);
  return ret;
}

unsigned ThreadLockCount() {
  unsigned ret;
  pthread_mutex_lock(&lock2);
  ret = lockCount;
  pthread_mutex_unlock(&lock2);
  return ret;
}

/*
  We prevent deadlocks by detecting when a deadlock would occur and
  offering one of two choices:
  1. fail the lock
  2. release locks held by the caller (who wants more locks) to prevent
     the deadlock from occurring

  We detect deadlocks by doing a depth-first recursion down the tree
  formed by mapping the waited-for locks of each thread to the thread
  that holds each of those locks.  If we reach ourselves at any point
  in the search, then we have a cycle, and the last lock being waited
  for is one we must unlock to prevent a deadlock.  We must continue
  after this to complete the search in order to find all possible
  deadlocks.

  ThreadMutexPreventDeadlock performs this search.  If fails is true,
  then it returns a negative value if a deadlock would occur by locking
  lock num, and a positive value if it would not.
  If fail is false, then all locks held by the caller that would cause
  deadlock are released and added to the wait list before returning a
  positive value.

  ThreadMutexPreventDeadlock assumes that we have already tried to
  lock but failed, and that the passed thread is not the thread that
  holds the lock.
 */
// 
static void MutexWait4Add(unsigned num,int count) {
  Thread *me = pthread_getspecific(threadKey);
  printf("socket %d wait4add %d (%p,%p,%p)\n",me->socket,num,me,me->wait4,me->wait4n);
  int n = me->waitCount++;
  me->wait4 = realloc(me->wait4,sizeof(unsigned)*me->waitCount);
  me->wait4[n] = num;
  me->wait4n = realloc(me->wait4n,sizeof(unsigned)*me->waitCount);
  me->wait4n[n] = count;
}

static int MutexWait4Remove(Thread *me,unsigned num) {
  int i,n;
  printf("socket %d wait4remove %d\n",me->socket,num);
  for (i=0;i<me->waitCount;i++) {
    if (me->wait4[i] == num) break;
  }
  assertf(i < me->waitCount,"socket=%d, num=%d",me->socket,num);
  n = me->wait4n[i];
  for (;i<me->waitCount-1;i++) {
    me->wait4[i] = me->wait4[i+1];
    me->wait4n[i] = me->wait4n[i+1];
  }
  me->waitCount--;
  me->wait4 = realloc(me->wait4,sizeof(unsigned)*me->waitCount);
  me->wait4n = realloc(me->wait4n,sizeof(unsigned)*me->waitCount);
  return n;
}
/*
__attribute__((always_inline)) 
static inline int MutexLockDo(unsigned num) {
  int ret;
  MutexWait4Add(num);
  if (num == 0) {
    struct sembuf sop = { 0, -1, SEM_UNDO };
    ret = 1+2*TEMP_FAILURE_RETRY(semop(semid, &sop, 1));
  } else {
    ret = (pthread_mutex_lock(mutexes+num) == 0)?1:-1;
  }
  MutexWait4Remove(num);
  return ret;
}
*/
__attribute__((always_inline)) 
static inline Thread *_MutexHolder(unsigned num) {
  return lockinfo[num].count ? lockinfo[num].threadHolding : 0;
}
__attribute__((always_inline)) 
static inline int MutexLockIncr(unsigned num) {
  lockinfo[num].count++;
  return 1;
}
__attribute__((always_inline)) 
static inline int MutexLockDecr(unsigned num) {
  return --lockinfo[num].count;
}
__attribute__((always_inline)) 
static inline void MutexProtect() {
  pthread_mutex_lock(&mutex2);
}
__attribute__((always_inline)) 
static inline void MutexUnprotect() {
  pthread_mutex_unlock(&mutex2);
}
__attribute__((always_inline)) 
static inline void MutexClaim(Thread *th,unsigned num) {
  lockinfo[num].count = 1;
  lockinfo[num].threadHolding = th;
}
__attribute__((always_inline)) 
static inline void MutexUnclaim(unsigned num) {
  lockinfo[num].count = 0;
}
enum {
  SUCCESS=1,
  ErrorWouldBlock=-1, ErrorWouldDeadLock=-2, ErrorNotOwner=-3
};

static int ThreadRunnable(Thread *th) {
  int i,n;

  for (i=0;i<th->waitCount;i++) {
    n = th->wait4[i];
    if (lockinfo[n].threadHolding != th && lockinfo[n].count) break;
  }
  return (i == th->waitCount);
}

static int ThreadTryWake(Thread *th) {
  int i,n;
  Thread *me = pthread_getspecific(threadKey);

  if (th != me && ThreadRunnable(th)) {
    pthread_mutex_lock(&th->mutex);
    pthread_cond_signal(&th->condition);
    pthread_mutex_unlock(&th->mutex);
    return 1;
  }
  return 0;
}
/*
  Mutex <num> is currently locked, and not by this thread.
  We are going to block waiting for this lock.
  Therefore, we need to first check if blocking would cause a deadlock.
  If so, then if <fail> then we return failure.
  Otherwise, we release all locks which would deadlock to the process
  that we would deadlock with, and then wake them up.
  Finally, we go to sleep.

  _MutexHolder(num) holds lock <num>.

  Note: this function can't acquire the lock the caller wants, as
  it is recursive.  Also, we can't call this function if WE own the
  lock!
 */
static int ThreadPreventDeadlock(Thread *me,Thread *ob,int num,int fail) {
  int i,ret,n;

  if (!ob) return SUCCESS;
  assertf(me != ob,"me == ob");
    /* if <ob> has all the locks it needs, wake it up
       can we assume that this will be true?
       1. is it ever possible that we could have two cycles, and that
       each of them would take part of our locks and deadlock each other?
       answer: it is not possible, because we won't allow the first
       cycle to occur, therefore a second cycle isn't possible.
       2. is it possible that the lock we want would create more than
       one cycle? i'm thinking it shouldn't because when the first
       cycle is broken the second should be also.  the reason for this
       is that we always check for a cycle with the addition of one
       lock at a time.  only the lock we are trying to add can result
       in a cycle, because all the existing locks we are waiting on
       did not have cycles already.
     */
  for (i=ob->waitCount-1;i>=0;i--) {
    n = ob->wait4[i];
    if (_MutexHolder(n) == me) {
      if (fail) return ErrorWouldDeadLock;
      MutexWait4Add(n,lockinfo[num].count);
      lockinfo[n].count = MutexWait4Remove(ob,n);
      lockinfo[n].threadHolding = ob;
      ThreadTryWake(ob);
    } else {
      ret = ThreadPreventDeadlock(me,_MutexHolder(n),n,fail);
      if (ret < 0) return ret;
    }
  }
  return SUCCESS;
}

/*
  Unlock lock <num>.
  next, determine if we should wake up a thread.
  one way would be to scan through all our threads and find the first
  one that can acquire all the mutexes it wants.  by advancing which
  thread we look at first we can achieve some manner of fairness. we
  could also have some kind of prioritization, for instance, who has
  been waiting the longest (by number of schedules or something)
*/
static int ThreadSchedule() {
  Thread *th;
  int head,i,n;
  
  pthread_mutex_lock(&watchlock);
  th = rr_thread;
  head = (th == head_thread);
  do {
    if (ThreadTryWake(th)) {
      // actually claim any locks that we are waiting on and are
      // free but which we don't have locked
      for (i=th->waitCount-1;i>=0;i--) {
	n = th->wait4[i];
	lockinfo[n].count = MutexWait4Remove(th,n);
	lockinfo[n].threadHolding = th;
      }
      break;
    }
    th = th->next;
    if (th == 0) th = head_thread;
  } while (th != head_thread);
  rr_thread = rr_thread->next;
  if (rr_thread == 0) rr_thread = head_thread;
  pthread_mutex_unlock(&watchlock);
}

#define WANTED 999

int ThreadMutexLock(unsigned num,int mode) {
  int ret;
  Thread *th = pthread_getspecific(threadKey);

  if (num == 0) {
    struct sembuf sop = { 0, -1, SEM_UNDO };
    //fprintf(stderr,"SBUS LOCK...");
    //system("/mnt/host/home/michael/semtest -q");
    int ret =  1+2*TEMP_FAILURE_RETRY(semop(semid, &sop, 1));
    //fprintf(stderr,"LOCKED\n");
    return ret;
  }

  if (num==WANTED) fprintf(stderr,"ThreadMutexLock(%p/%d:%d)\n",th,th->pid,num);
  ret = pthread_mutex_lock(mutexes+num);
  if (num==WANTED) fprintf(stderr,"ThreadMutexLock(%p/%d:%d) ret=%d\n",th,th->pid,num,ret);
  return ret == 0 ? 1 : ret;
  // old code
#if 0
  Thread *me,*you;
  int ret;
  if (num >= mutexCount) return 0; // unprotected since mutexCount is ++ only
  me = pthread_getspecific(threadKey);
  MutexProtect();
  if (me == (you=_MutexHolder(num)) && MutexLockIncr(num)) {
    MutexUnprotect(); 
    return SUCCESS;
  }
  if (you == 0) { // nobody holds the mutex
    MutexClaim(me,num);

    MutexUnprotect(); 
    if (num == 0) {
      // we have already claimed the lock to this process
      // now try to get the semaphore
      struct sembuf sop = { 0, -1, SEM_UNDO };
      ret = 1+2*TEMP_FAILURE_RETRY(semop(semid, &sop, 1));
      //fprintf(stderr,"Lock=%d\n",ret);
    } else ret = SUCCESS;
    return ret;
  } else if (mode == LOCK_TRY) {
    MutexUnprotect(); 
    return ErrorWouldBlock;
  }
  // TEMP REMOVAL OF DEADLOCK PREVENTION
  //ret=ThreadPreventDeadlock(me,lockinfo[num].threadHolding,num,mode==LOCK_FOD);
  //if (ret < 0) return ret;
  MutexWait4Add(num,1);
  pthread_mutex_unlock(&mutex2);
  pthread_mutex_lock(&me->mutex);
  while (!ThreadRunnable(me)) {
    pthread_cond_wait(&me->condition,&me->mutex);
  }
  pthread_mutex_unlock(&me->mutex);
  //lockinfo[num].count = MutexWait4Remove(me,num);
#endif
}

int ThreadMutexUnlock(unsigned num) {
  Thread *th = pthread_getspecific(threadKey);
  if (num == 0) {
    struct sembuf sop = { 0, 1, SEM_UNDO };
    //fprintf(stderr,"SBUS UNLOCK...");
    int ret = 1+2*TEMP_FAILURE_RETRY(semop(semid, &sop, 1));
    //fprintf(stderr,"UNLOCK\n");
    return ret;
  } 
  if (num==WANTED) fprintf(stderr,"ThreadMutexUnlock(%p/%d:%d)\n",th,th->pid,num);
  int ret = pthread_mutex_unlock(mutexes+num);
  if (num==WANTED) fprintf(stderr,"ThreadMutexUnlock(%p/%d:%d) ret=%d\n",th,th->pid,num,ret);
  return (ret==0) ? 1 : ret;
  // Old code
#if 0
  Thread *me;
  int ret = 1;
  if (num >= mutexCount) return 0; // unprotected since mutexCount is ++ only
  me=pthread_getspecific(threadKey);
  MutexProtect();
  if (me != _MutexHolder(num)) {
    MutexUnprotect(); 
    return ErrorNotOwner;
  }
  if (MutexLockDecr(num)) {
    MutexUnprotect(); 
    return 1;
  }
  ThreadSchedule();
  if (num == 0 && _MutexHolder(0) == 0) {
    struct sembuf sop = { 0, 1, SEM_UNDO };
    ret = 1+2*TEMP_FAILURE_RETRY(semop(semid, &sop, 1));
    //fprintf(stderr,"Unlock=%d\n",ret);
  } 
  MutexUnprotect(); 
  return ret;
#endif
}

void ThreadUnlockAll(Thread *me) {
  //Thread *me = pthread_getspecific(threadKey);
  unsigned i,zero=0,ret;

  MutexProtect();
  //fprintf(stderr,"ThreadUnlockAll %p/%d\n",me,pthread_self());
  for (i=0;i<mutexCount;i++) {
    //Thread *tmp = (void *)mutexes[i].__m_owner;
    //if (tmp == me) {
    // the following line, if uncommented, causes an immediate segfault
    // in the destructor, in an unrelated place. i have not yet figured out
    // why, as far as i can tell we don't leave me->readers uninitialized
    // anywhere, but we must have a bad but non-null pointer at this
    // point and i must figure out why!!
    if (me->readers && i < me->rcount) {
      readers[i] -= me->readers[i];
    }
    ret = pthread_mutex_unlock(mutexes+i);
    pthread_cond_signal(conditions+i);
    //  fprintf(stderr,"%d:%d:%p/%p ",i,ret,tmp,me);
    //mutexes[i].__m_owner = 0;
    //if (me == _MutexHolder(i)) {
    //if (i == 0) zero = 1;
    //MutexUnclaim(i);
    //}
  }
  //fprintf(stderr,"\n");
  //ThreadSchedule();
  //if (zero && _MutexHolder(0) == 0) {
  //struct sembuf sop = { 0, 1, SEM_UNDO };
  //int ret = TEMP_FAILURE_RETRY(semop(semid, &sop, 1));
    //fprintf(stderr,"UnlockAll=%d\n",ret);
  //} 
  MutexUnprotect(); 
}

int ThreadWaitDo(int (*f)(int),unsigned num,int mode,void (*g)()) {
  int ret;

  pthread_mutex_lock(&mutex3);
  //if ((ret=ThreadMutexLock(num,mode)) < 0) {
  //pthread_mutex_unlock(&mutex3);
  //return ret;
  //}
  pthread_mutex_lock(mutexes+num);
  pthread_mutex_unlock(&mutex3); // was after next statement, that deadlocks!
  // but, without it we can't protect conditions/mutexes during wait
  while (!f(num)) pthread_cond_wait(conditions+num,mutexes+num);
  if (g) g();
  pthread_mutex_unlock(mutexes+num);
  //ThreadMutexUnlock(num);
  return SUCCESS;
}

int ThreadWait(int (*f)(int),unsigned num,int mode) {
  return ThreadWaitDo(f,num,mode,0);
}

int ThreadSignalIf(int (*f)(int),unsigned num) {
  if (f(num)) {
    pthread_mutex_lock(&mutex3);
    pthread_mutex_lock(mutexes+num);    
    pthread_cond_signal(conditions+num);
    pthread_mutex_unlock(mutexes+num);
    pthread_mutex_unlock(&mutex3);
    return 1;
  }
  return 0;
}

// ThreadMsgSend takes the message slot (num), pointer to message (msg), and
// value to send in the message.
// Waits for the message to be null (0), then sends the message
int ThreadMsgSend(int num,void **msg,void *val) {
  int msgrdy(int x) { return !!*msg; }
  int msgempty(int x) { return !*msg; }
  void msgset() { *msg = val; }
  int ret;

  ret = ThreadWaitDo(msgempty,num,LOCK_SOD,msgset);
  if (ret <= 0) return ret;
  return ThreadSignalIf(msgrdy,num);
}

// ThreadMsgRecv takes the message slot (num), and pointer to message (msg).
// Waits for the message to be present (non-zero), saves the message, clears
// it to signal that another message can be sent, then returns the message.
void *ThreadMsgRecv(int num,void **msg) {
  void *ret;
  int msgrdy(int x) { return !!*msg; }
  void msgclr() { ret = *msg; *msg = 0; }
  ThreadWaitDo(msgrdy,num,LOCK_SOD,msgclr);
  return ret;
}

static int ThreadLockRWGet(unsigned n,unsigned *r,unsigned *w) {
  pthread_mutex_lock(&lock2);
  if (n >= lockCount) {
    pthread_mutex_unlock(&lock2);
    return -1;
  }
  *r = rmuts[n];
  *w = wmuts[n];
  pthread_mutex_unlock(&lock2);
  return 1;
}

/*
We must avoid deadlocks.  Currently we don't.  For example, if we try
to acquire a write lock when we hold a read lock, we will deadlock.
we won't deadlock if we try to acquire a read lock and
already hold the read lock, because we aren't actually holding anything;
read locks are just advisory to write locking.

the solution to avoiding a deadlock when acquiring a write lock while
holding a read lock?
one would be to keep a list of all the threads that hold read locks.
then we would scan to see if we are already on the list.
this is information that currently isn't held anywhere. so we basically
need an Array for each lock to hold all the readers.

we also have to avoid a deadlock if we hold a read lock while waiting to
upgrade to a write lock. i think it should be sufficient to drop the read
lock, wait for the lock, and then re-aquire it, since now nobody else can
be holding it and we must succeed.
 */
__attribute__((always_inline)) 
static inline void LocalReadersInit(Thread *th) {
  if (!th->readers || lockCount > th->rcount) {
    int i;
    th->readers = realloc(th->readers,sizeof(unsigned)*lockCount);
    for (i=th->rcount;i<lockCount;i++) th->readers[i] = 0;
    th->rcount = lockCount;
  }
}

int ThreadLockW(unsigned num,int mode) {
  int ret;
  unsigned r,w;
  Thread *th = pthread_getspecific(threadKey);

  if (ThreadLockRWGet(num,&r,&w) < 0) return -8;
  if (num==WANTED) fprintf(stderr,"ThreadLockW(%p/%d:%d=%d/%d)\n",th,th->pid,num,r,w);
  ret = pthread_mutex_lock(mutexes+r);
  if (ret < 0) return ret;
  ret = pthread_mutex_lock(mutexes+w);
  if (ret < 0) {
    pthread_mutex_unlock(mutexes+r);
    if (num==WANTED) fprintf(stderr,"ThreadLockW(%p/%d:%d) failed %d\n",th,th->pid,num,ret);
    return ret;
  }
  if (mode == LOCK_TRY && readers[num]) {
    pthread_mutex_unlock(mutexes+r);
    pthread_mutex_unlock(mutexes+w);
    if (num==WANTED) fprintf(stderr,"ThreadLockW(%p/%d:%d failed TRY)\n",th,th->pid,num);
    return -9;
  }
  LocalReadersInit(th);
  while (readers[num] - th->readers[num]) {
    //fprintf(stderr,"(->%d-%d)",readers[num],th->readers[num]);
    pthread_cond_wait(conditions+w,mutexes+w);
    //fprintf(stderr,"(%d-%d->)",readers[num],th->readers[num]);
  }
  pthread_mutex_unlock(mutexes+r);
  //mutexes[r].__m_owner = (void *)th;
  //fprintf(stderr,"note: %d=%p\n",r,th);

  if (num==WANTED) fprintf(stderr,"ThreadLockW(%p/%d:%d) ret %d\n",th,th->pid,num,ret);
  return ret == 0 ? 1 : ret;
}
int ThreadLockR(unsigned num,int mode) {
  int ret;
  unsigned r,w;
  Thread *th = pthread_getspecific(threadKey);

  if (ThreadLockRWGet(num,&r,&w) < 0) return -8;  
  if (num==WANTED) fprintf(stderr,"ThreadLockR(%p/%d:%d=%d/%d)\n",th,th->pid,num,r,w);
  ret = pthread_mutex_lock(mutexes+r);
  if (ret < 0) {
    if (num==WANTED) fprintf(stderr,"ThreadLockR(%p/%d:%d) fail %d\n",th,th->pid,num,ret);
    return ret;
  }
  ret = pthread_mutex_lock(mutexes+w);
  if (ret < 0) {
    pthread_mutex_unlock(mutexes+r);
    if (num==WANTED) fprintf(stderr,"ThreadLockR(%p/%d:%d) fail2 %d\n",th,th->pid,num,ret);
    return ret;
  }
  readers[num]++;
  LocalReadersInit(th);
  th->readers[num]++;
  pthread_mutex_unlock(mutexes+w);
  pthread_mutex_unlock(mutexes+r);
  if (num==WANTED) fprintf(stderr,"ThreadLockR(%p/%d:%d) ret %d\n",th,th->pid,num,ret);
  return ret == 0 ? 1 : ret;
}

int ThreadUnlockW(unsigned num) {
  unsigned r,w;
  Thread *th = pthread_getspecific(threadKey);

  if (ThreadLockRWGet(num,&r,&w) < 0) return -8;
  if (num==WANTED) fprintf(stderr,"ThreadUnlockW(%p/%d:%d=%d/%d)\n",th,th->pid,num,r,w);
  int ret = pthread_mutex_unlock(mutexes+w);
  if (num==WANTED) fprintf(stderr,"ThreadUnlockW(%p/%d:%d=%d/%d) ret=%d\n",th,th->pid,num,r,w,ret);
  if (ret == 1) {
    fprintf(stderr,"oops1\n");
  }
  return (ret==0) ? 1 : ret;
}

int ThreadUnlockR(unsigned num) {
  int ret;
  unsigned r,w;
  Thread *th = pthread_getspecific(threadKey);

  if (ThreadLockRWGet(num,&r,&w) < 0) return -8;  
  if (num==WANTED) fprintf(stderr,"ThreadUnlockR(%p/%d:%d=%d/%d)\n",th,th->pid,num,r,w);
  ret = pthread_mutex_lock(mutexes+w);
  if (ret < 0) {
    if (num==WANTED) fprintf(stderr,"ThreadUnlockR(%p/%d:%d=%d/%d) fail %d\n",th,th->pid,num,r,w,ret);
    return ret;
  }
  LocalReadersInit(th);
  if (th->readers[num] == 0) {
    fprintf(stderr,"oops2\n");
    ret = pthread_mutex_unlock(mutexes+w);
    return -99; // we don't hold a lock!
  }
  th->readers[num]--; 
  readers[num]--;
  // we could say if (--readers[num] == 0)
  // but this will deadlock if the thread wanting the write lock already holds a
  // read lock. the alternative would be to subtract off the number of read
  // locks the write waiter holds, but this would be additional housekeeping
  pthread_cond_signal(conditions+w);

  //fprintf(stderr,"<%d>",readers[num]);
  ret = pthread_mutex_unlock(mutexes+w);
  if (num==WANTED) fprintf(stderr,"ThreadUnlockR(%p/%d:%d=%d/%d) ret=%d\n",th,th->pid,num,r,w,ret);
  return (ret == 0) ? 1 : ret;
}




int oldThreadLockW(unsigned num,int mode) {
  int ret;
  unsigned r,w;

  if (ThreadLockRWGet(num,&r,&w) < 0) return -8;
  //fprintf(stderr,"ThreadLockW(%d) r=%d w=%d\n",num,r,w);
  ret = ThreadMutexLock(r,mode);
  if (ret < 0) return ret;
  ret = ThreadMutexLock(w,mode);
  if (ret < 0) {
    ThreadMutexUnlock(r);
    return ret;
  }
  if (mode == LOCK_TRY && readers[num]) {
    ThreadMutexUnlock(r);
    ThreadMutexUnlock(w);
    return -9;
  }
  if (readers[num]) {
    int f(int x) { return readers[num]; }
    ret = ThreadWait(f,readers[num],mode);
  }
  ThreadMutexUnlock(r);
  return ret;
}
int oldThreadLockR(unsigned num,int mode) {
  int ret;
  unsigned r,w;
  pthread_t me = pthread_self();

  if (ThreadLockRWGet(num,&r,&w) < 0) return -8;  
  //fprintf(stderr,"ThreadLockR(%d) r=%d w=%d\n",num,r,w);
  ret = ThreadMutexLock(r,mode);
  if (ret < 0) return ret;
  ret = ThreadMutexLock(w,mode);
  if (ret < 0) {
    ThreadMutexUnlock(r);
    return ret;
  }
  readers[num]++;
  // it is at this point that we need to add out thread info to the list
  //rholders[num] = ArrayQueue(rholders[num],A(pthread_t,me));
  //fprintf(stderr,"readers[%d] incr to %d\n",num,readers[num]);
  ThreadMutexUnlock(w);
  ThreadMutexUnlock(r);
  return 1;
}

int oldThreadUnlockW(unsigned num) {
  unsigned r,w;

  if (ThreadLockRWGet(num,&r,&w) < 0) return -8;
  //fprintf(stderr,"ThreadUnlockW(%d) r=%d w=%d\n",num,r,w);
  return ThreadMutexUnlock(w);
}

int oldThreadUnlockR(unsigned num) {
  int ret;
  unsigned r,w;

  if (ThreadLockRWGet(num,&r,&w) < 0) return -8;  
  //fprintf(stderr,"ThreadUnlockR(%d) r=%d w=%d\n",num,r,w);
  ret = ThreadMutexLock(w,LOCK_FOD);
  assertf(ret>0,"would deadlock1");
  // err whoops! we need to remove OUR entry
  //rholders[num] = ArrayPop(rholders[num],A(pthread_t,tmp));
  int f(int x) { return --readers[num] == 0; }
  ThreadSignalIf(f,w);
  //fprintf(stderr,"readers[%d] decr to %d\n",num,readers[num]);
  ThreadMutexUnlock(w);
  return ret;
}

Thread *ThreadMutexHolder(unsigned num) {
  Thread *ret;
  MutexProtect();
  if (num >= mutexCount) {
    MutexUnprotect();
    return 0;
  }
  ret = _MutexHolder(num);
  MutexUnprotect();
  return ret;
}

Thread *ThreadLockHolder(unsigned num) {
  unsigned r,w;
  Thread *rh,*wh;

  if (ThreadLockRWGet(num,&r,&w) < 0) return 0;
  MutexProtect();
  rh = _MutexHolder(r);
  wh = _MutexHolder(r);
  MutexUnprotect();
  if (rh == 0) return wh;
  if (wh == 0) return rh;
  assertf(rh == wh,"rh=%p, rw=%p",rh,wh);
  return rh;
}

void dump_threadinfo(FILE *fw) {
  int i,n = ThreadMutexCount();
  Thread *ob;
  fprintf(fw,"mutexes=%d\n",n);
  for (i=0;i<n;i++) {
    ob = ThreadMutexHolder(i);
    if (ob) {
      fprintf(fw,"%d held by tid=%d,pid=%d,socket=%d\n",
	      i,ob->tid,ob->pid,ob->socket);
    }
  }
  n = ThreadLockCount();
  fprintf(fw,"locks=%d\n",n);
  for (i=0;i<n;i++) {
    ob = ThreadLockHolder(i);
    if (ob) {
      fprintf(fw,"%d held by tid=%d,pid=%d,socket=%d\n",
	      i,ob->tid,ob->pid,ob->socket);
    }
  }
  pthread_mutex_lock(&watchlock);
  ob = head_thread;
  while (ob) {
    fprintf(fw,"thread tid=%d,pid=%d,socket=%d,waitCount= ",
	   ob->tid,ob->pid,ob->socket);
    for (i=0;i<ob->waitCount;i++) {
      fprintf(fw,"%d ",ob->wait4[i]);
    }
    fprintf(fw,"\n");
    ob = ob->next;
  }
  pthread_mutex_unlock(&watchlock);
}
#ifdef THREAD_TEST

void *Server(void *arg) {
  LogEnter("%p",arg);
  Thread *th = arg;
  FILE *fw = fdopen(th->socket,"w");
  assertf(fw != NULL,"w:%m");
  FILE *fr = fdopen(th->socket,"r");
  assertf(fr != NULL,"r:%m");
  char *str,cmd[80];
  char *argv[16];
  int i,argc=0,quoting=0;

  Log(LOG_INFO | LOG_THREAD,"Server started: %s:%d\n"
       "tid=%d\n"
       "pid=%d\n"
       "socket=%d\n",
       th->name,th->instance,th->tid,th->pid,th->socket);
  while (!feof(fr)) {
    fgets(cmd,78,fr);
    // trim off any CR/LF characters
    str = cmd; while (*str) str++; str--;
    while (*str == '\n' || *str == '\r') str--;
    str[1] = 0;
    // split command into arguments
    argc = 0;
    str = cmd;
    argv[argc++] = str++;
    while (*str && argc < 16) {
      if (*str == ' ' && !quoting) {
	argv[argc++] = str+1;
	*str = 0;
      } else if (*str == '"' || *str == '\'') {
	quoting = !quoting;
      }
      str++;
    }
    //
    if (!strcasecmp(argv[0],"malloc")) {
      fprintf(fw,"result=%u\n",ThreadMutexAllocate(1));
    } else if (!strcasecmp(argv[0],"lalloc")) {
      fprintf(fw,"result=%u\n",ThreadLockAllocate(1));
    } else if (!strcasecmp(argv[0],"trylock")) {
      if (argc < 2) {
	fprintf(fw,"missing argument\n");
      } else {
	unsigned num = atoi(argv[1]);
	fprintf(fw,"result=%d\n",ThreadMutexLock(num,LOCK_TRY));
      }
    } else if (!strcasecmp(argv[0],"trylockw")) {
      if (argc < 2) {
	fprintf(fw,"missing argument\n");
      } else {
	unsigned num = atoi(argv[1]);
	fprintf(fw,"result=%d\n",ThreadLockW(num,LOCK_TRY));
      }
    } else if (!strcasecmp(argv[0],"trylockr")) {
      if (argc < 2) {
	fprintf(fw,"missing argument\n");
      } else {
	unsigned num = atoi(argv[1]);
	fprintf(fw,"result=%d\n",ThreadLockR(num,LOCK_TRY));
      }
    } else if (!strcasecmp(argv[0],"lock")) {
      if (argc < 2) {
	fprintf(fw,"missing argument\n");
      } else {
	unsigned num = atoi(argv[1]);
	fprintf(fw,"locking\n"); fflush(fw);
	fprintf(fw,"lock result=%d\n",ThreadMutexLock(num,LOCK_FOD));
      }
    } else if (!strcasecmp(argv[0],"lockw")) {
      if (argc < 2) {
	fprintf(fw,"missing argument\n");
      } else {
	unsigned num = atoi(argv[1]);
	fprintf(fw,"locking\n"); fflush(fw);
	fprintf(fw,"lock result=%d\n",ThreadLockW(num,LOCK_FOD));
      }
    } else if (!strcasecmp(argv[0],"lockr")) {
      if (argc < 2) {
	fprintf(fw,"missing argument\n");
      } else {
	unsigned num = atoi(argv[1]);
	fprintf(fw,"locking\n"); fflush(fw);
	fprintf(fw,"lock result=%d\n",ThreadLockR(num,LOCK_FOD));
      }
    } else if (!strcasecmp(argv[0],"lockok")) {
      if (argc < 2) {
	fprintf(fw,"missing argument\n");
      } else {
	unsigned num = atoi(argv[1]);
	fprintf(fw,"locking\n"); fflush(fw);
	fprintf(fw,"lock result=%d\n",ThreadMutexLock(num,LOCK_SOD));
      }
    } else if (!strcasecmp(argv[0],"lockwok")) {
      if (argc < 2) {
	fprintf(fw,"missing argument\n");
      } else {
	unsigned num = atoi(argv[1]);
	fprintf(fw,"locking\n"); fflush(fw);
	fprintf(fw,"lock result=%d\n",ThreadLockW(num,LOCK_SOD));
      }
    } else if (!strcasecmp(argv[0],"lockrok")) {
      if (argc < 2) {
	fprintf(fw,"missing argument\n");
      } else {
	unsigned num = atoi(argv[1]);
	fprintf(fw,"locking\n"); fflush(fw);
	fprintf(fw,"lock result=%d\n",ThreadLockR(num,LOCK_SOD));
      }
    } else if (!strcasecmp(argv[0],"unlock")) {
      if (argc < 2) {
	fprintf(fw,"missing argument\n");
      } else {
	unsigned num = atoi(argv[1]);
	fprintf(fw,"result=%d\n",ThreadMutexUnlock(num));
      }
    } else if (!strcasecmp(argv[0],"unlockw")) {
      if (argc < 2) {
	fprintf(fw,"missing argument\n");
      } else {
	unsigned num = atoi(argv[1]);
	fprintf(fw,"result=%d\n",ThreadUnlockW(num));
      }
    } else if (!strcasecmp(argv[0],"unlockr")) {
      if (argc < 2) {
	fprintf(fw,"missing argument\n");
      } else {
	unsigned num = atoi(argv[1]);
	fprintf(fw,"result=%d\n",ThreadUnlockR(num));
      }
    } else if (!strcasecmp(argv[0],"dump")) {
      dump(fw);
    } else if (!strcasecmp(argv[0],"me")) {
      Thread *me = pthread_getspecific(threadKey);
      assertf(me,"");
      fprintf(fw,"ob=%p,tid=%d,pid=%d,socket=%d\n",
	      me,me->tid,me->pid,me->socket);
    } else {
      fprintf(fw,"unknown command:%s\n",argv[0]);
    }
    fflush(fw);
    /*
    for(i=0;i<argc;i++) {
      fprintf(fw,"%d:%s\n",i,argv[i]);
    }
    fflush(fw);
    */
  }
  LogReturn("%p",0);
}

#include "ServerTCP.h"

int main(int argc,char *argv[]) {
  int i;
  ThreadInit();
  ServerTCPInfo info;
  info.port = 8000;
  info.f1 = Server;
  info.f2 = 0;
  ThreadNew("test",1,ServerTCP,-1,&info,0);
  while(1) sleep(1);
}
#endif
/*
  regression testing

  We have a test which obtains several locks and makes sure that no deadlock 
  occurs. It then unlocks and makes sure they are released.

  We need something a bit more rigorous. One idea would be to automate the 
  process of determining what locks to acquire or release, and what the 
  current state of locks and waits are under those conditions
   We could then feed these results to our test program to check it.
  We could also try get obtain a metric as to how stressful our test was.
  We start with a set of N locks given.  We then open up to M connections at a
  time.  Each step we determine with a given probability what to do next: open
  a connection, close an open connection at random, try to lock a random lock 
  on a given connection at random, or unlock a randomly held lock on a given
  connection.
  The more connections that are open, the lower the probability should be that
  we open another connection and the higher the probability that we will close
  one.
 */
#if 0
int topLevelTest() {
  while (1) {
    // generate a pseudo-random number
    if (random_action_open_connection) {
      // open connection
    } else if (random_action_close_connection) {
      // close connection
      // update state model
      // compare state model against actual
    } else if (random_action_acquire_lock) {
      // update state model
      // acquire lock
      // compare state model against actual      
    } else if (random_action_release_lock) {
      // update state model
      // release lock
      // compare state model against actual
    }
  }
}
#endif
