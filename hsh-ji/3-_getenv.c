#include "header.h"

char *_getenv(char *name)
{
	extern char **environ;
	int i = 0;
	
	while (environ[i])
		if (strcmp(strtok(environ[i++], "="), name) == 0)
			return(strtok(NULL,"\n"));

    return (NULL);
}