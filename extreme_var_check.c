#include "shell.h"

/**
 * check_env - Checks input correspondence to an environment variable.
 * @h: Head of the linked list storing environment variable information.
 * @in: Input string to be checked.
 * @data: Data structure containing shell information.
 */
void check_env(r_var **h, char *in, data_shell *data)
{
    int row, chr, j, lval;
    char **_envr;

    _envr = data->_environ;

    // Iterating through environment variables
    for (row = 0; _envr[row]; row++)
    {
        // Comparing characters in the input with the current environment variable
        for (j = 1, chr = 0; _envr[row][chr]; chr++)
        {
            if (_envr[row][chr] == '=')
            {
                // If '=' is found, add the environment variable to the linked list
                lval = _strlen(_envr[row] + chr + 1);
                add_rvar_node(h, j, _envr[row] + chr + 1, lval);
                return;
            }

            if (in[j] == _envr[row][chr])
                j++;
            else
                break;
        }
    }

    // If no match is found, add an empty node to the linked list
    for (j = 0; in[j]; j++)
    {
        if (in[j] == ' ' || in[j] == '\t' || in[j] == ';' || in[j] == '\n')
            break;
    }

    add_rvar_node(h, j, NULL, 0);
}

/**
 * check_vars - Checks for variables in the input string and adds them to a linked list.
 * @h: Head of the linked list storing variable information.
 * @in: Input string to be checked.
 * @st: String representation of the shell's status.
 * @data: Data structure containing shell information.
 * Return: Number of characters processed in the input string.
 */
int check_vars(r_var **h, char *in, char *st, data_shell *data)
{
    int i, lst, lpd;

    lst = _strlen(st);
    lpd = _strlen(data->pid);

    // Iterating through characters in the input string
    for (i = 0; in[i]; i++)
    {
        if (in[i] == '$')
        {
            // Checking for special variables ('$?', '$$', '\n', ' ', '\t', ';')
            if (in[i + 1] == '?')
                add_rvar_node(h, 2, st, lst), i++;
            else if (in[i + 1] == '$')
                add_rvar_node(h, 2, data->pid, lpd), i++;
            else if (in[i + 1] == '\n')
                add_rvar_node(h, 0, NULL, 0);
            else if (in[i + 1] == '\0')
                add_rvar_node(h, 0, NULL, 0);
            else if (in[i + 1] == ' ')
                add_rvar_node(h, 0, NULL, 0);
            else if (in[i + 1] == '\t')
                add_rvar_node(h, 0, NULL, 0);
            else if (in[i + 1] == ';')
                add_rvar_node(h, 0, NULL, 0);
            else
                // If not a special variable, check if it corresponds to an environment variable
                check_env(h, in + i, data);
        }
    }

    return (i);
}

/**
 * replaced_input - Replaces variables in the input string with their values.
 * @head: Head of the linked list storing variable information.
 * @input: Input string.
 * @new_input: Buffer to store the replaced input string.
 * @nlen: Length of the new input string.
 * Return: Pointer to the replaced input string.
 */
char *replaced_input(r_var **head, char *input, char *new_input, int nlen)
{
    r_var *indx;
    int i, j, k;

    indx = *head;

    // Iterating through characters in the new input string
    for (j = i = 0; i < nlen; i++)
    {
        if (input[j] == '$')
        {
            if (!(indx->len_var) && !(indx->len_val))
            {
                new_input[i] = input[j];
                j++;
            }
            else if (indx->len_var && !(indx->len_val))
            {
                // Skipping the variable in the input string
                for (k = 0; k < indx->len_var; k++)
                    j++;
                i--;
            }
            else
            {
                // Copying the value of the variable to the new input string
                for (k = 0; k < indx->len_val; k++)
                {
                    new_input[i] = indx->val[k];
                    i++;
                }
                j += (indx->len_var);
                i--;
            }
            indx = indx->next;
        }
        else
        {
            // Copying non-variable characters to the new input string
            new_input[i] = input[j];
            j++;
        }
    }

    return (new_input);
}

/**
 * rep_var - Replaces variables in the input string with their values.
 * @input: Input string.
 * @datash: Data structure containing shell information.
 * Return: Pointer to the replaced input string.
 */
char *rep_var(char *input, data_shell *datash)
{
    r_var *head, *indx;
    char *status, *new_input;
    int olen, nlen;

    // Converting the shell's status to a string
    status = aux_itoa(datash->status);

    head = NULL;

    // Checking for variables and adding them to the linked list
    olen = check_vars(&head, input, status, datash);

    // If no variables are found, return the original input string
    if (head == NULL)
    {
        free(status);
        return (input);
    }

    indx = head;
    nlen = 0;

    // Calculating the length of the new input string
    while (indx != NULL)
    {
        nlen += (indx->len_val - indx->len_var);
        indx = indx->next;
    }

    nlen += olen;

    // Allocating memory for the new input string
    new_input = malloc(sizeof(char) * (nlen + 1));
    new_input[nlen] = '\0';

    // Replacing variables in the input string
    new_input = replaced_input(&head, input, new_input, nlen);

    free(input);
    free(status);

    // Freeing the linked list of variables
    free_rvar_list(&head);

    return (new_input);
}
#include "shell.h"

