#define THREAD_USE_POSIX
#include "libtsctl.h"
#include "mtrace.c"
#include "ts/tcp.c"
#include "ts/http.c"
#include <stdio.h>
#include <string.h>
#include "ts/Array.h"
#include "ts/Net.h"
#include "ts/shell.h"
#include "ts/IteratorHashTable.c"
#include "ts/Mode.h"

#include "command1.h"
#include "command.c"
#include "command1.c"
#include "Stream.c"
#include "LookupRef.c"

#include <readline/readline.h>
#include <readline/history.h>

//typedef long long int64;
//typedef unsigned long long uint64;

int iabs(int i) { return i>0 ? i : -i; }

CAN** CANArr;
#ifdef THREAD_USE_POSIX
static pthread_mutex_t CANmutex=PTHREAD_MUTEX_INITIALIZER;
#endif

static void alarmsig(int x) {
  int i;

  if (CANArr) {
    for (i=0;i<ArrayLength(CANArr);i++) {
      if (CANArr[i]) {
	CANArr[i]->Abort(CANArr[i]);
      }
    }
  }
}

char** str2args(char *str) {
  char** ret = ArrayAlloc(0,sizeof(char*));
  int n,len;
  while (*str) {
    while (*str && isspace(*str)) str++;
    if (!*str) break;
    len = 0;
    while (str[len] && !isspace(str[len])) len++;
    if (str[len]) str[len++] = 0;
    ret = ArrayQueue(ret,A(char*,ASCIIZ(str)));
    str += len;
  }
  return ret;
}

// convert argv style list of ASCIIZ arguments into Array of Array of bytes
// containing the current command, and advance argv to start of
// next command, if any
char** argv2args(char ***argv) {
  char** args, *semi;
  int i,j=0,bare_semicolon;

  args = ArrayAlloc(0,sizeof(char*));

  // find end of command, which is either when we run out of arguments,
  // or until we hit an argument ending with a semi-colon
  while ((*argv)[j] && !(semi=strchr((*argv)[j],';'))) {
    args = ArrayQueue(args,A(char*,ASCIIZ((*argv)[j++])));
  }
  
  // we assume that there is no whitespace in our command, as that has
  // already been used to parse it into arguments
  if (semi) {
    if (semi > (*argv)[j]) {
	// there is a command before the semi-colon;
	// append it to our command
	char* tmp = ArrayAlloc(semi-(*argv)[j],sizeof(char*));
	strncpy(tmp,(*argv)[j],j); tmp[j] = 0;
	args = ArrayQueue(args,A(char*,ASCIIZ(tmp)));
	(*argv)[j] = semi+1;
    } else {
      (*argv)[j]++;
    }
    if (!semi[1]) {
      j++;
    }
  }
  *argv += j;
  return args;
}

#ifdef DONT_USE_READLINE
char* readline1(char *host,char **stack) {
  char* buffer = ArrayAlloc(4096,sizeof(char));
  int i;

  buffer[0] = 0;
  fprintf(stderr,"tsctl");
  if (host) fprintf(stderr," %s",host);
  for (i=0;i<ArrayLength(stack);i++) {
    fprintf(stderr," %s",stack[i]);
  }     
  fprintf(stderr,"> ");
  fflush(stdout);
  fgets(buffer,4096,stdin);
  return buffer;
}
#else
char* readline1(char *host,char **stack) {
  char *buf;
  char* buffer,* prompt;
  int i;

  prompt = ASCIIZ("tsctl");
  if (host) {
    prompt = ArrayQueue(prompt,A(char,' '));
    prompt = ArrayAppend(prompt,host);
  }
  for (i=0;i<ArrayLength(stack);i++) { 
    prompt = ArrayQueue(prompt,A(char,' '));
    prompt = ArrayAppend(prompt,stack[i]);
  }
  prompt = ArrayQueue(prompt,A(char,'>'));
  prompt = ArrayQueue(prompt,A(char,' '));
  
  buf = readline(prompt);
  ArrayFree(prompt);
  if (buf && buf[0] != 0) add_history(buf);
  if (!buf) {
    return 0;
  } if (buf[0] == 0) {
    buffer = ASCIIZ("\n");
  } else {
    buffer = ASCIIZ(buf);
  }
  free(buf);
  return buffer;
}
#endif

