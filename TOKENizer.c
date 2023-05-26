#include "shell.h"

/**
 * **strtow - Split a String into words
 * @str: input String
 * @D:  delimeter String
 * Return: pointer to an array of Strings.
 */
char **strtow(char *str, char *D)
{
	int U, j, K, m, numwords = 0;
	char **S;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!D)
		D = " ";
	for (U = 0; str[U] != '\0'; U++)
		if (!is_delim(str[U], D) && (is_delim(str[U + 1], D) || !str[U + 1]))
			numwords++;

	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if (!S)
		return (NULL);
	for (U = 0, j = 0; j < numwords; j++)
	{
		while (is_delim(str[U], D))
			U++;
		K = 0;
		while (!is_delim(str[U + K], d) && str[U + K])
			K++;
		S[j] = malloc((K + 1) * sizeof(char));
		if (!S[j])
		{
			for (K = 0; K < j; K++)
				free(S[K]);
			free(S);
			return (NULL);
		}
		for (m = 0; m < K; m++)
			S[j][m] = str[U++];
		S[j][m] = 0;
	}
	S[j] = NULL;
	return (S);
}
/**
 * **strtow2 - splits a string
 * @str: input
 * @d: Delimeter
 * Return: pointer to an array of strings
 */
char **strtow2(char *str, char D)
{
	int U, j, K, m, numwords = 0;
	char **S;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (U = 0; str[U] != '\0'; U++)
		if ((str[U] != D && str[U + 1] == D) ||
		    (str[U] != D && !str[U + 1]) || str[U + 1] == D)
			numwords++;
	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if (!S)
		return (NULL);
	for (U = 0, j = 0; j < numwords; j++)
	{
		while (str[U] == D && str[U] != D)
			U++;
		K = 0;
		while (str[U + K] != D && str[U + K] && str[U + K] != D)
			K++;
		S[j] = malloc((K + 1) * sizeof(char));
		if (!S[j])
		{
			for (K = 0; K < j; K++)
				free(S[k]);
			free(S);
			return (NULL);
		}
		for (m = 0; m < K; m++)
			S[j][m] = str[U++];
		S[j][m] = 0;
	}
	S[j] = NULL;
	return (S);
}
