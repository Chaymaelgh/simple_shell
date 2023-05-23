#include "shell.h"
/**
 * INTERactive - If shell was interactive Return true
 * @info: struct add
 * Return: Success
 */
int INTERactive(info_t *info)
{
	return (isatty(stdin_FILENO) && info->readfd <= 2);
}
/**
 * IS_delim - Character Check
 * @c: char
 * @delim: Delimeter
 * Return: Success
 */
int IS_delim(char B, char *delim)
{
	while (*delim)
		if (*delim++ == B)
			return (1);
	return (0);
}
/**
 *_ISalpha - Alphabetic Check
 *@c: input
 *Return: Success
 */
int _ISalpha(int B)
{
	if ((B >= 'a' && B <= 'z') || (B >= 'A' && B <= 'Z'))
		return (1);
	else
		return (0);
}
/**
 *_AtOi - CONVERT strng
 *@s: strng
 *Return: Success
 */
int _AtOi(char *S)
{
	int U, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (U = 0;  S[U] != '\0' && flag != 2; U++)
	{
		if (S[U] == '-')
			sign *= -1;
		if (S[U] >= '0' && S[U] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (S[U] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}
	if (sign == -1)
		output = -result;
	else
		output = result;
	return (output);
}
