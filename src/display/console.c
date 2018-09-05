#include "console.h"

static int actualWidth = 0;
static int actualHeight = 0;

void print(char character)
{
    if (character == '\n' || actualWidth == WIDTH)
    {
        actualHeight++;
        actualWidth = 0;
        return;
    }
    unsigned short c = (unsigned short)character | (0x0F) << 8;
    *(unsigned short *)(VGA_START + actualHeight * 2 * WIDTH + actualWidth * 2) = c;
    actualWidth++;
}

void printstring(char characters[])
{
    // TODO Add strlen to for loop
    for (int i = 0; characters[i] != 0; i++)
    {
        print(characters[i]);
    }
}