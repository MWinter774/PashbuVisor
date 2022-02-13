.PHONY: all clean

# Destination paths
OUTPUT_FOLDER = ./out
SOURCE_FOLDER = ./src

# Finds all .c files in the source folder.
# Each element in this list will look like this: ./src/subfolder/.../file.c
C_SOURCES = $(shell find $(SOURCE_FOLDER) -name *.c)

# Creates a list of the object files needed to be created from the C_SOURCES files.
# It's created by replacing the $(SOURCE_FOLDER) part of the path in the C_SOURCES and the .c suffix
# with $(OUTPUT_FOLDER) and .o of the c file, accordingly.
C_OBJECT_FILES := $(subst $(SOURCE_FOLDER), $(OUTPUT_FOLDER), $(C_SOURCES:%.c=%.o))

# Assmebler settings
ASSEMBLER=nasm
ASSEMBLER_INCLUDE_FOLDER=./include
ASSEMBLER_FLAGS_FOR_BOOTSECTOR=-fbin -i$(ASSEMBLER_INCLUDE_FOLDER)
ASSEMBLER_FLAGS=-felf -i$(ASSEMBLER_INCLUDE_FOLDER)

# Compiler settings
COMPILER=i686-elf-gcc
COMPILER_INCLUDE_FOLDER=./include
COMPILER_FLAGS=-ffreestanding -I$(COMPILER_INCLUDE_FOLDER)

# Linker settings
LINKER=i686-elf-ld
LINKER_FLAGS=-Ttext 0x1000 --oformat binary

all: _all
clean:
	rm -rf $(OUTPUT_FOLDER)/*

_all: $(OUTPUT_FOLDER)/os-image.bin

$(OUTPUT_FOLDER)/os-image.bin: $(OUTPUT_FOLDER)/bootsector.bin $(OUTPUT_FOLDER)/kernel.bin
	cat $^ > $@

$(OUTPUT_FOLDER)/bootsector.bin: $(SOURCE_FOLDER)/bootsector.asm
	$(ASSEMBLER) $(ASSEMBLER_FLAGS_FOR_BOOTSECTOR) $^ -o $@

# Creates kernel_entry and the C_OBJECT_FILES object files, in that order! the order is improtant
$(OUTPUT_FOLDER)/kernel.bin: $(OUTPUT_FOLDER)/kernel_entry.o $(C_OBJECT_FILES)
	$(LINKER) $(LINKER_FLAGS) $^ -o $@

# General rule to create object files from .c files
# Also creates the subfolder of the c source file in the output folder
$(OUTPUT_FOLDER)/%.o: $(SOURCE_FOLDER)/%.c
	@mkdir -p $(@D)
	$(COMPILER) $(COMPILER_FLAGS) -c $< -o $@

# General rule to create object files from .asm files
# Also creates the subfolder of the asm source file in the output folder
$(OUTPUT_FOLDER)/%.o: $(SOURCE_FOLDER)/%.asm
	@mkdir -p $(@D)
	$(ASSEMBLER) $(ASSEMBLER_FLAGS) $< -o $@

