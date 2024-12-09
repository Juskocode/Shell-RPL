#include "utils.h"
#include "envcp.h"

/** Executes external commands */
void handle_external(const char *input) {
    char **args = parse_args(input);
    char *path = find_executable(args[0]);

    if (path) {
        pid_t pid = fork();
        if (pid == 0) {
            execvp(path, args);  // In child process
            perror(RED "Execution failed" RESET);
            exit(EXIT_FAILURE);
        } else if (pid > 0) {
            int status;
            waitpid(pid, &status, 0);
        } else {
            perror(RED "Fork failed" RESET);
        }
    } else {
        printf(RED "%s: not found\n" RESET, args[0]);
    }

    free_args(args);
}

/** Resolves a relative or absolute path */
char* resolve_path(const char *path) {
    static char resolved_path[MAX_CWD_SIZE];

    if (realpath(path, resolved_path) == NULL) {
        perror(RED "Error resolving path" RESET);
        return NULL;
    }

    return resolved_path;
}
