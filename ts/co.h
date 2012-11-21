#ifndef __COROUTINE_H
#define __COROUTINE_H
#include <stdlib.h>

#define LABEL2(x) label ## x
#define LABEL1(x) LABEL2(x)
#define HERE &&LABEL1(__LINE__); LABEL1(__LINE__):
#define CALL(x) last = &&LABEL1(__LINE__); goto x; LABEL1(__LINE__):
#define LABEL(x) LABEL1(x)

#define coParm         void **__context__
#define coBeginContext struct context { void *line
#define coEndContext   } *__ctx = *__context__
#define coBegin        if (!__ctx) {\
                         __ctx = *__context__ = malloc(sizeof(*__ctx));\
			 memset(__ctx,0,sizeof(*__ctx));\
                         __ctx->line = 0;\
                       }\
                       if (__ctx->line) goto *(__ctx->line);
#define coEnd          free(*__context__); *__context__=0
#define coReturn(z)   { coEnd; return (z); }
#define coYield(z)    { ((struct context *)*__context__)->line = &&LABEL(__LINE__); return (z); LABEL(__LINE__): ; }
#define co(x)          (__ctx->x)
#endif
/*
  Author: Michael Schmidt (michael@embeddedARM.com)
 */
