#include "header.h"
/**
 * make_path_list - make linked list of directory paths
 * @path: list of directories, colon separated.
 * Return: address to head node of list
 **/

dir_t *make_path_list(char *path)
{
	dir_t *head = NULL;
	char *dir;
	char *hold = strtok(path, ":");
	char *dup;
	
	while (hold)
	{
		dup = strdup(hold);
		dup = realloc(dup, sizeof(char) * strlen(hold) + 2);
		dir = strcat(dup, "/");
		printf("creating node for %s\n", dir);
		add_dir(&head, dir);
		hold = strtok(NULL, ":");
		if (hold == NULL)
			printf("NULL NULL NULL\n");
		free(dup);
	}

	return (head);
}
