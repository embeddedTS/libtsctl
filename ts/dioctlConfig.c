#ifndef __dioctlConfig_c
#define __dioctlConfig_c
#ifndef DONT_USE_BZ2
#include <bzlib.h>
#endif
#include <stdio.h> // sprintf
#include "shell.h"
#include "Array.h"
#include "System.h"
#include "shell.h"


int line_type(char *line) {
  static int initialized = 0;
  static regex_t pat1,pat2,pat3,pat4,pat5,pat6,pat7,pat8;

  if (!initialized) {
    regcomp(&pat1,"attrib\\.....\\.Wire",REG_NOSUB|REG_EXTENDED);
    regcomp(&pat2,"attrib\\.Connector\\.Name\\.[A-Za-z_0-9]\\+$",REG_NOSUB);
    regcomp(&pat3,"attrib\\.Connector\\.Count$",REG_NOSUB);
    regcomp(&pat4,"attrib\\.Connector\\.[0-9]\\+\\.Pins$",REG_NOSUB);
    regcomp(&pat5,"attrib\\.Connector\\.[0-9]\\+\\.[0-9]\\+$",REG_NOSUB);
    regcomp(&pat6,"attrib\\.DIO\\.Count$",REG_NOSUB);
    regcomp(&pat7,"attrib\\.DIO\\.Instances$",REG_NOSUB);
    regcomp(&pat8,"[A-Za-z0-9_]\\+$",REG_NOSUB);
    initialized = 1;
  }

  if (!regexec(&pat1,line,0,0,0)) return 11;
  //3. attrib.Connector.Name._
  if (!regexec(&pat2,line,0,0,0)) return 3;
  //2. attribute.Connector.Count
  if (!regexec(&pat3,line,0,0,0)) return 2;
  //4. attrib.Connector.#1.Pins
  if (!regexec(&pat4,line,0,0,0)) return 4;
  //5. attrib.Connector.#1.#2
  if (!regexec(&pat5,line,0,0,0)) return 5;
  //9. attrib.DIO.Count
  if (!regexec(&pat6,line,0,0,0)) return 9;
  //10. attrib.DIO.Instances
  if (!regexec(&pat7,line,0,0,0)) return 10;
  //1. NAME=# , where NAME does not contain any periods
  if (!regexec(&pat8,line,0,0,0)) return 1;
  if (line[0] && line[0] != '#') {
    //fprintf(stderr,"Warning:no match for '%s'\n",line);
  }
  return 0;
}

typedef struct {
  int DIOStart; // = 0 at init
  int DIOConns; // = 0 before each dioctladd()
  int DIOConn; // = 0 at init
  int DIOCount; // = 0 before each dioctladd()
  int DIOInstances; // = 1 before each dioctladd() ?
} diostuff;

// X.#1.Pins -> X.#1+n.Pins
char *add1(char *line,int n) {
  line = strdup(line);
  char *str = line,*ret;
  int num;

  //ret = malloc(strlen(line)+2);
  ret = ArrayAlloc(strlen(line)+2,sizeof(char));
  while (!isdigit(*str)) str++;
  num = atoi(str);
  *str = 0;
  while (*str != '.') str++;
  sprintf(ret,"%s%d%s",line,num+n,str);
  free(line);
  return ret;  
}

// X.#1.#2 -> X.#1+n.#2
char *add13(char *line,int n) {
  line = strdup(line);
  char *str = line,*str2,*ret;
  int num,num2;

  //ret = malloc(strlen(line)+4);
  ret = ArrayAlloc(strlen(line)+4,sizeof(char));
  while (!isdigit(*str)) str++;
  num = atoi(str);
  *str = 0;
  while (*str != '.') str++;
  sprintf(ret,"%s%d%s",line,num+n,str);
  free(line);
  return ret;
}

FILE *fout;
System *SystemInit(int);

char* XYZ(char* str,int *val) {
  static System *sys = 0;
  char *str0 = str;
  char *name;
  char* tmp;
  unsigned value;
  static int lines=0; lines++;

  
  if (!sys) sys = SystemInit(0);
  while (*str && *str != '=') str++;
  if (*str != '=') return;
  *str = 0;
  str++;
  value = strtoul(str,0,0);
  name = str0;
  if (value == 0 && str[0] != '0') {
    tmp = ASCIIZ(str);
    value = sys->MapLookup(sys,tmp);
    ArrayFree(tmp);
  }
  *val = value;
  return name;
}

