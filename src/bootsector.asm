[org 0x7c00] ; bootloader offset
KERNEL_OFFSET equ 0x1000
    mov [BOOT_DRIVE], dl
    mov bp, 0x9000 ; set the stack
    mov sp, bp

    call load_kernel
    call switch_to_protected_mode
    jmp entry

%include "bootsector_disk_load.asm"
%include "protected_mode.asm"

[bits 16]
load_kernel:
    mov bx, KERNEL_OFFSET
    mov dh, 2
    mov dl, [BOOT_DRIVE]
    call disk_load
    ret

[bits 32]
entry:
    call KERNEL_OFFSET
    jmp $

BOOT_DRIVE db 0

; bootsector
times 510-($-$$) db 0
dw 0xaa55

