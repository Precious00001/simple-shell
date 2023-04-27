#include "shell.h"

/**
 * get_environ - returns the string array copy of our environ
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
char **get_environ(info_t *info)
{
	char **environ;

	if (info->environ && !info->env_changed)
		return (info->environ);

	environ = list_to_strings(info->env);

	if (environ)
	{
		if (info->environ)
			ffree(info->environ);
		info->environ = environ;
		info->env_changed = 0;
	}
	return (info->environ);
}
/**
 * _unsetenv - Remove an environment variable
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: 1 on delete, 0 otherwise
 * @var: the string env var property
 */
int _unsetenv(info_t *info, char *var)
{
	int count;
	list_t *prev = NULL;
	list_t *current = info->env;


	if (!info->env || !var)
		return (0);

	count = 0;

	while (current != NULL)
	{
		char *p = starts_with(current->str, var);

		if (p && *p == '=')
		{
			if (prev == NULL)
			{
				info->env = current->next;
			}
			else
			{
				prev->next = current->next;
			}
			free(current->str);
			free(current);
			count++;
			current = prev == NULL ? info->env : prev->next;
		}
		else
		{
			prev = current;
			current = current->next;
		}
	}
	info->env_changed = count > 0;
	return (info->env_changed);
}


/**
 * _setenv - Initialize a new environment variable,
 *             or modify an existing one
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * @var: the string env var property
 * @value: the string env var value
 *  Return: Always 0
 */
int _setenv(info_t *info, char *var, char *value)
{
	char *abuff = NULL;
	list_t *node;
	char *o;

	if (!var || !value)
		return (0);

	abuff = malloc(_strlen(var) + _strlen(value) + 2);
	if (!abuff)
		return (1);
	_strcpy(abuff, var);
	_strcat(abuff, "=");
	_strcat(abuff, value);
	node = info->env;
	while (node)
	{
		o = starts_with(node->str, var);
		if (o && *o == '=')
		{
			free(node->str);
			node->str = abuff;
			info->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	add_node_end(&(info->env), abuff, 0);
	free(abuff);
	info->env_changed = 1;
	return (0);
}
