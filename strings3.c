#include "shell.h"

/**
 * err_putchar - writes the character c to stderr
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 **/
int err_putchar(char c)
{
	return (write(2, &c, 1));
}

/**
 * _puts - puts a string, followed by \n, to stdout
 * @str: string to put to stdout
 **/
void err_puts(char *str)
{
	int i = 0;

	for (; str[i] != '\0'; i++)
	{
		err_putchar(str[i]);
	}
}

/**
 * print_number - prints an integer
 * @n: integer to print
 **/
void err_print_number(int n)
{
	if (n < 0)
	{
		err_putchar('-');
		n = -n;
	}

	if (n / 10)
		err_print_number(n / 10);

	err_putchar(n % 10 + '0');
}
