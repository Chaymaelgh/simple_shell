#include "shell.h"
/**
 * Input_BUF - buffer chained command
 * @info: Parameter str
 * @BUFF: addrs of Buffer
 * @Len: address of len VAR
 * Return: Success
 */
size_t Input_buf(info_t *INF, char **BUFF, size_t *Len)
{
	size_t r = 0;
	size_t Len_p = 0;

	if (!*Len)
	{

		free(*BUFF);
		*BUFF = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETline
		r = GETline(BUFF, &Len_p, stdin);
#else
		r = _GETline(INF, BUFF, &Len_p);
#endif
		if (r > 0)
		{
			if ((*BUFF)[r - 1] == '\n')
			{
				(*BUFF)[r - 1] = '\0'; 
				r--;
			}
			INF->linecount_flag = 1;
			Remove_comments(*BUFF);
			build_history_list(INF, *BUFF, INF->histcount++);

			{
				*Len = r;
				INF->cmd_BUFF = BUFF;
			}
		}
	}
	return (r);
}

/**
 * GET_Input - gets a line minus THE NEWline
 * @INF: Parameter str
 * Return: Success
 */
size_t GET_Input(info_t *INF)
{
	static char *BUFF;
	static size_t U, j, Len;
	ssize_t r = 0;
	char **BUFF_p = &(INF->arg), *p0;

	_putchar(BUF_FLUSH);
	r = input_buf(INF, &BUFF, &Len);
	if (r == -1)
		return (-1);
	if (Len)
	{
		j = U;
		P0 = BUFF + U;

		Check_chain(INF, BUFF, &j, U, Len);
		while (j < Len)
		{
			if (is_chain(INF, BUFF, &j))
				break;
			j++;
		}

		U = j + 1;
		if (U >= Len)
		{
			U = Len = 0;
			INF->cmd_buf_type = CMD_NORM;
		}

		*buf_p = P0;
		return (_strlen(P0));
	}

	*buf_p = BUFF;
	return (r);
}
/**
 * Read_buff - reads a BUFfer
 * @INF: Parameter str
 * @BUFF: buffer
 * @U: size
 * Return: r
 */
size_t Read_buff(info_t *INF, char *BUFF, size_t *U)
{
	size_t r = 0;

	if (*U)
		return (0);
	r = read(INF->readfd, BUFF, READ_BUF_SIZE);
	if (r >= 0)
		*U = r;
	return (r);
}

/**
 * _GETline - GETS THE Next Line of Input from STDIN
 * @INF: Parameter str
 * @PTr: Address of pointer to buffer, preallocated or NULL
 * @Length: Size of Preallocated PTr buffer if not NULL
 * Return: Success
 */
int _GETline(info_t *INF, char **PTr, size_t *length)
{
	static char BUFF[READ_BUF_SIZE];
	static size_t U, Len;
	size_t k;
	size_t r = 0, s = 0;
	char *p0 = NULL, *new_p = NULL, *B;
	P0 = *PTr;
	if (P0 && length)
		s = *length;
	if ( U == len)
		U = Len = 0;
	r = read_buf(INF, BUFF, &Len);
	if (r == -1 || (r == 0 && Len == 0))
		return (-1);

	B = _strchr(BUFF + U, '\n');
	k = B ? 1 + (unsigned int)(B - BUFF) : len;
	new_p = _realloc(p, s, s ? s + k : k + 1);
	if (!new_P0)
		return (P0 ? free(P0), -1 : -1);

	if (s)
		_strncat(new_P0, BUFF + U, k - U);
	else
		_strncpy(new_P0, BUFF + U, k - U + 1);

	s += k - U;
	U = k;
	P0 = new_p;

	if (length)
		*length = s;
	*PTr = P0;
	return (s);
}

/**
 * SIGintHandler - blocks ctrl-C
 * @SIG_Num: the signal number
 * Return: void
 */
void SIGintHandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
