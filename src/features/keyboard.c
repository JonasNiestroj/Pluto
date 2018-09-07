#include "keyboard.h"
#include "../architecture/ports.h"
#include "../architecture/interrupts.h"
#include "../display/console.h"

char rawbuffer[128] = {0};
char asciibuffer[128] = {0};
unsigned char current_position = 0;
unsigned char *keyboardbuffer = (void *)0;
char *rows[] = {"qwertzuiop", "asdfghjkl", "yxcvbnm"};

void keyboardinit()
{
    printstring("Keyboard initialized");
    setinterrupt(1, keyboardirq);
    current_position = 0;
}

char *strcpy(char *dest, const char *src)
{
    char *temp = dest;
    while (*dest++ = *src++)
        ;
    return temp;
}

void getbuffer()
{
    rawbuffer[current_position] = 0;
    strcpy(asciibuffer, rawbuffer);
    current_position = 0;
}

char *getascii()
{
    getbuffer();
    char key = 0;
    if (asciibuffer[0] == 0)
    {
        return (void *)0;
    }
    for (unsigned char i = 0;; i++)
    {
        key = asciibuffer[i];
        if (key == 0)
        {
            break;
        }
        if (key == 0x1C)
        {
            asciibuffer[i] == '\n';
        }
        else if (key >= 0x10 & key <= 0x1C)
        {
            asciibuffer[i] = rows[0][key - 0x10];
        }
        else if (key >= 0x1E && key <= 0x26)
        {
            asciibuffer[i] = rows[1][key - 0x1E];
        }
        else if (key >= 0x2C && key <= 0x32)
        {
            asciibuffer[i] = rows[2][key - 0x2C];
        }
        else
        {
            asciibuffer[i] = 0;
        }
    }
    return asciibuffer;
}

void keyboardirq()
{
    if ((inportbyte(0x64) & 0x01) && current_position < 128)
    {
        rawbuffer[current_position++] = inportbyte(0x60);
        keyboardbuffer = getascii();
        if (keyboardbuffer[0] != 0)
        {
            printstring(keyboardbuffer);
            keyboardbuffer[0] = 0;
        }
    }
}