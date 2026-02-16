#include "main.h"
#include <unistd.h>

/**
 * _putchar - writes the character c to stdout
 * @c: The character to print
 * Return: On success 1, on error -1
 */
int _putchar(char c)
{
    return (write(1, &c, 1));
}

/**
 * _puts - prints a string followed by a new line to stdout
 * @str: The string to print
 */
void _puts(char *str)
{
    int i = 0;

    if (!str)
        return;

    while (str[i])
    {
        _putchar(str[i]);
        i++;
    }
}

/**
 * _strlen - returns the length of a string
 * @s: string to check
 * Return: length of the string
 */
int _strlen(const char *s)
{
	int len = 0;

	if (!s)
		return (0);

	while (s[len])
		len++;
	return (len);
}

/**
 * _strcmp - compares two strings
 * @s1: first string
 * @s2: second string
 * Return: difference between strings
 */
int _strcmp(const char *s1, const char *s2)
{
	while (*s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}

/**
 * _strncmp - compares two strings up to n bytes
 * @s1: first string
 * @s2: second string
 * @n: number of characters to compare
 * Return: 0 if match, difference if not
 */
int _strncmp(const char *s1, const char *s2, size_t n)
{
	size_t i;

	for (i = 0; i < n && s1[i] && s2[i]; i++)
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
	}
	if (i == n)
		return (0);
	return (s1[i] - s2[i]);
}

/**
 * _strdup - duplicates a string in heap memory
 * @src: string to duplicate
 * Return: pointer to the new string
 */
char *_strdup(const char *src)
{
	char *dst;
	int i, len;

	if (src == NULL)
		return (NULL);

	len = _strlen(src);
	dst = malloc(sizeof(char) * (len + 1));
	if (dst == NULL)
		return (NULL);

	for (i = 0; i <= len; i++)
		dst[i] = src[i];

	return (dst);
}

/**
 * _strchr - locates a character in a string
 * @s: string to search
 * @c: character to find
 * Return: pointer to first occurrence or NULL
 */
char *_strchr(const char *s, char c)
{
	while (*s)
	{
		if (*s == c)
			return ((char *)s);
		s++;
	}
	if (*s == c)
		return ((char *)s);
	return (NULL);
}

/**
 * _strcat - concatenates two strings
 * @dest: destination string
 * @src: source string
 * Return: pointer to destination string
 */
char *_strcat(char *dest, const char *src)
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

/**
 * _strcpy - copies a string from src to dest
 * @dest: destination
 * @src: source
 * Return: pointer to dest
 */
char *_strcpy(char *dest, const char *src)
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
 * _strtok - breaks a string into a sequence of zero or more nonempty tokens
 * @str: the string to be parsed
 * @delim: the characters that separate tokens
 *
 * Return: a pointer to the next token, or NULL if there are no more tokens
 */
char *_strtok(char *str, const char *delim)
{
	static char *next_token;
	char *token_start;

	/* If a new string is provided, start from the beginning */
	if (str != NULL)
		next_token = str;

	/* If we've reached the end of the string, return NULL */
	if (next_token == NULL || *next_token == '\0')
		return (NULL);

	/* Skip leading delimiters */
	while (*next_token != '\0' && _strchr(delim, *next_token) != NULL)
		next_token++;

	/* If after skipping delimiters we are at the end, return NULL */
	if (*next_token == '\0')
		return (NULL);

	token_start = next_token;

	/* Find the end of the current token */
	while (*next_token != '\0' && _strchr(delim, *next_token) == NULL)
		next_token++;

	/* If we found a delimiter, null-terminate the token and move past it */
	if (*next_token != '\0')
	{
		*next_token = '\0';
		next_token++;
	}
	else
	{
		/* We hit the end of the string, ensure next call returns NULL */
		next_token = NULL;
	}

	return (token_start);
}

/**
 * _atoi - converts a string to an integer
 * @s: string to convert
 * Return: integer value
 */
int _atoi(char *s)
{
	int i = 0;
	unsigned int res = 0;

	if (!s)
		return (0);
	while (s[i])
	{
		if (s[i] >= '0' && s[i] <= '9')
			res = res * 10 + (s[i] - '0');
		else
			return (-1);
		i++;
	}
	return ((int)res);
}
