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
	char *new_env;
	size_t var_len, value_len;

	var_len = _strlen(var);
	value_len = _strlen(value);

	if (!var || !value)
		return (0);

	new_env = malloc(var_len + value_len + 2);

	if (!new_env)
		return (1);

	_strcpy(new_env, var);
	new_env[var_len] = '=';
	_strcpy(new_env + var_len + 1, value);

	node_ptr = &(info->env);

	while (*node_ptr)
	{
		char *p = starts_with((*node_ptr)->str, var);

		if (p && *p == '=')
		{
			free((*node_ptr)->str);
			(*node_ptr)->str = new_env;
			info->env_changed = 1;
			return (0);
		}
		node_ptr = &((*node_ptr)->next);
	}

	add_node_end(node_ptr, new_env, 0);
	info->env_changed = 1;
	return (0);
}

