#include "shell.h"

/**
 * is_cdir - Checks if the current character in the path is a colon or not.
 * @path: The path string.
 * @i: Pointer to the current index in the path.
 * Return: 1 if the current character is a colon, 0 otherwise.
 */
int is_cdir(char *path, int *i)
{
    if (path[*i] == ':')
        return (1);

    while (path[*i] != ':' && path[*i])
    {
        *i += 1;
    }

    if (path[*i])
        *i += 1;

    return (0);
}

/**
 * _which - Locates the executable path of a given command.
 * @cmd: The command to locate.
 * @_environ: The environment variable array.
 * Return: The full path to the executable command, or NULL if not found.
 */
char *_which(char *cmd, char **_environ)
{
    char *path, *ptr_path, *token_path, *dir;
    int len_dir, len_cmd, i;
    struct stat st;

    path = _getenv("PATH", _environ);

    if (path)
    {
        ptr_path = _strdup(path);
        len_cmd = _strlen(cmd);
        token_path = _strtok(ptr_path, ":");
        i = 0;

        while (token_path != NULL)
        {
            if (is_cdir(path, &i))
                if (stat(cmd, &st) == 0)
                    return (cmd);

            len_dir = _strlen(token_path);
            dir = malloc(len_dir + len_cmd + 2);
            _strcpy(dir, token_path);
            _strcat(dir, "/");
            _strcat(dir, cmd);
            _strcat(dir, "\0");

            if (stat(dir, &st) == 0)
            {
                free(ptr_path);
                return (dir);
            }

            free(dir);
            token_path = _strtok(NULL, ":");
        }

        free(ptr_path);

        if (stat(cmd, &st) == 0)
            return (cmd);

        return (NULL);
    }

    if (cmd[0] == '/')
        if (stat(cmd, &st) == 0)
            return (cmd);

    return (NULL);
}

/**
 * is_executable - Checks if the input command is executable.
 * @datash: Data structure containing shell information.
 * Return: The index where the command becomes non-executable, or -1 if not found.
 */
int is_executable(data_shell *datash)
{
    struct stat st;
    int i;
    char *input;

    input = datash->args[0];

    for (i = 0; input[i]; i++)
    {
        if (input[i] == '.')
        {
            if (input[i + 1] == '.')
                return (0);
            if (input[i + 1] == '/')
                continue;
            else
                break;
        }
        else if (input[i] == '/' && i != 0)
        {
            if (input[i + 1] == '.')
                continue;
            i++;
            break;
        }
        else
            break;
    }

    if (i == 0)
        return (0);

    if (stat(input + i, &st) == 0)
    {
        return (i);
    }

    get_error(datash, 127);
    return (-1);
}

/**
 * check_error_cmd - Checks for errors related to the command's executability.
 * @dir: The directory path of the command.
 * @datash: Data structure containing shell information.
 * Return: 1 if there is an error, 0 otherwise.
 */
int check_error_cmd(char *dir, data_shell *datash)
{
    if (dir == NULL)
    {
        get_error(datash, 127);
        return (1);
    }

    if (_strcmp(datash->args[0], dir) != 0)
    {
        if (access(dir, X_OK) == -1)
        {
            get_error(datash, 126);
            free(dir);
            return (1);
        }
        free(dir);
    }
    else
    {
        if (access(datash->args[0], X_OK) == -1)
        {
            get_error(datash, 126);
            return (1);
        }
    }

    return (0);
}

/**
 * cmd_exec - Executes the given command.
 * @datash: Data structure containing shell information.
 * Return: 1 if successful, 0 otherwise.
 */
int cmd_exec(data_shell *datash)
{
    pid_t pd;
    pid_t wpd;
    int state;
    int exec;
    char *dir;
    (void)wpd;

    exec = is_executable(datash);

    if (exec == -1)
        return (1);

    if (exec == 0)
    {
        dir = _which(datash->args[0], datash->_environ);

        if (check_error_cmd(dir, datash) == 1)
            return (1);
    }

    pd = fork();

    if (pd == 0)
    {
        if (exec == 0)
            dir = _which(datash->args[0], datash->_environ);
        else
            dir = datash->args[0];

        execve(dir + exec, datash->args, datash->_environ);
    }
    else if (pd < 0)
    {
        perror(datash->av[0]);
        return (1);
    }
    else
    {
        do
        {
            wpd = waitpid(pd, &state, WUNTRACED);
        } while (!WIFEXITED(state) && !WIFSIGNALED(state));
    }

    datash->status = state / 256;

    return (1);
}
