#include "shell.h"

/**
 * get_help - Displays help information for shell built-in commands.
 * @datash: Data structure containing shell information.
 * Return: 1 (success).
 */
int get_help(data_shell *datash)
{
    // Check if a specific command is/is not provided
    if (datash->args[1] == 0)
        aux_help_general(); // Display general help information
    else if (_strcmp(datash->args[1], "setenv") == 0)
        aux_help_setenv(); // Display help information for 'setenv' command
    else if (_strcmp(datash->args[1], "env") == 0)
        aux_help_env(); // Display help information for 'env' command
    else if (_strcmp(datash->args[1], "unsetenv") == 0)
        aux_help_unsetenv(); // Display help information for 'unsetenv' command
    else if (_strcmp(datash->args[1], "help") == 0)
        aux_help(); // Display help information for 'help' command
    else if (_strcmp(datash->args[1], "exit") == 0)
        aux_help_exit(); // Display help information for 'exit' command
    else if (_strcmp(datash->args[1], "cd") == 0)
        aux_help_cd(); // Display help information for 'cd' command
    else if (_strcmp(datash->args[1], "alias") == 0)
        aux_help_alias(); // Display help information for 'alias' command
    else
        // If an unknown command is provided, display an error message
        write(STDERR_FILENO, datash->args[0], _strlen(datash->args[0]));

    datash->status = 0; // Reset the shell status
    return (1); // Return success
}
