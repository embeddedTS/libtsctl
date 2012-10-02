  arch = ArchFirst;
  i = 0;
  while (arch) {
    while (arch->TEMPLATE(CLASS,Init)(0,i,1)) i++;
    arch->Instances[TEMPLATE(Class,CLASS)] = i;
    i = 0;
    arch = arch->next;
  }
#undef CLASS
