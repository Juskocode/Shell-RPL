#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#define RESET   "\x1b[0m"
#define GREEN   "\x1b[32m"
#define BLUE    "\x1b[34m"
#define YELLOW  "\x1b[33m"
#define RED     "\x1b[31m"

int check_exec(const char *path) {
	return access(path, X_OK) == 0;
}

char* handle_path(const char *file) {
	char *path_env = getenv("PATH");
	if (!path_env)
		return NULL;

	char *path_copy = strdup(path_env);
	char *dir = strtok(path_copy, ":");
	static char full_path[1024];

	while (dir != NULL) {
		
		//strjoin path + file into fullpath
		snprintf(full_path, sizeof(full_path), "%s/%s", dir, file);
		if (check_exec(full_path)) {
			free(path_copy);
			return full_path;
		}
		//check next dir
		dir = strtok(NULL, ":");
	}
	free(path_copy);
	return NULL;
}

void execute_echo(const char *input) {
    printf(GREEN "%s\n" RESET, input);
}

void execute_type(const char *input) {
    if (!strncmp(input + 5, "echo", 4)) {
        printf(BLUE "echo " GREEN "is a shell builtin\n" RESET);
    } else if (!strncmp(input + 5, "exit", 4)) {
        printf(BLUE "exit " GREEN "is a shell builtin\n" RESET);
    } else if (!strncmp(input + 5, "type", 4)) {
        printf(BLUE "type " GREEN "is a shell builtin\n" RESET);
    }
    else {
	char* path = handle_path(input + 5);
	if (path)
		printf(GREEN"%s"RESET " is " YELLOW "%s\n" RESET, input + 5, path);
	else
        	printf(RED "%s: not found\n" RESET, input + 5);
    }
}

void execute_exit() {
    exit(0);
}

void handle_command(const char *input) {
    if (!strcmp(input, "exit 0")) {
        execute_exit();
    } else if (!strncmp(input, "echo ", 5)) {
        execute_echo(input + 5);
    } else if (!strncmp(input, "type ", 5)) {
        execute_type(input);
    } else {
        printf(RED "%s: not found\n" RESET, input);
    }
}

int main() {
    char input[100];

    while (1) {
        printf("$ ");
        fflush(stdout);

        fgets(input, 100, stdin);

        input[strlen(input) - 1] = '\0';  // Remove newline
        handle_command(input);
    }
    
    return 0;
}

