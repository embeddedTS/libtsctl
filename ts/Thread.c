#ifndef Thread_C
#define Thread_C
#ifdef THREAD_USE_POSIX
#ifndef __USE_UNIX98
#define __USE_UNIX98
#endif
#ifndef _XOPEN_SOURCE
#define _XOPEN_SOURCE 600
#endif
#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif
#include "PThread.c"
#else
#include "NoThread.c"
#endif
#endif
