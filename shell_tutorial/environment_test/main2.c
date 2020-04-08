#include "header.h"

int main(int ac __attribute__((unused)), char **av __attribute__((unused)), char **env)
{
	extern char **environ;
	int i = 0;
	printf("welcome to other ==============================\n");
	printf("environ[%d] = %s\n", i, environ[i]);
	
	while (environ[i])
		printf("%s\n", environ[i++]);

	printf("environ printed...\n");
	printf("printing envp...\n");
	i = 0;
	while (env[i])
		printf("%s\n", env[i++]);
	printf("we outie\n");

	
	return(0);
}