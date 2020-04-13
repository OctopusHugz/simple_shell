#include <stdio.h>
#include <string.h>
#include <stdlib.h>
char **return_array(char *s);
int main(void)
{
	char *s = "This is a test";
	char **av = return_array(s);
	int index = 0;

	while (av[index])
		printf("%s\n", av[index++]);
	return(0);
}
char **return_array(char *s)
{
	char *cpy = strdup(s);
	char *delims = " ";
	char *token = strtok(cpy, delims);
	char **array = NULL;
	int index = 0, gate = 0;

	while (token || gate)
	{
		array = realloc(array, sizeof(char *) * (index + 1));
		array[index++] = token;
		if (token)
			token = strtok(NULL, delims);
		if (!(token))
			gate = gate ^ 1;
	}
	return (array);
}