// read array of commands terminated by newline or EOF
// a semi-colon terminates commands in the command array
char*** ReadTsctlCommands(Stream *in) {
  char*** cmd = ArrayAlloc(0,sizeof(char**));
  char** args=0;
  char* arg;
  int n,len,ch,ch2;

  while (!in->isEOF(in)) {
    // skip whitespace
    do {
      ch = in->ReadChar(in);
    } while (ch > 0 && isspace(ch) && ch != '\n');
    if (ch <= 0 || ch == '\n') break;
    len = 0;
    arg = ArrayAlloc(0,sizeof(char));
    // read argument
    while (ch > 0 && !isspace(ch) && ch != ';') {
      arg = ArrayQueue(arg,A(char,ch));
      ch = in->ReadChar(in);
    }
    ch2 = ch;
    if (ch2 > 0 && isspace(ch2) && ch2 != '\n') {
      while (ch2 > 0 && isspace(ch2) && ch2 != '\n') { 
	ch2 = in->ReadChar(in);
      }
      if (ch2 == '\n' || ch2 < 0) {
	ch = ch2;
      } else {
	in->Unread(in,ch2);
      }
    }
    if (ArrayLength(arg) > 0) { // argument found
      arg = ArrayQueue(arg,A(char,0));
      ArraySizeAuto(arg,ArrayLength(arg)-1);
      if (!args) args = ArrayAlloc(0,sizeof(char*));
      args = ArrayQueue(args,A(char*,arg));
      if (ch <= 0 || ch == ';' || ch == '\n') {
	cmd = ArrayQueue(cmd,A(char**,args));
	args = 0;
      }
    } else {
      ArrayFree(arg);
      if (ch == ';' || ch == '\n') {
	cmd = ArrayQueue(cmd,A(char**,args));
	args = 0;
      }
    }
    if (ch == '\n') break;
  }
  return cmd;
}

char*** StringToTsctlCommands(char* buf) {
  Stream *in;
  char*** cmds;

  in = (Stream *)StringStreamInit(&buf,&buf);
  cmds = ReadTsctlCommands(in);
  in->Fini(in);
  return cmds;
}

int printcmds(char*** cmds) {
  int i,j;
  for (i=0;i<ArrayLength(cmds);i++) {
    printf("%d:",i);
    if (cmds[i]) {
      for (j=0;j<ArrayLength(cmds[i]);j++) {
	printf("<%s>",cmds[i][j]);
      }
    }
    printf("\n");
  }
}

int ClientSocketNew(char *host,int port) {
  int			rc;            /* system calls return value storage */
  int            	s;             /* socket descriptor */
  struct addrinfo *result,*rp;
  struct addrinfo hints;
  char service[8];

  sprintf(service,"%d",port);
  memset(&hints,0,sizeof(struct addrinfo));
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;
  // next line commented out because when compiling for TS-4500 I get this:
  // error: `AI_NUMERICSERV' undeclared
  //hints.ai_flags = AI_NUMERICSERV;
  if (getaddrinfo(host,service,&hints,&result) < 0) {
    return -1;
  }
  for (rp=result; rp != NULL; rp = rp->ai_next) {
    s = socket(rp->ai_family, rp->ai_socktype,rp->ai_protocol);
    if (s < 0) continue;
    if (connect(s, rp->ai_addr, rp->ai_addrlen) != -1) break;
    close(s);
  }
  if (rp == NULL) return -1;
  freeaddrinfo(result);
  return s;
}