#ifdef TESTME
int dioctladd(char **config,int *val,diostuff *S) {
#else
NameValuePair* _MapConfigLineAssign(NameValuePair* map,char *name,int value);
extern NameValuePair **archmapptr;

NameValuePair* dioctladd(NameValuePair ***map,char **config,diostuff *S) {
#endif
  int type,inst=-1,v,i,j,thisInstance=1,tofree,val1;
  char *str,**conf;
  char* str2, *str2a;

  S->DIOCount = S->DIOConns = 0;
  for (i=1;i<=S->DIOInstances;i++) {
    conf = config;
    for (j=0;j<ArrayLength(conf);j++) {
      str2 = str2a = ArrayDup(conf[j]);
      while (isspace(*str2)) str2++;
      if (str2[0] == '#' || !str2[0]) continue;
      str = XYZ(str2,&val1); 
      type = line_type(str); 
      //fprintf(stderr,"%s = %d (%d)\n",str,val1,type);
      tofree = 0;
      switch (type) {
      case 1: val1 += S->DIOStart; break;
      case 2: S->DIOConns = val1; break;
      case 3:
	if (inst == -1) {
	  str = str2;
	  val1 += S->DIOConn;
	} else {
	  str = strf("%s%d_",str2,i);
	  tofree = 1;
	  //ArrayFree(conf[j]);
	  //conf[j] = str;
	  val1 += S->DIOConn;
	}
	break;
      case 4:  
	str = add1(str2,S->DIOConn); 
	tofree = 1;
	//ArrayFree(conf[j]);
	//conf[j] = str;
	break;
      case 5:
	str = add13(str2,S->DIOConn); 
	tofree = 1;
	//ArrayFree(conf[j]);
	//conf[j] = str;
	val1 += S->DIOStart;
	break;
      case 9: 
	S->DIOCount = val1; 
	break;
      case 10:
	if (thisInstance == 1) {
	  inst = S->DIOInstances = val1; break;
	}
      }
      if (type != 9 && type != 10 && type != 2) {
#ifdef TESTME
	fprintf(fout,"%s=%d\n",str,val1);
#else
	**map = _MapConfigLineAssign(**map,str,val1); 
#endif
      }
      if (tofree) ArrayFree(str2a);
    }
    S->DIOStart += S->DIOCount;
    S->DIOConn += S->DIOConns;
  }
  return **map;
}

#define NUM 130

char** decodearch2(char *enc,int len,int lenout) {
#ifndef DONT_USE_BZ2
  char* outarr = ArrayAlloc(lenout,sizeof(char));
  int ret = BZ2_bzBuffToBuffDecompress(outarr,&lenout,enc,len,0,0);
  ret = (ret == BZ_OK);
#else
  char *outarr = enc;
  int ret = 1;
#endif
  char** arr=0;
  if (ret) {
    arr = split(outarr,'\n');
  }
#ifndef DONT_USE_BZ2
  ArrayFree(outarr);
#endif
  return arr;
}

void init_diostuff(diostuff *d) {
  d->DIOStart=0;
  d->DIOConn=0;
  
  d->DIOConns=0;
  d->DIOCount=0;
  d->DIOInstances=1;
}

void subinit_diostuff(diostuff *d) {
  d->DIOConns = d->DIOCount = 0;
  d->DIOInstances = 1;
}

#ifdef TESTME
void finish_diostuff(diostuff *d) {
  fprintf(fout,"attrib.Connector.Count=%d\n",d->DIOConn);
  fprintf(fout,"attrib.DIO.Count=%d\n",d->DIOStart);
}
#else
NameValuePair* finish_diostuff(NameValuePair *map,diostuff *d) {
  map = _MapConfigLineAssign(map,"attrib.Connector.Count",d->DIOConn);
  return _MapConfigLineAssign(map,"attrib.DIO.Count",d->DIOStart);
}
#endif

NameValuePair *archmap;
NameValuePair **archmapptr = &archmap;
int CompareNameValuePair(const void *a1,const void *b1);

void dioctl_config_add2(char *names,int len,int lenout) {
  static int started = 0;
  static diostuff d;
  char** tmp;

  if (!started) {
    init_diostuff(&d);
    archmapptr[0] = ArrayAlloc(0,sizeof(NameValuePair));
    ArraySort(archmapptr[0],CompareNameValuePair); 
    started = 1;
  } else {
    subinit_diostuff(&d); 
  }
  if (names) {
    tmp = decodearch2(names,len,lenout); 
    dioctladd(&archmapptr,tmp,&d);
    ArrayFree(tmp);
  } else {
    archmapptr[0] = finish_diostuff(archmapptr[0],&d);
  }
}

#endif
