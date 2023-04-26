//-----------------------------------------------------------------------------------------------------
// Assignment   : <Lab04>
// Date         : 02/19/2023
//
// Author       : Kiavash Seraj
//
// File Name    : user.c
//-----------------------------------------------------------------------------------------------------

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    int request = atoi(argv[1]);
    int reply = atoi(argv[2]);


    printf("This is the User process (id = %d).\n", getpid());
    printf("\tUser: Please, enter:\tvalue1\toperation\tvalue2\n");

    int num1;
    int num2;
    char op;

    scanf("%d %c %d", &num1, &op, &num2);
    printf("\tUser Sending the following: %d %c %d on FD 4\n", num1, op, num2);
    write(request, &num1, sizeof(num1));
    write(request, &op, sizeof(op));
    write(request, &num2, sizeof(num2));

    int answer;
    read(reply, &answer, sizeof(answer));
    printf("User Received the following result: %d from FD 5\n", answer);

}