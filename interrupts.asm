; interrupts.asm
; Defined in isr.c
extern isr_handler
extern irq_handler
; Common ISR code
isr_common_stub:
    pusha
    mov ax, ds
    push eax
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    push esp
    call isr_handler
    add esp, 4
    pop eax
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    popa
    add esp, 8
    iret

isr_common_stub_errcode:
    pusha
    mov ax, ds
    push eax
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    push esp
    call isr_handler
    add esp, 4
    pop eax
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    popa
    add esp, 4
    iret

; Common IRQ code. Identical to ISR code except for the 'call'
; and the 'pop ebx'
irq_common_stub:
    ; 1. Save CPU state
    pusha
    mov ax, ds
    push eax
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    
    ; 2. Call C handler
    push esp
    call irq_handler
    add esp, 4
    
    ; 3. Restore state
    pop eax
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    popa
    
    ; 4. Clean up stack
    add esp, 8     ; Remove error code and IRQ number
    iret           ; Return from interrupt

; We don't get information about which interrupt was caller
; when the handler is run, so we will need to have a different handler
; for every interrupt.
; Furthermore, some interrupts push an error code onto the stack but others
; don't, so we will push a dummy error code for those which don't, so that
; we have a consistent stack for all of them.
; First make the ISRs global
global isr0
global isr1
global isr2
global isr3
global isr4
global isr5
global isr6
global isr7
global isr8
global isr9
global isr10
global isr11
global isr12
global isr13
global isr14
global isr15
global isr16
global isr17
global isr18
global isr19
global isr20
global isr21
global isr22
global isr23
global isr24
global isr25
global isr26
global isr27
global isr28
global isr29
global isr30
global isr31
; 0: Divide By Zero Exception
isr0:
    push byte 0
    push byte 0
    jmp isr_common_stub
; 1: Debug Exception
isr1:
    push byte 0
    push byte 1
    jmp isr_common_stub
; 2: Non Maskable Interrupt Exception
isr2:
    push byte 0
    push byte 2
    jmp isr_common_stub
; 3: Int 3 Exception
isr3:
    push byte 0
    push byte 3
    jmp isr_common_stub
; 4: INTO Exception
isr4:
    push byte 0
    push byte 4
    jmp isr_common_stub
; 5: Out of Bounds Exception
isr5:
    push byte 0
    push byte 5
    jmp isr_common_stub
; 6: Invalid Opcode Exception
isr6:
    push byte 0
    push byte 6
    jmp isr_common_stub
; 7: Coprocessor Not Available Exception
isr7:
    push byte 0
    push byte 7
    jmp isr_common_stub
; 8: Double Fault Exception (With Error Code!)
isr8:
    push byte 8
    jmp isr_common_stub_errcode
; 9: Coprocessor Segment Overrun Exception
isr9:
    push byte 0
    push byte 9
    jmp isr_common_stub
; 10: Bad TSS Exception (With Error Code!)
isr10:
    push byte 10
    jmp isr_common_stub_errcode
isr11:
    push byte 11
    jmp isr_common_stub_errcode
isr12:
    push byte 12
    jmp isr_common_stub_errcode
isr13:
    push byte 13
    jmp isr_common_stub_errcode
isr14:
    push byte 14
    jmp isr_common_stub_errcode
; 15: Reserved Exception
isr15:
    push byte 0
    push byte 15
    jmp isr_common_stub
; 16: Floating Point Exception
isr16:
    push byte 0
    push byte 16
    jmp isr_common_stub
; 17: Alignment Check Exception
isr17:
    push byte 0
    push byte 17
    jmp isr_common_stub
; 18: Machine Check Exception
isr18:
    push byte 0
    push byte 18
    jmp isr_common_stub
; 19: Reserved
isr19:
    push byte 0
    push byte 19
    jmp isr_common_stub
; 20: Reserved
isr20:
    push byte 0
    push byte 20
    jmp isr_common_stub
; 21: Reserved
isr21:
    push byte 0
    push byte 21
    jmp isr_common_stub
; 22: Reserved
isr22:
    push byte 0
    push byte 22
    jmp isr_common_stub
; 23: Reserved
isr23:
    push byte 0
    push byte 23
    jmp isr_common_stub
; 24: Reserved
isr24:
    push byte 0
    push byte 24
    jmp isr_common_stub
; 25: Reserved
isr25:
    push byte 0
    push byte 25
    jmp isr_common_stub
; 26: Reserved
isr26:
    push byte 0
    push byte 26
    jmp isr_common_stub
; 27: Reserved
isr27:
    push byte 0
    push byte 27
    jmp isr_common_stub
; 28: Reserved
isr28:
    push byte 0
    push byte 28
    jmp isr_common_stub
; 29: Reserved
isr29:
    push byte 0
    push byte 29
    jmp isr_common_stub
; 30: Reserved
isr30:
    push byte 0
    push byte 30
    jmp isr_common_stub
; 31: Reserved
isr31:
    push byte 0
    push byte 31
    jmp isr_common_stub
; IRQs
global irq0
global irq1
global irq2
global irq3
global irq4
global irq5
global irq6
global irq7
global irq8

global irq9
global irq10
global irq11
global irq12
global irq13
global irq14
global irq15
; IRQ handlers
irq0:
    push byte 0
    push byte 32
    jmp irq_common_stub
irq1:
    push byte 0
    push byte 33
    jmp irq_common_stub
irq2:
    push byte 0
    push byte 34
    jmp irq_common_stub
irq3:
    push byte 0
    push byte 35
    jmp irq_common_stub
irq4:
    push byte 0
    push byte 36
    jmp irq_common_stub
irq5:
    push byte 0
    push byte 37
    jmp irq_common_stub
irq6:
    push byte 0
    push byte 38
    jmp irq_common_stub
irq7:
    push byte 0
    push byte 39
    jmp irq_common_stub
irq8:
    push byte 0
    push byte 40
    jmp irq_common_stub
irq9:
    push byte 0
    push byte 41
    jmp irq_common_stub
irq10:
    push byte 0
    push byte 42
    jmp irq_common_stub
irq11:
    push byte 0
    push byte 43
    jmp irq_common_stub
irq12:
    push byte 0
    push byte 44
    jmp irq_common_stub
irq13:
    push byte 0
    push byte 45
    jmp irq_common_stub
irq14:
    push byte 0
    push byte 46
    jmp irq_common_stub
irq15:
    push byte 0
    push byte 47
    jmp irq_common_stub