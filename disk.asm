[bits 16]
load_disk:
	pusha
	push dx
	; disk read mode
	mov ah, 0x2
	; read dh number of sector
	mov al, dh
	; start from sector 2, because the bootloader is in the sector 1
	mov cl, 0x2
	; read cylinder 0
	mov ch, 0x0
	; read head 0
	mov dh, 0x0
	int 0x13
	; if the interrupt has an error the carry flag become 1
	jc disk_error
	; load back the number of sectors
	pop dx
	; the BIOS set the al, how many sector was read
	; and compare it with our number what we want to read
	cmp al, dh
	jne disk_sectors_error
	popa
	ret

disk_error:
	jmp disk_loop

disk_sectors_error:
	jmp disk_loop

disk_loop:
	jmp $