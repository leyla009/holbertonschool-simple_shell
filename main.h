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

#define BUF_SIZE 1024

/* --- Global Variable Handlers --- */
extern char **environ;
extern char *env_memory_to_free;
extern char **env_array_to_free; /* Tracker for the 232-byte array */

/* --- Built-in Command Logic --- */
int shell_cd(char **argv);
void handle_exit(char **argv, char *line, int status);
void print_env(void);

/* --- Environment & Path Utilities --- */
char *_getenv(const char *name);
int _setenv(const char *name, const char *value);
int _unsetenv(const char *name);
char *find_path(char *command);

/* --- Core Execution Engine --- */
ssize_t _getline(char **lineptr, size_t *n, FILE *stream);
int execute_command(char *path, char **argv);
void check_ctrlc(int signo);

/* --- Memory Management --- */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
void free_argv(char **argv);
void cleanup_all(char *line, char **argv);

/* --- String & Input/Output Utilities --- */
int _strlen(const char *s);
int _strcmp(const char *s1, const char *s2);
int _strncmp(const char *s1, const char *s2, size_t n);
char *_strdup(const char *src);
char *_strchr(const char *s, char c);
char *_strcpy(char *dest, const char *src);
char *_strcat(char *dest, const char *src);
char *_strtok(char *str, const char *delim);
int _atoi(char *s);
int _putchar(char c);
void _puts(char *str);

/* --- UI/UX Helpers  --- */
char *get_username(void);
char *get_current_directory(void);

#endif /* MAIN_H */
