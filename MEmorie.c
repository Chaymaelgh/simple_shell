#include "shell.h"

/**
 * BFree - Frees a pointer and NULLs the address
 * @PTr: address OF THE POINTERS to free
 * Return: Success
 */

int BFree(void **PTr)
{
	if (PTr && *PTr)
	{
		free(*PTr);
		*PTr = NULL;
		return (1);
	}
	return (0);
}
