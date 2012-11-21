#ifndef __dioctlConfig_c
#define __dioctlConfig_c
#include "dioctl.dict.c"
#include "dioctl_map.c"
#include "shell.c"
#include "Array.h"
#include "System.h"

int line_type(char *line) {
  if (grep1(line,"attrib\\.....\\.Wire")) return 11;
  //3. attrib.Connector.Name._
  if (grep1s(line,"attrib\\.Connector\\.Name\\.[A-Za-z_0-9]\\+$")) return 3;
  //2. attribute.Connector.Count
  if (grep1s(line,"attrib\\.Connector\\.Count$")) return 2;
  //4. attrib.Connector.#1.Pins
  if (grep1s(line,"attrib\\.Connector\\.[0-9]\\+\\.Pins$")) return 4;
  //5. attrib.Connector.#1.#2
  if (grep1s(line,"attrib\\.Connector\\.[0-9]\\+\\.[0-9]\\+$")) return 5;
  //9. attrib.DIO.Count
  if (grep1s(line,"attrib\\.DIO\\.Count$")) return 9;
  //10. attrib.DIO.Instances
  if (grep1s(line,"attrib\\.DIO\\.Instances$")) return 10;
  //1. NAME=# , where NAME does not contain any periods
  if (grep1s(line,"[A-Za-z0-9_]\\+$")) return 1;
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
  char* str2;

  S->DIOCount = S->DIOConns = 0;
  for (i=1;i<=S->DIOInstances;i++) {
    conf = config;
    for (j=0;j<ArrayLength(conf);j++) {
      str2 = ArrayDup(conf[j]);
      str = XYZ(str2,&val1);
      //fprintf(stderr,"%s = %d\n",str,val1);
      type = line_type(str);
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
      if (tofree) ArrayFree(str);
    }
    S->DIOStart += S->DIOCount;
    S->DIOConn += S->DIOConns;
  }
  return **map;
}

#define NUM 130
char* decode(char *str) {
  unsigned char *s = (unsigned char *)str;
  char* ret;
  int len = 0,n;
  static int initialized = 0;

  if (!initialized) {
    initialized = 1;
    char *s;
    int i;
    for (i=0;dict[i];i++);
    s = malloc(4*(NUM-10+1));
    for (n=NUM;n>9;n--) {
      sprintf(&s[(n-10)*4],"%d",n);
      dict[i++] = &s[(n-10)*4];
    }
    dict[i] = 0;
  }
 
  while (*s) {
    if (diodict[*s] != -1) {
      n = strlen(dict[diodict[*s]]);
      len += n;
    } else {
      len++;
    }
    s++;
  }
  ret = ArrayAlloc(len,sizeof(char));
  s = (unsigned char *)str;
  len = n = 0;
  while (*s) {
    if (diodict[*s] != -1) {
      n = strlen(dict[diodict[*s]]);
      memcpy(ret+len,dict[diodict[*s]],n);
      len += n;
    } else {
      ret[len++] = *s;
    }
    s++;
  }
  return ret;
}

char** decodearch(char **enc) {
  int i,n = len(enc);
  char** ret = ArrayAlloc(n,sizeof(char*));

  for (i=0;i<n;i++) {
    ret[i] = decode(enc[i]);
  }
  return ret;
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

void dioctl_config_add(char **names) {
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
    tmp = decodearch(names);
    dioctladd(&archmapptr,tmp,&d);
    ArrayFree(tmp);
  } else {
    archmapptr[0] = finish_diostuff(archmapptr[0],&d);
  }
}

#ifdef TESTME
char *l1names[] = {
  "ts4200", "ts4700", "ts4800",0
};
char *l2names[] = {
  "ts8100", "ts8160", "ts8200", "ts8390", "ts8900", "ts9490",0
};
char *l3names[] = {
  "tsdio24","tsrelay8",0
};

char **socket_board_names[] = {
  ts4200_dioctl_config,
  ts4700_dioctl_config,
  ts4800_dioctl_config,
  0
};

int *socket_board_values[] = {
  ts4200_dioctl_config_val,
  ts4700_dioctl_config_val,
  ts4800_dioctl_config_val,
  0
};

