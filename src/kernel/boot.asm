global start

section .text
bits 32

%include "src/kernel/check_functions.asm"
%include "src/kernel/paging.asm"

start:
    mov esp, stack_top

    call check_multiboot
    call check_cpuid
    call check_long_mode

    call set_up_page_tables
    call enable_paging

    ; print `OK` to screen
    mov dword [0xb8000], 0x2f4b2f4f

    hlt

section .bss
align 4096
p4_table:
    resb 4096
p3_table:
    resb 4096
p2_table:
    resb 4096
stack_bottom:
    resb 64
stack_top:
