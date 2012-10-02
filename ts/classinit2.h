CLASS *(*TEMPLATE3(ARCH,__,CLASS,Init)[1+TEMPLATE2(ARCH,CLASS,Instances)])(CLASS *,int) = {
#if TEMPLATE2(ARCH,CLASS,Instances) > 0
  TEMPLATE3(ARCH,__,CLASS,Init0),
#endif
#if TEMPLATE2(ARCH,CLASS,Instances) > 1
  TEMPLATE3(ARCH,__,CLASS,Init1),
#endif
#if TEMPLATE2(ARCH,CLASS,Instances) > 2
  TEMPLATE3(ARCH,__,CLASS,Init2),
#endif
#if TEMPLATE2(ARCH,CLASS,Instances) > 3
  TEMPLATE3(ARCH,__,CLASS,Init3),
#endif
#if TEMPLATE2(ARCH,CLASS,Instances) > 4
  TEMPLATE3(ARCH,__,CLASS,Init4),
#endif
#if TEMPLATE2(ARCH,CLASS,Instances) > 5
  TEMPLATE3(ARCH,__,CLASS,Init5),
#endif
#if TEMPLATE2(ARCH,CLASS,Instances) > 6
  TEMPLATE3(ARCH,__,CLASS,Init6),
#endif
#if TEMPLATE2(ARCH,CLASS,Instances) > 7
  TEMPLATE3(ARCH,__,CLASS,Init7),
#endif
#if TEMPLATE2(ARCH,CLASS,Instances) > 8
  TEMPLATE3(ARCH,__,CLASS,Init8),
#endif
#if TEMPLATE2(ARCH,CLASS,Instances) > 9
  TEMPLATE3(ARCH,__,CLASS,Init9),
#endif
#if TEMPLATE2(ARCH,CLASS,Instances) > 10
  TEMPLATE3(ARCH,__,CLASS,Init10),
#endif
#if TEMPLATE2(ARCH,CLASS,Instances) > 11
  TEMPLATE3(ARCH,__,CLASS,Init11),
#endif
#if TEMPLATE2(ARCH,CLASS,Instances) > 12
  TEMPLATE3(ARCH,__,CLASS,Init12),
#endif
#if TEMPLATE2(ARCH,CLASS,Instances) > 13
  TEMPLATE3(ARCH,__,CLASS,Init13),
#endif
#if TEMPLATE2(ARCH,CLASS,Instances) > 14
  TEMPLATE3(ARCH,__,CLASS,Init14),
#endif
#if TEMPLATE2(ARCH,CLASS,Instances) > 15
  TEMPLATE3(ARCH,__,CLASS,Init15),
#endif
#if TEMPLATE2(ARCH,CLASS,Instances) > 16
  TEMPLATE3(ARCH,__,CLASS,Init16),
#endif
#if TEMPLATE2(ARCH,CLASS,Instances) > 17
  TEMPLATE3(ARCH,__,CLASS,Init17),
#endif
#if TEMPLATE2(ARCH,CLASS,Instances) > 18
  TEMPLATE3(ARCH,__,CLASS,Init18),
#endif
#if TEMPLATE2(ARCH,CLASS,Instances) > 19
  TEMPLATE3(ARCH,__,CLASS,Init19),
#endif
#if TEMPLATE2(ARCH,CLASS,Instances) > 20
  TEMPLATE3(ARCH,__,CLASS,Init20),
#endif
#if TEMPLATE2(ARCH,CLASS,Instances) > 21
  TEMPLATE3(ARCH,__,CLASS,Init21),
#endif
#if TEMPLATE2(ARCH,CLASS,Instances) > 22
  TEMPLATE3(ARCH,__,CLASS,Init22),
#endif
#if TEMPLATE2(ARCH,CLASS,Instances) > 23
  TEMPLATE3(ARCH,__,CLASS,Init23),
#endif
#if TEMPLATE2(ARCH,CLASS,Instances) > 24
  TEMPLATE3(ARCH,__,CLASS,Init24),
#endif
#if TEMPLATE2(ARCH,CLASS,Instances) > 25
  TEMPLATE3(ARCH,__,CLASS,Init25),
#endif
#if TEMPLATE2(ARCH,CLASS,Instances) > 26
  TEMPLATE3(ARCH,__,CLASS,Init26),
#endif
#if TEMPLATE2(ARCH,CLASS,Instances) > 27
  TEMPLATE3(ARCH,__,CLASS,Init27),
#endif
#if TEMPLATE2(ARCH,CLASS,Instances) > 28
  TEMPLATE3(ARCH,__,CLASS,Init28),
#endif
#if TEMPLATE2(ARCH,CLASS,Instances) > 29
  TEMPLATE3(ARCH,__,CLASS,Init29),
#endif

  0
};

