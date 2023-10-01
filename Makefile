ASM=nasm
ASMFLAGS=-fbin

OUTDIR=out

all: bootsector

bootsector:
	mkdir -p $(OUTDIR)
	$(ASM) $(ASMFLAGS) bootsector.asm -o $(OUTDIR)/bootsector.bin

clean:
	rm -rf $(OUTDIR)
