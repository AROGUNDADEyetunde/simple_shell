#include "shell.h"

/**
 * free_data - Frees memory allocated for data_shell structure.
 * @datash: Pointer to the data_shell structure.
 * Return: void
 */
void free_data(data_shell *datash)
{
	unsigned int i;

	// Free environment variables
	for (i = 0; datash->_environ[i]; i++)
	{
		free(datash->_environ[i]);
	}

	free(datash->_environ);
	free(datash->pid);
}

/**
 * set_data - Initializes data_shell structure with environment variables.
 * @datash: Pointer to the data_shell structure.
 * @av: Arguments vector.
 * Return: void
 */
void set_data(data_shell *datash, char **av)
{
	unsigned int i;

	// Set data_shell members
	datash->av = av;
	datash->input = NULL;
	datash->args = NULL;
	datash->status = 0;
	datash->counter = 1;

	// Count environment variables
	for (i = 0; environ[i]; i++)
		;

	// Allocate memory for environment variables
	datash->_environ = malloc(sizeof(char *) * (i + 1));

	// Copy environment variables
	for (i = 0; environ[i]; i++)
	{
		datash->_environ[i] = _strdup(environ[i]);
	}

	datash->_environ[i] = NULL;
	datash->pid = aux_itoa(getpid());
}

/**
 * main - Entry point for the shell program.
 * @ac: Number of arguments.
 * @av: Arguments vector.
 * Return: Shell exit status.
 */
int main(int ac, char **av)
{
	data_shell datash;
	(void) ac;

	// Set up signal handler for SIGINT
	signal(SIGINT, get_sigint);

	// Initialize data_shell structure
	set_data(&datash, av);

	// Run the shell loop
	shell_loop(&datash);

	// Free allocated memory
	free_data(&datash);

	// Return shell exit status
	if (datash.status < 0)
		return (255);
	return (datash.status);
}
