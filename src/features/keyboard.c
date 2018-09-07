#include "keyboard.h"
#include "../architecture/ports.h"
#include "../architecture/interrupts.h"
#include "../display/console.h"

char rawbuffer[128] = {0};
char asciibuffer[128] = {0};
unsigned char current_position = 0;
unsigned char *keyboardbuffer = (void *)0;
char *lowercaserows[] = {"qwertzuiop", "asdfghjkl", "yxcvbnm"};
char *uppercaserows[] = {"QWERTZUIOP", "ASDFGHJKL", "YXCVBNM"};
unsigned char caps = 0;
unsigned char shift = 0;

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
        // Capslock
        if (key == 0x3A)
        {
            if (caps == 0)
            {
                caps = 1;
            }
            else
            {
                caps = 0;
            }
        }
        // Enter key
        else if (key == 0x1C)
        {
            asciibuffer[i] = '\n';
        }
        // Space
        else if (key == 0x39)
        {
            asciibuffer[i] = ' ';
        }
        else if (key >= 0x10 & key <= 0x19)
        {
            if (caps == 0)
            {
                asciibuffer[i] = lowercaserows[0][key - 0x10];
            }
            else
            {
                asciibuffer[i] = uppercaserows[0][key - 0x10];
            }
        }
        else if (key >= 0x1E && key <= 0x26)
        {
            if (caps == 0)
            {
                asciibuffer[i] = lowercaserows[1][key - 0x1E];
            }
            else
            {
                asciibuffer[i] = uppercaserows[1][key - 0x1E];
            }
        }
        else if (key >= 0x2C && key <= 0x32)
        {
            if (caps == 0)
            {
                asciibuffer[i] = lowercaserows[2][key - 0x2C];
            }
            else
            {
                asciibuffer[i] = uppercaserows[2][key - 0x2C];
            }
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