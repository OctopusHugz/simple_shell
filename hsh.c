#include "shell.h"

int main(int argc, char *argv[], char *envp[])
{
	char *buf = NULL, *av[4096], *path;
	size_t size = 0;
	int status = 0, line_num = 0;
	pid_t child_pid = 0;

	if (argc != 1) /* Print usage if argc is off */
	{
		dprintf(STDERR_FILENO, "Usage: %s\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	/* av[0] = NULL; */
	while (1)
	{
		line_num++;
		if (isatty(STDIN_FILENO) == 1) /* Print $ if stdin is terminal */
			printf("$ ");
		if (getline(&buf, &size, stdin) == -1) /* Copy command line to buf */
		{
			free(buf);
			buf = NULL;
			break;
		}
		if ((strcmp(buf, "\n") == 0)) /* Start over if buf is just '\n' */
			continue;
		path = make_av(av, buf); /* Make argv[] for next exec */
		/* ADD FUNCTION HERE TO CHECK IF BUILTIN EXIT, ENV, SETENV, OR UNSETENV */
		if (strcmp(buf, "exit") == 0)
		{
			if (av[1])
				status = atoi(av[1]);
			free(buf);
			buf = NULL;
			exit(status);
		}
		if (strcmp(buf, "env") == 0)
		{
			print_env(envp);
			free(buf);
			buf = NULL;
			free(path);
			path = NULL;
			continue;
		}
		if (*path != '/')
		{
			printf("%s: %d: %s: not found\n", argv[0], line_num, av[0]);
			status = 127;
			continue;
		}
		child_pid = fork(); /* fork if command is valid */
		if (child_pid == -1)
		{
			perror("fork");
			free(buf);
			buf = NULL;
			exit(EXIT_FAILURE);
		}
		else if (child_pid == 0)
		{
			if (execve(path, av, envp) == -1)
			{
				perror("execve");
				free(buf);
				buf = NULL;
				exit(EXIT_FAILURE);
			}
		}
		else
		{
			if (wait(&status) == -1)
				perror("wait");
		}
		/* DOUBLE CHECK NO PARAMETERS THAT FAIL FOLLOWING CODE CHECK BEFORE MOVING ON!!!! */
		if (*buf != '/' && *buf != ' ' && *buf != '\n')
		{
			free(path);
			path = NULL;
		}

	}
	if (isatty(STDIN_FILENO) == 1) /* Print newline before exiting */
		putchar('\n');
	exit(status);
}

char *find_right_path(char *command)
{
	struct stat st;
	char *path = NULL, *dir = NULL, *ptr = NULL;
	size_t size;
	int i = 0;

	/*CHECK LATER WHAT HAPPENS IF COMMAND IS NULL*/
    if (command == NULL)
		return (NULL);
    
	dir = _getenv("PATH");

	while (*dir != '=')
        dir++;
    dir++;

    if (*dir == ':')
    {
        /**
         * The fix looks something like what I wrote below. It uses
         * getcwd, which gets the current working directory
         * and returns it as a string. We can set path to "cwd/command",
         * stat it, and if stat finds a match, then we return this path.
         * If it doesn't find a match, then we free the ptr we used to point
         * to cwd and move on to the rest of the function.
         *  
         *      cwd = getcwd(arguments); <--- idk what the args are. pay attention to freeing things.
         *      cwd = strcat(strcat(cwd, "/"), command);
         *      if (stat(cwd, &st) == 0)
         *          return (cwd);
         *      free(cwd); <---- idk if this is what needs to be freed, but it'll be something.
         **/
        return (command);
    }


	for (; *dir != '\0'; dir++)
	{
		ptr = dir;
		for (i = 0; *dir != ':' && *dir != '\0'; i++, dir++)
			;

		size = (i + strlen(command) + 2);
		path = realloc(path, size);
		if (path == NULL)
			return (NULL);
		strncpy(path, ptr, i);
		path[i] = '\0';
		path = strcat(strcat(path, "/"), command);

		if (stat(path, &st) == 0)
			return (path);
	}
	free(path);
	return (command);
}
/**
 * get_env - returns environment info for name
 * @name: environment variable to search for
 * Return - env var info in a string of type key=value
 **/
char *_getenv(char *name)
{
	extern char **environ;
	size_t i, j;

	for (i = 0; environ[i]; i++)
	{
		for (j = 0; name[j] != '\0'; j++)
			if (environ[i][j] != name[j])
				break;
		
		if (j == strlen(name) && environ[i][j - 1] == name[j - 1])
			break;
	}
	return (environ[i]);
}
/**
 * make_av - make argument array for an execve from a string
 * @av: pointer to argument array to be filled
 * @line: line to be turned into arguments
 * Return: void
 **/
char *make_av(char *av[], char *line)
{
	int i = 0, j = 0;
	char *ptr = NULL, *path_ptr = NULL;
	memset(av, 0, 1024);
	for (; line[i] != '\0'; i++, j++)
	{
		while (line[i] == ' ' || line[i] == '\n')
			i++;
		ptr = line + i;
		while (line[i] != ' ' && line[i] != '\n' && line[i] != '\0')
			i++;
		if (line[i] != '\0')
			line[i] = '\0';
		else
		{
			break;
		}
		av[j] = ptr;
		if (j == 0)
		{
			path_ptr = find_right_path(ptr);
			/* if ((*av)[j] == NULL)
			{
				dprintf(STDERR_FILENO, "%s: command not found\n", ptr);
				break;
			} */
		}
	}
	av[j] = NULL;
	return (path_ptr);
}

void print_env(char *envp[])
{
	int i = 0;
	while (envp[i])
	{
		printf("%s\n", envp[i]);
		i++;
	}
}
