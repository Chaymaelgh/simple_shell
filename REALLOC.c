#include "shell.h"
/**
 **_memSET - fills Memory with a constant byte
 *@g: THE Pointer to the memory area
 *@e: THE byte to fill *s with
 *@m: THE amount of bytes to be filled
 *Return: Success
 */
char *_memSET(char *g, char e, unsigned int n)
{
	unsigned int U;

	for (U = 0; U < n; U++)
		g[U] = e;
	return (g);
}
/**
 * FFree - Frees a String of strings
 * @kk: string of strings
 */
void FFree(char **kk)
{
	char **a = kk;

	if (!kk)
		return;
	while (*kk)
		free(*kk++);
	free(a);
}

/**
 * _REAlloc - REAllocates a block of Memory
 * @PTR: Pointer to PREVIOUS malloc'ated Block
 * @OLD_size: Byte size of Previous block
 * @New_size: Byte size of New block
 * Return: Success
 */
void *_REAlloc(void *PTR, unsigned int OLD_size, unsigned int new_size)
{
	char *P0;

	if (!PTR)
		return (malloc(new_size));
	if (!new_size)
		return (free(PTR), NULL);
	if (New_size == OLD_size)
		return (PTR);

	P0 = malloc(New_size);
	if (!P0)
		return (NULL);

	OLD_size = OLD_size < New_size ? OLD_size : New_size;
	while (Old_size--)
		P0[OLD_size] = ((char *)PTR)[OLD_size];
	free(PTR);
	return (P0);
}
