#include "shell.h"
/**
 * _strcpy - a function that copy the string from src to dest
 * @d: the place to where we paste the string
 * @s: the source where we copy the string from
 * Return: the copied string to destination
 */
char *_strcpy(char *d, char *s)
{
	int a = 0;

	if (d == s || s == 0)
	{
		return (d);
	}
	while (s[a])
	{
		d[a] = s[a];
		a++;
	}
	d[a] = 0;
	return (d);
}
/**
 * _strdup - a function that can duplicate a string
 * @s: the string to be checked and to be duplicated
 * Return: the duplicated string
 */
char *_strdup(const char *s)
{
	char *res;
	int len = 0;

	if (s == NULL)
	{
		return (NULL);
	}
	while (*s++)
	{
		len++;
	}
	res = malloc(sizeof(char) * (len + 1));
	if (!res)
	{
		return (NULL);
	}
	for (len++; len--;)
	{
		res[len] = *--s;
	}
	return (res);
}
/**
 *_puts - a function theat prints an input string
 *@s: the string that will be printed
 * Return: there is nothing to be returned
 */
void _puts(char *s)
{
	int e = 0;

	if (!s)
	{
		return;
	}
	while (s[e] != '\0')
	{
		_putchar(s[e]);
		e++;
	}
}
/**
 * _putchar - a function that print out to stdout a single character
 * @cha: The character that will be printed
 * Return: 1 in case of success
 * erno is set approbiately and -1 in the case of error
 */
int _putchar(char cha)
{
	static int v;
	static char buf[BUF_WRITE_SIZE];

	if (cha == BUF_FLUSH || v >= BUF_WRITE_SIZE)
	{
		write(1, buf, v);
		v = 0;
	}
	if (cha != BUF_FLUSH)
	{
		buf[v++] = cha;
	}
	return (1);
}
