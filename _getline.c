#define BUF_SIZE 1024

/**
 * _getline - reads an entire line from stream
 * @lineptr: buffer that stores the line
 * @n: size of lineptr
 * @stream: stream to read from
 *
 * Return: the number of characters read
 */
ssize_t _getline(char **lineptr, size_t *n, FILE *stream)
{
    static char buffer[BUF_SIZE];
    static size_t pos = 0;
    static size_t n_chars = 0;
    size_t i = 0;
    int c;

    if (lineptr == NULL || n == NULL)
        return (-1);

    /* Allocate initial memory if lineptr is empty */
    if (*lineptr == NULL || *n == 0)
    {
        *n = BUF_SIZE;
        *lineptr = malloc(*n);
        if (*lineptr == NULL)
            return (-1);
    }

    while (1)
    {
        /* If buffer is empty, read more from the file descriptor */
        if (pos >= n_chars)
        {
            n_chars = read(fileno(stream), buffer, BUF_SIZE);
            pos = 0;
            if (n_chars <= 0) /* EOF or Error */
                return (-1);
        }

        c = buffer[pos++];
        
        /* If we run out of space in lineptr, reallocate */
        if (i >= *n - 1)
        {
            *n += BUF_SIZE;
            *lineptr = realloc(*lineptr, *n);
            if (*lineptr == NULL)
                return (-1);
        }

        (*lineptr)[i++] = c;
        if (c == '\n')
            break;
    }

    (*lineptr)[i] = '\0';
    return (i);
}
