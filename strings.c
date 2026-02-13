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

/**
 * _strcpy - copies a string
 * @dest: destination
 * @src: source
 * Return: pointer to dest
 */
char *_strcpy(char *dest, char *src)
{
	int i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

/**
 * _strcat - concatenates two strings
 * @dest: destination
 * @src: source
 * Return: pointer to dest
 */
char *_strcat(char *dest, char *src)
{
	int i = 0, j = 0;
	while (dest[i])
		i++;
	while (src[j])
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	dest[i] = '\0';
	return (dest);
}
