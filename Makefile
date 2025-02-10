# Define the compiler and assembler
CC = gcc
ASM = nasm

# Define the flags for compiler and assembler
CFLAGS = -m32 -ffreestanding
ASMFLAGS = -f bin

# Define the source and object files
SOURCES = kernel.c screen.c games.c cursor.c ports.c tools.c
OBJECTS = $(SOURCES:.c=.o)
KERNEL_BIN = kernel.bin

# Define the output files
BOOTLOADER_BIN = bootloader.bin
OS_IMAGE = BustOS.img
QEMU = "C:\\Program Files\\qemu\\qemu-system-x86_64.exe"

# Default target
all: $(OS_IMAGE)

$(BOOTLOADER_BIN): bootloader.asm
    $(ASM) $(ASMFLAGS) bootloader.asm -o $(BOOTLOADER_BIN)

$(OBJECTS): %.o: %.c
    $(CC) $(CFLAGS) -c $< -o $@

$(KERNEL_BIN): $(OBJECTS)
    ld -T NUL -mi386pe -o kernel.tmp -Ttext 0x7e00 $(OBJECTS)
    objcopy -O binary -j .text kernel.tmp $(KERNEL_BIN)

$(OS_IMAGE): $(BOOTLOADER_BIN) $(KERNEL_BIN)
    copy /b $(BOOTLOADER_BIN)+$(KERNEL_BIN)+padding.bin $(OS_IMAGE)

# Clean up
clean:
    rm -f *.o *.tmp $(BOOTLOADER_BIN) $(KERNEL_BIN) $(OS_IMAGE)

# Run the OS
run: $(OS_IMAGE)
    $(QEMU) $(OS_IMAGE)
