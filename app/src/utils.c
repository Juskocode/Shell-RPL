#include "colors.h"
#include "utils.h"

/** Checks if a file is executable */
int check_exec(const char *path) {
    return access(path, X_OK) == 0;
}

/** Checks if a path is a directory */
int check_dir(const char *path) {
    struct stat path_stat;

    if (stat(path, &path_stat) != 0) {
        printf(GREEN "cd: %s" RED ": No such file or directory\n" RESET, path);
        return 0;
    }

    if (!S_ISDIR(path_stat.st_mode)) {
        printf(GREEN "cd: %s" RED ": Not a directory\n" RESET, path);
        return 0;
    }

    return 1;
}

/** Finds the full path of an executable */
char* find_executable(const char *file) {
    char *path_env = getenv("PATH");
    if (!path_env)
        return NULL;

    char *path_copy = strdup(path_env);
    char *dir = strtok(path_copy, ":");
    static char full_path[1024];

    while (dir != NULL) {
        snprintf(full_path, sizeof(full_path), "%s/%s", dir, file);
        if (check_exec(full_path)) {
            free(path_copy);
            return full_path;
        }
        dir = strtok(NULL, ":");
    }

    free(path_copy);
    return NULL;
}

/** Parses input into an array of arguments */
char** parse_args(const char *input) {
    char **args = malloc(MAX_ARGS * sizeof(char *));
    if (!args) {
        perror(RED "Error allocating memory for args" RESET);
        exit(1);
    }

    int i = 0;
    char *input_copy = strdup(input);
    char *arg = strtok(input_copy, " ");

    while (arg != NULL && i < MAX_ARGS - 1) {
        args[i++] = strdup(arg);
        arg = strtok(NULL, " ");
    }
    args[i] = NULL;

    free(input_copy);
    return args;
}

/** Frees the memory allocated for arguments */
void free_args(char **args) {
    if (!args) return;
    for (int i = 0; args[i] != NULL; i++) {
        free(args[i]);
    }
    free(args);
}
