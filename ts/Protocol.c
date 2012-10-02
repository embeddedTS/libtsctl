#if 0
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include "Net.h"
#include "Bus.h"
#include "System.h"

typedef unsigned char IntU8;
typedef char Int8;
typedef unsigned short IntU16;
typedef short Int16;
typedef unsigned IntU32;
typedef int Int32;
typedef char *Bytes;

typedef struct Protocol Protocol;
typedef struct SystemObjects SystemObjects;
struct Protocol {
  int (*Fini)();
  IntU8 (*_IntU8)();
  IntU16 (*_IntU16)();
  unsigned (*_IntU32)();
  Int8 (*_Int8)();
  Int16 (*_Int16)();
  int (*_Int32)();
  IntU8 *(*IntU8)(IntU8);
  IntU16 *(*IntU16)(IntU16);
  IntU32 *(*IntU32)(IntU32);
  Int8 *(*Int8)(Int8);
  Int16 *(*Int16)(Int16);
  Int32 *(*Int32)(Int32);
  void (*AssignIntU8)(IntU8 *,IntU8);
  void (*AssignIntU16)(IntU16 *,IntU16);
  void (*AssignIntU32)(unsigned *,unsigned);
  void (*AssignInt8)(Int8 *,Int8);
  void (*AssignInt16)(Int16 *,Int16);
  void (*AssignInt32)(int *,int);
  Bytes (*_Bytes)(int); // get bytes from request
  Bytes (*Bytes)(int);
  // the following functions allocate the specified number of bytes in
  // the reply buffer and return a pointer.  the second parameter points
  // to the parameter containing the actual length.  When it is set via
  // the appropriate assign, buffer will be resize to the actual length.
  Bytes (*Bytes8)(int,IntU8 *);
  Bytes (*Bytes16)(int,IntU16 *);
  Bytes (*Bytes32)(int,IntU32 *);
  // alloc allocates bytes as follows: the first parameter is a pointer
  // to a marshalled value, and the second is a constant. actual space is 
  // the two multiplied together.  if the first value is re-assigned,
  // the space is re-allocated.  The Alloc# number indicates the size
  // of the variable holding the length.
  Bytes (*Alloc8)(IntU8 *,int);
  Bytes (*Alloc16)(IntU16 *,int);
  Bytes (*Alloc32)(IntU32 *,int);

  //Bytes (*Bytes_)(int); // copy temporary space to reply
  //Bytes (*_Bytes_)(int); // allocate temporary space for bytes
};


typedef struct Object Object;
typedef int (*Function)(int,...);

struct Object {
  Function *F;
};

struct SystemObjects {
  Object **ob;
  IntU8 nInst[NetSPIClass+1], nCmd[NetSPIClass+1];
};