int serverRunning() {
  int socket = ClientSocketNew("127.0.0.1",5001);
  if (socket >= 0) {
    close(socket);
    return 1;
  }
  return 0;
}

// in=0 means interactive shell
// implement Stream type argv, or simply convert the args to a string
// tsctl_shell
//   reads commands from an input stream
//   commands consist of arguments separated by white-space
//   commands are separated by a newline or semi-colon
//   maintains a command stack which is enlarged with partial arguments
//     and shrunk with an empty command
int tsctl_shell(Stream *in,Stream *out) {
  int i,j,exception=0,socket=-1,count=0;
  char* host=0;
  char** stack = ArrayAlloc(0,sizeof(char *));
  char*** cmds;
  Stream *RequestStream, *ReplyStream, *OutputStream, *HostStream=0;
  int8 *RequestString;
  int8 *ReplyString;
  int8 *OutputString;
  LookupRef* lu;
  mode *mode1 = &ModeAssign;
  void *tmp=0,*tmp2=0;

  void setHost(char *host0) {
    if (socket >= 0) {
      close(socket);
      socket = -1;
    }
    if (host) ArrayFree(host);
    host = host0;
    if (HostStream) { // if socket >=0, HostStream should be non-null
      HostStream->Fini(HostStream);
      socket = -1;
    }
    socket = ClientSocketNew(host[0] == '@' ? host+1:host,5001);
    if (socket < 0) {
      fprintf(stderr,"Server error on %s: %m\n",host);
      exit(1);
    } else {
      HostStream = DescriptorStreamInit(socket,socket);
    }
  }

  if (!in) {
    printf("tsctl " LIBTSCTL_FULL_VERSION " (%s)\n",compiledate+7);
    printf("Type \"?\" to get context-sensitive help.\n");
    mode1 = &ModeNL;
    mode1->base = 10;
  }
  while (!exception) {
    if (!in) { // interactive, display prompt
      char* cmd0 = readline1(host,stack);
      if (!cmd0 || !cmd0[0]) {
	fprintf(stderr,"\n");
	return;
      }
      cmds = StringToTsctlCommands(cmd0);
      ArrayFree(cmd0);
    } else {
      if (in->isEOF(in)) return 1;
      cmds = ReadTsctlCommands(in);
    }
    if (ArrayLength(cmds) == 0) { // empty input, pop command stack
      if (ArrayLength(stack) > 0) { // if possible
	int q;
	ArrayFree(stack[ArrayLength(stack)-1]);
	stack = ArrayDelete(stack,-1,1);
      } else if (host) {
	ArrayFree(host);
	host = 0;
      }
      continue;
    }
    RequestString = ArrayAlloc(0,1);
    ReplyString = ArrayAlloc(0,1);
    OutputString = ArrayAlloc(0,1);
    RequestStream = StringStreamInit(&RequestString,&RequestString);
    ReplyStream = StringStreamInit(&ReplyString,&ReplyString);
    OutputStream = StringStreamInit(&OutputString,&OutputString);
    lu = LookupRefNew();
    for (i=0;i<ArrayLength(cmds);i++) {
      if (!cmds[i] || ArrayLength(cmds[i]) == 0) { // empty input,pop cmd stack
	if (ArrayLength(stack) > 0) { // if possible
	  ArrayFree(stack[ArrayLength(stack)-1]);	  
	  stack = ArrayDelete(stack,-1,1);
	} else if (host) {
	  ArrayFree(host);
	  host = 0;
	}
	if (cmds[i]) ArrayFree(cmds[i]);
      } else if (ArrayLength(cmds[i]) == 1 && ArrayLength(cmds[i][0]) == 3 
		 && cmds[i][0][0]=='e' 
		 && cmds[i][0][1]=='n' && cmds[i][0][2]=='d') {
	return 1;
      } else {
	if (ArrayLength(stack) == 0 && !host) { // first command might be host
	  if (cmds[i][0][0] != '@' && !isdigit(cmds[i][0][0])) {
	    host = 0;
	  } else {
	    setHost(ArrayDup(cmds[i][0]));
	    cmds[i] = ArrayDelete(cmds[i],0,1);
	    if (ArrayLength(cmds[i]) == 0) continue;
	  }
	}
	if (cmds[i][0][0] != '?' 
	    && ArrayLength(stack)+ArrayLength(cmds[i]) < 2) {
	  //stack = ArrayAppend(stack,cmds[i]); // command not yet specified
	  char** newargs = ArrayAlloc(ArrayLength(cmds[i]),sizeof(char*));
	  int q;
	  for (q=0;q<ArrayLength(cmds[i]);q++) {
	    newargs[q] = ArrayDup(cmds[i][q]);
	  }
	  stack = ArrayAppend(stack,newargs);
	} else {
	  int q;
	  char** cmdcopy = ArrayAlloc(ArrayLength(cmds[i]),sizeof(char*));;
	  for (q=0;q<ArrayLength(cmds[i]);q++) {
	    cmdcopy[q] = ArrayDup(cmds[i][q]);
	  }
	  char** cmd = ArrayJoin(stack,cmdcopy);
	  int ret = tsctlCommandParse(RequestStream,&lu,cmd);
	  if (ret == -6) { // insufficient args, so add to stack
	    ArrayFree(stack);
	    stack = cmd;
	  } else if (ret < 0) {
	    // TO DO: directly output the exception
	  } else { // ok, we have a valid command to execute
	    count++;
	    if (ArrayLength(lu) > 0) { // patch lookups into the req stream
	      System *sys = SystemInit(0);
	      int val;
	      for (i=0;i<ArrayLength(lu);i++) {
		val = sys->MapLookup(sys,lu[i].name);
		for (j=0;j<ArrayLength(lu[i].offset);j++) {
		  RequestString[lu[i].offset[j]] = val & 0xFF;
		  RequestString[lu[i].offset[j]+1] = (val>>8) & 0xFF;
		  RequestString[lu[i].offset[j]+2] = (val>>16) & 0xFF;
		  RequestString[lu[i].offset[j]+3] = (val>>24) & 0xFF;
		}
	      }
	    }
	  }
	}
      }
    }
    //fprintf(stderr,"count=%d\n",count);
    ArrayFreeFreeFree(cmds);
    // at this point, i == ArrayLength(cmds)
    // i therefore contains the number of commands to run
    // if we are in host mode, then we can use this to count
    // the number of replies receives, so as to not continue until
    // all our current requests have been satisfied

    if (!host && serverRunning()) {
      setHost(ASCIIZ("@127.0.0.1"));
    }

    if (host) {
      WriteArray(HostStream,RequestString);
      while (count > 0 && !HostStream->isEOF(HostStream)) {
	if (coWriteTagged0(&tmp,&tmp2,OutputStream,HostStream,&mode1)) {
	  count--;
	}
      }
    } else {
      count = 0;
      int ret = tsctlDoCommand(ReplyStream,RequestStream);
      if (ret < 0 && in) exception = 1;
      while (!ReplyStream->isEOF(ReplyStream)) {
	coWriteTagged0(&tmp,&tmp2,OutputStream,ReplyStream,&mode1);
      }
    }
    WriteArray(out,OutputString);
    ArrayFree(RequestString);
    ArrayFree(ReplyString);
    ArrayFree(OutputString);
    RequestStream->Fini(RequestStream);
    ReplyStream->Fini(ReplyStream);
    OutputStream->Fini(OutputStream);
    LookupRefOld(lu);
  }
 tsctl_shell_done:
  for (i=0;i<ArrayLength(stack);i++) ArrayFree(stack[i]);
  ArrayFree(stack);
}

