#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

/* Environment */
extern char **environ;

/* Function Prototypes */
ssize_t _getline(char **lineptr, size_t *n, FILE *stream);
int execute_command(char **argv);
char *find_path(char *command);
char *_getenv(const char *name);

#endif /* MAIN_H */
