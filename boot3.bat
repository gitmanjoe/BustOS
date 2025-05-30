rem boot3.bat
nasm -f bin bootloader.asm -o bootloader.bin
gcc -m32 -ffreestanding -c kernel.c -o kernel.o
rem objdump -d kernel.o
gcc -m32 -ffreestanding -c ports.c -o ports.o
gcc -m32 -ffreestanding -c cursor.c -o cursor.o
gcc -m32 -ffreestanding -c screen.c -o screen.o
gcc -m32 -ffreestanding -c strings.c -o strings.o
gcc -m32 -ffreestanding -c keyboard.c -o keyboard.o
gcc -m32 -ffreestanding -c isr.c -o isr.o
gcc -m32 -ffreestanding -c idt.c -o idt.o
gcc -m32 -ffreestanding -c hardware.c -o hardware.o
gcc -m32 -ffreestanding -c tools.c -o tools.o
gcc -m32 -ffreestanding -c games.c -o games.o
gcc -m32 -ffreestanding -c hardware.c -o hardware.o
nasm -f elf interrupts.asm -o interrupts.o
ld -T NUL -m i386pe -o kernel.tmp -Ttext 0x7e00 interrupts.o kernel.o ports.o tools.o cursor.o screen.o strings.o keyboard.o isr.o idt.o games.o hardware.o
objcopy -O binary -j .text kernel.tmp kernel.bin
rem "C:\Program Files\nasm\ndisasm" -b 32 kernel.bin
copy /b bootloader.bin+kernel.bin+padding.bin BustOS.img
rem "C:\Program Files\nasm\ndisasm" -b 32 BustOS.img
"C:\Program Files\qemu\qemu-system-x86_64.exe" BustOS.img
IF %ERRORLEVEL% NEQ 0 (C:\msys64\ucrt64\bin\qemu-system-x86_64.exe BustOS.img)