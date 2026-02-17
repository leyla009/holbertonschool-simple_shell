#include <stdio.h>
#include "main.h"

extern char **environ;

/**
 * shell_cd - Changes the current working directory.
 * @argv: Array of arguments (argv[0] is "cd").
 * 
 * Return: 0 on success, -1 on failure.
 */

int shell_cd(char **argv)
{
    char *target = NULL, cwd[1024], *target_copy = NULL;
    char *old_val = _getenv("OLDPWD");
    char *s_old = old_val ? _strdup(old_val) : NULL;
    char *s_home = _getenv("HOME") ? _strdup(_getenv("HOME")) : NULL;

    if (!argv[1])
        target = s_home;
    else if (_strcmp(argv[1], "-") == 0)
        target = s_old;
    else
        target = argv[1];

    if (!target) {
        free(s_old); free(s_home);
        return (0);
    }

    target_copy = _strdup(target);
    if (getcwd(cwd, sizeof(cwd)) && target_copy)
    {
        if (chdir(target_copy) == 0)
        {
            _setenv("OLDPWD", cwd); 
            if (getcwd(cwd, sizeof(cwd)))
                _setenv("PWD", cwd);
        }
        else
            fprintf(stderr, "./hsh: 1: cd: can't cd to %s\n", target_copy);
    }

    free(target_copy); free(s_old); free(s_home);
    return (0);
}


/**
 * print_env - prints the environment.
 *
 * Return: void.
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
