#include "../display/console.h"
#include "../architecture/gdt.h"
#include "../architecture/idt.h"

extern struct gdtentry gdt[];

void kernel_main()
{
    printstring("hello world");

    idtinit();

    return;
}