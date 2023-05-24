#include "shell.h"
/**
 *is_exec - Checks if file is executable
 *@info: The struct defined
 *@path: path to the file
 *Return: 1 == true 0 ==  Otherwise
 */
int is_exec(info_t *info, char *path)
{
	struct stat st;

	(void)info;
	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}
/**
 *dbl_char - duplicates characters
 *@pathstr: Path in string
 *@start: Starts at index
 *@stop: Stops at index
 * Return: pointer
 */
char *dbl_char(char *pathstr, int start, int stop)
{
	static char buff[1024];
	int i = 0;
	int j = 0;

	for (j = 0, i = start; i < stop; i++)
		if (pathstr[i] != ':')
			buff[j++] = pathstr[i];
	buff[j] = 0;
	return (buff);
}
/**
 *findpth - Match path to string
 *@info: The struct defined
 *@paths: Path in string
 *@cmd: Expected command
 *Return: Returns path of cmd if found or NULL.
 */
char *findpth(info_t *info, char *paths, char *cmd)
{
	int i = 0;
	int current = 0;
	char *path;

	if (!paths)
		return (NULL);
	if ((mystrlen(cmd) > 2) && start_search(cmd, "./"))
	{
		if (is_exec(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!paths[i] || paths[i] == ':')
		{
			path = dbl_char(paths, current, i);
			if (!*path)
				mystrcat(path, cmd);
			else
			{
				mystrcat(path, "/");
				mystrcat(path, cmd);
			}
			if (is_exec(info, path))
				return (path);
			if (!paths[i])
				break;
			current = i;
		}
		i++;
	}
	return (NULL);
}
