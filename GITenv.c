#include "shell.h"

/**
 * GET_Environ - Return string Array copy of ENVIRON
 * @info: Str containing Potential arg
 * Return: Always Success
 */
char **GET_Environ(info_t *INF)
{
	if (!INF->Environment || INF->ENV_changed)
	{
		INF->Environment = List_to_strings(INF->ENV);
		INF->ENV_changed = 0;
	}
	return (INF->Environment);
}
/**
 * _UNsetenv - Remove an Environment
 * @info: Str containing Potential arg.
 *  Return: 1 on delete, 0 otherwise
 * @VAR: String
 */
int _UNsetenv(info_t *INF, char *VAR)
{
	List_t *node = INF->ENV;
	size_t U = 0;
	char *P0;

	if (!node || !VAR)
		return (0);

	while (node)
	{
		P0 = starts_with(node->STR, var);
		if (P0 && *P0 == '=')
		{
			INF->ENV_changed = delete_node_at_INDX(&(INF->ENV), U);
			U = 0;
			node = INF->ENV;
			continue;
		}
		node = node->next;
		U++;
	}
	return (INF->ENV_changed);
}
/**
 * _setenV - Initialize new Environment VAR
 * @info: Str containing Potential arg.
 * @VAR: String
 * @Value: String of the value of string ENV
 *  Return: Always Success
 */
int _setenV(info_t *INF, char *VAR, char *Value)
{
	char *buff = NULL;
	List_t *node;
	char *P0;

	if (!VAR || !Value)
		return (0);

	buff = malloc(_strlen(VAR) + _strlen(value) + 2);
	if (!buff)
		return (1);
	_strcpy(buff, VAR);
	_strcat(buff, "=");
	_strcat(buff, Value);
	node = INF->ENV;
	while (node)
	{
		P0 = starts_with(node->STR, VAR);
		if (P0 && *P0 == '=')
		{
			free(node->STR);
			node->STR = buff;
			INF->ENV_changed = 1;
			return (0);
		}
		node = node->next;
	}
	add_node_end(&(INF->ENV), b, 0);
	free(buff);
	INF->ENV_changed = 1;
	return (0);
}
