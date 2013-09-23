#ifndef __shell_c
#define __shell_c
#include <sys/types.h>
#include <errno.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <regex.h>
#include <stdarg.h>
#include "HashTable.h"
#include "Array.h"

// to test:
// ls
//
// tested:
// cat, strf, split, var, assign

static HashTable *symtab;
static regex_t varsubstpreg;
char *nullstring;

void shellinit() {
  symtab = HashTableNewArrKey();
  nullstring = ASCIIZ("");
  regcomp(&varsubstpreg,"[^$]*(\\$[A-Za-z][A-Za-z0-9_.]*|\\$\\{[A-Za-z][A-Za-z0-9_.]*\\})?",REG_EXTENDED);
}

// obsolete
char *strappend(char *str1,char *str2) {
  char *str = malloc(strlen(str1)+strlen(str2)+1);
  strcpy(str,str1);
  strcat(str,str2);
  return str;
}

#ifndef __vstrf_defined
#define __vstrf_defined
char *vstrf(char *format,va_list ap) {
  int len;
  char *str,dummy[1];

  len = vsnprintf(dummy,0,format,ap);
  str = ArrayAlloc(len,sizeof(char));
  vsprintf(str,format,ap);
  return str;
}
#endif
char *strf(char *format,...) {
  va_list ap;
  int len;
  char *str,dummy[1];

  va_start(ap, format);
  len = vsnprintf(dummy,0,format,ap);
  str = ArrayAlloc(len,sizeof(char));
  vsprintf(str,format,ap);
  va_end(ap);
  return str;
}

char *var(char *name) {
  char *ret;
  if (!symtab) { shellinit(); return nullstring; }
  ret = HashTableLookup(symtab,name);
  return ret ? ret : nullstring;
}

char *assign(char *name,char *value) {
  if (!symtab) shellinit();
  if (!value) {
    HashTableRemove(symtab,name);
  } else {
    HashTableInsert(symtab,name,value);
  }
  return value;
}

char *ShellContext = 0;

// varname is either $name or ${name}
static char *lookup(char *varname) {
  char *ret;
  varname++;
  if (*varname == '{') {
    varname[strlen(varname)-1] = 0;
    varname++;
  }
  if (ShellContext) {
    char *tmp = strf("%s%s",ShellContext,varname);
    ret = var(tmp);
    free(tmp);
  } else {
    ret = var(varname);
  }
  return ret;
}

/*
// expands any occurences of $var and ${var} in name with the values of
// those variables, if any
// FIXME: strappend, lookup, strsub
char *varsubst(HashTable *symtab,char* name) {
  char* ret;
  regmatch_t pmatch[2];
  int i,j;

  if (!symtab) shellinit();

  do {
    if (regexec(&varsubstpreg,name,2,pmatch,0) == REG_NOMATCH) {
      return ret;
    }
    if (pmatch[1].rm_so != -1) {
      ret = strappend(ret,strsub(name,pmatch[0].rm_so,pmatch[1].rm_so-1));
      ret = strappend(ret,
		      lookup(strsub(name,pmatch[1].rm_so,pmatch[1].rm_eo-1)));
      //printf("%d,%d:%s:",pmatch[1].rm_so,pmatch[1].rm_eo,
      //strsub(name,pmatch[1].rm_so,pmatch[1].rm_eo-1));
      //for (j=pmatch[1].rm_so;j<pmatch[1].rm_eo;j++) printf("%c",name[j]);
      //printf("\n");
    } else {
      ret = strappend(ret,name);
    }
    name += pmatch[0].rm_eo;
  } while (*name);
  return ret;
}
*/

void sourceline(char *line) {
  char *str;
  int nosubst=0;
  if (line[0] != '#') {
    str = line;
    while (*str && *str != '=') str++;
    if (*str != '=') return;
    *(str++) = 0;
    if (str[0] == '"' || str[0] == '\'') {
      nosubst=(str[0] == '\'');
      char *last = str + strlen(str)-1;
      if (*last == str[0]) {
	*last = 0;
	str++;
      }
    }
    if (nosubst) {
      assign(strdup(line),strdup(str));
    } else {
      //assign(strdup(line),varsubst(str));
    }
  }
}

char **cat(char *filename) {
  FILE *f = fopen(filename,"r");
  char **ret,*str,buf[1024];
  int n=0;

  ret = ArrayAlloc(0,sizeof(char *));
  if (!f) return ret;
  while (!feof(f)) {
    if (fgets(buf,1023,f)) {
      str = buf;
      while (*str) str++;
      str--;
      while(str >= buf && (*str == '\n' || *str == '\r')) {
	*str = 0;
	str--;
      }
      ret = ArrayQueue(ret,A(char*,ASCIIZ(buf)));
      n++;
    }
  }
  fclose(f);
  return ret;
}

