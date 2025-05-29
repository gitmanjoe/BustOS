# Detect OS
ifeq ($(OS),Windows_NT)
	RM = del /Q
	COPY = copy /b
	CAT = type
	LD = ld
	OBJCPY = objcopy
	QEMU = qemu-system-x86_64
	NULLDEV = NUL
	SEP = &
	LDFLAGS = -Ttext 0x7e00 -m elf_i386
else
	RM = rm -f
	COPY = cat
	CAT = cat
	LD = ld
	OBJCPY = objcopy
	QEMU = qemu-system-x86_64
	NULLDEV = /dev/null
	SEP = ;
	LDFLAGS = -Ttext 0x7e00 -m elf_i386
endif

# Tools
CC = gcc
ASM = nasm

# Flags
CFLAGS = -m32 -ffreestanding -fno-pic -fno-pie
ASMFLAGS_BIN = -f bin
ASMFLAGS_ELF = -f elf

# Sources
C_SOURCES = kernel.c ports.c mem.c cursor.c screen.c strings.c keyboard.c isr.c idt.c games.c
ASM_SOURCES = interrupts.asm
BOOTLOADER_SRC = bootloader.asm

# Objects
C_OBJECTS = $(C_SOURCES:.c=.o)
ASM_OBJECTS = interrupts.o

# Outputs
BOOTLOADER_BIN = bootloader.bin
KERNEL_BIN = kernel.bin
KERNEL_TMP = kernel.tmp
OS_IMAGE = BustOS.img
PADDING = padding.bin

all: $(OS_IMAGE)

$(BOOTLOADER_BIN): $(BOOTLOADER_SRC)
	$(ASM) $(ASMFLAGS_BIN) $< -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

interrupts.o: interrupts.asm
	$(ASM) $(ASMFLAGS_ELF) $< -o $@

$(KERNEL_TMP): $(C_OBJECTS) $(ASM_OBJECTS)
	$(LD) $(LDFLAGS) -o $@ $(C_OBJECTS) $(ASM_OBJECTS)

$(KERNEL_BIN): $(KERNEL_TMP)
	$(OBJCPY) -O binary -j .text -j .data -j .rodata $< $@

$(OS_IMAGE): $(BOOTLOADER_BIN) $(KERNEL_BIN) $(PADDING)
ifeq ($(OS),Windows_NT)
	$(COPY) $(BOOTLOADER_BIN)+$(KERNEL_BIN)+$(PADDING) $(OS_IMAGE)
else
	$(CAT) $(BOOTLOADER_BIN) $(KERNEL_BIN) $(PADDING) > $(OS_IMAGE)
endif

clean:
	$(RM) $(C_OBJECTS) $(ASM_OBJECTS) $(KERNEL_TMP) $(BOOTLOADER_BIN) $(KERNEL_BIN) $(OS_IMAGE)

run: $(OS_IMAGE)
	$(QEMU) $(OS_IMAGE)
