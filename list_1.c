#include "shell.h"
/**
 *list_lenght - Lenght of list
 *@hd: Pointer to first node
 * Return: Returns size of list
 */
size_t list_lenght(const list_t *hd)
{
	size_t j = 0;

	while (hd)
	{
		hd = hd->next;
		j++;
	}
	return (j);
}
/**
 *list_str - Returns array of strings based on struct
 *@head: pointer to first node
 *Return: Returns arrays of strings
 */
char **list_str(list_t *head)
{
	list_t *node = head;
	size_t i = list_lenght(head), j;
	char **strs;
	char *str;

	if (!head || !i)
		return (NULL);
	strs = malloc(sizeof(char *) * (i + 1));
	if (!strs)
		return (NULL);
	for (i = 0; node; node = node->next, i++)
	{
		str = malloc(mystrlen(node->str) + 1);
		if (!str)
		{
			for (j = 0; j < i; j++)
				free(strs[j]);
			free(strs);
			return (NULL);
		}
		str = mystrcpy(str, node->str);
		strs[i] = str;
	}
	strs[i] = NULL;
	return (strs);
}
/**
 *out_list - Prints the contents of the linked list
 *@hd: Points to the first node
 *Return: Returns the size of list
 */
size_t out_list(const list_t *hd)
{
	size_t i = 0;

	while (hd)
	{
		myputs(convert_num(hd->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		myputs(hd->str ? hd->str : "(nil)");
		myputs("\n");
		hd = hd->next;
		i++;
	}
	return (i);
}
/**
 *node_check - Chec for prefix against nodes
 *@node: Points to head
 *@prefix: Content to search and match
 *@chars: Char after prefix
 *Return: Matched prefix and node or NULL
 */
list_t *node_check(list_t *node, char *prefix, char chars)
{
	char *ptr = NULL;

	while (node)
	{
		ptr = start_search(node->str, prefix);
		if (ptr && ((chars == -1) || (*ptr == chars)))
			return (node);
		node = node->next;
	}
	return (NULL);
}
/**
 *find_index - gets the index of a node
 *@head: Pointer to head of list
 *@node: Pointer to nodes
 *Return: The index at which node is
 */
ssize_t find_index(list_t *head, list_t *node)
{
	size_t i = 0;

	while (head)
	{
		if (head == node)
			return (i);
		head = head->next;
		i++;
	}
	return (-1);
}
