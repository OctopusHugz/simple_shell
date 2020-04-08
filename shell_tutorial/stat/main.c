#include "header.h"

int main(void)
{
	char *path = _getenv("PATH");
	dir_t *head;

	printf("path = %s\n", path);

	head = make_path_list(path);
	path = find_right_path(head, "/ls");

	while (head)
	{
		printf("%s\n", head->dir);
		head = head->next;
	}

	printf("path = %s\n", path);

	return (0);
}
