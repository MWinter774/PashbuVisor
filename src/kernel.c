#include <paging/paging.h>

void main()
{
    char * video_memory = (char *)0xb8000;

    initialize_paging();

    *video_memory = 'X';
}

