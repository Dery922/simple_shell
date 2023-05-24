#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2
#define USE_GETLINE 0
#define USE_STRTOK 0
#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;
/**
 *struct liststr - Function defined listr
 *@num: Number node
 *@str: String node in struct
 *@next: Next node in struct
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 *struct passinfo - Passes info
 *@arg: Arguements in functions in string data type
 *@argv: Arguements in functions in string data type
 *@path: PATH String
 *@argc: The number of arguements
 *@line_count: Holds the number of lines
 *@err_num: The error code
 *@linecount_flag: Flags on line count
 *@fname: File name of the program
 *@env: Environment variable node
 *@environ: Environment struct node
 *@history: Handles the history in the program
 *@alias: The alias node in the program
 *@env_changed: Changes environment var
 *@status: Status of execv command
 *@cmd_buf: Pointer to command buffer
 *@cmd_buf_type: Command buffer
 *@readfd: Reads from stdin file input
 *@histcount: The number of lines
 */
typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buf;
	int cmd_buf_type;
	int readfd;
	int histcount;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
		0, 0, 0}

/**
 *struct builtin - Struct Builtin function
 *@type: Type function defined
 *@func: Function defined
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;

int myexit(info_t *info);
int mycd(info_t *info);
int myhelp(info_t *info);
int myputsfd(char *str, int fd);
int myputfd(char chr, int fd);
int myeputchar(char chr);
void myeputs(char *str);
int myalias(info_t *info);
int outalias(list_t *node);
int setalias(info_t *info, char *str);
int unsetalias(info_t *info, char *str);
int myhistory(info_t *info);
void handle_comment(char *buff);
char *convert_num(long int no, int base, int flag);
int print_dec(int input, int fd);
void outerror(info_t *info, char *errstr);
int myerratoi(char *str);
int mystratoi(char *str);
int myalpha(int chr);
int mydelim(char chr, char *delim);
int interactive(info_t *info);
int myenv(info_t *info);
char *my_getenv(info_t *info, const char *name);
int seten(info_t *info);
int unseten(info_t *info);
int pop_envlist(info_t *info);
char *mystrncpy(char *dest, char *src, int num);
char *mystrncat(char *dest, char *src, int num);
char *mystrchr(char *str, char chr);
int mysetenv(info_t *info, char *var, char *envvalue);
int myunsetenv(info_t *info, char *var);
char **get_environ(info_t *info);
void clearinfo(info_t *info);
void setinfo(info_t *info, char **av);
void freeinfo(info_t *info, int whole);
void sign_h(__attribute__((unused))int num);
int mygetline(info_t *info, char **ptr, size_t *num);
ssize_t read_b(info_t *info, char *buff, size_t *size);
ssize_t get_input(info_t *info);
ssize_t in_buf(info_t *info, char **buff, size_t *len);
int mem_free(void **ptr);
char *get_file(info_t *info);
int num_history(info_t *info);
int build_list(info_t *info, char *buff, int lcount);
int read_h(info_t *info);
int write_history(info_t *info);
char *get_file(info_t *info);
void freelist(list_t **hd);
int del_node(list_t **head, unsigned int idx);
size_t out_liststr(const list_t *hd);
list_t *end_node(list_t **head, const char *str, int num);
list_t *add_node(list_t **head, int num, const char *str);
ssize_t find_index(list_t *head, list_t *node);
list_t *node_check(list_t *node, char *prefix, char chars);
size_t out_list(const list_t *hd);
char **list_str(list_t *head);
size_t list_lenght(const list_t *hd);
int main(int ac, char **av);
void *myrealloc(void *ptr, unsigned int old, unsigned int new);
void d2_free(char **p);
char *mymemset(char *sptr, char byt, unsigned int num);
int is_exec(info_t *info, char *path);
char *dbl_char(char *pathstr, int start, int stop);
char *findpth(info_t *info, char *paths, char *cmd);
char **str2_split(char *str, char d);
char **str_split(char *str, char *d);
int change_vars(info_t *info);
int change_string(char **old, char *new);
int change_alias(info_t *info);
void checkfor_chain(info_t *info, char *buffer, size_t *cc, size_t b, size_t c);
int chain(info_t *info, char *buffer, size_t *cc);
int _putchar(char c);
void myputs(char *str);
char *mystrdup(const char *str);
char *mystrcpy(char *dest, char *src);
int mystrlen(char *str);
int mystrcmp(char *s1, char *s2);
char *start_search(const char *haystack, const char *needle);
char *mystrcat(char *dest, char *src);
int loop(info_t *info, char **av);
int find_builtcmd(info_t *info);
void findcmd(info_t *info);
void forkcmd(info_t *info);
#endif
