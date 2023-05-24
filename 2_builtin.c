#include "shell.h"
/**
 *myhistory - Hnadles histrory
 *@info: Struct defined
 *Return: Always 0
 */
int myhistory(info_t *info)
{
	out_list(info->history);
	return (0);
}

/**
 *unsetalias - Handles alias
 *@info: Struct defined
 *@str: Alias
 * Return: Either one or two
 */
int unsetalias(info_t *info, char *str)
{
	char *buff, chr;
	int ret;

	buff = mystrchr(str, '=');
	if (!buff)
		return (1);
	chr = *buff;
	*buff = 0;
	ret = del_node(&(info->alias),
		find_index(info->alias, node_check(info->alias, str, -1)));
	*buff = chr;
	return (ret);
}
/**
 *setalias - Handles alias
 *@info: parameter struct
 *@str: Alias
 *Return: Either one or two
 */
int setalias(info_t *info, char *str)
{
	char *buff;

	buff = mystrchr(str, '=');
	if (!buff)
		return (1);
	if (!*++buff)
		return (unsetalias(info, str));

	unsetalias(info, str);
	return (end_node(&(info->alias), str, 0) == NULL);
}
/**
 *outalias - Prints alias
 *@node: Node
 * Return: Either one or zero
 */
int outalias(list_t *node)
{
	char *buff = NULL, *duff = NULL;

	if (node)
	{
		buff = mystrchr(node->str, '=');
		for (duff = node->str; duff <= buff; duff++)
		_putchar(*duff);
		_putchar('\'');
		myputs(buff + 1);
		myputs("'\n");
		return (0);
	}
	return (1);
}
/**
 *myalias - Handles alkias
 *@info: Structure defined
 *Return: Always (0)
 */
int myalias(info_t *info)
{
	int i = 0;
	char *buff = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			outalias(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; info->argv[i]; i++)
	{
		buff = mystrchr(info->argv[i], '=');
		if (buff)
			setalias(info, info->argv[i]);
		else
			outalias(node_check(info->alias, info->argv[i], '='));
	}

	return (0);
}
