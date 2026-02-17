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

    char *h_raw = _getenv("HOME");
    char *o_raw = _getenv("OLDPWD");
    char *p_raw = _getenv("PWD");

    char *home = h_raw ? _strdup(h_raw) : NULL;
    char *oldpwd = o_raw ? _strdup(o_raw) : NULL;
    char *pwd = p_raw ? _strdup(p_raw) : NULL;

    if (!argv[1])
        target = home;
    else if (_strcmp(argv[1], "-") == 0)
    {
        target = oldpwd ? oldpwd : pwd;
        if (target)
        {
            _puts(target);
            _putchar('\n');
        }
    }
    else
        target = argv[1];

    if (target && (target_copy = _strdup(target)))
    {
        if (getcwd(cwd, sizeof(cwd)) != NULL)
        {
            if (chdir(target_copy) != 0)
                fprintf(stderr, "./hsh: 1: cd: can't cd to %s\n", target_copy);
            else
            {
                _setenv("OLDPWD", cwd);
                if (getcwd(cwd, sizeof(cwd)) != NULL)
                    _setenv("PWD", cwd);
            }
        }
        free(target_copy);
    }

    free(home);
    free(oldpwd);
    free(pwd);
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
