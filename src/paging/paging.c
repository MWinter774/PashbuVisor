#include <paging/paging.h>

unsigned int page_directory[1024] __attribute__((aligned(4096)));

void setup_page_directory()
{
    for (int i = 0; i < 1024; i++)
    {
        page_directory[i] = 0x00000002;
    }
}

