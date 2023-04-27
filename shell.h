#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#define BUF_READ_SIZE 1024
#define BUF_WRITE_SIZE 1024
#define BUF_FLUSH -1
#define NOR_CMD 0
#define OR_CMD 1
#define AND_CMD 2
#define CHAI_CMD 3
#define CONVERT_LOWERCASE 1
#define CONVERT_UNSIGNED 2
#define US_GETLINE 0
#define US_STRTOK 0
#define HST_FILE ".our_history_on_simple_shell"
#define HST_MAX 4096
extern char **environ;
/**
 * struct listofstr - a singly linked list
 * @number : the number field
 * @str : the string
 * @next : to point to the next node
 */
typedef struct listofstr
{
	int number;
	char *str;
	struct listofstr *next;
} list_t;
/**
 * struct infopass - a struct that contains arguments to pass to a function
 * @arg : a string that is generated from the getline that contains arguments
 * @path : the current command path
 * @argv : an array of string that is generated from arg
 * @argc : the number of arguments
 * @fname : the name of the prgram file
 * @linecount : the error of count
 * @err_num : the error of code for the exit() function
 * @linecount_flag : if on count this is the line of input
 * @env : linked list
 * @environ: a custom modified copy of the environ
 * @alias: the alias node
 * @history: the history node
 * @histcount: the line number count of history
 * @status: the return of the last command
 * @env_changed: on if there is change in environ
 * @cmd_buf: the address of the pointer to cmd_buf
 * @cmd_buf_type: CMD_type ||, &&, ;
 * @readfd: to read the line input from fd
 */
typedef struct infopass
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int linecount;
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
 * struct builtin - a structure that contains a builtin string
 * @type : the command flag
 * @func : a function
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_t;
int is_chain(info_t *, char *, size_t *);
void check_chain(info_t *, char *, size_t *, size_t, size_t);
int replace_alias(info_t *);
int replace_vars(info_t *);
int replace_string(char **, char *);
int hsh(info_t *, char **);
int find_builtin(info_t *);
void find_cmd(info_t *);
void fork_cmd(info_t *);
int is_cmd(info_t *, char *);
char *dup_chars(char *, int, int);
char *find_path(info_t *, char *, char *);
int loophsh(char **);
void _eputs(char *);
int _eputchar(char);
int _putfd(char c, int fd);
int _putsfd(char *str, int fd);
int _strlen(char *);
int _strcmp(char *, char *);
char *starts_with(const char *, const char *);
char *_strcat(char *, char *);
char *_strcpy(char *, char *);
char *_strdup(const char *);
void _puts(char *);
int _putchar(char);
char *_strncpy(char *, char *, int);
char *_strncat(char *, char *, int);
char *_strchr(char *, char);
char **strtow(char *, char *);
char **strtow2(char *, char);
char *_memset(char *, char, unsigned int);
void ffree(char **);
void *_realloc(void *, unsigned int, unsigned int);
int bfree(void **);
int interactive(info_t *);
int is_delim(char, char *);
int _isalpha(int);
int _atoi(char *);
int _erratoi(char *);
void print_error(info_t *, char *);
int print_d(int, int);
char *convert_number(long int, int, int);
void remove_comments(char *);
int _myexit(info_t *);
int _mycd(info_t *);
int _myhelp(info_t *);
int _myhistory(info_t *);
int _myalias(info_t *);
ssize_t get_input(info_t *);
int _getline(info_t *, char **, size_t *);
void sigintHandler(int);
void clear_info(info_t *);
void set_info(info_t *, char **);
void free_info(info_t *, int);
char *_getenv(info_t *, const char *);
int _myenv(info_t *);
int _mysetenv(info_t *);
int _myunsetenv(info_t *);
int populate_env_list(info_t *);
list_t *add_node(list_t **, const char *, int);
list_t *add_node_end(list_t **, const char *, int);
size_t print_list_str(const list_t *);
int delete_node_at_index(list_t **, unsigned int);
void free_list(list_t **);
char **get_environ(info_t *);
int _unsetenv(info_t *, char *);
int _setenv(info_t *, char *, char *);
char *get_history_file(info_t *info);
int write_history(info_t *info);
int read_history(info_t *info);
int build_history_list(info_t *info, char *buf, int linecount);
int renumber_history(info_t *info);
size_t list_len(const list_t *);
char **list_to_strings(list_t *);
size_t print_list(const list_t *);
list_t *node_starts_with(list_t *, char *, char);
ssize_t get_node_index(list_t *, list_t *);
#endif