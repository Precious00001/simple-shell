#include "shell.h"
/**
 * _myenv - a function that prints the current environment
 * @info: a structure that is containing potential arguments.
 * Used to maintain constant function prototype.
 * Return: 0 Always
 */
int _myenv(info_t *info)
{
	print_list_str(info->env);
	return (0);
}

/**
 * _getenv - a function that get the value of a variablen in an eviron
 * @info: a structure that is containing potential arguments.
 * Used to maintain
 * @name: env var name
 * Return: a null value
 */
char *_getenv(info_t *info, const char *name)
{
	list_t *node = info->env;
	char *b;

	while (node)
	{
		b = starts_with(node->str, name);
		if (b && *b)
			return (b);
		node = node->next;
	}
	return (NULL);
}

/**
 * _mysetenv - a function that Initialize a new environment variable,
 *             or modify the variable that is existed
 * @info: a structure that is containing potential arguments.
 *  Used to maintain constant function prototype.
 *  Return: 0
 */
int _mysetenv(info_t *info)
{
	if (info->argc != 3)
	{
		_eputs("the number of argument is incorrect\n");
		return (1);
	}
	if (_setenv(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * _myunsetenv - a function that removes the environment variable
 * @info: a structure that is containing
 * a potential arguments. and its Used to maintain
 * a constant function prototype.
 *  Return: Always 0
 */
int _myunsetenv(info_t *info)
{
	int a;

	if (info->argc == 1)
	{
		_eputs("the arguments is too much.\n");
		return (1);
	}
	for (a = 1; a <= info->argc; a++)
		_unsetenv(info, info->argv[a]);

	return (0);
}

/**
 * populate_env_list - a function that populates an env linked list
 * @info: a structure that is containing a potential arguments.
 * and its Used to maintain constant function prototype.
 * Return: 0
 */
int populate_env_list(info_t *info)
{
	list_t *node = NULL;
	size_t a;

	for (a = 0; environ[a]; a++)
		add_node_end(&node, environ[a], 0);
	info->env = node;
	return (0);
}
