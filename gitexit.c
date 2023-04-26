#include "shell.h"
/**
 * _strncat - a function that concatenates two strings
 * @dest : the string that will be concatenated
 * @src : the string which will concatenate the first string
 * @n : the number of bytes that can be used
 * Return: the concatenated string
 */
char *_strncat(char *dest, char *src, int n)
{
	char *str = dest;
	int a, b;

	a = 0;
	b = 0;
	while (dest[a] != '\0')
	{
		a++;
	}
	while (src[b] && b < n)
	{
		dest[a] = src[b];
		a++;
		b++;
	}
	if (b < n)
	{
		dest[a] = '\0';
	}
	return (str);
}
/**
 * _strncpy - a function that copy a string from a source to destination
 * @dest : the string that will be copied to
 * @src : the place that we will copy from
 * @n: the number of characters that we will copy
 * Return: the string that is copied
 */
char *_strncpy(char *dest, char *src, int n)
{
	int a, b;
	char *str = dest;

	a = 0;
	while (src[a] != '\0' && a < n - 1)
	{
		dest[a] = src[a];
		a++;
	}
	if (a < n)
	{
		a = b;
		while (b < n)
		{
			dest[b] = '\0';
			b++;
		}
	}
	return (str);
}
/**
 **_strchr - a function that locates a character in a string
 *@s: the string to be measured
 *@c: the character we are looking for
 *Return: a pointer to the memory
 */
char *_strchr(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}
