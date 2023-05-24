#include "shell.h"
/**
 * clear_INF - Initialize INF_t str
 * @INF: str address
 */
void clear_INF(INF_t *INF)
{
	INF->arg = NULL;
	INF->argv = NULL;
	INF->path = NULL;
	INF->argc = 0;
}
/**
 * set_INF - Initialize INF_t str
 * @INF: str adrs
 * @Av: arg vector
 */
void set_INF(INF_t *INF, char **Av)
{
	int U = 0;

	INF->fname = Av[0];
	if (INF->arg)
	{
		INF->argv = strtow(INF->arg, " \t");
		if (!INF->argv)
		{

			INF->argv = malloc(sizeof(char *) * 2);
			if (INF->argv)
			{
				INF->argv[0] = _strdup(INF->arg);
				INF->argv[1] = NULL;
			}
		}
		for (U = 0; INF->argv && INF->argv[U]; U++)
			;
		INF->argc = U;

		replace_alias(INF);
		replace_vars(INF);
	}
}
/**
 * free_INF - frees INF_t str field
 * @INF: str adrs
 * @all: true If Freeing filied
 */
void free_INF(INF_t *INF, int all)
{
	Ffree(INF->argv);
	INF->argv = NULL;
	INF->path = NULL;
	if (all)
	{
		if (!INF->cmd_buff)
			free(INF->arg);
		if (INF->ENV)
			free_list(&(INF->ENV));
		if (INF->history)
			free_list(&(INF->history));
		if (INF->Alias)
			free_list(&(INF->Alias));
		Ffree(INF->Environment);
			INF->Environment = NULL;
		Bfree((void **)INF->cmd_buff);
		if (INF->readfd > 2)
			close(INF->readfd);
		_putchar(BUFF_FLUSH);
	}
}
