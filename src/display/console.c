#include "console.h"

void print(char character)
{
    unsigned short c = (unsigned short)character | (0x0F) << 8;
    *(unsigned short *)(0xb8000) = c;
}