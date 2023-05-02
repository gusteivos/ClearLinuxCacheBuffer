#include <ctl_listener.h>

char           listen_ip[16];

unsigned short listen_port;

short          listen_buffer_size;

int                listen_socket_fd;

struct sockaddr_in listen_address;

int start_ctl_listener()
{

    int _output_value = 0;

    listen_socket_fd = socket(AF_INET, SOCK_DGRAM | SOCK_NONBLOCK, IPPROTO_UDP);
    
    if (listen_socket_fd < 0)
    {

        _output_value = errno;

        goto _end_of_function;

    }

    memset(&listen_address, 0, sizeof(listen_address));
    
    listen_address.sin_family = AF_INET;
    
    listen_address.sin_addr.s_addr = inet_addr(listen_ip);
    
    listen_address.sin_port = htons(listen_port);

    if (bind(listen_socket_fd, (struct sockaddr *)&listen_address, sizeof(listen_address)) < 0)
    {
    
        _output_value = errno;

        close(listen_socket_fd);

    }

_end_of_function:

    return _output_value;

}

int read_ctl_listener(unsigned char *buffer, int *num_of_bytes_received)
{

    int _output_value = 0;

    *num_of_bytes_received = recvfrom(listen_socket_fd, buffer, listen_buffer_size, 0, NULL, NULL);
    
    if (num_of_bytes_received < 0)
    {

        _output_value = errno;
    
    }

    return _output_value;

}

void close_ctl_listener()
{
    close(listen_socket_fd);
}