char **base_board_names[] = {
  ts8100_dioctl_config,
  ts8160_dioctl_config,
  ts8200_dioctl_config,
  ts8390_dioctl_config,
  // 8820
  ts8900_dioctl_config,
  ts9490_dioctl_config,
  0
};

int *base_board_values[] = {
  ts8100_dioctl_config_val,
  ts8160_dioctl_config_val,
  ts8200_dioctl_config_val,
  ts8390_dioctl_config_val,
  // 8820
  ts8900_dioctl_config_val,
  ts9490_dioctl_config_val
};

char **pc104_board_names[] = {
  tsdio24_dioctl_config,
  tsrelay8_dioctl_config,
  0
};

int *pc104_board_values[] = {
  tsdio24_dioctl_config_val,
  tsrelay8_dioctl_config_val
};

void diff(char *name1,char *name2) {
  char* cmd = strf("diff %s %s\n",name1,name2);
  system(cmd);
  ArrayFree(cmd);
}

int main(int argc,char *argv[]) {
  char*** level1 = socket_board_names;
  char*** level2 = base_board_names;
  char*** level3 = pc104_board_names;
  int i,j,k;
  diostuff d;

  char *s;
  int n;
  for (i=0;dict[i];i++);
  s = malloc(4*(NUM-10+1));
  for (n=NUM;n>9;n--) {
    sprintf(&s[(n-10)*4],"%d",n);
    dict[i++] = &s[(n-10)*4];
  }
  dict[i] = 0;

  i = j = k = -1;
  if (argc > 1) {
    for (i=0;l1names[i] && strcmp(l1names[i],argv[1]);i++);
    if (!l1names[i]) return;
    if (argc > 2) {
      for (j=0;l2names[j] && strcmp(l2names[j],argv[2]);j++);
      if (l2names[j] && argc > 3) {
	for (k=0;l3names[k] && strcmp(l3names[k],argv[3]);k++);
      }
    }
  }
  fout = fopen("tmp.txt","w");
  init_diostuff(&d);
  dioctladd(decodearch(level1[i]),socket_board_values[i],&d);
  if (j >= 0) {
    subinit_diostuff(&d);
    dioctladd(decodearch(level2[j]),base_board_values[j],&d);
    if (k >= 0) {
      subinit_diostuff(&d);
      dioctladd(decodearch(level3[k]),pc104_board_values[k],&d);
      n = 4;
      while (n < argc) {
	for (k=0;l3names[k] && strcmp(l3names[k],argv[n]);k++);
	if (l3names[k]) {
	  subinit_diostuff(&d);
	  dioctladd(decodearch(level3[k]),pc104_board_values[k],&d);
	}
	n++;
      }
    }
  }
  finish_diostuff(&d);
  fclose(fout);
  return 0;
  for (i=0;socket_board_names[i];i++) {
    init_diostuff(&d);
    dioctladd(decodearch(level1[i]),socket_board_values[i],&d);
    finish_diostuff(&d);
    fclose(fout);
    diff("tmp.txt",strf("~/libtsctl-src/config/%s.dioctl.config",l1names[i]));
    for (j=0;base_board_names[j];j++) {
      fout = fopen("tmp.txt","w");
      init_diostuff(&d);
      dioctladd(decodearch(level1[i]),socket_board_values[i],&d);
      subinit_diostuff(&d);
      dioctladd(decodearch(level2[j]),base_board_values[j],&d);
      finish_diostuff(&d);
      fclose(fout);
      diff("tmp.txt",strf("~/libtsctl-src/config/%s-%s.dioctl.config",
			  l1names[i],l2names[j]));
      for (k=0;pc104_board_names[k];k++) {
	fout = fopen("tmp.txt","w");
	init_diostuff(&d);
	dioctladd(decodearch(level1[i]),socket_board_values[i],&d);
	subinit_diostuff(&d);
	dioctladd(decodearch(level2[j]),base_board_values[j],&d);
	subinit_diostuff(&d);
	dioctladd(decodearch(level3[k]),pc104_board_values[k],&d);
	finish_diostuff(&d);
	diff("tmp.txt",strf("~/libtsctl-src/config/%s-%s-%s.dioctl.config",
			    l1names[i],l2names[j],l3names[k]));
      }
    }
  }

}
#endif
#endif
