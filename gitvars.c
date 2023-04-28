#include "shell.h"

/**
 * is_chain - a function that test the chain
 * @finf: a structure parameter
 * @abuff: buffer char
 * @b: address
 * Return:0 in otherwise condition and 1 if is chain delimeter
 */
int is_chain(info_t *finf, char *abuff, size_t *b)
{
	size_t g = *b;

	if (abuff[g] == '|' && abuff[g + 1] == '|')
	{
		abuff[g] = 0;
		g++;
		finf->cmd_buf_type = OR_CMD;
	}
	else if (abuff[g] == '&' && abuff[g + 1] == '&')
	{
		abuff[g] = 0;
		g++;
		finf->cmd_buf_type = AND_CMD;
	}
	else if (abuff[g] == ';')
	{
		abuff[g] = 0;
		finf->cmd_buf_type = CHAI_CMD;
		abuff[g] = 0;
		finf->cmd_buf_type = CHAI_CMD;
	}
	else
		return (0);
	*b = g;
	return (1);
}

/**
 * check_chain - a function that checks depend on the last statues
 * if we should continue chaining
 * @finf: the structure parameter
 * @abuff: buffer char
 * @ad: the current pointer in a buffer adress
 * @a : a buf starting position
 * @l: buf length
 * Return: nothing
 */
void check_chain(info_t *finf, char *abuff, size_t *ad, size_t a, size_t l)
{
	size_t g = *ad;

	if (finf->cmd_buf_type == AND_CMD)
	{
		if (finf->status)
		{
			abuff[a] = 0;
			g = l;
		}
	}
	if (finf->cmd_buf_type == OR_CMD)
	{
		if (!finf->status)
		{
			abuff[a] = 0;
			g = l;
		}
	}

	*ad = g;
}

/**
 * replace_alias - the tokenized string get replaced in the alias
 * @finf: the structure parameter
 * Return: in otherwise 0 and 1 if its replaced
 */
int replace_alias(info_t *finf)
{
	int a;
	list_t *n;
	char *b;

	for (a = 0; a < 10; a++)
	{
		n = node_starts_with(finf->alias, finf->argv[0], '=');
		if (!n)
		{
			return (0);
		}
		free(finf->argv[0]);
		b = _strchr(n->str, '=');
		if (!b)
		{
			return (0);
		}
		b = _strdup(b + 1);
		if (!b)
		{
			return (0);
		}
		finf->argv[0] = b;
	}
	return (1);
}
/**
 * replace_vars - in the tokenized string the vars get replaced
 * @finf: a structure parameter
 * Return: 0 otherwise and 1 if replaced
 */
int replace_vars(info_t *finf)
{
	int a = 0;
	list_t *n;

	for (a = 0; finf->argv[a]; a++)
	{
		if (finf->argv[a][0] != '$' || !finf->argv[a][1])
			continue;

		if (!_strcmp(finf->argv[a], "$?"))
		{
			replace_string(&(finf->argv[a]),
				_strdup(convert_number(finf->status, 10, 0)));
			continue;
		}
		if (!_strcmp(finf->argv[a], "$$"))
		{
			replace_string(&(finf->argv[a]),
				_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		n = node_starts_with(finf->env, &finf->argv[a][1], '=');
		if (n)
		{
			replace_string(&(finf->argv[a]),
				_strdup(_strchr(n->str, '=') + 1));
			continue;
		}
		replace_string(&finf->argv[a], _strdup(""));

	}
	return (0);
}

/**
 * replace_string - a function that replaces a string
 * @o: old string address
 * @w: the new string
 * Return: 0 otherwise and 1 if replaced
 */
int replace_string(char **o, char *w)
{
	free(*o);
	*o = w;
	return (1);
}
