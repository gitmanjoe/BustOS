# Define the compiler and assembler
CC = gcc
ASM = nasm
QEMU = "C:\\Program Files\\qemu\\qemu-system-x86_64.exe"

# Define the flags for compiler and assembler
CFLAGS = -m32 -ffreestanding
ASMFLAGS = -f bin

# Define the source and object files
SOURCES = kernel.c screen.c games.c cursor.c ports.c tools.c
OBJECTS = $(SOURCES:.c=.o)
KERNEL_BIN = kernel.bin
BOOTLOADER_BIN = bootloader.bin
OS_IMAGE = BustOS.img

# Default target
all: $(OS_IMAGE)

# Build bootloader
$(BOOTLOADER_BIN): bootloader.asm
	$(ASM) $(ASMFLAGS) bootloader.asm -o $(BOOTLOADER_BIN)

# Compile C files to object files
$(OBJECTS): %.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Link object files to create kernel
$(KERNEL_BIN): $(OBJECTS)
	ld -T NUL -mi386pe -o kernel.tmp -Ttext 0x7e00 $(OBJECTS)
	objcopy -O binary -j .text kernel.tmp $(KERNEL_BIN)

# Create the final OS image
$(OS_IMAGE): $(BOOTLOADER_BIN) $(KERNEL_BIN)
	cat $(BOOTLOADER_BIN) $(KERNEL_BIN) padding.bin > $(OS_IMAGE)

# Clean up object files, temporary files, and binaries
clean:
	rm -f $(OBJECTS) kernel.tmp $(BOOTLOADER_BIN) $(KERNEL_BIN)

# Run the OS in QEMU
run:
	$(QEMU) $(OS_IMAGE)
