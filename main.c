#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 12345
#define BUFFER_SIZE 1024

int main(int argument_count, char *argument_values[])
{

    int sockfd;
    struct sockaddr_in serverAddr;
    char buffer[BUFFER_SIZE];

    sockfd = socket(AF_INET, SOCK_DGRAM | SOCK_NONBLOCK, IPPROTO_UDP);

    if (sockfd < 0)
    {
    
        perror("Erro ao criar socket");
    
        exit(1);
    
    }

    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(SERVER_PORT);
    
    if (inet_pton(AF_INET, SERVER_IP, &(serverAddr.sin_addr)) <= 0)
    {
    
        perror("Erro ao configurar informações do servidor");
    
        exit(1);
    
    }

    strcpy(buffer, "Olá, servidor!");
    
    if (sendto(sockfd, buffer, strlen(buffer), 0, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0)
    {
    
        perror("Erro ao enviar mensagem");
    
        exit(1);
    
    }

    printf("Mensagem enviada para o servidor\n");

    close(sockfd);

    return 0;

}
