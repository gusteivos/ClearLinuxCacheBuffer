#include <stdbool.h>
#include <getopt.h>
#include <syslog.h>
#include <program_information.h>
#include <cache_buffer.h>
#include <ctl_listener.h>

#define DIRTY_EXPIRE_CENTISECS_PATH "/proc/sys/vm/dirty_expire_centisecs"

#define DEFAULT_EXPIRE_CENTISECS    1000

#define DIRTY_WRITEBACK_CENTISECS_PATH "/proc/sys/vm/dirty_writeback_centisecs"

#define DEFAULT_WRITEBACK_CENTISECS    250

extern long int expire_centisecs;

extern long int writeback_centisecs;

extern long int maximum_accepted_cache;

extern long int maximum_accepted_buffer;
