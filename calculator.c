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
int main(int argc, char *argv[])
{

    int sockfd = socket(AF_INET, SOCK_DGRAM, 0); // SOCK_DGRAM for UDP

    int req_write_fd = atoi(argv[0]);
    int rep_read_fd = atoi(argv[1]);
    printf("This is the Calculator process (id = %d).\t\n", getpid());
    printf("Calculator waiting to receive from FD %d\n", req_write_fd);

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

    write(rep_read_fd, &result, sizeof(result));
    return 0;
}