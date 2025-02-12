# Compiler and Assembler
CC = gcc
ASM = nasm
LD = C:\\i686-elf-tools-windows\\bin\\i686-elf-ld
OBJCOPY = objcopy
QEMU = "C:\\Program Files\\qemu\\qemu-system-x86_64.exe"

# Flags
CFLAGS = -m32 -ffreestanding
ASMFLAGS = -f elf
LDFLAGS = -m elf_i386 -Ttext 0x7e00

# Source Files
C_SOURCES = kernel.c screen.c games.c cursor.c ports.c tools.c interrupts/idt.c interrupts/isr.c
ASM_SOURCES = interrupts/interrupt.asm

# Object Files
C_OBJECTS = $(C_SOURCES:.c=.o)
ASM_OBJECTS = $(ASM_SOURCES:.asm=.o)

# Output Files
BOOTLOADER_BIN = bootloader.bin
KERNEL_BIN = kernel.bin
OS_IMAGE = BustOS.img

# Default Target
all: $(OS_IMAGE)

# Assemble Bootloader
$(BOOTLOADER_BIN): bootloader.asm
	$(ASM) -f bin $< -o $@

# Compile C Files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Compile Assembly Files
%.o: %.asm
	$(ASM) $(ASMFLAGS) $< -o $@

# Link Kernel
$(KERNEL_BIN): $(C_OBJECTS) $(ASM_OBJECTS)
	$(LD) $(LDFLAGS) -o kernel.tmp $(C_OBJECTS) $(ASM_OBJECTS)
	$(OBJCOPY) -O binary -j .text kernel.tmp $(KERNEL_BIN)

# Create OS Image
$(OS_IMAGE): $(BOOTLOADER_BIN) $(KERNEL_BIN)
	cat $(BOOTLOADER_BIN) $(KERNEL_BIN) padding.bin > $(OS_IMAGE)

# Clean Build Files
clean:
	rm -f $(C_OBJECTS) $(ASM_OBJECTS) kernel.tmp $(BOOTLOADER_BIN) $(KERNEL_BIN)

# Run in QEMU
run: $(OS_IMAGE)
	$(QEMU) $(OS_IMAGE)