int ProtocolTsctl(Protocol *p,SystemObjects *so) {
  IntU8 command, instance;
  IntU16 class;
  Object *ob;
  Function F;

  command=p->_IntU8();
  instance=p->_IntU8();
  class=p->_IntU16();
  if (class >= Net_ClassCount || instance > so->nInst[class]
      || command > so->nCmd[class]) return -1;
  ob=so->ob[instance];
  F=ob->F[command];
  switch (class) {
  case NetSystemClass:
    switch (command) {
    case NetSystem_ClassCount:    p->Int32(F(1,ob)); break;
    case NetSystem_InstanceCount: p->Int32(F(2,ob,p->_IntU32())); break;
    case NetSystem_APICount:      p->Int32(F(2,ob,p->_IntU32())); break;
    case NetSystem_LockCount:     p->Int32(F(1,ob)); break;
    case NetSystem_LockHolderInfo: {
      IntU32 *pcount = p->Int32(ob->F[NetSystem_LockCount](1,ob));
      Bytes buf = p->Alloc32(pcount,8);
      p->AssignInt32(pcount,F(2,ob,buf));
      break;
    }
    case NetSystem_ConnWaitInfo: {
      IntU32 *pcount = p->Int32(1024);
      Bytes buf = p->Alloc32(pcount,8);
      p->AssignInt32(pcount,F(2,ob,buf));
      break;
    }
    case NetSystem_CANBusGet:     p->Int8(F(2,ob,p->_IntU32())); break;
    case NetSystem_BuildInfo:
      // tricky.  BuildInfo() returns a fixed size structure, but our
      // protocol is supposed to turn the null terminated strings into
      // length delimited strings.
      // To do this we probably have to take this approach:
      // Bytes *buf = p->Int32(0); // buildNumber
      // p->Int32(0); // buildTime;
      // p->Int32(0); // uptime
      // Bytes *hn = p->Bytes(256); // hostname
      // Bytes *arch = p->Bytes(256); // arch
      // problem is, this doesn't document things. we need to somehow
      // enter a recursive definition i think
      break;
    case NetSystem_ModelId:       p->Int32(F(1,ob)); break;
    case NetSystem_BaseBoardId:   p->Int32(F(1,ob)); break;
    case NetSystem_MapLength:     p->Int32(F(1,ob)); break;
    case NetSystem_MapGet: {
      IntU32 n=p->_Int32();
      Bytes value=p->Bytes(4);
      IntU8 *len = p->IntU8(0);
      p->AssignIntU8(len,F(4,ob,n,p->Bytes8(256,len),value));
      // note: this does NOT match the documentation!!!
    }
    }
  case NetBusClass:
    switch (command) {
    case NetBus_Peek16: {
      unsigned adrs=p->_IntU32();
      p->Int16(F(2,ob,adrs));
      break;
    }
    case NetBus_PeekStream: {
      unsigned adrs=p->_IntU32();
      unsigned dir=p->_Int32();
      unsigned len=p->_Int32();
      Int8 *buf=p->Bytes(len);
      F(5,ob,adrs,dir,buf,len);
    }
    }
  }
  return p->Fini();
}
/*
  To be generic, our protocol definition is limited in what functions it
  can call and what operations it can perform.  Specifically, it must
  limit itself to calling Protocol object functions to specify the
  format of the data stream, and SystemObjects functions to specify
  how these relate to functions that get called.

  In general, we must provide a 1:1 mapping between a specific packet
  and a specific function call.  The data passed to and from the
  packet is irrelevant and we must not deal with it in any way.
  
  Therefore, our logic must consist solely in mapping the regions of
  data in the data stream to data passed to and from the function itself.
  There are several ways this can be done.

  1. We can extract a piece of data from the request and pass it to the 
     function directly. 
     Likewise we can take the return value of the function and put it
     directly into the reply data stream.
  2. We can take a range of data from the request and pass it to the
     function using a pointer.  We may have another value that specifies
     the length of the data, or it may be inferred from the contents
     of the stream.  (for instance, null terminated) if implicit, we
     must have some way of determine the explicit length.
     Likewise, we can have the function return a range of data that
     gets put into the reply.  The length can either be explicit or
     implicit, but if it is implicit, then we need some way of determining
     that length explicitly.
     The function might also return data but require us to allocate the
     buffer.

   1. variable <- input stream
      output stream <- variable
   2. pointer <- input stream
      output stream <- pointer
      pointer <- temporary space

   Function(IntU8 value,Object,Int32 adrs)
   Request(Int32 adrs)
   Reply(IntU16 value)

   All our functions must take a series of parameters, and return a
   value, each of which is either a value or a pointer.  To make
   things a bit more complicated, in a few cases, the pointer is
   to a struct which itself must be de-composed down into a data stream.

   C does not define the order in which arguments to a function are
   evaluated; therefore, we must explicitly specify the order before
   calling the function.

   Our protocol specification must be reasonably efficient to be
   directly executed as C code.
  
   We have had to create generic functions taking a variable number
   of parameters, but this doesn't seem to lend itself well to
   documenting functions, or to type checking calls to those
   functions!

   We aren't supposed to touch our parameters, so how do we deal with
   calculating lengths?

   Can we use the same protocol code to generate the request? I'm
   thinking we should be able to.  We just set the protocol object
   to parse our input, and the SystemObjects to send data for our
   request (instead of receive) and receive data for our reply
   (instead of send).
 */

