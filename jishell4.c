#ifndef GUARD
#define GUARD

/* Header files go here */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>

/* Prototypes go here */
char *_getenv(char *name);
char *find_right_path(char *command);
char *make_av(char *av[], char *line);
void print_env(char *envp[]);
#endif

int main(int argc, char *argv[], char *envp[])
{
	char *buf = NULL, *av[4096], *path;
	size_t size = 0;
	int status = 0, line_num = 0;
	pid_t child_pid = 0;

	if (argc != 1) /* Print usage if argc is off */
	{
		dprintf(STDERR_FILENO, "Usage: %s\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	/* av[0] = NULL; */
	while (1)
	{
		line_num++;
		if (isatty(STDIN_FILENO) == 1) /* Print $ if stdin is terminal */
			printf("$ ");
		if (getline(&buf, &size, stdin) == -1) /* Copy command line to buf */
		{
			free(buf);
			buf = NULL;
			break;
		}
		if (buf[0] == '\n') /* Start over if buf is just '\n' */
			continue;
		path = make_av(av, buf); /* Make argv[] for next exec */
		/* ADD FUNCTION HERE TO CHECK IF BUILTIN EXIT, ENV, SETENV, OR UNSETENV */
		if (strcmp(buf, "exit") == 0)
		{
			if (av[1])
				status = atoi(av[1]);
			free(buf);
			buf = NULL;
			exit(status);
		}
		if (strcmp(buf, "env") == 0)
		{
			print_env(envp);
			free(buf);
			buf = NULL;
			free(path);
			path = NULL;
			continue;
		}
		if (*path != '/')
		{
			printf("%s: %d: %s: not found\n", argv[0], line_num, av[0]);
			continue;
		}
		child_pid = fork(); /* fork if command is valid */
		if (child_pid == -1)
		{
			perror("fork");
			free(buf);
			buf = NULL;
			exit(EXIT_FAILURE);
		}
		else if (child_pid == 0)
		{
			if (execve(path, av, envp) == -1)
			{
				perror("execve");
				free(buf);
				buf = NULL;
				exit(EXIT_FAILURE);
			}
		}
		else
		{
			if (wait(&status) == -1)
				perror("wait");
		}
		/* DOUBLE CHECK NO PARAMETERS THAT FAIL FOLLOWING CODE CHECK */
		if (*buf != '/')
		{
			free(path);
			path = NULL;
		}
	}
	if (isatty(STDIN_FILENO) == 1) /* Print newline before exiting */
		putchar('\n');
	return (0);
}

char *find_right_path(char *command)
{
	struct stat st;
	char *path = NULL, *dir = NULL, *ptr = NULL;
	size_t size;
	int i = 0, j = 0;

	if (command == NULL)
		return (NULL);
	ptr = _getenv("PATH");
	while (ptr[i] != '=')
		i++;
	dir = ptr + i + 1;
	for (i = 0; dir[i] != '\0'; i++)
	{
		ptr = dir + i;
		for (j = 0; dir[i] != ':' && dir[i] != '\0'; j++, i++)
			;
		if (dir[i] == '\0')
			break;
		size = (j + strlen(command) + 2);
		path = realloc(path, size);
		if (path == NULL)
			return (NULL);
		strncpy(path, ptr, j);
		path[j] = '\0';
		path = strcat(strcat(path, "/"), command);

		if (stat(path, &st) == 0)
		{
			/* strcpy(pp, path);
			path_ptr = pp;
			free(path);
			return (path_ptr); */
			return (path);
		}
	}
	free(path);
	return (command);
}
/**
 * get_env - returns environment info for name
 * @name: environment variable to search for
 * Return - env var info in a string of type key=value
 **/
char *_getenv(char *name)
{
	extern char **environ;
	size_t size = sizeof(char) * strlen(name) + 1;
	/* CHANGE THIS CALLOC BELOW AND DOES IT NEED A FREE?????*/
	char *matcher = malloc(size);
	int i;

	if (matcher == NULL)
		return (NULL);
	memset(matcher, 0, size);
	for (i = 0; environ[i]; i++)
	{
		strncpy(matcher, environ[i], size - 1);
		if (strcmp(matcher, name) == 0)
			break;
	}
	free(matcher);
	return (environ[i]);
}
/**
 * make_av - make argument array for an execve from a string
 * @av: pointer to argument array to be filled
 * @line: line to be turned into arguments
 * Return: void
 **/
char *make_av(char *av[], char *line)
{
	int i = 0, j = 0;
	char *ptr = NULL, *path_ptr = NULL;

	memset(av, 0, 1024);
	for (; line[i] != '\0'; i++, j++)
	{
		while (line[i] == ' ' || line[i] == '\n')
			i++;
		ptr = line + i;
		while (line[i] != ' ' && line[i] != '\n' && line[i] != '\0')
			i++;
		if (line[i] != '\0')
		{
			*(line + i) = '\0';
			if (j == 0)
				path_ptr = find_right_path(ptr);
			av[j] = ptr;
			/* printf("av[%d] is: %s\n", j, av[j]); */
			/* if (j == 0)
				av[j] = find_right_path(ptr);
			printf("av[%d] is: %s\n", j, av[j]); */
		}
	}
	av[j] = NULL;
	/* printf("av[%d] is: %s\n", j, av[j]);
	printf("path_ptr is: %s\n", path_ptr); */
	return (path_ptr);
}

void print_env(char *envp[])
{
	int i = 0;
	while (envp[i])
	{
		printf("%s\n", envp[i]);
		i++;
	}
}
