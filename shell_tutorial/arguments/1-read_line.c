#include "shell.h"

int main(void)
{
	size_t read = 1024;
	char *line = NULL;

	printf("$ ");
	if (_getline(&line, &read, stdin) == -1)
	{
		printf("Such error\n");
		return (-1);
	}
	printf("%s", line);
	free(line);
	return (0);
}
