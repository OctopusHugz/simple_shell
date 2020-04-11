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

/* Typedefs go here */
typedef struct list_s
{
	char *dir;
	struct list_s *next;
} dir_t;

/* Colson Prototypes go here */
char *rev_string(char *s);
void free_grid(char **grid, int height);
/* Prototypes go here */
char *_getenv(char *name);
char *find_right_path(char *command);
dir_t *make_path_list(char *path);
dir_t *add_dir(dir_t **head, const char *dir);
void free_list(dir_t *head);
void make_av(char *av[], char *line);
void print_env(char *envp[]);
#endif

int main(int argc, char *argv[], char *envp[])
{
	char *buf = NULL, *av[1024];
	size_t size = 0;
	int status = 0;
	pid_t child_pid = 0;

	if (argc != 1) /* Print usage if argc is off */
	{
		dprintf(STDERR_FILENO, "Usage: %s\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	/* av[0] = NULL; */ /* I don't know why I have to do this frankly */
	while (1)
	{
		if (isatty(STDIN_FILENO) == 1) /* Print $ if stdin is terminal */
			printf("$ ");
		if (getline(&buf, &size, stdin) == -1) /* Copy command line to buf */
		{
			free(buf);
			buf = NULL;
			/* free(*av);
			*av = NULL; */
			printf("getline -1 has freed buf\n");
			break;
		}
		if (buf[0] == '\n') /* Start over if buf is just '\n' */
			continue;
		/* av = malloc(sizeof(char *) * 2 num_args + 1);
		if (av == NULL)
			return (0); */
		make_av(av, buf); /* Make argv[] for next exec */
		/* if (av[0] == NULL)
			continue; */
		/* if ((av_status == 1 && (strcmp(buf, "exit") != 0)))
			continue; */
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
			free(*av);
			*av = NULL;
			continue;
		}
		child_pid = fork(); /* fork if command is valid */
		if (child_pid == -1)
		{
			perror("fork");
			free(buf);
			buf = NULL;
			/* IS THIS EXIT NEEDED????? */
			exit(EXIT_FAILURE);
		}
		else if (child_pid == 0)
		{
			if (execve(av[0], av, envp) == -1)
			{
				perror("execve");
				/* printf("%s: 1: ", argv[0]);
				while (av[1][i])
				{
					if (av[1][i] != '"')
						printf("%c", av[1][i]);
					i++;
				}
				printf(": not found"); */
				/* break; */
				free(buf);
				buf = NULL;
				printf("child has freed buf\n");
				exit(EXIT_FAILURE);
			}
		}
		else
		{
			if (wait(&status) == -1)
				perror("wait");
		}
		/* INVALID FREE WHEN NOT USING /BIN/ FIRST!!!!!!?????? */
		/* printf("*av is: %s\n", *av); */
		/* free(*av);
		*av = NULL;
		printf("av has been freed and nulled from end of while loop\n"); */
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
			return(path);
		/* return (path); */
		/* IS PATH NOT FREED HERE??? IS THAT OUR ISSUE */
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
void make_av(char *av[], char *line)
{
	int i = 0, j = 0;
	char *ptr = NULL;

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
			av[j] = ptr;
			if (j == 0)
				av[j] = find_right_path(av[j]);
			/* printf("av[1] is: %s\n", av[1]); */
			/* (*av)[j] = NULL; */
		}
	}
	/* This logic below was blocking arguments to /bin/ls when inside of for loop, does movig help????*/
	/* if ((*av)[0][0] == '/')
	{
		k = 1;
		printf("returning k as: %d from outside for loop\n", k);
		return (k);
	} */
	printf("j is: %d\n", j);
	av[j] = NULL;
	printf("av[1] is: %s\n", av[1]);
	/* printf("returning k as: %d from end of program\n", k); */
	/* return (k); */
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
