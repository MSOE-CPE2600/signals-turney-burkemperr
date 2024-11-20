/**
 * @file signal_segfault.c
 * @brief Program that dereferences a null pointer causing a segmentation fault
 */

/**
 * Modified by: Reagan Burkemper
 * 
 * Brief summary of modifications:
 * - Installed a handler for SIGSEGV to catch segmentation faults and print a message.
 */

/**
 * Behavior:
 * - When SIGSEGV occurs, the handler prints out the message.
 * - The program then resumes execution, this will re-trigger the segmentation fault
 *   because the invalid memory access is repeated.
 * - The message will print out over and over again in the terminal.
 * Reason:
 * - The signal handler does not fix the invalid memory access. The handler catches 
 *   the signal but does not change the issue, it continues the program.
 */

#include <stdio.h>
#include <signal.h>
/**
 * @brief Handles SIGSEGV - prints a message when a segmentation fault occurs.
 */

void handle_sigsegv(int signal) {
    printf("Caught SIGSEGV (Segmentation Fault): %d\n", signal);
    return; 

}


int main (int argc, char* argv[]) {
    signal(SIGSEGV, handle_sigsegv);
    // Declare a null pointer
    int* i = NULL;

    // Dereference the null pointer
    printf("The value of i is: %d\n", *i);

    // Return to exit the program
    return 0;
}