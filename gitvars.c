#include "shell.h"

/**
 * is_chain - test if current char in buffer is a chain delimeter
 * @info: the parameter struct
 * @buf: the char buffer
 * @p: address of current position in buf
 *
 * Return: 1 if chain delimeter, 0 otherwise
 */
int is_chain(info_t *info, char *buf, size_t *p)
{
	size_t j = *p;

	if (buf[j] == '|' && buf[j + 1] == '|')
	{
		buf[j] = '\0';
		j++;
		info->cmd_buf_type = OR_CMD;
	}
	else if (buf[j] == '&' && buf[j + 1] == '&')
	{
		buf[j] = '\0';
		j++;
		info->cmd_buf_type = AND_CMD;
	}
	else if (buf[j] == ';')
	{
		buf[j] = '\0';
		info->cmd_buf_type = CHAIN_CMD;
	}

	else
		return (0);

	*p = j;
	return (1);
}

/**
 * check_chain - checks we should continue chaining based on last status
 * @info: the parameter struct
 * @buf: the char buffer
 * @p: address of current position in buf
 * @i: starting position in buf
 * @len: length of buf
 *
 * Return: Void
 */
void check_chain(info_t *info, char *buf, size_t *p, size_t i, size_t len)
{
	size_t j = *p;

	if (info->cmd_buf_type == AND_CMD)
	{
		if (info->status)
		{
			buf[i] = '\0';
			j = len;
		}
	}
	if (info->cmd_buf_type == OR_CMD)
	{
		if (!info->status)
		{
			buf[i] = 0;
			j = len;
		}
	}

	*p = j;
}

/**
 * replace_alias - replaces an aliases in the tokenized string
 * @info: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_alias(info_t *info)
{
	int i;
	list_t *node;
	char *p;

	for (i = 0; i < 10; i++)
	{
		node = node_starts_with(info->alias, info->argv[0], '=');
		if (!node)
			return (0);
		free(info->argv[0]);
		p = strchr(node->str, '=');
		if (!p)
			return (0);
		p = strdup(p + 1);
		if (!p)
			return (0);
		info->argv[0] = p;
	}
	return (1);
}

/**
 * replace_vars - replaces vars in the gittoken string
 * @info: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_vars(info_t *info)
{
	int i = 0;
	list_t *node;
	char *num_str = convert_number(info->status, 10, 0);
	char *pid_str = convert_number(getpid(), 10, 0);
	char *value = _strchr(node->str, '=') + 1;

	while (info->argv[i])
	{
		if (info->argv[i][0] == '$' && info->argv[i][1])
		{
			if (!_strcmp(info->argv[i], "$?"))
			{
				if (!num_str)
					return (-1);
				replace_string(&(info->argv[i]), _strdup(num_str));
				free(num_str);
			}
			else if (!_strcmp(info->argv[i], "$$"))
			{
				if (!pid_str)
					return (-1);
				replace_string(&(info->argv[i]), _strdup(pid_str));
				free(pid_str);
			}
			else
			{
				node = node_starts_with(info->env, &(info->argv[i][1]), '=');
				if (node)
				{
					if (!value)
						return (-1);
					replace_string(&(info->argv[i]), _strdup(value));
				}
				else
				{
					replace_string(&info->argv[i], _strdup(""));
				}
			}
		}
		i++;
	}
	return (0);
}



/**
 * replace_string - replaces string
 * @old: address of old string
 * @new: new string
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_string(char **old, char *new)
{
	if (*old)
		free(*old);
	*old = new;
	return (1);
}

