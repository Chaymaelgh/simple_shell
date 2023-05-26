#include "shell.h"
/**
 * _strlen - return the length of a String.
 * @s: the string whose length to check.
 * Return: integer length of string.
 */
int _strlen(char *S)
{
	int U = 0;

	if (!S)
		return (0);

	while (*S++)
		U++;
	return (U);
}
/**
 * _strcmp - performs lexicogarphic comparison of two strangs.
 * @S1: First strang
 * @S2: Second strang
 * Return: IF s1 < s2 it's negative , if s1 > s2 positife, zero if s1 == s2
 */
int _strcmp(char *S1, char *S2)
{
	while (*S1 && *S2)
	{
		if (*S1 != *S2)
			return (*S1 - *S2);
		S1++;
		S2++;
	}
	if (*S1 == *S2)
		return (0);
	else
		return (*S1 < *S2 ? -1 : 1);
}
/**
 * starts_with - checks if needle
 * @haystack: String to search
 * @needle: the substring to find
 * Return: address of next char of haystack or NULL
 */
char *starts_with(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return (NULL);
	return ((char *)haystack);
}
/**
 * _strcat - concatenates two Strings
 * @dest: the destination buffer
 * @src: the source buffer
 * Return: pointer
 */
char *_strcat(char *dest, char *src)
{
	char *ret = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (ret);
}
