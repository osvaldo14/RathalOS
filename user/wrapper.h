#include "../kernel/fs/fs.h"

#define LINE_SIZE 80
#define SCREEN_SIZE 80*25

// syscalls
void puts(char* str);
int exec(char* filename);
int keypressed();
int getc();
int file_stat(char *filename, stat_t *stats);
int file_open(char *filename);
int file_read(int fd, void *buf, uint_t count);
void file_close(int fd);
int file_seek(int fd, uint_t offset);
int file_remove(char *filename);
file_iterator_t file_iterator();
bool file_has_next(file_iterator_t *it);
void file_next(char *filename, file_iterator_t *it);
uint_t get_ticks() ;
void putc(char c);
void printf(char* fmt, ...);
int srand(uint_t seed);
int rand();
void sleep(uint_t ms);
void exit();
int strlen(char* str);
int strcmp(const char *p, const char *q);
void read_string(char *buffer);

// tool functions for shell.c
void read_string(char* buf);
char* trim(char* str);
int starts_with(char* str, char* line);
int atoi(char* str);