#include "shell.h"
/**
 *add_node - Add new node at head
 *@head: Pointer to fkirst node
 *@str: String part of node
 *@num: Node index
 *Return: Always size of list
 */
list_t *add_node(list_t **head, int num, const char *str)
{
	list_t *Added_head;

	if (!head)
		return (NULL);
	Added_head = malloc(sizeof(list_t));
	if (!Added_head)
		return (NULL);
	mymemset((void *)Added_head, 0, sizeof(list_t));
	Added_head->num = num;
	if (str)
	{
		Added_head->str = mystrdup(str);
		if (!Added_head->str)
		{
			free(Added_head);
			return (NULL);
		}
	}
	Added_head->next = *head;
	*head = Added_head;
	return (Added_head);
}
/**
 *end_node - Adds new node at end
 *@head: Ponts to first node
 *@str: String part of node
 *@num: Node index
 * Return: Always size of list
 */
list_t *end_node(list_t **head, const char *str, int num)
{
	list_t *Added_node, *node;

	if (!head)
		return (NULL);

	node = *head;
	Added_node = malloc(sizeof(list_t));
	if (!Added_node)
		return (NULL);
	mymemset((void *)Added_node, 0, sizeof(list_t));
	Added_node->num = num;
	if (str)
	{
		Added_node->str = mystrdup(str);
		if (!Added_node->str)
		{
			free(Added_node);
			return (NULL);
		}
	}
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = Added_node;
	}
	else
		*head = Added_node;
	return (Added_node);
}
/**
 *out_liststr - Prints string in list
 *@hd: Pointer to first node
 *Return: Returns size of list
 */
size_t out_liststr(const list_t *hd)
{
	size_t i = 0;

	while (hd)
	{
		myputs(hd->str ? hd->str : "(nil)");
		myputs("\n");
		hd = hd->next;
		i++;
	}
	return (i);
}
/**
 *del_node - Deletes the node at said index
 *@head: Points to first node
 *@idx: Index
 *Return: On success return 1 else 0
 */
int del_node(list_t **head, unsigned int idx)
{
	list_t *node, *prev;
	unsigned int i = 0;

	if (!head || !*head)
		return (0);

	if (!idx)
	{
		node = *head;
		*head = (*head)->next;
		free(node->str);
		free(node);
		return (1);
	}
	node = *head;
	while (node)
	{
		if (i == idx)
		{
			prev->next = node->next;
			free(node->str);
			free(node);
			return (1);
		}
		i++;
		prev = node;
		node = node->next;
	}
	return (0);
}
/**
 *freelist - Frees contents of list
 *@hd: Pointer to head node
 * Return: Returns nothing
 */
void freelist(list_t **hd)
{
	list_t *node, *next_node, *head;

	if (!hd || !*hd)
		return;
	head = *hd;
	node = head;
	while (node)
	{
		next_node = node->next;
		free(node->str);
		free(node);
		node = next_node;
	}
	*hd = NULL;
}