#ifdef PROTOCOL_TEST
void TsctlDocument() {
  int i,j;
  Object ob;
  SystemObjects so;
  Protocol p;
  int state = 0,rstate=0;
  int command,instance,class;

  int TSDFini() {
    printf("done\n");
    return 1;
  }
  IntU8 TSD_IntU8() {
    printf("%d <- _IntU8\n",state);
    switch (state) {
    case 0: state++; return command;
    case 1: state++; return instance;
    }
    return state++;
  }
  IntU16 TSD_IntU16() {
    printf("%d <- _IntU16\n",state);
    switch (state) {
    case 2: state++; return class;
    }
    return state++;
  }
  unsigned TSD_IntU32() {
    printf("%d <- _Int32\n",state);
    return state++;
  }
  Int8 TSD_Int8() {
    printf("%d <- _Int8\n",state);
    return state++;
  }
  Int16 TSD_Int16() {
    printf("%d <- _Int16\n",state);
    return state++;
  }
  int TSD_Int32() {
    printf("%d <- _Int32\n",state);
    return state++;
  }
  IntU8 *TSDIntU8(IntU8 u8) {
    printf("IntU8 %x\n",u8);
  }
  IntU16 *TSDIntU16(IntU16 u16) {
    printf("IntU16 %x\n",u16);
  }
  IntU32 *TSDIntU32(IntU32 u32) {
    printf("IntU32 %x\n",u32);
  }
  Int8 *TSDInt8(Int8 i8) {
    printf("Int8 %x\n",i8);
  }
  Int16 *TSDInt16(Int16 i16) {
    printf("Int16 %x\n",i16);
  }
  Int32 *TSDInt32(Int32 i32) {
    printf("Int32 %x\n",i32);
  }
  void TSDAssignIntU8(IntU8 *pu8,IntU8 u8) {
    printf("AssignIntU8\n");
  }
  void TSDAssignIntU16(IntU16 *pu16,IntU16 u16) {
    printf("AssignIntU16\n");
  }
  void TSDAssignIntU32(unsigned *pu32,unsigned u32) {
    printf("AssignIntU32\n");
  }
  void TSDAssignInt8(Int8 *pi8,Int8 i8) {
    printf("AssignInt8\n");
  }
  void TSDAssignInt16(Int16 *pi16,Int16 i16) {
    printf("AssignInt16\n");
  }
  void TSDAssignInt32(int *pi32,int i32) {
    printf("AssignInt32\n");
  }
  Bytes TSD_Bytes(int n) {
    printf("_Bytes\n");
    return (Bytes)state++;
  }
  Bytes TSDBytes(int n) {
    printf("%d <- Bytes(%d)\n",rstate,n);
    return (Bytes)rstate++;
  }
  Bytes TSDBytes8(int n,IntU8 *pu8) {
    printf("%d <- Bytes8(%d)\n",rstate,n);
    return (Bytes)rstate++;    
  }
  Bytes TSDBytes16(int n,IntU16 *pu16) {
    printf("%d <- Bytes16\n");
    return (Bytes)rstate++;
  }
  Bytes TSDBytes32(int n,IntU32 *pu32) {
    printf("%d <- Bytes32\n");
    return (Bytes)rstate++;
  }
  Bytes TSDAlloc8(IntU8 *pu8,int n) {
    printf("%d <- IntU8\n");
    return (Bytes)rstate++;
  }
  Bytes TSDAlloc16(IntU16 *pu16,int n) {
    printf("%d <- IntU16\n");
    return (Bytes)rstate++;
  }
  Bytes TSDAlloc32(IntU32 *pu32,int n) {
    printf("%d <- IntU32\n");
    return (Bytes)rstate++;
  }

  p.Fini = TSDFini;
  p._IntU8 = TSD_IntU8;
  p._IntU16 = TSD_IntU16;
  p._IntU32 = TSD_IntU32;
  p._Int8 = TSD_Int8;
  p._Int16 = TSD_Int16;
  p._Int32 = TSD_Int32;
  p.IntU8 = TSDIntU8;
  p.IntU16 = TSDIntU16;
  p.IntU32 = TSDIntU32;
  p.Int8 = TSDInt8;
  p.Int16 = TSDInt16;
  p.Int32 = TSDInt32;
  p.AssignIntU8 = TSDAssignIntU8;
  p.AssignIntU16 = TSDAssignIntU16;
  p.AssignIntU32 = TSDAssignIntU32;
  p.AssignInt8 = TSDAssignInt8;
  p.AssignInt16 = TSDAssignInt16;
  p.AssignInt32 = TSDAssignInt32;
  p._Bytes = TSD_Bytes;
  p.Bytes = TSDBytes;
  p.Bytes8 = TSDBytes8;
  p.Bytes16 = TSDBytes16;
  p.Bytes32 = TSDBytes32;
  p.Alloc8 = TSDAlloc8;
  p.Alloc16 = TSDAlloc16;
  p.Alloc32 = TSDAlloc32;

  int G(int n,...) {
    int i,x;
    va_list ap;

    printf("args:");
    va_start(ap, n);
    for (i=0;i<n;i++) {
      x = va_arg(ap,int);
      printf("%08x ",x);
    }
    va_end(ap);
    printf("\n");
    return 1;
  }

  ob.F = malloc(sizeof(Function) * 16);
  ob.F[NetSystem_ClassCount] = G;
  ob.F[NetSystem_InstanceCount] = G;
  ob.F[NetSystem_APICount] = G;
  ob.F[NetSystem_LockCount] = G;
  ob.F[NetSystem_LockHolderInfo] = G;
  ob.F[NetSystem_ConnWaitInfo] = G;
  ob.F[NetSystem_CANBusGet] = G;
  ob.F[NetSystem_BuildInfo] = G;
  ob.F[NetSystem_ModelId] = G;
  ob.F[NetSystem_BaseBoardId] = G;
  ob.F[NetSystem_MapLength] = G;
  ob.F[NetSystem_MapGet] = G;
  so.ob = malloc(sizeof(Object *) * 1);
  so.ob[0] = &ob;
  so.nInst[0] = 1;
  so.nCmd[0] = System_APICount-1;
  class = NetSystemClass;
  instance = 0;
  for (i=NetSystem_ClassCount;i<=NetSystem_MapGet;i++) {
    printf("Command %d\n",i);
    command = i;
    state = 0;
    rstate = 100;
    ProtocolTsctl(&p,&so);
  }
}

