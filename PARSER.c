#include "shell.h"
/**
 * is_CMD - Determines if a file IS AN  Executable Command
 * @info: THE info str
 * @Path: Path to THE file
 * Return: Success
 */
int is_CMD(info_t INF char *Path)
{
	struct stat st;

	(void)INF;
	if (!Path || stat(Path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * DUP_chars - DUPlicates caracters
 * @PatHstr: THE PATH String
 * @strt: Starting index
 * @stp: Stopping index
 * Return: Success
 */
char *DUP_chars(char *PatHstr, int strt, int stp)
{
	static char BUFF[1024];
	int U = 0, k = 0;

	for (k = 0, U = strt; U < stp; U++)
		if (PatHstr[U] != ':')
			buf[k++] = pathstr[U];
	buf[k] = 0;
	return (BUFF);
}
/**
 * Find_Path - Find this CMD in the PATH String
 * @info: THE info str
 * @PatHstr:THE PATH string
 * @CMD: the CMD to find
 * Return: Success
 */
char *Find_Path(info_t *INF, char *PatHstr, char *CMD)
{
	int U = 0, curr_pos = 0;
	char *Path;

	if (!PatHstr)
		return (NULL);
	if ((_strlen(CMD) > 2) && starts_with(CMD, "./"))
	{
		if (is_CMD(INF, CMD))
			return (CMD);
	}
	while (1)
	{
		if (!PatHstr[U] || PatHstr[U] == ':')
		{
			Path = dup_chars(PatHstr, curr_pos, U);
			if (!*Path)
				_strcat(Path, CMD);
			else
			{
				_strcat(Path, "/");
				_strcat(Path, CMD);
			}
			if (is_CMD(INF, Path))
				return (Path);
			if (!Pathstr[U])
				break;
			curr_pos = U;
		}
	U++;
	}
	return (NULL);
}
