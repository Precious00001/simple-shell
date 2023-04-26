#include "shell.h"

/**
 **_memset - fills memory with a constant byte
 *@s: the pointer to the memory area
 *@b: the byte to fill *s with
 *@n: the amount of bytes to be filled
 *Return: (s) a pointer to the memory area s
 */
char *_memset(char *s, char b, unsigned int n)
{
	char *ptr = s;

	while (n--)
		*ptr++ = b;
	return (s);
}


/**
 * ffree - frees a string of strings
 * @pp: string of strings
 */
void ffree(char **pp)
{
	char **a;
	a = pp;

	if (!pp)
		return;

	while (*pp)
	{
		char *p = *pp;
		*pp = NULL;
		free(p);
		pp++;
	}

	free(a);
}

/**
 * _realloc - reallocates a block of memory
 * @ptr: pointer to previous malloc'ated block
 * @old_size: byte size of previous block
 * @new_size: byte size of new block
 *
 * Return: pointer to da ol'block nameen.
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	void *new_ptr;

	if (new_size == 0)
	{
		free(ptr);
		return (NULL);
	}

	if (ptr == NULL)
		return (malloc(new_size));

	if (new_size <= old_size)
		return (ptr);

	new_ptr = malloc(new_size);
	if (!new_ptr)
		return (NULL);

	memcpy(new_ptr, ptr, old_size);
	free(ptr);
	return (new_ptr);
}

