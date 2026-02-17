#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 
#include "main.h"

extern char **environ;

/**
 * shell_cd - Changes the current working directory.
 * @argv: Array of arguments (argv[0] is "cd").
 * Return: 0 on success.
 */
int shell_cd(char **argv)
{
    char *target = NULL, cwd[1024], *target_copy = NULL;
    /* İbirincini alir */
    char *h_val = _getenv("HOME"), *o_val = _getenv("OLDPWD"), *p_val = _getenv("PWD");

    /* 1. HOME yoxlamasi */
    if (!argv[1] || _strcmp(argv[1], "$HOME") == 0)
        target = h_val;
    /* 2. CD DASH yoxlamasiı (cd -) */
    else if (_strcmp(argv[1], "-") == 0)
    {
        target = o_val ? o_val : p_val;
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
            if (chdir(target_copy) == 0)
            {
                _setenv("OLDPWD", cwd);
                if (getcwd(cwd, sizeof(cwd)))
                    _setenv("PWD", cwd);
            }
            else
            {

                fprintf(stderr, "./hsh: 1: cd: can't cd to %s\n", target);
            }
        }
        free(target_copy);
    }

    /*yaddasi musteqil etme */

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
