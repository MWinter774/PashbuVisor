#include <paging/paging.h>
#define PML4_TABLE_SIZE (512)
#define PAGE_DIRECTORY_POINTER_TABLE_SIZE (512)
#define PAGE_DIRECTORY_SIZE (512)
#define PAGE_TABLE_SIZE (512)

// The PML4 Table, each entry holds pointer to a page directory pointer table.
unsigned long pml4_table[PML4_TABLE_SIZE] __attribute__((aligned(4096)));

// The PDPT, each entry holds pointer to a page directory. This is in order to enable PAE.
unsigned long page_directory_pointer_table[PAGE_DIRECTORY_POINTER_TABLE_SIZE] __attribute__((aligned(512)));

// The Page Directory table, each entry holds pointer to a page table and some flags
unsigned long page_directory[PAGE_DIRECTORY_SIZE] __attribute__((aligned(4096)));

// A Page Table, each entry holds pointer to physical memory and some flags
unsigned long page_table[PAGE_TABLE_SIZE] __attribute__((aligned(4096)));

/*
 * Puts page_directory in cr3.
 */
void load_page_directory(void * page_directory)
{
    asm volatile("movl %%cr3, %0\n;"
                :
                : "r"(page_directory)
                :);
}

/*
 * Sets the 32th bit in CR0 in order to turn on paging.
 */
void enable_paging()
{
    asm volatile(   "mov %eax, %cr0\n;"
                    "or $0x80000000, %eax\n;"
                    "mov %cr0, %eax\n;");
}

/*
 * Set the 5th bit in CR4 to enable PAE.
 */
void enable_pae()
{
    asm volatile (  "movl %%cr4, %%eax\n;"
                    "bts $5, %%eax\n;"
                    "movl %%eax, %%cr4\n;"
                    :
                    :
                    : "eax");
}

/*
 * Initializes a page directory table. page_directory_size SHOULD BE 1024!
 */
void setup_page_directory(unsigned long * page_directory, unsigned int page_directory_size)
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
void setup_page_table(unsigned long * page_table, unsigned int page_table_size)
{
    for (unsigned int i = 0; i < page_table_size; i++)
    {
        page_table[i] = (i * 0x1000) | 3;
    }
}

/*
 * Sets the 9th bit of EFER MSR.
 */
void enter_compatibility_mode()
{
    asm volatile(   "mov $0xC0000080, %ecx\n;"
                    "rdmsr\n;"
                    "or $(1 << 8), %eax\n;"
                    "wrmsr\n;");
}

void initialize_paging()
{
    setup_page_directory(page_directory, sizeof(page_directory));
    setup_page_table(page_table, sizeof(page_table));

    pml4_table[0] = ((unsigned long)page_directory_pointer_table);

    page_directory_pointer_table[0] = ((unsigned long)page_directory) | 1;

    // Page directory holds only one page table.
    // This page table is:
    // Present
    // Read/Write
    // 2MiB (not 4KiB which is 32 bit)
    page_directory[0] = ((unsigned int)page_table) | 0b10000011;

    load_page_directory(page_directory);

    enable_pae();

    enter_compatibility_mode();

    enable_paging();
}

