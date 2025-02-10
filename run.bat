nasm -f bin bootloader.asm -o bootloader.bin
gcc -m32 -ffreestanding -c kernel.c -o kernel.o
gcc -m32 -ffreestanding -c screen.c -o screen.o
gcc -m32 -ffreestanding -c games.c -o games.o
gcc -m32 -ffreestanding -c cursor.c -o cursor.o
gcc -m32 -ffreestanding -c ports.c -o ports.o
gcc -m32 -ffreestanding -c tools.c -o tools.o
ld -T NUL -mi386pe -o kernel.tmp -Ttext 0x7e00 kernel.o screen.o games.o cursor.o ports.o tools.o
objcopy -O binary -j .text kernel.tmp kernel.bin
copy /b bootloader.bin+kernel.bin+padding.bin BustOS.img
rm *.o
"C:\Program Files\qemu\qemu-system-x86_64.exe" BustOS.img