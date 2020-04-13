#include "shell.h"

/**
 * main - run UNIX simple shell command interpreter
 * @argc: number of arguments provided to main
 * @argv: array of strings containing arguments to main
 * @envp: array of strings containing environment variables
 * Return: exit status
 **/
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
	while (1)
	{
		line_num++;
		if (isatty(STDIN_FILENO) == 1) /* Print $ if stdin is terminal */
			printf("$ ");
		if (getline(&buf, &size, stdin) == -1) /* Copy command line to buf */
			break;
		if ((strcmp(buf, "\n") == 0)) /* Start over if buf is just '\n' */
			continue;
		if (strcmp(buf, "env") == 0)
		{
			print_env(envp);
			continue;
		}
		if (strncmp(buf, "exit", 4) == 0)
			exit(status);
		path = make_av(av, buf); /* Make argv[] for next exec */
		if (path == NULL)
		{
			printf("%s: %d: %s: not found\n", argv[0], line_num, av[0]);
			status = 127;
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
		free(path);
		path = NULL;
	}
	if (isatty(STDIN_FILENO) == 1) /* Print newline before exiting */
		putchar('\n');
	free(buf);
	exit(status);
}

/**
 * find_right_path - finds the location of an exectuable in the PATH
 * @command: command exectuable to find in the PATH
 * Return: path found where command resides, or the command if no path found
 **/
char *find_right_path(char *command)
{
	struct stat st;
	char *path = NULL, *dir = NULL, *ptr = NULL, *pwd = NULL;
	size_t size = strlen(command) + 1;
	int i = 0;

	/*CHECK LATER WHAT HAPPENS IF COMMAND IS NULL*/
	if (command == NULL)
		return (NULL);

	path = strdup(command);

	if (stat(path, &st) == 0)
		return (path);

	dir = _getenv("PATH");

	while (*dir != '=')
		dir++;
	dir++;

	if (*dir == ':')
	{
		pwd = _getenv("PWD");
		path = getcwd(path, strlen(pwd));
		path = strcat(strcat(path, "/"), command);
		if (stat(path, &st) == 0)
			return (path);
	}

	for (; *dir != '\0'; dir++)
	{
		ptr = dir;
		for (i = 0; *dir != ':' && *dir != '\0'; i++, dir++)
			;

		size = (i + strlen(command) + 2);
		path = realloc(path, size);
		if (path == NULL)
			return (NULL);
		strncpy(path, ptr, i);
		path[i] = '\0';
		path = strcat(strcat(path, "/"), command);

		if (stat(path, &st) == 0)
			return (path);
	}
	free(path);
	return (NULL);
}

/**
 * _getenv - returns environment info for name
 * @name: environment variable to search for
 * Return: env var info in a string of type key=value
 **/
char *_getenv(char *name)
{
	extern char **environ;
	size_t i, j;

	for (i = 0; environ[i]; i++)
	{
		for (j = 0; name[j] != '\0'; j++)
			if (environ[i][j] != name[j])
				break;

		if (j == strlen(name) && environ[i][j - 1] == name[j - 1])
			break;
	}
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
			line[i] = '\0';
		else
		{
			break;
		}
		av[j] = ptr;
		if (j == 0)
		{
			path_ptr = find_right_path(ptr);
			if (av[j] == NULL)
			{
				dprintf(STDERR_FILENO, "%s: command not found\n", ptr);
				break;
			}
		}
	}
	av[j] = NULL;
	return (path_ptr);
}

/**
 * print_env - prints all the environment variables
 * of the current environment from *envp[]
 * @envp: array of strings containing environment variables
 **/
void print_env(char *envp[])
{
	int i = 0;

	while (envp[i])
	{
		printf("%s\n", envp[i]);
		i++;
	}
}
