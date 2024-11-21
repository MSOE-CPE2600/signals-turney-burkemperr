/**
 * @file send_signal.c
 * Brief summary of program:
 * - Sends SIGUSR1 with a random integer to the process using `sigqueue`.
 * - It will print the number in the sending program before sending SIGUSR1
 * 
 * Modified by: Reagan Burkemper
 * 
 * Instructions:
 * - Compile the program: 
 *      gcc -o send_signal send_signal.c
 * - Run the program (with the PID of `recv_signal` as an argument):
 *    ./send_signal <PID>
 * - To see the output in the terminal see running `recv_signal`.
 */

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>

/**
 * Main function to send SIGUSR1 with an attached random integer to a target PID.
 */
int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <PID>\n", argv[0]);
        return 1;
    }

    // Convert the provided PID argument to an integer
    pid_t target_pid = atoi(argv[1]);
    if (target_pid <= 0) {
        fprintf(stderr, "Invalid PID: %s\n", argv[1]);
        return 1;
    }

    // Seed the random number generator
    srand(time(NULL));

    // Generate a random integer
    int random_value = rand() % 100; // Random value between 0 and 99
    printf("Sending SIGUSR1 with value: %d to PID: %d\n", random_value, target_pid);

    // Prepare the sigval structure to send the value
    union sigval sig_data;
    sig_data.sival_int = random_value;

    // Send the signal with the random value using sigqueue
    if (sigqueue(target_pid, SIGUSR1, sig_data) == -1) {
        perror("sigqueue");
        return 1;
    }

    return 0;
}
