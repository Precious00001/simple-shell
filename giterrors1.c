#include "shell.h"
/**
 * _erratoi - a function that converts a string to an integer
 * @s : the string that will be converted
 * Return: -1 on error and 0 if no number in string and otherwise the number
 */
int _erratoi(char *s)
{
	int a = 0;

	unsigned int long res = 0;

	if (*s == '+')
	{
		s++;
	}
	for (a = 0; s[a] != '\0'; a++)
	{
		if (s[a] >= '0' && s[a] <= '9')
		{
			res *= 10;
			res += (s[a] - '0');
			if (res > INT_MAX)
			{
				return (-1);
			}
		}
		else
		{
			return (-1);
		}
	}
		return (res);
}
/**
 * print_d - a function that prints a number in base 10
 * @input : is the input
 * @fd : the filedescriptor
 * Return: the number of character that is printed
 */
int print_d(int input, int fd)
{
	int a, cnt = 0;
	unsigned int _abc_, now;
	int (*__putchar)(char) = _putchar;

	if (fd == STDERR_FILENO)
	{
		__putchar = _eputchar;
	}
	if (input < 0)
	{
		_abc_ = -input;
		__putchar('-');
		cnt++;
	}
	else
	{
		_abc_ = input;
	}
	now = _abc_;
	for (a = 1000000000; a > 1; a /= 10)
	{
		if (_abc_ / a)
		{
			__putchar('0' + now / a);
			cnt++;
		}
		now %= a;
	}
	__putchar('0' + now);
	cnt++;

	return (cnt);
}
/**
 * print_error - print a error message
 * @info : return info and parameter struct
 * @estr : a string that is containing specified error type
 * Return: 0 if no number in string and otherwise it return a number
 * and -1 in error
 */
void print_error(info_t *info, char *estr)
{
	_eputs(info->fname);
	_eputs(": ");
	print_d(info->linecount, STDERR_FILENO);
	_eputs(": ");
	_eputs(info->argv[0]);
	_eputs(": ");
	_eputs(estr);
}
/**
 * convert_number - a function that work as convention
 * @flags: flags argument
 * @num: is a number
 * @base: is a base
 * Return: a string is returned
 */
char *convert_number(long int num, int base, int flags)
{
	static char *ray;
	char sin = 0;
	static char buf[50];
	char *ptr;
	unsigned long a = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		a = -num;
		sin = '-';
	}
	ray = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buf[49];
	*ptr = '\0';

	do	{
		*--ptr = ray[a % base];
		a /= base;
	} while (a != 0);

	if (sin)
		*--ptr = sin;
	return (ptr);
}
/**
 * remove_comments - a function that replaces
 * the first instance of '#' with '\0'
 * @buf : the address of the modified string
 * Return: 0 always
 */
void remove_comments(char *buf)
{
	int a;

	for (a = 0; buf[a] != '\0'; a++)
	{
		if (buf[a] == '#' && (!a || buf[a - 1] == ' '))
		{
			buf[a] = '\0';
			break;
		}
}
}
