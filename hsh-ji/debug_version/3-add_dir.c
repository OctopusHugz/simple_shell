#include "header.h"
/**
 * add_dir - adds a new directory node to end of a dir list
 *
 * @head: pointer to (head of) linked list
 * @dir: new node to add to end of linked list
 *
 * Return: address of head | NULL if malloc fails
 */

dir_t *add_dir(dir_t **head, const char *dir)
{
	dir_t *new = malloc(sizeof(dir_t));
	dir_t *tmp1;

	if (new == NULL)
		return (NULL);

	new->dir = NULL;

	if (dir)
		new->dir = strdup(dir);
	new->next = NULL;				/*1c*/

	if (*head == NULL)
	{
		*head = new;
	}
	else
	{
		tmp1 = *head;
		for (; tmp1->next != NULL; tmp1 = tmp1->next)
			printf("looking for last dir...\n");
		tmp1->next = new;
	}
	return (*head);
}
