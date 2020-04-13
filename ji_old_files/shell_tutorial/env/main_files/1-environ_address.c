#include "header.h"

int main(int ac __attribute__((unused)), char **av __attribute__((unused)), char **env)
{
    extern char **environ;
    void *environ_address = &environ, *env_address = &env;

    printf("&environ = %p\n", environ_address);
    printf("&env = %p\n", env_address);

    return (0);

}