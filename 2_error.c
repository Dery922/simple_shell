#include "shell.h"
/**
 *myerratoi - String into int
 *@str: The string to convert
 * Return: Returns 0 on success
 */
int myerratoi(char *str)
{
	int i = 0;
	unsigned long int res = 0;

	if (*str == '+')
		str++;
	for (i = 0;  str[i] != '\0'; i++)
	{
		if (str[i] >= '0' && str[i] <= '9')
		{
			res *= 10;
			res += (str[i] - '0');
			if (res > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (res);
}
/**
 *outerror - Prints error msg
 *@info: Struct defined
 *@errstr: Error type string
 *Return: 0 on success
 */
void outerror(info_t *info, char *errstr)
{
	myeputs(info->fname);
	myeputs(": ");
	print_dec(info->line_count, STDERR_FILENO);
	myeputs(": ");
	myeputs(info->argv[0]);
	myeputs(": ");
	myeputs(errstr);
}
/**
 *print_dec - Prints decimal
 *@input: Input integer
 *@fd: The file descriptor
 *Return: Number of ouputed characters
 */
int print_dec(int input, int fd)
{
	int (*__putchar)(char) = _putchar;
	int i, count = 0;
	unsigned int _abs_, current;

	if (fd == STDERR_FILENO)
		__putchar = myeputchar;
	if (input < 0)
	{
		_abs_ = -input;
		__putchar('-');
		count++;
	}
	else
		_abs_ = input;
	current = _abs_;
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (_abs_ / i)
		{
			__putchar('0' + current / i);
			count++;
		}
		current %= i;
	}
	__putchar('0' + current);
	count++;

	return (count);
}
/**
 *convert_num - Convert function
 *@no: Number set
 *@base: Base set
 *@flag: Flags
 *Return: Returns a string
 */
char *convert_num(long int no, int base, int flag)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = no;

	if (!(flag & CONVERT_UNSIGNED) && no < 0)
	{
		n = -no;
		sign = '-';

	}
	array = flag & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do	{
		*--ptr = array[n % base];
		n /= base;
	} while (n != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}
/**
 *handle_comment - Handles comment
 *@buff: String pointer
 *Return: Always (0)
 */
void handle_comment(char *buff)
{
	int i;

	for (i = 0; buff[i] != '\0'; i++)
		if (buff[i] == '#' && (!i || buff[i - 1] == ' '))
		{
			buff[i] = '\0';
			break;
		}
}

