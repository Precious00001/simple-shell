#include "shell.h"

/**
 * list_len - a function that determines the length of a linked list
 * @p: first node pointer
 * Return: list size
 */
size_t list_len(const list_t *p)
{
	size_t a = 0;

	while (p)
	{
		p = p->next;
		a++;
	}
	return (a);
}
/**
 * list_to_strings - a function that return an arrays of strings
 * @ptr1: first node pointer
 * Return: strings array
 */
char **list_to_strings(list_t *ptr1)
{
	list_t *n = ptr1;
	size_t a = list_len(ptr1), b;
	char **ss;
	char *s;

	if (!ptr1 || !a)
	{
		return (NULL);
	}
	ss = malloc(sizeof(char *) * (a + 1));
	if (!ss)
	{
		return (NULL);
	}
	for (a = 0; n; n = n->next, a++)
	{
		s = malloc(_strlen(n->str) + 1);
		if (!s)
		{
			for (b = 0; b < a; b++)
				free(ss[b]);
			free(ss);
			return (NULL);
		}
		s = _strcpy(s, n->str);
		ss[a] = s;
	}
	ss[a] = NULL;
	return (ss);
}
/**
 * print_list - all linked list printed by this function
 * @ptr1: a first node pointer
 * Return: list size
 */
size_t print_list(const list_t *ptr1)
{
	size_t a = 0;

	while (ptr1)
	{
		_puts(convert_number(ptr1->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(ptr1->str ? ptr1->str : "(nil)");
		_puts("\n");
		ptr1 = ptr1->next;
		a++;
	}
	return (a);
}
/**
 * node_starts_with - return string starting with prefix within a node
 * @n: list head pointer
 * @rfx: match string
 * @nc: match the next prefix of a string
 * Return: null or you can say match node
 */
list_t *node_starts_with(list_t *n, char *rfx, char nc)
{
	char *b = NULL;

	while (n)
	{
		b = starts_with(n->str, rfx);
		if (b && ((nc == -1) || (*b == nc)))
		{
			return (n);
		}
		n = n->next;
	}
	return (NULL);
}
/**
 * get_node_index - a function that get the index of a node
 * @h: list head pointer
 * @n: node pointer
 * Return: -1 or index of a node
 */
ssize_t get_node_index(list_t *h, list_t *n)
{
	size_t a = 0;

	while (h)
	{
		if (h == n)
		{
			return (a);
		}
		h = h->next;
		a++;
	}
	return (-1);
}
