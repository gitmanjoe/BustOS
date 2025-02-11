[bits 32]
global load_idt    ; Export load_idt for linking

load_idt:
    mov eax, [esp+4]  ; Load the pointer from stack
    lidt [eax]        ; Load the IDT
    ret
