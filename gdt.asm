[bits 16]

; this GDT (global descriptor table)
; using the flat memory model


; help to calculate the size of gdt
gdt_start:
	dq 0x0

gdt_code:
	; segment length
	dw 0xffff
	; segment location 0-15
 	dw 0x0
 	; nothing set for 0-15

 	; segment location 16-23
	db 0x0
	; flags (8 bits)
	db 10011010b 
	; other flags (4 bits) + segment length
	db 11001111b
	; segment location 24-31 
	db 0x0

gdt_data:
	dw 0xffff
	dw 0x0
	db 0x0
	db 10010010b
	db 11001111b
	db 0x0

; help for calculate GDT size
gdt_end:

gdt_descriptor:
	; size (16 bit)
	dw gdt_end-gdt_start-1
	; GDT start address (32 bit)
	dd gdt_start

CODE_SEGMENT equ gdt_code - gdt_start
DATA_SEGMENT equ gdt_data - gdt_start