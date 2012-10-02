#include "cpp.h"

ArchInfo TEMPLATE(ARCH,_ArchInfo) = {
  .Instances= {
    TEMPLATE(ARCH,SystemInstances),
    TEMPLATE(ARCH,BusInstances),
    TEMPLATE(ARCH,TimeInstances),
    TEMPLATE(ARCH,PinInstances),
    TEMPLATE(ARCH,DIORawInstances),
    TEMPLATE(ARCH,DIOInstances),
    TEMPLATE(ARCH,TWIInstances),
    TEMPLATE(ARCH,CANInstances),
    TEMPLATE(ARCH,SPIInstances),
    TEMPLATE(ARCH,AIOInstances),
    TEMPLATE(ARCH,EDIOInstances)
  },
  .name=STRINGIFY(ARCH),
  .type=ARCHTYPE,
  .subarches=ArrayL(TEMPLATE(a,ARCHSUBTYPE)),
  .parent=0,
  .CANBusNum=TEMPLATE(ARCH,_CANBusNum),
  .ArchInit=TEMPLATE(ARCH,_ArchInit),
  .SystemInit=TEMPLATE(ARCH,_SystemInit),
  .BusInit=TEMPLATE(ARCH,_BusInit),
  .TimeInit=TEMPLATE(ARCH,_TimeInit),
  .PinInit=TEMPLATE(ARCH,_PinInit),
  .DIORawInit=TEMPLATE(ARCH,_DIORawInit),
  .DIOInit=TEMPLATE(ARCH,_DIOInit),
  .TWIInit=TEMPLATE(ARCH,_TWIInit),
  .CANInit=TEMPLATE(ARCH,_CANInit),
  .SPIInit=TEMPLATE(ARCH,_SPIInit),
  .AIOInit=TEMPLATE(ARCH,_AIOInit),
  .EDIOInit=TEMPLATE(ARCH,_EDIOInit)
};
#ifndef ARCH_LAST
ArchInfo *ArchFirst = &TEMPLATE(ARCH,_ArchInfo);
#endif

void TEMPLATE(ARCH,_ArchListInit)(void *next) {
  TEMPLATE(ARCH,_ArchInfo).next = next;
#ifdef ARCH_LAST
  TEMPLATE(ARCH_LAST,_ArchListInit)(&TEMPLATE(ARCH,_ArchInfo));
#endif
  //TEMPLATE(ARCH,_ArchInit)();
}
#undef ARCH_LAST
#undef ARCH
#undef ARCHTYPE
#undef ARCHSUBTYPE
