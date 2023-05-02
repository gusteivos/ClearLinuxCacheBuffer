#include <main.h>

long int expire_centisecs    = DEFAULT_EXPIRE_CENTISECS;

long int writeback_centisecs = DEFAULT_WRITEBACK_CENTISECS;

long int maximum_accepted_cache = 256;

long int maximum_accepted_buffer = 64;

int set_expire_centisecs_on_file()
{
    
    int _output_value = 0;

    FILE *_dirty_expire_centisecs_file = fopen(LINUX_DIRTY_EXPIRE_CENTISECS, "w");
    
    if (_dirty_expire_centisecs_file == NULL)
    {

        _output_value = errno;
        
        goto _end_of_function;

    }

    fprintf(_dirty_expire_centisecs_file, "%ld", expire_centisecs);

    fclose(_dirty_expire_centisecs_file);

_end_of_function:

    return _output_value;

}

int set_expire_centisecs_on_file_perror()
{

    int _output_value = set_expire_centisecs_on_file();

    if (_output_value != 0)
    {

        char __error_string[1024];

        sprintf(__error_string, "Error setting expire_centisecs in file: %s", LINUX_DIRTY_EXPIRE_CENTISECS);

        perror(__error_string);
    
    }

    return _output_value;

}

int set_writeback_centisecs_on_file()
{
    
    int _output_value = 0;

    FILE *_dirty_writeback_centisecs_file = fopen(LINUX_DIRTY_WRITEBACK_CENTISECS, "w");
    
    if (_dirty_writeback_centisecs_file == NULL)
    {

        _output_value = errno;
        
        goto _end_of_function;

    }

    fprintf(_dirty_writeback_centisecs_file, "%ld", writeback_centisecs);

    fclose(_dirty_writeback_centisecs_file);

_end_of_function:

    return _output_value;

}

int set_writeback_centisecs_on_file_perror()
{

    int _output_value = set_writeback_centisecs_on_file();

    if (_output_value != 0)
    {

        char __error_string[1024];

        sprintf(__error_string, "Error setting writeback_centisecs in file: %s", LINUX_DIRTY_WRITEBACK_CENTISECS);

        perror(__error_string);
    
    }

    return _output_value;

}

void print_address_and_port(struct sockaddr_in address)
{

    char ip[INET_ADDRSTRLEN];

    inet_ntop(AF_INET, &(address.sin_addr), ip, INET_ADDRSTRLEN);
    
    printf("IP: %s\n", ip);
    
    printf("Porta: %d\n", ntohs(address.sin_port));

}


int main(int argument_count, char *argument_values[])
{

    char *str = "127.0.0.1";

    strcpy(listen_ip, str);

    listen_port = DEFAULT_LISTEN_PORT;



    if (start_ctl_listener() != 0)
    {

        perror("Error on start_ctl_listener");

        goto _direct_exit_program;

    }
    else
    {

        printf("Listening to ctl in:\n");

        print_address_and_port(listen_address);

    }

    if (set_expire_centisecs_on_file_perror() == 0)
    {

        //Todo: 

    }
    else
    {

        //Todo: 

    }

    if (set_writeback_centisecs_on_file_perror() == 0)
    {

        //Todo: 

    }
    else
    {

        //Todo: 

    }

    bool _can_run = true;

    while (_can_run)
    {

        int level_of_possible_cleanliness = 0;

        long int __current_buffer_usage = 0;

        get_buffer_usage(&__current_buffer_usage);

        __current_buffer_usage /= 1024;

        if (__current_buffer_usage > maximum_accepted_buffer) level_of_possible_cleanliness += 1;

        long int __current_cache_usage = 0;

        get_cache_usage(&__current_cache_usage);

        __current_cache_usage /= 1024;

        if (__current_cache_usage > maximum_accepted_cache) level_of_possible_cleanliness += 2;

        if (level_of_possible_cleanliness > 0)
        {

            char *cmd_str = "sync; echo %d > /proc/sys/vm/drop_caches";

            char cmd_str_form[1024];

            sprintf(cmd_str_form, cmd_str, level_of_possible_cleanliness);

            system(cmd_str_form);

            printf("Clean memory using level: %d\n", level_of_possible_cleanliness);

            sleep(1);

        }

        char received_ctl_data[1024];

        int size_of_received_ctl_data = 0;

        int _successful_reading = read_ctl_listener(received_ctl_data, &size_of_received_ctl_data);

        if (_successful_reading == 0)
        {

            //todo

        }
        else
        {

            //todo

        }

        usleep(100000);

    }

_exit_program:

    close_ctl_listener();

_direct_exit_program:

    return 0;

}
