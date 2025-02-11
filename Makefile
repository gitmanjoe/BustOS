# Compiler and Assembler
CC = gcc
ASM = nasm
LD = ld
OBJCOPY = objcopy
QEMU = "C:\\Program Files\\qemu\\qemu-system-x86_64.exe"

# Flags
CFLAGS = -m32 -ffreestanding
ASMFLAGS = -f bin
LDFLAGS = -T NUL -mi386pe -Ttext 0x7e00

# Source and Object Files
C_SOURCES = kernel.c screen.c games.c cursor.c ports.c tools.c interrupts/idt.c interrupts/isr.c
C_OBJECTS = $(C_SOURCES:.c=.o)

# Output Files
BOOTLOADER_BIN = bootloader.bin
KERNEL_BIN = kernel.bin
OS_IMAGE = BustOS.img

# Default Target
all: $(OS_IMAGE)

# Assemble Bootloader
$(BOOTLOADER_BIN): bootloader.asm
	$(ASM) $(ASMFLAGS) $< -o $@

# Compile C Files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Link Kernel
$(KERNEL_BIN): $(C_OBJECTS)
	$(LD) $(LDFLAGS) -o kernel.tmp $(C_OBJECTS)
	$(OBJCOPY) -O binary -j .text kernel.tmp $(KERNEL_BIN)

# Create OS Image
$(OS_IMAGE): $(BOOTLOADER_BIN) $(KERNEL_BIN)
	cat $(BOOTLOADER_BIN) $(KERNEL_BIN) padding.bin > $(OS_IMAGE)

# Clean Build Files
clean:
	rm -f $(OBJECTS) kernel.tmp $(BOOTLOADER_BIN) $(KERNEL_BIN)

# Run in QEMU
run: $(OS_IMAGE)
	$(QEMU) $(OS_IMAGE)
