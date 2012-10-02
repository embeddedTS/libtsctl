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

typedef long long int64;
typedef unsigned long long uint64;

void hprintf(int h,char *format, ...) {
  va_list ap;
  char dummy[1];
  int len;

  va_start(ap,format);
  len = vsnprintf(dummy,0,format,ap);
  {
    char str[len];
    vsprintf(str,format,ap);
    write(h,str,len);
  }
}

typedef struct prototype {
  int opcode; // unused
  int *reqtypes, *replytypes;
  // request/reply types:
  // 8, 16, or 32-bit signed or unsigned int
  // or array thereof
  // -8 = 8-bit signed int
  // 8 = 8-bit unsigned int
  // 1008 = array of 8-bit unsigned int
  // -1008 = array of 8-bit signed int
  // etc.
  void (*f)(OutInfo *,int,char *[]);
} prototype;

unsigned htCount(HashTable *ht,char *str) {
  unsigned ret = (unsigned)HashTableLookup(ht,str);
  HashTableInsert(ht,str,(void *)(ret+1));
  return ret;
}

void Output_Flush(HashTable *ht,int tsctl_o) {
  if (!ht) return;
  IteratorHashTable *it = IteratorHashTableNew(ht);
  while (it) {
    char *name = IteratorHashTableKey(it);
    if (!name) break;
    unsigned count = (unsigned)IteratorHashTableValue(it);
    hprintf(tsctl_o,"Count_%s=%u\n",name,count);
    if (IteratorHashTableNext(it) == 0) break;
  }
}

void NVPRINT(OutInfo *oi,char *fmt,char *name,int val) {
  char tmp[80];

  if (oi->fAssign) {
    if (oi->ht) {
      if (oi->fAssign == 2) {
	sprintf(tmp,"\"%%s_%%d\":%s,\n",fmt);
      } else {
	sprintf(tmp,"%%s_%%d=%s\n",fmt);
      }
      hprintf(oi->tsctl_o,tmp,name,htCount(oi->ht,name),val);
    } else {
      if (oi->fAssign == 2) {
	sprintf(tmp,"\"%%s\":%s,\n",fmt);
      } else {
	sprintf(tmp,"%%s=%s\n",fmt);
      }
      hprintf(oi->tsctl_o,tmp,name,val);
    }
  } else {
    sprintf(tmp,"%s\n",fmt);
    hprintf(oi->tsctl_o,tmp,val);
  }
}

void NVPRINT64(OutInfo *oi,char *fmt,char *name,long long val) {
  char tmp[80];

  if (oi->fAssign) {
    if (oi->ht) {
      if (oi->fAssign == 2) {
	sprintf(tmp,"\"%%s_%%d\":%s,\n",fmt);
      } else {
	sprintf(tmp,"%%s_%%d=%s\n",fmt);
      }
      hprintf(oi->tsctl_o,tmp,name,htCount(oi->ht,name),val);
    } else {
      if (oi->fAssign == 2) {
	sprintf(tmp,"\"%%s\":%s,\n",fmt);
      } else {
	sprintf(tmp,"%%s=%s\n",fmt);
      }
      hprintf(oi->tsctl_o,tmp,name,val);
    }
  } else {
    sprintf(tmp,"%s\n",fmt);
    hprintf(oi->tsctl_o,tmp,val);
  }
}

void Output900(OutInfo *oi,char *name,float val) { 
  char tmp[80];
  char *fmt = "%f";

  if (oi->fAssign) {
    if (oi->ht) {
      if (oi->fAssign == 2) {
	sprintf(tmp,"\"%%s_%%d\":%s,\n",fmt);
      } else {
	sprintf(tmp,"%%s_%%d=%s\n",fmt);
      }
      hprintf(oi->tsctl_o,tmp,name,htCount(oi->ht,name),val);
    } else {
      if (oi->fAssign == 2) {
	sprintf(tmp,"\"%%s\":%s,\n",fmt);
      } else {
	sprintf(tmp,"%%s=%s\n",fmt);
      }
      hprintf(oi->tsctl_o,tmp,name,val);
    }
  } else {
    sprintf(tmp,"%s\n",fmt);
    hprintf(oi->tsctl_o,tmp,val);
  }
}

