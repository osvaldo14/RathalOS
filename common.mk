LD=gcc
NO_BUILTIN_LIBS=-ffreestanding -static -nostdlib -fno-builtin -fno-stack-protector
CC=gcc -g -std=gnu11 -m32 $(NO_BUILTIN_LIBS) -Wall -Wextra -MMD -c
