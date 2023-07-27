#include "shell.h"

/**
 * bfree - Frees a pointer and sets the address to NULL.
 * @ptr: Address of the pointer to free
 *
 * This function frees the memory block pointed to by @ptr and
 * sets the pointer to NULL, preventing it from becoming a dangling pointer.
 *
 * Return: 1 if memory is successfully freed, otherwise 0.
 */
int bfree(void **ptr)
{
    if (ptr != NULL && *ptr != NULL)
    {
        free(*ptr);
        *ptr = NULL;
        return (1);
    }
    return (0);
}
