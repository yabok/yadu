CC := clang
CFLAGS += -std=c11 -Weverything -D_DEFAULT_SOURCE -lbsd

ifeq ($(V),1)
	verbose_hide := $(empty)
	verbose_echo := @:
else
	verbose_hide := @
	verbose_echo := @echo
endif

all: yadu

yadu: yadu.c time-dst.c time-dst.h util.h
	$(verbose_echo) "  CC    $@"
	$(verbose_hide) $(CC)  $(CFLAGS)  -o $@  yadu.c time-dst.c

clean:
	-rm -f yadu

.PHONY: all clean
