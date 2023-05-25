#include <getopt.h>
#include <program_information.h>
#include <simple_meminfo.h>
#include <stdbool.h>
#include <syslog.h>
#include <unistd.h>
#include <signal.h>

#ifdef PROGRAM_ACCEPTS_SYSTEMD

    #include <systemd/sd-daemon.h>
    #include <systemd/sd-journal.h>

#endif

#define DEFAULT_DIRTY_EXPIRE_CENTISECS_VALUE    1000

#define DEFAULT_DIRTY_WRITEBACK_CENTISECS_VALUE 250

#define DIRTY_EXPIRE_CENTISECS_FILE_PATH        "/proc/sys/vm/dirty_expire_centisecs"

#define DIRTY_WRITEBACK_CENTISECS_FILE_PATH     "/proc/sys/vm/dirty_writeback_centisecs"

extern long int dirty_expire_centisecs_value;

extern long int dirty_writeback_centisecs_value;

extern long int maximum_accepted_buffer;

extern long int maximum_accepted_cache;
