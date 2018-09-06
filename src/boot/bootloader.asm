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
extern gdtsize
extern gdt
GLOBAL _main

_main:
    cli ; clean interrupts
    mov esp, kernel_stack

    ; Load GDT
    sub esp, 6
    mov cx, [gdtsize]
    mov [esp+0], cx
    mov ecx, gdt
    mov [esp+2], ecx
    lgdt [esp]
    add esp, 6
    
    mov cx, 0x10
    mov ds, cx
    mov es, cx
    mov fs, cx
    mov gs, cx
    mov ss, cx

    call kernel_main ;call our kernel main
    jmp _loop

_loop:
    hlt
    jmp _loop

SECTION .bss:
    RESB 64*1024 ;Our kernel gets 64KB stack

kernel_stack:
