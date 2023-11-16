#include "shell.h"

/**
 * bfree - frees a pointer and makes the address NULL.
 * @ptr: address of the pointer to free.
 *
 * Return: Returns 1 if pointer is freed, Returns 0 if otherwise.
 */
int bfree(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}
