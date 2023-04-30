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

    struct sockaddr_in serverSocket, clientSocket;
    unsigned short port = 13;
    time_t now;
    char buf[ MAXBUFLEN ];
    char ipAddress[ IPSTRLEN ];
    char timeStr[MAXBUFLEN ];

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
    
    if ( bind(socketfd, (SA *)&serverSocket, sizeof(serverSocket)) < 0 ) {
        snprintf( buf, MAXBUFLEN, "Could NOT bind to port %d\n", port);
        err_sys(buf);
    }

    inet_ntop (AF_INET, (void *)&serverSocket.sin_addr.s_addr, ipAddress, IPSTRLEN);
    printf("\nBound socket %d to IP %s Port %d\n", sd, ipAddress, ntohs(serverSocket.sin_port));
    

    while(1) {
        addressLength = sizeof(clientSocket);
        printf("\nCALCULATOR server waiting for Requests\n");

        if (recvfrom(socketfd, buf, MAXBUFLEN, 0, (SA *) &clientSocket, &addressLength) < 0){
            err_sys("recvfrom");
        }

        printf("CALCULATOR server recieved: { Name=~~~~~~~~~}\n");

    }









    int num1;
    char op;
    int num2;

    read(req_write_fd, &num1, sizeof(num1));
    read(req_write_fd, &op, sizeof(op));
    read(req_write_fd, &num2, sizeof(num2));

    printf("\tCalculator received the following: %d %c %d from FD %d\n", num1, op, num2, req_write_fd);

    int result;
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

    printf("Calculator sent the following to the User: %d on FD %d\n", result, rep_read_fd);
}
