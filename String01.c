#include "shell.h"
/**
 * _strcpy - copie a string
 * @DEST: Destination
 * @src: Source.
 * Return: pointer to DEST
 */
char *_strcpy(char *DEST, char *src)
{
	int U = 0;

	if (DEST == src || src == 0)
		return (DEST);
	while (src[U])
	{
		DEST[U] = src[U];
		U++;
	}
	DEST[U] = 0;
	return (DEST);
}
/**
 * _strdup - Duplicate an String
 * @str: String to Duplicate.
 * Return: to pointer for Duplicate a string
 */
char *_strdup(const char *str)
{
	int length = 0;
	char *ret;

	if (str == NULL)
		return (NULL);
	while (*str++)
		length++;
	ret = malloc(sizeof(char) * (length + 1));
	if (!ret)
		return (NULL);
	for (length++; length--;)
		ret[length] = *--str;
	return (ret);
}
/**
 *_puts - Print a input string.
 *@str: String to printe.
 * Return: nothing.
 */
void _puts(char *str)
{
	int U = 0;

	if (!str)
		return;
	while (str[U] != '\0')
	{
		_putchar(str[U]);
		U++;
	}
}
/**
 * _putchar - write the character B to stdout
 * @B: character to print
 * Return: On Success 1.
 */
int _putchar(char B)
{
	static int U;
	static char buff[WRITE_BUF_SIZE];

	if (B == BUF_FLUSH || U >= WRITE_BUF_SIZE)
	{
		write(1, buff, U);
		U = 0;
	}
	if (B != BUF_FLUSH)
		buff[U++] = B;
	return (1);
}
