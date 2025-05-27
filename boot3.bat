rem boot3.bat
"C:\Program Files\nasm\nasm" -f bin bootloader.asm -o bootloader.bin
gcc -m32 -ffreestanding -c kernel.c -o kernel.o
rem objdump -d kernel.o
gcc -m32 -ffreestanding -c ports.c -o ports.o
gcc -m32 -ffreestanding -c mem.c -o men.o
gcc -m32 -ffreestanding -c screen.c -o screen.o
gcc -m32 -ffreestanding -c strings.c -o strings.o
gcc -m32 -ffreestanding -c keyboard.c -o keyboard.o
gcc -m32 -ffreestanding -c isr.c -o isr.o
gcc -m32 -ffreestanding -c idt.c -o idt.o
"C:\Program Files\nasm\nasm" -f elf interrupts.asm -o interrupts.o
ld -T NUL -m i386pe -o kernel.tmp -Ttext 0x7e00 kernel.o ports.o mem.o screen.o strings.o 
keyboard.o isr.o idt.o interrupts.o
objcopy -O binary -j .text kernel.tmp kernel.bin
rem "C:\Program Files\nasm\ndisasm" -b 32 kernel.bin
copy /b bootloader.bin+kernel.bin+padding.bin osximage.img
rem "C:\Program Files\nasm\ndisasm" -b 32 osximage.img
"C:\Program Files\qemu\qemu-system-x86_64.exe" osximage.img