#!/bin/bash

# boot3.sh

set -e

nasm -f bin bootloader.asm -o bootloader.bin
gcc -m32 -ffreestanding -c kernel.c -o kernel.o
# objdump -d kernel.o
gcc -m32 -ffreestanding -fno-pic -fno-pie -c kernel.c -o kernel.o
gcc -m32 -ffreestanding -fno-pic -fno-pie -c ports.c -o ports.o
gcc -m32 -ffreestanding -fno-pic -fno-pie -c mem.c -o mem.o
gcc -m32 -ffreestanding -fno-pic -fno-pie -c cursor.c -o cursor.o
gcc -m32 -ffreestanding -fno-pic -fno-pie -c screen.c -o screen.o
gcc -m32 -ffreestanding -fno-pic -fno-pie -c strings.c -o strings.o
gcc -m32 -ffreestanding -fno-pic -fno-pie -c keyboard.c -o keyboard.o
gcc -m32 -ffreestanding -fno-pic -fno-pie -c isr.c -o isr.o
gcc -m32 -ffreestanding -fno-pic -fno-pie -c idt.c -o idt.o
nasm -f elf interrupts.asm -o interrupts.o
ld -Ttext 0x7e00 -m elf_i386 -o kernel.tmp kernel.o ports.o mem.o cursor.o screen.o strings.o keyboard.o isr.o idt.o interrupts.o
objcopy -O binary -j .text kernel.tmp kernel.bin
# ndisasm -b 32 kernel.bin
cat bootloader.bin kernel.bin padding.bin > BustOS.img
# ndisasm -b 32 BustOS.img

if command -v qemu-system-x86_64 &> /dev/null; then
    qemu-system-x86_64 BustOS.img
else
    echo "qemu-system-x86_64 not found in PATH."
    exit 1
fi