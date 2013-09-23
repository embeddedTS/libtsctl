#define NEW_ARCH
typedef void *(*InitFunctionPtr)(void *,int);

struct Arch;
typedef struct Arch Arch;

struct Arch {
  Arch *(*Init)();
  void *(*Function)(int class,int inst);
  Arch *(*NextSubArch)();
  void (*NextSubArchSet)(Arch *);
  int (*CANBusId)(int inst);
};

Arch *ts4200ArchInit();
Arch *ts4500ArchInit();
Arch *ts4700ArchInit();
Arch *ts4800ArchInit();
Arch *ts81x0ArchInit();
Arch *ts8200ArchInit();
Arch *ts8390ArchInit();
Arch *ts8820ArchInit();
Arch *ts8900ArchInit();
Arch *ts9490ArchInit();

unsigned DIOCount();
int ArchClassCount(Arch *hw,unsigned class,int recurse);
void *ClassInit(int class,int inst);
Arch *ArchInit();
Arch *ArchBBInit();
void ArchPC104Init(Arch *owner);
int ArchPC104Max();

System *SystemInit(int inst);
Bus *BusInit(int inst);
Time *TimeInit(int inst);
Pin *PinInit(int inst);
DIORaw *DIORawInit(int inst);
DIO *DIOInit(int inst);
TWI *TWIInit(int inst);
CAN *CANInit(int inst);
SPI *SPIInit(int inst);
AIO *AIOInit(int inst);
EDIO *EDIOInit(int inst);
