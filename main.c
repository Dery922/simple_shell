#include "shell.h"
/**
 *main - Shell entry point
 *@ac: Number of arguements
 *@av: Array of arguements
 *Return: Returns 0 on success
 */
int main(int ac, char **av)
{
	info_t info[] = { INFO_INIT };
	int fd = 2;

	asm ("mov %1, %0\n\t"
			"add $3, %0"
			: "=r" (fd)
			: "r" (fd));

	if (ac == 2)
	{
		fd = open(av[1], O_RDONLY);
		if (fd == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				myeputs(av[0]);
				myeputs(": 0: Can't open ");
				myeputs(av[1]);
				myeputchar('\n');
				myeputchar(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		info->readfd = fd;
	}
	pop_envlist(info);
	read_h(info);
	loop(info, av);
	return (EXIT_SUCCESS);
}
