#ifndef GUARD
#define GUARD

/* Header files go here */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>

/* Typedefs go here */
typedef struct list_s {
	char *dir;
	struct list_s *next;
} dir_t;

/* Prototypes go here */
char *_getenv(char *name);
char *find_right_path(dir_t *head, char *command);
dir_t *make_path_list(char *path);
dir_t *add_dir(dir_t **head, const char *dir);


#endif
