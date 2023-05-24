#include "shell.h"
/**
 *mystrlen - Determines the lenght of a string
 *@str: The string to count.
 *Return: Returns the lenght as int.
 */
int mystrlen(char *str)
{
	int i = 0;

	if (!str)
		return (0);
	while (*str++)
		i++;
	return (i);
}
/**
 *mystrcmp - Compares string.
 *@s1: Strng one
 *@s2: String two
 *Return: Returns an int
 */
int mystrcmp(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	if (*s1 == *s2)
		return (0);
	else
		return (*s1 < *s2 ? -1 : 1);
}
/**
 *start_search - Haystack check
 *@haystack: Expected string to search
 *@needle: Sub-string expected to find
 *Return: Pointer to nect string or NULL
 */
char *start_search(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return (NULL);
	return ((char *)haystack);
}
/**
 *mystrcat - Joins strings.
 *@dest: Destination string buffer
 *@src: Source string buffer
 *Return: pointer to destination buffer
 */
char *mystrcat(char *dest, char *src)
{
	char *ret = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (ret);
}
