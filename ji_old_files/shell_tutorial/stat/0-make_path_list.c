#include "header.h"
/**
 * make_path_list - make linked list of directory paths
 * @path: list of directories, colon separated.
 * Return: address to head node of list
 **/

dir_t *make_path_list(char *path)
{
	dir_t *head = NULL;
	char *dir = strtok(path, ":");

	while (dir)
	{
		add_dir(&head, dir);
		dir = strtok(NULL, ":");
	}

	return (head);
}
