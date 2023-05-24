#include "shell.h"
/**
 *in_buf - Handles buffer chan commands
 *@info: Struct defined
 *@buff: Buffer address
 *@len: Lenght buff
 *Return: Number of bytes
 */
ssize_t in_buf(info_t *info, char **buff, size_t *len)
{
	ssize_t r = 0;
	size_t lenp = 0;

	if (!*len)
	{

		free(*buff);
		*buff = NULL;
		signal(SIGINT, sign_h);
#if USE_GETLINE
		r = getline(buff, &lenp, stdin);
#else
		r = mygetline(info, buff, &lenp);
#endif
		if (r > 0)
		{
			if ((*buff)[r - 1] == '\n')
			{
				(*buff)[r - 1] = '\0';
				r--;
			}
			info->linecount_flag = 1;
			handle_comment(*buff);
			build_list(info, *buff, info->histcount++);
			{
				*len = r;
				info->cmd_buf = buff;
			}
		}
	}
	return (r);
}
/**
 *get_input - Get line input
 *@info: Struct defined
 *Return: bytes read
 */
ssize_t get_input(info_t *info)
{
	static char *buff;
	static size_t i, j, len;
	ssize_t r = 0;
	char **buf_p = &(info->arg), *p;

	_putchar(BUF_FLUSH);
	r = in_buf(info, &buff, &len);
	if (r == -1)
		return (-1);
	if (len)
	{
		j = i;
		p = buff + i;

		checkfor_chain(info, buff, &j, i, len);
		while (j < len)
		{
			if (chain(info, buff, &j))
				break;
			j++;
		}
		i = j + 1;
		if (i >= len)
		{
			i = len = 0;
			info->cmd_buf_type = CMD_NORM;
		}

		*buf_p = p;
		return (mystrlen(p));
	}

	*buf_p = buff;
	return (r);
}
/**
 *read_b - Gets buffer
 *@info: Struct defined
 *@buff: The buffer
 *@size: Specifies size
 * Return: Number in integer
 */
ssize_t read_b(info_t *info, char *buff, size_t *size)
{
	ssize_t r = 0;

	if (*size)
		return (0);
	r = read(info->readfd, buff, READ_BUF_SIZE);
	if (r >= 0)
		*size = r;
	return (r);
}
/**
 *mygetline - Reads and saves input string
 *@info: Struct defined
 *@ptr: Pointer to buffer
 *@num: Size of ptr
 *Return: String
 */
int mygetline(info_t *info, char **ptr, size_t *num)
{
	static char buf[READ_BUF_SIZE];
	static size_t i, len;
	size_t k;
	ssize_t r = 0, s = 0;
	char *p = NULL;
	char *new = NULL;
	char *c;

	p = *ptr;
	if (p && num)
		s = *num;
	if (i == len)
		i = len = 0;

	r = read_b(info, buf, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);

	c = mystrchr(buf + i, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len;
	new = myrealloc(p, s, s ? s + k : k + 1);
	if (!new)
		return (p ? free(p), -1 : -1);

	if (s)
		mystrncat(new, buf + i, k - i);
	else
		mystrncpy(new, buf + i, k - i + 1);

	s += k - i;
	i = k;
	p = new;

	if (num)
		*num = s;
	*ptr = p;
	return (s);
}

/**
 *sign_h - Handles control plus c
 *@num: The number
 *Return: Void
 */
void sign_h(__attribute__((unused))int num)
{
	myputs("\n");
	myputs("$ ");
	_putchar(BUF_FLUSH);
}

