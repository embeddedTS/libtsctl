-include Makefile.config
CC=$(TOOL_PREFIX)gcc
CXX=$(TOOL_PREFIX)g++
ARCH?=noncavium
DIR?=$(ARCH)
ifeq ($(ARCH),cavium)
SUPPORT?=4500 81x0 8200 8390 8820 8900 9490 relay8 dio24 can1
endif
ifeq ($(ARCH),noncavium)
SUPPORT?=4200 4700 4800 81x0 8200 8390 8820 8900 9490 relay8 dio24 can1
endif
SUPPORTFLAGS=$(SUPPORT:%=-DARCH_%)
ARCHLIBS=$(SUPPORT:%=libts%.a)
ARCHLINK=$(SUPPORT:%=-lts%)
CFLAGS+=-march=armv4 -ffunction-sections -fdata-sections -D$(ARCH)=1 -Its
CFLAGS+=$(SUPPORTFLAGS)
LDFLAGS+=-Wl,-gc-sections -L$(DIR)
#DEPS=$(shell ls ts/*.[ch])
#DEPS2=$(shell ls net/*.[ch])
vpath %.cpp . ts
vpath %.c . ts
vpath %.o $(DIR)
vpath %.a $(DIR)
ifeq ($(DIR_CUSTOM),)
else
vpath %.cpp . ts $(DIR_CUSTOM)
vpath %.c . ts $(DIR_CUSTOM)
-include $(DIR_CUSTOM)/Makefile
endif

ifeq ($(DEBUG),)
CFLAGS+=-Os
else
CFLAGS+=-g
endif
CPPFLAGS=$(CFLAGS)

PRODUCTS=tsctl CAN2 CANTx CANDiag CANRx diotoggle spi8200 ts8160ctl DIOTest canctl spictl NetTest NetTest2

$(shell mkdir -p $(DIR))

$(DIR)/libtsctl-pthread.a: $(addprefix $(DIR)/,$(ARCHLIBS) PThread.o libtsctlutil.a)
	ar -r $@ $^

$(DIR)/libtsctl.a: $(addprefix $(DIR)/,$(ARCHLIBS) NoThread.o libtsctlutil.a)
	ar -r $@ $^

MapDump: $(DIR)/MapDump
	@true

$(DIR)/MapDump: $(addprefix $(DIR)/,MapDump.o Arch.o NoThread.o $(ARCHLIBS)) -ltsctl -lbz2 

$(DIR)/%.o: %.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<

$(DIR)/libtsctlutil.a: $(addprefix $(DIR)/,Arch.o dioctlConfig.o shell.o opt.o HashTable.o IteratorHashTable.o tcp.o http.o Stream.o socket.o LookupRef.o ts.o)
	ar -r $@ $^

$(DIR)/libts81x0.a: $(addprefix $(DIR)/,ts81x0Arch.o ts8100_dioctl_config.o ts8160_dioctl_config.o)
	ar -r $@ $^

$(DIR)/libts8200.a: $(addprefix $(DIR)/,ts8200Arch.o ts8200_dioctl_config.o)
	ar -r $@ $^

$(DIR)/libts7670.a: $(addprefix $(DIR)/,ts7670Arch.o MMapBus.o DummyBus.o LocalSystem.o SystemTime.o ts7670Pin.o ts7670DIORaw.o CacheBus.o PhysicalDIO.o AggregateDIO.o DIOTWI.o)
	ar -r $@ $^

$(DIR)/libts8390.a: $(addprefix $(DIR)/,ts8390Arch.o ts8390_dioctl_config.o)
	ar -r $@ $^

$(DIR)/libts8820.a: $(addprefix $(DIR)/,ts8820Arch.o ts8820DIORaw.o ts8820Pin.o ts8820ADCAIO.o ts8820DACAIO.o ts8820EDIO.o PhysicalDIO.o CacheBus.o ts8820_dioctl_config.o)
	ar -r $@ $^

