#include "ts/co.h"

/*
reply parsing works as follows.
every reply is prefixed with an class#:cmd# header

our current output mode consists of an encoding and a base.  we call a
function corresponding to our current encoding and pass a base formatting
function corresponding to our class and command.

our reply handling functions are continuations, so that if we don't have
enough data to finish the output the continutation will pick up where it
left off when more data arrives.

Mode bases are:
  HEX=16
  DEC=10
  OCT=8
  ESC=-1 is escaped binary mode
  BIN=0 is binary mode
  note: any base accepted by WriteInt is valid
Mode encodings are:
  JSON is  "name": value,  entries
  ASSIGN is name=value pairs
  NL is values separated by newlines
  RAW is unseparated values, probably only useful for binary mode

In JSON and ASSIGN modes the name is appended by a number indicating how
many times that particular function has been called.  This is tracked in
the count variable.

We also have the global variable cmdname which has Arrays of command names
for each command for each class.

Upon input to the encoding function, the class#/cmd# has already been read
off the input and we are left with the actual data returned.

We must handle ESC and BIN mode differently from other bases, because our
WriteInt function can't handle these.

in binary output mode, all we really need to know if the length of the
data so we can copy it directly to the output.
int WriteArrayInt8AsBin(coParm,Stream *out,Stream *in,int base) {
  StreamCopy(out,in,1);
}
int WriteArrayInt16AsBin(coParm,Stream *out,Stream *in,int base) {
  WriteInt16LE(out,ReadInt16LE(in));
}

For escaped binary output, we must know the length of the data as well,
but instead of copying it directly to the output, we must filter it
through an escaping function which converts all special characters into
escape sequences.

 */
//int (****binarybasefunc)(coParm,Stream *,Stream *,int,int);
//int (****escapebasefunc)(coParm,Stream *,Stream *,int,int);

/*
JSON : encodefunc = WriteJSONVal
Assign : encodefunc = WriteAssignVal
NoAssign : encodefunc = WriteNLVal
Hex : base=16
Dec : base=10
Oct : base=8
AStr : ?
AHex : ?
ADec : ?
AOct : ?
 */
#if 0
typedef struct {
  int base;
  int abase;
  int (*encodefunc)(coParm,Stream *,Stream *,int,int,int **,
		    int (**)(coParm,Stream *,Stream *,int,int),
		    int,int);
} modeinfo;

int WriteJSONVal(coParm,Stream *out,Stream *in,int obj,int cmd,int** count,
		 int (**basefunc)(coParm,Stream *,Stream *,int,int),int base,
		 int abase);
int WriteAssignVal(coParm,Stream *out,Stream *in,int obj,int cmd,int** count,
		   int (**basefunc)(coParm,Stream *,Stream *,int,int),int base,
		   int abase);
int WriteNLVal(coParm,Stream *out,Stream *in,int obj,int cmd,int** count,
	       int (**basefunc)(coParm,Stream *,Stream *,int,int),int base,
	       int abase);
int WriteRawVal(coParm,Stream *out,Stream *in,int obj,int cmd,int** count,
		int (**basefunc)(coParm,Stream *,Stream *,int,int),int base,
		int abase);

#if 0
// generate output for as many commands in input as are available
// yields 0 if in the middle of a command but needs more input
// returns 1 when finished processing and no more input available
// UNUSED
int tsctlOutputReply(coParm,Stream *out,Stream *in,int** count,modeinfo *mode){
  coBeginContext;
  void *context;
  int16 class;
  int8 cmd;
  int (**basefunc)(coParm,Stream *,Stream *,int,int);
  int (**abasefunc)(coParm,Stream *,Stream *,int,int);
  coEndContext;

  coBegin;
  co(context) = 0;
  while (InputReady(in) > 0) {
    while (InputReady(in) < 3) coYield(0);
    co(class) = ReadInt16LE(in);
    co(cmd) = ReadInt8LE(in);
    if (co(class) == NetModeClass) {
      switch (co(cmd)) {
      case NetMode_JSON: mode->encodefunc = WriteJSONVal; break;
      case NetMode_Assign: mode->encodefunc = WriteAssignVal; break;
      case NetMode_NoAssign: mode->encodefunc = WriteNLVal; break;
      case NetMode_Hex: mode->base = 16; break;
      case NetMode_Dec: mode->base = 10; break;
      case NetMode_Oct: mode->base = 8; break;
      case NetMode_AStr: mode->abase = 0; break;
      case NetMode_AHex: mode->abase = 16; break;
      case NetMode_ADec: mode->abase = 10; break;
      case NetMode_AOct: mode->abase = 8; break;
      }
      continue;
    }
    if (mode->base > 1) {
      co(basefunc) = (int (**)(coParm,Stream *,Stream *,int,int))
	textbasefunc[co(class)][co(cmd)];
    } else if (mode->base == 0) {
      co(basefunc) = (int (**)(coParm,Stream *,Stream *,int,int))
	binarybasefunc[co(class)][co(cmd)];
    } else if (mode->base == -1) {
      co(basefunc) = (int (**)(coParm,Stream *,Stream *,int,int))
	escapebasefunc[co(class)][co(cmd)];
    }
    if (mode->abase > 1) {
      co(abasefunc) = (int (**)(coParm,Stream *,Stream *,int,int))
	textbasefunc[co(class)][co(cmd)];
    } else if (mode->abase == 0) {
      co(abasefunc) = (int (**)(coParm,Stream *,Stream *,int,int))
	binarybasefunc[co(class)][co(cmd)];
    } else if (mode->abase == -1) {
      co(abasefunc) = (int (**)(coParm,Stream *,Stream *,int,int))
	escapebasefunc[co(class)][co(cmd)];
    }
    while (!mode->encodefunc(&co(context),out,in,co(class),co(cmd),count,
			     co(basefunc),mode->base,mode->abase)) {
      coYield(0);
    }
  }
  coReturn(1);
}
#endif

int WriteJSONVal(coParm,Stream *out,Stream *in,int obj,int cmd,int** count,
		 int (**basefunc)(coParm,Stream *,Stream *,int,int),int base,
		 int abase) {
      coBeginContext;
      void *context;
      int i;
      coEndContext;

      coBegin;
      co(context) = 0;
      for (co(i)=0;co(i) < ArrayLength(basefunc);co(i)++) {
	WriteChar(out,'"');
	WriteASCIIZ(out,cmdname[obj][cmd]);
	WriteInt(out,count[obj][cmd]++,10,0,0);
	WriteChar(out,'"');
	WriteChar(out,',');
	while (!basefunc[co(i)](&co(context),out,in,base,abase)) coYield(0);
	WriteChar(out,',');
	WriteChar(out,'\n');
      }
      coReturn(1);
}

