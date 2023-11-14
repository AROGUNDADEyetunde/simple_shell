#include "shell.h"

/**
 * strcat_cd - Concatenates error message components for 'cd' command.
 * @datash: Data structure containing shell information.
 * @msg: Message indicating the type of error.
 * @error: Buffer to store the concatenated error message.
 * @ver_str: String representation of the shell's counter.
 * Return: Pointer to the concatenated error message.
 */

char *strcat_cd(data_shell *datash, char *msg, char *error, char *ver_str)
{
    char *illegal_flag;

    // Copying base error message
    _strcpy(error, datash->av[0]);
    _strcat(error, ": ");
    _strcat(error, ver_str);
    _strcat(error, ": ");
    _strcat(error, datash->args[0]);
    _strcat(error, msg);

    // Handling illegal flag if present
    if (datash->args[1][0] == '-')
    {
        illegal_flag = malloc(3);
        illegal_flag[0] = '-';
        illegal_flag[1] = datash->args[1][1];
        illegal_flag[2] = '\0';
        _strcat(error, illegal_flag);
        free(illegal_flag);
    }
    else
    {
        _strcat(error, datash->args[1]);
    }

    _strcat(error, "\n");
    _strcat(error, "\0");
    return (error);
}

 /**
 *
 * error_get_cd - Generates error message for 'cd' command.
 * @datash: Data structure containing shell information.
 * Return: Pointer to the error message.
 */

char *error_get_cd(data_shell *datash)
{
    int length, len_id;
    char *error, *ver_str, *msg;

    // Generating string representation of the shell's counter
    ver_str = aux_itoa(datash->counter);

    // Determining error message type and length
    if (datash->args[1][0] == '-')
    {
        msg = ": Illegal option ";
        len_id = 2;
    }
    else
    {
        msg = ": can't cd to ";
        len_id = _strlen(datash->args[1]);
    }

    length = _strlen(datash->av[0]) + _strlen(datash->args[0]);
    length += _strlen(ver_str) + _strlen(msg) + len_id + 5;

    // Allocating memory for the error message
    error = malloc(sizeof(char) * (length + 1));

    // Checking for allocation failure
    if (error == 0)
    {
        free(ver_str);
        return (NULL);
    }

    // Constructing the error message using strcat_cd function
    error = strcat_cd(datash, msg, error, ver_str);

    // Freeing memory used for string representation of the counter
    free(ver_str);

    return (error);
}

/**
 * error_not_found - Generates error message for command not found.
 * @datash: Data structure containing shell information.
 * Return: Pointer to the error message.
 */
char *error_not_found(data_shell *datash)
{
    int length;
    char *error;
    char *ver_str;

    // Generating string representation of the shell's counter
    ver_str = aux_itoa(datash->counter);

    // Calculating the length of the error message
    length = _strlen(datash->av[0]) + _strlen(ver_str);
    length += _strlen(datash->args[0]) + 16;

    // Allocating memory for the error message
    error = malloc(sizeof(char) * (length + 1));

    // Checking for allocation failure
    if (error == 0)
    {
        free(error);
        free(ver_str);
        return (NULL);
    }

    // Constructing the error message
    _strcpy(error, datash->av[0]);
    _strcat(error, ": ");
    _strcat(error, ver_str);
    _strcat(error, ": ");
    _strcat(error, datash->args[0]);
    _strcat(error, ": not found\n");
    _strcat(error, "\0");

    // Freeing memory used for string representation of the counter
    free(ver_str);

    return (error);
}

/**
 * error_exit_shell - Generates error message for illegal shell exit.
 * @datash: Data structure containing shell information.
 * Return: Pointer to the error message.
 */
char *error_exit_shell(data_shell *datash)
{
    int length;
    char *error;
    char *ver_str;

    // Generating string representation of the shell's counter
    ver_str = aux_itoa(datash->counter);

    // Calculating the length of the error message
    length = _strlen(datash->av[0]) + _strlen(ver_str);
    length += _strlen(datash->args[0]) + _strlen(datash->args[1]) + 23;

    // Allocating memory for the error message
    error = malloc(sizeof(char) * (length + 1));

    // Checking for allocation failure
    if (error == 0)
    {
        free(ver_str);
        return (NULL);
    }

    // Constructing the error message
    _strcpy(error, datash->av[0]);
    _strcat(error, ": ");
    _strcat(error, ver_str);
    _strcat(error, ": ");
    _strcat(error, datash->args[0]);
    _strcat(error, ": Illegal number: ");
    _strcat(error, datash->args[1]);
    _strcat(error, "\n\0");

    // Freeing memory used for string representation of the counter
    free(ver_str);

    return (error);
}
