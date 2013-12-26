#ifndef __Array_h
#define __Array_h

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

#include <stdlib.h>
#include <string.h>

#if 1
void *ArrayAlloc(unsigned count,unsigned elementBytes) {
  unsigned *ptr = (unsigned *)malloc(elementBytes * (1+count) + 12);
  ptr[0] = 0;
  ptr[1] = elementBytes;
  ptr[2] = count;
  memset(&((char *)ptr)[12+count*ptr[1]],0,elementBytes);
  return &ptr[3];
}
#else
#define ArrayAlloc(count,elementBytes) ({ \
      unsigned *ptr = (unsigned *)malloc((elementBytes) * (1+(count)) + 12);	\
  ptr[0] = 0;\
  ptr[1] = elementBytes;\
  ptr[2] = count;\
  memset(&((char *)ptr)[12+(count)*ptr[1]],0,elementBytes);	\
  (void *)(&ptr[3]);					 \
    })
#endif

void ArrayFree(const void *arr) {
  unsigned *ptr = (unsigned *)arr;
  free(ptr-3);
}

#if 1
void *ArraySize(void *arr,unsigned count) {
  unsigned *ptr = (unsigned *)arr;
  ptr -= 3;
  ptr = (unsigned *)realloc(ptr,ptr[1] * (1+count) + 12);
  ptr[2] = count;
  memset(&((char *)ptr)[12+count*ptr[1]],0,ptr[1]);
  return &ptr[3];
}
#else
#define ArraySize(arr,count) ({ \
      unsigned *ptr = (unsigned *)(arr);	\
  void *ret;\
  ptr -= 3;\
  ptr = (unsigned *)realloc(ptr,ptr[1] * (1+(count)) + 12);	\
  ptr[2] = (count);					\
  memset(&((char *)ptr)[12+(count)*ptr[1]],0,ptr[1]);	\
  (void *)(&ptr[3]);				\
    })

void *ArraySize1(void *arr,unsigned count) {
  unsigned *ptr = (unsigned *)arr;
  ptr -= 3;
  ptr = (unsigned *)realloc(ptr,ptr[1] * (1+count) + 12);
  ptr[2] = count;
  memset(&((char *)ptr)[12+count*ptr[1]],0,ptr[1]);
  return &ptr[3];
}
void *ArraySize2(void *arr,unsigned count) {
  return ArraySize(arr,count);
}
#endif

char *ASCIIZ(const char *str) {
  unsigned len = strlen(str);
  char *str2 = (char *)ArrayAlloc(len,1);
  strncpy(str2,str,len);
  return str2;
}

void *ArraySizeAuto(void *arr,unsigned count) {
  unsigned *ptr = (unsigned *)arr;
  ptr -= 3;
  ptr[2] = count;
  return &ptr[3];
}

#define ArrayAutoOfSize(type,name,size)					\
  struct {								\
  unsigned c,bytes,len;							\
  type arr[size];							\
} TEMPLATE(name,_array) = {						\
    0, sizeof(type), size						\
}; \
type *name = TEMPLATE(name,_array).arr

    /* Ug. C++ does NOT like this
  .c = 0,								\
  .bytes = sizeof(type),						\
  .len = size								\
    */

#define ArrayAuto(type,name,value)					\
  struct {								\
  unsigned c,bytes,len;							\
  type arr[sizeof((type[])value)/sizeof((type[])value[0])];		\
} TEMPLATE(name,_array) = {						\
    0,sizeof(type),sizeof((type[])value)/sizeof((type[])value[0]),value	\
}; \
type* name = TEMPLATE(name,_array).arr

/*
  .c = 0,								\
  .bytes = sizeof(type),						\
  .len = sizeof((type[])value)/sizeof((type[])value[0]),		\
  .arr = value								\
 */

#define ArrayAuto0(type,name,value)					\
  struct {								\
  unsigned c,bytes,len;							\
  type arr[sizeof((type[])value)/sizeof((type[])value[0])];		\
} TEMPLATE(name,_array) = {						\
    0, 1, sizeof((type[])value)/sizeof((type[])value[0])-1, value	\
}; \
type* name = TEMPLATE(name,_array).arr

/*
  .c = 0,								\
  .bytes = 1, .len = sizeof((type[])value)/sizeof((type[])value[0])-1,	\
  .arr = value								\
 */

#define ArrayAutoASCIIZ(name) ArrayAuto0(char,TEMPLATE(s,name),ARR(#name))

#define ArrayL(name) TEMPLATE(name,_array).arr

