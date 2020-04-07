#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void main()
{
	int i;

	for (i = 0; i < 10; i++)
		;
	printf("%d\n", i);
	i = 0;

	while (i < 10)
		i++;

	printf("%d\n", i);
}