int WriteAssignVal(coParm,Stream *out,Stream *in,int obj,int cmd,int** count,
		   int (**basefunc)(coParm,Stream *,Stream *,int,int),int base,
		   int abase) {
      coBeginContext;
      void *context;
      int i;
      coEndContext;

      coBegin;
      co(context) = 0;
      for (co(i)=0;co(i) < ArrayLength(basefunc);co(i)++) {
	WriteASCIIZ(out,cmdname[obj][cmd]);
	WriteChar(out,'_');
	WriteInt(out,count[obj][cmd]++,10,0,0);
	WriteChar(out,'=');
	while (!basefunc[co(i)](&co(context),out,in,base,abase)) coYield(0);
	WriteChar(out,'\n');
      }
      coReturn(1);
}

int WriteNLVal(coParm,Stream *out,Stream *in,int obj,int cmd,int** count,
	       int (**basefunc)(coParm,Stream *,Stream *,int,int),int base,
	       int abase) {
      coBeginContext;
      void *context;
      int i;
      coEndContext;

      coBegin;
      for (co(i)=0;co(i) < ArrayLength(basefunc);co(i)++) {
	co(context) = 0;
	while (!basefunc[co(i)](&co(context),out,in,base,abase)) coYield(0);
	WriteChar(out,'\n');
      }
      coReturn(1);
}

int WriteRawVal(coParm,Stream *out,Stream *in,int obj,int cmd,int** count,
		int (**basefunc)(coParm,Stream *,Stream *,int,int),int base,
		int abase) {
      coBeginContext;
      void *context;
      int i;
      coEndContext;

      coBegin;
      co(context) = 0;
      for (co(i)=0;co(i) < ArrayLength(basefunc);co(i)++) {
	while (!basefunc[co(i)](&co(context),out,in,base,abase)) coYield(0);
      }
      coReturn(1);
}
#endif
/*
What functions need to be implemented for Bin and Esc?
WriteArrayInt8*
WriteArrayUInt8*
WriteArrayInt16*
WriteArrayInt32*
WriteArrayUInt32*
WriteArrayReal32*
WriteVoid*
WriteInt8*
WriteInt16*
WriteInt32*
WriteUInt8*
WriteUInt16*
WriteUInt32*

what is missing?
ArrayUInt16, Real32
 */
int WriteArrayInt8Bin(coParm,Stream *out,Stream *in,int base,int abase) {
  WriteInt8LE(out,ReadInt8LE(in));
}

int WriteArrayUInt8Bin(coParm,Stream *out,Stream *in,int base,int abase) {
}

int WriteArrayInt16Bin(coParm,Stream *out,Stream *in,int base,int abase) {
}

int WriteArrayInt32Bin(coParm,Stream *out,Stream *in,int base,int abase) {
}

int WriteArrayUInt32Bin(coParm,Stream *out,Stream *in,int base,int abase) {
}

int WriteArrayReal32Bin(coParm,Stream *out,Stream *in,int base,int abase) {
  // TO DO
}

int WriteVoidBin(coParm,Stream *out,Stream *in,int base,int abase) {
}

int WriteInt8Bin(coParm,Stream *out,Stream *in,int base,int abase) {
}
int WriteInt16Bin(coParm,Stream *out,Stream *in,int base,int abase) {
}
int WriteInt32Bin(coParm,Stream *out,Stream *in,int base,int abase) {
}
int WriteUInt8Bin(coParm,Stream *out,Stream *in,int base,int abase) {
}
int WriteUInt16Bin(coParm,Stream *out,Stream *in,int base,int abase) {
}
int WriteUInt32Bin(coParm,Stream *out,Stream *in,int base,int abase) {
}

// =================================

int WriteArrayInt8Esc(coParm,Stream *out,Stream *in,int base,int abase) {
  int8 ch = ReadInt8LE(in);
  if (ch < 32 || ch > 126) {
    out->WriteChar(out,'\\');
    out->WriteChar(out,'x');
    WriteInt(out,ch,8,3,'0');
  } else {
    WriteInt8LE(out,ch);
  }
}

int WriteArrayUInt8Esc(coParm,Stream *out,Stream *in,int base,int abase) {
}

int WriteArrayInt16Esc(coParm,Stream *out,Stream *in,int base,int abase) {
}

int WriteArrayInt32Esc(coParm,Stream *out,Stream *in,int base,int abase) {
}

int WriteArrayUInt32Esc(coParm,Stream *out,Stream *in,int base,int abase) {
}

int WriteArrayReal32Esc(coParm,Stream *out,Stream *in,int base,int abase) {
  // TO DO
}

int WriteVoidEsc(coParm,Stream *out,Stream *in,int base,int abase) {
}

int WriteInt8Esc(coParm,Stream *out,Stream *in,int base,int abase) {
}
int WriteInt16Esc(coParm,Stream *out,Stream *in,int base,int abase) {
}
int WriteInt32Esc(coParm,Stream *out,Stream *in,int base,int abase) {
}
int WriteUInt8Esc(coParm,Stream *out,Stream *in,int base,int abase) {
}
int WriteUInt16Esc(coParm,Stream *out,Stream *in,int base,int abase) {
}
int WriteUInt32Esc(coParm,Stream *out,Stream *in,int base,int abase) {
}

// =================================
int WriteArrayInt8As(coParm,Stream *out,Stream *in,int base,int abase) {
  coBeginContext;
  unsigned length;
  coEndContext;
  int i;

  coBegin;
  while (in->InputReady(in) < 4) coYield(0);
  co(length) = ReadInt32LE(in);
  while (in->InputReady(in) < co(length)) coYield(0);
  for (i=0;i<co(length);i++) {
    WriteInt(out,ReadInt8LE(in),base,0,0);
    if (i+1<co(length)) out->WriteChar(out,':');
  }
  coReturn(1);
}

int WriteArrayUInt8As(coParm,Stream *out,Stream *in,int base,int abase) {
  coBeginContext;
  unsigned length;
  coEndContext;
  int i;

  coBegin;
  while (in->InputReady(in) < 4) coYield(0);
  co(length) = ReadInt32LE(in);
  while (in->InputReady(in) < co(length)) coYield(0);
  for (i=0;i<co(length);i++) {
    WriteUInt(out,ReadUInt8LE(in),base,0,0);
    if (i+1<co(length)) out->WriteChar(out,':');
  }
  coReturn(1);
}

int WriteArrayInt16As(coParm,Stream *out,Stream *in,int base,int abase) {
  coBeginContext;
  unsigned length;
  coEndContext;
  int i;

  coBegin;
  while (in->InputReady(in) < 4) coYield(0);
  co(length) = ReadInt32LE(in);
  while (in->InputReady(in) < co(length)) coYield(0);
  for (i=0;i<co(length);i++) {
    WriteInt(out,ReadInt16LE(in),base,0,0);
    if (i+1<co(length)) out->WriteChar(out,':');
  }
  coReturn(1);
}