/**
 * check_env - Checks if the input corresponds to an environment variable.
 * @h: Head of the linked list storing environment variable information.
 * @in: Input string to be checked.
 * @data: Data structure containing shell information.
 */
void check_env(r_var **h, char *in, data_shell *data)
{
    int row, chr, j, lval;
    char **_envr;

    _envr = data->_environ;

    // Iterating through environment variables
    for (row = 0; _envr[row]; row++)
    {
        // Comparing characters in the input with the current environment variable
        for (j = 1, chr = 0; _envr[row][chr]; chr++)
        {
            if (_envr[row][chr] == '=')
            {
                // If '=' is found, add the environment variable to the linked list
                lval = _strlen(_envr[row] + chr + 1);
                add_rvar_node(h, j, _envr[row] + chr + 1, lval);
                return;
            }

            if (in[j] == _envr[row][chr])
                j++;
            else
                break;
        }
    }

    // If no match is found, add an empty node to the linked list
    for (j = 0; in[j]; j++)
    {
        if (in[j] == ' ' || in[j] == '\t' || in[j] == ';' || in[j] == '\n')
            break;
    }

    add_rvar_node(h, j, NULL, 0);
}

/**
 * check_vars - Checks for variables in the input string and adds them to a linked list.
 * @h: Head of the linked list storing variable information.
 * @in: Input string to be checked.
 * @st: String representation of the shell's status.
 * @data: Data structure containing shell information.
 * Return: Number of characters processed in the input string.
 */
int check_vars(r_var **h, char *in, char *st, data_shell *data)
{
    int i, lst, lpd;

    lst = _strlen(st);
    lpd = _strlen(data->pid);

    // Iterating through characters in the input string
    for (i = 0; in[i]; i++)
    {
        if (in[i] == '$')
        {
            // Checking for special variables ('$?', '$$', '\n', ' ', '\t', ';')
            if (in[i + 1] == '?')
                add_rvar_node(h, 2, st, lst), i++;
            else if (in[i + 1] == '$')
                add_rvar_node(h, 2, data->pid, lpd), i++;
            else if (in[i + 1] == '\n')
                add_rvar_node(h, 0, NULL, 0);
            else if (in[i + 1] == '\0')
                add_rvar_node(h, 0, NULL, 0);
            else if (in[i + 1] == ' ')
                add_rvar_node(h, 0, NULL, 0);
            else if (in[i + 1] == '\t')
                add_rvar_node(h, 0, NULL, 0);
            else if (in[i + 1] == ';')
                add_rvar_node(h, 0, NULL, 0);
            else
                // If not a special variable, check if it corresponds to an environment variable
                check_env(h, in + i, data);
        }
    }

    return (i);
}

/**
 * replaced_input - Replaces variables in the input string with their values.
 * @head: Head of the linked list storing variable information.
 * @input: Input string.
 * @new_input: Buffer to store the replaced input string.
 * @nlen: Length of the new input string.
 * Return: Pointer to the replaced input string.
 */
char *replaced_input(r_var **head, char *input, char *new_input, int nlen)
{
    r_var *indx;
    int i, j, k;

    indx = *head;

    // Iterating through characters in the new input string
    for (j = i = 0; i < nlen; i++)
    {
        if (input[j] == '$')
        {
            if (!(indx->len_var) && !(indx->len_val))
            {
                new_input[i] = input[j];
                j++;
            }
            else if (indx->len_var && !(indx->len_val))
            {
                // Skipping the variable in the input string
                for (k = 0; k < indx->len_var; k++)
                    j++;
                i--;
            }
            else
            {
                // Copying the value of the variable to the new input string
                for (k = 0; k < indx->len_val; k++)
                {
                    new_input[i] = indx->val[k];
                    i++;
                }
                j += (indx->len_var);
                i--;
            }
            indx = indx->next;
        }
        else
        {
            // Copying non-variable characters to the new input string
            new_input[i] = input[j];
            j++;
        }
    }

    return (new_input);
}

/**
 * rep_var - Replaces variables in the input string with their values.
 * @input: Input string.
 * @datash: Data structure containing shell information.
 * Return: Pointer to the replaced input string.
 */
char *rep_var(char *input, data_shell *datash)
{
    r_var *head, *indx;
    char *status, *new_input;
    int olen, nlen;

    // Converting the shell's status to a string
    status = aux_itoa(datash->status);

    head = NULL;

    // Checking for variables and adding them to the linked list
    olen = check_vars(&head, input, status, datash);

    // If no variables are found, return the original input string
    if (head == NULL)
    {
        free(status);
        return (input);
    }

    indx = head;
    nlen = 0;

    // Calculating the length of the new input string
    while (indx != NULL)
    {
        nlen += (indx->len_val - indx->len_var);
        indx = indx->next;
    }

    nlen += olen;

    // Allocating memory for the new input string
    new_input = malloc(sizeof(char) * (nlen + 1));
    new_input[nlen] = '\0';

    // Replacing variables in the input string
    new_input = replaced_input(&head, input, new_input, nlen);

    free(input);
    free(status);

    // Freeing the linked list of variables
    free_rvar_list(&head);

    return (new_input);
}
