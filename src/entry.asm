%include "protected_mode.asm"

[org 0x7c00] ; bootloader offset
mov bp, 0x9000 ; set the stack
mov sp, bp

call switch_to_protected_mode
jmp $ ; this will actually never be executed

; bootsector
times 510-($-$$) db 0
dw 0xaa55