int WriteArrayInt32As(coParm,Stream *out,Stream *in,int base,int abase) {
  coBeginContext;
  unsigned length;
  coEndContext;
  int i;

  coBegin;
  while (in->InputReady(in) < 4) coYield(0);
  co(length) = ReadInt32LE(in);
  while (in->InputReady(in) < co(length)) coYield(0);
  for (i=0;i<co(length);i++) {
    WriteInt(out,ReadInt32LE(in),base,0,0);
    if (i+1<co(length)) out->WriteChar(out,':');
  }
  coReturn(1);
}

int WriteArrayUInt32As(coParm,Stream *out,Stream *in,int base,int abase) {
  coBeginContext;
  unsigned length;
  coEndContext;
  int i;

  coBegin;
  while (in->InputReady(in) < 4) coYield(0);
  co(length) = ReadInt32LE(in);
  while (in->InputReady(in) < co(length)) coYield(0);
  for (i=0;i<co(length);i++) {
    WriteInt(out,ReadUInt32LE(in),base,0,0);
    if (i+1<co(length)) out->WriteChar(out,':');
  }
  coReturn(1);
}

int WriteArrayReal32As(coParm,Stream *out,Stream *in,int base,int abase) {
  // TO DO
}

int WriteVoidAs(coParm,Stream *out,Stream *in,int base,int abase) {
}

int WriteInt8As(coParm,Stream *out,Stream *in,int base,int abase) {
  if (in->InputReady(in) < 1) return 0;
  WriteInt(out,ReadInt8LE(in),base,0,0);
  return 1;
}
int WriteInt16As(coParm,Stream *out,Stream *in,int base,int abase) {
  if (in->InputReady(in) < 1) return 0;
  WriteInt(out,ReadInt16LE(in),base,0,0);
  return 1;
}
int WriteInt32As(coParm,Stream *out,Stream *in,int base,int abase) {
  if (in->InputReady(in) < 1) return 0;
  WriteInt(out,ReadInt32LE(in),base,0,0);
  return 1;
}
int WriteUInt8As(coParm,Stream *out,Stream *in,int base,int abase) {
  if (in->InputReady(in) < 1) return 0;
  WriteInt(out,ReadInt8LE(in),base,0,0);
  return 1;
}
int WriteUInt16As(coParm,Stream *out,Stream *in,int base,int abase) {
  if (in->InputReady(in) < 1) return 0;
  WriteUInt(out,ReadInt16LE(in),base,0,0);
  return 1;
}
int WriteUInt32As(coParm,Stream *out,Stream *in,int base,int abase) {
  if (in->InputReady(in) < 1) return 0;
  WriteUInt(out,ReadInt32LE(in),base,0,0);
  return 1;
}
//ArrayAuto(char*,invalidInstStr,ARR("invalid instance"));

//=================================
int tsctlDoCommand(Stream *out,Stream *in) {
  int class,inst,cmd;
  void (*cmdfunc)(void *,Stream *,Stream *);
  void *ob = 0;

  while (!in->isEOF(in)) {
    class = ReadInt16LE(in);
    inst = ReadInt8LE(in);
    cmd = ReadInt8LE(in);
    switch (class) {
    case NetSystemClass: ob = SystemInit(inst); break;
    case NetBusClass: ob = BusInit(inst); break;
    case NetTimeClass: ob = TimeInit(inst); break;
    case NetPinClass: ob = PinInit(inst); break;
    case NetDIORawClass: ob = DIORawInit(inst); break;
    case NetDIOClass: ob = DIOInit(inst); break;
    case NetTWIClass: ob = TWIInit(inst); break;
    case NetCANClass: ob = CANInit(inst); break;
    case NetSPIClass: ob = SPIInit(inst); break;
    case NetAIOClass: ob = AIOInit(inst); break;
    case NetEDIOClass: ob = EDIOInit(inst); break;
    case NetModeClass:
      if (cmd >= NetMode_JSON && cmd < XMode_APICount) {
	WriteInt16LE(out,class);
	WriteInt8LE(out,cmd);
	//WriteInt8LE(out,0x80); // end
	continue;
      }
    default: return -1;
    }
    if (class >= ArrayLength(docmd)) return -2;
    if (cmd >= ArrayLength(docmd[class])) return -3;
    //WriteInt16LE(out,class);
    //WriteInt8LE(out,cmd);
    if (ob == 0) {
      return tsctlException(out,8,ASCIIZ("invalid instance"),0);
    }
    cmdfunc = (void (*)(void *,Stream *,Stream *))docmd[class][cmd];
    cmdfunc(ob,out,in);
  }
  return 1;
}

/*
  exceptions
  class = System
  instance = ?
  cmd = NetSystem_Note

  int = exception number or error code
  char* = error string
 */
int tsctlException(Stream *out,int num,char* str,int request) {
  WriteUInt16LE(out,NetSystemClass);
  if (request) WriteUInt8LE(out,0);
  WriteUInt8LE(out,NetSystem_Note);

  //if (!request) WriteUInt8LE(out,0x13);
  //WriteUInt32LE(out,num);
  if (!request) WriteUInt8LE(out,0x50);
  WriteInt32LE(out,ArrayLength(str));
  WriteArray(out,str);
  //if (request) WriteUInt32LE(out,ArrayLength(str));
  if (!request) WriteUInt8LE(out,0x80);
  ArrayFree(str);
  return -num;
}

static void ListClassesHelper(Stream *st) {
  int i;
  WriteASCIIZ(st,"Class is one of the following:\n");
  for (i=0;i<ArrayLength(classname);i++) {
    WriteASCIIZ(st,classname[i]);
    st->WriteChar(st,' ');
  }
  st->WriteChar(st,'\n');
}

char* ObjNotSpecifiedStr() {
  char* ret = ArrayAlloc(0,1);
  Stream *st = StringStreamInit(0,&ret);
  ListClassesHelper(st);
  st->Fini(st);
  return ret;
}

char* ListClasses() {
  char* ret = ArrayAlloc(0,1);
  Stream *st = StringStreamInit(0,&ret);
  WriteASCIIZ(st,"\
tsctl expects commands separated by semi-colons or newlines.\n\
The format of each command is: [<@Host>] <Class> <Function> <Args...>\n\n\
Host is optional and must be preceded by the '@' character. If the\n\
Host is not specified, direct access to the hardware is performed unless\n\
tsctl server is already running, in which case the host 'localhost' is used.\n\n\
If you type a partial command, that command will be added to the\n\
'command stack', which is automatically prefixed to all subsequent commands.\n\
To pop the top element from the stack, enter an empty line.\n\n");
  ListClassesHelper(st);
  WriteASCIIZ(st,"\n\
To see a list of functions available for a given class, use the command:\n\
<Class> ?\n\
\n\
For a list of command-line options to tsctl, use the --help option.\n");
  st->Fini(st);
  return ret;
}

