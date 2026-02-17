/**
 * shell_cd - Changes the current working directory.
 * @argv: Array of arguments (argv[0] is "cd").
 * Return: 0 on success.
 */
int shell_cd(char **argv)
{
    char *target = NULL, cwd[1024];
    char *h_val = _getenv("HOME"), *o_val = _getenv("OLDPWD");
    int ret;


    if (getcwd(cwd, sizeof(cwd)) == NULL)
        return (1);

    if (!argv[1] || _strcmp(argv[1], "$HOME") == 0)
    {
        target = h_val;
    }
    else if (_strcmp(argv[1], "-") == 0)
    {
        target = o_val;
        if (target)
        {
            _puts(target);
            _putchar('\n');
        }
    }
    else
    {
        target = argv[1];
    }

    if (!target)
        target = cwd;

    ret = chdir(target);
    if (ret == 0)
    {
        _setenv("OLDPWD", cwd);
        if (getcwd(cwd, sizeof(cwd)))
            _setenv("PWD", cwd);
    }
    else
    {

        fprintf(stderr, "./hsh: 1: cd: can't cd to %s\n", argv[1]);
    }


    free(h_val);
    free(o_val);

    return (0);
}