// assignment mode: name=value\n
// literal mode: value\n
// binary mode: <binary>
void Output_8(OutInfo *oi,char *name,char val) { 
  char *mode="";
  switch (oi->oMode) {
  case MODE_HEX: mode="0x%02X"; break;
  case MODE_DEC: mode="%d"; break;
  case MODE_OCT: mode="%o"; break;
  }
  NVPRINT(oi,mode,name,val); 
}
void Output_16(OutInfo *oi,char *name,short val) { 
  char *mode="";
  switch (oi->oMode) {
  case MODE_HEX: mode="0x%04X"; break;
  case MODE_DEC: mode="%d"; break;
  case MODE_OCT: mode="%o"; break;
  }
  NVPRINT(oi,mode,name,val); 
}
void Output_32(OutInfo *oi,char *name,int val) { 
  char *mode="";
  switch (oi->oMode) {
  case MODE_HEX: mode="0x%08X"; break;
  case MODE_DEC: mode="%d"; break;
  case MODE_OCT: mode="%o"; break;
  }
  NVPRINT(oi,mode,name,val); 
}
void Output8(OutInfo *oi,char *name,unsigned char val) { 
  char *mode="";
  switch (oi->oMode) {
  case MODE_HEX: mode="0x%02X"; break;
  case MODE_DEC: mode="%u"; break;
  case MODE_OCT: mode="%o"; break;
  }
  NVPRINT(oi,mode,name,val); 
}
void Output16(OutInfo *oi,char *name,unsigned short val) { 
  char *mode="";
  switch (oi->oMode) {
  case MODE_HEX: mode="0x%04X"; break;
  case MODE_DEC: mode="%u"; break;
  case MODE_OCT: mode="%o"; break;
  }
  NVPRINT(oi,mode,name,val); 
}
void Output32(OutInfo *oi,char *name,unsigned int val) { 
  char *mode="";
  switch (oi->oMode) {
  case MODE_HEX: mode="0x%08X"; break;
  case MODE_DEC: mode="%u"; break;
  case MODE_OCT: mode="%o"; break;
  }
  NVPRINT(oi,mode,name,val); 
}
void Output_64(OutInfo *oi,char *name,int64 val) { 
  char *mode="";
  switch (oi->oMode) {
  case MODE_HEX: mode="0x%16llX"; break;
  case MODE_DEC: mode="%lld"; break;
  case MODE_OCT: mode="%llo"; break;
  }
  NVPRINT64(oi,mode,name,val); 
}
void Output64(OutInfo *oi,char *name,uint64 val) { 
  char *mode="";
  switch (oi->oMode) {
  case MODE_HEX: mode="0x%16llX"; break;
  case MODE_DEC: mode="%llu"; break;
  case MODE_OCT: mode="%llo"; break;
  }
  NVPRINT64(oi,mode,name,val); 
}

