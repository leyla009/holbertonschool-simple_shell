#include "main.h"

/**
 * main - Entry point for the simple shell
 *
 * Return: The last exit status
 */
void cleanup_all(char *line, char **argv);

int main(void)
{
    char *line = NULL, *token, *full_path = NULL;
    size_t len = 0;
    ssize_t nread;
    char **argv;
    int i, j, status = 0;

    while (1)
    {
        if (isatty(STDIN_FILENO))
            printf(":) ");

        nread = _getline(&line, &len, stdin);
        if (nread == -1)
        {
            if (isatty(STDIN_FILENO))
                printf("\n");
            break;
        }
        if (line[nread - 1] == '\n')
            line[nread - 1] = '\0';

	argv = malloc(sizeof(char *) * 32);
        /* Tokenization */
        i = 0;
        token = _strtok(line, " ");
        while (token != NULL && i < 31)
        {
            argv[i++] = token;
            token = _strtok(NULL, " ");
        }
        argv[i] = NULL;

        if (argv[0] == NULL)
	{
		free(argv);
		continue;
	}

        /* 1. Builtin: Exit */
        if (_strcmp(argv[0], "exit") == 0)
		{
			int exit_code = status;
			
			if (argv[1] != NULL)
			{
				for (j = 0; argv[1][j]; j++)
				{
					if (argv[1][j] < '0' || argv[1][j] > '9')
					{
						fprintf(stderr, "./hsh: 1: exit: Illegal number: %s\n", argv[1]);
						exit_code = 2;
						break;
					}
				}
        		if (exit_code != 2)
				exit_code = _atoi(argv[1]);
			}
			
			cleanup_all(line, argv);

			exit(exit_code);
		}	

        /* 2. Builtin: Env */
        if (_strcmp(argv[0], "env") == 0)
        {
            for (j = 0; environ[j]; j++)
            {
                _puts(environ[j]);
                _putchar('\n');
	    }
            status = 0;
            continue;
        }

        /* 3. Builtin: Setenv */
        if (_strcmp(argv[0], "setenv") == 0)
        {
            if (argv[1] && argv[2])
            {
                if (_setenv(argv[1], argv[2]) == -1)
                    fprintf(stderr, "setenv: Error occurred\n");
                else
                    status = 0;
            }
            else
            {
                fprintf(stderr, "setenv: usage: setenv VAR VALUE\n");
                status = 1;
            }
	    free_argv(argv);
            continue;
        }

        /* 4. Builtin: Unsetenv */
        if (_strcmp(argv[0], "unsetenv") == 0)
        {
            if (argv[1])
                status = _unsetenv(argv[1]);
            else
            {
                fprintf(stderr, "unsetenv: Too few arguments\n");
                status = 1;
            }
            continue;
        }

        /* 5. Execution Logic  */
        full_path = find_path(argv[0]);
        if (full_path != NULL)
        {
            status = execute_command(full_path, argv);
            if (full_path != argv[0])
	    {
		    free(full_path);
	    }
        }
        else
        {
            fprintf(stderr, "./hsh: 1: %s: not found\n", argv[0]);
            status = 127;
        }
	free_argv(argv);
    }
    free(line);
    
    if (argv != NULL)
	    free_argv(argv);

    if (env_memory_to_free)
	    free(env_memory_to_free);

    return (status);
}
void cleanup_all(char *line, char **argv)
{
    extern char *env_memory_to_free;

    if (argv)
        free(argv);
    if (line)
        free(line);
    if (env_memory_to_free)
        free(env_memory_to_free);
}
