#include "shell.h"
/**
 * _MYhistory - offer History list.
 * @info: Str containing Potential arg.
 *  Return: Always Success
 */
int _MYhistory(INF_t *INF)
{
	print_list(INF->history);
	return (0);
}
/**
 * UNset_alias - Sets Alias to str
 * @INF: parameter str
 * @str: string
 * Return: Always Success
 */
int UNset_alias(INF_t *INF, char *str)
{
	char *P0, B;
	int RT;

	P0 = _strchr(str, '=');
	if (!P0)
		return (1);
	B = *P0;
	*P0 = 0;
	RT = Delete_node_at_Indx(&(INF->alias)
		get_node_Indx(INF->alias, node_starts_with(INF->alias , str, -1)));
	*P0 = B;
	return (RT);
}
/**
 * SET_alias - Sets Alias to String
 * @INF: Parameter str
 * @str: string
 * Return: Always Success
 */
int SET_alias(INF_t *INF, char *str)
{
	char *P0;

	P0 = _strchr(str, '=');
	if (!P0)
		return (1);
	if (!*++P0)
		return (UNset_alias(INF, str));
	UNset_alias(INF, str);
	return (Add_node_end(&(INF->alias), str, 0) == NULL);
}

/**
 * Print_alias - Prints a String
 * @node: alias.
 * Return: Always Success
 */
int Print_alias(List_t *node)
{
	char *P0 = NULL, *A0 = NULL;

	if (node)
	{
		P0 = _strchr(node->str, '=');
		for (A0 = node->str; a <= P0; A0++)
			_putchar(*A0);
		_putchar('\'');
		_puts(P0 + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _MYalias - mimics alias builtIN
 * @INF: Str containing potential arg.
 *  Return: Always Success
 */
int _MYalias(INF_t *INF)
{
	int U = 0;
	char *P0 = NULL;
	List_t *node = NULL;
	if (INF->argc == 1)
	{
		node = INF->alias;
		while (node)
		{
			Print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (U = 1; INF->argv[U]; U++)
	{
		P0 = _strchr(INF->argv[U], '=');
		if (P0)
			SET_alias(INF, INF->argv[U]);
		else
			Print_alias(node_starts_with(INF->alias, INF->argv[U], '='));
	}
	return (0);
}