int main(int argc,char *argv[]) {
  TsctlDocument();
}

#endif
#endif // 0

typedef struct var var;
typedef struct stream stream;
typedef struct function function;

struct var {
  int dummy;
};

struct stream {
  var *(*int8)(var *);
  var *(*uint8)(var *);
  var *(*int16)(var *);
  var *(*uint16)(var *);
  var *(*int32)(var *);
  var *(*uint32)(var *);
  var *(*arrayof)(var *,stream *elem,var *len0,var *len1);
  // if var is null, it indicates padding or otherwise unused data
  // len0 is the length of the array in the stream
  // len1 is the length of the array when unmarshalled
  // if one of these elements is 0, it means that we have a null terminated
  // array.
  // if len1 is constant, then it means we should temp allocate that fixed
  // number of elements and copy the array into it.  if len0 is constant, 
  // then it means a fixed number of elements.
};

struct function {
  void (*arg)(var *);
  void (*argptr)(var *);
  void (*ret)(var *);
};

stream *var_struct(void);
var *constant_int32(var *,int);
// var_closure1 creates a variable that binds a function taking an int
// and returning an int to the in1 var as the input, and calls the function
// when needed to calculate the actual value.  this will only happen if
// a stream is actually being processed.
var *var_closure1(var *,var *in1);

void ProtocolSystemClassCount(stream *request,stream *reply,function *f) {
  var count;
  reply->int32(&count);
  f->ret(&count);
}

void ProtocolSystemInstanceCount(stream *request,stream *reply,function *f) {
  var class,count;
  request->int32(&class);
  reply->int32(&count);
  f->arg(&class);
  f->ret(&count);
}

// ProtocolSystemAPICount is same as ProtocolSystemInstanceCount
// ProtocolSystemLockCount is same as ProtocolSystemClassCount

