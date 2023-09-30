ASM=nasm
ASMFLAGS=-fbin

bootsector:
	$(ASM) $(ASMFLAGS) boot.asm -o boot.bin
