ASM=nasm
ASMFLAGS=-felf64

OUTDIR=out
SRCDIR=src
BUILDDIR=build

LD=ld
LINKER_SCRIPT=$(BUILDDIR)/linker.ld
LDFLAGS=-n -T $(LINKER_SCRIPT)

KERNEL=$(OUTDIR)/PashbuVisor.bin
ISO=$(OUTDIR)/PashbuVisor.iso

GRUB_CFG_FILE=$(SRCDIR)/kernel/grub.cfg

KERNEL_SOURCE_FILES := $(wildcard src/kernel/*.asm)
KERNEL_OBJECT_FILES := $(patsubst src/kernel/%.asm, out/kernel/%.o, $(KERNEL_SOURCE_FILES))

.PHONY: all clean run

all: $(ISO)

run: $(ISO)
	@qemu-system-x86_64 $(ISO)

$(ISO): $(KERNEL) $(GRUB_CFG_FILE)
	@mkdir -p $(OUTDIR)/isofiles/boot/grub
	@cp $(GRUB_CFG_FILE) $(OUTDIR)/isofiles/boot/grub/
	@cp $(KERNEL) $(OUTDIR)/isofiles/boot/
	@grub-mkrescue -o $(ISO) $(OUTDIR)/isofiles 2> /dev/null

$(KERNEL): $(KERNEL_OBJECT_FILES) $(LINKER_SCRIPT)
	@mkdir -p $(shell dirname $@)
	$(LD) $(LDFLAGS) $(KERNEL_OBJECT_FILES) -o $(KERNEL)

out/%.o: src/%.asm
	@mkdir -p $(shell dirname $@)
	$(ASM) $(ASMFLAGS) $< -o $@

clean:
	rm -rf $(OUTDIR)
