#include "header.h"

int main(void)
{
	char *name = _getenv("PATH");

	printf("%s\n", name);

	return (0);
}