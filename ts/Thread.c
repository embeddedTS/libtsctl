#ifndef Thread_C
#define Thread_C
#ifdef THREAD_USE_POSIX
#define __USE_UNIX98
#define _XOPEN_SOURCE 600
#define _GNU_SOURCE
#include "PThread.c"
#else
#include "NoThread.c"
#endif
#endif