$(DIR)/libts8900.a: $(addprefix $(DIR)/,ts8900Arch.o ts8900DIORaw.o ts8900Pin.o PhysicalDIO.o CacheBus.o PC104Bus.o ts8900_dioctl_config.o)
	ar -r $@ $^

$(DIR)/libts9490.a: $(addprefix $(DIR)/,ts9490Arch.o ts9490_dioctl_config.o)
	ar -r $@ $^

$(DIR)/libts4200.a: $(addprefix $(DIR)/,ts4200Arch.o DummyBus.o MMapBus.o TSMuxBus.o CacheBus.o ts4200Pin.o AtmelAT91DIORaw.o ts4200DIORaw.o SystemTime.o PhysicalDIO.o AggregateDIO.o DIOTWI.o DIOSPI.o LocalSystem.o SJA1000CAN.o ts4200DIO.o ts4200_dioctl_config.o)
	ar -r $@ $^

$(DIR)/libts4500.a: $(addprefix $(DIR)/,ts4500Arch.o DummyBus.o MMapBus.o TSMuxBus.o CacheBus.o ts4500Pin.o Cavium2132DIORaw.o ts4500DIORaw.o SystemTime.o PhysicalDIO.o AggregateDIO.o DIOTWI.o WBSPI.o LocalSystem.o SJA1000CAN.o Cavium2132SBus.o Cavium2132SBusWindowBus.o WBWindowBus.o Cavium2132Time.o WBSPI.o ts4500_dioctl_config.o)
	ar -r $@ $^

$(DIR)/libts4700.a: $(addprefix $(DIR)/,ts4700Arch.o DummyBus.o MMapBus.o TSMuxBus.o CacheBus.o ts4700Pin.o MarvellPXA166DIORaw.o ts4700DIORaw.o ts7700DIORaw.o SystemTime.o PhysicalDIO.o AggregateDIO.o DIOTWI.o WBSPI.o LocalSystem.o SJA1000CAN.o ts4700_dioctl_config.o ts7700_dioctl_config.o)
	ar -r $@ $^

$(DIR)/libts4800.a: $(addprefix $(DIR)/,ts4800Arch.o DummyBus.o MMapBus.o TSMuxBus.o CacheBus.o ts4800Pin.o FreescaleIMX51DIORaw.o ts4800DIORaw.o SystemTime.o PhysicalDIO.o AggregateDIO.o LinuxTWI.o WBSPI.o LocalSystem.o SJA1000CAN.o TSTime.o WBWindowBus.o WindowBus.o ts4800_dioctl_config.o)
	ar -r $@ $^

$(DIR)/libtsrelay8.a: $(addprefix $(DIR)/,tsrelay8Arch.o tsRelay8DIORaw.o DummyDIO.o PhysicalDIO.o)
	ar -r $@ $^

$(DIR)/libtsdio24.a: $(addprefix $(DIR)/,tsdio24Arch.o tsDIO24DIORaw.o DummyDIO.o PhysicalDIO.o CacheBus.o)
	ar -r $@ $^

$(DIR)/libtscan1.a: $(addprefix $(DIR)/,tscan1Arch.o TSCAN1Bus.o SJA1000CAN.o)
	ar -r $@ $^

tsctl: $(DIR)/tsctl
	@true

$(DIR)/tsctl: $(addprefix $(DIR)/,tsctl.o Arch.o PThread.o command.o command1.o $(ARCHLIBS)) -lreadline -lcurses -ltsctlutil -lbz2 -lpthread

# /usr/lib/libreadline.a

MapDump2: $(DIR)/MapDump2
	@true

$(DIR)/MapDump2.o: MapDump2.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

$(DIR)/MapDump2: $(addprefix $(DIR)/,MapDump2.o Arch.o NoThread.o $(ARCHLIBS)) -ltsctlutil /usr/lib/gst/gstdeps/lib/libbz2.so /usr/lib/libstdc++.so.6

