// Usage:
// 1. define exactly one of the following:
// #define LOCK_TYPE_EXCLUSIVE
// #define LOCK_TYPE_SHARED
// #define LOCK_TYPE_EXCLUSIVE_DEFERRED
// #define LOCK_TYPE_SHARED_DEFERRED
// note: deferred requires
//       1. only a single lock
//       2. deferlock for exclusive, deferlockW and deferlockR for shared
//       3. sub for sub-object to defer the lock to
// 2. define the class name
// #define LOCK_CLASS Bus
// 3. optionally define a callback on lock success function
// static inline void callbackFunction(Bus *bus) { }
// #define LOCK_CALLBACK callbackFunction
// 3. include this file where you want the lock functions defined
// #include "TSLock.h"
// 4. Call $(CLASS)LockInit in the $(CLASS)Init function.
// 5. If lock type is deferred, call $(CLASS)LockReal as needed

// To do: need to make all objects use the standard "LockBase" element
// to hold the starting lock number
// Second, need to pass an object pointer as the first arg of each function.
// third, need to use LockBase
#include "Thread.h"
#include "Lock.h"
#include "cpp.h"

#ifdef LOCK_TYPE_EXCLUSIVE
static inline unsigned TEMPLATE(LOCK_CLASS,LockInit)(LOCK_CLASS *ob,
						     unsigned lockCount) {
  return ob->LockBase = ThreadMutexAllocate(lockCount);
}

int TEMPLATE(LOCK_CLASS,Lock)(LOCK_CLASS *ob, unsigned num, int flags) {
  //if (flags & SHARED) return ErrorInvalidArgument;
  int ret = ThreadMutexLock(ob->LockBase+num,(flags & NONBLOCKING) ? 
			    LOCK_TRY :
			    (flags & NOUNLOCK) ? LOCK_FOD : LOCK_SOD);
#ifdef LOCK_CALLBACK
  if (ret > 0) LOCK_CALLBACK(ob,num);
#undef LOCK_CALLBACK
#endif
  return ret;
}

int TEMPLATE(LOCK_CLASS,Unlock)(LOCK_CLASS *ob, unsigned num, int flags) {
  //if (flags & SHARED) return ErrorInvalidArgument;
  return ThreadMutexUnlock(ob->LockBase+num);
}

int TEMPLATE(LOCK_CLASS,Preempt)(LOCK_CLASS *ob) {
  TEMPLATE(LOCK_CLASS,Unlock)(ob,0,0);
  sched_yield();
  TEMPLATE(LOCK_CLASS,Lock)(ob,0,0);
  return 1;
}

#undef LOCK_TYPE_EXCLUSIVE
#endif

#ifdef LOCK_TYPE_SHARED
static inline unsigned TEMPLATE(LOCK_CLASS,LockInit)(LOCK_CLASS *ob,
						     unsigned lockCount) {
  return ob->LockBase = ThreadLockAllocate(lockCount);
}

int TEMPLATE(LOCK_CLASS,Lock)(LOCK_CLASS *ob,unsigned num,int flags) {
  int ret;
  if (flags & SHARED) {
    ret = ThreadLockR(ob->LockBase+num,(flags & NONBLOCKING) ? 
		      LOCK_TRY :
		      (flags & NOUNLOCK) ? LOCK_FOD : LOCK_SOD);
  } else {
    ret = ThreadLockW(ob->LockBase+num,(flags & NONBLOCKING) ? 
		      LOCK_TRY :
		      (flags & NOUNLOCK) ? LOCK_FOD : LOCK_SOD);
  }
#ifdef LOCK_CALLBACK
  if (ret > 0) LOCK_CALLBACK(ob,num);
#undef LOCK_CALLBACK
#endif
  return ret;
}

int TEMPLATE(LOCK_CLASS,Unlock)(LOCK_CLASS *ob, unsigned num, int flags) {
  if (flags & SHARED) {
    return ThreadUnlockR(ob->LockBase+num);
  } else {
    return ThreadUnlockW(ob->LockBase+num);
  }
}

int TEMPLATE(LOCK_CLASS,Preempt)(LOCK_CLASS *ob) {
  return -1; // unimplemented
}

#undef LOCK_TYPE_SHARED
#endif

#ifdef LOCK_TYPE_EXCLUSIVE_DEFERRED
static inline unsigned TEMPLATE(LOCK_CLASS,LockInit)(LOCK_CLASS *ob) {
  ob->deferlock = 0;
}

int TEMPLATE(LOCK_CLASS,Lock)(LOCK_CLASS *ob, unsigned num, int flags) {
  //			      LockCallback f) {
  //if (flags & SHARED) return ErrorInvalidArgument;
  ob->deferlock++;
  return 1;    
}

int TEMPLATE(LOCK_CLASS,Unlock)(LOCK_CLASS *ob, unsigned num, int flags) {
  //if (flags & SHARED) return ErrorInvalidArgument;
  if (ob->deferlock) {
    ob->deferlock--;
  } else {
    ob->sub->Unlock(ob->sub,num,flags);
  }
  return 1;    
}

static inline int TEMPLATE(LOCK_CLASS,LockReal)(LOCK_CLASS *dio,int flags) {
  //if (flags & SHARED) return ErrorInvalidArgument;
  while (dio->deferlock) {
    dio->sub->Lock(dio->sub,0,0); // or flags
    dio->deferlock--;
  }
}

int TEMPLATE(LOCK_CLASS,Preempt)(LOCK_CLASS *ob) {
  return -1; // unimplemented
}

#undef LOCK_TYPE_EXCLUSIVE_DEFERRED
#endif

#ifdef LOCK_TYPE_SHARED_DEFERRED
static inline unsigned TEMPLATE(LOCK_CLASS,LockInit)(LOCK_CLASS *ob) {
  ob->deferlockR = ob->deferlockW = 0;
}

int TEMPLATE(LOCK_CLASS,Lock)(LOCK_CLASS *ob, unsigned num, int flags) {
//			      LockCallback f) {
  if (flags & SHARED) {
    ob->deferlockR++;
  } else {
    ob->deferlockW++;
  }
  return 1;    
}

int TEMPLATE(LOCK_CLASS,Unlock)(LOCK_CLASS *ob, unsigned num, int flags) {
  if (flags & SHARED) {
    if (ob->deferlockR) {
      ob->deferlockR--;
    } else {
      ob->sub->Unlock(ob->sub,num,flags);
    }
    return 1;    
  } else {
    if (ob->deferlockW) {
      ob->deferlockW--;
    } else {
      ob->sub->Unlock(ob->sub,num,flags);
    }
    return 1;    
  }
}

static inline int TEMPLATE(LOCK_CLASS,LockReal)(LOCK_CLASS *dio,int flags) {
  if (flags & SHARED) {
    while (dio->deferlockR) {
      dio->sub->Lock(dio->sub,0,SHARED); // or flags
      dio->deferlockR--;
    }
  } else {
    while (dio->deferlockW) {
      dio->sub->Lock(dio->sub,0,0); // or flags
      dio->deferlockW--;
    }
  }
}

int TEMPLATE(LOCK_CLASS,Preempt)(LOCK_CLASS *ob) {
  return -1; // unimplemented
}

#undef LOCK_TYPE_SHARED_DEFERRED
#endif

#ifdef LOCK_CLASS
#endif
#undef LOCK_CLASS
