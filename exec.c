#include "main.h"

/**
 * execute_command - Forks a process and executes a command with arguments.
 * @path: The full path to the executable.
 * @argv: An array of strings (pointers) containing the command and arguments.
 *
 * Return: 0 on success, 1 if fork fails.
 */
int execute_command(char *path, char **argv)
{
    pid_t child_pid;
    int status;

    child_pid = fork();
    if (child_pid == -1)
    {
        perror("fork");
        return (1);
    }

    if (child_pid == 0)
    {
        /* Use 'path' for the file, but 'argv' for the arguments */
        if (execve(path, argv, environ) == -1)
        {
            perror("execve");
            exit(1);
        }
    }
    else
    {
        wait(&status);
        if (WIFEXITED(status))
            return (WEXITSTATUS(status));
        if (WIFSIGNALED(status))
            return (128 + WTERMSIG(status));
    }
    return (0);
}
