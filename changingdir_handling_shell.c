#include "shell.h"

/**
 * cd_shell - Changes the current working directory based on the provided arguments.
 * @datash: Data structure containing shell information.
 * Return: Always returns 1 to continue shell execution.
 */
int cd_shell(data_shell *datash)
{
	char *dir;
	int ishome, ishome2, isddash;

	// Get the directory argument from the command
	dir = datash->args[1];

	// Check if the directory is specified or matches special cases
	if (dir != NULL)
	{
		// Check if the directory is "$HOME" or "~"
		ishome = _strcmp("$HOME", dir);
		ishome2 = _strcmp("~", dir);

		// Check if the directory is "--"
		isddash = _strcmp("--", dir);
	}

	// If no directory is specified or matches special cases, change to the home directory
	if (dir == NULL || !ishome || !ishome2 || !isddash)
	{
		cd_to_home(datash);
		return (1);
	}

	// If the directory is "-", change to the previous directory
	if (_strcmp("-", dir) == 0)
	{
		cd_previous(datash);
		return (1);
	}

	// If the directory is ".", change to the previous directory or remain in the current directory
	if (_strcmp(".", dir) == 0 || _strcmp("..", dir) == 0)
	{
		cd_dot(datash);
		return (1);
	}

	// Change to the specified directory
	cd_to(datash);

	// Always return 1 to continue shell execution
	return (1);
}
