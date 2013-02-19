#ifndef __Array_h
#define __Array_h
#include "cpp.h"
#include <stdlib.h>
#include <string.h>

#if 1
__attribute__((always_inline)) 
static inline void *ArrayAlloc(unsigned count,unsigned elementBytes) {
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

__attribute__((always_inline)) 
static inline void ArrayFree(const void *arr) {
  unsigned *ptr = (unsigned *)arr;
  free(ptr-3);
}

#if 1
__attribute__((always_inline)) 
static inline void *ArraySize(void *arr,unsigned count) {
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

__attribute__((always_inline)) 
static inline char *ASCIIZ(const char *str) {
  unsigned len = strlen(str);
  char *str2 = (char *)ArrayAlloc(len,1);
  strncpy(str2,str,len);
  return str2;
}

__attribute__((always_inline)) 
static inline void *ArraySizeAuto(void *arr,unsigned count) {
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
static inline unsigned ArrayElementSize(const void *array) {
  const unsigned *ptr = (unsigned *)array;
  return ptr[-2];
}
__attribute__((always_inline)) 
static inline unsigned ArrayLength(const void *array) {
  const unsigned *ptr = (unsigned *)array;
  return ptr[-1];
}
__attribute__((always_inline)) 
static inline void ArrayFreeFree(const void *arr0) {
  const void * const *arr = (const void * const *)arr0;
  int i;
  for (i=0;i<ArrayLength(arr);i++) {
    if (arr[i]) ArrayFree(arr[i]);
  }
  ArrayFree(arr);
}
__attribute__((always_inline)) 
static inline void ArrayFreeFreeFree(const void *arr0) {
  const void ** const *arr = (const void ** const *)arr0;
  int i,j;
  for (i=0;i<ArrayLength(arr);i++) {
    if (arr[i]) {
      for (j=0;j<ArrayLength(arr[i]);j++) {
	if (arr[i][j]) ArrayFree(arr[i][j]);
      }
      ArrayFree(arr[i]);
    }
  }
  ArrayFree(arr);
}
__attribute__((always_inline)) 
static inline void *ArrayCompareFunction(const void *array) {
  const unsigned *ptr = (const unsigned *)array;
  return (void *)ptr[-3];
}

__attribute__((always_inline)) 
static inline unsigned ArrayIndex(void *arr,int index) {
  if (index >= 0) {
    if (index > ArrayLength(arr)) return ArrayLength(arr)-1;
    return index;
  }
  index += ArrayLength(arr);
  return (index < 0) ? 0 : index;
}

__attribute__((always_inline)) 
static inline void *ArrayDup(const void *arr) {
  unsigned *arr1 = (unsigned *)arr;
  unsigned *arr2 = (unsigned *)malloc(ArrayElementSize(arr) * (1+ArrayLength(arr)) + 12);
  memcpy(arr2,&arr1[-3],ArrayElementSize(arr) * (1+ArrayLength(arr)) + 12);
  return &arr2[3];
}
__attribute__((always_inline)) 
static inline void *ArrayJoin(void *arr1,void *arr2) {
  if (ArrayElementSize(arr1) != ArrayElementSize(arr2)) return 0;
  unsigned *ret = (unsigned *)malloc(ArrayElementSize(arr1) * (1+ArrayLength(arr1)) +
		      ArrayElementSize(arr2) * ArrayLength(arr2) + 12);
  ret[0] = 0;
  ret[1] = ArrayElementSize(arr1);
  ret[2] = ArrayLength(arr1) + ArrayLength(arr2);
  memcpy(&ret[3],arr1,ArrayElementSize(arr1) * ArrayLength(arr1));
  memcpy(&((char *)ret)[12+ArrayLength(arr1)*ArrayElementSize(arr1)],arr2,
	 ArrayElementSize(arr2) * ArrayLength(arr2));
  memset(&((char *)ret)[12+ArrayLength(arr1)*ArrayElementSize(arr1)
			+ArrayLength(arr2)*ArrayElementSize(arr2)],0,
	 ArrayElementSize(arr1));
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
  unsigned *ret = (unsigned *)malloc(ArrayElementSize(arr) * (end-start+2) + 12);
  char *_arr = (char *)arr;
  ret[0] = (int)ArrayCompareFunction(arr);
  ret[1] = ArrayElementSize(arr);
  ret[2] = (end-start+1);
  memcpy(&ret[3],&_arr[start*ArrayElementSize(arr)],
	 ArrayElementSize(arr) * (end-start+1));
  memset(&((char *)ret)[12+ret[2]*ArrayElementSize(arr)],
	 0,ArrayElementSize(arr));
  return &ret[3];
}
__attribute__((always_inline)) 
static inline int ArrayCompare(const void *arr1,const void *arr2) {
  //if (ArrayElementSize(arr1) < ArrayElementSize(arr2)) return -1;
  int ret = memcmp(arr1,arr2,ArrayElementSize(arr1)*ArrayLength(arr1));
  if (ret == 0 && (ArrayLength(arr1) != ArrayLength(arr2))) {
    return (ArrayLength(arr1) > ArrayLength(arr2)) ? 1 : -1;
  } else {
    return ret;
  }
}
__attribute__((always_inline)) 
static inline int ArrayCompare1(const void *arr1,const void *arr2) {
  //if (ArrayElementSize(arr1) != ArrayElementSize(arr2)) return 0;
  //if (ArrayLength(arr2) < ArrayLength(arr1)) return 0;
  return memcmp(arr1,arr2,ArrayElementSize(arr1)*ArrayLength(arr1));
}

__attribute__((always_inline)) 
static inline void *ArrayElemPtr(void *arr,unsigned ind) {
  return ((char *)arr)+ind*ArrayElementSize(arr);
}

__attribute__((always_inline)) 
static inline void *ArrayAfter(void *arr,unsigned index,const void *value) {
    int ind = (ArrayLength(arr) == 0) ? -1 : ArrayIndex(arr,index);
    arr = ArraySize(arr,ArrayLength(arr)+1);
    memmove(ArrayElemPtr(arr,ind+2),ArrayElemPtr(arr,ind+1),
	    ArrayElementSize(arr)*(ArrayLength(arr)-ind-1));
    memmove(ArrayElemPtr(arr,ind+1),value,ArrayElementSize(arr));
    return arr;
}

__attribute__((always_inline)) 
static inline void *ArrayBefore(void *arr,unsigned index,const void *value) {
    unsigned ind = ArrayIndex(arr,index);
    arr = ArraySize(arr,ArrayLength(arr)+1);
    memmove(ArrayElemPtr(arr,ind+1),ArrayElemPtr(arr,ind),
	    ArrayElementSize(arr)*(ArrayLength(arr)-ind-1));
    memmove(ArrayElemPtr(arr,ind),value,ArrayElementSize(arr));
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
  if (start + len > ArrayLength(arr)
      || start + len < start) len = ArrayLength(arr) - start;
  memmove(((char *)arr)+start*ArrayElementSize(arr),
	  ((char *)arr)+(start+len)*ArrayElementSize(arr),
	  ArrayElementSize(arr)*(ArrayLength(arr)-start-len+1));
  return ArraySize(arr,ArrayLength(arr)-len);
}

__attribute__((always_inline)) 
static inline void *ArrayPop(void *arr,void *value) {
  memmove(value,ArrayElemPtr(arr,0),ArrayElementSize(arr));
  return ArrayDelete(arr,0,1);
}

__attribute__((always_inline)) 
static inline void *ArrayPull(void *arr,void *value) {
  memmove(value,ArrayElemPtr(arr,ArrayIndex(arr,-1)),ArrayElementSize(arr));
  return ArrayDelete(arr,-1,1);
}

__attribute__((always_inline)) 
static inline void ArrayPeek(void *arr,void *value,int index) {
  memmove(value,ArrayElemPtr(arr,ArrayIndex(arr,index)),ArrayElementSize(arr));
}
__attribute__((always_inline)) 
static inline void ArrayPoke(void *arr,const void *value,int index) {
  memmove(ArrayElemPtr(arr,ArrayIndex(arr,index)),value,ArrayElementSize(arr));
}

__attribute__((always_inline)) 
static inline void ArraySort(void *arr,int (*Compare)(const void *,const void *)) {
  unsigned *ptr = (unsigned *)arr;
  ptr[-3] = (unsigned)Compare;
  if (Compare) {
    qsort(arr,ArrayLength(arr),ArrayElementSize(arr),Compare);
  }
}

// returns the index in the array to insert the value before in order for
// the array to remain sorted.
// to test if the specified value was found, compare it against the
// element at this index.
__attribute__((always_inline)) 
static inline unsigned ArrayFind(void *arr,const void *value) {
  int (*Compare)(const void *,const void *) = (int (*)(const void *,const void *))ArrayCompareFunction(arr);
  if (Compare) {
    unsigned mid,low=0,high=ArrayLength(arr);

    if (!arr) return 0;
    while (low < high) {
      mid = low + ((high - low) / 2);
      if (Compare(((char *)arr)+mid*ArrayElementSize(arr),value) < 0) {
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
  unsigned mid,low=0,high=ArrayLength(arr);

  if (!arr) return 0;
  while (low < high) {
    mid = low + ((high - low) / 2);
    if (Compare(((char *)arr)+mid*ArrayElementSize(arr),value) < 0) {
      low = mid + 1;
    } else {
      high = mid;
    }
  }
  return low;
}

__attribute__((always_inline)) 
static inline void *ArrayInsert(void *arr,const void *value) {
  int (*Compare)(const void *,const void *) = (int (*)(const void *,const void *))ArrayCompareFunction(arr);
    if (Compare) {
      unsigned index = ArrayFind(arr,value);
      arr = ArrayBefore(arr,index,value);
    }
    return arr;
}

__attribute__((always_inline)) 
static inline void *ArrayReplace(void *arr,const void *value) {
    int (*Compare)(const void *,const void *) = (int (*)(const void *,const void *))ArrayCompareFunction(arr);
    if (Compare) {
      unsigned index = ArrayFind(arr,value);
      if (index >= ArrayLength(arr)
	  || Compare(ArrayElemPtr(arr,index),value)) {
	arr = ArrayBefore(arr,index,value);
      } else {
	memmove(ArrayElemPtr(arr,index),value,ArrayElementSize(arr));
      }
    }
    return arr;
}

__attribute__((always_inline)) 
static inline void *ArrayReplaceWith(void *arr,const void *value,    
		   int (*Compare)(const void *,const void *)) {
  unsigned index = ArrayFind(arr,value);
  if (index >= ArrayLength(arr)
      || Compare(ArrayElemPtr(arr,index),value)) {
    arr = ArrayBefore(arr,index,value);
  } else {
    memmove(ArrayElemPtr(arr,index),value,ArrayElementSize(arr));
  }
  return arr;
}

__attribute__((always_inline)) 
static inline void *ArrayFindDelete(void *arr,void *value) {
    int (*Compare)(const void *,const void *) = (int (*)(const void *,const void *))ArrayCompareFunction(arr);
    if (Compare) {
      unsigned index = ArrayFind(arr,value);
      if (index >= ArrayLength(arr) 
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
