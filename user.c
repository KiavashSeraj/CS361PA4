/*----------------------------------------------------------------------
PA-04  The User process
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
/* -------------------------------------------------------------------*/
int main(int argc, char *argv[])
{
    int req_write_fd = atoi(argv[0]);
    int rep_read_fd = atoi(argv[1]);

    printf("This is the User process (id = %d)\n", getpid());
    printf("\tUser: Please, enter:\tvalue1\toperation\tvalue2\n");

    int num1;
    char op;
    int num2;

    

    scanf("%d %c %d", &num1, &op, &num2);
    printf("\tUser Sending the following: %d %c %d on FD %d\n", num1, op, num2, req_write_fd);
    write(req_write_fd, &num1, sizeof(num1));
    write(req_write_fd, &op, sizeof(op));
    write(req_write_fd, &num2, sizeof(num2));

    int result;

    read(rep_read_fd, &result, sizeof(int));

    printf("User received the following: %d from FD %d\n", result, rep_read_fd);

}