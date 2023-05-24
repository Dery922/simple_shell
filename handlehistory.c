#include "shell.h"
/**
 *get_file - Pulls history filke
 *@info: Struct defined
 *Return: Pointer to history file
 */
char *get_file(info_t *info)
{
	char *buff;
	char *dir;

	dir = my_getenv(info, "HOME=");
	if (!dir)
		return (NULL);
	buff = malloc(sizeof(char) * (mystrlen(dir) + mystrlen(HIST_FILE) + 2));
	if (!buff)
		return (NULL);
	buff[0] = 0;
	mystrcpy(buff, dir);
	mystrcat(buff, "/");
	mystrcat(buff, HIST_FILE);
	return (buff);
}
/**
 *write_history - Writes history
 *@info: Struct defined
 *Return: 1 == Succes
 */
int write_history(info_t *info)
{
	ssize_t fd;
	char *filename = get_file(info);
	list_t *node = NULL;

	if (!filename)
		return (-1);

	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fd == -1)
		return (-1);
	for (node = info->history; node; node = node->next)
	{
		myputsfd(node->str, fd);
		myputfd('\n', fd);
	}
	myputfd(BUF_FLUSH, fd);
	close(fd);
	return (1);
}
/**
 *read_h - Read history
 *@info: Struct defined
 *Return: 1 == Success
 */
int read_h(info_t *info)
{
	int i;
	int last = 0;
	int linecount = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *filename = get_file(info);

	if (!filename)
		return (0);
	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (0);
	rdlen = read(fd, buf, fsize);
	buf[fsize] = 0;
	if (rdlen <= 0)
		return (free(buf), 0);
	close(fd);
	for (i = 0; i < fsize; i++)
		if (buf[i] == '\n')
		{
			buf[i] = 0;
			build_list(info, buf + last, linecount++);
			last = i + 1;
		}
	if (last != i)
		build_list(info, buf + last, linecount++);
	free(buf);
	info->histcount = linecount;
	while (info->histcount-- >= HIST_MAX)
		del_node(&(info->history), 0);
	num_history(info);
	return (info->histcount);
}
/**
 *build_list - Builds histor list
 *@info: Struct defined
 *@buff: String buffer
 *@lcount: Line count
 *
 * Return: Always 0
 */
int build_list(info_t *info, char *buff, int lcount)
{
	list_t *node = NULL;

	if (info->history)
		node = info->history;
	end_node(&node, buff, lcount);

	if (!info->history)
		info->history = node;
	return (0);
}
/**
 *num_history - Renumbers list history file
 *@info: Struct defined
 *Return: Int to count
 */
int num_history(info_t *info)
{
	list_t *node = info->history;
	int i = 0;

	while (node)
	{
		node->num = i++;
		node = node->next;
	}
	return (info->histcount = i);
}