// The following isn't reliable, because (apparently) the scope of
// a declaration in an expression is not defined.  As a result, this
// construct will work properly for some compilers, but not for others.
// It seems to work well enough in certain cases that we are leaving it
// in for now.
#define ASCIIZLocal(str) ({						\
    struct { unsigned c,bytes,len;					\
    char arr[sizeof(str)/sizeof(str[0])]; } tmplocal = {		\
      0,1, sizeof(str)/sizeof(str[0])-sizeof(str[0]), str		\
    }; tmplocal.arr; })

/*
      .c = 0,								\
      .bytes = 1, .len = sizeof(str)/sizeof(str[0])-sizeof(str[0]),	\
      .arr = str							\

 */  
//#define NullQ(type,ptr)
  
__attribute__((always_inline)) 
static inline unsigned _ArrayElementSize(const void *array) {
  const unsigned *ptr = (unsigned *)array;
  return ptr[-2];
}
unsigned ArrayElementSize(const void *array) {
  return _ArrayElementSize(array);
}
__attribute__((always_inline)) 
static inline unsigned _ArrayLength(const void *array) {
  const unsigned *ptr = (unsigned *)array;
  return ptr[-1];
}

unsigned ArrayLength(const void *array) {
  return _ArrayLength(array);
}

void ArrayFreeFree(const void *arr0) {
  const void * const *arr = (const void * const *)arr0;
  int i;
  for (i=0;i<_ArrayLength(arr);i++) {
    if (arr[i]) ArrayFree(arr[i]);
  }
  ArrayFree(arr);
}

void ArrayFreeFreeFree(const void *arr0) {
  const void ** const *arr = (const void ** const *)arr0;
  int i,j;
  for (i=0;i<_ArrayLength(arr);i++) {
    if (arr[i]) {
      for (j=0;j<_ArrayLength(arr[i]);j++) {
	if (arr[i][j]) ArrayFree(arr[i][j]);
      }
      ArrayFree(arr[i]);
    }
  }
  ArrayFree(arr);
}
__attribute__((always_inline)) 
static inline void *_ArrayCompareFunction(const void *array) {
  const unsigned *ptr = (const unsigned *)array;
  return (void *)ptr[-3];
}

void *ArrayCompareFunction(const void *array) {
  return ArrayCompareFunction(array);
}

__attribute__((always_inline)) 
static inline unsigned ArrayIndex(void *arr,int index) {
  if (index >= 0) {
    if (index > _ArrayLength(arr)) return _ArrayLength(arr)-1;
    return index;
  }
  index += _ArrayLength(arr);
  return (index < 0) ? 0 : index;
}

__attribute__((always_inline)) 
static inline void *ArrayDup(const void *arr) {
  unsigned *arr1 = (unsigned *)arr;
  unsigned *arr2 = (unsigned *)malloc(_ArrayElementSize(arr) * (1+_ArrayLength(arr)) + 12);
  memcpy(arr2,&arr1[-3],_ArrayElementSize(arr) * (1+_ArrayLength(arr)) + 12);
  return &arr2[3];
}
__attribute__((always_inline)) 
static inline void *ArrayJoin(void *arr1,void *arr2) {
  if (_ArrayElementSize(arr1) != _ArrayElementSize(arr2)) return 0;
  unsigned *ret = (unsigned *)malloc(_ArrayElementSize(arr1) * (1+_ArrayLength(arr1)) +
		      _ArrayElementSize(arr2) * _ArrayLength(arr2) + 12);
  ret[0] = 0;
  ret[1] = _ArrayElementSize(arr1);
  ret[2] = _ArrayLength(arr1) + _ArrayLength(arr2);
  memcpy(&ret[3],arr1,_ArrayElementSize(arr1) * _ArrayLength(arr1));
  memcpy(&((char *)ret)[12+_ArrayLength(arr1)*_ArrayElementSize(arr1)],arr2,
	 _ArrayElementSize(arr2) * _ArrayLength(arr2));
  memset(&((char *)ret)[12+_ArrayLength(arr1)*_ArrayElementSize(arr1)
			+_ArrayLength(arr2)*_ArrayElementSize(arr2)],0,
	 _ArrayElementSize(arr1));
  return &ret[3];
}

