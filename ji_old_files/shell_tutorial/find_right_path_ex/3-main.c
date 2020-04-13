#include "header.h"

int main(void)
{
	char *path = strdup("a:as:asd:asdf");
	dir_t *head;

	printf("path = %s\n", path);

	head = make_path_list(path);
	path = find_right_path(head, "l");

	while (head)
	{
		printf("%s\n", head->dir);
		head = head->next;
	}
	free_list(head);
	printf("path = %s\n", path);
	return (0);
}
