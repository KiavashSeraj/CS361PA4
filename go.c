//-----------------------------------------------------------------------------------------------------
// Assignment   : <Lab04>
// Date         : 02/19/2023
//
// Author       : Kiavash Seraj
//
// File Name    : go.c
//-----------------------------------------------------------------------------------------------------

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include <sys/wait.h>

/* Wrapper function for fork() */
pid_t Fork(void)
{
    pid_t n;
    n = fork() ;
    if ( n < 0 ) 
    {
		perror("Fork failed");
		exit(-1) ;
    }
    return n;
}

#define  READ_END	0
#define  WRITE_END	1
#define  STDIN_FD	0
#define  STDOUT_FD	1

int main(void)
{                                        	
    pid_t user, calculate;
	int request[2];
    int reply[2];

	/** create the pipe */
	if ( pipe(request) == -1 || pipe(reply) == -1) 
	{
        fprintf(stderr,"Pipe failed");
        return 1;
	}

    printf("Go started and created these pipes\n" );
    printf("\tUser-to-Calculator Request pipe: read=3 write =4\n");
    printf("\tCalculator-to-User Reply pipe: read=5 write=6\n\n");

	/** now fork the Left-Child process */
	user = Fork();
	if (user == 0)   /* Left-Child process */
    {
        close(request[READ_END]);
        close(reply[WRITE_END]);


        char request_str[20];
        char reply_str[20];

        sprintf(request_str, "%d", request[WRITE_END]);
        sprintf(reply_str, "%d", reply[READ_END]);
        // start the new executable for the Left-Child
        if( execlp("./user", "user", request_str, reply_str, NULL) < 0)
        {
            perror("execlp user failed");
            exit(-1);
        }
	}
	else /* Parent process */
	{
        /* now fork the Right-Child process */
        calculate = Fork();
        if (calculate == 0)   /* Right-Child process */
        {

            close(request[WRITE_END]);
            close(reply[READ_END]);


            char request_str[20];
            char reply_str[20];

            sprintf(request_str, "%d", request[READ_END]);
            sprintf(reply_str, "%d", reply[WRITE_END]);
            // start the new executable for the Left-Child
            if( execlp("./calculator", "calculator", request_str, reply_str, NULL) < 0 )
            {
                perror("execlp calculate failed");
                exit(-1) ;
            }
        }
        else
        { 
            printf("\nGo is now waiting for User to terminate\n");
            waitpid( user , NULL , 0 ) ;
            printf("\nGo is now waiting for Calculator to terminate\n");
            waitpid( calculate, NULL , 0 ) ;
            printf("\nThe Go process has terminated\n");
        }
	}
	return 0;
}

