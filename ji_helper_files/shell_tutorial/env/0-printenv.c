#include "header.h"

int main(void)
{
    int i = 0;
    extern char **environ;

    while (environ[i])
        printf("%s\n", environ[i++]);

    return (0);
}