ALIGNFG equ 1<<0
MEMINFOFG equ 1<<1
FLAGSFG equ ALIGNFG|MEMINFOFG
MAGICFG equ 0x1BADB002
CHECKSUMFG equ -(MAGICFG + FLAGSFG)

SECTION .multiboot
ALIGN 4
    dd MAGICFG
    dd FLAGSFG
    dd CHECKSUMFG

SECTION .text
extern kernel_main
GLOBAL _main


_main:
    cli ; clear all interupts

    mov esp, kernel_stack
    call kernel_main ;call our kernel main
    jmp _loop

_loop:
    hlt
    jmp _loop

SECTION .bss:
    RESB 64*1024 ;Our kernel gets 64KB stack

kernel_stack:
