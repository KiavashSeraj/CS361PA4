//-----------------------------------------------------------------------------------------------------
// Assignment   : <Lab04>
// Date         : 02/19/2023
//
// Author       : Kiavash Seraj
//
// File Name    : calculator.c
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
    printf("Calculator Waiting to receive from FD 3\n");

    int num1;
    int num2;
    char op;

    read(request, &num1, sizeof(num1));
    read(request, &op, sizeof(op));
    read(request, &num2, sizeof(num2));

    printf("\tCalculator received the following: %d %c %d on FD 3\n", num1, op, num2);
    int result;
    switch (op) {
        case '+': result = num1 + num2; break;
        case '-': result = num1 - num2; break;
        case '*': result = num1 * num2; break;
        case '/': result = num1 / num2; break;
        default:
            fprintf(stderr, "Invalid operator: %c\n", op);
    }

    printf("Calculator sent the following to the User: %d on FD 6\n", result);

    write(reply, &result, sizeof(result));
}