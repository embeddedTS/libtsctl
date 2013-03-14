// we now include support for all architecture in a single build
// we retain the cavium versus non-cavium distinction to allo separate
// binaries to be built for each, for cases where this is required.
//#if defined(cavium) || defined(__cavium)
//  #include "libtsctl-cavium.c"
//#endif 

//#if defined(noncavium) || defined(__noncavium)
  #include "libtsctl-noncavium.c"
//#endif 





