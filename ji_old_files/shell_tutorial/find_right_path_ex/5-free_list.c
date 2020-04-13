#include "header.h"
/**
 * free_list - frees a list of its allocated memory
 *
 * @head: list to be freed
 *
 * Return: void
 */

void free_list(dir_t *head)
{
	dir_t *tmp;

	if (head == NULL)
		return;

	while (head != NULL)
	{
		tmp = head->next;
		free(head);
		head = tmp;
	}
}
