#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
/**
 * main - prints process ID of parent process
 * Return: always 0.
 */
int main(void)
{
	pid_t ppid = getppid();

	printf("%d\n", ppid);
	return (0);
}