char* ObjNotFoundStr(char* class) {
  char* ret = ArrayAlloc(0,1);
  Stream *st = StringStreamInit(0,&ret);
  int i;
  WriteF(st,"Invalid class %s. Classes available:\n",class);
  for (i=0;i<ArrayLength(classname);i++) {
    WriteASCIIZ(st,classname[i]);
    st->WriteChar(st,' ');
  }
  st->WriteChar(st,'\n');
  st->Fini(st);
  return ret;
}

static void ListFunctionsHelper(Stream *st,int cl) {
  int i;
  WriteF(st,"Functions available for class %s:\n",classname[cl]);
  for (i=0;i<ArrayLength(cmdname[cl]);i++) {
    WriteASCIIZ(st,cmdname[cl][i]);
    st->WriteChar(st,' ');
  }
  WriteF(st,"\n\
To see the arguments expected for a given function, use the command:\n\
<%s> <Function> ?",classname[cl]);
}

char* CmdNotSpecifiedStr(char* class,int cl) {
  char* ret = ArrayAlloc(0,1);
  Stream *st = StringStreamInit(0,&ret);
  ListFunctionsHelper(st,cl);
  st->Fini(st);
  return ret;
}

char* CmdInvalidStr(char* class,int cl,char* cmd) {
  char* ret = ArrayAlloc(0,1);
  Stream *st = StringStreamInit(0,&ret);
  WriteF(st,"Invalid function %s.\n",
	 cmd,class);
  ListFunctionsHelper(st,cl);
  st->Fini(st);
  return ret;
}

static void ListArgsHelper(Stream *st,int cl,int cmdnum) {
  int i;
  WriteF(st,"Usage: %s %s ",classname[cl],cmdname[cl][cmdnum]);
  for (i=0;i<ArrayLength(ArgNames[cl][cmdnum]);i++) {
    WriteF(st,"<%s>",ArgNames[cl][cmdnum][i]);
    if (i+1<ArrayLength(ArgNames[cl][cmdnum])) st->WriteChar(st,' ');
  }
}

char* CmdTooManyArgs(int cl,int cmdnum,char* cmd) {
  char* ret = ArrayAlloc(0,1);
  Stream *st = StringStreamInit(0,&ret);
  WriteF(st,"Too many arguments to command %s.\n",cmd);

  ListArgsHelper(st,cl,cmdnum);
  st->Fini(st);
  return ret;
}

char* ListArgs(int cl,int cmdnum) {
  char* ret = ArrayAlloc(0,1);
  Stream *st = StringStreamInit(0,&ret);
  ListArgsHelper(st,cl,cmdnum);
  st->Fini(st);
  return ret;
}

// -1 = class not specified
// -2 = class not found
// -3 = command not specified
// -4 = command not found
// -5 = Init/Fini cannot be called directly
// -6 = insufficient arguments
// -7 = too many arguments
// -8 = instance not found
int tsctlCommandParse(Stream* out,LookupRef* *lu,char** args) {
  int class,inst=0,cmd,i;
  char *colon;

  if (ArrayLength(args) < 1) return tsctlException(out,1,ObjNotSpecifiedStr(),1);
  colon = strchr(args[0],':');
  if (colon) {
    inst = strtol(colon+1,0,0);
  }
  if (args[0][0] == '?') {
    return tsctlException(out,0,ListClasses(),1);
  }
  class = tsctlClassTextToBin(args[0]);
  if (class == -1) return tsctlException(out,2,ObjNotFoundStr(args[0]),1);
  if (ArrayLength(args) < 2) {
    return tsctlException(out,3,CmdNotSpecifiedStr(args[0],class),1);
  }
  if (args[1][0] == '?') {
    return tsctlException(out,0,CmdNotSpecifiedStr(args[0],class),1);
  }
  cmd = tsctlCommand[class](args[1]);
  if (cmd == -1) {
    return tsctlException(out,4,CmdInvalidStr(args[0],class,args[1]),1);
  }
  if (cmd < 2) return tsctlException(out,5,CmdInvalidStr(args[0],class,args[1]),1);
  cmd -= 2;
  if (ArrayLength(args) - 2 < ArrayLength(Args[class][cmd])) {
    if (args[ArrayLength(args)-1][0] == '?') {
      return tsctlException(out,0,ListArgs(class,cmd),1);
    } else return -6; // insufficient arguments
  }
  if (ArrayLength(args) - 2 > ArrayLength(Args[class][cmd])) {
    // too many arguments
    return tsctlException(out,7,CmdTooManyArgs(class,cmd,args[1]),1);
  }
  if (args[ArrayLength(args)-1][0] == '?') {
    return tsctlException(out,0,ListArgs(class,cmd),1);
  }
  // TO DO: experimenting with invalid class, instance, and command
  WriteInt16LE(out,class);
  WriteInt8LE(out,inst);
  WriteInt8LE(out,cmd);
  for (i=2;i<ArrayLength(args);i++) {
    int (*func)(Stream *,LookupRef **,char *) = Args[class][cmd][i-2];
    func(out,lu,args[i]);
  }
  return 1;
  // convert each arguments from text to stream
  // to do this we need:
  // 1. a way to map type numbers to conversion functions
  // 2. a conversion to stream function for each type
  
    /* So let's look at a concrete example of this.  Take the
       command DIO SetAsync GREEN_LED HIGH
       a this point we will already know that we have       class=5
       inst=0
       cmd=7
       and what we have left is "GREEN_LED", "HIGH"
       our autogenerated code for class 5, command 7 
       must parse 2 arguments of type int (DIOState enum is an int)
       
       But, whenever we have an integer argument, we must accept
       a (non-numeric) string as well. For that we put 0 in as the value,
       but create an entry in the lookup section.
       
       does the code really have to be auto-generated? probably not.
       in fact, we just need a table to look up the type of each argument,
       which returns the function to call.  The function will take the
       string argument and write out its value to the output stream,
       and possibly add a lookup to the table.

     */
}

// tsctlArgParseInt8 replaces Input_8
int tsctlArgParseInt8(Stream *out,LookupRef* *lu,char *arg) {
  int offset = out->outputOffset;
  int val = strtol(arg,0,0);
  WriteInt8LE(out,val);
  if (!val && arg[0] != '0') {
    LookupRef *entry = LookupRefName(lu,arg);
    entry->offset = ArrayQueue(entry->offset,A(int,offset));
  }
}

