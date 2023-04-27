#include "shell.h"

/**
 *_eputs - prints an input string
 * @str: the string to be printed
 *
 * Return: Nothing
 */
void _eputs(char *str)
{
	if (str == NULL)
		return;

	for (; *str != '\0'; str++)
		_eputchar(*str);
}

/**
 * _eputchar - writes the character c to stderr
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _eputchar(char c)
{
	static char buf[BUF_WRITE_SIZE];
	static int buf_len;

	if (buf_len >= BUF_WRITE_SIZE || c == BUF_FLUSH)
	{
		write(STDERR_FILENO, buf, buf_len);
		buf_len = 0;
	}

	if (c != BUF_FLUSH)
		buf[buf_len++] = c;

	return (1);
}


/**
 * _putfd - writes the character c to given fd
 * @c: The character to print
 * @fd: The filedescriptor to write to
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putfd(char c, int fd)
{
	static int i;
	static char buf[BUF_WRITE_SIZE];

	if (c == BUF_FLUSH || i >= BUF_WRITE_SIZE)
	{
		write(fd, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}

/**
 *_putsfd - prints an input string
 * @str: the string to be printed
 * @fd: the filedescriptor to write to
 *
 * Return: the number of chars put
 */
int _putsfd(char *str, int fd)
{
	int i = 0;

	if (!str)
		return (0);
	for (i = 0; str[i]; i++)
		_putfd(str[i], fd);
	return (i);
}


