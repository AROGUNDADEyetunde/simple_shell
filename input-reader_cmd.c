#include "shell.h"

/**
 * read_line - Reads a line of input from the user.
 *
 * @i_eof: Pointer to store the return value of the getline function.
 * Return: A pointer to the input string.
 */
char *read_line(int *i_eof)
{
    char *input = NULL; // Pointer to store the input string
    size_t bufsize = 0; // Initial size of the input buffer

    *i_eof = getline(&input, &bufsize, stdin); // Reads a line of input from stdin

    return (input); // Returns the input string
}
