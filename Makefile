all: run clean

kernel.bin: kernel_entry.o kernel.o
	ld -m elf_i386 -o $@ -Ttext 0x1000 $^ --oformat binary

kernel_entry.o: kernel_entry.asm
	nasm $< -f elf -o $@

kernel.o: kernel.c
	gcc -fno-pie -m32 -ffreestanding -Wall -Wextra -c $< -o $@ 

boot.bin: boot.asm
	nasm $< -f bin -o $@

os.bin: boot.bin kernel.bin
	cat $^ > $@

run: os.bin
	qemu-system-i386 -drive file=$<,format=raw,index=0

clean:
	$(RM) *.bin *.o
