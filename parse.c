#include "shell.h"

/**
 * is_cmd - executable command
 * @finf : structure info
 * @pth: the file path
 * Return: 0 in the otherwise case and 1 if true
 */
int is_cmd(info_t *finf, char *pth)
{
	struct stat st;

	(void)finf;
	if (!pth || stat(pth, &st))
	{
		return (0);
	}

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * dup_chars - characters to be duplicated
 * @pths: string path
 * @strt: index of starting
 * @stp: index to stop
 * Return: pointer to return a new buffer
 */
char *dup_chars(char *pths, int strt, int stp)
{
	static char abuff[1024];
	int a = 0, c = 0;

	for (c = 0, a = strt; a < stp; a++)
	{
		if (pths[a] != ':')
		{
			abuff[c++] = pths[a];
		}
	}
	abuff[c] = 0;
	return (abuff);
}
/**
 * find_path - a function to look at the cmd in the pathstring
 * @finf: the structure information
 * @pths: string path
 * @cemde: to find the cmd
 * Return: null or if the path if cmd found
 */
char *find_path(info_t *finf, char *pths, char *cemde)
{
	int a = 0, place_now = 0;
	char *pth;

	if (!pths)
	{
		return (NULL);
	}
	if ((_strlen(cemde) > 2) && starts_with(cemde, "./"))
	{
		if (is_cmd(finf, cemde))
		{
			return (cemde);
		}
	}
	while (1)
	{
		if (!pths[a] || pths[a] == ':')
		{
			pth = dup_chars(pths, place_now, a);
			if (!*pth)
				_strcat(pth, cemde);
			else
			{
				_strcat(pth, "/");
				_strcat(pth, cemde);
			}
			if (is_cmd(finf, pth))
				return (pth);
			if (!pths[a])
				break;
			place_now = a;
		}
		a++;
	}
	return (NULL);
}
