/*
  Creating an efficient logging framework that can enable or disable
  logging on a per-file or per-function basis, either at compile-time
  or run-time, without requiring any change to the actual code to
  change what is logged.
 */

#include <stdarg.h>
#include <sys/time.h>
#include <string.h>
#include <pthread.h>
#include <stdio.h>
#include "Log.h"
#include "Thread.h"
#include "HashTable.h"

/*
    for (i=0;i<logconns;i++) {
      if (flags & LC[i].flags) {
	if (LC[i].flags & LOG_TIME) {
	}
	if (write(LC[i].socket,str,len) <= 0) {
	  close(LC[i].socket);
	  for (j=i;j<logconns-1;j++) {
	    LC[j] = LC[j+1];
	  }
	  logconns--;
	  logflags = 0;
	  for (j=0;j<logconns;j++) {
	    logflags |= LC[j].flags;
	  }
	  i--; // so i++ won't skip next element
	}
      }
    }

 */
pthread_mutex_t loglock = PTHREAD_MUTEX_INITIALIZER;

void _log8(int flags,char *buffer,int len) {
  write(2,buffer,len);
}
static int LogFlags=-1;
int LogMin=0,LogMax=0x7FFFFFFF;
static unsigned LogMutex;
int LogStackDepth;

void log8(int flags,char *file, int line, const char *func, char *format,...) {
  if ((LogFlags & flags) == 0) return;
  va_list ap;

  va_start(ap, format);
  int i,j,len0,len,len2,len3,len4;
  char dummy[1];

  len0 = len = vsnprintf(dummy,0,format,ap);
  if (LogFlags & LOG_FILELINE) {
    len2 = snprintf(dummy,0,"%s:%d:",file,line);
    len += len2;
  }
  if (LogFlags & LOG_FUNCTION) {
    len3 = 1+strlen(func);
    len += len3;
  }
  if (LogFlags & LOG_DEPTH) {
    len4 = snprintf(dummy,0,"%d:",LogStackDepth);
    len += len4;
  }
  if (LogFlags & LOG_TIMESTAMP) len += 18;
  {
    char str[len+1],*s=str;
    if (LogFlags & LOG_TIMESTAMP) {
      struct timeval t;
      gettimeofday(&t,0);
      sprintf(s,"%10d.%06d:",t.tv_sec,t.tv_usec);
      s += 18;
    }
    if (LogFlags & LOG_DEPTH) {
      sprintf(s,"%d:",LogStackDepth);
      s += len4;
    }

    if (LogFlags & LOG_FILELINE) {
      sprintf(s,"%s:%d:",file,line);
      s += len2;
    }
    if (LogFlags & LOG_FUNCTION) {
      sprintf(s,"%s:",func);
      s += len3;
    }
    vsprintf(s,format,ap);
    s[len0] = '\n';

    ThreadMutexLock(LogMutex,LOCK_SOD);
    _log8(flags,str,len+1);
    ThreadMutexUnlock(LogMutex);
  }
  va_end(ap);
}

static HashTable *logfunc,*logfname;
static int excluding;

int LogInit(int excludeAll) { // initialize the logging system
  static int initialized = 0;
  if (initialized) return 1;
  initialized = 1;
  excluding = excludeAll ? 1 : 0;
  LogMutex = ThreadMutexAllocate(1);
  logfunc = HashTableNew(8,(hFcn)ASCIIZHash,(eFcn)ASCIIZEqual);
  logfname = HashTableNew(8,(hFcn)ASCIIZHash,(eFcn)ASCIIZEqual);
  return 1;
}

// return whether or not named file/func should be logged 
int LogQ(const char *file,const char *func) {
  LogInit(0); // just in case
  
  return (((int)HashTableLookup(logfunc,(void *)func)) ||
	  ((int)HashTableLookup(logfname,(void *)file)))
    == excluding;
}



int LogExcludeAll() {
  excluding = 1;
}

int LogIncludeAll() {
  excluding = 0;
}

int LogFlagsSet(int flags) { // set the flags of what to log
  LogFlags = flags;
  return 1;
}

int LogMaxDepth(int max) { // don't log anything above this stack depth
  LogMax = max;
  return 1;
}

int LogMinDepth(int min) { // don't log anything below this stack depth
  LogMin = min;
  return 1;
}

int LogFileAdd(char *fname) { // add file name to be included or excluded
  HashTableInsert(logfname,fname,(void *)1);
  return 1;
}

int LogFunctionAdd(char *name) { // add function name to be included/excluded
  HashTableInsert(logfunc,name,(void *)1);
  return 1;
}

#if 0
int main(int argc,char *argv[]) {
  LogEnter(int,main,"%d %p",argc,argv);
  Log(1,"%d",argc);
  LogReturn("%d",0);
}
#endif
