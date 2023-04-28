#include "shell.h"
/**
 * _strncpy - a function that copy a string from a source to destination
 * @d : the string that will be copied to
 * @sr : the place that we will copy from
 * @x: the number of characters that we will copy
 * Return: the string that is copied
 */
char *_strncpy(char *d, char *sr, int x)
{
	int a, b;
	char *c = d;

	a = 0;
	while (sr[a] != '\0' && a < x - 1)
	{
		d[a] = sr[a];
		a++;
	}
	if (a < x)
	{
		b = a;
		while (b < x)
		{
			d[b] = '\0';
			b++;
		}
	}
	return (c);
}
/**
 * _strncat - a function that concatenates two strings
 * @d : the string that will be concatenated
 * @sr : the string which will concatenate the first string
 * @x : the number of bytes that can be used
 * Return: the concatenated string
 */
char *_strncat(char *d, char *sr, int x)
{
	int a, b;
	char *c = d;

	a = 0;
	b = 0;
	while (d[a] != '\0')
		a++;
	while (sr[b] != '\0' && b < x)
	{
		d[a] = sr[b];
		a++;
		b++;
	}
	if (b < x)
		d[a] = '\0';
	return (c);
}
/**
 **_strchr - a function that locates a character in a string
 *@str: the string to be measured
 *@g: the character we are looking for
 *Return: a pointer to the memory
 */
char *_strchr(char *str, char g)
{
	do {
		if (*str == g)
			return (str);
	} while (*str++ != '\0');

	return (NULL);
}
