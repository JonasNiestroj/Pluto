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
extern tss
GLOBAL _main

_main:
    cli ; clean interrupts
    mov esp, kernel_stack

    mov ecx, tss
    mov [gdt + 0x28 + 2], cx
    shr ecx, 16
    mov [gdt + 0x28 + 4], cl
    shr ecx, 8
    mov [gdt + 0x28 + 7], cl

    ; Load GDT
    sub esp, 6
    mov cx, [gdtsize]
    mov [esp+0], cx
    mov ecx, gdt
    mov [esp+2], ecx
    lgdt [esp]
    add esp, 6
    jmp 0x08:l1
    
l1:
    mov cx, 0x10
    mov ds, cx
    mov es, cx
    mov fs, cx
    mov gs, cx
    mov ss, cx

    mov cx, (0x28|0x3)
    ltr cx

    call kernel_main ;call our kernel main

_loop:
    cli
    hlt
    jmp _loop

SECTION .bss:
    RESB 64*1024 ;Our kernel gets 64KB stack

kernel_stack:
