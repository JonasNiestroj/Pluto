%macro isr 1
    GLOBAL isr%1:function
    isr%1:
        push dword 0
        push dword %1
        jmp prepare
%endmacro

%macro isrerror 1
    GLOBAL isr%1:function
    isr%1:
        push dword %1
        jmp prepare
%endmacro

%macro irq 1
    GLOBAL irq%1:function
    irq%1:
        push dword 0
        push dword %1+32
        jmp prepare
%endmacro

; Find better solution
isr 0
isr 1
isr 2
isr 3
isr 4
isr 5
isr 6
isr 7
isrerror 8
isr 9
isrerror 10
isrerror 11
isrerror 12
isrerror 13
isrerror 14
isr 15
isr 16
isrerror 17
isr 18
isr 19
isr 20
isr 21
isr 22
isr 23
isr 24
isr 25
isr 26
isr 27
isr 28
isr 29
isrerror 30
isr 31

irq 0
irq 1
irq 3
irq 4
irq 5
irq 6
irq 7
irq 8
irq 9
irq 10
irq 11
irq 12
irq 13
irq 14
irq 15

extern interruptrelay

prepare:
    cld

; Save registers
    push eax
    push ecx
    push edx
    push ebx
    push ebp
    push esi
    push edi
    push ds
    push es
    push fs
    push gs

    mov ebp, 0x10
    mov ds, ebp
    mov es, ebp
    mov fs, ebp
    mov gs, ebp

    mov ebp, cr2
    push ebp

    mov ebx, esp
    sub esp, 4
    and esp, 0xFFFFFFF0
    mov [esp], ebx
    call interruptrelay
    mov esp, ebx
    pop ebp
    mov cr2, ebp

    ; Load registers
    pop gs
    pop fs
    pop es
    pop ds
    pop edi
    pop esi
    pop ebp
    pop ebx
    pop edx
    pop ecx
    pop eax

    add esp, 8
    iret