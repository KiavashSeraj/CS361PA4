/*----------------------------------------------------------------------
PA-04: UDP Socket Programming
            Message Layouts

Written By: Team-00
    1- Mateen Faieq
    2- Kiavash Seraj

Submitted on: 05/01/2023
----------------------------------------------------------------------*/

#ifndef  MESSAGE_H
#define  MESSAGE_H

#include <sys/types.h>
#include <stdio.h>

typedef struct   // Using Network Byte-Order
{
    int  msgType ;         /* 1: request , 2: reply , etc. */
    int  num1, num2 ;      /* two operands */
    char operation ;       /* arithmetic operation '+' , '-' , 'x' , '/' */
    int  result ;          /* result of  num1 operation num2 */
    char fullName[125] ;    // snprintf your full name into this array
} calcMsg ;

typedef struct
{
    char  fullName[125] ;  // snprintf your full name into this array

    char  ipStr[30] ;     // snprintf the IP address of your Calculator server here
                          // in dotted decimal format

    short port ;          // Tell me the port number of your Calculator server
                          // in Network Byte-Order
} student ;

void printMsg( FILE *log , calcMsg *m ) ;
void printStudent( FILE *log , student *m ) ;

#endif