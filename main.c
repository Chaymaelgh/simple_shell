#include "shell.h"
/**
 * main - Entry
 * @ac: arg Count
 * @av: arg Vector
 * Return: if was 0 Success,if 1 error
 */
int main(int ac, char **av)
{
	info_t INF[] = { INFO_INIT };
	int fd = 2;

	asm ("mov %1, %0\n\t"
		"add $3, %0"
		: "=r" (fd)
		: "r" (fd));

	if (ac == 2)
	{
		fd = open(av[1], O_RDONLY);
		if (fd == -1)
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
		INF->readfd = fd;
	}
	populate_ENV_List(INF);
	read_Histry(INF);
	hsh(INF, av);
	return (EXIT_SUCCESS);
}
