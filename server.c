/**
 * @file server.c
 * @brief Implements the serving player for the signal tennis game, with clean termination if the receiver ends.
 * 
 * Modified by: Reagan Burkemper
 * 
 * Instructions:
 * 1. Compile: gcc -o server server.c
 * 2. Run the receiver first and note its PID.
 * 3. Start the server: ./server <receiver_pid>
 */

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <time.h>
#include <errno.h>

volatile int volley_count = 0; // Keeps track of volley count
pid_t receiver_pid;            // Stores the PID of the receiver

/**
 * @brief Signal handler for the "ball" signal.
 */
void handle_ball(int sig, siginfo_t *info, void *context) {
    printf("\007Server: Received the ball from PID %d. Volley count: %d\n", info->si_pid, volley_count);

    // Check if the game should end
    if (volley_count >= 10) {
        printf("Server: Game over! Total volleys: %d\n", volley_count);
        union sigval value;
        value.sival_int = volley_count;
        printf("\007Server: Hitting the ball back to PID %d.\n", receiver_pid);
        if (sigqueue(receiver_pid, SIGUSR1, value) == -1) {
            if (errno == ESRCH) { // ESRCH: No such process
                printf("Server: Receiver process (PID %d) has terminated. Ending game.\n", receiver_pid);
                exit(0);
            }
            perror("sigqueue");
            exit(1);
        }
        exit(0);
    }


    usleep((rand() % 2 + 1) * 1000000); // random time from 1 to 2 seconds

    volley_count++; // add number of volleys

    // sends the ball back to the receiver
    union sigval value; 
    value.sival_int = volley_count;
    printf("\007Server: Hitting the ball back to PID %d.\n", receiver_pid);
    if (sigqueue(receiver_pid, SIGUSR1, value) == -1) {
        if (errno == ESRCH) { // ESRCH: if theres no such process
            printf("Server: Receiver process (PID %d) has terminated. Ending game.\n", receiver_pid);
            exit(0);
        }
        perror("sigqueue");
        exit(1);
    }
}

// Checks if the receiver process is still running.
void check_receiver_alive() {
    if (kill(receiver_pid, 0) == -1) {
        if (errno == ESRCH) { // ESRCH: No such process
            printf("Server: Receiver process (PID %d) has terminated. Ending game.\n", receiver_pid);
            exit(0);
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <receiver_pid>\n", argv[0]);
        return 1;
    }

    receiver_pid = atoi(argv[1]);
    if (receiver_pid <= 0) {
        fprintf(stderr, "Invalid receiver PID: %s\n", argv[1]);
        return 1;
    }

    srand(time(NULL)); // seed random number generator

    // setting up the signal handler
    struct sigaction sa;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_SIGINFO;
    sa.sa_sigaction = handle_ball;

    if (sigaction(SIGUSR1, &sa, NULL) == -1) {
        perror("sigaction");
        return 1;
    }

    // to serve the first ball
    union sigval value;
    value.sival_int = volley_count;
    printf("\007Server: Serving the ball to PID %d.\n", receiver_pid);
    if (sigqueue(receiver_pid, SIGUSR1, value) == -1) {
        if (errno == ESRCH) { // ESRCH: if no such process
            printf("Server: Receiver process (PID %d) has terminated. Exiting.\n", receiver_pid);
            exit(0);
        }
        perror("sigqueue");
        return 1;
    }

    // wait for signals indefinitely, periodically checking receiver status
    while (1) {
        check_receiver_alive(); 
        pause();
    }

    return 0;
}
