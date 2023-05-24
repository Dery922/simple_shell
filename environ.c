#include "shell.h"
/**
 *myenv - Handles environment variables
 *@info: Struct defined
 *Return: Always (0)
 */
int myenv(info_t *info)
{
	out_liststr(info->env);
	return (0);
}
/**
 *my_getenv - Gets env value
 *@info: Struct defined
 *@name: Environment variable
 * Return: That value
 */
char *my_getenv(info_t *info, const char *name)
{
	list_t *node = info->env;
	char *buff;

	while (node)
	{
		buff = start_search(node->str, name);
		if (buff && *buff)
			return (buff);
		node = node->next;
	}
	return (NULL);
}
/**
 *mysetenv - Initialize new env var
 *@info: Struct defined
 *Return: Always (0)
 */
int seten(info_t *info)
{
	if (info->argc != 3)
	{
		myeputs("Wrong number of arguements\n");
		return (1);
	}
	if (mysetenv(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}
/**
 *myunsetenv - Remove a env var
 *@info: Struct defined
 *Return: Always (0)
 */
int unseten(info_t *info)
{
	int i;

	if (info->argc == 1)
	{
		myeputs("Too few arguements.\n");
		return (1);
	}
	for (i = 1; i <= info->argc; i++)
		myunsetenv(info, info->argv[i]);

	return (0);
}
/**
 *pop_envlist - Environment var population
 *@info: Struct defined
 *Return: Always (0)
 */
int pop_envlist(info_t *info)
{
	list_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		end_node(&node, environ[i], 0);
	info->env = node;
	return (0);
}
