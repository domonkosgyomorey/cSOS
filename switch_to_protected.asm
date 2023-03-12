[bits 16]
switch_to_protected:
	cli ; clear the interrupt flags
	lgdt [gdt_descriptor] ; load the gdt
	mov eax, cr0 ; set cr0 (control register) to 1, for protected mode
	or eax, 0x1
	mov cr0, eax
	jmp CODE_SEGMENT:init_32bit ; far jump to the right segment

[bits 32]
init_32bit:
; setup all the segment register to the data segment
	mov ax, DATA_SEGMENT
	mov ds, ax
	mov ss, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
; setup the stack
	mov ebp, 0x80000
	mov esp, ebp

call begin_protected