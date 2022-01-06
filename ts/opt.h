#ifndef __OPT_H
#define __OPT_H
#include <unistd.h>

typedef int (*OptionFunction)(char *arg,void *target,int opt);

struct option2 {
  int has_arg;
  OptionFunction f;
  void *target;
  const char *name;
  const char *help;
};

extern int (*OptionHostSocketCreate)(char *,int);
extern int OptionHostPortDefault;

int OptionHost(char *arg,void *target0,int opt); // int *target
int OptionString(char *arg,void *target,int opt); // char **target
int OptionBoolean(char *arg,void *target0,int opt); // int *target
int OptionBoolean0(char *arg,void *target0,int opt); // int *target
int OptionUnsigned(char *arg,void *target0,int opt); // unsigned *target
int OptionSigned(char *arg,void *target0,int opt);

int OptionsParse(int argc,char **argv,struct option2 *opts);
#endif
// Author: Michael Schmidt (michael@embeddedTS.com)
// Copyright (c) 2011-2022 Technologic Systems, Inc. dba embeddedTS, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
