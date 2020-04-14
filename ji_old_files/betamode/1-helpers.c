#include "header.h"
/**
 * find_right_path - finds path for a command, if it exists
 * @command: command to find
 * Return - path to command, command included
 **/
char *find_right_path(char *command)
{
	struct stat st;
	char *path = NULL, *dir = NULL, *ptr = NULL;
	size_t size = 0;
	int i = 0, j = 0;

	if (command == NULL)
		return (NULL);
	ptr = _getenv("PATH");
	if (ptr == NULL)
		return (NULL);
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
		size = sizeof(char) * (j + strlen(command) + 2);
		path = realloc(path, size);
		strncpy(path, ptr, j);
		path[j] = '\0';
		path = strcat(strcat(path, "/"), command);
		if (stat(path, &st) == 0)
			return (path);			
	}
	free(path);
	return (NULL);
}
/**
 * get_env - returns environment info for name
 * @name: environment variable to search for
 * Return - env var info in a string of type key=value
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
void make_av(char *(*av)[], char *line)
{
	int i = 0, j = 0;
	char *ptr = NULL;

	for (; line[i] != '\0'; i++, j++)
	{
		/* Find beginning of word */
		while (line[i] == ' ' || line[i] == '\n')
			i++;		
		/* check later if arrow keys mess this up */
		/* Use ptr to store beginning of word */
		ptr = &line[i];
		/* Find end of word */
		while (line[i] != ' ' && line[i] != '\n' && line[i] != '\0')
			i++;
		/* Assign word to index in av */
		(*av)[j] = ptr;
		/* Check if you found the last word. If not,  */
		if (line[i] != '\0')
			*(line + i) = '\0';
		else
			break;
		/* Create command for av[0] */
		if (j == 0)
		{
			(*av)[j] = find_right_path((*av)[j]);
			if ((*av)[j] == NULL)
			{
				dprintf(STDERR_FILENO, "%s: command not found\n", ptr);
				break;
			}
		}
	}
	(*av)[j] = NULL;
}