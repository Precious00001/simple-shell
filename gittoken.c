#include "shell.h"
/**
 * **strtow - a function that by which the string splits to words
 * @s: the string to be input
 * @deli: the string delimeter
 * Return: a null on failure and a pointer to an array os strings
 */
char **strtow(char *s, char *deli)
{
	int a, b, c, m, nw = 0;
	char **k;

	if (s == NULL || s[0] == 0)
		return (NULL);
	if (!deli)
		deli = " ";
	for (a = 0; s[a] != '\0'; a++)
		if (!is_delim(s[a], deli) && (is_delim(s[a + 1], deli) || !s[a + 1]))
			nw++;

	if (nw == 0)
		return (NULL);
	k = malloc((1 + nw) * sizeof(char *));
	if (!k)
		return (NULL);
	for (a = 0, b = 0; b < nw; b++)
	{
		while (is_delim(s[a], deli))
			a++;
		c = 0;
		while (!is_delim(s[a + c], deli) && s[a + c])
			c++;
		k[b] = malloc((c + 1) * sizeof(char));
		if (!k[b])
		{
			for (c = 0; c < b; c++)
				free(k[c]);
			free(k);
			return (NULL);
		}
		for (m = 0; m < c; m++)
			k[b][m] = s[a++];
		k[b][m] = 0;
	}
	k[b] = NULL;
	return (k);
}
/**
 * **strtow2 - a function that splits a string into word
 * @s: the string that is inputted
 * @deli: delimeter
 * Return: null on failure and pointer to an array of strings
 */
char **strtow2(char *s, char deli)
{
	int a, b, c, n, nws = 0;
	char **k;

	if (s == NULL || s[0] == 0)
		return (NULL);
	for (a = 0; s[a] != '\0'; a++)
		if ((s[a] != deli && s[a + 1] == deli) ||
		    (s[a] != deli && !s[a + 1]) || s[a + 1] == deli)
			nws++;
	if (nws == 0)
		return (NULL);
	k = malloc((1 + nws) * sizeof(char *));
	if (!k)
		return (NULL);
	for (a = 0, b = 0; b < nws; b++)
	{
		while (s[a] == deli && s[a] != deli)
			a++;
		c = 0;
		while (s[a + c] != deli && s[a + c] && s[a + c] != deli)
			c++;
		k[b] = malloc((c + 1) * sizeof(char));
		if (!k[b])
		{
			for (c = 0; c < b; c++)
				free(k[c]);
			free(k);
			return (NULL);
		}
		for (n = 0; n < c; n++)
			k[b][n] = s[a++];
		k[b][n] = 0;
	}
	k[b] = NULL;
	return (k);
}
