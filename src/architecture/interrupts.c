#include "interrupts.h"

static void (*interrupthandler[16])();

void interruptinit()
{
    // Set every position to null
    for (unsigned char i = 0; i < 16; i++)
    {
        interrupthandler[i] = (void *)0;
    }
}

void setinterrupt(unsigned char interruptnumber, void (*handler)())
{
    interrupthandler[interruptnumber] = handler;
}

void interruptrelay(interruptstruct *interrupt)
{
    if (interrupt->int_no > 31 && interrupt->int_no < 48)
    {
        // IRQs
        if (interrupthandler[interrupt->int_no - 32] != (void *)0)
        {
            interrupthandler[interrupt->int_no - 32]();
        }
    }
    else
    {
        // ISRs
        if (interrupthandler[interrupt->int_no] != (void *)0)
        {
            interrupthandler[interrupt->int_no]();
        }
    }
}