# -lstdc++

#	@echo "Building --- $@"
#	$(CXX) $(CFLAGS) $(CFLAGS_$(patsubst %.c,%,$<)) $< \
#        $(LDFLAGS) $(ARCH)/libtsctl.a -o $@

all: $(PRODUCTS)

CAN2: $(DIR)/CAN2
	@true

$(DIR)/CAN2: $(addprefix $(DIR)/,CAN2.o Arch.o PThread.o $(ARCHLIBS)) -ltsctlutil -lbz2 -lpthread

CAN3: $(DIR)/CAN3
	@true

$(DIR)/CAN3: $(addprefix $(DIR)/,CAN3.o Arch.o PThread.o $(ARCHLIBS)) -ltsctlutil -lbz2 -lpthread

CANTx: $(DIR)/CANTx
	@true

$(DIR)/CANTx: $(addprefix $(DIR)/,CANTx.o Arch.o NoThread.o $(ARCHLIBS)) -ltsctlutil -lbz2

CANDiag: $(DIR)/CANDiag
	@true

$(DIR)/CANDiag: $(addprefix $(DIR)/,CANDiag.o Arch.o NoThread.o $(ARCHLIBS)) -ltsctlutil -lbz2

CANRx: $(DIR)/CANRx
	@true

$(DIR)/CANRx: $(addprefix $(DIR)/,CANRx.o Arch.o PThread.o $(ARCHLIBS)) -ltsctlutil -lbz2 -lpthread

diotoggle: $(DIR)/diotoggle
	@true

$(DIR)/diotoggle: $(addprefix $(DIR)/,diotoggle.o Arch.o NoThread.o $(ARCHLIBS)) -ltsctlutil -lbz2

spi8200: $(DIR)/spi8200
	@true

$(DIR)/spi8200: $(addprefix $(DIR)/,spi8200.o Arch.o NoThread.o $(ARCHLIBS)) -ltsctlutil -lbz2

ts8160ctl: $(DIR)/ts8160ctl
	@true

$(DIR)/ts8160ctl: $(addprefix $(DIR)/,ts8160ctl.o Arch.o NoThread.o $(ARCHLIBS)) -ltsctlutil -lbz2

DIOTest: $(DIR)/DIOTest
	@true

$(DIR)/DIOTest: $(addprefix $(DIR)/,DIOTest.o Arch.o NoThread.o $(ARCHLIBS)) -ltsctlutil -lbz2

canctl: $(DIR)/canctl
	@true

$(DIR)/canctl: $(addprefix $(DIR)/,canctl.o Arch.o PThread.o $(ARCHLIBS)) -ltsctlutil -lbz2 -lpthread

spictl: $(DIR)/spictl
	@true

$(DIR)/spictl: $(addprefix $(DIR)/,spictl.o Arch.o PThread.o $(ARCHLIBS)) -ltsctlutil -lbz2 -lpthread


NetTest: $(DIR)/NetTest
	@true

$(DIR)/NetTest: NetTest.c $(DEPS2)
	@echo "Building $@";$(CC) $(CFLAGS) -I. -Inet $< $(LDFLAGS) -o $@

CANNetTx: $(DIR)/CANNetTx
	@true

$(DIR)/CANNetTx: CANNetTx.c $(DEPS2)
	@echo "Building $@";$(CC) $(CFLAGS) -I. -Inet $< $(LDFLAGS) -o $@

NetTest2: $(DIR)/NetTest2
	@true

$(DIR)/NetTest2: NetTest2.c $(DEPS2)
	@echo "Building $@";$(CC) $(CFLAGS) -Inet $< $(LDFLAGS) -o $@

clean:
	@rm -rf $(DIR)
	@rm -f $(PRODUCTS) tsctl_wrap.* *~ *.py

.PHONY: clean
