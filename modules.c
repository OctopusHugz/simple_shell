#include "shell.h"

/**
 * make_av - make argument array for an execve from a string
 * @av: pointer to argument array to be filled
 * @str: line to be turned into arguments
 * Return: void
 **/
char *make_av(char *av[], char *str)
{
	int i = 0, j = 0, k = 0;
	char *ptr = NULL, *path_ptr = NULL;

	while (k < 4096)
	{
		av[k] = 0;
		k++;
	}
	for (; str[i] != '\0'; i++, j++)
	{
		while (str[i] == ' ' || str[i] == '\t')
			i++;
		ptr = str + i;
		if (j != 0 || str[i] != '\n')
		{
			while (str[i] != ' ' && str[i] != '\n' && str[i] != '\0' && str[i] != '\t')
				i++;
			str[i] = '\0';
		}
		if (*ptr && (j == 0 || *ptr != '#') && *ptr != '$')
			av[j] = ptr;
		else if (*ptr == '$')
		{
			av[j] = get_var(ptr);
			if (!av[j])
			{
				j--;
				continue;
			}
		}
		if (j == 0 && (_strncmp(ptr, "env", 3) != 0))
			path_ptr = find_right_path(ptr);
		if (*ptr == '#')
			break;
	}
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
	char *path = NULL, *dir = NULL, *tmp = NULL,
		 *ptr = _getenv("PATH") + 5, *cwd = _getenv("PWD") + 4;
	size_t com_len = _strlen(command), dir_len = 0,
		   old_size = 0, new_size = com_len + 1;
	int path_check = slash_check(command);

	while (*ptr != '\0' && path_check)
	{
		tmp = ptr;
		if (*ptr == ':')
			ptr = cwd;
		dir = ptr;
		for (dir_len = 0; *ptr != ':' && *ptr != '\0'; dir_len++, ptr++)
			;
		new_size = (dir_len + com_len + 2);
		path = _realloc(path, old_size, new_size);
		if (path == NULL)
			return (NULL);
		_strncpy(path, dir, dir_len);
		path[dir_len] = '\0';
		path = _strcat(_strcat(path, "/"), command);
		if (stat(path, &st) == 0)
			return (access_check(path));
		old_size = _strlen(path) + 1;
		if (*tmp == ':')
			ptr = tmp;
		ptr++;
	}
	path = _realloc(path, old_size, com_len + 1);
	path = _strncpy(path, command, com_len + 1);
	if (stat(path, &st) == 0)
		return (access_check(path));
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
 * print_env - prints all the environment variables
 * of the current environment from *envp[]
 * @envp: array of strings containing environment variables
 **/
void print_env(char *envp[])
{
	int i = 0;

	while (envp[i])
	{
		_puts(envp[i]);
		_putchar('\n');
		i++;
	}
}

/**
 * access_check - checks if calling process
 * has permissions to file found in PATH
 * @path: directory where executable was found
 * Return: path if correct perms, bad perms if incorrect perms
 **/
char *access_check(char *path)
{
	char *perms = "Bad perms";

	if (access(path, X_OK) == 0)
		return (path);
	free(path);
	path = NULL;
	return (perms);
}
