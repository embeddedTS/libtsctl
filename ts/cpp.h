#ifndef __cpp_h
#define __cpp_h
#define TOKENIZE(a,b) a##b
#define TOKENIZE2(a,b,c) a##b##c
#define TOKENIZE3(a,b,c,d) a##b##c##d
#define TEMPLATE(a,b) TOKENIZE(a,b)
#define TEMPLATE2(a,b,c) TOKENIZE2(a,b,c)
#define TEMPLATE3(a,b,c,d) TOKENIZE3(a,b,c,d)

#define COMMA_TOKENIZE(a,b) , a##b
#define COMMA_TEMPLATE(a,b) COMMA_TOKENIZE(a,b)

#define STRINGIFY(s) STRINGIFY0(s)
#define STRINGIFY0(s) #s

#define ARGS(...) __VA_ARGS__
#endif
