#ifndef _IDT_H__
#define _IDT_H__

#define IDTINTERRUPT 0xE
#define IDTSTORAGE 0x20
#define IDTDPL 0x60
#define IDTPRESENT (1 << 7)

typedef struct
{
    unsigned short offset_low;
    unsigned short selector;
    unsigned char zerobyte;
    unsigned char type;
    unsigned short offset_high;
} __attribute__((__packed__)) IDT;

void call(unsigned int base, unsigned short limit);

void idtinit();

void idt_set_handler(IDT *entry, void (*handler)(void), unsigned char type, unsigned char access);

// TODO Find better solution

void isr0();
void isr1();
void isr2();
void isr3();
void isr4();
void isr5();
void isr6();
void isr7();
void isr8();
void isr9();
void isr10();
void isr11();
void isr12();
void isr13();
void isr14();
void isr15();
void isr16();
void isr17();
void isr18();
void isr19();
void isr20();
void isr21();
void isr22();
void isr23();
void isr24();
void isr25();
void isr26();
void isr27();
void isr28();
void isr29();
void isr30();
void isr31();
void irq0();
void irq1();
void irq2();
void irq3();
void irq4();
void irq5();
void irq6();
void irq7();
void irq8();
void irq9();
void irq10();
void irq11();
void irq12();
void irq13();
void irq14();
void irq15();

#endif