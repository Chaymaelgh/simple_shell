#include "shell.h"
/**
 *_Eputs - Prints Input String
 * @Str: string be Printed
 * Return: Success
 */
void _Eputs(char *Str)
{
	int U = 0;

	if (!Str)
		return;
	while (Str[U] != '\0')
	{
		_Eputchar(Str[U]);
		U++;
	}
}
/**
 * _Eputchar - writes character B to Stder
 * @B: character to print
 * Return: Success.
 * Error, -1 Is Returned
 */
int _Eputchar(char B)
{
	static int U;
	static char buff[WRITE_BUFF_SIZE];

	if (B == BUFF_FLUSH || U >= WRITE_BUFF_SIZE)
	{
		write(2, buff, U);
		U = 0;
	}
	if (B != BUFF_FLUSH)
		buff[U++] = B;
	return (1);
}
/**
 * _Putfd - Write Character B to give fd
 * @B: character
 * @fd: To write Filedescriptor.
 * Return: 1 Success
 */
int _Putfd(char B, int fd)
{
	static int U;
	static char buff[WRITE_BUFF_SIZE];

	if (B == BUFF_FLUSH || U >= WRITE_BUFF_SIZE)
	{
		write(fd, buff, U);
		U = 0;
	}
	if (B != BUFF_FLUSH)
		buff[U++] = B;
	return (1);
}
/**
 *_Putsfd - print a Input
 * @Str: string to be printe
 * @fd: to write filedescriptor.
 * Return: number of char
 */
int _Putsfd(char *Str, int fd)
{
	int U = 0;

	if (!Str)
		return (0);
	while (*Str)
	{
		U += _Putfd(*Str++, fd);
	}
	return (U);
}
