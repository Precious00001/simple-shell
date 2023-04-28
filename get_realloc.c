#include "shell.h"
/**
 **_memset - a function that has a constant byte to be filled within memory
 *@c: memory area referred to the pointer
 *@y: fill s with the byte
 *@b: the byte amounts to be filled
 *Return: to the memory s returned a pointer s
 */
char *_memset(char *c, char y, unsigned int b)
{
	unsigned int a;

	for (a = 0; a < b; a++)
		c[a] = y;
	return (c);
}
/**
 * ffree - a string of strings to be free
 * @ontoal: you can say a one string of alot of strings
 */
void ffree(char **ontoal)
{
	char **x = ontoal;

	if (!ontoal)
		return;
	while (*ontoal)
		free(*ontoal++);
	free(x);
}
/**
 * _realloc - a function that reallocates a couple of blocks of memory
 * @p: a pointer to the previous
 * @oz: previous block byte size
 * @nz: the new block byte size
 * Return: a pointer to be returned
 */
void *_realloc(void *p, unsigned int oz, unsigned int nz)
{
	char *b;

	if (!p)
		return (malloc(nz));
	if (!nz)
		return (free(p), NULL);
	if (nz == oz)
		return (p);

	b = malloc(nz);
	if (!b)
		return (NULL);

	oz = oz < nz ? oz : nz;
	while (oz--)
		b[oz] = ((char *)p)[oz];
	free(p);
	return (b);
}
