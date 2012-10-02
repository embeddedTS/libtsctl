#define THREAD_USE_POSIX
#include "libtsctl.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

// test PThread.c

// test only valid if it unlocks everything it locks, and never unlocks
// something that is not already locked
int lock_test_valid(int n,int *cmd) {
  int rl=0,wl=0,i;

  for (i=0;i<n;i++) {
    switch (cmd[i]) {
    case 0: rl++; break;
    case 1: rl--; break;
    case 2: wl++; break;
    case 3: wl--; break;
    }
    if (rl < 0 || wl < 0) return 0;
  }
  return rl == 0 && wl == 0;
}

char *lock_name[] = { "RL","RU","WL","WU" };

// perform nth 2 step lock test
// n < (2^(2^2) = 16)
// unused as lock_test4 is a superset of it
void lock_test2(unsigned n) {
  int cmd[2];

  cmd[0] = (n>>2)&3;
  cmd[1] = n&3;
  if (!lock_test_valid(2,cmd)) return;
  printf("%s %s\n",lock_name[cmd[0]],lock_name[cmd[1]]);
}

// perform nth 4 step lock test
// n < (2^(2^4) = 256)
void lock_test4(unsigned n) {
  int i,cmd[4];

  cmd[0] = (n>>6)&3;
  cmd[1] = (n>>4)&3;
  cmd[2] = (n>>2)&3;
  cmd[3] = n&3;
  if (!lock_test_valid(4,cmd)) return;
  fprintf(stderr,"%3d ",n);
  for (i=0;i<4;i++) {
    fprintf(stderr,"%s ",lock_name[cmd[i]]);
    switch (cmd[i]) {
    case 0: ThreadLockR(2,LOCK_SOD); break;
    case 1: ThreadUnlockR(2); break;
    case 2: ThreadLockW(2,LOCK_SOD); break;
    case 3: ThreadUnlockW(2); break;
    }
  }
  fprintf(stderr,"\n");
}

// nth 6 step lock test would require 2^(2^6) = 2^64 iterations!

void *msg1;

/*
multi-thread tests:
1. second thread can acquire read lock when first thread holds it
RL1 RL2 RU2 RU1
2. second thread cannot acquire read lock until first thread releases write lock
3. second thread cannot acquire write lock until first thread releases write lock
4. second thread cannot acquire write lock until first thread releases read lock

In general:
start one thread whose purpose is to acquire a lock
wait for that thread to acquire the lock
start second thread whose purpose is to acquire a lock
verify that lock is correctly acquired or not acquired, depending on test
message first thread to release lock
 */
void *test1(void *arg) {
  Thread *th = arg;
  int i;

  usleep(10000);
  //fprintf(stderr,"thread %d started, tid=%d\n",th->pid,th->tid);
  // test recursive read/write locking by a single thread
  for (i=0;i<256;i++) {
    lock_test4(i);
  }
  ThreadMsgSend(1,&msg1,&msg1);
  //fprintf(stderr,"thread %d/%d finished\n",th->pid,th->tid);
}

#define V(x) ((void *)x)

enum {
  MSG_LOCKW=0x100, MSG_LOCKR=0x200, MSG_UNLOCKW=0x300, MSG_UNLOCKR=0x400, 
  MSG_QUIT=0x500
};

char *msgname(int cmd) {
  switch (cmd & 0xFFFF) {
  case MSG_LOCKW: return "MSG_LOCKW";
  case MSG_LOCKR: return "MSG_LOCKR";
  case MSG_UNLOCKW: return "MSG_UNLOCKW";
  case MSG_UNLOCKR: return "MSG_UNLOCKR";
  case MSG_QUIT: return "MSG_QUIT";
  }
  return "???";
}


typedef struct {
  int tx,rx;
  void *msgtx,*msgrx;
} test3info;


void *test3(void *arg) {
  Thread *th = arg;
  test3info *info = th->data;
  int ret=1;

  while (1) {
    // send result of previous command, then wait for next command and process
    ThreadMsgSend(info->rx,&info->msgrx,V(ret));
    ret = (int)ThreadMsgRecv(info->tx,&info->msgtx);
    switch (ret & 0xFF00) {
    case MSG_LOCKW: ret = ThreadLockW(ret & 0xFF,LOCK_SOD); break;
    case MSG_LOCKR: ret = ThreadLockR(ret & 0xFF,LOCK_SOD); break;
    case MSG_UNLOCKW: ret = ThreadUnlockW(ret & 0xFF); break;
    case MSG_UNLOCKR: ret = ThreadUnlockR(ret & 0xFF); break;
    case MSG_QUIT: return 0;
    default: ret = -999;
    }
  }
}

int runtest1 = 0;
int runtest2 = 0;
int runtest3 = 0;

