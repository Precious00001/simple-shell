#include "shell.h"

/**
 * interactive - a functio that returns true if the shell is interactive
 * @finf: adress of the structure
 * Return: 0 otherwise and 1 if interactive
 */
int interactive(info_t *finf)
{
	return (isatty(STDIN_FILENO) && finf->readfd <= 2);
}
/**
 * is_delim - a function that checks the delimeter of a character
 * @t: the character to be checked
 * @del: string delimeter
 * Return: 0 in false case and 1 if true
 */
int is_delim(char t, char *del)
{
	while (*del)
		if (*del++ == t)
			return (1);
	return (0);
}

/**
 *_isalpha - a function that checks for the alphapatic of character
 *@t: The input character
 *Return: 0 otherwise and 1 if alphabetic
 */

int _isalpha(int t)
{
	if ((t >= 'a' && t <= 'z') || (t >= 'A' && t <= 'Z'))
		return (1);
	else
		return (0);
}
/**
 *_atoi - a function that converts a string to an integer
 *@t: the string that we want to convert
 *Return: converted otherwise and return 1 if no number in string
 */
int _atoi(char *t)
{
	int a, s = 1, f = 0, op;
	unsigned int res = 0;

	for (a = 0;  t[a] != '\0' && f != 2; a++)
	{
		if (t[a] == '-')
			s *= -1;

		if (t[a] >= '0' && t[a] <= '9')
		{
			f = 1;
			res *= 10;
			res += (t[a] - '0');
		}
		else if (f == 1)
			f = 2;
	}

	if (s == -1)
		op = -res;
	else
		op = res;

	return (op);
}
