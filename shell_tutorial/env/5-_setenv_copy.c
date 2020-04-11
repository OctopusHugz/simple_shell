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
char *_getenv(const char *name)
{
	extern char **environ;
	size_t size = sizeof(char) * strlen(name) + 1;
	char *matcher = calloc(size, sizeof(char));
	int i;

	for (i = 0; environ[i]; i++)
	{
		strncpy(matcher, environ[i], size - 1);
		if (strcmp(matcher, name) == 0)
			break;
	}
	free(matcher);
	return (environ[i]);
}
int strings_size(char **strings)
{
    int i, j, size = 0;

    for (i = 0; strings[i]; i++, size++)
        for (j = 0; strings[i][j] != '\0'; j++, size++)
            ;
    
    return (size);
}
int _setenv(const char *name, const char *value, int overwrite)
{
    extern char **environ;
    char *changer, *ptr = _getenv(name);
    char **shifter;
    size_t new_entry_size = sizeof(char) * (strlen(name) + strlen(value) + 2);
    size_t old_env_size = strings_size(environ) * sizeof(char);
    size_t new_env_size = (old_env_size + new_entry_size) * sizeof(char);
    int i = 0, j = 0;

    printf("O.Env.S = %d\n", (int)old_env_size);
    printf("N.E.S. = %d\t", (int)new_entry_size);
    printf("N.Env. S = %d\n", (int)new_env_size);
    printf("ptr = %s\n", ptr);
    
    if (!name)
        return (-1);

    if (ptr)
    {
        if (overwrite)
        {
            if (strlen(ptr) + 1 < new_entry_size)
            {
                environ = realloc(environ, new_env_size);
                shifter = &ptr;
                for (; shifter[i]; i++)
                    printf("shifter = %s\n", *shifter);
                for (j = 0; shifter[i][j] != '\0'; j++)
                    printf("shifter = %s\n", *shifter);

                changer = *(shifter + i) + (j + new_entry_size);

                for (; &shifter[i][j] != &ptr[new_entry_size]; i--)
                    for (j = strlen(shifter[i]); j >= 0; j--, changer--)
                        if (&shifter[i][j] == &ptr[new_entry_size])
                            break;
                        else
                            *changer = shifter[i][j];

                *(changer - 1) = '\0';
            }

            while (*(ptr - 1) != '=')
                ptr++;
            printf("ptr = %s\n", ptr);
            for (i = 0; value[i] != '\0'; i++)
            {
                ptr[i] = value[i];
                printf("ptr = %s\n", ptr);
            }
                
            for (; ptr[i] != '\0'; i++)
                ptr[i] = '\0';
        }
    }
    else
    {
        environ = strdup(environ);
        environ = realloc(environ, new_entry_size);

        for (i = 0; environ[i]; i++)
            ;

        printf("environ[i] = %s\n", environ[i]);
        ptr = environ[i];
        environ[i + 1] = NULL;
        printf("ptr = %s\n", ptr);

        for (i = 0; name[i]; i++)
        {
                ptr[i] = name[i];
                printf("%s\n", ptr);
        }    

        ptr[i++] = '=';

        for (; *value != '\0'; i++)
        {
            ptr[i] = value[i];
            printf("%s\n", ptr);
        }
    }

    for (i = 0; environ[i]; i++)
        printf("%s\n", environ[i]);

    return (0);
}
int main(void)
{   
    _setenv("STACE", "i miss chidi. he was an excellent mailman.", 1);
    return (0);
}