__attribute__((always_inline)) 
static inline void *ArrayAppend(void *arr1,void *arr2) {
  void *ret = ArrayJoin(arr1,arr2);
  ArrayFree(arr1);
  return ret;
}
__attribute__((always_inline)) 
static inline void *ArrayRange(void *arr,int index1,int index2) {
  unsigned start = ArrayIndex(arr,index1);
  unsigned end = ArrayIndex(arr,index2);
  unsigned *ret = (unsigned *)malloc(_ArrayElementSize(arr) * (end-start+2) + 12);
  char *_arr = (char *)arr;
  ret[0] = (int)_ArrayCompareFunction(arr);
  ret[1] = _ArrayElementSize(arr);
  ret[2] = (end-start+1);
  memcpy(&ret[3],&_arr[start*_ArrayElementSize(arr)],
	 _ArrayElementSize(arr) * (end-start+1));
  memset(&((char *)ret)[12+ret[2]*_ArrayElementSize(arr)],
	 0,_ArrayElementSize(arr));
  return &ret[3];
}
__attribute__((always_inline)) 
static inline int ArrayCompare(const void *arr1,const void *arr2) {
  //if (_ArrayElementSize(arr1) < _ArrayElementSize(arr2)) return -1;
  int ret = memcmp(arr1,arr2,_ArrayElementSize(arr1)*_ArrayLength(arr1));
  if (ret == 0 && (_ArrayLength(arr1) != _ArrayLength(arr2))) {
    return (_ArrayLength(arr1) > _ArrayLength(arr2)) ? 1 : -1;
  } else {
    return ret;
  }
}
__attribute__((always_inline)) 
static inline int ArrayCompare1(const void *arr1,const void *arr2) {
  //if (_ArrayElementSize(arr1) != _ArrayElementSize(arr2)) return 0;
  //if (_ArrayLength(arr2) < _ArrayLength(arr1)) return 0;
  return memcmp(arr1,arr2,_ArrayElementSize(arr1)*_ArrayLength(arr1));
}

__attribute__((always_inline)) 
static inline void *ArrayElemPtr(void *arr,unsigned ind) {
  return ((char *)arr)+ind*_ArrayElementSize(arr);
}

__attribute__((always_inline)) 
static inline void *ArrayAfter(void *arr,unsigned index,const void *value) {
    int ind = (_ArrayLength(arr) == 0) ? -1 : ArrayIndex(arr,index);
    arr = ArraySize(arr,_ArrayLength(arr)+1);
    memmove(ArrayElemPtr(arr,ind+2),ArrayElemPtr(arr,ind+1),
	    _ArrayElementSize(arr)*(_ArrayLength(arr)-ind-1));
    memmove(ArrayElemPtr(arr,ind+1),value,_ArrayElementSize(arr));
    return arr;
}

__attribute__((always_inline)) 
static inline void *ArrayBefore(void *arr,unsigned index,const void *value) {
    unsigned ind = ArrayIndex(arr,index);
    arr = ArraySize(arr,_ArrayLength(arr)+1);
    memmove(ArrayElemPtr(arr,ind+1),ArrayElemPtr(arr,ind),
	    _ArrayElementSize(arr)*(_ArrayLength(arr)-ind-1));
    memmove(ArrayElemPtr(arr,ind),value,_ArrayElementSize(arr));
    return arr;
}

__attribute__((always_inline)) 
static inline void *ArrayQueue(void *arr,const void *value) {
  return ArrayAfter(arr,-1,value);
}
__attribute__((always_inline)) 
static inline void *ArrayPush(void *arr,const void *value) {
  return ArrayBefore(arr,0,value);
}

__attribute__((always_inline)) 
static inline void *ArrayDelete(void *arr,int index,unsigned len) {
  unsigned start = ArrayIndex(arr,index);
  if (start + len > _ArrayLength(arr)
      || start + len < start) len = _ArrayLength(arr) - start;
  memmove(((char *)arr)+start*_ArrayElementSize(arr),
	  ((char *)arr)+(start+len)*_ArrayElementSize(arr),
	  _ArrayElementSize(arr)*(_ArrayLength(arr)-start-len+1));
  return ArraySize(arr,_ArrayLength(arr)-len);
}

__attribute__((always_inline)) 
static inline void *ArrayPop(void *arr,void *value) {
  memmove(value,ArrayElemPtr(arr,0),_ArrayElementSize(arr));
  return ArrayDelete(arr,0,1);
}

__attribute__((always_inline)) 
static inline void *ArrayPull(void *arr,void *value) {
  memmove(value,ArrayElemPtr(arr,ArrayIndex(arr,-1)),_ArrayElementSize(arr));
  return ArrayDelete(arr,-1,1);
}

