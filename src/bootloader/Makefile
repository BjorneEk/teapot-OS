# $@ = target file
# $< = first dependency
# $^ = all dependencies

ASSEMBLER = nasm
VM = qemu-system-x86_64

FLAGS = -f bin -g
SOURCES = $(wildcard src/*.S src/*.s src/*.asm)

boot.bin: $(SOURCES)
	$(ASSEMBLER) $(FLAGS) $^ -o $@

launch: boot.bin
	$(VM) $^
	
clean:
	$(RM) *.bin
