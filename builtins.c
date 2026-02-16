#include <stdio.h>
#include "main.h"

extern char **environ;

/**
 * shell_cd - Changes the current working directory.
 * @argv: Array of arguments (argv[0] is "cd").
 * Return: 0 on success, -1 on failure.
 */

int shell_cd(char **argv)
{
    char *target = NULL, cwd[1024];
    char *target_copy = NULL;
    char *home = _getenv("HOME");
    char *oldpwd = _getenv("OLDPWD");
    char *pwd = _getenv("PWD");

    if (!argv[1])
        target = home;
    else if (_strcmp(argv[1], "-") == 0)
    {
        target = oldpwd ? oldpwd : _getenv("PWD");
        if (target)
        {
            _puts(target);
            _putchar('\n');
        }
    }
    else
        target = argv[1];

    if (!target)
        return (0);

    target_copy = _strdup(target);
    if (!target_copy)
	    return (-1);

    if (getcwd(cwd, sizeof(cwd)) == NULL)
    {
	    free(target_copy);
	    return (-1);
    }
    
    if (chdir(target_copy) != 0)
    {
	    fprintf(stderr, "./hsh: 1: cd: can't cd to %s\n", target_copy);
	    free(target_copy);
	    return (-1);
    }

    _setenv("OLDPWD", cwd);
    if (getcwd(cwd, sizeof(cwd)) != NULL)
	    _setenv("PWD", cwd);

    free(target_copy);
    return (0);
}

/**
 * print_env - prints the environment
 */
void print_env(void)
{
    int i = 0;

    while (environ[i])
    {
        _puts(environ[i]);
        _putchar('\n');
        i++;
    }
}
