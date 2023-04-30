/*----------------------------------------------------------------------
PA-04  The Calculator process
Written By: Mateen Faieq and Kiavash Seraj
Submitted on: 05/01/2023
----------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include "message.h"
/* -------------------------------------------------------------------*/

#define MAXBUFLEN 256
#define IPSTRLEN 50
typedef struct sockaddr SA ;
/*------------------------------------------------------------------------
* Error Handling Functions
*----------------------------------------------------------------------*/
void err_sys(const char* msg)
{
    fflush( stderr ) ;
    perror( msg ) ;
    exit( 1 );
}


int main(int argc, char *argv[])
{



    int num1;
    char op;
    int num2;
    int result;
    

    struct sockaddr_in serverSocket, clientSocket;
    unsigned short port = 13;
    time_t now;
    char buf[ MAXBUFLEN ];
    char ipAddress[ IPSTRLEN ];
    char timeStr[MAXBUFLEN ];

    calcMsg received_message;
    ssize_t received_len

    unsigned int addressLength;


    int socketfd = socket(AF_INET, SOCK_DGRAM, 0); // SOCK_DGRAM for UDP
    if (socketfd < 0) {
        err_sys("Could NOT create socket\n");
    }

    // Prepare the server's socket address structure
    memset((void *)&serverSocket, 0, sizeof(serverSocket));
    serverSocket.sin_family = AF_INET;
    serverSocket.sin_addr.s_addr = htonl(INADDR_ANY);
    serverSocket.sin_port = htons(port);

    printf("\nThis is the Calculator server developed by Kiavash Seraj & Mateen Faieq\n");
    
    if ( bind(socketfd, (struct sockaddr *)&serverSocket, sizeof(serverSocket)) < 0 ) {
        snprintf( buf, MAXBUFLEN, "Could NOT bind to port %d\n", port);
        err_sys(buf);
    }

    inet_ntop (AF_INET, (void *)&serverSocket.sin_addr.s_addr, ipAddress, IPSTRLEN);
    printf("\nBound socket %d to IP %s Port %d\n", sd, ipAddress, ntohs(serverSocket.sin_port));
    

    while(1) {
        addressLength = sizeof(clientSocket);
        printf("\nCALCULATOR server waiting for Requests\n");

        if (recvfrom(socketfd, &received_message, sizeof(calcMsg), 0, (struct sockaddr *) &clientSocket, &addressLength) < 0){
            err_sys("recvfrom");
        }

        received_message.msgType = ntohl(received_message.msgType);
        received_message.num1 = ntohl(received_message.num1);
        received_message.num2 = ntohl(received_message.num2);
        received_message.operation = ntohl(received_message.operation);
        received_message.result = ntohl(received_message.result);
        received_message.fullName = ntohl(received_message.fullName);

        num1 = received_message.num1;
        num2 = received_message.num2;
        op = received_message.operation;

        
        printf("CALCULATOR server recieved: { Name='%s' Type=%d , %d %c %d , result=\t%d }\n");
        inet_ntop(AF_INET, (void *) &clientSocket.sin_addr.s_addr, ipAddress, IPSTRLEN);
        printf("\tfrom IP %s port %d\n", ipAddress, ntohs(clientSocket.sin_port));

        switch (op)
        {
        case '+':
            result = num1 + num2;
            break;
        case '-':
            result = num1 - num2;
            break;
        case '*':
            result = num1 * num2;
            break;
        case '/':
            result = num1 / num2;
            break;
        default:
            printf("\nINVALID operation\n");
            result = -9999;
        };

        calcMsg send_message;
        send_message.msgType = 2;
        send_message.num1 = num1;
        send_message.num2 = num2;
        send_message.operation = op;
        send_message.result = result;
        send_message.fullName = "Kiavash Seraj & Mateen Faieq-Calculator";

        sendto(socketfd, (void *) &send_message, sizeof(struct calcMsg), 0, (struct sockaddr *)&clientSocket, addressLength);

    }
}