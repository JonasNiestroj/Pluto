#include "ports.h"

unsigned char inportbyte(unsigned short port)
{
    unsigned char retval;
    __asm__ __volatile__("inb %1, %0"
                         : "=a"(retval)
                         : "dN"(port));
    return retval;
}

void outportbyte(unsigned short port, unsigned char val)
{
    __asm__ __volatile__("outb %1, %0" ::"dN"(port), "a"(val));
}

unsigned short inportshort(unsigned short port)
{
    unsigned short retval;
    __asm__ __volatile__("inw %1, %0"
                         : "=a"(retval)
                         : "dN"(port));
    return retval;
}

void outportshort(unsigned short port, unsigned short val)
{
    __asm__ __volatile__("outw %1, %0" ::"dN"(port), "a"(val));
}

unsigned int inportint(unsigned short port)
{
    unsigned int retval;
    __asm__ __volatile__("inl %1, %0"
                         : "=a"(retval)
                         : "dN"(port));
    return retval;
}

void outportint(unsigned short port, unsigned int val)
{
    __asm__ __volatile__("outl %1, %0" ::"dN"(port), "a"(val));
}