ASM=nasm
ASMFLAGS=-felf64


OUTDIR=out
SRCDIR=src
BUILDDIR=build

LD=ld
LDFLAGS=-n -T $(BUILDDIR)/linker.ld

all: multiboot2_header boot
	$(LD) $(LDFLAGS) $(OUTDIR)/multiboot2_header.o $(OUTDIR)/boot.o -o $(OUTDIR)/PashbuVisor.bin

multiboot2_header:
	mkdir -p $(OUTDIR)
	$(ASM) $(ASMFLAGS) $(SRCDIR)/multiboot2_header.asm -o $(OUTDIR)/multiboot2_header.o

boot:
	mkdir -p $(OUTDIR)
	$(ASM) $(ASMFLAGS) $(SRCDIR)/boot.asm -o $(OUTDIR)/boot.o

clean:
	rm -rf $(OUTDIR)