void ProtocolSystemLockHolderInfo(stream *request,stream *reply,function *f) {
  var lockcount,lhiarr;
  stream *lhi;

  // note: the value of lockcount can only be determined by calling
  // System:LockCount!
  lhi = var_struct();
  lhi->int32(0);
  lhi->int32(0);

  reply->int32(&lockcount);
  reply->arrayof(&lhiarr,lhi,&lockcount,&lockcount); // WRONG

  f->arg(&lhiarr);
  f->ret(&lockcount);
}

void ProtocolSystemConnWaitInfo(stream *request,stream *reply,function *f) {
  var max,cwiarr,count;
  stream *cwi;

  request->int32(&max);

  cwi = var_struct();
  cwi->int32(0);
  cwi->int32(0);

  reply->int32(&count);
  reply->arrayof(&cwiarr,cwi,&max,&count);

  f->arg(&max);
  f->arg(&cwiarr);
  f->ret(&count);
}

// ProtocolSystemCANBusGet is same as ProtocolSystemInstanceCount (*)

stream *UINT8;
// UINT8 = var_struct();
// UINT8->uint8(0);

void ProtocolSystemBuildInfo(stream *request,stream *reply,function *f) {
  var hostlen,archlen,cl1,cl2,c256;
  stream *bi,*UINT8;

  int padding(int len) { return 256-len; }
#if 0
  // this isn't quite accurate - is it???
  // we need to map between a fixed structure that we are passing,
  // and a slightly different structure in our packet.
  // 
  bi = var_struct();
  bi->uint32(0); // build number
  bi->int32(0); // build time
  bi->uint32(0); // uptime
  bi->uint8(&hostlen); // host length
  bi->arrayof(0,UINT8,&hostlen,constant_integer(&c256,256)); // host name
  bi->arrayof(0,UINT8,var_closure1(&cl1,hostlen));
  bi->uint8(&archlen); // arch length
  bi->asciiz(archlen); // arch name
  bi->arrayof(0,UINT8,var_closure1(&cl2,archlen));

  reply->struc(bi);
  f->arg(&bi);
#endif
}

// ProtocolSystemModelId same as ProtocolSystemClassCount (*)
// ProtocolSystemBaseBoardId same as ProtocolSystemClassCount (*)
// ProtocolSystemMapLength same as ProtocolSystemClassCount (*)

void ProtocolSystemMapGet(stream *request,stream *reply,function *f) {
  var n,namelen,name,value,c256;

  request->int32(&n);
  reply->uint8(&namelen);
  reply->arrayof(&name,UINT8,&namelen,constant_int32(&c256,256));
  reply->int32(&value);

  f->arg(&n);
  f->arg(&name);
  f->argptr(&value);
  f->ret(&namelen);
}

//=>
int ServerSystemMapGet(stream *request,stream *reply) {
  int32 n;
  uint8 *name;
  int32 value;
  uint8 namelen;

  // CHECK returns failure if connection ends
  CHECK(request->int32(&n));
  name = alloc(256);
  namelen2 = f(n,name,&value);
  reply->uint8(&namelen);
  reply->array(namelen,name);
  reply->int32(&value);
  reply->send();
  return 1;
}
//=>
int ClientSystemMapGet(int32 n,uint8 *name,int32 *value) {
  uint8 namelen;

  request->int32(&n);
  request->send();
  // here, reply must recv whatever bytes we tell it
  CHECK(reply->uint8(&namelen));
  // API says name arg must be allocated by caller
  CHECK(reply->array(namelen,name));
  CHECK(reply->int32(value));
  return namelen;
}

