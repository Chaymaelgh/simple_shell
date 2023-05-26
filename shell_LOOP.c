#include "shell.h"
/**
 * hsh - main shell LOOP
 * @info: Parameter AND return info str.
 * @av: Argument
 * Return: 0 on success, 1 on error.
 */
int hsh(info_t *INF, char **av)
{
	ssize_t r = 0;
	int BuiltIN_ret = 0;

	while (r != -1 && BuiltIN_ret != -2)
	{
		clear_info(INF);
		if (INTERactive(INF))
			_puts("$ ");
		_eputchar(BUF_FLUSH);
		r = get_input(INF);
		if (r != -1)
		{
			set_info(INF, av);
			BuiltIN_ret = find_BuiltIN(INF);
			if (BuiltIN_ret == -1)
				find_cmd(INF);
		}
		else if (INTERactive(INF))
			_putchar('\n');
		free_info(INF, 0);
	}
	write_Histry(INF);
	free_info(INF, 1);
	if (!INTERactive(INF) && INF->status)
		exit(INF->status);
	if (BuiltIN_ret == -2)
	{
		if (INF->err_Num == -1)
			exit(INF->status);
		exit(INF->err_Num);
	}
	return (BuiltIN_ret);
}
/**
 * find_BuiltIN - finds a BuiltIN command
 * @info: Parameter AND return info str.
 * Return: -1 if BuiltIN not FOUND
 *			0 if BuiltIN executed Success.
 *			1 if BuiltIN found but doesn't Success.
 *			-2 if BuiltIN signals exit().
 */
int find_BuiltIN(info_t *INF)
{
	int U, Built_IN_ret = -1;
	BuiltIN_table BuiltINtbl[] = {
		{"exit", _MYexit},
		{"env", _MYenv},
		{"help", _MYhelp},
		{"history", _MYhistory},
		{"setenv", _MYsetenV},
		{"unsetenv", _MYunsetenV},
		{"cd", _MYcd},
		{"alias", _MYalias},
		{NULL, NULL}
	};

	for (U = 0; BuiltINtbl[i].type; U++)
		if (_strcmp(INF->argv[0], BuiltINtbl[U].type) == 0)
		{
			INF->line_count++;
			Built_IN_ret = BuiltINtbl[U].func(INF);
			break;
		}
	return (Built_IN_ret);
}
/**
 * find_cmd - finds a command in PATH
 * @info: Parameter AND return info str
 * Return: Void
 */
void find_cmd(info_t *INF)
{
	char *path = NULL;
	int U, K;

	INF->path = INF->argv[0];
	if (INF->linecount_flag == 1)
	{
		INF->line_count++;
		INF->linecount_flag = 0;
	}
	for (U = 0, K = 0; INF->arg[U]; U++)
		if (!is_delim(info->arg[U], " \t\n"))
			K++;
	if (!K)
		return;

	path = find_path(INF, _GITenv(INF, "PATH="), INF->argv[0]);
	if (path)
	{
		INF->path = path;
		fork_cmd(INF);
	}
	else
	{
		if ((INTERactive(INF) || _GITenv(INF, "PATH=")
			|| INF->argv[0][0] == '/') && is_cmd(INF, INF->argv[0]))
			fork_cmd(INF);
		else if (*(INF->arg) != '\n')
		{
			INF->status = 127;
			print_error(INF, "not found\n");
		}
	}
}
/**
 * fork_cmd - forks a an exec thread to run cmd
 * @info: Parameter AND return info str.
 * Return: Void
 */
void fork_cmd(info_t *INF)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(INF->path, INF->argv, GET_Environ(INF)) == -1)
		{
			free_info(INF, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(INF->status));
		if (WIFEXITED(INF->status))
		{
			INF->status = WEXITSTATUS(INF->status);
			if (INF->status == 126)
				print_error(INF, "Permission denied\n");
		}
	}
}
