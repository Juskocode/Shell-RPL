#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>

#define RESET   "\x1b[0m"
#define GREEN   "\x1b[32m"
#define BLUE    "\x1b[34m"
#define YELLOW  "\x1b[33m"
#define RED     "\x1b[31m"

#define MAX_ARGS 10
#define MAX_CWD_SIZE 1024

// Command Handler Function Pointer
typedef void (*command_handler)(const char *input);

// Command Structure
typedef struct {
    const char *name;
    command_handler handler;
} Command;

// ======================= Utility Functions =======================

/** Checks if a file is executable */
int check_exec(const char *path) {
    return access(path, X_OK) == 0;
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
        args[i++] = strdup(arg);  // Allocate memory for each argument
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

// ==================== Built-in Command Handlers ====================

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

// ================== External Command Execution ==================

/** Executes external commands */
void handle_external(const char *input) {
    char **args = parse_args(input);
    char *path = find_executable(args[0]);

    if (path) {
        pid_t pid = fork();
        if (pid == 0) {
            // In child process
            execvp(path, args);
            perror(RED "Execution failed" RESET);  // If execvp fails
            exit(EXIT_FAILURE);
        } else if (pid > 0) {
            // In parent process
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

// ===================== Command Dispatcher =====================

/** Dispatches commands to the appropriate handlers */
void dispatch_command(const char *input) {
    // Define built-in commands
    Command commands[] = {
        {"echo", handle_echo},
        {"type", handle_type},
        {"exit", handle_exit},
        {"pwd", handle_pwd},
        {NULL, NULL}  // Sentinel
    };

    // Check if the input matches a built-in command
    for (int i = 0; commands[i].name != NULL; ++i) {
        if (strncmp(input, commands[i].name, strlen(commands[i].name)) == 0) {
            commands[i].handler(input);
            return;
        }
    }

    // Handle external commands
    handle_external(input);
}

// ======================== Main Loop ========================

int main() {
    char input[100];

    while (1) {
        printf("$ ");
        fflush(stdout);

        if (fgets(input, sizeof(input), stdin) == NULL) {
            break;  // Exit on EOF (Ctrl+D)
        }

        input[strcspn(input, "\n")] = '\0';  // Remove newline
        dispatch_command(input);
    }

    return 0;
}

