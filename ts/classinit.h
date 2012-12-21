#include "cpp.h"

CLASS *TEMPLATE(CLASS,Init)(int inst) {
  LogEnter("%d",inst);
  ArchInfo *cur,*par=0;
  ArchInfo* *parenta = ArrayAlloc(0,sizeof(ArchInfo *));
  int *parenti = ArrayAlloc(0,sizeof(int));
  int instances,ind=0,archexists;
  CLASS *ret,*ret1;
  ArchInit();
  if (inst < 0) {
    ArrayFree(parenta);
    ArrayFree(parenti);
    return 0;
  }

  parenta = ArrayQueue(parenta,A(ArchInfo *,&TS_ArchInfo));
  parenti = ArrayQueue(parenti,A(int,0));
  cur = aArchTypeCPU[0];

  ArchInfo *first_child() {
    parenta = ArrayQueue(parenta,&cur);
    parenti = ArrayQueue(parenti,&ind);
    ind = 0;
    Log(-1,"first_child=%s",cur->subarches[0]->name);
    return cur->subarches[0];  
  }

  ArchInfo *next_sibling() {
    if (ArrayLength(parenta) == 0) return 0;
    ++ind;
    ArchInfo* parent;
    ArrayPeek(parenta,&parent,-1);
    if (ind >= ArrayLength(parent->subarches)) {
      Log(-1,"next_sibling=0 (ind=%d,len=%d)",ind,ArrayLength(parent->subarches));
      return 0;
    }
    Log(-1,"next_sibling=%s",parent->subarches[ind]->name,ind);
    return parent->subarches[ind];
  }

  ArchInfo *parent() {
    if (ArrayLength(parenta) > 0) {
      ArchInfo *ret;
      parenta = ArrayPull(parenta,&ret);
      parenti = ArrayPull(parenti,&ind);
      Log(-1,"parent=%p @ %d, %d remain",ret,ind,ArrayLength(parenta));
      Log(-1,"parent=%s @ %d",ret->name,ind);
      return ret;
    } else {
      Log(-1,"parent=0");
      return 0;
    }
  }

  while (cur) {
    //printf("arch %s parent = %s\n",cur->name,par?par->name:"");
    cur->parent = par;
    archexists = cur->ArchInit();
    instances = archexists ? cur->Instances[TEMPLATE(Class,CLASS)] : 0;
    if (instances != 0 && inst < instances) {
      Log(-1,"Init inst %d of %s",inst,cur->name);
      ret = cur->TEMPLATE(CLASS,Init)(0,inst);
#ifdef CLASS_OVERRIDE
      // now allow for overrides
      int i;
      for (i=0;i<ArrayLength(cur->subarches);i++) {
	//printf("subarch %s parent = %s\n",cur->subarches[i]->name,par?par->name:"");
	cur->subarches[i]->parent = cur;
	ret1 = cur->subarches[i]->ArchInit() ? 
	  cur->subarches[i]->TEMPLATE(CLASS,Init)(ret,-inst-1) : 0;
	//printf("debug %s:%d:%s:%p\n",STRINGIFY(CLASS),i,cur->subarches[i]->name,ret1);
	if (ret1) ret = ret1;
      }
#undef CLASS_OVERRIDE
#endif
      ArrayFree(parenta);
      ArrayFree(parenti);
      LogReturn("%p",ret);
    } else {
      inst -= instances;
      if (/*instances != 0*/ archexists && ArrayLength(cur->subarches) > 0) {
	par = cur;
	cur = first_child();
      } else if (!(cur = next_sibling())) {
	cur = parent();
	if (ArrayLength(parenta) > 0) ArrayPeek(parenta,&par,-1); else par=0;
	if (cur) cur = next_sibling();
      }
    }
  }
  ArrayFree(parenta);
  ArrayFree(parenti);
  LogReturn("%p",0);
}

#if 0
// Note: The initial call to any Init function is not thread-safe
// For this reason, we should probably pre-compute the number of
// instances of each class during this initial call, otherwise it
// will not be thread-safe to call an Init function ever, so long as
// it is possible for inTestInit to be true.
CLASS *TEMPLATE(CLASS,Init)(int inst) {
  ArchInit();
  return ArchFirst->TEMPLATE(CLASS,Init)(0,inst);
}

CLASS *TEMPLATE(CLASS,InitOld)(int inst) {
  ArchInfo *arch = ArchFirst;
  int i = 0,n = 0,inst0 = inst;
  CLASS *ret = 0;

  ArchInit();
  while (arch) {
    int q = TEMPLATE(Class,CLASS);
    if (inst < arch->Instances[TEMPLATE(Class,CLASS)]) break;
    inst -= arch->Instances[TEMPLATE(Class,CLASS)];
    arch = arch->next;
  }
  if (!arch) return 0;
  // now initialize
  ret = arch->TEMPLATE(CLASS,Init)(0,inst);
  // next, pass the returned object to each sub-arch to give it a chance
  // to override it
  arch = arch->next;
  while (arch) {
    ret = arch->TEMPLATE(CLASS,Init)(ret,-1-inst);
    arch = arch->next;
  }
  return ret;
}
#endif

#undef CLASS
