/**
 * @file receiver.c
 * @brief Implements the receiving player for the signal tennis game.
 * 
 * Modified by: Reagan Burkemper
 * 
 * Instructions:
 * 1. Compile: gcc -o receiver receiver.c
 * 2. Run the receiver: ./receiver
 * 3. Note the PID printed by the receiver and pass it to the server.
 */

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <time.h>

volatile int volley_count = 0; // keeps track of volley count
pid_t sender_pid;              // stores the PID of the sender (server)

/**
 * @brief Signal handler for the "ball" signal.
 */
void handle_ball(int sig, siginfo_t *info, void *context) {
    sender_pid = info->si_pid; // Capture sender's PID
    printf("\007Receiver: Received the ball from PID %d. Volley count: %d\n", sender_pid, volley_count);

    // Check if the game should end
    if (volley_count >= 11) {
        printf("Receiver: Game over! Total volleys: %d\n", volley_count-1);
        exit(0);
        
    }

    usleep((rand() % 2 + 1) * 1000000); // random time from 1 to 2 seconds

    volley_count++; // volley count

    // sending the ball back to the sender
    union sigval value;
    value.sival_int = volley_count;
    printf("\007Receiver: Hitting the ball back to PID %d.\n", sender_pid);
    if (sigqueue(sender_pid, SIGUSR1, value) == -1) {
        perror("sigqueue");
        exit(1);
    }
}

int main() {
    srand(time(NULL)); // seed random number generator

    printf("Receiver PID: %d\n", getpid()); // print the pid so the sender can use it

    // setting up the signal handler
    struct sigaction sa;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_SIGINFO;
    sa.sa_sigaction = handle_ball;

    if (sigaction(SIGUSR1, &sa, NULL) == -1) {
        perror("sigaction");
        return 1;
    }

    // wait for signals 
    printf("Receiver: Waiting for the ball...\n");
    while (1) pause();

    return 0;
}
