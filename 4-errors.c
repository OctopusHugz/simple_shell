#include "shell.h"

/**
 * print_error_message - prints error
 * @shell_name: shell name
 * @line_num: line number of error
 * @program: program name
 * Return: status
 **/
int print_error_message(char *shell_name, int line_num, char *program)
{
	int status;
	char *error_message;

	if (errno == 2)
	{
		error_message = ": not found\n";
		status = 127;
	}
	else
	{
		printf("errno: %d\n", errno);
		error_message = ": error unknown\n";
		status = 126;
	}

	stderr_print(shell_name);
	stderr_print(": ");
	stderr_int_print(line_num);
	stderr_print(": ");
	stderr_print(program);
	stderr_print(error_message);

	return (status);
}

/**
 * stderr_print - print to stderr
 * @str: string
 **/
void stderr_print(char *str)
{
	if (str)
		write(2, str, _strlen(str));
}

/**
 * stderr_int_print - prints an integer to stderr
 * @n: integer to print
 **/
void stderr_int_print(int n)
{
	char digit_as_char;

	if (n < 0)
	{
		write(1, "-", 1);
		n = -n;
	}

	if (n / 10)
		stderr_int_print(n / 10);

	digit_as_char = (n % 10) + '0';

	write(2, &digit_as_char, 1);
}