int tsctlArgParseInt16(Stream *out,LookupRef* *lu,char *arg) {
  int offset = out->outputOffset;
  int val = strtol(arg,0,0);
  WriteInt16LE(out,val);
  if (!val && arg[0] != '0') {
    LookupRef *entry = LookupRefName(lu,arg);
    entry->offset = ArrayQueue(entry->offset,A(int,offset));
  }
}

int tsctlArgParseInt32(Stream *out,LookupRef* *lu,char *arg) {
  int offset = out->outputOffset;
  int val = strtol(arg,0,0);
  WriteInt32LE(out,val);
  if (!val && arg[0] != '0') {
    LookupRef *entry = LookupRefName(lu,arg);
    entry->offset = ArrayQueue(entry->offset,A(int,offset));
  }
}

int tsctlArgParseUInt8(Stream *out,LookupRef* *lu,char *arg) {
  int offset = out->outputOffset;
  int val = strtoul(arg,0,0);
  WriteInt8LE(out,val);
  if (!val && arg[0] != '0') {
    LookupRef *entry = LookupRefName(lu,arg);
    entry->offset = ArrayQueue(entry->offset,A(int,offset));
  }
}

int tsctlArgParseUInt16(Stream *out,LookupRef* *lu,char *arg) {
  int offset = out->outputOffset;
  int val = strtoul(arg,0,0);
  WriteInt16LE(out,val);
  if (!val && arg[0] != '0') {
    LookupRef *entry = LookupRefName(lu,arg);
    entry->offset = ArrayQueue(entry->offset,A(int,offset));
  }
}

int tsctlArgParseUInt32(Stream *out,LookupRef* *lu,char *arg) {
  int offset = out->outputOffset;
  int val = strtoul(arg,0,0);
  WriteInt32LE(out,val);
  if (!val && arg[0] != '0') {
    LookupRef *entry = LookupRefName(lu,arg);
    entry->offset = ArrayQueue(entry->offset,A(int,offset));
  }
}

int tsctlArgParseArrayInt8(Stream *out,LookupRef* *lu,char *arg) {
  char** n = split(arg,':');
  int i;
  if (ArrayLength(n) > 1) {
    WriteInt32LE(out,ArrayLength(n));
    for (i=0;i<ArrayLength(n);i++) {
      WriteInt8LE(out,strtol(n[i],0,0));
    }
  } else {
    WriteInt32LE(out,ArrayLength(arg));
    WriteArray(out,arg);
  }
  ArrayFree(n);
}

int tsctlArgParseArrayInt16(Stream *out,LookupRef* *lu,char *arg) {
  char** n = split(arg,':');
  int i;
  short val;

  if (ArrayLength(n) > 1) {
    WriteInt32LE(out,ArrayLength(n));
    for (i=0;i<ArrayLength(n);i++) {
      val = strtol(n[i],0,0);
      if (!val && n[i][0] != '0') {
	int offset = out->outputOffset;
	LookupRef *entry = LookupRefName(lu,arg);
	entry->offset = ArrayQueue(entry->offset,A(int,offset));
      }
      WriteInt16LE(out,val);
    }
  } else {
    if (ArrayLength(arg) == 0) {
      WriteInt32LE(out,0);
    } else {
      WriteInt32LE(out,1);
      val = strtol(arg,0,0);
      if (!val && n[0][0] != '0') {
	int offset = out->outputOffset;
	LookupRef *entry = LookupRefName(lu,arg);
	entry->offset = ArrayQueue(entry->offset,A(int,offset));
      }
      WriteInt16LE(out,val);
    }
  }
  ArrayFree(n);
}

int tsctlArgParseArrayInt32(Stream *out,LookupRef* *lu,char *arg) {
  char** n = split(arg,':');
  int i,val;

  if (ArrayLength(n) > 1) {
    WriteInt32LE(out,ArrayLength(n));
    for (i=0;i<ArrayLength(n);i++) {
      val = strtol(n[i],0,0);
      if (!val && n[i][0] != '0') {
	int offset = out->outputOffset;
	LookupRef *entry = LookupRefName(lu,arg);
	entry->offset = ArrayQueue(entry->offset,A(int,offset));
      }
      WriteInt32LE(out,val);
    }
  } else {
    if (ArrayLength(arg) == 0) {
      WriteInt32LE(out,0);
    } else {
      WriteInt32LE(out,1);
      val = strtol(arg,0,0);
      if (!val && n[0][0] != '0') {
	int offset = out->outputOffset;
	LookupRef *entry = LookupRefName(lu,arg);
	entry->offset = ArrayQueue(entry->offset,A(int,offset));
      }
      WriteInt32LE(out,val);
    }
  }
  ArrayFree(n);
}

int tsctlArgParseArrayUInt8(Stream *out,LookupRef* *lu,char *arg) {
  char** n = split(arg,':');
  int i;
  if (ArrayLength(n) > 1) {
    WriteInt32LE(out,ArrayLength(n));
    for (i=0;i<ArrayLength(n);i++) {
      WriteInt8LE(out,strtoul(n[i],0,0));
    }
  } else {
    WriteInt32LE(out,ArrayLength(arg));
    WriteArray(out,arg);
  }
  ArrayFree(n);
}

int tsctlArgParseReal32(Stream *out,LookupRef* *lu,char *arg) {
  WriteReal32LE(out,strtof(arg,0));
}

int tsctlArgParseArrayReal32(Stream *out,LookupRef* *lu,char *arg) {
  char** n = split(arg,':');
  float f;
  int i;
  if (ArrayLength(n) > 1) {
    WriteInt32LE(out,ArrayLength(n));
    for (i=0;i<ArrayLength(n);i++) {
      WriteReal32LE(out,strtof(n[i],0));
    }
  } else {
    if (ArrayLength(arg) == 0) {
      WriteInt32LE(out,0);
    } else {
      WriteInt32LE(out,1);
      WriteReal32LE(out,strtof(arg,0));
    }
  }
  ArrayFree(n);
}

// IDEA FOR TAGGED DATA
// 1. header
// byte 0-1 = class
// byte 2   = function

// 2. fields
//    one entry for each field.  terminated by a void field
// byte 0
//  bit 7:6 = type
//            00 = number
//            01 = array of numbers
//            10 = structure
//            11 = void
// bit 5    = signed (number or array only)
// bit 4:0  = element width or structure length (1-32)
// byte 1-4 = array length (array only)


// TAGGED DATA
// consists of
// Array/NotArray Signed/Unsigned ElementWidth [ElementCount]
// byte 0 = Flags
//  bit 7 = Array
//  bit 6 = Signed
//  bit 5 = Struct
//  bit 4 = void (no element width follows)
//  bit 3 = Enum
// byte 1 = ElementWidth 1-256 (0 means 256)
//          if Struct bit is set, means the number of elements
//          if Enum bit is set, means the specified enum follows (32-bit)
// byte 2-5 present only if Array bit set, contains little-endian ElementCount
// if bit 5 is set, then bit 7 is implied (but should/must still be set)
// because data returned in structs must always be done via an Array, even
// however, if the array length is 1, then is this REALLY needed???
// if it is a fixed length 1 array.
// if bit 5 is set, each element is itself treated as tagged data
// fixme: if the struct is also an Array, then what?

