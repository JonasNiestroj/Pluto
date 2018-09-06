#ifndef _GDT_H__
#define _GDT_H__

#define GDT64BIT (1 << 5)
#define GDT32BIT (1 << 6)
#define GDT4KBBLOCKSIZE (1 << 7)

struct tssentry
{
    unsigned int prevtss;
    unsigned int esp0;
    unsigned int ss0;
    unsigned int esp1;
    unsigned int ss1;
    unsigned int esp2;
    unsigned int ss2;
    unsigned int cr3;
    unsigned int eip;
    unsigned int eflags;
    unsigned int eax;
    unsigned int ecx;
    unsigned int edx;
    unsigned int ebx;
    unsigned int esp;
    unsigned int ebp;
    unsigned int esi;
    unsigned int edi;
    unsigned int es;
    unsigned int cs;
    unsigned int ss;
    unsigned int ds;
    unsigned int fs;
    unsigned int gs;
    unsigned int ldt;
    unsigned short trap;
    unsigned short iomapbase;
} __attribute__((__packed__));

struct gdtentry
{
    unsigned short limit_low;
    unsigned short base_low;
    unsigned char base_mid;
    unsigned char access;
    unsigned char granularity;
    unsigned char base_high;
} __attribute__((__packed__));

#define GDTENTRY(base, limit, access, granularity)         \
    {                                                      \
        (limit) & 0xFFFF,                                  \
            (base) >> 0 & 0xFFFF,                          \
            (base) >> 16 & 0xFF,                           \
            (access)&0xFF,                                 \
            ((limit) >> 16 & 0x0F) | ((granularity)&0xF0), \
            (base) >> 24 & 0xFF,                           \
    }

#endif