void source(char *filename,char *prefix) {
  FILE *f = fopen(filename,"r");
  char *str,buf[1024],*pbuf=buf,*ShellContextOld = ShellContext;
  if (!f) return;
  ShellContext = prefix;
  if (prefix) {
    strcpy(buf,prefix);
    pbuf += strlen(prefix);
  }
  while (!feof(f)) {
    fgets(pbuf,1023,f);
    if (pbuf[0] == 0) break;
    str = buf;
    while (*str) str++;
    str--;
    while(str >= buf && (*str == '\n' || *str == '\r')) {
      *str = 0;
      str--;
    }
    sourceline(buf);
  }
  fclose(f);
  ShellContext = ShellContextOld;
}

int len(char **in) {
  int n;
  if (!in) return 0;
  for (n=0;in[n];n++);
  return n;
}

char** ls(const char *path,char *regex) {
  regex_t preg;
  DIR *dir = opendir(path);
  struct dirent *entry;
  char **ret;
  int i=0,n=0;

  if (dir == 0) return 0;
  if (regex) {
    if (regcomp(&preg,regex,REG_NOSUB|REG_EXTENDED) != 0) {
      regex = 0;
    }
  }

  entry = readdir(dir);
  while (entry) {
    if (!regex || !regexec(&preg,entry->d_name,0,0,0)) i++;
    entry = readdir(dir);
  }
  rewinddir(dir);

  ret = ArrayAlloc(i,sizeof(char *));
  entry = readdir(dir);
  while (entry && n < i) {
    if (!regex || !regexec(&preg,entry->d_name,0,0,0)) {
      ret[n] = ArrayAlloc(strlen(entry->d_name),sizeof(char));
      strcpy(ret[n++],entry->d_name);
    }
    entry = readdir(dir);
  }
  closedir(dir);
  if (regex) regfree(&preg);
  return ret; // length n
}

// flags: match versus non-matching, case insensitive
char **grep(char **in,char *regex,int match) {
  regex_t preg;
  char **ret;
  int i,n,m=0;

  if (!in) return 0;
  match = (match == 0) ? REG_NOMATCH : 0;
  if (regcomp(&preg,regex,REG_NOSUB) != 0) return 0;
  n = len(in);
  ret = malloc(sizeof(char *) * (n+1));
  for (i=0;i<n;i++) {
    if (regexec(&preg,in[i],0,0,0) == match) {
      ret[m++] = in[i];
    }
  }
  ret[m] = 0;
  ret = realloc(ret,sizeof(char *) * (m+1));
  return ret; // length m
}

int grep1(char *str,char *regex) {
  regex_t preg;
  int ret;

  if (!regex || !regex[0]) return 0;
  if (regcomp(&preg,regex,REG_NOSUB|REG_EXTENDED) != 0) return 0;
  ret = (regexec(&preg,str,0,0,0) == 0);
  regfree(&preg);
  return ret;
}

int grep1s(char *str,char *regex) {
  regex_t preg;
  int ret;

  if (!regex || !regex[0]) return 0;
  if (regcomp(&preg,regex,REG_NOSUB) != 0) return 0;
  ret = (regexec(&preg,str,0,0,0) == 0);
  regfree(&preg);
  return ret;
}

int grep1s_pre(char *str,regex_t preg) {
  return (regexec(&preg,str,0,0,0) == 0);
}

static int charptrcomp(const void *a,const void *b) {
  return strcmp(* (char * const *) a, * (char * const *) b);
}
static int charptrcompn(const void *a,const void *b) {
  return -strcmp(* (char * const *) a, * (char * const *) b);
}

char **sort(char **in,int asc) {
  int i,n;
  char **ret;
  n = len(in);
  ret = malloc(sizeof(char *) * (n+1));
  for (i=0;i<=n;i++) ret[i] = in[i];
  qsort(ret,n,sizeof(char *),asc?charptrcomp:charptrcompn);
  return ret;
}

char **uniq(char **in) {
  char **ret;
  int i,n,m=0;

  n = len(in);
  ret = malloc(sizeof(char *) * (n+1));
  ret[m++] = in[0];
  for (i=1;i<n;i++) {
    if (strcmp(in[i],ret[m-1])) {
      ret[m++] = in[i];
    }
  }
  ret[m] = 0;
  ret = realloc(ret,sizeof(char *) * (m+1));
  return ret;
}

char **map(char **in,char *(*f)(char *)) {
  char **ret;
  int i,n;

  n = len(in);
  ret = malloc(sizeof(char **) * (n+1));
  for (i=0;i<n;i++) {
    ret[i] = f(in[i]);
  }
  ret[i] = 0;
  return ret;
}

char **split(char *in,char sep) {
  int n=0,m=0;
  char *str = in;
  char **ret;

  if (!in) return ArrayAlloc(0,sizeof(char *));
  while (*str) if (*(str++) == sep) n++;
  if (str[-1] != sep) n++;
  ret = ArrayAlloc(n,sizeof(char *));
  n=0; str = in;
  while (*str) {
    if (*str == sep) {
      ret[n] = ArrayAlloc(m,sizeof(char));
      strncpy(ret[n++],str-m,m);
      m=0;
    } else {
      m++;
    }
    str++;
  }
  if (str[-1] != sep) {
    ret[n] = ArrayAlloc(m,sizeof(char));
    strncpy(ret[n++],str-m,m);
  }
  return ret;
}

