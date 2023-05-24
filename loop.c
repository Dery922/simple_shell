#include "shell.h"
/**
 *loop - Main entry into loop
 *@info: The struct defined
 *@av: Main() function argument vector.
 *Return: Returns 0 on success and 1 on error.
 */
int loop(info_t *info, char **av)
{
	ssize_t i = 0;
	int builtin_ret = 0;

	while (i != -1 && builtin_ret != -2)
	{
		clearinfo(info);
		if (interactive(info))
			myputs("$ ");
		myeputchar(BUF_FLUSH);
		i = get_input(info);
		if (i != -1)
		{
			setinfo(info, av);
			builtin_ret = find_builtcmd(info);
			if (builtin_ret == -1)
				findcmd(info);
		}
		else if (interactive(info))
			_putchar('\n');
		freeinfo(info, 0);
	}
	write_history(info);
	freeinfo(info, 1);
	if (!interactive(info) && info->status)
		exit(info->status);
	if (builtin_ret == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->err_num);
	}
	return (builtin_ret);
}
/**
 *find_builtcmd - Finds  builtin command
 *@info: The struct defined.
 *Return: -1 if builtin not found
 */
int find_builtcmd(info_t *info)
{
	int i, built_in_ret = -1;
	builtin_table builtintbl[] = {
		{"exit", myexit},
		{"env", myenv},
		{"help", myhelp},
		{"history", myhistory},
		{"setenv", seten},
		{"unsetenv", unseten},
		{"cd", mycd},
		{"alias", myalias},
		{NULL, NULL}
	};

	for (i = 0; builtintbl[i].type; i++)
		if (mystrcmp(info->argv[0], builtintbl[i].type) == 0)
		{
			info->line_count++;
			built_in_ret = builtintbl[i].func(info);
			break;
		}
	return (built_in_ret);
}
/**
 *findcmd - Finds command in PATH env
 *@info: The struct defined.
 *Return: Returns void.
 */
void findcmd(info_t *info)
{
	char *path = NULL;
	int i, j;

	info->path = info->argv[0];
	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}
	for (i = 0, j = 0; info->arg[i]; i++)
		if (!mydelim(info->arg[i], " \t\n"))
			j++;
	if (!j)
		return;

	path = findpth(info, my_getenv(info, "PATH="), info->argv[0]);
	if (path)
	{
		info->path = path;
		forkcmd(info);
	}
	else
	{
		if ((interactive(info) || my_getenv(info, "PATH=")
					|| info->argv[0][0] == '/') && is_exec(info, info->argv[0]))
			forkcmd(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			outerror(info, "not found\n");
		}
	}
}
/**
 *forkcmd - Forms child program
 *@info: The struct defined
 *Return: Returns void
 */
void forkcmd(info_t *info)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(info->path, info->argv, get_environ(info)) == -1)
		{
			freeinfo(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				outerror(info, "Permission denied\n");
		}
	}
}