void Output_1008(OutInfo *oi,char *name,const char* val) { 
  int i;
  char *mode="";
  switch (oi->oMode) {
  case MODE_HEX: mode="0x%02X"; break;
  case MODE_DEC: mode="%d"; break;
  case MODE_OCT: mode="%o"; break;
  }
  if (oi->aMode != MODE_STR) {
    if (oi->fAssign) {
      if (oi->ht) {
	if (oi->fAssign == 2) {
	  hprintf(oi->tsctl_o,"\"%s_%d\":\"",name,htCount(oi->ht,name));
	} else {
	  hprintf(oi->tsctl_o,"%s_%d=\"",name,htCount(oi->ht,name));
	}
      } else {
	hprintf(oi->tsctl_o,"%s=\"",name);
      }
    }
    for (i=0;i<ArrayLength(val);i++) {
      hprintf(oi->tsctl_o,mode,val[i]);
      if (i+1<ArrayLength(val)) hprintf(oi->tsctl_o,":");
    }
    if (oi->fAssign) hprintf(oi->tsctl_o,oi->fAssign==2?"\",":"\"");
    hprintf(oi->tsctl_o,"\n");
  } else {
    if (oi->fAssign) {
      if (oi->ht) {
	if (oi->fAssign == 2) {
	  hprintf(oi->tsctl_o,"\"%s_%d\":\"%s\",\n",name,htCount(oi->ht,name),
		  val);
	} else {
	  hprintf(oi->tsctl_o,"%s_%d=\"%s\"\n",name,htCount(oi->ht,name),val);
	}
      } else {
	if (oi->fAssign == 2) {
	  hprintf(oi->tsctl_o,"\"%s\":\"%s\",\n",name,val);
	} else {
	  hprintf(oi->tsctl_o,"%s=\"%s\"\n",name,val);
	}
      }
    } else {
      hprintf(oi->tsctl_o,"%s\n",val);
    }
  }
}
void Output1008(OutInfo *oi,char *name,const unsigned char* val) { 
  char *mode="";
  int i;
  switch (oi->oMode) {
  case MODE_HEX: mode="0x%02X"; break;
  case MODE_DEC: mode="%u"; break;
  case MODE_OCT: mode="%o"; break;
  }
  if (oi->aMode != MODE_STR) {
    if (oi->fAssign) {
      if (oi->ht) {
	if (oi->fAssign == 2) {
	  hprintf(oi->tsctl_o,"\"%s_%d\":\"",name,htCount(oi->ht,name));
	} else {
	  hprintf(oi->tsctl_o,"%s_%d=\"",name,htCount(oi->ht,name));
	}
      } else {
	if (oi->fAssign == 2) {
	  hprintf(oi->tsctl_o,"\"%s\":\"",name);
	} else {
	  hprintf(oi->tsctl_o,"%s=\"",name);
	}
      }
    }
    for (i=0;i<ArrayLength(val);i++) {
      hprintf(oi->tsctl_o,mode,val[i]);
      if (i+1<ArrayLength(val)) hprintf(oi->tsctl_o,":");
    }
    if (oi->fAssign) hprintf(oi->tsctl_o,oi->fAssign==2?"\",":"\"");
    hprintf(oi->tsctl_o,"\n");
  } else {
    if (oi->fAssign) {
      if (oi->ht) {
	if (oi->fAssign == 2) {
	  hprintf(oi->tsctl_o,"\"%s_%d\":\"%s\",\n",name,htCount(oi->ht,name),
		  val);
	} else {
	  hprintf(oi->tsctl_o,"%s_%d=\"%s\"\n",name,htCount(oi->ht,name),val);
	}
      } else {
	if (oi->fAssign == 2) {
	  hprintf(oi->tsctl_o,"\"%s\":\"%s\",\n",name,val);
	} else {
	  hprintf(oi->tsctl_o,"%s=\"%s\"\n",name,val);
	}
      }
    } else {
      hprintf(oi->tsctl_o,"%s\n",val);
    }
  }
}
void Output_1016(OutInfo *oi,char *name,const short* val) { 
  int i;
  char *mode="";
  switch (oi->oMode) {
  case MODE_HEX: mode="0x%04X"; break;
  case MODE_DEC: mode="%d"; break;
  case MODE_OCT: mode="%o"; break;
  }
  if (oi->fAssign) {
    if (oi->ht) {
      if (oi->fAssign == 2) {
	hprintf(oi->tsctl_o,"\"%s_%d\":\"",name,htCount(oi->ht,name));
      } else {
	hprintf(oi->tsctl_o,"%s_%d=\"",name,htCount(oi->ht,name));
      }
    } else {
      if (oi->fAssign == 2) {
	hprintf(oi->tsctl_o,"\"%s\":\"",name);
      } else {
	hprintf(oi->tsctl_o,"%s=\"",name);
      }
    }
  }
  for (i=0;i<ArrayLength(val);i++) {
    hprintf(oi->tsctl_o,mode,val[i]);
    if (i+1<ArrayLength(val)) hprintf(oi->tsctl_o,":");
  }
  if (oi->fAssign) hprintf(oi->tsctl_o,oi->fAssign==2?"\",":"\"");
  hprintf(oi->tsctl_o,"\n");
}
void Output1016(OutInfo *oi,char *name,const unsigned short* val) {
  int i;
  char *mode="";
  switch (oi->oMode) {
  case MODE_HEX: mode="0x%04X"; break;
  case MODE_DEC: mode="%u"; break;
  case MODE_OCT: mode="%o"; break;
  }
  if (oi->fAssign) {
    if (oi->ht) {
      if (oi->fAssign == 2) {
	hprintf(oi->tsctl_o,"\"%s_%d\":\"",name,htCount(oi->ht,name));
      } else {
	hprintf(oi->tsctl_o,"%s_%d=\"",name,htCount(oi->ht,name));
      }
    } else {
      if (oi->fAssign == 2) {
	hprintf(oi->tsctl_o,"\"%s\":\"",name);
      } else {
	hprintf(oi->tsctl_o,"%s=\"",name);
      }
    }
  }
  for (i=0;i<ArrayLength(val);i++) {
    hprintf(oi->tsctl_o,mode,val[i]);
    if (i+1<ArrayLength(val)) hprintf(oi->tsctl_o,":");
  }
  if (oi->fAssign) hprintf(oi->tsctl_o,oi->fAssign==2?"\",":"\"");
  hprintf(oi->tsctl_o,"\n");
}
void Output_1032(OutInfo *oi,char *name,const int* val) { 
  int i;
  char *mode="";
  switch (oi->oMode) {
  case MODE_HEX: mode="0x%08X"; break;
  case MODE_DEC: mode="%d"; break;
  case MODE_OCT: mode="%o"; break;
  }
  if (oi->fAssign) {
    if (oi->ht) {
      if (oi->fAssign == 2) {
	hprintf(oi->tsctl_o,"\"%s_%d\":\"",name,htCount(oi->ht,name));
      } else {
	hprintf(oi->tsctl_o,"%s_%d=\"",name,htCount(oi->ht,name));
      }
    } else {
      if (oi->fAssign == 2) {
	hprintf(oi->tsctl_o,"\"%s\":\"",name);
      } else {
	hprintf(oi->tsctl_o,"%s=\"",name);
      }
    }
  }
  for (i=0;i<ArrayLength(val);i++) {
    hprintf(oi->tsctl_o,mode,val[i]);
    if (i+1<ArrayLength(val)) hprintf(oi->tsctl_o,":");
  }
  if (oi->fAssign) hprintf(oi->tsctl_o,oi->fAssign==2?"\",":"\"");
  hprintf(oi->tsctl_o,"\n");
}
void Output1032(OutInfo *oi,char *name,const unsigned* val) { 
  int i;
  char *mode="";
  switch (oi->oMode) {
  case MODE_HEX: mode="0x%08X"; break;
  case MODE_DEC: mode="%u"; break;
  case MODE_OCT: mode="%o"; break;
  }
  if (oi->fAssign) {
    if (oi->ht) {
      if (oi->fAssign == 2) {
	hprintf(oi->tsctl_o,"\"%s_%d\":\"",name,htCount(oi->ht,name));
      } else {
	hprintf(oi->tsctl_o,"%s_%d:\"",name,htCount(oi->ht,name));
      }
    } else {
      if (oi->fAssign == 2) {
	hprintf(oi->tsctl_o,"\"%s\":\"",name);
      } else { 
	hprintf(oi->tsctl_o,"%s=\"",name);
      }
    }
  }
  for (i=0;i<ArrayLength(val);i++) {
    hprintf(oi->tsctl_o,mode,val[i]);
    if (i+1<ArrayLength(val)) hprintf(oi->tsctl_o,":");
  }
  if (oi->fAssign) hprintf(oi->tsctl_o,oi->fAssign==2?"\",":"\"");
  hprintf(oi->tsctl_o,"\n");
}
void Output1900(OutInfo *oi,char *name,const float* val) { 
  int i;
  char *mode="%f";
  if (oi->fAssign) {
    if (oi->ht) {
      if (oi->fAssign == 2) {
      } else {
	hprintf(oi->tsctl_o,"\"%s_%d\":\"",name,htCount(oi->ht,name));
      }
    } else {
      if (oi->fAssign == 2) {
	hprintf(oi->tsctl_o,"\"%s\":\"",name);
      } else { 
	hprintf(oi->tsctl_o,"%s=\"",name);
      }
    }
  }
  for (i=0;i<ArrayLength(val);i++) {
    hprintf(oi->tsctl_o,mode,val[i]);
    if (i+1<ArrayLength(val)) hprintf(oi->tsctl_o,":");
  }
  if (oi->fAssign) hprintf(oi->tsctl_o,oi->fAssign==2?"\",":"\"");
  hprintf(oi->tsctl_o,"\n");
}


