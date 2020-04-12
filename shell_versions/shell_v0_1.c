#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

typedef struct list_s
{
	char *dir;
	struct list_s *next;
} dir_t;

dir_t *add_node_end(dir_t **head, const char *dir);

void free_dir_safe(dir_t **h);

void free_list(dir_t *head);

size_t print_list(const dir_t *h);

char *rev_string(char *s);

int main(int argc, char *argv[], char *envp[])
{
	char *buf = NULL, *token, *token_ptr, *args[1024], *dirs[1024], *path, *command;
	size_t len = 0;
	ssize_t characters = 0;
	int i = 0, j = 0, k = 0, l = 0, status = 0;
	pid_t child_pid = 0;
	struct stat st;

	if (argc != 1)
	{
		dprintf(STDERR_FILENO, "Usage: %s\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	/* head = NULL;
	while (envp[k] != NULL)
	{
		if (strcmp(strtok(envp[k], "="), "PATH") == 0)
		{
			path = strtok(NULL, ":");
			while ((path = strtok(NULL, ":")))
			{
				dirs[l] = strdup(path);

				tail = add_node_end(&head, dirs[l]);
				l++;
			}
			break;
		}
		k++;
	}

	printf("head string is : %s\n", head->dir);
	printf("tail string is : %s\n", tail->dir);
	print_list(head);
	printf("----------------------------\n"); */

	while (1)
	{
		if (isatty(STDIN_FILENO) == 1)
			printf("$ ");
		characters = getline(&buf, &len, stdin);
		if (characters == -1)
			break;
		j = strlen(buf) - 1;
		buf[j] = '\0';
		i = 0;
		token = strtok(buf, " ");
		args[i] = token;
		i++;

		/* REVERSE TOKEN AND STRTOK AT FIRST / WHICH WILL GIVE US THE COMMAND */

		while (token)
		{
			token = strtok(NULL, " ");
			if (token == NULL)
				break;
			args[i] = token;
			i++;
		}
		args[i] = NULL;

		i = 0;
		while (args[i])
		{
			printf("args[%d] is : %s\n", i, args[i]);
			i++;
		}
		printf("args[%d] is : %s\n", i, args[2]);

		/* token_ptr = strdup(token); */
		printf("----------------------------\n");
		token_ptr = malloc(strlen(args[0]));
		if (token_ptr == NULL)
			return (0);
		strcpy(token_ptr, args[0]);
		printf("token_ptr is : %s\n", token_ptr);
		command = rev_string(token_ptr);
		strtok(command, "/");
		strcat(command, "/");
		rev_string(command);
		printf("command is : %s\n", command);
		printf("----------------------------\n");

		while (envp[k] != NULL)
		{
			if (strcmp(strtok(envp[k], "="), "PATH") == 0)
			{
				path = strtok(NULL, ":");
				while ((path = strtok(NULL, ":")))
				{
					dirs[l] = strdup(path);
					/* NEED TO MAKE THE STRCAT BELOW CONCAT THE COMMAND TO DIRS[L] SO CODE NEEDS TO MOVE TO INFINITE LOOP */
					strcat(dirs[l], command);
					printf("dirs[%d] is : %s\n", l, dirs[l]);
					l++;
				}
				break;
			}
			k++;
		}

		/* l = 0;
		while (dirs[l])
		{
			printf("dirs[%d] is : %s\n", l, dirs[l]);
			strcat(dirs[l], command);
			printf("dirs[%d] is : %s\n", l, command);
			l++;
		} */
		printf("----------------------------\n");

		l = 0;
		while (dirs[l])
		{
			if (stat(args[l], &st) == 0)
			{
				printf("path found at: %s", dirs[l]);
			}
			break;
			l++;
		}

		printf("----------------------------\n");

		child_pid = fork();
		if (child_pid == -1)
		{
			perror("fork");
			_exit(EXIT_FAILURE);
		}
		if (child_pid == 0)
		{
			if (execve(args[0], args, envp) == -1)
			{
				perror("./hsh");
				_exit(EXIT_FAILURE);
			}
		}
		else
		{
			if (wait(&status) == -1)
				perror("wait");
		}
	}
	free(buf);
	if (isatty(STDIN_FILENO) == 1)
		putchar('\n');
	/* exit(status); */
	return (0);
}

dir_t *add_node_end(dir_t **head, const char *dir)
{
	dir_t *new_node = malloc(sizeof(dir_t));
	dir_t *tail = *head;

	if (new_node == NULL)
		return (NULL);

	new_node->dir = strdup(dir);
	new_node->next = NULL;

	if (*head == NULL)
	{
		*head = new_node;
		return (*head);
	}

	while (tail->next != NULL)
		tail = tail->next;
	tail->next = new_node;
	return (tail);
}

size_t print_list(const dir_t *h)
{
	int count = 0;
	const dir_t *current_node = h;

	if (h == NULL)
		return (0);

	while (current_node != NULL)
	{
		if (current_node->dir == NULL)
		{
			printf("[0] %s\n", "(nil)");
			count++;
		}
		else
		{
			printf("[%d] %s\n", count,
				   current_node->dir);
			count++;
		}
		current_node = current_node->next;
		if (current_node == NULL)
			return (count);
	}
	return (count);
}

void free_dir_safe(dir_t **h)
{
	const dir_t *node;
	size_t count = 0;

	if (*h == NULL || h == NULL)
		return;

	while (*h)
	{
		count++;
		if ((*h)->next >= *h)
		{
			node = *h;
			free((void *)node);
			*h = NULL;
			return;
		}
		node = *h;
		*h = (*h)->next;
		free((void *)node);
	}
	*h = NULL;
}

void free_list(dir_t *head)
{
	dir_t *new_node;

	while (head)
	{
		new_node = head;
		head = head->next;
		free(new_node->dir);
		free(new_node);
	}
}

char *rev_string(char *s)
{
	int i, len;
	char *beg, *end, tmp;

	for (len = 0; s[len] != '\0'; len++)
	{
		;
	}
	beg = s;
	end = s;

	for (i = 0; i < len - 1; i++)
	{
		end++;
	}

	/* swap chars until halfway */

	for (i = 0; i < len / 2; i++)
	{
		tmp = *beg;
		*beg = *end;
		*end = tmp;
		beg++;
		end--;
	}
	return (s);
}
