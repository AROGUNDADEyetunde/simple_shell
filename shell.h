#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <limits.h>

#define BUFSIZE 1024
#define TOK_BUFSIZE 128
#define TOK_DELIM " \t\r\n\a"

extern char **environ;

/**
 * struct data - Data structure for shell information.
 * @av: Array of strings containing the program name and arguments.
 * @input: Input string from the shell.
 * @args: Array of strings containing parsed arguments.
 * @status: Status of the last command execution.
 * @counter: Counter for the number of shell commands executed.
 * @_environ: Array of strings containing environment variables.
 * @pid: Process ID.
 */
typedef struct data
{
char **av;
char *input;
char **args;
int status;
int counter;
char **_environ;
char *pid;
} data_shell;

/**
 * struct sep_list_s - Node for a list of separators (; | &).
 * @separator: Separator character.
 * @next: Pointer to the next separator node.
 */
typedef struct sep_list_s
{
char separator;
struct sep_list_s *next;
} sep_list;

/**
 * struct line_list_s - Node for a list of lines.
 * @line: Line string.
 * @next: Pointer to the next line node.
 */
typedef struct line_list_s
{
char *line;
struct line_list_s *next;
} line_list;

/**
 * struct r_var_list - Node for a list of variables and their replacements.
 * @len_var: Length of the variable.
 * @val: Value of the variable.
 * @len_val: Length of the value.
 * @next: Pointer to the next variable node.
 */
typedef struct r_var_list
{
int len_var;
char *val;
int len_val;
struct r_var_list *next;
} r_var;

/**
 * struct builtin_s - Node for built-in command information.
 * @name: Name of the built-in command.
 * @f: Pointer to the corresponding function.
 */
typedef struct builtin_s
{
char *name;
int (*f)(data_shell *datash);
} builtin_t;

/* Function prototypes for a.c, a2.c, ac, a3.c, c.c, s.c, r.c, g.c, */

#endif
