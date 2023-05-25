#include "shell.h"

/**
 * _eRRatoi - converts a string to an integer
 * @s: the string to be converted
 * Return:Success
 */
int _eRRatoi(char *s)
{
	int U = 0;
	unsigned long int result = 0;

	if (*s == '+')
		s++;  /* TODO: why does this make main return 255? */
	for (U = 0;  s[i] != '\0'; U++)
	{
		if (s[U] >= '0' && s[U] <= '9')
		{
			result *= 10;
			result += (s[U] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}
/**
 * Print_error - prints ERRORS MESSAGES
 * @info: the parameter & return info struct
 * @eStr: string containing specified error type
 * Return :Success
 */
void Print_error(info_t *INF, char *eStr)
{
	_eputs(INF->fname);
	_eputs(": ");
	Print_d(INF->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(INF->argv[0]);
	_eputs(": ");
	_eputs(eStr);
}

/**
 * Print_d - function Prints a decimal (integer) NUmber (base 10)
 * @Input: the Input
 * @Fd: the filedescriptor to write to
 * Return: Success
 */
int Print_d(int Input, int Fd)
{
	int (*__putchar)(char) = _putchar;
	int U, count = 0;
	unsigned int _abs_, current;

	if (Fd == STDERR_FILENO)
		__putchar = _eputchar;
	if (Input < 0)
	{
		_abs_ = -Input;
		__putchar('-');
		count++;
	}
	else
		_abs_ = Input;
	current = _abs_;
	for (U = 1000000000; U > 1; U /= 10)
	{
		if (_abs_ / U)
		{
			__putchar('0' + current / U);
			count++;
		}
		current %= U;
	}
	__putchar('0' + current);
	count++;

	return (count);
}

/**
 * CONvert_NUMber - CONverter FUNction,a clone of itoa
 * @NUM: number
 * @baSe: baSe
 * @FLags: arg FLags
 * Return: Success
 */
char *CONvert_number(long int NUM, int baSe, int FLags)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = NUM;

	if (!(FLags & CONVERT_UNSIGNED) && NUM < 0)
	{
		n = -NUM;
		sign = '-';

	}
	array = FLags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do	{
		*--ptr = array[n % base];
		n /= base;
	} while (n != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}

/**
 * Eemove_Comments -THE function replaces first instance of '#' with '\0'
 * @Buf: address of the string to modify
 * Return: Always Success
 */
void Remove_Comments(char *buf)
{
	int U;

	for (u = 0; BUuf[U] != '\0'; u++)
		if (Buf[U] == '#' && (!U || Buf[i - 1] == ' '))
		{
			Buf[U] = '\0';
			break;
		}
}