// whether or not protocol data from the server is tagged should be a switch
// in the server itself.

// how does our auto-generated code tag data?
// idea: before
// WriteInt32LE(out,ArrayLength(arg3));
// we put:
// WriteInt8LE(out,0x40); // signed
// WriteInt8LE(out,4);    // 32 bits

#define WAITBYTES(n)  while (in->InputReady(in) < n) coYield(0);

typedef struct {
  int base,abase;
  void *(*InitState)(void **);
  void (*StartArray)(Stream *,void **,int,int,int);
  void (*EndArray)(Stream *,void **,int,int,int);
  void (*StartNonArray)(Stream *,void **,int,int,int);
  void (*EndNonArray)(Stream *,void **,int,int,int);
  void (*StartStruct)(Stream *,void **,int,int,int);
  void (*EndStruct)(Stream *,void **,int,int,int);
  void (*StartValue)(Stream *,void **,int,int);
  void (*EndValue)(Stream *,void **,int,int);
  void (*Separator)(Stream *,void **,int,int);
} mode;
// the mode, if needed, should define these functions such that
// as needed, it tracks the current position in the output 
// (using Start/End Array/Struct)
// and uses that to pick the correct tag to output for each value
//
// call mode->InitState() to initialize the state pointer before calling
// coWriteTagged, and free it when done.

/*
mode functions for:
1. JSON
2. Assign
3. NL
4. Raw
 */
mode ModeRaw = {
  .InitState = 0,
  .StartArray = 0,
  .EndArray = 0,
  .StartNonArray = 0,
  .EndNonArray = 0,
  .StartStruct = 0,
  .EndStruct = 0,
  .StartValue = 0,
  .EndValue = 0,
  .Separator = 0
};

static void ColonSeparator(Stream *out,void **state,int class,int func) {
  out->WriteChar(out,':');
}
static void NewlineSeparator(Stream *out,void **state,int class,int func,
			     int base) {
  int **count = *state;
  out->WriteChar(out,'\n');
  //count[class][func]++;
}

static void StartStruct(Stream *out,void **state,int class,int func,int index);
static void EndStruct(Stream *out,void **state,int class,int func,int index);

mode ModeNL = {
  .InitState = 0,
  .StartArray = 0,
  .EndArray = NewlineSeparator,
  .StartNonArray = 0,
  .EndNonArray = NewlineSeparator,
  .StartStruct = StartStruct,
  .EndStruct = EndStruct,
  .StartValue = 0,
  .EndValue = 0,
  .Separator = ColonSeparator,
  .base=16, .abase=-8
};

void ModeAssignInit(mode *mode) {
  /*
i'm not sure exactly what i was thinking when i decided we might need a
state area for each mode. i guess i could go back and look at my notes.
but i am not sure now if such a thing is really needed.
the only thing i think i need for mode assign is the counter array so
we can determine the number to append for each output
   */
}

typedef struct {
  int** count;
  int* stack; // of offset in Ret array
  int* index;
} internalstate;

void InitStateAssign(void **state) {
  int i,j,** count;
  internalstate *st = malloc(sizeof(internalstate));

  st->stack = ArrayAlloc(1,sizeof(int));
  st->stack[0] = 0;
  st->index = ArrayAlloc(0,sizeof(int));
  st->count = ArrayAlloc(ArrayLength(cmdname),sizeof(int**));
  for (i=0;i<ArrayLength(cmdname);i++) {
    st->count[i] = ArrayAlloc(ArrayLength(cmdname[i]),sizeof(int));
    for (j=0;j<ArrayLength(cmdname[i]);j++) {
      st->count[i][j] = 0;
    }
  }
  *state = st;
}

static void StartWithName(Stream *out,void **state,int class,int func,
			  int base) {
  if (!*state) InitStateAssign(state);
  int **count = ((internalstate *)(*state))->count;
  int *i = ((internalstate *)(*state))->stack;

  i += ArrayLength(i)-1;

  WriteASCIIZ(out,classname[class]);
  out->WriteChar(out,'_');
  WriteASCIIZ(out,cmdname[class][func]);
  out->WriteChar(out,'_');
  WriteInt(out,count[class][func],10,0,0);  

  if (*i >= ArrayLength(RetNames[class][func])) {
    fprintf(stderr,"error: assertion failure in StartWithName: %d>=%d\n",
	    *i,ArrayLength(RetNames[class][func]));
    exit(1);
  }
  if (RetNames[class][func][*i][0]) {
    int *index = ((internalstate *)(*state))->index;
    out->WriteChar(out,'_');
    switch (ArrayLength(index)) {
    case 0:
      WriteASCIIZ(out,RetNames[class][func][*i]);
      break;
    case 1:
      WriteF(out,RetNames[class][func][*i],index[0]);
      break;
    case 2:
      WriteF(out,RetNames[class][func][*i],index[0],index[1]);
      break;
    case 3:
      WriteF(out,RetNames[class][func][*i],index[0],index[1],index[2]);
      break;
    default:
      fprintf(stderr,"no support for more than 3 levels of structs\n");
      exit(1);
    }
  }
  (*i)++;

  out->WriteChar(out,'=');  
  if (base < 2) out->WriteChar(out,'"');  

}

static void EndWithQuote(Stream *out,void **state,int class,int func,
			 int base) {
  //int **count = ((internalstate *)(*state))->count;
  if (base < 2) out->WriteChar(out,'"');

  out->WriteChar(out,'\n');
  //count[class][func]++;
}

static void StartStruct(Stream *out,void **state,int class,int func,int index) {
  if (!*state) InitStateAssign(state);
  int *i = ((internalstate *)(*state))->stack;
  int n = i[ArrayLength(i)-1];
  
  ((internalstate *)(*state))->stack = ArrayQueue(i,A(int,n));
  ((internalstate *)(*state))->index = 
    ArrayQueue(((internalstate *)(*state))->index,A(int,index));
}

static void EndStruct(Stream *out,void **state,int class,int func,int index) {
  ((internalstate *)(*state))->stack = 
    ArrayDelete(((internalstate *)(*state))->stack,-1,1);
  ((internalstate *)(*state))->index = 
    ArrayDelete(((internalstate *)(*state))->index,-1,1);
}


