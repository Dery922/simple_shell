#include "shell.h"
/**
 *chain - check if buffer content is a chain delimeter
 *@info: The struct defined
 *@buffer: The character buffer
 *@cc: Address of position of buffer
 * Return: 1 == chain delimeter, 0 == Otherwise
 */
int chain(info_t *info, char *buffer, size_t *cc)
{
	size_t i = *cc;

	if (buffer[i] == '|' && buffer[i + 1] == '|')
	{
		buffer[i] = 0;
		i++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buffer[i] == '&' && buffer[i + 1] == '&')
	{
		buffer[i] = 0;
		i++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buffer[i] == ';')
	{
		buffer[i] = 0; /*Put : at NULL*/
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*cc = i;
	return (1);
}
/**
 *checkfor_chain - Determine if or not chaining based on status
 *@info: The struct defined
 *@buffer: The character buffer
 *@cc: address of current position in buf
 *@b: Beginning position of buffer
 *@c: length of buffer
 * Return: Void
 */
void checkfor_chain(info_t *info, char *buffer, size_t *cc, size_t b, size_t c)
{
	size_t i = *cc;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buffer[b] = 0;
			i = c;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			buffer[b] = 0;
			i = c;
		}
	}

	*cc = i;
}
/**
 *change_alias - Replace aliasis
 *@info: The struct defined
 *Return: 1 == replaced 0 == otherwise
 */
int change_alias(info_t *info)
{
	int i;
	list_t *node;
	char *cc;

	for (i = 0; i < 10; i++)
	{
		node = node_check(info->alias, info->argv[0], '=');
		if (!node)
			return (0);
		free(info->argv[0]);
		cc = mystrchr(node->str, '=');
		if (!cc)
			return (0);
		cc = mystrdup(cc + 1);
		if (!cc)
			return (0);
		info->argv[0] = cc;
	}
	return (1);
}
/**
 *change_vars - replaces vars in tokenized string
 *@info: The struct defined
 *Return: 1 == replaced == otherwise
 */
int change_vars(info_t *info)
{
	int i = 0;
	list_t *node;

	for (i = 0; info->argv[i]; i++)
	{
		if (info->argv[i][0] != '$' || !info->argv[i][1])
			continue;

		if (!mystrcmp(info->argv[i], "$?"))
		{
			change_string(&(info->argv[i]),
					mystrdup(convert_num(info->status, 10, 0)));
			continue;
		}
		if (!mystrcmp(info->argv[i], "$$"))
		{
			change_string(&(info->argv[i]),
					mystrdup(convert_num(getpid(), 10, 0)));
			continue;
		}
		node = node_check(info->env, &info->argv[i][1], '=');
		if (node)
		{
			change_string(&(info->argv[i]),
					mystrdup(mystrchr(node->str, '=') + 1));
			continue;
		}
		change_string(&info->argv[i], mystrdup(""));

	}
	return (0);
}
/**
 *change_string - replaces string
 *@old: Old string's Address
 *@new: New string's Address
 *Return: 1 == replaced 0 == otherwise
 */
int change_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
