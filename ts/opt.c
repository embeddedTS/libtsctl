#include <ctype.h>
#include <getopt.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "opt.h"

int (*OptionHostSocketCreate)(char *,int);
int OptionHostPortDefault;
// "<host:>port" tries to open a socket; descriptor goes in *target
// "<host> assumes port 7033 on the remote host
// "port" assumes localhost
// no option assumes localhost, port 7033
// port 7033 can be overridden
int OptionHost(char *arg,void *target0,int opt) {
  int *target = target0;
  char *sport, *host;
  int port;

  if (!arg || arg[0] == 0) {
    host = "127.0.0.1";
    port = OptionHostPortDefault;
  } else {
    sport = strchr(arg,':');
    if (sport) { // <host>:<port>
      *(sport++) = 0;
      host = arg;
      port = strtoul(sport, NULL, 0);
    } else if (!strchr(arg,'.') && (port = atoi(arg))) {
      host = "127.0.0.1";
    } else {
      host = arg;
      port = OptionHostPortDefault;
    }
  }
  if (OptionHostSocketCreate) {
    *target = OptionHostSocketCreate(host,port);
  } else {
    *target = -1;
  }
  if (*target < 0) {
    //fprintf(stderr,"create_client_socket(%s,%p):%m\n",host,port);
    return 0;
  }
  return 1;
}

int OptionString(char *arg,void *target0,int opt) {
  char **target = target0;
  *target = malloc(strlen(arg)+1);
  strcpy(*target,arg);
  return 1;
}

int OptionBoolean(char *arg,void *target0,int opt) {
  int *target = target0;
  *target = 1;
  return 1;
}

int OptionBoolean0(char *arg,void *target0,int opt) {
  int *target = target0;
  *target = 0;
  return 1;
}
			
int OptionUnsigned(char *arg,void *target0,int opt) {
  unsigned *target = target0;
  if (arg) {
    *target = strtoul(arg,NULL,0);
  } else {
    *target = 0xFFFFFFFF;
  }
  return 1;
}

int OptionSigned(char *arg,void *target0,int opt) {
  int *target = target0;
  if (arg) {
    *target = strtol(arg,NULL,0);
  } else {
    *target = 0xDEADBEEF;
  }
  return 1;
}

// replace the first occurence of <X> with X in str.
// if this character is upper-case, make it lower-case
static char *unaccelerate(const char *str) {
  char *ret,*str2 = malloc(strlen(str)+1);
  int found = 0;
  int i;

  ret = str2;
  while (*str) {
    if (found == 0 && *str == '<') {
      found = 1;
      str++;
    } else if (found == 1 && *str == '>') {
      found = 2;
      str++;
    } else {
      if (found != 1) {
	*(str2++) = *(str++);
      } else {
	*(str2++) = *(str++); // tolower(*(str++));
      }
    }
  }
  return ret;
}

// return X for the first occurence of <X> in str
// if there is none, return a special non-char value
static int accelerate(const char *str) {
  static int nonchar = 0x1000;

  while (*str && *str != '<') {
    str++;
  }
  if (*str == '<') {
    return *(str+1);
  } else {
    return nonchar++;
  }
}

int OptionsParse(int argc,char **argv,struct option2 *opts) {
  struct option *long_options;
  char *optstr,*helpstr;
  const char *prolog="",*epilog="";
  int i,n,j,c,total=0,gothelp=0;

  for (n=0;
       opts[n].has_arg||opts[n].f||opts[n].target;
       n++);
  if (opts[n].name) {
    prolog = opts[n].name;
  }
  if (opts[n].help) {
    epilog = opts[n].help;
  }
  long_options = malloc(sizeof(struct option) * (n+2));
  optstr = malloc(2+3*n);
  j=0;
  optstr[j] = 0;
  for (i=0;i<n;i++) {
    long_options[i].name = unaccelerate(opts[i].name);
    long_options[i].has_arg = opts[i].has_arg;
    long_options[i].flag = 0;
    long_options[i].val = accelerate(opts[i].name);
    if (long_options[i].val && long_options[i].val < 0xFF) {
      optstr[j++] = long_options[i].val;
      if (long_options[i].has_arg > 0) {
	optstr[j++] = ':';
      } 
      if (long_options[i].has_arg > 1) {
	optstr[j++] = ':';
      }
      optstr[j] = 0;
    }
  }
  long_options[i].name = "help";
  long_options[i].has_arg = 0;
  long_options[i].flag = 0;
  long_options[i].val = 0xFFF;
  long_options[i+1].name = 0;
  long_options[i+1].has_arg = 0;
  long_options[i+1].flag = 0;
  long_options[i+1].val = 0;
  optstr[j++] = 'h';
  optstr[j] = 0;

  while ((c = getopt_long(argc,argv,optstr,long_options,NULL)) != -1) {
    for (i=0;i<=n;i++) {
      if (c == long_options[i].val) {
	if (c == 0xFFF) {
	  gothelp = 1;
	  fprintf(stderr,"%s",prolog);
	  for (j=0;j<n;j++) {
	    if (opts[j].help) {
	      if (long_options[j].val < 0x100) {
		fprintf(stderr,"-%c | --%s%s%s\n",long_options[j].val,
			long_options[j].name, 
			(long_options[j].has_arg>0 ? "=" : " "),
			opts[j].help);
		/*
		  To do: if has_arg == 2, then the parameter is optional.
		  we should show that somehow.
		 */
	      } else {
		fprintf(stderr,"--%s  %s\n",long_options[j].name, opts[j].help);
	      }
	    }
	  }
	  fprintf(stderr,"%s",epilog);
	} else if (!++total || !opts[i].f(optarg,opts[i].target,c)) {
	  goto OptionsParseDone;
	}
      }
    }
  }
 OptionsParseDone:
  free(long_options);
  free(optstr);
  return (gothelp && total == 0) ? -1 : total;
}
// Author: Michael Schmidt (michael@embeddedARM.com)
// Copyright (c) 2011, Technologic Systems, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
