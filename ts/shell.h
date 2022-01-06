#include "Array.h"
#include <stdarg.h>

//char *strappend(char *str1,char *str2);
//char **strarrappend(char **arr,char *str);
//char *strsub(char *str1,int start,int end);
char *strf(char *format,...);
char *vstrf(char *format,va_list ap);
int strlookup(char **arr,char *str);

char *var(char *name);
char *varsubst(char *name);
char *assign(char *name,char *value);

void sourceline(char *line);

int len(char **in);
char **cat(char *filename);
void source(char *filename,char *prefix);
char **ls(const char *path,char *regex);
char **grep(char **in,char *regex,int match);
char **sort(char **in,int asc);
char **uniq(char **in);
char **map(char **in,char *(*f)(char *));
char **split(char *in,char sep);
char *join(char **in,char *sep);

char *cat1(char *filename);
char *pathbetween(char *dest,char *src);

int cp(char *dest,char *src);
int mv(char *dest,char *src);
int tarczf(char *dest,char *src,char *pattern);
int symlink1(char *dest,char *src);
int system1(char *cmd);

int grep1(char *str,char *regex);
int grep1s(char *str,char *regex);
#include <regex.h>
int grep1s_pre(char *str,regex_t preg);

extern char *nullstring;
extern int ShellDryRun,ShellVerbose;
// Author: Michael Schmidt (michael@embeddedTS.com)
// Copyright (c) 2012-2022 Technologic Systems, Inc. dba embeddedTS, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
