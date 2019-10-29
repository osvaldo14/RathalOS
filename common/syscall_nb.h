#ifndef _SYSCALL_NB_H_
#define _SYSCALL_NB_H_

typedef enum { 
    SYSCALL_PUTS            = 0,
    SYSCALL_EXEC            = 1,
    SYSCALL_KEYPRESSED      = 2,
    SYSCALL_GETC            = 3,
    SYSCALL_FILE_STAT       = 4,
    SYSCALL_FILE_OPEN       = 5,
    SYSCALL_FILE_READ       = 6,
    SYSCALL_FILE_CLOSE      = 7,
    SYSCALL_FILE_SEEK       = 8,
    SYSCALL_FILE_REMOVE     = 9,
    SYSCALL_FILE_ITERATOR   = 10,
    SYSCALL_FILE_HAS_NEXT   = 11,
    SYSCALL_FILE_NEXT       = 12,
    SYSCALL_GET_TICKS       = 13,
    SYSCALL_PUTC            = 14,
    SYSCALL_PRINTF          = 15,
    SYSCALL_SRAND           = 16,
    SYSCALL_RAND            = 17,
    SYSCALL_SLEEP           = 18,
    SYSCALL_EXIT            = 19,
    SYSCALL_STRLEN          = 20,
    SYSCALL_STRCMP          = 21,
    SYSCALL_READ_STRING     = 22,
    
    SYSCALL_END
} syscall_t;

#endif
