#ifndef _INTERRUPTS_H__
#define _INTERRUPTS_H__

#include "idt.h"

typedef struct
{
    unsigned int cr2;
    unsigned int gs;
    unsigned int fs;
    unsigned int ds;
    unsigned int es;
    unsigned int edi;
    unsigned int esi;
    unsigned int ebp;
    unsigned int ebx;
    unsigned int edx;
    unsigned int ecx;
    unsigned int eax;
    unsigned int int_no;
    unsigned int err_code;
    unsigned int eip;
    unsigned int cs;
    unsigned int eflags;
    unsigned int esp;
    unsigned int ss;
} __attribute__((__packed__)) interruptstruct;

void interruptinit();

void set_interrupt(unsigned char interruptnumber, void (*handler)());

void interruptrelay(interruptstruct *irt);

#endif