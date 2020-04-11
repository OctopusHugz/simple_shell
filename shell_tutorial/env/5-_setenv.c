#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
/**
 * _setenv - set an environment variable
 * @name: environment variable to set
 * @value: value
 * @overwrite: idk 
 * Return: Not sure.
 **/
int _setenv(const char *name, const char *value, int overwrite)
{
    extern char **environ;
    char *ptr = _getenv(name);
    char *shifter;
    int old_entry_size = strlen(ptr) + 1;
    int new_entry_size = strlen(name) + strlen(value) + 2;
    int old_env_size = strings_size(environ);
    int new_env_size = old_env_size + new_entry_size;
    int i = 0;

    if (ptr)
    {
        if (overwrite)
        {
            if (old_entry_size < new_entry_size)
            {
                environ = realloc(environ, new_env_size);
                
                for (next = ptr; next + 1; next++)
                    ;

                for (; next != ptr + new_entry_size; next--)
                    *(next + new_entry_size) = *next;

                --next = '\0';
            }

            while (*(ptr - 1) != '=')
                ptr++;
            
            for (i = 0; value[i] != '\0'; i++)
                ptr[i] = value[i];
                
            for (; ptr[i] != '\0'; i++)
                ptr[i] = '\0';
        }

    }
    else
    {
        environ = realloc(environ, size);

        for (i = 0; name[i]; i++, prev_size++)
            environ[prev_size] = name[i];
    
        environ[prev_size++] = '=';

        for (i = 0; value[i]; i++, prev_size++)
            environ[prev_size] = value[i];

        environ = realloc(environ, size);
    }
    
}
int strings_size(char **strings)
{
    long int start = &strings[0][0];
    long int end;
    int i, j;

    for (i = 0; strings[i]; i++)
        for (j = 0; strings[i][j] != '\0'; j++)
            ;
    
    end = &strings[i - 1][j - 1];
    return (end - start + 2);
}
int main(void)
{
    char *strings[] = {"One", "two", "tee", NULL};
    int size = strings_size(strings);

    printf("%s\n", *strings);
    printf("%d\n", size);
    return (0);
}
