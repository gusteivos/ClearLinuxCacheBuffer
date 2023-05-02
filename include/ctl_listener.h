
#ifndef CTL_LISTENER_H_
#define CTL_LISTENER_H_

    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>
    #include <string.h>
    #include <stdlib.h>
    #include <unistd.h>
    #include <errno.h>

    #define  DEFAULT_LISTEN_IP "127.0.0.1"

    #define  DEFAULT_LISTEN_PORT (unsigned short)12345

    extern char           listen_ip[16];

    extern unsigned short listen_port;

    extern short          listen_buffer_size;

    extern int listen_socket_fd;

    extern struct sockaddr_in listen_address;

    extern int start_ctl_listener();

    extern int read_ctl_listener(unsigned char *, int *);

    extern void close_ctl_listener();

#endif
