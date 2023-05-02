#include <stdbool.h>
#include <cahe_buffer.h>
#include <ctl_listener.h>

#define LINUX_DIRTY_EXPIRE_CENTISECS    "/proc/sys/vm/dirty_expire_centisecs"

#define DEFAULT_EXPIRE_CENTISECS    1000

#define LINUX_DIRTY_WRITEBACK_CENTISECS "/proc/sys/vm/dirty_writeback_centisecs"

#define DEFAULT_WRITEBACK_CENTISECS 250

#define LINUX

extern long int expire_centisecs;

extern long int writeback_centisecs;

extern long int maximum_accepted_cache;

extern long int maximum_accepted_buffer;
