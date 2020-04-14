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
			_puts("$ ");
		if (getline(&buf, &size, stdin) == -1) /* Copy command line to buf */
		{
			free(buf);
			buf = NULL;
			break;
		}
		path = make_av(av, buf);			/* Make argv[] for next exec */
		if ((_strncmp(path, "\n", 1) == 0)) /* Start over if buf is just '\n' */
			continue;
		if (_strncmp(path, "exit", 4) == 0)
		{
			free(buf);
			exit(status);
		}
		if (_strncmp(path, "env", 3) == 0)
		{
			print_env(envp);
			free(buf);
			buf = NULL;
			continue;
		}
		if (path == NULL)
		{
			printf("%s: %d: %s: not found\n", argv[0], line_num, av[0]);
			status = 2;
			continue;
		}
		child_pid = fork(); /* fork if command is valid */
		if (child_pid == -1)
		{
			perror("fork");
			free(buf);
			buf = NULL;
			free(path);
			path = NULL;
			exit(EXIT_FAILURE);
		}
		else if (child_pid == 0)
		{
			if (execve(path, av, envp) == -1)
			{
				perror("execve");
				free(buf);
				buf = NULL;
				/* NEED TO FREE PATH AND NULL IT HERE?! */
				exit(EXIT_FAILURE);
			}
		}
		else
		{
			if (wait(&status) == -1)
				perror("wait");
		}
		/* DOUBLE CHECK NO PARAMETERS THAT FAIL */
		/* FOLLOWING CODE CHECK BEFORE MOVING ON!!!! */
		free(path);
		path = NULL;
	}
	if (isatty(STDIN_FILENO) == 1) /* Print newline before exiting */
		_putchar('\n');
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
	size_t size = _strlen(command) + 1;
	int i = 0, path_size = 0;

	if (command == NULL)
		return (NULL);
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
		size = (i + _strlen(command) + 2);
		path = _realloc(path, path_size, size);
		if (path == NULL)
			return (NULL);
		_strncpy(path, ptr, i);
		path[i] = '\0';
		path = _strcat(_strcat(path, "/"), command);

		if (stat(path, &st) == 0)
			return (path);

		path_size = _strlen(path);
	}
	path = _realloc(path, path_size, _strlen(command) + 1);
	path = _strncpy(path, command, _strlen(command) + 1);
	if (stat(path, &st) == 0)
		return (path);
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
	size_t i, j;

	for (i = 0; environ[i]; i++)
	{
		for (j = 0; name[j] != '\0'; j++)
			if (environ[i][j] != name[j])
				break;

		if (j == _strlen(name) && environ[i][j - 1] == name[j - 1])
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
		while (line[i] == ' ')
			i++;
		ptr = line + i;
		if (*ptr != '\n')
		{
			while (line[i] != ' ' && line[i] != '\n' && line[i] != '\0')
				i++;
			line[i] = '\0';
		}

		av[j] = ptr;
		if (j == 0)
			path_ptr = find_right_path(ptr);
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
