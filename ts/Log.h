#ifndef __Log_h
#define __Log_h

#include <assert.h>
#include "cpp.h"

#define assertf(expr,fmt,...) if (!(expr)) { fprintf(stderr,"%s:%d:%s:" fmt "\n",__FILE__,__LINE__,__PRETTY_FUNCTION__,##__VA_ARGS__); exit(3); }

#ifdef LOGGING
extern int LogStackDepth,LogMin,LogMax;

#define LogEnter(format,...)			\
  static int LogState=-1;			\
  LogState = LogQ(__FILE__,__func__);		\
  LogStackDepth++;				\
  Log(LOG_ENTER,"I:" format,##__VA_ARGS__)

#define LogReturn(format,...) {			\
  Log(LOG_RETURN,"O:" format,##__VA_ARGS__);	\
  LogStackDepth--;				\
  return __VA_ARGS__; }


#define Log(flags,format,...) if (LogState && LogStackDepth >= LogMin && LogStackDepth <= LogMax) log8(flags,__FILE__,__LINE__,__PRETTY_FUNCTION__,format,##__VA_ARGS__)

int LogQ(const char *file,const char *func); // return whether or not named func should be logged

// functions to configure logging
int LogFlagsSet(int); // set the flags of what to log
int LogMaxDepth(int); // don't log anything above this stack depth
int LogMinDepth(int); // don't log anything below this stack depth
int LogInit(int excludeAll); // initialize the logging system
int LogFileAdd(char *); // add file name to be included or excluded
int LogFunctionAdd(char *); // add function name to be included or excluded
int LogExcludeAll();
int LogIncludeAll();

void _log8(int flags,char *buffer,int len) __attribute__ ((weak));
void log8(int flags,char *file, int line, const char *func, char *format,...);
#else
#define Log(flags,format,...)
#define LogEnter(format,...)
#define LogReturn(format,...) return __VA_ARGS__
#endif

enum {
  LOG_SYSTEM=0x01,
  LOG_BUS=0x02,
  LOG_TIME=0x04,
  LOG_PIN=0x08,
  LOG_DIORAW=0x10,
  LOG_DIO=0x20,
  LOG_TWI=0x40,
  LOG_CAN=0x80,
  LOG_SPI=0x100,
  LOG_ASSERT=0x100000,
  LOG_THREAD=0x200000,
  LOG_DIOCTL=0x400000,
  LOG_TIMESTAMP=0x800000,
  LOG_ENTER=0x10000000, LOG_RETURN=0x08000000, LOG_DEPTH=0x04000000,
  // the following are for LogFlags() only, not calls to Log()
  LOG_FILELINE=0x80000000, LOG_FUNCTION=0x40000000, LOG_THREADID=0x20000000,
  LOG_INFO=0xD0000000
};

#endif
