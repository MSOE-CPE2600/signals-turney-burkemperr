/**
 * File: signal_alarm.c
 * Modified by: Reagan Burkemper
 * 
 * Brief summary of program:
 * - Signal handler for SIGALRM to print a message when the alarm triggers after 5 seconds.
 * - Prints sleep until a signal is received, prints the message, than continues sleeping. 
 */

 /**
 * Instructions on how to compile & run:
 * gcc -o signal_alarm signal_alarm.c / or make
 * ./signal_alarm
 */

#include <stdio.h>
#include <signal.h>
#include <unistd.h>

/**
 * @brief handler for SIGALRM - prints a message when the alarm is triggered.
 */
void signal_handler(int signal)
{
    printf("Signal %d was received\n", signal);
}
int main()
{
    signal(SIGALRM, signal_handler);
    alarm(5);

    // Wait until a signal is received
    while(1) {
        printf("Sleeping\n");
        sleep(1);
    }
}