// TO DO:
// state must contain
// 1. flag indicating whether counter is global or per-function
// 2. single counter or counter per function
mode ModeAssign = {
  .InitState = 0,
  .StartArray = StartWithName,
  .EndArray = EndWithQuote,
  .StartNonArray = StartWithName,
  .EndNonArray = NewlineSeparator,
  .StartStruct = StartStruct,
  .EndStruct = EndStruct,
  .StartValue = 0,
  .EndValue = 0,
  .Separator = ColonSeparator,
  .base=16, .abase=-8
};

/*
  JSON needs to start an array with '[', and it with ']', and separate it
  with ','.
 */
static void StartWithJSONName(Stream *out,void **state,int class,int func,
			      int base) {
  if (!*state) InitStateAssign(state);
  int **count = ((internalstate *)(*state))->count;
  int *i = ((internalstate *)(*state))->stack;

  i += ArrayLength(i)-1;

  out->WriteChar(out,'"');  
  WriteASCIIZ(out,classname[class]);
  out->WriteChar(out,'_');
  WriteASCIIZ(out,cmdname[class][func]);
  out->WriteChar(out,'_');
  WriteInt(out,count[class][func],10,0,0);  

  if (*i >= ArrayLength(RetNames[class][func])) {
    fprintf(stderr,"error: assertion failure in StartWithName\n");
    exit(1);
  }
  if (RetNames[class][func][*i][0]) {
    int *index = ((internalstate *)(*state))->index;
    out->WriteChar(out,'_');
    switch (ArrayLength(index)) {
    case 0:
      WriteASCIIZ(out,RetNames[class][func][*i]);
      break;
    case 1:
      WriteF(out,RetNames[class][func][*i],index[0]);
      break;
    case 2:
      WriteF(out,RetNames[class][func][*i],index[0],index[1]);
      break;
    case 3:
      WriteF(out,RetNames[class][func][*i],index[0],index[1],index[2]);
      break;
    default:
      fprintf(stderr,"no support for more than 3 levels of structs\n");
      exit(1);
    }
  }
  (*i)++;
  out->WriteChar(out,'"');  

  out->WriteChar(out,':');  
  //if (base < 2) out->WriteChar(out,'"');  
}

void JSONEndValue(Stream *out,void **state,int class,int func) {
  out->WriteChar(out,',');
}

mode ModeJSON = {
  .InitState = 0,
  .StartArray = StartWithJSONName,
  .EndArray = NewlineSeparator,
  .StartNonArray = StartWithJSONName,
  .EndNonArray = NewlineSeparator,
  .StartStruct = StartStruct,
  .EndStruct = EndStruct,
  .StartValue = 0,
  .EndValue = JSONEndValue,
  .Separator = ColonSeparator,
  .base=16, .abase=-1616
};

void ModeSet(mode **mode,int func) {
  switch(func) {
  case NetMode_JSON:
    ModeJSON.base = (*mode)->base;
    ModeJSON.abase = (*mode)->abase;
    *mode = &ModeJSON;
    break;
  case NetMode_Assign:
    ModeAssign.base = (*mode)->base;
    ModeAssign.abase = (*mode)->abase;
    *mode = &ModeAssign;
    break;
  case NetMode_NoAssign:
    ModeNL.base = (*mode)->base;
    ModeNL.abase = (*mode)->abase;
    *mode = &ModeNL;
    break;
  case NetMode_Hex:
    (*mode)->base = 16;
    break;
  case NetMode_Dec:
    (*mode)->base = 10;
    break;
  case NetMode_Oct:
    (*mode)->base = 8;
    break;
  case NetMode_AStr:
    *mode = &ModeRaw;
    break;
  case NetMode_AHex:
    (*mode)->abase = 16;
    break;
  case NetMode_ADec:
    (*mode)->abase = 10;
    break;
  case NetMode_AOct:
    (*mode)->abase = 8;
    break;
  case NetMode_ABinOct:
    (*mode)->abase = -8;
    break;
  case NetMode_ABinHex:
    (*mode)->abase = -16;
    break;
  case NetMode_ABinUni:
    (*mode)->abase = -1616;
    break;

  }
}

// processes one command per call
// this consists of a 3 byte header, followed by tags until we get a void
// tag.  coWriteTagged must return whether or not we got a void tag so we
// know when our function is done
int coWriteTagged0(coParm,void **state,Stream *out,Stream *in,mode **mode) {
  coBeginContext;
  void *sub; 
  int class,func,ret;
  coEndContext;
  coBegin;
  co(sub) = 0;
  WAITBYTES(3);
  co(class) = ReadInt16LE(in);
  co(func) = ReadInt8LE(in);
  if (co(class) == NetModeClass) {
    ModeSet(mode,co(func));
    coReturn(1);
  }
  while (1) {
    co(ret) = coWriteTagged(&co(sub),state,out,in,mode,co(class),co(func));
    if (co(ret) == -1) {
      if (*state) {
	int **count = ((internalstate *)(*state))->count;
	count[co(class)][co(func)]++;	
	int *i = ((internalstate *)(*state))->stack;
	if (ArrayLength(i) != 1) {
	  fprintf(stderr,"assert failure in coWriteTagged0\n");
	  exit(1);
	}
	*i = 0;
      }
      coReturn(1);
    }
    if (co(ret) == 0) coYield(0);
  }
}

typedef struct {
  unsigned bytes,enumn,i,j; // i and j are structdef indicies
  unsigned int signd:1, array:1, struc:1, enumx:1, real:1;
} varinfo;

int StreamCopyEscaped(Stream *out,Stream *in,unsigned len) {
  int i;
  int ch;
  for (i=0;i<len;i++) {
    ch = in->ReadChar(in);
    if (ch == '\n' || (ch >= 32 && ch <= 126 && ch != '\\')) {
      out->WriteChar(out,ch);
    } else {
      // \nnn is octal
      // \xnn is hexadecimal
      out->WriteChar(out,'\\');
      WriteUInt(out,ch,8,3,'0');
    }
  }
}

