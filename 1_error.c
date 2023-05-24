#include "shell.h"
/**
 *myeputs - Prints error strings
 *@str: Print this string
 *Return: Void
 */
void myeputs(char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		myeputchar(str[i]);
		i++;
	}
}
/**
 *myeputchar - Prints error char
 *@chr: Print this character
 *Return: Either 1 or -1
 */
int myeputchar(char chr)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (chr == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(2, buf, i);
		i = 0;
	}
	if (chr != BUF_FLUSH)
		buf[i++] = chr;
	return (1);
}
/**
 *myputfd - Write error char to fd
 *@chr: The error char
 *@fd: The file descriptor
 *Return: On success == 1.
 */
int myputfd(char chr, int fd)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (chr == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(fd, buf, i);
		i = 0;
	}
	if (chr != BUF_FLUSH)
		buf[i++] = chr;
	return (1);
}

/**
 *myputsfd - Print string error input
 *@str: The error string
 *@fd: The file descriptor
 * Return: Int of number of chars
 */
int myputsfd(char *str, int fd)
{
	int i = 0;

	if (!str)
		return (0);
	while (*str)
	{
		i += myputfd(*str++, fd);
	}
	return (i);
}

