.PHONY: all clean

# Assmebler settings
ASSEMBLER=nasm
ASSEMBLER_FLAGS=-fbin

# Bootloader files
BOOTLOADER_ENTRY_FILE=./entry.asm

# Output file name
OUTPUT_DIR=./out
OUTPUT_FILE_NAME=output.bin

all: bootloader_entry
clean:
	rm -rf $(OUT_DIR)

bootloader_entry:
	$(ASSEMBLER) $(ASSEMBLER_FLAGS) $(BOOTLOADER_ENTRY_FILE) -o $(OUTPUT_DIR)/$(OUTPUT_FILE_NAME)
