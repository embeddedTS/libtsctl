#include "Stream.h"
#include "LookupRef.h"
#include "ts/co.h"

int tsctlArgParseInt8(Stream *out,LookupRef* *lu,char *arg);
int tsctlArgParseInt16(Stream *out,LookupRef* *lu,char *arg);
int tsctlArgParseInt32(Stream *out,LookupRef* *lu,char *arg);
int tsctlArgParseArrayInt8(Stream *out,LookupRef* *lu,char *arg) ;
int tsctlArgParseArrayInt16(Stream *out,LookupRef* *lu,char *arg) ;
int tsctlArgParseArrayUInt8(Stream *out,LookupRef* *lu,char *arg) ;
int tsctlArgParseArrayInt32(Stream *out,LookupRef* *lu,char *arg) ;
int tsctlArgParseUInt8(Stream *out,LookupRef* *lu,char *arg) ;
int tsctlArgParseUInt16(Stream *out,LookupRef* *lu,char *arg) ;
int tsctlArgParseUInt32(Stream *out,LookupRef* *lu,char *arg) ;
int tsctlArgParseReal32(Stream *out,LookupRef* *lu,char *arg) ;
int tsctlArgParseArrayReal32(Stream *out,LookupRef* *lu,char *arg) ;

int WriteArrayInt8As(coParm,Stream *out,Stream *in,int base,int abase);
int WriteArrayInt16As(coParm,Stream *out,Stream *in,int base,int abase);
int WriteArrayUInt8As(coParm,Stream *out,Stream *in,int base,int abase);
int WriteArrayInt32As(coParm,Stream *out,Stream *in,int base,int abase);
int WriteArrayUInt32As(coParm,Stream *out,Stream *in,int base,int abase);
int WriteInt8As(coParm,Stream *out,Stream *in,int base,int abase);
int WriteInt16As(coParm,Stream *out,Stream *in,int base,int abase);
int WriteInt32As(coParm,Stream *out,Stream *in,int base,int abase);
int WriteUInt8As(coParm,Stream *out,Stream *in,int base,int abase);
int WriteUInt16As(coParm,Stream *out,Stream *in,int base,int abase);
int WriteUInt32As(coParm,Stream *out,Stream *in,int base,int abase);
int WriteVoidAs(coParm,Stream *out,Stream *in,int base,int abase);
int WriteArrayReal32As(coParm,Stream *out,Stream *in,int base,int abase);

int WriteArrayInt8Bin(coParm,Stream *out,Stream *in,int base,int abase);
int WriteArrayInt16Bin(coParm,Stream *out,Stream *in,int base,int abase);
int WriteArrayUInt8Bin(coParm,Stream *out,Stream *in,int base,int abase);
int WriteArrayInt32Bin(coParm,Stream *out,Stream *in,int base,int abase);
int WriteArrayUInt32Bin(coParm,Stream *out,Stream *in,int base,int abase);
int WriteInt8Bin(coParm,Stream *out,Stream *in,int base,int abase);
int WriteInt16Bin(coParm,Stream *out,Stream *in,int base,int abase);
int WriteInt32Bin(coParm,Stream *out,Stream *in,int base,int abase);
int WriteUInt8Bin(coParm,Stream *out,Stream *in,int base,int abase);
int WriteUInt16Bin(coParm,Stream *out,Stream *in,int base,int abase);
int WriteUInt32Bin(coParm,Stream *out,Stream *in,int base,int abase);
int WriteVoidBin(coParm,Stream *out,Stream *in,int base,int abase);
int WriteArrayReal32Bin(coParm,Stream *out,Stream *in,int base,int abase);

int WriteArrayInt8Esc(coParm,Stream *out,Stream *in,int base,int abase);
int WriteArrayInt16Esc(coParm,Stream *out,Stream *in,int base,int abase);
int WriteArrayUInt8Esc(coParm,Stream *out,Stream *in,int base,int abase);
int WriteArrayInt32Esc(coParm,Stream *out,Stream *in,int base,int abase);
int WriteArrayUInt32Esc(coParm,Stream *out,Stream *in,int base,int abase);
int WriteInt8Esc(coParm,Stream *out,Stream *in,int base,int abase);
int WriteInt16Esc(coParm,Stream *out,Stream *in,int base,int abase);
int WriteInt32Esc(coParm,Stream *out,Stream *in,int base,int abase);
int WriteUInt8Esc(coParm,Stream *out,Stream *in,int base,int abase);
int WriteUInt16Esc(coParm,Stream *out,Stream *in,int base,int abase);
int WriteUInt32Esc(coParm,Stream *out,Stream *in,int base,int abase);
int WriteVoidEsc(coParm,Stream *out,Stream *in,int base,int abase);
int WriteArrayReal32Esc(coParm,Stream *out,Stream *in,int base,int abase);

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
  void (*EndValue)(Stream *,void **,int,int,int);
  void (*Separator)(Stream *,void **,int,int);
  void (*StartEnum)(Stream *,void **,int,int);
  void (*EndEnum)(Stream *,void **,int,int);
} mode;
extern mode ModeAssign, ModeJSON, ModeNL, ModeRaw;
