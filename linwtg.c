#include "shell.h"
/**
 * input_buf - a function that contains command the chained like a buffer
 * @info: a structure parameter
 * @abuff: the buffer address
 * @tall: the length variable address
 * Return: the number of bytes that have been red
 */
ssize_t input_buf(info_t *info, char **abuff, size_t *tall)
{
	size_t thp_tall = 0;
	ssize_t res = 0;

	if (!*tall)
	{
		free(*abuff);
		*abuff = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		res = getline(abuff, &thp_tall, stdin);
#else
		res = _getline(info, abuff, &thp_tall);
#endif
		if (res > 0)
		{
			if ((*abuff)[res - 1] == '\n')
			{
				(*abuff)[res - 1] = '\0';
				res--;
			}
			info->linecount_flag = 1;
			remove_comments(*abuff);
			build_history_list(info, *abuff, info->histcount++);
			{
				*tall = res;
				info->cmd_buf = abuff;
			}
		}
	}
	return (res);
}
/**
 * get_input - a function that get a line and substract it from the new line
 * @info: a structure parameter
 * Return: the amount of bytes that is red
 */
ssize_t get_input(info_t *info)
{
	char **abuff_b = &(info->arg), *t;
	static char *abuff;
	ssize_t res = 0;
	static size_t a, b, tall;

	_putchar(BUF_FLUSH);
	res = input_buf(info, &abuff, &tall);
	if (res == -1)
	{
		return (-1);
	}
	if (tall)
	{
		b = a;
		t = abuff + a;

		check_chain(info, abuff, &b, a, tall);
		while (b < tall)
		{
			if (is_chain(info, abuff, &b))
			{
				break;
			}
			b++;
		}

		a = b + 1;
		if (a >= tall)
		{
			a = tall = 0;
			info->cmd_buf_type = NOR_CMD;
		}
		*abuff_b = t;
		return (_strlen(t));
	}
	*abuff_b = abuff;
	return (res);
}
/**
 * read_buf - a function that reads a buffer
 * @info: a structure parameter
 * @buf: the buffer to be checked
 * @i: the size
 * Return: the result
 */
ssize_t read_buf(info_t *info, char *buf, size_t *i)
{
	ssize_t res = 0;

	if (*i)
	{
		return (0);
	}
	res = read(info->readfd, buf, BUF_READ_SIZE);
	if (res >= 0)
	{
		*i = res;
	}
	return (res);
}
/**
 * sigintHandler - a function that blocks the ctrl_c
 * @tint_n: the number of signals that recieved
 * Return: in finall return a void
 */
void sigintHandler(__attribute__((unused))int tint_n)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
/**
 * _getline - gets the next line of input from STDIN
 * @info: parameter struct
 * @point: address of pointer to buffer, preallocated or NULL
 * @len: size of preallocated ptr buffer if not NULL
 * Return: s
 */
int _getline(info_t *info, char **point, size_t *len)
{
	static size_t a, tall;
	static char abuff[BUF_READ_SIZE];
	size_t b;
	ssize_t res = 0, str = 0;
	char *t = NULL, *n_t = NULL, *k;

	t = *point;
	if (t && len)
	{
		str = *len;
	}
	if (a == tall)
	{
		a = tall = 0;
	}
	res = read_buf(info, abuff, &tall);
	if (res == -1 || (res == 0 && tall == 0))
	{
		return (-1);
	}
	k = _strchr(abuff + a, '\n');
	b = k ? 1 + (unsigned int)(k - abuff) : tall;
	n_t = _realloc(t, str, str ? str + b : b + 1);
	if (!n_t)
	{
		return (t ? free(t), -1 : -1);
	}
	if (str)
	{
		_strncat(n_t, abuff + a, b - a);
	}
	else
		_strncpy(n_t, abuff + a, b - a + 1);
	str += b - a;
	a = b;
	t = n_t;
	if (len)
		*len = str;
	*point = t;
	return (str);
}
