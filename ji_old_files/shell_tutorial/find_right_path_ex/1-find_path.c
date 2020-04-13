#include "header.h"
/**
 * find_right_path - finds if a path exists within a list of paths
 * @path_list: head to node of a path linked list (dir_t)
 * @command: command to find
 * Return - path (as a pointer to a string)
 **/
char *find_right_path(dir_t *head, char *command)
{
	struct stat st;
	char *path, *dup;

	if (head == NULL || command == NULL)
		return (NULL);

	for (; head; head = head->next)
	{
		dup = strdup(head->dir);
		dup = realloc(dup, sizeof(char) * (strlen(dup) + strlen(command)) + 1);
		path = strcat(dup, command);
		free(dup);
		if (stat(path, &st) == 0)
			return (path);
	}
	return (NULL);
}