#include "shell.h"

/**
 * exit_shell - Handles the 'exit' command for the shell.
 *
 * datash: Data structure containing shell information.
 * Return: 1 if there is an error, 0 otherwise.
 */
int exit_shell(data_shell *datash)
{
    unsigned int ustatus;
    int is_digit;
    int str_len;
    int big_number;

    // Checks if an exit status is provided
    if (datash->args[1] != NULL)
    {
        // Convert the exit status argument to an unsigned integer
        ustatus = _atoi(datash->args[1]);
        
        // Checks if the argument is a digit
        is_digit = _isdigit(datash->args[1]);
        
        // Gets the length of the argument
        str_len = _strlen(datash->args[1]);
        
        // Checks if the exit status is a big number
        big_number = ustatus > (unsigned int)INT_MAX;

        // Checks for invalid exit status conditions
        if (!is_digit || str_len > 10 || big_number)
        {
            get_error(datash, 2); // Display an error message
            datash->status = 2;   // Set the shell status to 2 (error)
            return (1);
        }

        // Sets the shell status to the provided exit status
        datash->status = (ustatus % 256);
    }

    return (0); // Return 0 for successful execution
}
