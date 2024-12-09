#ifndef UTILS_H
# define UTILS_H

#include <sys/stat.h>
#include <sys/wait.h>
#include "handlers.h"

#define MAX_ARGS 10

int check_exec(const char *path);
int check_dir(const char *path);
char *find_executable(const char *file);
char **parse_args(const char *input);
void free_args(char **args);

#endif
