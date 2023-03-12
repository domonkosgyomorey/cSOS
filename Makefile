boot: boot.asm
	nasm $< -o $@

run: boot
	qemu-system-i386 $<