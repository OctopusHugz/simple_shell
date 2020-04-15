#include "shell.h"

/**
 * make_av - make argument array for an execve from a string
 * @av: pointer to argument array to be filled
 * @line: line to be turned into arguments
 * Return: void
 **/
char *make_av(char *av[], char *line)
{
	int i = 0, j = 0, k = 0;
	char *ptr = NULL, *path_ptr = NULL;

	while (k < 4096)
	{
		av[k] = 0;
		k++;
	}
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
		if (j == 0 && (_strncmp(ptr, "env", 3) != 0))
			path_ptr = find_right_path(ptr);
	}
	av[j] = NULL;
	return (path_ptr);
}

/**
 * find_right_path - finds the location of an exectuable in the PATH
 * @command: command exectuable to find in the PATH
 * Return: path found where command resides, or the command if no path found
 **/
char *find_right_path(char *command)
{
	struct stat st;
	char *path = NULL, *dir = _getenv("PATH"),
		 *ptr = NULL, *pwd = NULL;
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
		path = stat_access_check(path, &st);
		if (path)
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
		{
			printf("PATH IS NULL RETURNING NULL\n");
			return (NULL);
		}
		_strncpy(path, ptr, i);
		path[i] = '\0';
		path = _strcat(_strcat(path, "/"), command);
		path_size = _strlen(path);
		path = stat_access_check(path, &st);
		if (path)
		{
			printf("The loop is returning %s!\n", path);
			return (path);
		}
	}
	path = _realloc(path, path_size, _strlen(command) + 1);
	path = _strncpy(path, command, _strlen(command) + 1);
	path = stat_access_check(path, &st);
	if (path)
	{
		printf("The penultimate return is returning %s!\n", path);
		return (path);
	}
	free(path);
	printf("The last return is returning null!\n");
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
 * stat_access_check - runs path dir through stat and access
 * @path: array of strings containing environment variables
 * Return: bad perms if access fails, path if executable is found,
 * and NULL if command is invalid
 **/
char *stat_access_check(char *path, struct stat *st)
{
	char *perms = "Bad perms";

	printf("path is: %s\n", path);
	if (stat(path, st) == 0)
	{
		if (access(path, X_OK) == 0)
		{
			printf("Returning path!\n");
			return (path);
		}
		free(path);
		path = NULL;
		printf("Returning perms!\n");
		return (perms);
	}
	printf("Returning null!\n");
	return (NULL);
}