int Lookup(char* str);

float Input900(char *str) {
  return strtof(str,0);
}

float* Input1900(char *str) {
  char** n = split(str,':');
  if (ArrayLength(n) > 1) {
    int i;
    float* arr = ArrayAlloc(ArrayLength(n),sizeof(float));
    for (i=0;i<ArrayLength(n);i++) {
      arr[i] = strtof(n[i],0);
    }
    ArrayFree(n);
    return arr;
  } else {
    ArrayFree(n);
    if (ArrayLength(str) == 0) {
      return ArrayAlloc(0,sizeof(float));
    } else {
      float* arr = ArrayAlloc(1,sizeof(float));
      arr[0] = strtof(str,0);
      return arr;
    }
  }
}

int Input_32(char* str) { 
  int val = strtol(str,0,0);
  if (!val && str[0] != '0') return Lookup(str); else return val;
}
unsigned int Input32(char* str) { 
  int val = strtoul(str,0,0); 
  if (!val && str[0] != '0') return Lookup(str); else return val;
}
char Input_8(char* str) { return Input_32(str); }
short Input_16(char* str) { return Input_32(str); }
unsigned char Input8(char* str) { return Input32(str); }
unsigned short Input16(char* str) { return Input32(str); }

// array of numbers separate with colons with no intervening whitespace
// OR
// literal character strings (containing no colons)
char* Input_1008(char* str) {
  char** n = split(str,':');
  if (ArrayLength(n) > 1) {
    int i;
    char* arr = ArrayAlloc(ArrayLength(n),1);
    for (i=0;i<ArrayLength(arr);i++) {
      arr[i] = strtol(n[i],0,0);
    }
    ArrayFree(n);
    return arr;
  } else {
    ArrayFree(n);
    return ArrayDup(str);
  }
}

// array of numbers separate with colons with no intervening whitespace
short* Input_1016(char* str) {
  // TO DO
}
// array of numbers separate with colons with no intervening whitespace
int* Input_1032(char* str) {
  char** n = split(str,':');
  if (ArrayLength(n) > 1) {
    int i;
    int* arr = ArrayAlloc(ArrayLength(n),sizeof(int));
    for (i=0;i<ArrayLength(n);i++) {
      arr[i] = strtol(n[i],0,0);
      if (!arr[i] && n[i][0] != '0') arr[i] = Lookup(n[i]);
    }
    ArrayFree(n);
    return arr;
  } else {
    ArrayFree(n);
    if (ArrayLength(str) == 0) {
      return ArrayAlloc(0,sizeof(int));
    } else {
      int* arr = ArrayAlloc(1,sizeof(int));
      arr[0] = strtol(str,0,0);
      if (!arr[0] && str[0] != '0') arr[0] = Lookup(str);
      return arr;
    }
  }
}
typedef unsigned char uchar;
typedef unsigned short ushort;
typedef unsigned int uint;

#include "ts/defs.h"

