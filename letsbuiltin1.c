#include "shell.h"

/**
 * _myhistory - displays the history list, one command by line, preceded
 *              with line numbers, starting at 0.
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int _myhistory(info_t *info)
{
	list_t *history_node = info->history;

	while (history_node)
	{
		printf("%s\n", history_node->str);
		history_node = history_node->next;
	}
	return (0);
}


/**
 * unset_alias - sets alias to string
 * @info: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int unset_alias(info_t *info, char *str)
{
	char *a, b;
	int ret;

	a = _strchr(str, '=');
	if (!a)
		return (1);
	b = *a;
	*a = 0;
	ret = delete_node_at_index(&(info->alias),
		get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
	*a = b;
	return (ret);
}

/**
 * set_alias - sets alias to string
 * @info: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int set_alias(info_t *info, char *str)
{
	char *p;
	int ret;

	p = _strchr(str, '=');
	if (!p)
		return (1);

	if (!*++p)
		return (unset_alias(info, str));

	unset_alias(info, str);
	ret = add_node_end(&(info->alias), str, 0) == NULL;
	return (ret);
}

/**
 * print_alias - prints an alias string
 * @node: the alias node
 *
 * Return: Always 0 on success, 1 on error
 */
int print_alias(list_t *node)
{

	char *p = NULL, *a = NULL;


	if (node)
	{

		p = _strchr(node->str, '=');

		for (a = node->str; a <= p; a++)
			_putchar(*a);


		_putchar('\'');
		_puts(p + 1);

		_puts("'\n");

		return (0);
	}

	return (1);
}

/**
 * _myalias - mimics the alias builtin (man alias)
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int _myalias(info_t *info)
{
	char *p;
	list_t *node;
	int i;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}


	for (i = 1; info->argv[i]; i++)
	{
		p = strchr(info->argv[i], '=');

		if (p != NULL)
			set_alias(info, info->argv[i]);
		else
		{
			node = node_starts_with(info->alias, info->argv[i], '=');
			if (node != NULL)
				print_alias(node);
		}
	}

	return (0);
}