extern void** WriteEnum;
// coWriteTagged
// co-routine based Write allowing for incomplete output
// processes one tagged datum per call
int coWriteTagged(coParm,void **state,Stream *out,Stream *in,mode **mode,
		  int class,int func) {
  coBeginContext;
  int isSigned, width, isArray, length;
  int i,j,b;
  void *sub;
  coEndContext;
  int val;
  int8 byte;
  float f;
  double d;

  coBegin;
  //if (!*state && (*mode)->InitState) (*mode)->InitState(state);
  WAITBYTES(1);
  byte = ReadInt8LE(in);
  if (byte == 0x80) return -1; // void
  co(isArray) = ( ((byte & 0x80) == 0) && (byte & 0x40)) ? 1 : 0;
  if (co(isArray)) {
    WAITBYTES(4);
    co(length) = ReadInt32LE(in);
    if (co(length) > 1) {
      co(b) = (*mode)->abase;
    } else {
      co(b) = (*mode)->base;
    }
  } else {
    co(length) = 1;
    co(b) = (*mode)->base;
  }

  if ((byte & 0xC0) == 0xC0) {
    // enum
    WAITBYTES(4);
    val = ReadInt32LE(in);
    if (!co(isArray) && (*mode)->StartNonArray) {
      (*mode)->StartNonArray(out,state,class,func,co(b));
    }
    if ((*mode)->StartValue) {
      (*mode)->StartValue(out,state,class,func);
    }
    if ((byte & 0x3F) > ArrayLength(WriteEnum)) {
      // should not happen
      WriteInt(out,val,16,0,0);
    } else {
      int (*func)(Stream *,int) = WriteEnum[byte&0x3F];
      func(out,val);
    }
    if ((*mode)->EndValue) (*mode)->EndValue(out,state,class,func);
    if (!co(isArray) && (*mode)->EndNonArray) {
      (*mode)->EndNonArray(out,state,class,func,co(b));
    }
  } else if ((byte & 0xA0) == 0) { // integer
    co(isSigned) = (byte & 0x10) ? 1 : 0;
    co(width) = (byte & 0xF) + 1;
    if (co(b) < 0 && co(width) > 1) {
      co(b) = (*mode)->base;
    }
    WAITBYTES(co(width)*co(length));
    if (co(isArray) && (*mode)->StartArray) {
      (*mode)->StartArray(out,state,class,func,co(b));
    }
    if (!co(isArray) && (*mode)->StartNonArray) {
      (*mode)->StartNonArray(out,state,class,func,co(b));
    }
    for (co(i)=0;co(i)<co(length);co(i)++) {
      val = 0;
      if ((*mode)->StartValue) {
	(*mode)->StartValue(out,state,class,func);
      }
      if (co(b) == 0) { // binary
	for (co(j)=0;co(j)<co(width);co(j)++) {
	  out->WriteChar(out,in->ReadChar(in));
	}
      } else if (co(b) < 0) { // escaped
	val = in->ReadChar(in);
	if (val == '\n' || (val >= 32 && val <= 126 && val != '\\')) {
	  out->WriteChar(out,val);
	} else if (co(b) == -8) { // \nnn is octal
	  out->WriteChar(out,'\\');
	  WriteUInt(out,val,8,3,'0');
	} else if (co(b) == -16) { // \xnn is hexadecimal
	  out->WriteChar(out,'\\');
	  out->WriteChar(out,'x');
	  WriteUInt(out,val,16,2,'0');
	} else if (co(b) == -1616) { // \unnnn is hexadecimal unicode
	  out->WriteChar(out,'\\');
	  out->WriteChar(out,'u');
	  WriteUInt(out,val,16,4,'0');
	}
      } else {
	for (co(j)=0;co(j)<co(width);co(j)++) {
	  val = val + (ReadInt8LE(in) << (8*co(j)));
	}
	if (co(b) == 16) {
	  WriteASCIIZ(out,"0x");
	  WriteUInt(out,val,co(b),co(width)*2,'0');
	} else if (co(b) == 8) {
	  out->WriteChar(out,'0');
	  WriteUInt(out,val,co(b),0,0);
	} else {
	  if (co(isSigned)) {
	    WriteInt(out,val,co(b),0,0);
	  } else {
	    WriteUInt(out,val,co(b),0,0);
	  }
	}
      }
      if ((*mode)->EndValue) (*mode)->EndValue(out,state,class,func);
      if (co(b) > 0 && co(i)+1<co(length) && (*mode)->Separator) {
	(*mode)->Separator(out,state,class,func); 
      }
    }
    if (co(isArray) && (*mode)->EndArray) {
      (*mode)->EndArray(out,state,class,func,co(b));
    }
    if (!co(isArray) && (*mode)->EndNonArray) {
      (*mode)->EndNonArray(out,state,class,func,co(b));
    }
  } else if ((byte & 0xB0) == 0x20) { // real
    co(width) = (byte & 0xF) + 1;
    if (co(b) < 0 && co(width) > 1) {
      co(b) = (*mode)->base;
    }
    WAITBYTES(co(width)*co(length));
    if (co(isArray) && (*mode)->StartArray) {
      (*mode)->StartArray(out,state,class,func,co(b));
    }
    if (!co(isArray) && (*mode)->StartNonArray) {
      (*mode)->StartNonArray(out,state,class,func,co(b));
    }

    for (co(i)=0;co(i)<co(length);co(i)++) {
      if ((*mode)->StartValue) {
	(*mode)->StartValue(out,state,class,func);
      }
      if (co(b) == 0) { // binary
	StreamCopy(out,in,co(width));
      } else if (co(b) < 0) { // escaped
	StreamCopy(out,in,co(width)); // we can't escape a real
      } else {
	if (co(width) == 4) {
	  real32 num = ReadReal32LE(in);
	  WriteReal64A(out,num,0,0);
	} else if (co(width) == 8) {
	  //real64 num = ReadReal64LE(in);
	}
      }
      if ((*mode)->EndValue) (*mode)->EndValue(out,state,class,func);
      if (co(b) > 0 && co(i)+1<co(length) && (*mode)->Separator) {
	(*mode)->Separator(out,state,class,func); 
      }
    }

    if (co(isArray) && (*mode)->EndArray) {
      (*mode)->EndArray(out,state,class,func,co(b));
    }
    if (!co(isArray) && (*mode)->EndNonArray) {
      (*mode)->EndNonArray(out,state,class,func,co(b));
    }

  } else if ((byte & 0xB0) == 0x30) { // struct
    co(width) = (byte & 0xF) + 2; // fields
    co(sub) = 0;
    //if (co(isArray) && (*mode)->StartArray) {
    //(*mode)->StartArray(out,state,class,func,co(b));
    //}
    for (co(i)=0;co(i)<co(length);co(i)++) {
      if ((*mode)->StartStruct) {
	(*mode)->StartStruct(out,state,class,func,co(isArray)?co(i):-1);
      }
      for (co(j)=0;co(j)<co(width);co(j)++) {
	while (!coWriteTagged(&co(sub),state,out,in,mode,class,func)) coYield(0);
      }
      if ((*mode)->EndStruct) (*mode)->EndStruct(out,state,class,func,
						 co(isArray)?co(i):-1);
    }
    //if (co(isArray) && (*mode)->EndArray) {
    //(*mode)->EndArray(out,state,class,func,co(b));
    //}
  } else { // unreachable
    fprintf(stderr,"unreachable code reached\n"); exit(1);
  }
  coReturn(1);
}
// should be able to turn off tagging in the server, when off we should
// terminate the connection on an exception.
// non-tagged mode is probably what we want for our Net classes, while
// tagged mode is for tsctl command line output.
