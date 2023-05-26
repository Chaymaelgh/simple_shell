#include "shell.h"

/**
 * _MYenv - Prints the current Environment
 * @info: Str containing Potential arg.
 * Return: Always Success 
 */
int _MYenv(info_t INF)
{
	Print_list_Str(INF->Env);
	return (0);
}
/**
 * _GetEnv - Get value of Environment Var
 * @info: Str CONtaining Potential arg.
 * @Name: Environment var Name
 *
 * Return: Success
 */
char *_GetEnv(info_t *INF, const char *Name)
{
	List_t *node = INF->Env;
	char *P0;

	while (node)
	{
		P0 = starts_with(node->Str, Name);
		if (P0 && *P0)
			return (P0);
		node = node->next;
	}
	return (NULL);
}

/**
 * _MYsetenV - NEW  Environment VAR.
 * @info: Str containing Potential arg
 *  Return: Always Success
 */
int _MYsetenV(info_t *INF)
{
	if (INF->argc != 3)
	{
		_eputs("incorrect number of arguements\n");
		return (1);
	}
	if (_setenV(INF, INF->argv[1], INF->argv[2]))
		return (0);
	return (1);
}
/**
 * _MYunsetenV - Remove Var Environment
 * @info: str containing Potential arg.
 *  Return: Always Success
 */
int _MYunsetenV(info_t *INF)
{
	int U;

	if (info->argc == 1)
	{
		_eputs("too Few arguements.\n");
		return (1);
	}
	for (U = 1; U <= INF->argc; U++)
		_unsetenV(INF, INF->argv[U]);
	return (0);
}
/**
 * populate_ENV_list - populate ENV List
 * @info: Str containing Potential arg
 * Return: Always Success
 */
int populate_ENV_list(info_t *INF)
{
	List_t *node = NULL;
	size_t U;

	for (U = 0; Enviroment[U]; U++)
		add_node_end(&node, Environment[U], 0);
	INF->ENV = node;
	return (0);
}
