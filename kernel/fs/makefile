CC=gcc
CFLAGS=-m32 -ffreestanding -nostdlib -fno-builtin -fno-stack-protector -Wall -Wextra -c -MMD

SRCS=$(wildcard *.c)
OBJS=$(SRCS:%.c=%.o)
DEPS=$(OBJS:%.o=%.d)

all: fs.o

%.o: %.c
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f *.o *.d

-include $(DEPS)