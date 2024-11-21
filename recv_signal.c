/**
 * @file recv_signal.c
 *
 * Modified by: Reagan Burkemper
 * 
 * Brief summary of program:
 * -uses sigaction to register a handler for the SIGUSR1 signal than waits in an
 *  infinite loop 
 *
 * Instructions:
 * - Compile the program: 
 *      gcc -o recv_signal recv_signal.c
 * - Run the program: 
 *     ./recv_signal
 * - Find the process ID (PID) of the running program:
 *    ps -aux | grep recv_signal
 * - To get this PID use `send_signal` to send SIGUSR1
 */

#include <stdio.h>
#include <signal.h>
#include <unistd.h>


// signal handler for SIGUSR1 that prints the attached integer value.
 void handle_sigusr1(int sig, siginfo_t *info, void *context) 
 {
    printf("Received SIGUSR1 with value: %d\n", info->si_value.sival_int);
}

int main() {
    struct sigaction sa;

    // Zero out the sigaction struct
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_SIGINFO; // Enable extended signal information
    sa.sa_sigaction = handle_sigusr1; // Register the signal handler

    // Register the signal handler for SIGUSR1
    if (sigaction(SIGUSR1, &sa, NULL) == -1) {
        perror("sigaction");
        return 1;
    }

    printf("Waiting for SIGUSR1...\n");

    // Wait indefinitely for signals
    while (1) 
    {
        while(1) 
        {
            sleep(1);
        }
    }

    return 0;
}