#include "shell.h"
/**
 * get_environ - a function that return the string array copy
 * @finf: a potential arguments contained in a structure
 * Return: 0 in all time
 */
char **get_environ(info_t *finf)
{
	if (!finf->environ || finf->env_changed)
	{
		finf->environ = list_to_strings(finf->env);
		finf->env_changed = 0;
	}

	return (finf->environ);
}
/**
 * _unsetenv - a function that removes a variable of an environment
 * @finf: a potential arguments contained in a structure
 *  Return: 0 otherwise and 1 in delete
 * @v:  the property of string env var
 */
int _unsetenv(info_t *finf, char *v)
{
	list_t *n = finf->env;
	size_t a = 0;
	char *b;

	if (!n || !v)
		return (0);

	while (n)
	{
		b = starts_with(n->str, v);
		if (b && *b == '=')
		{
			finf->env_changed = delete_node_at_index(&(finf->env), a);
			a = 0;
			n = finf->env;
			continue;
		}
		n = n->next;
		a++;
	}
	return (finf->env_changed);
}
/**
 * _setenv - a new environment variable to be initialized or modified
 * if one is existed
 * @finf: a potential arguments contained in a structure
 * @v: var property of string env
 * @val: var value of a string environment
 *  Return: 0 in all time
 */
int _setenv(info_t *finf, char *v, char *val)
{
	char *abuff = NULL;
	list_t *n;
	char *b;

	if (!v || !val)
		return (0);

	abuff = malloc(_strlen(v) + _strlen(val) + 2);
	if (!abuff)
		return (1);
	_strcpy(abuff, v);
	_strcat(abuff, "=");
	_strcat(abuff, val);
	n = finf->env;
	while (n)
	{
		b = starts_with(n->str, v);
		if (b && *b == '=')
		{
			free(n->str);
			n->str = abuff;
			finf->env_changed = 1;
			return (0);
		}
		n = n->next;
	}
	add_node_end(&(finf->env), abuff, 0);
	free(abuff);
	finf->env_changed = 1;
	return (0);
}
