#include <main.h>

bool can_clean = true;

long int expire_centisecs    = DEFAULT_EXPIRE_CENTISECS;

long int writeback_centisecs = DEFAULT_WRITEBACK_CENTISECS;

long int maximum_accepted_cache = 256;

long int maximum_accepted_buffer = 64;

int set_expire_centisecs_on_file()
{
    
    int _output_value = 0;

    FILE *_dirty_expire_centisecs_file = fopen(DIRTY_EXPIRE_CENTISECS_PATH, "w");
    
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

        sprintf(__error_string, "Error setting expire_centisecs in file: %s", DIRTY_EXPIRE_CENTISECS_PATH);

        perror(__error_string);
    
    }

    return _output_value;

}

int set_writeback_centisecs_on_file()
{
    
    int _output_value = 0;

    FILE *_dirty_writeback_centisecs_file = fopen(DIRTY_WRITEBACK_CENTISECS_PATH, "w");
    
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

        sprintf(__error_string, "Error setting writeback_centisecs in file: %s", DIRTY_WRITEBACK_CENTISECS_PATH);

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

    //Temp:

        char *str = "127.0.0.1";

        strcpy(listen_ip, str);

        listen_port = DEFAULT_LISTEN_PORT;
  
    static const struct option _long_opts[] =
    {

		{ "daemon",	no_argument, NULL, 'D'},
		{   "help",	no_argument, NULL, 'h'},

#ifdef PROGRAM_ACCEPTS_SYSTEMD

        {"systemd", no_argument, NULL, 'S'},

#endif

        {"version",	no_argument, NULL, 'V'},
		{NULL, 0, NULL, 0}
	
    };

    int _opt;
    
    bool _daemon_opt = false;

    while ((_opt = getopt_long(argument_count, argument_values, "DhSV", _long_opts, NULL)) != -1)
        switch (_opt)
        {

            case 'D':
                _daemon_opt = true;
                break;

#ifdef PROGRAM_ACCEPTS_SYSTEMD

            case 'S':


                
                break;

#endif

            case 'h':
                printf("To Do: Create the Help Option");
            case 'V':
                printf("%s version: %s", PROGRAM_NAME, PROGRAM_VERSION);
                goto _direct_exit_program;

            case '?':
                printf("Unknown option ignoring...");
                break;

            default:
                printf("Unexpected result from getopt_long(): %d\n", _opt);
                break;

        }

    if (_daemon_opt)
    {
        
        if (daemon(0, 0) == -1)
        {
        
            perror("Failed to daemonize program");
        
            exit(EXIT_FAILURE);
        
        }

        fclose(stdin);

        fclose(stdout);

        fclose(stderr);

        openlog(PROGRAM_NAME, LOG_PID, LOG_DAEMON);

        setlogmask(LOG_UPTO(LOG_INFO));

        syslog(LOG_INFO, "Starting as a demon.");

    }

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
    
    while (can_clean)
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
