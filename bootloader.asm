; boatloader4.asm
; prints character to the screen using a function
; generate 16 bit code code
bits 16
; lood bootloader at this address 0x7c00
; hence offsets should be calculated in relation to this address
org 0x7c00

mov bx, Welcome_Msg
call print_string
jmp $

print_char:
    mov ah,0x0e ; BIOS teletype output
    push bp
    int 0x10 ; print the character in al
    pop bp
    ret
print_string:
    pusha ; save register ax
    mov ah,0x0e ; BIOS teletype output
print_string_loop:
    mov al,[bx] ; Store the char at EBX in AL
    cmp al,0 ; end of string?
    je done ; jump to done
    call print_char ; print char to screen
    add bx,1 ; Increment BX to the next char in string.
    jmp print_string_loop ; loop to print the next char.
done:
    popa ; restore register ax
    ret
    
; Data
Welcome_Msg:
db 'Welcome to the OsX Operating System',13,10,0 ;

times 510 - ($-$$) db 0
dw 0xaa55

