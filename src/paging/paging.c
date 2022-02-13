#include <paging/paging.h>

unsigned int page_directory[1024] __attribute__((aligned(4096)));

void setup_page_directory()
{
    for (int i = 0; i < 1024; i++)
    {
        // Page table pointer: 0x00000000
        // Supervisor: only the kernel can access this page table
        // Read/Write: Read/Write access to this page table
        // Not Present: This page table is not present
        page_directory[i] = 0x00000002;
    }
}