__attribute__((always_inline)) 
static inline void ArrayPeek(void *arr,void *value,int index) {
  memmove(value,ArrayElemPtr(arr,ArrayIndex(arr,index)),_ArrayElementSize(arr));
}
__attribute__((always_inline)) 
static inline void ArrayPoke(void *arr,const void *value,int index) {
  memmove(ArrayElemPtr(arr,ArrayIndex(arr,index)),value,_ArrayElementSize(arr));
}

__attribute__((always_inline)) 
static inline void ArraySort(void *arr,int (*Compare)(const void *,const void *)) {
  unsigned *ptr = (unsigned *)arr;
  ptr[-3] = (unsigned)Compare;
  if (Compare) {
    qsort(arr,_ArrayLength(arr),_ArrayElementSize(arr),Compare);
  }
}

// returns the index in the array to insert the value before in order for
// the array to remain sorted.
// to test if the specified value was found, compare it against the
// element at this index.
__attribute__((always_inline)) 
static inline unsigned ArrayFind(void *arr,const void *value) {
  int (*Compare)(const void *,const void *) = (int (*)(const void *,const void *))_ArrayCompareFunction(arr);
  if (Compare) {
    unsigned mid,low=0,high=_ArrayLength(arr);

    if (!arr) return 0;
    while (low < high) {
      mid = low + ((high - low) / 2);
      if (Compare(((char *)arr)+mid*_ArrayElementSize(arr),value) < 0) {
	low = mid + 1;
      } else {
	high = mid;
      }
    }
    return low;
  } else {
    return -1;
  }
}

__attribute__((always_inline)) 
static inline void *ArrayFindEq(void *arr,const void *value) {
  unsigned index = ArrayFind(arr,value);
  return ArrayCompare(ArrayElemPtr(arr,index),value)?0:ArrayElemPtr(arr,index);
}

__attribute__((always_inline)) 
static inline unsigned ArrayFindWith(void *arr,const void *value,
		       int (*Compare)(const void *,const void *)) {
  unsigned mid,low=0,high=_ArrayLength(arr);

  if (!arr) return 0;
  while (low < high) {
    mid = low + ((high - low) / 2);
    if (Compare(((char *)arr)+mid*_ArrayElementSize(arr),value) < 0) {
      low = mid + 1;
    } else {
      high = mid;
    }
  }
  return low;
}

__attribute__((always_inline)) 
static inline void *ArrayInsert(void *arr,const void *value) {
  int (*Compare)(const void *,const void *) = (int (*)(const void *,const void *))_ArrayCompareFunction(arr);
    if (Compare) {
      unsigned index = ArrayFind(arr,value);
      arr = ArrayBefore(arr,index,value);
    }
    return arr;
}

__attribute__((always_inline)) 
static inline void *ArrayReplace(void *arr,const void *value) {
    int (*Compare)(const void *,const void *) = (int (*)(const void *,const void *))_ArrayCompareFunction(arr);
    if (Compare) {
      unsigned index = ArrayFind(arr,value);
      if (index >= _ArrayLength(arr)
	  || Compare(ArrayElemPtr(arr,index),value)) {
	arr = ArrayBefore(arr,index,value);
      } else {
	memmove(ArrayElemPtr(arr,index),value,_ArrayElementSize(arr));
      }
    }
    return arr;
}

__attribute__((always_inline)) 
static inline void *ArrayReplaceWith(void *arr,const void *value,    
		   int (*Compare)(const void *,const void *)) {
  unsigned index = ArrayFind(arr,value);
  if (index >= _ArrayLength(arr)
      || Compare(ArrayElemPtr(arr,index),value)) {
    arr = ArrayBefore(arr,index,value);
  } else {
    memmove(ArrayElemPtr(arr,index),value,_ArrayElementSize(arr));
  }
  return arr;
}

__attribute__((always_inline)) 
static inline void *ArrayFindDelete(void *arr,void *value) {
    int (*Compare)(const void *,const void *) = (int (*)(const void *,const void *))_ArrayCompareFunction(arr);
    if (Compare) {
      unsigned index = ArrayFind(arr,value);
      if (index >= _ArrayLength(arr) 
	  || Compare(ArrayElemPtr(arr,index),value)) {
      } else {
	arr=ArrayDelete(arr,index,1);
      }
    }
    return arr;
}

#ifdef __cplusplus
#define A(type,x) (&(const type &)(type)x)
#define Of(...) { __VA_ARGS__ }
#else
#define A(type,x) (&(type){x})
#define Of(...) __VA_ARGS__
#endif
#define ARR(...) {__VA_ARGS__ }
#endif
