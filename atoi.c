#include "shell.h"
/**
 *interactive - interactive mode
 *@info: Info struct
 *Return: one or zero
 */
int interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}
/**
 *mydelim - Is character a delimeter
 *@chr: character variable
 *@delim: The delimeter to check
 *Return: Either true or false
 */
int mydelim(char chr, char *delim)
{
	while (*delim)
		if (*delim++ == chr)
			return (1);
	return (0);
}
/**
 *myalpha - Is is an alphabet
 *@chr: Character variable
 *Return: Either 1 0r 2
 */
int myalpha(int chr)
{
	if ((chr >= 'a' && chr <= 'z') || (chr >= 'A' && chr <= 'Z'))
		return (1);
	else
		return (0);
}
/**
 *mystratoi - Change string to int
 *@str: The string expected
 *Return: Check string
 */
int mystratoi(char *str)
{
	int i, sn = 1, fg = 0, out;
	unsigned int res = 0;

	for (i = 0; str[i] != '\0' && fg != 2; i++)
	{
		if (str[i] == '-')
			sn *= -1;

		if (str[i] >= '0' && str[i] <= '9')
		{
			fg = 1;
			res *= 10;
			res += (str[i] - '0');
		}
		else if (fg == 1)
			fg = 2;
	}
	if (sn == -1)
		out = -res;
	else
		out = res;

	return (out);
}
