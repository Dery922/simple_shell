#include "shell.h"
/**
 *mem_free - Frees the content of pointer and sets it to NULL
 *@ptr: Points to the array to be freed
 *Return: Returns 1 onn success
 */
int mem_free(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}
