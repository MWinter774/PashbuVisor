#include <paging/paging.h>
#define PAGE_DIRECTORY_SIZE (1024)
#define PAGE_TABLE_SIZE (1024)

// The Page Directory table, each entry holds pointer to a page table and some flags
unsigned int page_directory[PAGE_DIRECTORY_SIZE] __attribute__((aligned(4096)));

// A Page Table, each entry holds pointer to physical memory and some flags
unsigned int page_table[PAGE_TABLE_SIZE] __attribute__((aligned(4096)));

/*
 * Puts page_directory in cr3.
 */
void load_page_directory(void * page_directory)
{
    __asm__("movl %%cr3, %0\n;"
            :
            : "r"(page_directory)
            :);
}

/*
 * Sets the 32th bit in CR0 in order to turn on paging.
 */
void enable_paging()
{
    __asm__("mov %eax, %cr0\n\t"
            "or $0x80000000, %eax\n\t"
            "mov %cr0, %eax\n\t");
}

/*
 * Initializes a page directory table. page_directory_size SHOULD BE 1024!
 */
void setup_page_directory(unsigned int * page_directory, unsigned int page_directory_size)
{
    for (unsigned int i = 0; i < page_directory_size; i++)
    {
        // Page table pointer: 0x00000000
        // Supervisor: only the kernel can access this page table
        // Read/Write: Read/Write access to this page table
        // Not Present: This page table is not present
        page_directory[i] = 0x00000002;
    }
}

/*
 * Initializes a page table. page_table_size SHOULD BE 1024!
 */
void setup_page_table(unsigned int * page_table, unsigned int page_table_size)
{
    for (unsigned int i = 0; i < page_table_size; i++)
    {
        page_table[i] = (i * 0x1000) | 3;
    }
}

void initialize_paging()
{
    setup_page_directory(page_directory, sizeof(page_directory));
    setup_page_table(page_table, sizeof(page_table));

    // Page directory holds only one page table
    page_directory[0] = ((unsigned int)page_table) | 3;

    load_page_directory(page_directory);
    enable_paging();
}

