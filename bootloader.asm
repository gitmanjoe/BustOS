; boatloader4.asm
; prints character to the screen using a function
; generate 16 bit code code
bits 16
; lood bootloader at this address 0x7c00
; hence offsets should be calculated in relation to this address
org 0x7c00

print_loop:
mov al,'?'
call print_char
jmp print_loop



print_char:
    mov ah,0x0e ; BIOS teletype output
    push bp
    int 0x10 ; print the character in al
    pop bp
    ret

times 510 - ($-$$) db 0
dw 0xaa55