void *binaryServer(void *arg) {
  Thread *th = arg;
  int socket = th->socket;
  Stream *io = th->data;
  tsctlDoCommand(io,io);
  return 0;
}

int main(int argc,char *argv[]) {
  struct sigaction sa;
  Stream *stdioStream = (Stream *)FileStreamInit(stdin,stdout);
  int i;

  // catch alarms and interrupts and make sure CAN is cleanly shut down
  sa.sa_handler = alarmsig;
  sigemptyset(&sa.sa_mask);
  sa.sa_flags = 0;
  sigaction(SIGALRM, &sa, NULL);

  if (SignalCapture(SIGINT,alarmsig) < 0) {
    fprintf(stderr,"signal %d capture error:%m\n",SIGINT);
  }
  if (SignalCapture(SIGTERM,alarmsig) < 0) {
    fprintf(stderr,"signal %d capture error:%m\n",SIGTERM);
  }
  if (SignalCapture(SIGHUP,alarmsig) < 0) {
    fprintf(stderr,"signal %d capture error:%m\n",SIGHUP);
  }

  EnumInit();

  if (argc < 2) return tsctl_shell(0,stdioStream);

  // argument "--" to read commands from stdin
  // argument "-f file" to read commands from file
  // otherwise, commands separated by a semi-colon as it's own argument

  if (argc == 2 && !strcmp(argv[1],"--server")) {
    ServerData sd,sd2;

    if (serverRunning()) {
      return 0;
    }
    sd.f = httpServer;
    sd.constor = httpServerConstor;
    sd.destor = httpServerDester;

    sd2.f = binaryServer;
    sd2.constor = httpServerConstor;
    sd2.destor = httpServerDester;

    SignalIgnore(SIGCHLD);
    SignalIgnore(SIGPIPE);

    printf("Server running\n");
    daemon(1,0); // remove if linking against uclibc with daemon/pthread bug

    ThreadInit();
    ThreadNew("http server",0,ServerTCP,-8000,&sd,0);
    ThreadNew("binary server",0,ServerTCP,-5001,&sd2,0);

    // or daemon(1,1) and avoid the following?
    for (i = 0; i < 3; i++) {
      if (fcntl(i, F_GETFD) ==-1) {
	dup2(i ? i-- : open("/dev/null", O_RDWR), i);
      }
    }
    // since we sleep here, sd and sd2 never go out of scope
    while (1) sleep(1);
  } else if (argc == 2 && !strcmp(argv[1],"--")) {
    tsctl_shell(stdioStream,stdioStream);
  } else if (argc == 3 && !strcmp(argv[1],"-f")) {
    FILE *f = fopen(argv[2],"r");
    if (!f) {
      fprintf(stderr,"Error opening %s: %m\n",argv[2]);
      return 1;
    }
    Stream *in = (Stream *)FileStreamInit(f,0);
    tsctl_shell(in,stdioStream);
    fclose(f);
  } else if (argc < 2) {
    int j;
    fprintf(stderr,"Usage:\n");
    fprintf(stderr,"\ttsctl --server\n");
    fprintf(stderr,"\ttsctl <Class[:Instance]> <Command> [Args...]\n");
    fprintf(stderr,"Where Class is one of the following:\n");
    for (j=0;j<ArrayLength(classname);j++) {
      fprintf(stderr,"%s ",classname[j]);
    }
    fprintf(stderr,"\n");
    return 1;
  } else {
    Stream *in;
    char*** cmds;
    char* cmd = ArrayAlloc(0,sizeof(char));
    char* arg;
    int i;
    for (i=1;i<argc;i++) {
      arg = ASCIIZ(argv[i]);
      cmd = ArrayAppend(cmd,arg);
      ArrayFree(arg);
      if (i+1 < argc) cmd = ArrayQueue(cmd,A(char,' '));
    }
    in = StringStreamInit(&cmd,&cmd);
    tsctl_shell(in,stdioStream);
  }
  return 0;
}