ArrayAuto(int,typesNone,ARR());
ArrayAuto(int,typesInt,ARR(32));
ArrayAuto(int,typesString,ARR(-1008));
void ModeCommand0(OutInfo *oi,int inst,char *argv[]) { oi->fAssign = 2; }
void ModeCommand1(OutInfo *oi,int inst,char *argv[]) { oi->fAssign = 1; }
void ModeCommand2(OutInfo *oi,int inst,char *argv[]) { oi->fAssign = 0; }
void ModeCommand3(OutInfo *oi,int inst,char *argv[]) { oi->oMode=MODE_HEX; }
void ModeCommand4(OutInfo *oi,int inst,char *argv[]) { oi->oMode=MODE_DEC; }
void ModeCommand5(OutInfo *oi,int inst,char *argv[]) { oi->oMode=MODE_OCT; }
void ModeCommand6(OutInfo *oi,int inst,char *argv[]) { oi->aMode=MODE_STR; }
void ModeCommand7(OutInfo *oi,int inst,char *argv[]) { oi->aMode=MODE_HEX; }
void ModeCommand8(OutInfo *oi,int inst,char *argv[]) { oi->aMode=MODE_DEC; }
void ModeCommand9(OutInfo *oi,int inst,char *argv[]) { oi->aMode=MODE_OCT; }
prototype protMode0 = { 0,ArrayL(typesNone),ArrayL(typesNone),ModeCommand0 };
prototype protMode1 = { 0,ArrayL(typesNone),ArrayL(typesNone),ModeCommand1 };
prototype protMode2 = { 0,ArrayL(typesNone),ArrayL(typesNone),ModeCommand2 };
prototype protMode3 = { 0,ArrayL(typesNone),ArrayL(typesNone),ModeCommand3 };
prototype protMode4 = { 0,ArrayL(typesNone),ArrayL(typesNone),ModeCommand4 };
prototype protMode5 = { 0,ArrayL(typesNone),ArrayL(typesNone),ModeCommand5 };
prototype protMode6 = { 0,ArrayL(typesNone),ArrayL(typesNone),ModeCommand6 };
prototype protMode7 = { 0,ArrayL(typesNone),ArrayL(typesNone),ModeCommand7 };
prototype protMode8 = { 0,ArrayL(typesNone),ArrayL(typesNone),ModeCommand8 };
prototype protMode9 = { 0,ArrayL(typesNone),ArrayL(typesNone),ModeCommand9 };
void LogCommand1(OutInfo *oi,int inst,char *argv[]) { LogExcludeAll(); }
void LogCommand2(OutInfo *oi,int inst,char *argv[]) { LogIncludeAll(); }
void LogCommand3(OutInfo *oi,int inst,char *argv[]) { 
  int arg0 = Input32(argv[0]);
  LogFlagsSet(arg0);
}
void LogCommand4(OutInfo *oi,int inst,char *argv[]) { 
  int arg0 = Input32(argv[0]);
  LogMaxDepth(arg0);
}
void LogCommand5(OutInfo *oi,int inst,char *argv[]) { 
  int arg0 = Input32(argv[0]);
  LogMinDepth(arg0);
}
void LogCommand6(OutInfo *oi,int inst,char *argv[]) {
  char* arg0 = Input_1008(argv[0]);
  LogFileAdd(arg0);
}
void LogCommand7(OutInfo *oi,int inst,char *argv[]) { 
  char* arg0 = Input_1008(argv[0]);
  LogFunctionAdd(arg0);
}
prototype protLog1 = { 0,ArrayL(typesNone),ArrayL(typesNone),LogCommand1 };
prototype protLog2 = { 0,ArrayL(typesNone),ArrayL(typesNone),LogCommand2 };
prototype protLog3 = { 0,ArrayL(typesInt),ArrayL(typesNone),LogCommand3 };
prototype protLog4 = { 0,ArrayL(typesInt),ArrayL(typesNone),LogCommand4 };
prototype protLog5 = { 0,ArrayL(typesInt),ArrayL(typesNone),LogCommand5 };
prototype protLog6 = { 0,ArrayL(typesString),ArrayL(typesNone),LogCommand6 };
prototype protLog7 = { 0,ArrayL(typesString),ArrayL(typesNone),LogCommand7 };

void PrototypeInit2() {
  static int initialized=0;
  if (initialized) return;
  HashTableInsert(ci,"Mode JSON",(char*)&protMode0);
  HashTableInsert(ci,"Mode Assign",(char*)&protMode1);
  HashTableInsert(ci,"Mode NoAssign",(char*)&protMode2);
  HashTableInsert(ci,"Mode Hex",(char*)&protMode3);
  HashTableInsert(ci,"Mode Dec",(char*)&protMode4);
  HashTableInsert(ci,"Mode Oct",(char*)&protMode5);
  HashTableInsert(ci,"Mode AStr",(char*)&protMode6);
  HashTableInsert(ci,"Mode AHex",(char*)&protMode7);
  HashTableInsert(ci,"Mode ADec",(char*)&protMode8);
  HashTableInsert(ci,"Mode AOct",(char*)&protMode9);

  HashTableInsert(ci,"Log Exclude",(char *)&protLog1);
  HashTableInsert(ci,"Log Include",(char *)&protLog2);
  HashTableInsert(ci,"Log FlagsSet",(char *)&protLog3);
  HashTableInsert(ci,"Log Max",(char *)&protLog4);
  HashTableInsert(ci,"Log Min",(char *)&protLog5);
  HashTableInsert(ci,"Log File",(char *)&protLog6);
  HashTableInsert(ci,"Log Function",(char *)&protLog7);
  initialized = 1;
}

int Lookup(char* str) {
#ifdef THREAD_USE_POSIX
	pthread_mutex_lock(&Systemmutex);
#endif
  if (!SystemArr) {
    SystemArr = ArrayAlloc(1,sizeof(System *));
    SystemArr[0]= SystemInit(0);
  }
#ifdef THREAD_USE_POSIX
	pthread_mutex_unlock(&Systemmutex);
#endif
  char **names = split(str,'+');
  int i,val=0,n;
  for (i=0;i<ArrayLength(names);i++) {
    n = SystemArr[0]->MapLookup(SystemArr[0],names[i]);
    if (n > 0) val |= n;
  }
  ArrayFree(names);
  int ret = SystemArr[0]->MapLookup(SystemArr[0],str);
  if (ret == -1) {
    char* str2 = ArrayDup(str);
    char *s = str2;
    while (*s) {
      *s = toupper(*s);
      s++;
    }
    ret = SystemArr[0]->MapLookup(SystemArr[0],str2);
    if (ret == -1) {
      char* enum1 = strf("enum.%s",str2);
      ret = SystemArr[0]->MapLookup(SystemArr[0],enum1);
      ArrayFree(enum1);
    }
    ArrayFree(str2);
  }
  return ret;
}

#if 0
ArrayAuto(char,nameSystem,ARR("System"));
ArrayAuto(char,nameBus,ARR("Bus"));
ArrayAuto(char *,classNames,
	  ARR(ArrayL(nameSystem),
	      ArrayL(nameBus)
	      ));

