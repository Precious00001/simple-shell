#include "shell.h"
/**
 * bfree - a function that null the address and free the pointer
 * @p: a pointer to free is the address
 * Return: 0 in the otherwise case and 1 if free
 */
int bfree(void **p)
{
	if (p && *p)
	{
		free(*p);
		*p = NULL;
		return (1);
	}
	return (0);
}
