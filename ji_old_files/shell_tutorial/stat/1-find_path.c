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
	char *path;

	if (command == NULL)
		return (NULL);


	for (; head; head = head->next)
	{
		path = strcat(head->dir, command);
		printf("\tpath = %s\n", path);
		if (stat(path, &st) == 0)
			return (path);
	}

	return (NULL);
}