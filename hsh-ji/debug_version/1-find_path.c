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
	char *dup;

	printf("find_right_path: command = %s\n", command);
	if (head == NULL)
	{
		printf("find_right_path: HEAD IS NULL\n");
		return (NULL);
	} 

	if (command == NULL)
		return (NULL);


	for (; head; head = head->next)
	{
		dup = strdup(head->dir);
		dup = realloc(dup, sizeof(char) * (strlen(dup) + strlen(command)) + 1);
		path = strcat(dup, command);
		printf("find_right_path: path = %s\n", path);
		if (head->next == NULL)
			printf(":(\n");
		if (stat(path, &st) == 0)
			return (path);
	}
	printf("find_right_path: returning NULL\n");
	return (NULL);
}