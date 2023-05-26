#include <main.h>

long int dirty_expire_centisecs_value    = DEFAULT_DIRTY_EXPIRE_CENTISECS_VALUE;

long int dirty_writeback_centisecs_value = DEFAULT_DIRTY_WRITEBACK_CENTISECS_VALUE;

long int maximum_accepted_buffer = 256;

long int maximum_accepted_cache  = 512;

static unsigned char for_print_output = 0; /* 0 - printf, 1 - syslog, 2 - sd_journal_print */

static bool keep_running = true;

bool daemon_option = false;

#ifdef PROGRAM_ACCEPTS_SYSTEMD

bool systemd_option = false;

#endif

static void on_program_exit(void)
{

#ifdef PROGRAM_ACCEPTS_SYSTEMD
    if (systemd_option)
        sd_notify(0, "STOPPING=1");
    else 
#endif
    {

        if (daemon_option) closelog();

    }

}

static void print_message(const char* format, ...)
{

    char formatted_string[(strlen(format) + 1) * 2];

    va_list args;
    
    va_start(args, format);

    vsnprintf(formatted_string, sizeof(formatted_string), format, args);

    va_end(args);

    switch (for_print_output)
    {

        case 0: printf (formatted_string);                    break;

        case 1: syslog          (LOG_INFO, formatted_string); break;

#ifdef PROGRAM_ACCEPTS_SYSTEMD        
        case 2: sd_journal_print(LOG_INFO, formatted_string); break;
#endif

        default: printf(formatted_string);                    break;

    }

}

static void __attribute__ ((__noreturn__)) print_usage(FILE * out)
{

    fprintf(out, "Usage: %s [options]\n", PROGRAM_NAME);

    fprintf(out, "Options:\n");

    fprintf(out, "  -D, --daemon              Run the program as a daemon\n");

    fprintf(out, "  -h, --help                Display this help message\n"  );

    fprintf(out, "  -S, --systemd             Enable systemd integration\n" );

    fprintf(out, "  -V, --version             Display version information\n");

    exit(out == stderr ? EXIT_FAILURE : EXIT_SUCCESS);

}

static void signal_handler(int signal_number)
{

    switch(signal_number)
    {

        case SIGINT:
            
            print_message("SIGINT received.");

            keep_running = false;
            
            break;

        case SIGTERM:

            print_message("SIGTERM received.");

            on_program_exit();

            exit(0);

    } 

}

int set_dirty_expire_centisecs_on_file()
{
    
    int _output_value = 0;

    FILE *_dirty_expire_centisecs_file = fopen(DIRTY_EXPIRE_CENTISECS_FILE_PATH, "w");
    
    if (_dirty_expire_centisecs_file == NULL)
    {

        _output_value = errno;
        
        goto _end_of_function;

    }

    fprintf(_dirty_expire_centisecs_file, "%ld", dirty_expire_centisecs_value);

    fclose(_dirty_expire_centisecs_file);

_end_of_function:

    return _output_value;

}

int set_dirty_writeback_centisecs_on_file()
{
    
    int _output_value = 0;

    FILE *_dirty_writeback_centisecs_file = fopen(DIRTY_WRITEBACK_CENTISECS_FILE_PATH, "w");
    
    if (_dirty_writeback_centisecs_file == NULL)
    {

        _output_value = errno;
        
        goto _end_of_function;

    }

    fprintf(_dirty_writeback_centisecs_file, "%ld", dirty_writeback_centisecs_value);

    fclose(_dirty_writeback_centisecs_file);

_end_of_function:

    return _output_value;

}

int main(int argument_count, char **argument_values)
{

    int option;

    static const struct option longopts[] =
    {

		{ "daemon",	no_argument, NULL, 'D'},

		{   "help",	no_argument, NULL, 'h'},

#ifdef PROGRAM_ACCEPTS_SYSTEMD
        {"systemd", no_argument, NULL, 'S'},
#endif

        {"version",	no_argument, NULL, 'V'},
		
        {NULL, 0, NULL, 0}
	
    };
  
    while ((option = getopt_long(argument_count, argument_values, "DhSV", longopts, NULL)) != -1)
        switch (option)
        {
            
            case 'D': daemon_option = true;  break;

#ifdef PROGRAM_ACCEPTS_SYSTEMD
            case 'S': systemd_option = true; break;
#endif

            case 'h': print_usage(stdout);
      
            case 'V':
                printf("%s version: %s\n", PROGRAM_NAME, PROGRAM_VERSION);
                exit(0);

            case '?':
                printf("Invalid option and or argument.\n");
                print_usage(stderr);

            default: print_usage(stderr);

        }

#ifdef PROGRAM_ACCEPTS_SYSTEMD
    if (systemd_option)
    {

        if (sd_booted() <= 0 || sd_notify(0, "READY=1") < 0)
        {
            
            fprintf(stderr, "Program was not started by systemd or could not notify; errno: %d\n", errno);
        
            exit(EXIT_FAILURE);

        }

        sd_journal_print(LOG_INFO, "Starting as a systemd daemon.");

        for_print_output = 2; /*To sd_journal_print.*/

    }
    else
#endif
    {

        if (daemon_option)
        {   

            if (daemon(0, 0) == -1)
            {
                
                fprintf(stderr, "Failed to daemonize program; errno: %d\n", errno);
            
                exit(EXIT_FAILURE);
            
            }

            fclose(stdin);

            fclose(stdout);

            fclose(stderr);

            openlog(PROGRAM_NAME, LOG_PID, LOG_DAEMON);

            setlogmask(LOG_UPTO(LOG_INFO));

            syslog(LOG_INFO, "Starting as a daemon.");

            for_print_output = 1; /*To syslog.*/

        }

    }



    int q = set_dirty_expire_centisecs_on_file();

    if (q != 0)
    {   

        print_message("Error when setting dirty_expire_centisecs (%s) with value: %d; errno: %d\n", DIRTY_EXPIRE_CENTISECS_FILE_PATH, dirty_expire_centisecs_value, errno);

    }

    q = set_dirty_writeback_centisecs_on_file();

    if (q != 0)
    {   

        print_message("Error when setting dirty_writeback_centisecs (%s) with value: %d; errno: %d\n", DIRTY_EXPIRE_CENTISECS_FILE_PATH, dirty_expire_centisecs_value, errno);

    }



    signal(SIGINT , signal_handler);

    signal(SIGTERM, signal_handler);

    while (keep_running)
    {

        smi_meninfo_t meninfo;

        int output_of_meninfo_reading = smi_get_infos(&meninfo);

        if (output_of_meninfo_reading == 0)
        {

            int level_of_possible_cleanliness = 0;

            if (meninfo.buffers > maximum_accepted_buffer) level_of_possible_cleanliness += 1;

            if (meninfo.cached  > maximum_accepted_cache)  level_of_possible_cleanliness += 2;
            
            if (level_of_possible_cleanliness > 0)
            {

                char *command_format_string = "sync; echo %d > /proc/sys/vm/drop_caches";

                char command_string[48];

                sprintf(command_string, command_format_string, level_of_possible_cleanliness);

                system(command_string);

                print_message("Clean memory using level: %d\n", level_of_possible_cleanliness);

                sleep(1);

            }
            
        }
        else
            print_message("Error reading meminfo file: %s, errno: %d", SMI_MEMINFO_FILE_PATH, output_of_meninfo_reading);

        if (for_print_output == 0) fflush(stdout); /*This prevents errors from the terminal not being updated.*/

        usleep(100000);

    }

    on_program_exit();

    return 0;

}