int main(int argc,char *argv[]) {
  int n=1,ret,i;

  ThreadInit();
  ThreadLockAllocate(100);
  if (runtest1) {
    ThreadNew("test1",0,test1,0,0,0);
    ThreadMsgRecv(1,&msg1);
  }

 test4:
  ;
  test3info *test3infoNew() {
    test3info *ret = malloc(sizeof(test3info));
    ret->tx = ThreadLockAllocate(2);
    ret->rx = ret->tx + 1;
    ret->msgtx = ret->msgrx = 0;
    return ret;
  }

  test3info *ThreadStart() {
    static int test3count = 1;
    test3info *t3 = test3infoNew();
    int ret;

    ThreadNew("test3",test3count++,test3,0,t3,0);
    ret = (int)ThreadMsgRecv(t3->rx,&t3->msgrx);
    if (ret != 1) {
      free(t3);
      return 0;
    }
    return t3;
  }

  void ThreadFinish(test3info *t3) {
    ThreadMsgSend(t3->tx,&t3->msgtx,V(MSG_QUIT));
    free(t3);
  }

  int ThreadCmdExpectSuccess(test3info *t3,int command) {
    ThreadMsgSend(t3->tx,&t3->msgtx,V(command));
    return (int)ThreadMsgRecv(t3->rx,&t3->msgrx);
  }

  int ThreadCmdExpectBlocking(test3info *t3,int command) {
    ThreadMsgSend(t3->tx,&t3->msgtx,V(command));
    usleep(100000);
    if (t3->msgrx == 0) {
      return 1;
    } else {
      return -1;
    }
  }

  int ThreadCmdExpectCompletion(test3info *t3) {
    return (int)ThreadMsgRecv(t3->rx,&t3->msgrx);
  }

  static test3info* *th = 0;

  int ThreadInterpret(char* commands) {

    char** cmds = split(commands,' ');
    char *end,*end2;
    int i,j,ret,tn,cmd,rw,lu,ln,mode;
    for (i=0;i<ArrayLength(cmds);i++) {
      if (!strcmp(cmds[i],"ENDALL")) {
	for (j=0;j<ArrayLength(th);j++) {
	  ThreadFinish(th[j]);
	  free(th[j]);
	}
	ArrayFree(th);
	th = 0;
	continue;
      }
      fprintf(stderr,"%s ",cmds[i]);
      tn = strtoul(cmds[i],&end,0);
      rw = lu = -1;
      if (end[0] == 'R') {
	rw = 1;
      } else if (end[0] == 'W') {
	rw = 0;
      }
      if (end[1] == 'L') {
	lu = 1;
      } else if (end[1] == 'U') {
	lu = 0;
      }
      if (rw == -1 || lu == -1) {
	fprintf(stderr,"* ");
	continue;
      }
      ln = strtoul(end+2,&end2,0);
      switch (rw + 2*lu) {
      case 0: cmd = MSG_UNLOCKW; break;
      case 1: cmd = MSG_UNLOCKR; break;
      case 2: cmd = MSG_LOCKW; break;
      case 3: cmd = MSG_LOCKR; break;
      }
      if (end2[0] == '?') mode = 1;
      else if (end2[0] == '+') mode = 2;
      else mode = 0;
      if (th == 0) {
	th = ArrayAlloc(tn+1,sizeof(test3info *));
	for (j=0;j<=tn;j++) th[j] = ThreadStart();
      } else if (tn >= ArrayLength(th)) {
	j = ArrayLength(th);
	th = ArraySize(th,tn+1);
	for (;j<=tn;j++) th[j] = ThreadStart();
      }
      //printf("%d,%d,%s<%d> ",tn,ln,msgname(cmd),mode);
      switch (mode) {
      case 0:
	//printf("ThreadCmdExpectSuccess(%d,%s,%d)\n",tn,msgname(cmd),ln);
	assert(ThreadCmdExpectSuccess(th[tn],cmd+ln)==1);
	break;
      case 1:
	//printf("ThreadCmdExpectBlocking(%d,%s,%d)\n",tn,msgname(cmd),ln);
	assert(ThreadCmdExpectBlocking(th[tn],cmd+ln)==1);
	break;
      case 2:
	//printf("ThreadCmdExpectCompletion(%d,%s,%d)\n",tn,msgname(cmd),ln);
	assert(ThreadCmdExpectCompletion(th[tn])==1);
	break;
      }
    }
    fprintf(stderr,"\n");
    return 1;
  }

  // the following will assert fail since we don't own the lock!
  //ThreadInterpret(ASCIIZLocal("1RL10 2RU10"));

  ThreadInterpret(ASCIIZLocal("1RL10 2RL10 1RU10 2RU10"));
  ThreadInterpret(ASCIIZLocal("1WL10 2RL10? 1WU10 2RL+ 2RU10"));
  ThreadInterpret(ASCIIZLocal("1RL10 2WL10? 1RU10 2WL+ 2WU10"));
  ThreadInterpret(ASCIIZLocal("1WL10 2WL10? 1WU10 2WL+ 2WU10"));
  ThreadInterpret(ASCIIZLocal("1RL10 2WL10? 3RL10? 1RU10 2WL+ 2WU10 3RL+ 3RU10"));
  ThreadInterpret(ASCIIZLocal("1RL10 2RL10 2WL10? 1RU10 2WL+ 2WU10 2RU10"));
  ThreadInterpret(ASCIIZLocal("1RL10 2RL10 2WL10? 3RL10? 1RU10 2WL+ 2WU10 3RL+ 3RU10 2RU10"));

  ThreadInterpret(ASCIIZLocal("1RL10 1WL10 1WU10 2RL10 2WL10? 3RL10? 1RU10 2WL+ 2WU10 3RL+ 3RU10"));

  ThreadInterpret(ASCIIZLocal("1WL11 2WL10"));
  ThreadFinish(th[1]);
  sleep(1);
  th[1] = ThreadStart();

  for (i=0;i<10;i++) {
    ThreadInterpret(ASCIIZLocal("2WL11 2WU11 1WL11"));
  
    ThreadFinish(th[1]);
    sleep(1);
    th[1] = ThreadStart();
  }

  ThreadInterpret(ASCIIZLocal("3WL10"));

  printf("done\n");
  // now make sure that if we have something locked and our thread is
  // killed, that it gets released


  ThreadInterpret(ASCIIZLocal("ENDALL"));

  return 0;
}
