
#ifndef CACHE_BUFFER_H_
#define CACHE_BUFFER_H_

    #include <errno.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>

    #define CB_MENINFO_PATH     "/proc/meminfo"
    
    #define CB_LINE_BUFFER_SIZE 1024 * sizeof(char)

    extern int get_buffer_usage(unsigned long *);

    extern int get_cache_usage (unsigned long *);
    
#endif
