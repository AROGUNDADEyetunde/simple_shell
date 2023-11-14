#include "shell.h"

/**
 * aux_help - Displays useful help information for the 'help' command.
 * Return: None.
 */
void aux_help(void)
{
    char *help = "help: help [-dms] [pattern ...]\n";

    // Write help information to standard output
    write(STDOUT_FILENO, help, _strlen(help));
    
    help = "\tDisplay information about builtin commands.\n ";
    write(STDOUT_FILENO, help, _strlen(help));
    
    help = "Displays brief summaries of builtin commands.\n";
    write(STDOUT_FILENO, help, _strlen(help));
}

/**
 * aux_help_alias - Displays help information for the 'alias' command.
 * Return: None.
 */
void aux_help_alias(void)
{
    char *help = "alias: alias [-p] [name[=value]...]\n";

    // Write help information to standard output
    write(STDOUT_FILENO, help, _strlen(help));

    help = "\tDefine or display aliases.\n ";
    write(STDOUT_FILENO, help, _strlen(help));
}

/**
 * aux_help_cd - Displays help information for the 'cd' command.
 * Return: None.
 */
void aux_help_cd(void)
{
    char *help = "cd: cd [-L|[-P [-e]] [-@]] [dir]\n";

    // Write help information to standard output
    write(STDOUT_FILENO, help, _strlen(help));

    help = "\tChange the shell working directory.\n ";
    write(STDOUT_FILENO, help, _strlen(help));
}