// combined=>
#ifdef SERVER
int ServerSystemMapGet(stream *request,stream *reply) {
  int32 n;
  uint8 *name;
  int32 value;
  uint8 namelen;
#else
int ClientSystemMapGet(int32 n,uint8 *name,int32 *value) {
  uint8 namelen;
#endif
  CHECK(request->int32(&n));
#ifdef SERVER
  name = alloc(256);
  namelen2 = f(n,name,&value);
#else
  request->send();
#endif
  CHECK(reply->uint8(&namelen));
  CHECK(reply->array(namelen,name));
  CHECK(reply->int32(value));
#ifdef SERVER
  return reply->send();
#else
  return namelen;
#endif
}

/*
  If our reply contains a fixed set of fields, with only the length of
  a given field possible to change, then we could just have a struct
  containing pointers to each field.
  Then we would have a function to pack and unpack the structure.

  If we consider our entire protocol this is not true, individual requests
  once we reach the target function probably are.
  
  Even better would be if we could come up with a standard method of
  converting between C parameters/return values and network format.
  This would definitely require some changes to the API.  For the tsctl
  protocol this would definitely be acceptable, since it is still in beta.
  In addition, it would eliminate the need to do all of the protocol stuff
  anyway, as the C prototypes would define the wire format.

  1. primitive types
     These directly translate to their corresponding network form, so
     all that is required is endian translation.
  2. arrays are length delimited.  all arrays must be types ending in "Array"
     and such types must always consist of a 32-bit int containing the length
     as the first element, and a pointer to the array of that length as the
     second and final element.     
  3. all results (reply) allocated by the function are returned directly
  4. all results placed in buffers allocated by the caller are in pointers
     passed to the function



is it possible to always put all the reply in the return value?
struct nv (*MapGet)(void *,int n);
struct lhi (*LockHolderInfo)(void *);

// passes a pointer to hold the length of the array
// returns the array, allocated by the function
ConnectionWaitInfo *(*ConnWaitInfo)(void *,int *len);
// BuildInfo needs overhauling as:
// 1. we no longer have a build number
void (*BuildInfo)(void *,uint32 *buildTime,uint32 uptime,char *hostname,char *archname);
// for BuildInfo, we need a way to return two strings that we allocate
// seems like this is problematic, as we need a way to identify that an
// int * and char * go together, or else create a special construct to recongize
// this.

C strings are problematic.

DIO Wait uses arrays of integers.

CAN uses the CANMessage parameter, which is a struct containing fixed fields.
Rx takes a caller supplied buffer.

SPI ReadWrite uses a single number to indicate the length of two buffers,
since they must be the same size.  The caller provides these buffers.

For fixed size buffers (any time we know the size in advance) it makes sense 
for the caller to provide them. In this case it also may make sense to 
pass the length separately.

The Gets function uses a void * buffer because the size depends on the
sample mode.
 */
void ProtocolSystemMapLookup(stream *request,stream *reply,function *f) {
  var namelen,name,value;

  request->uint8(&namelen);
  request->arrayof(&name,UINT8,&namelen,0);
  reply->int32(&value);

  f->arg(&namelen);
  f->ret(&value);
}

void ProtocolSystemMapLookupPartial(stream *request,stream *reply,function *f) {
  var namelen,name,value,namelen2,name2,c256;

  request->int32(&value);
  request->uint8(&namelen);
  request->arrayof(&name,UINT8,&namelen,constant_int32(&c256,256));

  reply->uint8(&namelen2);
  reply->arrayof(&name2,UINT8,&namelen2,&namelen2);

  f->arg(&namelen);
  f->arg(&value);
  f->arg(&name2);
  f->ret(&namelen2);
}

void ProtocolSystemMapAdd(stream *request,stream *reply,function *f) {
  var value,namelen,name,result;

  request->int32(&value);
  request->uint8(&namelen);
  request->arrayof(&name,UINT8,&namelen,0);
  reply->int32(&result);

  f->arg(&name);
  f->arg(&value);
  f->ret(&result);
}

void ProtocolSystemMapDelete(stream *request,stream *reply,function *f) {
  var namelen,name,result;

  request->uint8(&namelen);
  request->arrayof(&name,UINT8,&namelen,0);
  reply->int32(&result);

  f->arg(&name);
  f->ret(&result);
}

/*
  Things to figure out:
  1. How do we call another function to get a value we need?
     needed by: ProtocolSystemLockHolderInfo

  Clean up:
  to solve problem 2 we probably need to specify a callback function
  to calculate the value from a specified number of input variables.

 */

