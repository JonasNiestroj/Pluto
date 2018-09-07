#ifndef _PIC_H__
#define _PIC_H__

#define PIC1 0x20
#define PIC2 0xA0
#define PIC1COMMAND PIC1
#define PIC1DATA (PIC1 + 1)
#define PIC2COMMAND PIC2
#define PIC2DATA (PIC2 + 1)
#define PICEND 0x20

#define ICW1ICW4 0x01
#define ICW1SINGLE 0x02
#define ICW1INTERVAL4 0x04
#define ICW1LEVEL 0x08
#define ICW1INIT 0x10

#define ICW48086 0x01
#define ICW4AUTO 0x02
#define ICW4BUFSLAVE 0x08
#define ICW4BUFMASTER 0x0c
#define ICW4SFNM 0x10

void picinit();

void picendmaster();

void picendslave();

unsigned short picgetirr();

unsigned short picgetisr();

#endif