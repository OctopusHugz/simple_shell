#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>

extern char **environ;

char *_getenv(char *name);

char *find_right_path(char *command);

char *make_av(char *av[], char *line);

void print_env(char *envp[]);

int _strncmp(char *s1, char *s2, int n);

char *_strncpy(char *dest, char *src, int n);

char *_strcat(char *dest, char *src);

size_t _strlen(char *s);

int _putchar(char c);

void _puts(char *str);

void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);

#endif /* SHELL_H */
