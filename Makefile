ASM=nasm
ASMFLAGS=-fbin

OUTDIR=out

all: bootsector

bootsector:
	mkdir -p $(OUTDIR)
	$(ASM) $(ASMFLAGS) boot.asm -o $(OUTDIR)/boot.bin

clean:
	rm -rf $(OUTDIR)
