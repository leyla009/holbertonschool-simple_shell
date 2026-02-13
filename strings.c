#include "main.h"

/**
 * _strcmp - compares two strings
 * @s1: string 1
 * @s2: string 2
 * Return: difference
 */
int _strcmp(char *s1, char *s2)
{
	while (*s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}

/**
 * _strdup - duplicates a string
 * @src: source string
 * Return: pointer to new string
 */
char *_strdup(char *src)
{
	char *dst;
	int i, len = 0;

	if (src == NULL)
		return (NULL);
	while (src[len])
		len++;
	dst = malloc(sizeof(char) * (len + 1));
	if (dst == NULL)
		return (NULL);
	for (i = 0; i <= len; i++)
		dst[i] = src[i];
	return (dst);
}
