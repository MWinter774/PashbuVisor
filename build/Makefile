.PHONY: all clean

SOURCE_FOLDER=./src

# Assmebler settings
ASSEMBLER=nasm
ASSEMBLER_INCLUDE_FOLDER=./include
ASSEMBLER_FLAGS=-fbin -i$(ASSEMBLER_INCLUDE_FOLDER)

COMPILER=i686-elf-gcc
COMPILER_INCLUDE_FOLDER=./include
COMPILER_FLAGS=-ffreestanding

LINKER=i686-elf-ld
LINKER_FLAGS=-Ttext 0x1000 --oformat binary

# Output file name
OUTPUT_DIR=./out

all: _all
clean:
	rm -rf $(OUTPUT_DIR)

_all: $(OUTPUT_DIR)/os-image.bin

$(OUTPUT_DIR)/os-image.bin: $(OUTPUT_DIR)/bootsector.bin $(OUTPUT_DIR)/kernel.bin
	cat $^ > $@

$(OUTPUT_DIR)/bootsector.bin: $(SOURCE_FOLDER)/bootsector.asm
	$(ASSEMBLER) $(ASSEMBLER_FLAGS) $^ -o $@

$(OUTPUT_DIR)/kernel.bin: $(OUTPUT_DIR)/kernel.o
	$(LINKER) $(LINKER_FLAGS) $^ -o $@

$(OUTPUT_DIR)/kernel.o: $(SOURCE_FOLDER)/kernel.c
	$(COMPILER) $(COMPILER_FLAGS) -c $^ -o $@

