#include "shell.h"
/**
 **mystrncpy - Function pointer copies string
 *@dest: Destination
 *@src: Source
 *@num: Number of chars to copy
 *Return: Returns astring
 */
char *mystrncpy(char *dest, char *src, int num)
{
	int i;
	int j;
	char *st = dest;

	i = 0;
	while (src[i] != '\0' && i < num - 1)
	{
		dest[i] = src[i];
		i++;
	}
	if (i < num)
	{
		j = i;
		while (j < num)
		{
			dest[j] = '\0';
			j++;
		}
	}
	return (st);
}
/**
 **mystrncat - Joins two strings
 *@dest: Destination string
 *@src: Source string
 *@num: Number of chars
 *Return: Returns a string
 */
char *mystrncat(char *dest, char *src, int num)
{
	int i, j;
	char *st = dest;

	i = 0;
	j = 0;
	while (dest[i] != '\0')
		i++;
	while (src[j] != '\0' && j < num)
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	if (j < num)
		dest[i] = '\0';
	return (st);
}
/**
 **mystrchr - Finds character in str
 *@str: The containing string
 *@chr: The sought after char
 *Return: Pointer to str
 */
char *mystrchr(char *str, char chr)
{
	do {
		if (*str == chr)
			return (str);
	} while (*str++ != '\0');

	return (NULL);
}
