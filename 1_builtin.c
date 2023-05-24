#include "shell.h"
/**
 *myexit - Exits shell nterface
 *@info: Struct defined
 *Return: Exits shell
 */
int myexit(info_t *info)
{
	int exitck;

	if (info->argv[1])
	{
		exitck = myerratoi(info->argv[1]);
		if (exitck == -1)
		{
			info->status = 2;
			outerror(info, "Wrong number: ");
			myeputs(info->argv[1]);
			myeputchar('\n');
			return (1);
		}
		info->err_num = myerratoi(info->argv[1]);
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}
/**
 *mycd - Change directory
 *@info: Struct defined
 *Return: Always (0)
 */
int mycd(info_t *info)
{
	char *str, *dir, buffer[1024];
	int chdir_ret;

	str = getcwd(buffer, 1024);
	if (!str)
		myputs("TODO: >>getcwd failure emsg here<<\n");
	if (!info->argv[1])
	{
		dir = my_getenv(info, "HOME=");
		if (!dir)
			chdir_ret =
				chdir((dir = my_getenv(info, "PWD=")) ? dir : "/");
		else
			chdir_ret = chdir(dir);
	}
	else if (mystrcmp(info->argv[1], "-") == 0)
	{
		if (!my_getenv(info, "OLDPWD="))
		{
			myputs(str);
			_putchar('\n');
			return (1);
		}
		myputs(my_getenv(info, "OLDPWD=")), _putchar('\n');
		chdir_ret =
			chdir((dir = my_getenv(info, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_ret = chdir(info->argv[1]);
	if (chdir_ret == -1)
	{
		outerror(info, "cannot cd intoto ");
		myeputs(info->argv[1]), myeputchar('\n');
	}
	else
	{
		mysetenv(info, "OLDPWD", my_getenv(info, "PWD="));
		mysetenv(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}
/**
 *myhelp - Brings help
 *@info: Struct defined
 *Return: Always (0)
 */
int myhelp(info_t *info)
{
	char **arg_array;

	arg_array = info->argv;
	myputs("Function not implemented yet \n");
	if (0)
		myputs(*arg_array);
	return (0);
}
