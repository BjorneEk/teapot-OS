# $@ = target file
# $< = first dependency
# $^ = all dependencies

TARGET = teapot-os.bin
MBR = boot.bin

CC = x86_64-elf-gcc
ASMBLR = nasm
LNKR = x86_64-elf-ld
VM = qemu-system-i386

C_FLAGS = -g -m32 -ffreestanding -c -Wall
LNKR_FLAGS = -m elf_i386

HEADERS = $(wildcard src/kernel/drivers/include/*.h src/kernel/libc/include/*.h src/kernel/graphics/*.h src/kernel/cpu/*.h src/kernel/lin-alg/*.h)
BOOT_SOURCES = $(wildcard src/bootloader/*.S)
C_SOURCES = $(wildcard src/kernel/*.c src/kernel/drivers/lib/*.c src/kernel/libc/lib/*.c src/kernel/graphics/*.c src/kernel/cpu/*.c src/kernel/lin-alg/*.c src/kernel/objects/*.c)
OBJ = ${C_SOURCES:.c=.o src/kernel/cpu/interrupt.o}

# First rule is the one executed when no parameters are fed to the Makefile
all: run

kernel.bin: src/bootloader/kernel-entry.o $(OBJ)
	$(LNKR) $(LNKR_FLAGS) -o $@ -Ttext 0x9000 $^ --oformat binary

%.o: %.S
	$(ASMBLR) $< -f elf -o $@

%.o: %.c ${HEADERS}
	$(CC) $(C_FLAGS) $< -o $@

# only for debug
kernel.elf: src/bootloader/kernel-entry.o $(OBJ)
	$(LNKR) $(LNKR_FLAGS) -o $@ -Ttext 0x1000 $^

debug: $(TARGET) kernel.elf
	$(VM) -s -S -fda $(TARGET) -d guest_errors,int &
	i386-elf-gdb -ex "target remote localhost:1234" -ex "symbol-file kernel.elf"

$(MBR): src/bootloader/boot.S
	$(ASMBLR) $< -f bin -o $@

$(TARGET): $(MBR) kernel.bin
	cat $^ > $@

run: $(TARGET)
	$(VM) -fda $<

clean:
	$(RM) *.bin
	$(RM) *.o *.dis .*.swp
	$(RM) src/bootloader/*.bin src/bootloader/*.o src/bootloader/.*.swp
	$(RM) src/kernel/*.bin src/kernel/*.o src/kernel/.*.swp
	$(RM) src/kernel/drivers/lib/*.o src/kernel/drivers/lib/.*.swp
	$(RM) src/kernel/libc/lib/*.o src/kernel/libc/lib/*.swp
	$(RM) src/kernel/graphics/*.o src/kernel/graphics/*.swp
	$(RM) src/kernel/cpu/*.o src/kernel/cpu/*.swp
	$(RM) src/kernel/lin-alg/*.o src/kernel/lin-alg/*.swp

cst: #clean but save target
	$(RM) *.o *.dis .*.swp
	$(RM) src/bootloader/*.bin src/bootloader/*.o src/bootloader/.*.swp
	$(RM) src/kernel/*.bin src/kernel/*.o src/kernel/.*.swp
	$(RM) src/kernel/drivers/lib/*.o src/kernel/drivers/lib/.*.swp
	$(RM) src/kernel/libc/lib/*.o src/kernel/libc/lib/*.swp
	$(RM) src/kernel/graphics/*.o src/kernel/graphics/*.swp
	$(RM) src/kernel/cpu/*.o src/kernel/cpu/*.swp
	$(RM) src/kernel/lin-alg/*.o src/kernel/lin-alg/*.swp
