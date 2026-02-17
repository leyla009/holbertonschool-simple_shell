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

    char *s_home = _getenv("HOME") ? _strdup(_getenv("HOME")) : NULL;
    char *s_old = _getenv("OLDPWD") ? _strdup(_getenv("OLDPWD")) : NULL;
    char *s_pwd = _getenv("PWD") ? _strdup(_getenv("PWD")) : NULL;

    if (!argv[1])
        target = s_home;
    else if (_strcmp(argv[1], "-") == 0)
    {
        target = s_old ? s_old : s_pwd;
        if (target)
        {
            _puts(target);
            _putchar('\n');
        }
    }
    else
        target = argv[1];

    if (target)
    {
        target_copy = _strdup(target);
        if (target_copy && getcwd(cwd, sizeof(cwd)))
        {
            if (chdir(target_copy) != 0)
                fprintf(stderr, "./hsh: 1: cd: can't cd to %s\n", target_copy);
            else
            {
                _setenv("OLDPWD", cwd);
                if (getcwd(cwd, sizeof(cwd)))
                    _setenv("PWD", cwd);
            }
        }
    }

    free(s_home);
    free(s_old);
    free(s_pwd);
    free(target_copy);
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