int ArrayPtrCompare(const void *a,const void *b) {
  const void **a1 = (const void **)a;
  const void **b1 = (const void **)b;
  return ArrayCompare(a1[0],b1[0]);
}
  //ArraySort(protosSystem,ComparePrototype);
  //ArraySort(protosBus,ComparePrototype);
  //ArraySort(classNames,ArrayPtrCompare);

  unsigned class = ArrayFind(classNames,&argv[0]);
  printf("%s %u--%d\n",argv[0],class,ArrayCompare(classNames[class],argv[0]));
  char **cnameptr = ArrayFindEq(classNames,&argv[0]);
  if (cnameptr) printf("class %d\n",cnameptr - classNames);

  prototype p,*pp=&p;
  p.command = argv[1];
  //unsigned index = ArrayFind(protosSystem,&pp);
  unsigned index = ArrayFind(protosSystem,A(prototype *,&p));
  protosSystem[index]->f(sys,argv+2);

int BusMustLock[] = {
  MustReadLock, MustWriteLock,
  MustReadLock, MustWriteLock,
  MustReadLock, MustWriteLock,
  MustReadLock, MustWriteLock, MustWriteLock, MustWriteLock,
  MustReadLock, MustWriteLock, MustWriteLock, MustWriteLock,
  MustReadLock, MustWriteLock, MustWriteLock, MustWriteLock,
  MustReadLock, MustWriteLock, MustNoLock, MustNoLock,
  MustWriteLock, MustWriteLock, MustWriteLock,
  MustWriteLock, MustWriteLock, MustWriteLock,
  MustReadLock, MustReadLock, MustReadLock
};

int PinMustLock[] = {
  MustReadLock, MustWriteLock
};

int DIORawMustLock[] = {
  MustWriteLock, MustWriteLock,
  MustReadLock, MustReadLock, MustNoLock
};

int DIOMustLock[] = {
  MustNoLock, MustNoLock, MustWriteLock, MustReadLock,
  MustWriteLock, MustReadLock, MustReadLock, MustNoLock, MustNoLock
};

int TWIMustLock[] = {
  MustWriteLock, MustWriteLock
};

int SPIMustLock[] = {
  MustWriteLock, MustWriteLock, MustWriteLock,
  MustWriteLock, MustWriteLock
};

char *SystemCommandDesc[] = {
  "", // ClassCount
  "<class#>", // InstanceCount
  "<class#>", // APICount
  "", //LockCount
  "", //LockHolderInfo
  "<Max>", //ConnWaitInfo
  "<CANInst>", // CANBusGet
  "", // BuildInfo
  "", // ModelId
  "" // BaseBoardId
  "", // MapLength
  "<index>", // MapGet
  "<name>", // MapLookup
  "<name> <value>", // MapLookupPartial
  "<name> <value>", //MapAdd
  "<name>" // MapDelete
};

char *BusCommandDesc[] = {
  "<address>", // Peek8
  "<address> <8-bit value>", // Poke8
  "<address>", // Peek16
  "<address> <16-bit value>", // Poke16
  "<address>", // Peek32
  "<address> <32-bit value>", // Poke32
  "<address> <bit>", // BitGet8
  "<address> <bit> <0|1>", // BitAssign8
  "<address> <bit>", // BitSet8
  "<address> <bit>", // BitClear8
  "<address> <bit>", // BitGet16
  "<address> <bit> <0|1>", // BitAssign16
  "<address> <bit>", // BitSet16
  "<address> <bit>", // BitClear16
  "<address> <bit>", // BitGet32
  "<address> <bit> <0|1>", // BitAssign32
  "<address> <bit>", // BitSet32
  "<address> <bit>", // BitClear32
  "<address> <direction> <length>", // PeekStream
  "<address> <direction> <byte array>", // PokeStream
  "", // Refresh
  "<forceall flag>", // Commit
  "<address> <bit>", // BitToggle8
  "<address> <bit>", // BitToggle16
  "<address> <bit>", // BitToggle32
  "<address> <bit1> <bit0> <value>", // Assign8X
  "<address> <bit1> <bit0> <value>", // Assign16X
  "<address> <bit1> <bit0> <value>", // Assign32X
  "<address> <bit1> <bit0>", // BitsGet8
  "<address> <bit1> <bit0>", // BitsGet16
  "<address> <bit1> <bit0>" // BitsGet32
};
char *TimeCommandDesc[] = {
  "<microseconds>", // Wait
  "<microseconds>", // Delay
  "", // Tick
  "<start>", // usElapsed
  "<start> <us>", // usFuture
  "<start> <end>", // TimeoutQ
  "" // TPS
};
char *PinCommandDesc[] = {
  "<pin number>", // ModeGet
  "<pin number> <mode>", // ModeSet
};
char *DIORawCommandDesc[] = {
  "<num> <asOutput>", // DirSet
  "<num> <asHigh>", // DataSet
  "<num>", // DirGet
  "<num>", // DataGet
  "" // Count
};
char *DIOCommandDesc[] = {
  "", // Refresh
  "<forceall flag>", // Commit
  "<DIO number> <state>", // Set
  "<DIO number>", // Get
  "<DIO number> <state>", // SetAsync
  "<DIO number>", // GetAsync
  "<min> <max> <DIONum:...> <DIONum:...>", // Wait
  "", // Count
  "<DIO number>" // Capabilities
};
char *TWICommandDesc[] = {
  "<devadr> <adrslen> <adrs> <byte array>", // Write
  "<devadr> <adrslen> <adrs> <length>" // Read
};
char *CANCommandDesc[] = {
  "", // Rx
  "<byte array>", // Tx
  "<baudrate>", // BaudSet
  "", // BaudGet
};
char *SPICommandDesc[] = {
  "<adrs> <byte array>", // Write
  "<adrs> <length>", // Read
  "<adrs> <byte array>", // ReadWrite
  "<clock freq>", // ClockSet
  "<edge>" // EdgeSet
};

