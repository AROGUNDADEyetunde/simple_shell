#include "shell.h"

/**
 * get_sigint - Handles the SIGINT signal (Ctrl+C) by printing a message.
 * @sig: The signal number (unused in the function but required for the signal handler).
 */
void get_sigint(int sig)
{
    (void)sig; // To avoid unused parameter warning

    // Write a message to the standard output when Ctrl+C is pressed
    write(STDOUT_FILENO, "\n^-^ ", 5);
}
