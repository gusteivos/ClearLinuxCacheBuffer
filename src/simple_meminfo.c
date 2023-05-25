#include <simple_meminfo.h>

int smi_get_info(unsigned long *info, const char *keyword)
{
    
    FILE *_info_file;
    
    int _output_value = smi_open_info_file(&_info_file);

    if (_output_value != 0) goto _end_of_function;
    
    char _info_file_line[256];

    while (fgets(_info_file_line, sizeof(_info_file_line), _info_file) != NULL)
    {
    
        if (strstr(_info_file_line, keyword) != NULL)
        {
        
            sscanf(_info_file_line, "%*s %lu", info);

            if (info != 0) *info /= SMI_MB_DIVISOR;
        
            break;
        
        }
    
    }
    
    fclose(_info_file);
    
_end_of_function:

    return _output_value;

}

int smi_get_infos(smi_meninfo_t *infos)
{

    if (infos == NULL) return -1;

    FILE *_info_file;
    
    int _output_value = smi_open_info_file(&_info_file);

    if (_output_value != 0) goto _end_of_function;
    
    char _info_file_line[256];

    while (fgets(_info_file_line, sizeof(_info_file_line), _info_file) != NULL)
    {

        unsigned long __info = 0;

        sscanf(_info_file_line, "%*s %lu", &__info);

        if (__info != 0) __info /= SMI_MB_DIVISOR;

        if (strstr(_info_file_line, SMI_AVAILABLEMEM_KEYWORD))
            infos->available_mem = __info;
        else if (strstr(_info_file_line, SMI_BUFFERS_KEYWORD))
            infos->buffers = __info;
        else if (strstr(_info_file_line, SMI_CACHED_KEYWORD))
            infos->cached = __info;
        else if (strstr(_info_file_line, SMI_FREEMEM_KEYWORD))
            infos->free_mem = __info;
        else if (strstr(_info_file_line, SMI_FREESWAP_KEYWORD))
            infos->free_swap = __info;
        else if (strstr(_info_file_line, SMI_MEMTOTAL_KEYWORD))
            infos->total_mem = __info;
        else if (strstr(_info_file_line, SMI_TOTALSWAP_KEYWORD))
            infos->total_swap = __info;

    }

    fclose(_info_file);
    
_end_of_function:

    return _output_value;

}

int smi_open_info_file(FILE **info_file)
{

    if (info_file == NULL) return -1;

    *info_file = fopen(SMI_MEMINFO_FILE_PATH, "r");
    
    if (*info_file == NULL) return errno;
    
    return 0;

}
