#include "shell.h"
/**
 *mymemset - Populate memory with specific byte
 *@sptr: Pointer to memory area
 *@byt: The byte to fill the above with
 *@num: The amount of bytes to be filled
 *Return: Return a pointer to the allocated memory area
 */
char *mymemset(char *sptr, char byt, unsigned int num)
{
	unsigned int i;

	for (i = 0; i < num; i++)
		sptr[i] = byt;
	return (sptr);
}
/**
 *d2_free - Frees such strings
 *@p: string containing strings
 */
void d2_free(char **p)
{
	char **b = p;

	if (!p)
		return;
	while (*p)
		free(*p++);
	free(b);
}
/**
 *myrealloc - Memory reallocation
 *@ptr: Points previous mem block
 *@old: Old byte size
 *@new: New byte size
 *Return: Points to old mem block
 */
void *myrealloc(void *ptr, unsigned int old, unsigned int new)
{
	char *lfp;

	if (!ptr)
		return (malloc(new));
	if (!new)
		return (free(ptr), NULL);
	if (new == old)
		return (ptr);
	lfp = malloc(new);
	if (!lfp)
		return (NULL);
	old = old < new ? old : new;
	while (old--)
		lfp[old] = ((char *)ptr)[old];
	free(ptr);
	return (lfp);
}
