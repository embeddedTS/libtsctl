#ifndef __Lock_h
#define __Lock_h
enum {
  NONBLOCKING=1, SHARED=2, NOUNLOCK=4,
  ErrorInvalidArgument=-1, ErrorUnimplemented=-999
};

typedef void (*LockCallback)(void *);

#endif
