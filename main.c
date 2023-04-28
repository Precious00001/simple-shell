#include "shell.h"
/**
 * main - a function entry point
 * @ac: the number of arguments
 * @av: the arguments that is contained in an array of arguments
 * Return: 1 in case of error and 0 in case of success
 */
int main(int ac, char **av)
{
	info_t finf[] = { INFO_INIT };
	int redfun = 2;

	asm ("mov %1, %0\n\t"
		"add $3, %0"
		: "=r" (redfun)
		: "r" (redfun));

	if (ac == 2)
	{
		redfun = open(av[1], O_RDONLY);
		if (redfun == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				_eputs(av[0]);
				_eputs(": 0: Can't open ");
				_eputs(av[1]);
				_eputchar('\n');
				_eputchar(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		finf->readfd = redfun;
	}
	populate_env_list(finf);
	read_history(finf);
	hsh(finf, av);
	return (EXIT_SUCCESS);
}
