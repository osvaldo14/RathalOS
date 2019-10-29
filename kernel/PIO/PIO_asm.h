#ifndef _PIO_H_
#define _PIO_H_

#include "../../common/types.h"
extern void    outb(ushort_t port, uchar_t data);
extern void    outw(ushort_t port, ushort_t data);
extern uchar_t  inb(ushort_t port);
extern ushort_t inw(ushort_t port);

#endif



