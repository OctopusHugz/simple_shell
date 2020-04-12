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

void free_list(dir_t *head);

void free_grid(char **grid, int height);

size_t print_list(const dir_t *h);

char *rev_string(char *s);

int main(int argc, char *argv[], char *envp[])
{
	char *buf = NULL, *token, *token_ptr = "", *args[1024], /*  *dirs[1024],  */ *dirs_two[1024], *path, *command, *dir;
	size_t len = 0;
	ssize_t characters = 0;
	int i = 0, j = 0, k = 0, l = 0, /* m = 0, p = 0,  */ q = 0, status = 0;
	pid_t child_pid = 0;
	dir_t *head, *tail;
	/* struct stat st; */

	if (argc != 1)
	{
		dprintf(STDERR_FILENO, "Usage: %s\n", argv[0]);
		exit(EXIT_FAILURE);
	}

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

		while (token)
		{
			token = strtok(NULL, " ");
			if (token == NULL)
				break;
			args[i] = token;
			i++;
		}
		args[i] = NULL;

		/* token_ptr = strdup(token); */
		printf("----------------------------\n");
		/* token_ptr = malloc(strlen(args[0]) + 1);
		if (token_ptr == NULL)
			return (0);
		strcpy(token_ptr, args[0]); */

		token_ptr = strdup(args[0]);

		printf("token_ptr is: %s\n", token_ptr);
		command = rev_string(token_ptr);
		strtok(command, "/");
		strcat(command, "/");
		rev_string(command);
		printf("command is: %s\n", command);
		printf("----------------------------\n");

		head = NULL;
		while (envp[k] != NULL)
		{
			if (strcmp(strtok(envp[k], "="), "PATH") == 0)
			{
				path = strtok(NULL, ":");
				while ((path = strtok(NULL, ":")))
				{
					/* dirs[l] = strdup(path); */

					dir = malloc(strlen(path) + strlen(command) + 1);
					dirs_two[l] = malloc(strlen(path) + strlen(command) + 1);
					if (dirs_two == NULL || dir == NULL)
						return (0);
					dir = "";
					strcpy(dir, path);
					strcat(dir, command);

					dirs_two[l] = strdup(dir);
					/* dirs[l] = dirs_two[l]; */

					tail = add_node_end(&head, dirs_two[l]);
					if (l == 0)
						printf("head->dir is: %s\n", head->dir);
					else
						printf("tail->dir is: %s\n", tail->next->dir);
					l++;
				}
				free_grid(dirs_two, l);
				break;
			}
			k++;
		}
		printf("----------------------------\n");

		child_pid = fork();
		if (child_pid == -1)
		{
			perror("fork");
			/* free(buf);
			free_list(head);
			free(command);
			free(dir);
			while (dirs[m])
			{
				free(dirs[m]);
				m++;
			}
			while (dirs_two[p])
			{
				free(dirs_two[p]);
				p++;
			}
			_exit(EXIT_FAILURE); */
			break;
		}
		if (child_pid == 0)
		{
			if (execve(args[0], args, envp) == -1)
			{
				printf("%s: 1: ", args[3]);
				while (args[1][q])
				{
					if (args[1][q] != '"')
						printf("%c", args[1][q]);
					q++;
				}
				printf(": not found");
				break;
				/* _exit(EXIT_FAILURE); */
			}
			/* l = 0;
			while (dirs[l])
			{
				if (stat(dirs[l], &st) == 0)
				{
				}
				l++;
			} */
		}
		else
		{
			if (wait(&status) == -1)
				perror("wait");
		}
	}
	printf("Exited while loop\n");
	free(buf);
	free(command);
	free(token);
	free(path);
	/* free(dir); */
	/* free(token_ptr); */
	free_list(head);
	printf("l is: %d\n", l);
	/* free_grid(dirs_two, l); */
	/* m = 0, l = 0;
	while (dirs[m])
	{
		free(dirs[m]);
		m++;
	}
	while (dirs_two[p])
	{
		free(dirs_two[p]);
		p++;
	} */
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

void free_grid(char **grid, int height)
{
	int rows;

	if (height > 0)
	{
		for (rows = 0; rows < height; rows++)
			free(grid[rows]);
	}
	free(grid);
}
