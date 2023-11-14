#include "shell.h"

/**
 * _memcpy - Copies the 'size' bytes from 'ptr' to 'newptr'.
 * @newptr: Destination memory address.
 * @ptr: Source memory address.
 * @size: Number of bytes to copy.
 *
 * Return: None.
 */
void _memcpy(void *newptr, const void *ptr, unsigned int size)
{
    char *char_ptr = (char *)ptr;
    char *char_newptr = (char *)newptr;
    unsigned int i;

    // Copy each byte from 'ptr' to 'newptr'
    for (i = 0; i < size; i++)
        char_newptr[i] = char_ptr[i];
}

/**
 * _realloc - Resizes the memory block pointed to by 'ptr'.
 * @ptr: Pointer to the memory block.
 * @old_size: Original size of the memory block.
 * @new_size: New size of the memory block.
 *
 * Return: Pointer to the resized memory block.
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
    void *newptr;

    // If 'ptr' is NULL, allocate new memory of 'new_size'
    if (ptr == NULL)
        return (malloc(new_size));

    // If 'new_size' is 0, free 'ptr' and return NULL
    if (new_size == 0)
    {
        free(ptr);
        return (NULL);
    }

    // If 'new_size' is equal to 'old_size', no need to reallocate
    if (new_size == old_size)
        return (ptr);

    // Allocate new memory of 'new_size'
    newptr = malloc(new_size);
    if (newptr == NULL)
        return (NULL);

    // Copy data from 'ptr' to 'newptr' based on the smaller size
    if (new_size < old_size)
        _memcpy(newptr, ptr, new_size);
    else
        _memcpy(newptr, ptr, old_size);

    // Free the old memory block
    free(ptr);

    return (newptr);
}

/**
 * _reallocdp - Resizes the dynamic array of pointers 'ptr'.
 * @ptr: Pointer to the dynamic array of pointers.
 * @old_size: Original size of the dynamic array.
 * @new_size: New size of the dynamic array.
 *
 * Return: Pointer to the resized dynamic array of pointers.
 */
char **_reallocdp(char **ptr, unsigned int old_size, unsigned int new_size)
{
    char **newptr;
    unsigned int i;

    // If 'ptr' is NULL, allocate new memory for an array of pointers of 'new_size'
    if (ptr == NULL)
        return (malloc(sizeof(char *) * new_size));

    // If 'new_size' is equal to 'old_size', no need to reallocate
    if (new_size == old_size)
        return (ptr);

    // Allocate new memory for an array of pointers of 'new_size'
    newptr = malloc(sizeof(char *) * new_size);
    if (newptr == NULL)
        return (NULL);

    // Copy pointers from 'ptr' to 'newptr' based on the smaller size
    for (i = 0; i < old_size; i++)
        newptr[i] = ptr[i];

    // Free the old array of pointers
    free(ptr);

    return (newptr);
}

