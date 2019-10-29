#ifndef _FUNC_H_
#define _FUNC_H_

#include "types.h"
#include "../kernel/display/display.h"

void *memset(void *dst, int value, uint_t count);
void *memcpy(void *dst, void *src, uint_t count);
char *strncpy(char *dest, const char *src, uint_t count);
int strcmp(const char *p, const char *q);
int strncmp(const char *p, const char *q, uint_t count);
int strlen(char *s);
void strcat(char *dst, char *src);
char *invert_string( char * ret );
int int_len( int x );


#endif