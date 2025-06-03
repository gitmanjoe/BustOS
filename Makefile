# Detect OS
ifeq ($(OS),Windows_NT)
    RM = rm -f
    COPY = copy /b
    CAT = type
    LD = ld
    OBJCPY = objcopy
    QEMU = qemu-system-x86_64
    NULLDEV = NUL
    SEP = &
    LDFLAGS = -Ttext 0x7e00 -m i386pe --kill-at
    ASMFLAGS_ELF = -f win32 -dWINDOWS
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
    ASMFLAGS_ELF = -f elf
endif

# Tools
CC = gcc
ASM = nasm

# Flags
CFLAGS = -m32 -ffreestanding -fno-pic -fno-pie
ASMFLAGS_BIN = -f bin

# Sources
C_SOURCES = kernel.c ports.c cursor.c screen.c strings.c keyboard.c isr.c idt.c games.c hardware.c tools.c timer.c
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

# Ensure interrupts.asm exports required symbols
interrupts.o: interrupts.asm
	$(ASM) $(ASMFLAGS_ELF) $< -o $@

# Link all object files
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
	$(RM) $(C_OBJECTS) $(ASM_OBJECTS)

clean:
	$(RM) $(C_OBJECTS) $(ASM_OBJECTS) $(KERNEL_TMP) $(BOOTLOADER_BIN) $(KERNEL_BIN) $(OS_IMAGE)

run: $(OS_IMAGE)
	$(QEMU) -audiodev sdl,id=speaker -machine pcspk-audiodev=speaker -drive file=$(OS_IMAGE),format=raw,index=0,media=disk