int *CommandMustLock[] = {
  0, BusMustLock, 0, PinMustLock,
  DIORawMustLock, DIOMustLock, TWIMustLock, 0,
  SPIMustLock
};

unsigned U32(char *str) {
  unsigned u32;
  OptionUnsigned(str,&u32,0);
  return u32;
}

int State(char *str) {
  if (!strcasecmp(str,"INPUT")) {
    return INPUT;
  } else if (!strcasecmp(str,"HIGH")) {
    return HIGH;
  } else if (!strcasecmp(str,"LOW")) {
    return LOW;
  } else return U32(str);
}

int DIONum(System *sys,char *str) {
  int number = 1;
  char *s = str;
  while (*s) {
    if (!isdigit(*s) && !isspace(*s)) break;
    s++;
  }
  if (*s) { // contains non-numeric, non-whitespace character
    return sys->MapLookup(sys,str);
  } else { // contains only numbers and whitespace
    return U32(str);
  }
}

// parse the arguments passed and modify the following cmd fields:
// Inst
// Class
// Opcode
// Extra (for locks)
// Command (not really needed since we translate it to Opcode)
int CommandParse(int argc,char **argv,tsctlCommand *cmd,int canlock) {
  char *tmp;

  // split instance from class, if specified, otherwise assume 0
  if (tmp = strchr(argv[2],':')) {
    *tmp = 0;
    cmd->Inst = strtol(tmp+1,NULL,0);
    if (cmd->Inst < 0) cmd->Inst = 0;
  } else {
    cmd->Inst = 0;
  }
  for (cmd->Class=0;Class[cmd->Class];cmd->Class++) {
    if (!strcmp(Class[cmd->Class],argv[2])) {
      break;
    }
  }
  if (!Class[cmd->Class]) return CommandErrorClass; 
  if (argc < 4) return CommandErrorArgCount;

  tmp = argv[3];
  while (*tmp) tmp++;
  tmp -= 4;
  if (!strcmp(tmp,"Lock")) {
    // Lock: Bus, Pin, DIORaw, DIO, TWI, SPI
    // Don't: System, Time, CAN
    if (cmd->Class == NetSystemClass || cmd->Class == NetTimeClass
	|| cmd->Class == NetCANClass) return CommandErrorCommandBad;
    if (argc != 5) return CommandErrorArgsBad;
    /*
      NOUNLOCK SHARED NONBLOCKING
      000 WriteLock
      001 TryWriteLock
      010 ReadLock
      011 TryReadLock
      100 FOD_WriteLock
      101 FOD_TryWriteLock
      110 FOD_ReadLock
      111 FOD_TryReadLock
    */

    if (!strcmp(argv[3],"WriteLock")) {
      cmd->Extra = 0;
    } else if (!strcmp(argv[3],"TryWriteLock")) {
      cmd->Extra = 1;
    } else if (!strcmp(argv[3],"ReadLock")) {
      cmd->Extra = 2;
    } else if (!strcmp(argv[3],"TryReadLock")) {
      cmd->Extra = 3;
    } else if (!strcmp(argv[3],"FOD_WriteLock")) {
      cmd->Extra = 4;
    } else if (!strcmp(argv[3],"FOD_TryWriteLock")) {
      cmd->Extra = 5;
    } else if (!strcmp(argv[3],"FOD_ReadLock")) {
      cmd->Extra = 6;
    } else if (!strcmp(argv[3],"FOD_TryReadLock")) {
      cmd->Extra = 7;
    } else if (!strcmp(argv[3],"WriteUnlock")) {
      cmd->Extra = 8;
    } else if (!strcmp(argv[3],"ReadUnlock")) {
      cmd->Extra = 10;
    } else {
      // note: we assume that there will never be an API command ending
      // in "Lock" that is not a Lock/Unlock command!
      return CommandErrorCommandBad;
    }
    cmd->OpCode = 0;
  } else if (!strcmp(argv[3],"Preempt")) {
    if (argc != 4) return CommandErrorArgsBad;
    cmd->OpCode = 0;
    cmd->Extra = -1;
  } else {
    // check for valid Command with correct number of args
    for (cmd->Command=0;CommandNames[cmd->Class][cmd->Command];cmd->Command++) {
      if (!strcmp(CommandNames[cmd->Class][cmd->Command],argv[3])) {
	break;
      }
    }
    if (!CommandNames[cmd->Class][cmd->Command]) return CommandErrorCommandBad;

    if (argc-4 != CommandOpts[cmd->Class][cmd->Command]) { // or <
      return CommandErrorArgsBad;
    }
    cmd->OpCode = CommandOpcode[cmd->Class][cmd->Command];
    if (CommandMustLock[cmd->Class]) {
      cmd->MustLock = CommandMustLock[cmd->Class][cmd->Command];
    } else {
      cmd->MustLock = MustNoLock;
    }
  }

}

void test() {
  //printf("%d\n",n=sys->MapLength(sys));
  /*
  for (i=0;i<n;i++) {
    char *tmp = sys->MapGet(sys,i);
    printf("%d:%s\n",i,tmp);
    ArrayFree(tmp);
  }
  */
  //PrototypeDump(protosSystem);
  //printf("%d:%s\n",index,protosSystem[index]->command);
  //for (i=0;i<ArrayLength(protosSystem[index]->reqtypes);i++) {
  //printf("%d ",protosSystem[index]->reqtypes[i]);
  //}
  //printf("\n");

}