char *join(char **in,char *sep) {
  int i,l1=0,l2,n = len(in);
  char *ret;

  l2 = strlen(sep);
  for (i=0;i<n;i++) l1 += (l2 + strlen(in[i]));
  ret = malloc(l1 + 1);
  ret[0] = 0;
  for (i=0;i<n;i++) {
    strcat(ret,in[i]);
    if (i+1 < n) strcat(ret,sep);
  }
  return ret;
}

char *cat1(char *filename) {
  return cat(filename)[0];
}

/* dirbetween - calculate the relative path from src to dest
   needed because symlinks on the ftp server can't be absolute
   note: assumes paths won't contain "." or ".."
 */
char *pathbetween(char *dest,char *src) {
  char *dest0 = dest,*ret,*str;
  int up=0;
  if (*src != '/' || *dest != '/') {
    return dest; // can't compute relative path
  }
  while (*src && *src == *dest) {
    src++; dest++;
  }
  if (!*src) return dest0; // no path because they are the same file!
  if (*(src-1) != '/') {
    while (*src != '/') { src--; dest--; }
    src++; dest++;
  }
  while (*src) {
    if (*(src++) == '/') up++;
  }
  str = ret = malloc(up * 3 * sizeof(char) + strlen(dest) + 1);
  while (up--) {
    *(str++) = '.';
    *(str++) = '.';
    *(str++) = '/';
  }
  *str = 0;
  strcat(str,dest);
  return ret;
}

int ShellDryRun,ShellVerbose;

int cp(char *dest,char *src) {
  char *command = strf("cp %s %s",src,dest);
  int ret=0;
  if (ShellDryRun || ShellVerbose) {
    puts(command);
  } 
  if (!ShellDryRun) {
    ret = system(command);
  }
  free(command);
  return ret;
}

int mv(char *dest,char *src) {
  char *command = strf("mv %s %s",src,dest);
  int ret=0;
  if (ShellDryRun || ShellVerbose) {
    puts(command);
  }
  if (!ShellDryRun) {
    ret = system(command);
  }
  free(command);
  return ret;
}

int tarczf(char *dest,char *src,char *pattern) {
  char *command = strf("cd %s;tar -czf %s %s",src,dest,pattern);
  int ret=0;
  if (ShellDryRun || ShellVerbose) {
    puts(command);
  }
  if (!ShellDryRun) {
    ret = system(command);
  }
  free(command);
  return ret;
}

int symlink1(char *dest,char *src) {
  char *command = strf("ln -sf %s %s",src,dest);
  int ret=0;
  if (ShellDryRun || ShellVerbose) {
    puts(command);
  }
  if (!ShellDryRun) {
    ret = system(command);
  }
  free(command);
  return ret;
}

int system1(char *command) {
  int ret=0;
  if (ShellDryRun || ShellVerbose) {
    puts(command);
  }
  if (!ShellDryRun) {
    ret = system(command);
  }
  return ret;
}

/*
The purpose of this file is to eliminate the need to write simple shell
scripts, which frequently require quirkly syntax and often have significant
overhead spawning sub-processes to perform trivial text operations.

The basic data type we deal with is an array of C (ASCIIZ) strings.
All functions malloc the return array.  If they create or modify the
strings in the array, those are malloced as well, otherwise the existing
data is re-used.

Shell variables are simple string to string lookups.  Variables can
be initialized from a file.  We support a subset of shell syntax:
1. name=value, where any single or double quotes around "value" 
   will be removed.  name must start with an alphabetic character,
   and can be followed by only alphanumeric characters, the underscore,
   and the period.
2. expansion of $var and ${var} in the right-hand side (value), unless
   the right-hand side is enclosed in single quotes.


Concerns:
1. We currently "leak" a lot of memory, because we don't bother to
de-allocate temporary data structures.  Simplest fix would be to link
against GC.  Next choice would be to devise some mechanism to easily
specify temporary usage in an expression so we can free afterwards.
2. All results stay in memory.  We need a pipe analog for external
processes, a kind of stream versus string approach.
3. There isn't any consistency in how we form strings. We can use
strappend or strf, or we can use varsubst.  The overall result is that
string handling is a bit more obscure than in bash.
Part of the reason for this is that we have two different ways we
can reference a string: either directly by a pointer, or indirectly
via another string name.  If we always reference by another string
name, then we will always incur a hash lookup.

srcdir = var(strappend(tops[i],"_src"));
srcdir = varf("%s_src", tops[i]);
SRCDIR = "${tops[i]}_src"
srcdir = var(S(tops[i],"_src"))

Another possibility is to link shell variables to C variables.
Not sure exactly how this would work, except that the C variable and shell
variable would have the same name.

 */
// Author: Michael Schmidt (michael@embeddedARM.com)
// Copyright (c) 2012, Technologic Systems, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
#endif
