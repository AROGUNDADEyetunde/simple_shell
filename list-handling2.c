#include "shell.h"

/**
 * add_rvar_node - Adds new nodes to the end of the linked lists of environment variables.
 * @head: Pointer to the head of the linked list.
 * @lvar: Length of the variable name.
 * @val: Value of the variable.
 * @lval: Length of the variable value.
 * Return: Pointer to the head of the updated list.
 */
r_var *add_rvar_node(r_var **head, int lvar, char *val, int lval)
{
    r_var *new, *temp;

    // Allocate memory for the new node
    new = malloc(sizeof(r_var));
    if (new == NULL)
        return (NULL);

    // Assign values to the new node
    new->len_var = lvar;
    new->val = val;
    new->len_val = lval;

    new->next = NULL;
    temp = *head;

    // Update the linked list
    if (temp == NULL)
    {
        *head = new;
    }
    else
    {
        while (temp->next != NULL)
            temp = temp->next;
        temp->next = new;
    }

    return (*head);
}

/**
 * free_rvar_list - Frees memory allocated for the linked list of environment variables.
 * @head: Pointer to the head of the linked list.
 */
void free_rvar_list(r_var **head)
{
    r_var *temp;
    r_var *curr;

    if (head != NULL)
    {
        curr = *head;
        // Traverse the list and free each node
        while ((temp = curr) != NULL)
        {
            curr = curr->next;
            free(temp);
        }
        *head = NULL;
    }
}

