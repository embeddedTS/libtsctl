#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dioctl_map.c"
#include "dioctl.dict.c"
#include "Array.h"

/*
  simple static dictionary based compression, to reduce the amount
  of space required in the tsctl binary to store all the dioctl.config
  files for all supported architectures.

  we have up to 179 dictionary elements, in the following ranges:
  1-45, 58-63, 127-255
 */


// encoding is slow, but this isn't important because we do this statically
// and generate code from it once at the factory.  if it were important that
// it be faster, we could sort dict and do a binary search or even use a
// hash table.
char *encode(char *str) {
  int i;
  char *o,*ret = malloc(strlen(str)+1);
  
  o = ret;
  while (*str) {
    for (i=0;dict[i];i++) {
      if (!strncmp(dict[i],str,strlen(dict[i]))) {
	*(o++) = dioeict[i];
	str += strlen(dict[i]);
	break;
      }
    }
    if (!dict[i]) {
      *(o++) = *(str++);
    }
  }
  *o = 0;
  return ret;
}

char *decode(char *str) {
  unsigned char *s = (unsigned char *)str;
  char *ret,*r;
  int len = 0,n;
  
  while (*s) {
    if (diodict[*s] != -1) {
      n = strlen(dict[diodict[*s]]);
      len += n;
    } else {
      len++;
    }
    s++;
  }
  r = ret = malloc(len+1);
  s = (unsigned char *)str;
  while (*s) {
    if (diodict[*s] != -1) {
      strcpy(r,dict[diodict[*s]]);
      r += strlen(dict[diodict[*s]]);
    } else {
      *(r++) = *s;
    }
    s++;
  }
  *r = 0;
  return ret;
}

void print_string(char *str) {
  putchar('"');
  while (*str) {
    if (*str < 32 || *str >= 127 || *str == '"') {
      printf("\\%03o",*(unsigned char *)str);
    } else {
      putchar(*str);
    }
    str++;
  }
  putchar('"');
}

void encode_file(char *filename) {
  FILE *f;
  char *str,buf[301],*res,*chk;
  int su=0,sc=0,i;
  char *header;

  fprintf(stderr,"%s:",filename);
  f = fopen(filename,"r");
  if (!f) {
    fprintf(stderr,"%m\n");
    return;
  }

  header = malloc(strlen(filename)+1);
  strcpy(header,filename);
  str = header;
  while (*str) {
    if (*str == '.') *str = '_';
    str++;
  }
  printf("char *%s[] = {\n",header);

  while (!feof(f)) {
    buf[0] = 0;
    fgets(buf,300,f);
    if (buf[0] == 0) goto encode_file_done;
    str = buf;
    while (*str) str++;
    str--;
    while(str >= buf 
	  && (*str == '\n' || *str == '\r' || *str == ' ' || *str == '\t')) {
      *str = 0;
      str--;
    }
    if (buf[0] && buf[0] != '#') {
      su += strlen(buf) + 1;
      //fprintf(stderr,"%s\n",buf);
      res = encode(buf);
      chk = decode(res);
      if (strcmp(chk,buf)) {
	fprintf(stderr,"fail: %s\n",buf);
	exit(3);
      }
      sc += (strlen(res) + 5);
      putchar('\t');
      print_string(res);
      putchar(',');
      putchar('\n');
    }
  }
 encode_file_done:
  printf("\t0\n};\n");
  free(header);

  fprintf(stderr,"%d/%d=%.3f\n",su,sc,(float)su/sc);
  return;
}

#define NUM 130
// dioctlConfig.c must have same definition

int main(int argc,char *argv[]) {
  int i,n;
  char *s;

  for (i=0;dict[i];i++);
  s = malloc(4*(NUM-10));
  for (n=NUM;n>9;n--) {
    sprintf(&s[(n-10)*4],"%d",n);
    dict[i++] = &s[(n-10)*4];
  }
  if (179-i < 0) {
    fprintf(stderr,"FATAL: too many dictionary entries, %d > 179\n",i);
    return 3;
    // remove dictionary entries of lower value of NUM
  }
  //fprintf(stderr,"%d left\n",179-i);
  dict[i] = 0;
  if (argc > 1) {
    encode_file(argv[1]);
  }
}

