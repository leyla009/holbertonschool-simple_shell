#include "main.h"

/**
 * _getline - reads an entire line from a stream
 * @lineptr: pointer to the buffer containing the text
 * @n: pointer to the size of the buffer
 * @stream: the input stream (unused, we use stdin)
 *
 * Return: number of characters read, or -1 on failure
 */
ssize_t _getline(char **lineptr, size_t *n, FILE *stream)
{
	static char buffer[1024];
	static size_t pos = 0;
	static size_t n_chars = 0;
	size_t i = 0;
	int c;
	char *new_ptr;

	(void)stream; 

	if (lineptr == NULL || n == NULL)
		return (-1);

	if (*lineptr == NULL || *n == 0)
	{
		*n = 128;
		*lineptr = malloc(*n);
		if (*lineptr == NULL)
			return (-1);
	}

	while (1)
	{
		if (pos >= n_chars)
		{
			n_chars = read(0, buffer, 1024);
			pos = 0;
			
			if (n_chars <= 0)
			{
				if (i == 0)
					return (-1);
				break;
			}
		}

		c = buffer[pos++];

		if (i >= *n - 1)
		{
			new_ptr = _realloc(*lineptr, *n, *n + 128);
			if (new_ptr == NULL)
				return (-1);
			*lineptr = new_ptr;
			*n += 128;
		}

		(*lineptr)[i++] = (char)c;

		if (c == '\n')
			break;
	}

	(*lineptr)[i] = '\0';
	return (i);
}
