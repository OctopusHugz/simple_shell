#include "header.h"

int main(int ac __attribute__((unused)), char **argv __attribute__((unused)), char **env)
{
	extern char **environ;
	char *av[] = {"/bin/other", NULL};
	int i = 0;

	while (environ[i])
		printf("%s\n", environ[i++]);
	
	printf("Leaving here....\n");
	if (execve(av[0], av, env) == -1)
		printf("Couldn't leave!");
	return(0);
}