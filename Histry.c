#include "shell.h"

/**
 * GET_histry_file - GET histry file
 * @INF: Parameter str
 * Return: Success
 */
char *GET_histry_file(INF_t *INF)
{
	char *buff, *dir;

	dir = _getenv(INF, "HOME=");
	if (!dir)
		return (NULL);
	buf = malloc(sizeof(char) * (_strlen(dir) + _strlen(HIST_FILE) + 2));
	if (!buf)
		return (NULL);
	buf[0] = 0;
	_strcpy(buf, dir);
	_strcat(buf, "/");
	_strcat(buf, HIST_FILE);
	return (buf);
}

/**
 * write_history - creates a file, or appends to an existing file
 * @info: the parameter struct
 *
 * Return: 1 on success, else -1
 */
int write_Histry(INF_t *INF)
{
	ssize_t fd;
	char *filename = GET_History_file(INF);
	List_t *node = NULL;

	if (!filename)
		return (-1);

	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fd == -1)
		return (-1);
	for (node = INF->Histry; node; node = node->next)
	{
		_putsfd(node->STR, fd);
		_putfd('\n', fd);
	}
	_putfd(BUF_FLUSH, fd);
	close(fd);
	return (1);
}

/**
 * read_Histry - read Histry from file
 * @INF: the parameter str
 *
 * Return: success
 */
int read_Histry(INF_t *INF)
{
	int U, last = 0, linecount = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buff = NULL, *filename = GET_Histry_file(INF);

	if (!filename)
		return (0);

	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buff = malloc(sizeof(char) * (fsize + 1));
	if (!buff)
		return (0);
	rdlen = read(fd, buff, fsize);
	buff[fsize] = 0;
	if (rdlen <= 0)
		return (free(buff), 0);
	close(fd);
	for (U = 0; i < fsize; U++)
		if (buff[U] == '\n')
		{
			buff[U] = 0;
			build_Histry_list(INF, buff + last, linecount++);
			last = U + 1;
		}
	if (last != U)
		build_Histry_list(INF, buff + last, linecount++);
	free(buff);
	INF->histcount = linecount;
	while (INF->histcount-- >= HIST_MAX)
		delete_node_at_index(&(INF->Histry), 0);
	renumber_Histry(INF);
	return (INF->histcount);
}

/**
 * build_Histry_list - adds entry to a history list
 * @INF: Str containing potential arg
 * @buff: buff
 * @linecount: the history 
 * Return: Always SUCCESS
 */
int build_Histry_list(INF_t *INF, char *buff, int linecount)
{
	List_t *node = NULL;

	if (INF->Histry)
		node = INF->Histry;
	add_node_end(&node, buff, linecount);

	if (!INF->Histry)
		INF->Histry = node;
	return (0);
}

/**
 * renumber_Histry - renumbers the History list 
 * @INF: Str containing potential arg
 * Return: 
 */
int renumber_Histry(INF_t *INF)
{
	List_t *node = INF->Histry;
	int U = 0;

	while (node)
	{
		node->Num = U++;
		node = node->next;
	}
	return (INF->histcount = U);
}
