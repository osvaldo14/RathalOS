# Run "make STATIC=1" to generate static binaries

include ../common.mk

COMMON_DIR=../common
COMMON_C=$(wildcard $(COMMON_DIR)/*.c)
COMMON_C+=$(wildcard $(COMMON_DIR)/fs/*.c)
COMMON_OBJ=$(COMMON_C:.c=.o)

CC=gcc
LD=gcc

ifeq ($(STATIC),1)
	LD+= -static
	SANITIZERS=
else
	SANITIZERS+= -fsanitize=address -fsanitize=leak -fsanitize=undefined -g
endif

CFLAGS=-m32 -c -std=gnu11 -MMD -Wall -Wextra $(SANITIZERS)
LDFLAGS=-m32 $(SANITIZERS)
#LDFLAGS=-m32 $(SANITIZERS) -fuse-ld=gold

SRCS=$(wildcard *.c)
OBJS=$(SRCS:%.c=%.o)
DEPS=$(OBJS:%.o=%.d)

BIN=fs_create fs_info fs_add fs_del fs_list fs_cat fs_read
BIN_OBJS=$(BIN:%=%.o)
NONBIN_OBJS=$(filter-out $(BIN_OBJS),$(OBJS))

all: common $(BIN)

common:
	$(MAKE) -C $(COMMON_DIR) NO_BUILTIN_LIBS=

%.o: %.c
	$(CC) -I .. $(CFLAGS) $<

fs_create: fs_create.o $(NONBIN_OBJS) $(COMMON_OBJ)
	$(LD) $(LDFLAGS) $^ -o $@

fs_info: fs_info.o $(NONBIN_OBJS) $(COMMON_OBJ)
	$(LD) $(LDFLAGS) $^ -o $@

fs_add: fs_add.o $(NONBIN_OBJS) $(COMMON_OBJ)
	$(LD) $(LDFLAGS) $^ -o $@

fs_cat: fs_cat.o $(NONBIN_OBJS) $(COMMON_OBJ)
	$(LD) $(LDFLAGS) $^ -o $@

fs_read: fs_read.o $(NONBIN_OBJS) $(COMMON_OBJ)
	$(LD) $(LDFLAGS) $^ -o $@

fs_del: fs_del.o $(NONBIN_OBJS) $(COMMON_OBJ)
	$(LD) $(LDFLAGS) $^ -o $@

fs_list: fs_list.o $(NONBIN_OBJS) $(COMMON_OBJ)
	$(LD) $(LDFLAGS) $^ -o $@

clean:
	$(MAKE) -C $(COMMON_DIR) clean
	/bin/rm -f *.o *.d $(BIN)

check:
	cppcheck --enable=all --language=c --platform=unix32 --std=c11 .

-include $(DEPS)
