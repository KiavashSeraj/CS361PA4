/*----------------------------------------------------------------------
PA-04  The User process
Written By: Mateen Faieq and Kiavash Seraj
Submitted on: 05/01/2023
----------------------------------------------------------------------*/
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
/* -------------------------------------------------------------------*/
int main(int argc, char *argv[])
{
    if (argc != 6)
    {
        printf("Usage: %s <ip_address> <port> <num1> <op> <num2>\n", argv[0]);
        exit(1);
    }

    int sockfd = socket(AF_INET, SOCK_DGRAM, 0); // SOCK_DGRAM for UDP

    char *ip_address = argv[1];
    int port = atoi(argv[2]);
    int num1 = atoi(argv[3]);
    char op = argv[4][0];
    int num2 = atoi(argv[5]);

    printf("This client is developed by Mateen Faieq & Kiavash Seraj\n");

    printf("Attempting Calculator server at '%s' : %d\n", ip_address, port);

    printf("User Mateen Faieq & Kiavash Seraj sent this message to the Calculator : { Name= }");

    
    

    int result;

    

    // printf("User received the following: %d from FD %d\n", result, rep_read_fd);

}