[bits 32]
global keyboard_isr

extern keyboard_handler  ; The C function to handle keyboard input

keyboard_isr:
    pusha              ; Save registers
    call keyboard_handler  ; Call the C function
    mov al, 0x20
    out 0x20, al       ; Send EOI (End of Interrupt) to PIC
    popa               ; Restore registers
    iretd              ; Return from interrupt
