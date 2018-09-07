#include "../display/console.h"
#include "../architecture/gdt.h"
#include "../architecture/idt.h"
#include "../features/keyboard.h"
#include "../architecture/interrupts.h"
#include "../architecture/pic.h"

extern struct gdtentry gdt[];

void kernel_main()
{

    printstring("hello world");

    idtinit();

    interruptinit();

    picinit();

    keyboardinit();

    // enable interrupts
    __asm__("sti" ::);

    // infinite while loop
    while (1)
        ;

    return;
}