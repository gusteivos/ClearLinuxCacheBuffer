#include <cahe_buffer.h>

int get_buffer_usage(unsigned long *buffer)
{

    int _output_value = 0;

    FILE *_meninfo_file = fopen(CB_MENINFO_PATH, "r");

    if (_meninfo_file == NULL)
    {
        
        _output_value = errno;

        goto _end_of_function;

    }

    char _meninfo_file_line[CB_LINE_BUFFER_SIZE];

    while (fgets(_meninfo_file_line, CB_LINE_BUFFER_SIZE, _meninfo_file) != NULL)
    {
    
        if (strncmp(_meninfo_file_line, "Buffers:", 8) == 0)
        {
        
            sscanf(_meninfo_file_line, "Buffers: %lu kB", buffer);
        
            break;
        
        }
    
    }

    fclose(_meninfo_file);

_end_of_function:

    return _output_value;

}

int get_cache_usage (unsigned long *cache)
{

    int _output_value = 0;

    FILE *_meninfo_file = fopen(CB_MENINFO_PATH, "r");

    if (_meninfo_file == NULL)
    {
        
        _output_value = errno;

        goto _end_of_function;

    }

    char _meninfo_file_line[CB_LINE_BUFFER_SIZE];

    while (fgets(_meninfo_file_line, CB_LINE_BUFFER_SIZE, _meninfo_file) != NULL)
    {
    
        if (strncmp(_meninfo_file_line, "Cached:", 7) == 0)
        {
        
            sscanf(_meninfo_file_line, "Cached: %lu kB", cache);
        
            break;
        
        }
    
    }

    fclose(_meninfo_file);

_end_of_function:

    return _output_value;

}