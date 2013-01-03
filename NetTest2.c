#define THREAD_USE_POSIX
#include "nettsctl.h"
#include <stdlib.h>
#include <stdio.h>

int main(int argc,char *argv[]) {
  Time *t;
  int i;
  unsigned t0,t1,tot=0;
  tsctl *conn;

  conn = TsctlClient("127.0.0.1",NetModeBlocking);
  if (!conn) {
    perror("socket:");
    return 1;
  }
  t = NetTimeInit(conn,0);
  if (!t) {
    printf("Error initializing Time\n");
    return 1;
  }

  if (!setjmp(conn->exception)) {
    t0 = t->Tick(t);
    for (i=0;i<1000;i++) {
      t1 = t->Tick(t);
      if (t1 > t0) {
	tot += (t1-t0);
      } else {
	tot += (0xFFFFFFFF - t0) + t1;
      }
      t0 = t1;
    }
    printf("%uus avg round trip time\n",tot/i);
  } else {
    printf("exception at loop %d\n",i);
  }
}
