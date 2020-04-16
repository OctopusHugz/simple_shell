#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>

typedef void (*sighandler_t)(int);

extern char **environ;

char *_getenv(char *name);

char *find_right_path(char *command);

char *make_av(char *av[], char *str);

void print_env(char *envp[]);

int _strncmp(char *s1, char *s2, int n);

char *_strncpy(char *dest, char *src, int n);

char *_strcat(char *dest, char *src);

size_t _strlen(char *s);

int _putchar(char c);

void _puts(char *str);

void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);

void sigint_handler(int signo);

int fork_exec(char *buf, char *path, char *av[4096], char *envp[]);

int built_in_check(char *buf, char *path, char *av[4096], char *argv[],
				   char *envp[], int status, int line_num);

void print_number(int n);

int print_error(char *path, char *argv[], int line_num, char *av[]);

char *access_check(char *path);

int slash_check(char *command);

int exit_parser(char *e_status);

#endif /* SHELL_H */
