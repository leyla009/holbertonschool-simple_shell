#include "main.h"

extern char *env_memory_to_free;

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
	    argv = malloc(sizeof(char *) * 32);
	    
	    if (argv == NULL)
		    break;

	    if (isatty(STDIN_FILENO))
            printf(":) ");
	    
	    nread = _getline(&line, &len, stdin);
	    if (nread == -1)
	    {
		    if (isatty(STDIN_FILENO))
			    printf("\n");
		    
		    cleanup_all(line, argv);
		    return (status);
	    }

	    if (nread > 0 && line[nread - 1] == '\n')
		    line[nread - 1] = '\0';

	/* Tokenization */
        i = 0;
        token = _strtok(line, " \t\n\r");
        while (token != NULL && i < 31)
        {
            argv[i++] = token;
            token = _strtok(NULL, " \t\n\r");
        }
        argv[i] = NULL;

        if (argv[0] == NULL)
	{
		goto skip_execution;
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
						status = 2;
						goto skip_execution;
					}
				}
				exit_code = _atoi(argv[1]);
			}
			cleanup_all(line, argv);
			
			(void)exit_code;

			exit(exit_code);
		}
		
        /* 2. Builtin: Env */
        if (_strcmp(argv[0], "env") == 0)
        {
		print_env();
		status = 0;
		goto skip_execution;
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
	    goto skip_execution;
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
            goto skip_execution;
        }

	/* 5. Builtin: CD  */
	if (_strcmp(argv[0], "cd") == 0)
	{
		status = shell_cd(argv);
		goto skip_execution;
	}
        /* 6. Execution Logic (External Commands)  */
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

    skip_execution:
	free(argv);
    }
    
    return (status);
}
void cleanup_all(char *line, char **argv)
{
    extern char *env_memory_to_free;
    extern char **env_array_to_free;
    
    if (argv)
        free(argv);
    
    if (line)
        free(line);
    
    if (env_memory_to_free)
	    free(env_memory_to_free);

    if (env_array_to_free)
	    free(env_array_to_free);
}
