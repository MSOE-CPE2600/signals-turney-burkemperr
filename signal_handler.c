/**
 * @file signal_handler.c
 * @brief Sets a signal handler for SIGINT, the handler prints a message and then quits
 */

/**
 * Modified by:Reagan Burkemper
 * 
 * Brief summary of modifications:
 * - Updated the signal handler for SIGINT to prevent the program from exiting.
 *
 * Instructions on how to test:
 * -Compile the program using gcc:
 *    gcc -o signal_handler signal_handler.c
 * -Run the program:
 *    ./signal_handler
 * -Send SIGINT to the process:
 *    -Press CTRL+C in the terminal running the program.
 *    -Find the process ID (PID) of the program using in another:
 *       ps -aux | grep signal_handler
 *       Send SIGINT using:
 *       kill -SIGINT <PID>
 *          it will print the signal message and continues running.
 * -To terminate the program, send SIGKILL:
 *    kill -SIGKILL <PID>
 */

#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

 /**
 * @brief Signal handler for SIGINT - prints a message but does not exit.
 *        The program continues running.
 */
void handle_signal(int signal) {
    printf("Received a signal: %d\n", signal);
    //exit(1);
}

int main() {

    // Register for the signal
    signal(SIGINT, handle_signal);

    // Wait until a signal is received
    while(1) {
        printf("Sleeping\n");
        sleep(1);
    }

    return 0;
}