#include "shell.h"
/**
 * get_history_file - a function that gets the file from history
 * @info: a structure parameter
 * Return: a history file that is allocated in the string
 */

char *get_history_file(info_t *info)
{
	char *abuff, *yo;

	yo = _getenv(info, "HOME=");
	if (!yo)
	{
		return (NULL);
	}
	abuff = malloc(sizeof(char) * (_strlen(yo) + _strlen(HST_FILE) + 2));
	if (!abuff)
	{
		return (NULL);
	}
	abuff[0] = 0;
	_strcpy(abuff, yo);
	_strcat(abuff, "/");
	_strcat(abuff, HST_FILE);
	return (abuff);
}
/**
 * write_history - a function that appends to an existing file or create a file
 * @info: a structure of the parameter
 * Return:in success it return 1 otherwise -1
 */
int write_history(info_t *info)
{
	ssize_t fd;
	char *filename = get_history_file(info);
	list_t *node = NULL;

	if (!filename)
	{
		return (-1);
	}
	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fd == -1)
	{
		return (-1);
	}
	for (node = info->history; node; node = node->next)
	{
		_putsfd(node->str, fd);
		_putfd('\n', fd);
	}
	_putfd(BUF_FLUSH, fd);
	close(fd);
	return (1);
}
/**
 * read_history - reads history from file
 * @info: the parameter struct
 *
 * Return: histcount on success, 0 otherwise
 */
int read_history(info_t *info)
{
	int i, last = 0, linecount = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *filename = get_history_file(info);

	if (!filename)
		return (0);

	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (0);
	rdlen = read(fd, buf, fsize);
	buf[fsize] = 0;
	if (rdlen <= 0)
		return (free(buf), 0);
	close(fd);
	for (i = 0; i < fsize; i++)
		if (buf[i] == '\n')
		{
			buf[i] = 0;
			build_history_list(info, buf + last, linecount++);
			last = i + 1;
		}
	if (last != i)
		build_history_list(info, buf + last, linecount++);
	free(buf);
	info->histcount = linecount;
	while (info->histcount-- >= HST_MAX)
		delete_node_at_index(&(info->history), 0);
	renumber_history(info);
	return (info->histcount);
}
/**
 * build_history_list - a singly linked list that has entry added to it
 * @info: a potential arguments that is contained in this structure
 * @abuff: a buffer
 * @linecount: a history of a linecount
 * Return: 0
 */
int build_history_list(info_t *info, char *abuff, int linecount)
{
	list_t *node = NULL;

	if (info->history)
	{
		node = info->history;
	}
	add_node_end(&node, abuff, linecount);

	if (!info->history)
	{
		info->history = node;
	}
	return (0);
}

/**
 * renumber_history - after change the linked list rename the history
 * @info: potential arguments contained in a structure
 * Return: the newhistcount returned
 */
int renumber_history(info_t *info)
{
	list_t *node = info->history;
	int a = 0;

	while (node)
	{
		node->number = a++;
		node = node->next;
	}
	return (info->histcount = a);
}
