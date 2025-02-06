; boatloader.asm
bits 16
org 0x7c00

mov bx, Real_Msg
call print_string
mov ax, 0x0000
mov ds, ax
mov cx, 100
jmp $

; Data
Real_Msg:
db 'BustOS is in 16 bit Real Mode',13,10,0 

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
    mov al,[bx] 
    cmp al,0 ; end of string?
    je done ; jump to done
    call print_char ; print char to screen
    add bx,1 ; Increment BX to the next char in string.
    jmp print_string_loop ; loop to print the next char.

done:
    popa ; restore register ax
    ret

print_crlf:
    mov al,13
    call print_char
    mov al,10
    call print_char
    ret
print_hex_digit:
    and al,0xF ; hex digit we want to print
    add al,'0' ; convert it into a character..
    cmp al,'9' ; test if hex letter
    jbe decimal ; is digits 0 -9
    add al,7 ; convert to 'A'-'F')
decimal:
    call print_char ; ptint hex digit
    ret
print_hex:
    push ax ; store reisters
    push cx
    push dx
    mov cx,4 ; print 4 hex digits (= 16 bits)
print_hex_loop:
    rol ax,4 ; move into the least significant 4 bits
    push ax ; save ax
    call print_hex_digit
    pop ax ; restore ax
    loop print_hex_loop
    pop dx ; restore registers
    pop cx
    pop ax
    ret
; GDT
gdt_start :
    dq 0x0000000000000000
    dq 0x00CF9A000000FFFF
    dq 0x00CF92000000FFFF
gdt_end :
gdt_descriptor :
    dw gdt_end - gdt_start - 1 ; Size of our GDT 
    dd gdt_start ; Start address of our GDT

times 510 - ($-$$) db 0
dw 0xaa55

