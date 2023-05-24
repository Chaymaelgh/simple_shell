#include "shell.h"

/**
 * Input_BUF - buffers chained commands
 * @INF: Parameter str
 * @BUF: address of Buffer
 * @Len: address of len var
 * Return: Success
 */
size_t Input_buf(INF_t *INF, char **BUFF, size_t *Len)
{
	size_t r = 0;
	size_t Len_p = 0;

	if (!*Len) /* If NOthing left in the BUffer, fill it */
	{
		/*bfree((void **)INF->cmd_BUFF);*/
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
				(*BUFF)[r - 1] = '\0'; /* Remove trailing NEWline */
				r--;
			}
			INF->linecount_flag = 1;
			Remove_comments(*BUFF);
			build_history_list(INF, *BUFF, INF->histcount++);
			/* if (_strchr(*buf, ';')) is THIS a Command Chain? */
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
size_t GET_Input(INF_t *INF)
{
	static char *BUFF; /* THE ';' Command Chain BUFfer */
	static size_t U, j, Len;
	ssize_t r = 0;
	char **BUFF_p = &(INF->arg), *p0;

	_putchar(BUF_FLUSH);
	r = input_buf(INF, &BUFF, &Len);
	if (r == -1) /* EOF */
		return (-1);
	if (Len)	/* We have commands left in chain BUFFER */
	{
		j = i; /* init NEW Iterator to current BUF Position */
		p = buf + i; /* GET Pointer for Return */

		Check_chain(INF, BUFF, &j, U, Len);
		while (j < Len) /* Iterate to semicolon or end */
		{
			if (is_chain(INF, BUFF, &j))
				break;
			j++;
		}

		U = j + 1; /* Increment Past Nulled ';'' */
		if (U >= Len) /* REAched end of BUFFer? */
		{
			U = Len = 0; /* reset position and length */
			INF->cmd_buf_type = CMD_NORM;
		}

		*buf_p = p; /* Pass back Pointer to Current command position */
		return (_strlen(p)); /* REturn length of CURrent COMMAND */
	}

	*buf_p = BUFF; /* else not chain, Pass Back BUFfer From _GETline() */
	return (r); /* Return Length of buffer from _GETline() */
}
/**
 * Read_buf - reads a BUFfer
 * @INF: Parameter str
 * @BUFF: buffer
 * @U: size
 * Return: r
 */
size_t Read_buf(INF_t *INF, char *BUFF, size_t *U)
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
int _GETline(INF_t *INF, char **PTr, size_t *length)
{
	static char BUFF[READ_BUF_SIZE];
	static size_t U, Len;
	size_t k;
	size_t r = 0, s = 0;
	char *p0 = NULL, *new_p = NULL, *B;
	p = *PTr;
	if (p && length)
		s = *length;
	if ( U == len)
		U = Len = 0;
	r = read_buf(INF, BUFF, &Len);
	if (r == -1 || (r == 0 && Len == 0))
		return (-1);

	c = _strchr(buf + i, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = _realloc(p, s, s ? s + k : k + 1);
	if (!new_p) /* MALLOC FAILURE! */
		return (p ? free(p), -1 : -1);

	if (s)
		_strncat(new_p, buf + U, k - i);
	else
		_strncpy(new_p, buf + i, k - U + 1);

	s += k - U;
	U = k;
	p = new_p;

	if (length)
		*length = s;
	*PTr = p;
	return (s);
}

/**
 * SIGintHandler - blocks ctrl-C
 * @SIG_num: the signal number
 * Return: void
 */
void SIGintHandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
