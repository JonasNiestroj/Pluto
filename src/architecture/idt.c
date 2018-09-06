#include "idt.h"

IDT idttable[256];

void call(unsigned int base, unsigned short limit)
{
    __asm__ __volatile__("subl $6, %%esp\n\t"
                         "movw %w0, 0(%%esp)\n\t"
                         "movl %1, 2(%%esp)\n\t"
                         "lidt (%%esp)\n\t"
                         "addl $6, %%esp"
                         :
                         : "rN"(limit), "r"(base));
}

void memset(unsigned char *s, unsigned char c, unsigned int n)
{
    while (n--)
    {
        *s++ = c;
    }
    return s;
}

void idtinit()
{
    memset(idttable, 0, sizeof(idttable));

    // TODO Find better solution

    idt_set_handler(&idttable[0], isr0, IDTINTERRUPT, 0x0);
    idt_set_handler(&idttable[1], isr1, IDTINTERRUPT, 0x0);
    idt_set_handler(&idttable[2], isr2, IDTINTERRUPT, 0x0);
    idt_set_handler(&idttable[3], isr3, IDTINTERRUPT, 0x0);
    idt_set_handler(&idttable[4], isr4, IDTINTERRUPT, 0x0);
    idt_set_handler(&idttable[5], isr5, IDTINTERRUPT, 0x0);
    idt_set_handler(&idttable[6], isr6, IDTINTERRUPT, 0x0);
    idt_set_handler(&idttable[7], isr7, IDTINTERRUPT, 0x0);
    idt_set_handler(&idttable[8], isr8, IDTINTERRUPT, 0x0);
    idt_set_handler(&idttable[9], isr9, IDTINTERRUPT, 0x0);
    idt_set_handler(&idttable[10], isr10, IDTINTERRUPT, 0x0);
    idt_set_handler(&idttable[11], isr11, IDTINTERRUPT, 0x0);
    idt_set_handler(&idttable[12], isr12, IDTINTERRUPT, 0x0);
    idt_set_handler(&idttable[13], isr13, IDTINTERRUPT, 0x0);
    idt_set_handler(&idttable[14], isr14, IDTINTERRUPT, 0x0);
    idt_set_handler(&idttable[15], isr15, IDTINTERRUPT, 0x0);
    idt_set_handler(&idttable[16], isr16, IDTINTERRUPT, 0x0);
    idt_set_handler(&idttable[17], isr17, IDTINTERRUPT, 0x0);
    idt_set_handler(&idttable[18], isr18, IDTINTERRUPT, 0x0);
    idt_set_handler(&idttable[19], isr19, IDTINTERRUPT, 0x0);
    idt_set_handler(&idttable[20], isr20, IDTINTERRUPT, 0x0);
    idt_set_handler(&idttable[21], isr21, IDTINTERRUPT, 0x0);
    idt_set_handler(&idttable[22], isr22, IDTINTERRUPT, 0x0);
    idt_set_handler(&idttable[23], isr23, IDTINTERRUPT, 0x0);
    idt_set_handler(&idttable[24], isr24, IDTINTERRUPT, 0x0);
    idt_set_handler(&idttable[25], isr25, IDTINTERRUPT, 0x0);
    idt_set_handler(&idttable[26], isr26, IDTINTERRUPT, 0x0);
    idt_set_handler(&idttable[27], isr27, IDTINTERRUPT, 0x0);
    idt_set_handler(&idttable[28], isr28, IDTINTERRUPT, 0x0);
    idt_set_handler(&idttable[29], isr29, IDTINTERRUPT, 0x0);
    idt_set_handler(&idttable[30], isr30, IDTINTERRUPT, 0x0);
    idt_set_handler(&idttable[31], isr31, IDTINTERRUPT, 0x0);
    idt_set_handler(&idttable[32], irq0, IDTINTERRUPT, 0x0);
    idt_set_handler(&idttable[33], irq1, IDTINTERRUPT, 0x0);
    idt_set_handler(&idttable[35], irq3, IDTINTERRUPT, 0x0);
    idt_set_handler(&idttable[36], irq4, IDTINTERRUPT, 0x0);
    idt_set_handler(&idttable[37], irq5, IDTINTERRUPT, 0x0);
    idt_set_handler(&idttable[38], irq6, IDTINTERRUPT, 0x0);
    idt_set_handler(&idttable[39], irq7, IDTINTERRUPT, 0x0);
    idt_set_handler(&idttable[40], irq8, IDTINTERRUPT, 0x0);
    idt_set_handler(&idttable[41], irq9, IDTINTERRUPT, 0x0);
    idt_set_handler(&idttable[42], irq10, IDTINTERRUPT, 0x0);
    idt_set_handler(&idttable[43], irq11, IDTINTERRUPT, 0x0);
    idt_set_handler(&idttable[44], irq12, IDTINTERRUPT, 0x0);
    idt_set_handler(&idttable[45], irq13, IDTINTERRUPT, 0x0);
    idt_set_handler(&idttable[46], irq14, IDTINTERRUPT, 0x0);
    idt_set_handler(&idttable[47], irq15, IDTINTERRUPT, 0x0);

    call((unsigned int)idttable, sizeof(idttable) - 1);
}

void idt_set_handler(IDT *entry, void (*handler)(void), unsigned char type, unsigned char access)
{
    entry->offset_low = (unsigned int)handler & 0xFFFF;
    entry->selector = 0x8;
    entry->zerobyte = 0;
    entry->type = IDTPRESENT | access << 5 | type;
    entry->offset_high = (unsigned int)handler >> 16 & 0xFFFF;
}