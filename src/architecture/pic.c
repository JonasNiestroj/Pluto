#include "pic.h"
#include "ports.h"
#include "../display/console.h"

void picinit()
{
    unsigned char a1 = inportbyte(PIC1DATA);
    unsigned char a2 = inportbyte(PIC2DATA);

    outportbyte(PIC1, ICW1INIT + ICW1ICW4);
    outportbyte(PIC2, ICW1INIT + ICW1ICW4);

    outportbyte(PIC1DATA, 0x20);
    outportbyte(PIC2DATA, 0x28);

    outportbyte(PIC1DATA, 4);
    outportbyte(PIC2DATA, 2);

    outportbyte(PIC1DATA, 0x01);
    outportbyte(PIC2DATA, 0x01);

    outportbyte(PIC1DATA, a1);
    outportbyte(PIC2DATA, a2);

    printstring("PIC is initialized");

    return;
}

void picendmaster()
{
    outportbyte(PIC1COMMAND, PICEND);
}

void picendslave()
{
    outportbyte(PIC2COMMAND, PICEND);
}

unsigned short picgetirr()
{
    outportbyte(PIC1COMMAND, 0x0A);
    outportbyte(PIC2COMMAND, 0x0A);
    return inportbyte(PIC2COMMAND) << 8 | inportbyte(PIC1COMMAND);
}

unsigned short picgetisr()
{
    outportbyte(PIC1COMMAND, 0x0B);
    outportbyte(PIC2COMMAND, 0x0B);
    return inportbyte(PIC2COMMAND) << 8 | inportbyte(PIC1COMMAND);
}