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
    struct sockaddr_in srvrSkt;
    memset((void *)&srvrSkt, 0, sizeof(srvrSkt));
    srvrSkt.sin_family = AF_INET;                    // IPv4 address
    srvrSkt.sin_addr.s_addr = inet_addr(ip_address); // Server IP address (network byte order
    srvrSkt.sin_port = htons(atoi(argv[2]));         // Server port

    calcMsg message;
    char fullName[125];

    // read myName.txt
    FILE *fp = fopen("myName.txt", "r");
    fgets(fullName, 125, fp);
    fclose(fp);

    // Remove newline character if present
    size_t len = strlen(fullName);
    if (len > 0 && fullName[len - 1] == '\n')
    {
        fullName[len - 1] = '\0';
    }
    strncpy(message.fullName, fullName, sizeof(message.fullName) - 1);

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

    // Send the message to the server
    socklen_t srvrSktLen = sizeof(srvrSkt);
    if (sendto(sockfd, (void *)&message, sizeof(message), 0, (struct sockaddr *)&srvrSkt, srvrSktLen) < 0)
    {
        perror("sendto failed");
        exit(EXIT_FAILURE);
    }

    printf("User %s sent this message to the Calculator : ", message.fullName);
    char userMsg[130];
    char calcMsg[130];

    snprintf(userMsg, sizeof(userMsg), "%s-User", fullName);
    strncpy(message.fullName, userMsg, sizeof(message.fullName) - 1);
    printMsg(stdout, &message);
    strncpy(message.fullName, fullName, sizeof(message.fullName) - 1);
    printf("\n");

    printf("User is now waiting to receive result ...\n");

    // Receive the result from the server

    calcMsg received_message;
    if (recvfrom(sockfd, (void *)&received_message, sizeof(received_message), 0, (struct sockaddr *)&srvrSkt, &srvrSktLen) < 0)
    {
        perror("recvfrom");
        exit(EXIT_FAILURE);
    }

    printf("User %s received this message from the Calculator server: ", received_message.fullName);
    snprintf(calcMsg, sizeof(calcMsg), "%s-Calc", fullName);
    strncpy(received_message.fullName, calcMsg, sizeof(received_message.fullName) - 1);
    printMsg(stdout, &received_message);
    strncpy(received_message.fullName, fullName, sizeof(received_message.fullName) - 1);
    printf("\n");
    int result;

    // printf("User received the following: %d from FD %d\n", result, rep_read_fd);
}