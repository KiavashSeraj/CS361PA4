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
#include "message.h"
/* -------------------------------------------------------------------*/
int main(int argc, char *argv[])
{
    if (argc != 6)
    {
        printf("Usage: %s <ip_address> <port> <num1> <op> <num2>\n", argv[0]);
        exit(1);
    }

    char *ip_address = argv[1];
    int port = atoi(argv[2]);
    int num1 = atoi(argv[3]);
    char op = argv[4][0];
    int num2 = atoi(argv[5]);

    // Allocate a socket
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0); // SOCK_DGRAM for UDP
    if (sockfd < 0)
    {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Set up the server address
    struct sockaddr_in srvrSkt, clntSkt;
    memset( (void *) &srvrSkt, 0, sizeof(srvrSkt));
    srvrSkt.sin_family = AF_INET;              // IPv4 address
    srvrSkt.sin_addr.s_addr = htonl(INADDR_ANY);
    srvrSkt.sin_port = htons(atoi(argv[2]));  // Server port

    // Bind the socket to the server address
    if (bind(sockfd, (struct sockaddr *) &srvrSkt, sizeof(srvrSkt)) < 0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    calcMsg message;

    // read myName.txt
    FILE *fp = fopen("myName.txt", "r");
    fgets(message.fullName, 125, fp);
    fclose(fp);

    // Remove newline character if present
    size_t len = strlen(message.fullName);
    if (len > 0 && message.fullName[len - 1] == '\n')
    {
        message.fullName[len - 1] = '\0';
    }

    // assign message type
    message.msgType = 1;
    // assign operands
    message.num1 = htonl(num1);
    message.num2 = htonl(num2);
    // assign operation
    message.operation = op;
    // set result to 0
    message.result = 0; 

    printf("This client is developed by %s\n", message.fullName);

    printf("Attempting Calculator server at '%s' : %d\n", ip_address, port);

    printf("User %s sent this message to the Calculator : ", message.fullName);
    message.fullName += "-User";
    printMsg(stdout, &message);
    // message.fullName = message.fullName[]
    printf("\n");

    printf("User is now waiting to receive result ...\n");
    printf("User %s received this message from the Calculator server: ", message.fullName);
    message.fullName += "-Calculator";
    printMsg(stdout, &message);
    printf("\n");
    int result;

    // printf("User received the following: %d from FD %d\n", result, rep_read_fd);
}