#endif

int tsctlInterpret(OutInfo *oi,char** argv) {
  prototype *p;
  char *str,*classfunc;
  int i,inst = 0;

  // fixme: assumes localhost
  // TO DO:
  // 1. print error messages as shell variables using Output_1008
  // 2. if length of argv is 1, scan table and print out all possible
  //    commands for the class given
  PrototypeInit();
  PrototypeInit2();
  if (ArrayLength(argv) < 2) {
    printf("Usage: tsctl <Class> <Command> ...\n");
    return 1;
  }
  str = argv[0];
  while (*str && *str != ':') str++;
  if (*str == ':') {
    *(str++) = 0;
    inst = strtoul(str,0,0);
  }
  classfunc = strf("%s %s",argv[0],argv[1]);
  p = (prototype *)HashTableLookup(ci,classfunc);
  if (!p) {
    printf("Error: No class %s with function %s\n",argv[0],argv[1]);
    return 1;
  }
  ArrayFree(classfunc);

  int argsprovided = ArrayLength(argv)-2;
  int argsexpected = ArrayLength(p->reqtypes);
  for (i=1;i<ArrayLength(p->replytypes);i++) {
    //    if (p->replytypes[i] == 1032 || p->replytypes[i] == -1032
    //	|| p->replytypes[i] == 1016 || p->replytypes[i] == -1016) argsexpected++;
    if (p->replytypes[i] >= 1000 && p->replytypes[i] <= 1999
	|| p->replytypes[i] <= -1000 && p->replytypes[i] >= -1999) argsexpected++;
  }
  if (argsexpected > argsprovided) {  // != for strictness
    printf("%d args provided, expected %d\n",argsprovided,argsexpected);
    return 1;
  }
  p->f(oi,inst,argv+2);
  return ArrayLength(p->replytypes);
}


int tsctlProcessFile(FILE *f) {
  char cmd[80],*str,**argv;
  int argc,len,quoting;
  OutInfo oibase = { 
    .fAssign = 1, .oMode = MODE_DEC, .aMode = MODE_DEC, .tsctl_o = 1,
    .ht = HashTableNewASCIIZ() };
  
  while (!feof(f)) {
    if (!fgets(cmd,78,f)) {
      Output_Flush(oibase.ht,1);
      return 0;
    }
    if (!strncasecmp(cmd,"end",3)) return 0;
    len = strlen(cmd);
    str = cmd; argc = 0; quoting = 0;
    if (cmd[len-1] == '\n') cmd[len-1] = 0;
    argv = split(cmd,' ');
    tsctlInterpret(&oibase,argv);
    // TODO: ArrayFree elements of array, then array
  }
  Output_Flush(oibase.ht,1);
  return 0;
}

int iabs(int i) { return i>0 ? i : -i; }

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

int main(int argc,char *argv[]) {
  struct sigaction sa;

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

  // argument "--" to read commands from stdin
  // argument "-f file" to read commands from file
  // otherwise, commands separated by a semi-colon as it's own argument

  if (argc == 2 && !strcmp(argv[1],"--server")) {
    ServerData sd;

    sd.f = httpServer;
    sd.constor = httpServerConstor;
    sd.destor = httpServerDester;

    SignalIgnore(SIGCHLD);
    SignalIgnore(SIGPIPE);
    ThreadInit();
    ThreadNew("http server",0,ServerTCP,-8000,&sd,0);
    printf("Server running\n");
    while (1) sleep(1);
  } else if (argc == 2 && !strcmp(argv[1],"--")) {
    tsctlProcessFile(stdin);
  } else if (argc == 3 && !strcmp(argv[1],"-f")) {
    FILE *f = fopen(argv[2],"r");
    if (!f) {
      fprintf(stderr,"Error opening %s: %m\n",argv[2]);
      return 1;
    }
    tsctlProcessFile(f);
    fclose(f);
  } else if (argc < 3) {
    fprintf(stderr,"Usage:\n");
    fprintf(stderr,"\ttsctl --server\n");
    fprintf(stderr,"\ttsctl <Class[:Instance]> <Command> [Args...]\n");
    return 1;
  } else {
    int i=1,start=1,j;
    char** argv2;
    OutInfo oibase = { 
      .fAssign = 1, .oMode = MODE_DEC, .aMode = MODE_DEC, .tsctl_o = 1,
      .ht = HashTableNewASCIIZ() };

    while (i < argc) {
      for (i=start;i<argc && strcmp(argv[i],";");i++);
      argv2 = ArrayAlloc(i-start,sizeof(char*));
      j = start;
      while (start < i) {
	argv2[start-j] = ASCIIZ(argv[start]);
	start++;
      }
      start++;
      tsctlInterpret(&oibase,argv2);
      ArrayFree(argv2);
    }
  }
  return 0;
}

#if 0
void SystemCommand12(OutInfo *oi,System *sys,char *argv[]) {
	int arg0 = Input_32(argv[0]);
	int *arg1 = ArrayAlloc(1,sizeof(int));
	char* ret = SystemArr[inst]->MapGet(SystemArr[inst],arg0,arg1);
	Output_1008(oi,"MapGet",ret);
	Output_1032(oi,"MapGet",arg1);
	ArrayFree(arg1);
	ArrayFree(ret);
}

#endif
