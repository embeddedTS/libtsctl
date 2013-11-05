#ifndef __NetTsctl_h
#define __NetTsctl_h

#include <setjmp.h>
#include "Stream.h"

#undef FUNC
#ifndef SWIGGY
#define FUNC(x) (*x) 
#else
#define FUNC(x) x
#endif

enum {
  NetModeBlocking=0, // all calls block until server returns completion
  NetModeNonBlocking=1, // calls to functions return void return immediately
  NetModeQueued=2 // we don't send commands to server until 
  // function returning non-void is called.
  // caller is responsible for making sure it doesn't queue too many
  // commands (and run out of transmit buffer space)
};

/* Currently unused, and obsolete as it no longer matches the Net structure
typedef struct Net Net;

struct Net {
  void *FUNC(Init)(void *me,...);
  void FUNC(Fini)(void *me);
  int InitStatus;
  int inst;
  int socket;
  int mode;
  Packet *q;
  int *cmds;
};
*/

typedef struct tsctl tsctl;
struct tsctl {
  jmp_buf exception;
  struct Stream *st;
  int mode,count;
};
tsctl *TsctlClient(char *host,int mode);
enum {
	NetSystemClass = 0,
	NetBusClass = 1,
	NetTimeClass = 2,
	NetPinClass = 3,
	NetDIORawClass = 4,
	NetDIOClass = 5,
	NetTWIClass = 6,
	NetCANClass = 7,
	NetSPIClass = 8,
	NetAIOClass = 9,
	NetEDIOClass = 10,
	NetModeClass = 11,
	Net_ClassCount=12
};

#include "NetSystem.h"
#include "NetBus.h"
#include "NetTime.h"
#include "NetPin.h"
#include "NetDIORaw.h"
#include "NetDIO.h"
#include "NetTWI.h"
#include "NetCAN.h"
#include "NetSPI.h"
#include "NetAIO.h"
#include "NetEDIO.h"

#endif
