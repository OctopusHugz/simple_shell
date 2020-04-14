#include "shell.h"

/**
 * find_right_path - finds the location of an exectuable in the PATH
 * @command: command exectuable to find in the PATH
 * Return: path found where command resides, or the command if no path found
 **/
char *find_right_path(char *command)
{
	struct stat st;
	char *path = NULL, *dir = _getenv("PATH"), *ptr = NULL, *pwd = NULL;
	size_t size = _strlen(command) + 1;
	int i = 0, path_size = 0;

	if (command == NULL)
		return (NULL);
	while (*dir != '=')
		dir++;
	dir++;
	if (*dir == ':')
	{
		pwd = _getenv("PWD");
		path = getcwd(path, _strlen(pwd));
		path = _strcat(_strcat(path, "/"), command);
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
		if (j != 0 || line[i] != '\n')
		{
			while (line[i] != ' ' && line[i] != '\n' && line[i] != '\0')
				i++;
			line[i] = '\0';
		}
		if (*ptr)
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

/**
 * sigint_handler - handles SIGINT (CTRL-C) signal for shell
 * @signum: signal number caught by signal, 2 for SIGINT
 **/
void sigint_handler(int signum)
{
	if (signum == 2)
	{
		_putchar('\n');
		_puts("$ ");
	}
}
