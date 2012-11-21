-include Makefile.config
CC=$(TOOL_PREFIX)gcc

CFLAGS+=-march=armv4 -ffunction-sections -fdata-sections -D$(BOARDSEL)=1
LDFLAGS+=-D$(BOARDSEL)=1

CFLAGS_tsctl_wrap=-I/usr/include/python2.5
LDFLAGS_CAN2=-lpthread
LDFLAGS_CANRx=-lpthread
CFLAGS_CANRx=-DTHREAD_USE_POSIX
LDFLAGS_canctl=-lpthread
#CFLAGS_tsctl=-DLOGGING
LDFLAGS_tsctl=-lpthread -lreadline
#-lefence
LDFLAGS_ptest=-lpthread

ifeq ($(DEBUG),)
CFLAGS+=-Os
else
CFLAGS+=-g
endif

BUILD_DIR:=$(BOARDSEL)

PRODUCTS ?= CAN2 CANTx CANDiag CANRx diotoggle spi8200 ts8160ctl DIOTest canctl tsctl spictl _tsctl.so

all: $(BUILD_DIR) $(addprefix $(BUILD_DIR)/,$(PRODUCTS))

$(BUILD_DIR)/%: %.c
	@echo "Compiling $<"; $(CC) $(CFLAGS) $(CFLAGS_$(lastword $(subst /, ,$(patsubst %.c,%,$<)))) $< -o $@ $(LDFLAGS) $(LDFLAGS_$(lastword $(subst /, ,$(patsubst %.c,%,$<))))

%.o: %.c
	@echo "Compiling $<"; $(CC) -c $(CFLAGS) $(CFLAGS_$(lastword $(subst /, ,$(patsubst %.o,%,$@)))) $< -o  $@

$(BUILD_DIR)/tsctl_wrap.o: tsctl_wrap.c
	@echo "Compiling $<"; $(CC) -c $(CFLAGS) $(CFLAGS_tsctl_wrap) $< -o  $@

tsctl_wrap.c: tsctl.i
	swig -python tsctl.i

$(BUILD_DIR)/_tsctl.so: $(BUILD_DIR)/tsctl_wrap.o
	@echo "Compiling $<"; $(CC) -shared $(CFLAGS) $(CFLAGS_$(lastword $(subst /, ,$(patsubst %.o,%,$@)))) libtsctl.c $< -o  $@ $(LDFLAGS) $(LDFLAGS_$@)

clean:
	@rm -rf $(BUILD_DIR)
	@rm -f $(PRODUCTS) tsctl_wrap.* *~ *.py

.PHONY: clean copy release

$(BUILD_DIR):
	@mkdir -p $@


