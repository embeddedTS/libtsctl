-include Makefile.config
CC=$(TOOL_PREFIX)gcc
ARCH?=noncavium
CFLAGS+=-march=armv4 -ffunction-sections -fdata-sections -D$(ARCH)=1
LDFLAGS+=-Wl,-gc-sections
DEPS=$(shell ls ts/*.[ch])

ifeq ($(DEBUG),)
CFLAGS+=-Os
else
CFLAGS+=-g
endif

DIR?=$(ARCH)

PRODUCTS=tsctl CAN2 CANTx CANDiag CANRx diotoggle spi8200 ts8160ctl DIOTest canctl spictl NetTest NetTest2

$(shell mkdir -p $(DIR))

tsctl: $(DIR)/tsctl
	@true

$(DIR)/tsctl: tsctl.c $(DEPS)
	@echo "Building $@"
	@$(CC) $(CFLAGS) $(CFLAGS_$(patsubst %.c,%,$<)) $< \
        $(LDFLAGS) -lpthread /usr/lib/libreadline.a -lcurses -o $@

all: $(PRODUCTS)

CAN2: $(DIR)/CAN2
	@true

$(DIR)/CAN2: CAN2.c
	@echo "Building $@";$(CC) $(CFLAGS) $< $(LDFLAGS) -lpthread -o $@

CANTx: $(DIR)/CANTx
	@true

$(DIR)/CANTx: CANTx.c
	@echo "Building $@";$(CC) $(CFLAGS) $< $(LDFLAGS) -o $@

CANDiag: $(DIR)/CANDiag
	@true

$(DIR)/CANDiag: CANDiag.c
	@echo "Building $@";$(CC) $(CFLAGS) $< $(LDFLAGS) -o $@

CANRx: $(DIR)/CANRx
	@true

$(DIR)/CANRx: CANRx.c
	@echo "Building $@";$(CC) $(CFLAGS) $< $(LDFLAGS) -lpthread -o $@

diotoggle: $(DIR)/diotoggle
	@true

$(DIR)/diotoggle: diotoggle.c
	@echo "Building $@";$(CC) $(CFLAGS) $< $(LDFLAGS) -o $@

spi8200: $(DIR)/spi8200
	@true

$(DIR)/spi8200: spi8200.c
	@echo "Building $@";$(CC) $(CFLAGS) $< $(LDFLAGS) -o $@

ts8160ctl: $(DIR)/ts8160ctl
	@true

$(DIR)/ts8160ctl: ts8160ctl.c
	@echo "Building $@";$(CC) $(CFLAGS) $< $(LDFLAGS) -o $@

DIOTest: $(DIR)/DIOTest
	@true

$(DIR)/DIOTest: DIOTest.c
	@echo "Building $@";$(CC) $(CFLAGS) $< $(LDFLAGS) -o $@

canctl: $(DIR)/canctl
	@true

$(DIR)/canctl: canctl.c
	@echo "Building $@";$(CC) $(CFLAGS) $< $(LDFLAGS) -lpthread -o $@

spictl: $(DIR)/spictl
	@true

$(DIR)/spictl: spictl.c
	@echo "Building $@";$(CC) $(CFLAGS) $< $(LDFLAGS) -o $@

NetTest: $(DIR)/NetTest
	@true

$(DIR)/NetTest: NetTest.c
	@echo "Building $@";$(CC) $(CFLAGS) -Its $< $(LDFLAGS) -o $@

NetTest2: $(DIR)/NetTest2
	@true

$(DIR)/NetTest2: NetTest2.c
	@echo "Building $@";$(CC) $(CFLAGS) -Its $< $(LDFLAGS) -o $@

clean:
	@rm -rf $(DIR)
	@rm -f $(PRODUCTS) tsctl_wrap.* *~ *.py

.PHONY: clean
