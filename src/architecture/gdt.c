#include "gdt.h"

struct tssentry tss = {
    .ss0 = 0x10,
    .esp0 = 0,
    .es = 0x10,
    .cs = 0x08,
    .ds = 0x13,
    .fs = 0x13,
    .gs = 0x13};

struct gdtentry gdt[] =
    {
        GDTENTRY(0, 0, 0, 0),
        GDTENTRY(0, 0xFFFFFFFF, 0x9A, GDT32BIT | GDT4KBBLOCKSIZE),
        GDTENTRY(0, 0xFFFFFFFF, 0x92, GDT32BIT | GDT4KBBLOCKSIZE),
        GDTENTRY(0, 0xFFFFFFFF, 0xFA, GDT32BIT | GDT4KBBLOCKSIZE),
        GDTENTRY(0, 0xFFFFFFFF, 0xF2, GDT32BIT | GDT4KBBLOCKSIZE),
        GDTENTRY(0, sizeof(tss) - 1, 0xE9, 0x00),
};

unsigned short gdtsize = sizeof(gdt) - 1;