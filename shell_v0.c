#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char *argv[], char *envp[])
{
	char *buf = NULL, *token, *args[1024];
	size_t len = 0;
	ssize_t characters = 0;
	int i = 0, j = 0, status = 0, num_proc = 0;
	pid_t child_pid = 0;

	if (strcmp(argv[0], "./sh") != 0)
		exit(97);
	if (argc < 1)
		return (1);

	/* isatty(STDIN_FILENO) == 1 */
	while (1)
	{
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

		child_pid = fork();

		num_proc++;

		if (child_pid == -1)
		{
			perror("Error:");
			return (1);
		}
		if (child_pid == 0)
		{
			execve(args[0], args, envp);
			/* _exit(EXIT_SUCCESS); */
		}
		else
		{
			wait(&status);
			/* printf("wpid is : %d\n", wpid);
			printf("child_pid is : %d\n", child_pid);
			if (wpid != child_pid)
			{
				free(buf);
				perror("wait() failed (no more child processes?)");
				_exit(EXIT_FAILURE);
			} */

			/* if ((wpid = wait(&status)) != -1)
				free(buf); */

			/* wpid = wait(&status);
			printf("wpid is : %d\n", wpid);
			printf("num_proc is : %d\n", num_proc);
			if (wpid == (pid + 2 * num_proc) && num_proc != 1)
			{
				printf("freeing from pid: %d\n", wpid);
				free(buf);
			} */
		}
		free(buf);
		buf = NULL;
	}
	free(buf);
	putchar('\n');
	return (0);
	/* exit(status); */
}
