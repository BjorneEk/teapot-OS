# $@ = target file
# $< = first dependency
# $^ = all dependencies

TARGET = teapot-os.bin
MBR = boot.bin

CC = x86_64-elf-gcc
ASMBLR = nasm
LNKR = x86_64-elf-ld
VM = qemu-system-i386

C_FLAGS = -g -m32 -ffreestanding -c
LNKR_FLAGS = -m elf_i386

HEADERS = $(wildcard src/kernel/*.h)
BOOT_SOURCES = $(wildcard src/bootloader/*.S)
C_SOURCES = $(wildcard src/kernel/*.c src/kernel/drivers/lib/*.c)
OBJ = ${C_SOURCES:.c=.o}

# First rule is the one executed when no parameters are fed to the Makefile
all: run

kernel.bin: src/bootloader/kernel-entry.o $(OBJ)
	$(LNKR) $(LNKR_FLAGS) -o $@ -Ttext 0x1000 $^ --oformat binary

%.o: %.S
	$(ASMBLR) $< -f elf -o $@

%.o: %.c ${HEADERS}
	$(CC) $(C_FLAGS) $< -o $@

$(MBR): src/bootloader/boot.S
	$(ASMBLR) $< -f bin -o $@

$(TARGET): $(MBR) kernel.bin
	cat $^ > $@

run: $(TARGET)
	$(VM) -fda $<

clean:
	$(RM) *.bin *.o *.dis .*.swp
	$(RM) src/bootloader/*.bin src/bootloader/*.o src/bootloader/.*.swp
	$(RM) src/kernel/*.bin src/kernel/*.o src/kernel/.*.swp
	$(RM) src/kernel/drivers/lib/*.o src/kernel/drivers/lib/.*.swp
