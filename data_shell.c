#include "shell.h"

/**
 * get_builtin - Returns a function pointer to a built-in command.
 * @cmd: Command name.
 * Return: Function pointer to the corresponding built-in function.
 */
int (*get_builtin(char *cmd))(data_shell *)
{
	// Array of structs representing built-in commands and their corresponding functions
	builtin_t builtin[] = {
		{ "env", _env },
		{ "exit", exit_shell },
		{ "setenv", _setenv },
		{ "unsetenv", _unsetenv },
		{ "cd", cd_shell },
		{ "help", get_help },
		{ NULL, NULL }
	};
	int i;

	// Iterate through the array to find a match for the given command
	for (i = 0; builtin[i].name; i++)
	{
		if (_strcmp(builtin[i].name, cmd) == 0)
			break;
	}

	// Return the corresponding function pointer
	return (builtin[i].f);
}
