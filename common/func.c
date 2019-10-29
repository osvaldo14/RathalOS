#include "func.h"
#include "types.h"

/* 
	The  memset()  function  fills  the  first  count  bytes of the memory area
    pointed to by dst with the constant byte value.

*/
void *memset(void *dst, int value, uint_t count){
	uchar_t *p = dst;
    while(count--)
        *p++ = (uchar_t) value;
    return dst;
}

/*
	The  memcpy()  function  copies count bytes from memory area src to memory
    area dst.
*/
void *memcpy(void *dst, void *src, uint_t count){
    uchar_t *dp = dst;
    uchar_t *sp = src;
    while (count--)
    	*dp++ = *sp++;
    return dst;
}

/* 
	returns the length of a null-terminated string
*/
int strlen(char *s){
	uint_t cnt = 0;
	while(*s++)
		cnt++;
	return cnt;
}

/*
	copies the first count chars of string src into string dst. If dst
	is shorter than count, fills the rest of dst with null bytes
*/
char *strncpy(char *dst, const char *src, uint_t count){
	char *ret = dst;
	do {
		if(!count--){
			return ret;
		}
	} while ((*dst++ = *src++)); // while *src++ exists
	while(count--)
		*dst++ = '\0';
	return ret;
}

/*
	compares strings p and q and returns 0 if they are equal, returns the
	alphabetical difference otherwise
*/
int strcmp(const char *p, const char *q){
	uchar_t c1, c2;

	do{
		c1 = *p++;
		c2 = *q++;
		if(c1 == '\0'){
			return c1-c2;
		}
	}
	while(c1 == c2);

	return c1-c2;
}

/*
	Functions like strcpy, but on the count first bytes
*/
int strncmp(const char *p, const char *q, uint_t count){
	uchar_t c1, c2;

	do{
		if(count--){	
			c1 = *p++;
			c2 = *q++;
			
			if(c1 == '\0'){
				return c1-c2;
			}
		} else {
			return c1-c2;
		}
	}
	while(c1 == c2);

	return c1-c2;
}

/*
	Function to copy string src at the end of string dst
*/
void strcat(char *dst, char *src){
	dst += strlen(dst);
	while((*dst++ = *src++))
		;
}

int int_len( int x ){
	int i = 0;
	do{
		i++;
	} while ( x /= 10 );
	return i;
}



