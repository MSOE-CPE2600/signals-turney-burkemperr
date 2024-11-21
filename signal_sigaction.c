/**
 * @file signal_sigaction.c
 * @brief Demonstrates using the sigaction system call to register a signal handler.
 *        The handler prints the process identifier (PID) of the sender of SIGUSR1.
 * 
 * Modified by: Reagan Burkemper
 * 
 * Brief summary of modifications:
 * - Uses `sigaction` to register a handler for SIGUSR1.
 * - The handler prints the PID of the signal sender.
 * 
 * Instructions to send SIGUSR1:
 * - Compile the program: 
 *      gcc -o signal_sigaction signal_sigaction.c or make
 * - Run the program: 
 *      ./signal_sigaction
 * - to find the PID of the running program:
 *    ps -aux | grep signal_sigaction
 * - to send SIGUSR1 to the process using:
 *    kill -SIGUSR1 <PID>
 */
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

void handle_sigusr1(int signal, siginfo_t *info, void*) 
{
    printf("Received SIGUSR1 from process with PID: %d\n", info->si_pid);
}

int main()
{
    struct sigaction sa;

    sigemptyset(&sa.sa_mask); // zeros out the struct
    sa.sa_flags = SA_SIGINFO; // enable extended signal information
    sa.sa_sigaction = handle_sigusr1; // register the signal handler

    // register the signal handler for SIGUSR1
    if (sigaction(SIGUSR1, &sa, NULL) == -1) {
        perror("sigaction");
        exit(1);
    }

    while(1) {
        //printf("Sleeping\n");
        sleep(1);
    }


    return 0;
}