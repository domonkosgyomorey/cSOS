[bits 16]
[org 0x7c00]

; kernel loading address
KERNEL_LOC equ 0x1000

; BIOS store the current boot drive number in dl
; store that number for later in BOOT_DRIVE
mov [BOOT_DRIVE], dl

; setup the stack base, and top pointer
mov bp, 0x8000
mov sp, bp

call load_kernel
call switch_to_protected

jmp $

%include "disk.asm"
%include "gdt.asm"
%include "switch_to_protected.asm"

[bits 16]
load_kernel:
; load kernel from disk
	mov bx, KERNEL_LOC ; load kernel into KERNEL_LOC
	mov dh, 0x2 ; load 2 sector
	mov dl, [BOOT_DRIVE] ; load from this drive
	call load_disk
	ret

[bits 32]
begin_protected:
	call KERNEL_LOC
	jmp $

; store the boot drive number
BOOT_DRIVE db 0

; fill the remaring space with 0
times 510-($-$$) db 0

; magic number for BIOS
dw 0xaa55