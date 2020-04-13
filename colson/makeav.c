#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>

char *make_av(char *av[], char *line)
{
    int i = 0, j = 0;
    char *ptr = NULL, *path_ptr = NULL;

    memset(av, 0, 1024);
    for (; line[i] != '\0'; i++, j++)
    {
        while (line[i] == ' ' || line[i] == '\n')
            i++;
        ptr = line + i;
        while (line[i] != ' ' && line[i] != '\n' && line[i] != '\0')
            i++;

        av[j] = ptr;
    
        if (line[i] != '\0')
        {
            *(line + i) = '\0';
        }  
        else
        {
            j++;
            break;
        }

        if (j == 0)
		{
			(*av)[j] = find_right_path((*av)[j]);
			/*if ((*av)[j] == NULL)
			{
				dprintf(STDERR_FILENO, "%s: command not found\n", ptr);
				break;
			}*/
		}
    }
    av[j] = NULL;
    return (path_ptr);
}

int main()
{
  char *av[1024];
  char *line = "this is a test\n";
  char *pathptr;
  
  pathptr = make_av(av, line);
  
  printf("done %c\n", *pathptr);
  
  return 0;
}