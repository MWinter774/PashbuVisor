#include <paging/paging.h>

void main()
{
    char * video_memory = (char *)0xb8000;
    *video_memory = 'X';

    setup_page_directory();
}
