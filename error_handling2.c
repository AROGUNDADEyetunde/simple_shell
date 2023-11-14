#include "shell.h"

/**
 * error_env - Generates an error message for issues related to environment.
 * @datash: Data structure containing shell information.
 * Return: Pointer to error message.
 */
char *error_env(data_shell *datash)
{
    int length;
    char *error;
    char *ver_str;
    char *msg;

    // Generating string representation of the shell's counter
    ver_str = aux_itoa(datash->counter);

    // Setting error message and calculating the length
    msg = ": Unable to add/remove from environment\n";
    length = _strlen(datash->av[0]) + _strlen(ver_str);
    length += _strlen(datash->args[0]) + _strlen(msg) + 4;

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
    _strcat(error, msg);
    _strcat(error, "\0");
    free(ver_str);

    return (error);
}

/**
 * error_path_126 - Generates an error message for 'Permission denied' (exit code 126).
 * @datash: Data structure containing shell information.
 * Return: Pointer to the error message.
 */
char *error_path_126(data_shell *datash)
{
    int length;
    char *ver_str;
    char *error;

    // Generating string representation of the shell's counter
    ver_str = aux_itoa(datash->counter);

    // Calculating the length of the error message
    length = _strlen(datash->av[0]) + _strlen(ver_str);
    length += _strlen(datash->args[0]) + 24;

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
    _strcat(error, ": Permission denied\n");
    _strcat(error, "\0");
    free(ver_str);

    return (error);
}
