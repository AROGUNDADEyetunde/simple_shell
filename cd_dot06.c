#include "shell.h"

/**
 * cd_dot - Changes directory to the previous directory or remains in the current directory.
 * @datash: Data structure containing shell information.
 * Return: None.
 */
void cd_dot(data_shell *datash)
{
	char pwd[PATH_MAX];
	char *dir, *cp_pwd, *cp_strtok_pwd;

	// Get the current working directory
	getcwd(pwd, sizeof(pwd));
	cp_pwd = _strdup(pwd);

	// Set the environment variable OLDPWD to the current working directory
	set_env("OLDPWD", cp_pwd, datash);

	dir = datash->args[1];

	// Check if the directory is "."
	if (_strcmp(".", dir) == 0)
	{
		// Set the environment variable PWD to the current working directory
		set_env("PWD", cp_pwd, datash);
		free(cp_pwd);
		return;
	}

	// Check if the current directory is root ("/")
	if (_strcmp("/", cp_pwd) == 0)
	{
		free(cp_pwd);
		return;
	}

	// Reverse the current working directory string for processing
	cp_strtok_pwd = cp_pwd;
	rev_string(cp_strtok_pwd);
	cp_strtok_pwd = _strtok(cp_strtok_pwd, "/");

	// Process the reversed string to get the next directory
	if (cp_strtok_pwd != NULL)
	{
		cp_strtok_pwd = _strtok(NULL, "\0");

		if (cp_strtok_pwd != NULL)
			rev_string(cp_strtok_pwd);
	}

	// Change the directory to the new path
	if (cp_strtok_pwd != NULL)
	{
		chdir(cp_strtok_pwd);
		set_env("PWD", cp_strtok_pwd, datash);
	}
	else
	{
		chdir("/");
		set_env("PWD", "/", datash);
	}

	// Set the status to 0 (success)
	datash->status = 0;
	free(cp_pwd);
}

/**
 * cd_to - Changes directory to the specified directory.
 * @datash: Data structure containing shell information.
 * Return: None.
 */
void cd_to(data_shell *datash)
{
	char pwd[PATH_MAX];
	char *dir, *cp_pwd, *cp_dir;

	// Get the current working directory
	getcwd(pwd, sizeof(pwd));

	dir = datash->args[1];

	// Change the directory to the specified path
	if (chdir(dir) == -1)
	{
		// Handle error if chdir fails
		get_error(datash, 2);
		return;
	}

	// Set the environment variable OLDPWD to the current working directory
	cp_pwd = _strdup(pwd);
	set_env("OLDPWD", cp_pwd, datash);

	// Set the environment variable PWD to the new working directory
	cp_dir = _strdup(dir);
	set_env("PWD", cp_dir, datash);

	// Free allocated memory
	free(cp_pwd);
	free(cp_dir);

	// Set the status to 0 (success)
	datash->status = 0;

	// Change the directory to the new path
	chdir(dir);
}

/**
 * cd_previous - Changes directory to the previous directory stored in OLDPWD.
 * @datash: Data structure containing shell information.
 * Return: None.
 */
void cd_previous(data_shell *datash)
{
	char pwd[PATH_MAX];
	char *p_pwd, *p_oldpwd, *cp_pwd, *cp_oldpwd;

	// Get the current working directory
	getcwd(pwd, sizeof(pwd));
	cp_pwd = _strdup(pwd);

	// Get the value of OLDPWD from the environment variables
	p_oldpwd = _getenv("OLDPWD", datash->_environ);

	// If OLDPWD is not set, use the current working directory
	if (p_oldpwd == NULL)
		cp_oldpwd = cp_pwd;
	else
		cp_oldpwd = _strdup(p_oldpwd);

	// Set the environment variable OLDPWD to the current working directory
	set_env("OLDPWD", cp_pwd, datash);

	// Change the directory to the previous directory
	if (chdir(cp_oldpwd) == -1)
		set_env("PWD", cp_pwd, datash);
	else
		set_env("PWD", cp_oldpwd, datash);

	// Get the current working directory for display
	p_pwd = _getenv("PWD", datash->_environ);

	// Write the current working directory to standard output
	write(STDOUT_FILENO, p_pwd, _strlen(p_pwd));
	write(STDOUT_FILENO, "\n", 1);

	// Free allocated memory
	free(cp_pwd);
	if (p_oldpwd)
		free(cp_oldpwd);

	// Set the status to 0 (success)
	datash->status = 0;

	// Change the directory to the new path
	chdir(p_pwd);
}

/**
 * cd_to_home - Changes directory to the user's home directory.
 * @datash: Data structure containing shell information.
 * Return: None.
 */
void cd_to_home(data_shell *datash)
{
	char *p_pwd, *home;
	char pwd[PATH_MAX];

	// Get the current working directory
	getcwd(pwd, sizeof(pwd));
	p_pwd = _strdup(pwd);

	// Get the value of HOME from the environment variables
	home = _getenv("HOME", datash->_environ);

	// If HOME is not set, set OLDPWD to the current working directory
	if (home == NULL)
	{
		set_env("OLDPWD", p_pwd, datash);
		free(p_pwd);
		return;
	}

	// Change the directory to the user's home directory
	if (chdir(home) == -1)
	{
		// Handle error if chdir fails
		get_error(datash, 2);
		free(p_pwd);
		return;
	}

	// Set the environment variable OLDPWD to the current working directory
	set_env("OLDPWD", p_pwd, datash);

	// Set the environment variable PWD to the home directory
	set_env("PWD", home, datash);

	// Free allocated memory
	free(p_pwd);

	// Set the status to 0 (success)
	datash->status = 0;
}