#if 0
extern ArchInfo ts4700_ArchInfo;
extern ArchInfo ts81x0_ArchInfo;
extern ArchInfo ts8900_ArchInfo;
extern ArchInfo tsRelay8_ArchInfo;
extern ArchInfo tsDIO24_ArchInfo;

ArrayAuto(ArchInfo*,aArchTypeTSSocketBB,ARR(&ts81x0_ArchInfo,&ts8900_ArchInfo));
ArrayAuto(ArchInfo*,aArchTypePC104,ARR(&tsRelay8_ArchInfo,&tsDIO24_ArchInfo));

extern ArchInfo *archesBaseBoard;
extern ArchInfo *archesPC104;


ArchInfo ts4700_ArchInfo = {
  // ...
  .subarches = archesBaseBoard,
};

extern ArchInfo TEMPLATE(ARCH,_ArchInfo);

// New e.g. ts4700_DIOInit(ob,inst)
CLASS *TEMPLATE3(ARCH,_,CLASS,Init)(CLASS *ob,int inst) {
  LogEnter("%p,%d",ob,inst);
  if (!TEMPLATE(ARCH,_ArchInit)()) LogReturn("%d",0);
  int index = inst >= 0 ? inst : -inst-1;
  CLASS *ret = ob,*ret1;
  ArchInfo *next,*me = &TEMPLATE(ARCH,_ArchInfo);

  next = me->next;

  // we can assume that we don't have a large architectural tree.
  // specifically, it will be a single chain of architectures, except
  // possibly for the last level, which may have multiple architectures.
  // an example of this is the TS-SOCKET board, which can have at most
  // one defined sub-arch, the socket base board, which in turn can have
  // at most one sub-arch, the PC-104 bus, which can have as terminal
  // arches one or more sub-arch.

  // therefore, it doesn't matter if we do depth first or breadth first
  // search.  in order to break the above assumption we would have to
  // have the actual tree representation of our architecture anyway.

  // would it be simpler to hold our representation as a tree?
  // at the moment we use a tricky include mechanism to define our architecture.
  // if, instead of this, we had a fixed structure referring to the
  // tree structure of our architectures, then we might have to manually
  // include all of them, but we would only do it once.
  while (next && next->type != me->type 
	 && !TEMPLATE(ARCH,_isSubArch)(next->type)) next = next->next;
  if (inst >= 0 && inst >= TEMPLATE2(ARCH,CLASS,Instances)) {
    ret = next ? 
      next->TEMPLATE(CLASS,Init)(ret,inst-TEMPLATE2(ARCH,CLASS,Instances)) : 0;
    LogReturn("%p",ret);
  } else {
    // specified instance is in this object. initialize it, then give
    // each sub-architecture a change to override it by passing the current
    // object to it, and if it returns non-null, changing our current object
    // to the returned object.
    ret = TEMPLATE3(ARCH,__,CLASS,Init)[index](ret,inst);
    while (1) {
      while (next && !TEMPLATE(ARCH,_isSubArch)(next->type)) next = next->next;
      if (!next) LogReturn("%p",ret);
      ret1 = next->TEMPLATE(CLASS,Init)(ret,-inst-1);
      if (ret1) ret = ret1;
    }
  }
}

#endif

CLASS *TEMPLATE3(ARCH,_,CLASS,Init)(CLASS *ob,int inst) {
  if (inst >= 0) {
    return (inst < TEMPLATE2(ARCH,CLASS,Instances)) ?
      TEMPLATE3(ARCH,__,CLASS,Init)[inst](ob,inst) : ob;
  } else {
    return (-inst-1 < TEMPLATE2(ARCH,CLASS,Instances)) ?
      TEMPLATE3(ARCH,__,CLASS,Init)[-inst-1](ob,inst) : ob;    
  }
  //return (inst>=0&&inst<TEMPLATE2(ARCH,CLASS,Instances))?TEMPLATE3(ARCH,__,CLASS,Init)[inst](ob,inst):ob;
}

#undef CLASS
