#include "shell.h"
/**
 *mystrcpy - Copies string.
 *@dest: Destination.
 *@src: Source.
 * Return: Returns a pointer to destination.
 */
char *mystrcpy(char *dest, char *src)
{
	int i = 0;

	if (dest == src || src == 0)
		return (dest);
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = 0;
	return (dest);
}
/**
 *mystrdup - Duplicates string
 *@str: String to be doubled.
 *Return: Returns pointer to the newly created string.
 */
char *mystrdup(const char *str)
{
	int count = 0;
	char *pt;

	if (str == NULL)
		return (NULL);
	while (*str++)
		count++;
	pt = malloc(sizeof(char) * (count + 1));
	if (!pt)
		return (NULL);
	for (count++; count--;)
		pt[count] = *--str;
	return (pt);
}

/**
 *myputs - Prints string
 *@str: String expected
 * Return: N/A
 */
void myputs(char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		_putchar(str[i]);
		i++;
	}
}

/**
 *_putchar - writes the character c to stdout
 *@c: The character to print
 *Return: On success 1.
 */
int _putchar(char c)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(1, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}
