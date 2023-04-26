#include "shell.h"
/**
 * _strlen - a function that calculates the length of the string
 * @str: the string that we will check its length
 * Return: the integer length of the string
 */
int _strlen(char *str)
{
	int a = 0;

	if (!str)
	{
		return (0);
	}
	while (*str++)
	{
		a++;
	}
	return (a);
}
/**
 * _strcmp - a function that compares the two strings
 * @strn1: the 1st string
 * @strn2: the 2st string
 * Return: 0 if s1 = s2 and positive if s1 > s2 and negative if s2 > s1
 */
int _strcmp(char *strn1, char *strn2)
{
	int g = 0, a = 0;

	while (strn1[a] != '\0' && strn2[a] != '\0')
	{
		if (strn1[a] != strn2[a])
		{
			g = strn1[a] - strn2[a];
			return (g);
		}
		a++;
	}
	return (g);
}
/**
 * starts_with - a function that checks heystack start within the needle
 * @heystack: th string that we will search for
 * @ndl: to find the substring
 * Return: NULL or the address of the next heystack
 */
char *starts_with(const char *heystack, const char *ndl)
{
	while (*ndl)
	{
		if (*ndl++ != *heystack++)
		{
			return (NULL);
		}
	return ((char *)heystack);
	}
}

/**
 * _strcat - a function that concatenates the two strings
 * @d: the place where we concatenate the string
 * @s: the string that we will concatenate in the place of destination
 * Return: the concatenated string
 */
char *_strcat(char *d, char *s)
{
	char *res = d;

	while (*d)
	{
		d++;
	}
	while (*s)
	{
		*d++ = *s++;
	}
	*d = *s;
	return (res);
}
