#include "utils.h"
#include "envcp.h"
#include "handlers.h"

/** Handles the `echo` command */
void handle_echo(const char *input) {
    printf(GREEN "%s\n" RESET, input + 5);
}

/** Handles the `type` command */
void handle_type(const char *input) {
    const char *target = input + 5;

    if (strcmp(target, "echo") == 0) {
        printf(BLUE "echo " GREEN "is a shell builtin\n" RESET);
    } else if (strcmp(target, "exit") == 0) {
        printf(BLUE "exit " GREEN "is a shell builtin\n" RESET);
    } else if (strcmp(target, "type") == 0) {
        printf(BLUE "type " GREEN "is a shell builtin\n" RESET);
    } else if (strcmp(target, "pwd") == 0) {
        printf(BLUE "pwd " GREEN "is a shell builtin\n" RESET);
    } else if (strcmp(target, "cd") == 0) {
        printf(BLUE "cd " GREEN "is a shell builtin\n" RESET);
    } else {
        char *path = find_executable(target);
        if (path) {
            printf(GREEN "%s" RESET " is " YELLOW "%s\n" RESET, target, path);
        } else {
            printf(RED "%s: not found\n" RESET, target);
        }
    }
}

/** Handles the `exit` command */
void handle_exit() {
    exit(0);
}

/** Handles the `pwd` command */
void handle_pwd() {
    char cwd[MAX_CWD_SIZE];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf(GREEN "%s\n" RESET, cwd);
    } else {
        perror(RED "getcwd failed" RESET);
    }
}

/** Handles the `cd` command */
void handle_cd(const char *input) {
    const char *path = input + 3;

    if (strcmp(path, "") == 0) {
        path = getenv("HOME");
    }

    char *resolved_path = resolve_path(path);
    if (resolved_path && check_dir(resolved_path)) {
        if (chdir(resolved_path) != 0) {
            perror(RED "chdir error" RESET);
        }
    }
}

