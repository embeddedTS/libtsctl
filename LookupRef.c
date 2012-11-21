#include "ts/Array.h"
#include "LookupRef.h"

int LookupRefCompare(const void *a,const void *b) {
  const LookupRef *r1 = a, *r2 = b;
  return ArrayCompare(r1->name,r2->name);
}

LookupRef* LookupRefNew() {
  LookupRef* ret = ArrayAlloc(0,sizeof(LookupRef));
  ArraySort(ret,LookupRefCompare);
  return ret;
}

void LookupRefOld(LookupRef* lu) {
  int i;

  for (i=0;i<ArrayLength(lu);i++) {
    ArrayFree(lu[i].offset);
  }
  ArrayFree(lu);
}

LookupRef *LookupRefName(LookupRef* *lu,char* name) {
  LookupRef ref;
  ref.name = name;
  if (ArrayLength(*lu) > 0) {
    unsigned index = ArrayFind(*lu,&ref);
    if (index < ArrayLength(*lu) && !LookupRefCompare(*lu+index,&ref)) {
      return *lu + index;
    }
  }
  ref.offset = ArrayAlloc(0,sizeof(int));
  *lu = ArrayInsert(*lu,&ref);
  return &lu[0][ArrayFind(*lu,&ref)];
}


