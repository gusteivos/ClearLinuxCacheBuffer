
#ifndef SIMPLE_MEMINFO_H
#define SIMPLE_MEMINFO_H

    #include <errno.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>

    #define SMI_MB_DIVISOR                1024

    #define SMI_MEMINFO_FILE_PATH         "/proc/meminfo"

    #define SMI_AVAILABLEMEM_KEYWORD "MemAvailable:"
    #define SMI_BUFFERS_KEYWORD      "Buffers:"
    #define SMI_CACHED_KEYWORD       "Cached:"
    #define SMI_FREEMEM_KEYWORD      "MemFree:"
    #define SMI_FREESWAP_KEYWORD     "SwapFree:"
    #define SMI_MEMTOTAL_KEYWORD     "MemTotal:"
    #define SMI_TOTALSWAP_KEYWORD    "SwapTotal:"

    typedef struct smi_meninfo
    {

        unsigned long available_mem;
        
        unsigned long buffers;
        
        unsigned long cached;
        
        unsigned long free_mem;
        
        unsigned long free_swap;
        
        unsigned long total_mem;
        
        unsigned long total_swap;

    } smi_meninfo_t;

    extern int smi_get_info(unsigned long *, const char *);
    
    extern int smi_get_infos(smi_meninfo_t *);
    
    extern int smi_open_info_file(FILE **);

#endif
