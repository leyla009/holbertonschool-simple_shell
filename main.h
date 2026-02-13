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

/* Custom String Functions */
int _strlen(char *s);
int _strcmp(char *s1, char *s2);
char *_strdup(char *src);
char *_strchr(char *s, char c);
char *_strcpy(char *dest, char *src);
char *_strcat(char *dest, char *src);
char *_strtok(char *str, const char *delim);

/* Function Prototypes */
ssize_t _getline(char **lineptr, size_t *n, FILE *stream);
int execute_command(char **argv);
char *find_path(char *command);


#endif /* MAIN_H */
