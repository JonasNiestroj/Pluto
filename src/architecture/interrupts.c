#include "interrupts.h"
#include "pic.h"

static void (*interrupthandler[16])();

void interruptinit()
{
    // Set every position to null
    for (unsigned char i = 0; i < 16; i++)
    {
        interrupthandler[i] = (void *)0;
    }
    return;
}

void setinterrupt(unsigned char interruptnumber, void (*handler)())
{
    interrupthandler[interruptnumber] = handler;
    return;
}

void interruptrelay(interruptstruct *irt)
{
    if (irt->int_no < 32)
    {
        // ISRs
        if (interrupthandler[irt->int_no] != (void *)0)
        {
            print('b');
            interrupthandler[irt->int_no]();
        }
    }
    else
    {
        // IRQs
        if (irt->int_no - 32 == 7 && !(picgetisr() & (1 << 7)))
        {
            return;
        }

        if (irt->int_no - 32 == 15 && !(picgetisr() & (1 << 15)))
        {
            return;
        }
        if (interrupthandler[irt->int_no - 32] != (void *)0)
        {
            interrupthandler[irt->int_no - 32]();
        }

        if (irt->int_no > 7)
        {
            picendslave();
        }
        picendmaster();
    }

    return;
}