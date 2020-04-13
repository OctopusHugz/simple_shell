#include "header.h"

int main(void)
{
	char *path = _getenv("PATH");
	dir_t *head;

	printf("path = %s\n", path);

	head = make_path_list(path);

	while (head)
	{
		printf("%s\n", head->dir);
		head = head->next;
	}

	return (0);
}
