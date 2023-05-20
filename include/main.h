#include <cache_buffer.h>
#include <getopt.h>
#include <program_information.h>
#include <stdbool.h>
#include <syslog.h>
#include <unistd.h>

#ifdef PROGRAM_ACCEPTS_SYSTEMD

    #include <systemd/sd-daemon.h>

    #include <systemd/sd-journal.h>

#endif

#define DEFAULT_EXPIRE_CENTISECS        1000

#define DEFAULT_WRITEBACK_CENTISECS     250

#define DIRTY_EXPIRE_CENTISECS_PATH     "/proc/sys/vm/dirty_expire_centisecs"

#define DIRTY_WRITEBACK_CENTISECS_PATH  "/proc/sys/vm/dirty_writeback_centisecs"

extern long int expire_centisecs;

extern long int writeback_centisecs;

extern long int maximum_accepted_cache;

extern long int maximum_accepted_buffer;
