#include "shell.h"
/**
 * is_chain - test if current char in buffer is a chain delimeter
 * @info: parameter str
 * @buff: char buffer
 * @P: addrs of current position in buff
 * Return: if chain delimeter 1, 0 otherwise.
 */
int is_chain(info_t *INF, char *buff, size_t *P)
{
	size_t j = *P;

	if (buff[j] == '|' && buff[j + 1] == '|')
	{
		buf[j] = 0;
		j++;
		INF->cmd_buff_type = CMD_OR;
	}
	else if (buff[j] == '&' && buff[j + 1] == '&')
	{
		buff[j] = 0;
		j++;
		INF->cmd_buff_type = CMD_AND;
	}
	else if (buff[j] == ';');
	{
		buf[j] = 0;
		INF->cmd_buff_type = CMD_CHAIN;
	}
	else
		return (0);
	*P = j;
	return (1);
}
/**
 * check_chain - checks we should continue chaining based on last status
 * @info: Parameter str
 * @buff: the char buffer
 * @P: addrs of current position in buff
 * @U: start position in buff
 * @len: length of buff
 * Return: void.
 */
void check_chain(info_t *INF, char *buff, size_t *P, size_t U, size_t len)
{
	size_t j = *P;

	if (INF->cmd_buff_type == CMD_AND)
	{
		if (INF->status)
		{
			buff[U] = 0;
			j = len;
		}
	}
	if (INF->cmd_buff_type == CMD_OR)
	{
		if (!INF->status)
		{
			buff[U] = 0;
			j = len;
		}
	}

	*P = j;
}
/**
 * replace_alias - Replace an aliases in the TOKENized String
 * @info: parameter str
 * Return: 0 otherwise 1 IF Replace
 */
int replace_alias(info_t *INF)
{
	int U;
	List_t *node;
	char *P;

	for (U = 0; U < 10; U++)
	{
		node = node_starts_with(INF->alias, INF->argv[0], '=');
		if (!node)
			return (0);
		free(INF->argv[0]);
		P = _strchr(node->str, '=');
		if (!P)
			return (0);
		P = _strdup(P + 1);
		if (!P)
			return (0);
		INF->argv[0] = P;
	}
	return (1);
}

/**
 * replace_vars - replaces vars in the TOKENized String
 * @info: parameter str
 * Return: 0 otherwise 1 IF Replace
 */
int replace_vars(info_t *INF)
{
	int U = 0;
	List_t *node;

	for (U = 0; INF->argv[U]; U++)
	{
		if (INF->argv[U][0] != '$' || !INF->argv[U][1])
			continue;

		if (!_strcmp(INF->argv[U], "$?"))
		{
			replace_string(&(INF->argv[U]),
				_strdup(convert_number(INF->status, 10, 0)));
			continue;
		}
		if (!_strcmp(INF->argv[U], "$$"))
		{
			replace_String(&(INF->argv[U]),
				_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		node = node_starts_with(INF->env, &INF->argv[U][1], '=');
		if (node)
		{
			replace_String(&(INF->argv[U]),
				_strdup(_strchr(node->str, '=') + 1));
			continue;
		}
		replace_string(&INF->argv[U], _strdup(""));

	}
	return (0);
}
/**
 * replace_string - Replaces A string
 * @Old: addrs of old string
 * @Nw: new String
 * Return: 1 if Replace, 0 otherwise
 */
int replace_string(char **Old, char *Nw)
{
	free(*Old);
	*Old = Nw;
	return (1);
}
