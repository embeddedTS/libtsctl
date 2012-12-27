#ifndef __Net2_h
#define __Net2_h
#include <setjmp.h>
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
#endif
