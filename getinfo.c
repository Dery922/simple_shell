#include "shell.h"
/**
 *clearinfo - Initaialize info node in struct
 *@info: Struct node
 */
void clearinfo(info_t *info)
{
	info->arg = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
}
/**
 *setinfo - Initaialize info node in struct
 *@info: Struct node
 *@av: Argument vector
 */
void setinfo(info_t *info, char **av)
{
	int i = 0;

	info->fname = av[0];
	if (info->arg)
	{
		info->argv = str_split(info->arg, " \t");
		if (!info->argv)
		{
			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = mystrdup(info->arg);
				info->argv[1] = NULL;
			}
		}
		for (i = 0; info->argv && info->argv[i]; i++)
			;
		info->argc = i;
		change_alias(info);
		change_vars(info);
	}
}
/**
 *freeinfo - Frees info node elements
 *@info: Struct defined
 *@whole: Free all fields
 */
void freeinfo(info_t *info, int whole)
{
	d2_free(info->argv);
	info->argv = NULL;
	info->path = NULL;
	if (whole)
	{
		if (!info->cmd_buf)
			free(info->arg);
		if (info->env)
			freelist(&(info->env));
		if (info->history)
			freelist(&(info->history));
		if (info->alias)
			freelist(&(info->alias));
		d2_free(info->environ);
			info->environ = NULL;
		mem_free((void **)info->cmd_buf);
		if (info->readfd > 2)
			close(info->readfd);
		_putchar(BUF_FLUSH);
	}
}

