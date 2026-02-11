#include "main.h"

/**
 * main - Entry point for the simple shell.
 *
 * Return: Always 0.
 */
int main(void)
{
    char *line = NULL;
    size_t len = 0;
    ssize_t nread;

    while (1)
    {
        if (isatty(STDIN_FILENO))
            printf("($) ");

        nread = getline(&line, &len, stdin);
        if (nread == -1) /* Handle EOF (Ctrl+D) */
        {
            if (isatty(STDIN_FILENO))
                printf("\n");
            free(line);
            break;
        }

        /* Logic to remove newline and call executor will go here */
        
    }
    return (0);
}
