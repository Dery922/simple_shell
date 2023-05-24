#include "shell.h"
/**
 *get_environ - Returns environ string
 *@info: Struct defined.
 *Return: Always 0
 */
char **get_environ(info_t *info)
{
	if (!info->environ || info->env_changed)
	{
		info->environ = list_str(info->env);
		info->env_changed = 0;
	}
	return (info->environ);
}
/**
 *myunsetenv - Function deletes environment vars
 *@info: Struct defined
 *@var: Variable string
 *Return: 1 == Deleted otherwise 0
 */
int myunsetenv(info_t *info, char *var)
{
	list_t *node = info->env;
	size_t i = 0;
	char *ppt;

	if (!node || !var)
		return (0);
	while (node)
	{
		ppt = start_search(node->str, var);
		if (ppt && *ppt == '=')
		{
			info->env_changed = del_node(&(info->env), i);
			i = 0;
			node = info->env;
			continue;
		}
		node = node->next;
		i++;
	}
	return (info->env_changed);
}
/**
 *mysetenv - Handles new env to set
 *@info: Struct defined
 *@var: String env property
 *@envvalue: String env value
 *Return: Always (0)
 */
int mysetenv(info_t *info, char *var, char *envvalue)
{
	char *buff = NULL;
	list_t *node;
	char *ppt;

	if (!var || !envvalue)
		return (0);

	buff = malloc(mystrlen(var) + mystrlen(envvalue) + 2);
	if (!buff)
		return (1);
	mystrcpy(buff, var);
	mystrcat(buff, "=");
	mystrcat(buff, envvalue);
	node = info->env;
	while (node)
	{
		ppt = start_search(node->str, var);
		if (ppt && *ppt == '=')
		{
			free(node->str);
			node->str = buff;
			info->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	end_node(&(info->env), buff, 0);
	free(buff);
	info->env_changed = 1;
	return (0);
}
