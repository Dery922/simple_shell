#include "shell.h"
/**
 * **str_split - Split full strings by delimeter
 *@str: String input
 *@d: Delimeter
 *Return: Pointer to array of strings
 */

char **str_split(char *str, char *d)
{
	int i, j, k, m, wcount = 0;
	char **spptr;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!d)
	{
		d = " ";
	}
	for (i = 0; str[i] != '\0'; i++)
		if (!mydelim(str[i], d) && (mydelim(str[i + 1], d) || !str[i + 1]))
			wcount++;

	if (wcount == 0)
		return (NULL);
	spptr = malloc((1 + wcount) * sizeof(char *));
	if (!spptr)
		return (NULL);
	for (i = 0, j = 0; j < wcount; j++)
	{
		while (mydelim(str[i], d))
			i++;
		k = 0;
		while (!mydelim(str[i + k], d) && str[i + k])
			k++;
		spptr[j] = malloc((k + 1) * sizeof(char));
		if (!spptr[j])
		{
			for (k = 0; k < j; k++)
				free(spptr[k]);
			free(spptr);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			spptr[j][m] = str[i++];
		spptr[j][m] = 0;
	}
	spptr[j] = NULL;
	return (spptr);
}
/**
 * **str2_split - splits a string.
 *@str: String input
 *@d: Delimeter
 *Return: a pointer to an array of strings.
 */
char **str2_split(char *str, char d)
{
	int i, j, k, m, wcount = 0;
	char **spptr;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (i = 0; str[i] != '\0'; i++)
		if ((str[i] != d && str[i + 1] == d) ||
				    (str[i] != d && !str[i + 1]) || str[i + 1] == d)
			wcount++;
	if (wcount == 0)
		return (NULL);
	spptr = malloc((1 + wcount) * sizeof(char *));
	if (!spptr)
		return (NULL);
	for (i = 0, j = 0; j < wcount; j++)
	{
		while (str[i] == d && str[i] != d)
			i++;
		k = 0;
		while (str[i + k] != d && str[i + k] && str[i + k] != d)
			k++;
		spptr[j] = malloc((k + 1) * sizeof(char));
		if (!spptr[j])
		{
			for (k = 0; k < j; k++)
				free(spptr[k]);
			free(spptr);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			spptr[j][m] = str[i++];
		spptr[j][m] = 0;
	}
	spptr[j] = NULL;
	return (spptr);
}
