#if defined(cavium) || defined(__cavium)
  #include "libtsctl-cavium.c"
#endif 

#if defined(noncavium) || defined(__noncavium)
  #include "libtsctl-noncavium.c"
#endif 





