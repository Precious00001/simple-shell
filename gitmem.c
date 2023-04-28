#include "shell.h"
/**
 * bfree - a function that null the address and free the pointer
 * @ad: a pointer to free is the address
 * Return: 0 in the otherwise case and 1 if free
 */
int bfree(void **ad)
{
	if (ad && *ad)
	{
		free(*ad);
		*ad = NULL;
		return (1);
	}
	return (0);
}
