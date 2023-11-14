#include "shell.h"

/**
 * exec_line - Executes a command line in the shell.
 *
 * @datash: Pointer to the data structure containing shell information.
 * Return: Returns the status of the executed command.
 */
int exec_line(data_shell *datash)
{
    // Function pointer to store the address of the detected built-in command
    int (*builtin)(data_shell *datash);

    // If the command is empty, return success
    if (datash->args[0] == NULL)
        return (1);

    // Check if the command is a built-in command
    builtin = get_builtin(datash->args[0]);

    // If it is a built-in command, execute it
    if (builtin != NULL)
        return (builtin(datash));

    // If it is not a built-in command, execute it as an external command
    return (cmd_exec(datash));
}

