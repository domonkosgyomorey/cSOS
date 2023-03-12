[bits 16]
[org 0x7c00]

mov bp, 0x8000
mov sp, bp

jmp $

times 510-($-$$) db 0
dw 0xaa55