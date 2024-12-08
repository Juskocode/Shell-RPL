#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define RESET   "\x1b[0m"
#define GREEN   "\x1b[32m"
#define BLUE    "\x1b[34m"
#define YELLOW  "\x1b[33m"
#define RED     "\x1b[31m"

void execute_echo(char *input) {
    printf(GREEN "%s\n" RESET, input);
}

void execute_type(char *input) {
    if (!strncmp(input + 5, "echo", 4)) {
        printf(BLUE "echo " GREEN "is a shell builtin\n" RESET);
    } else if (!strncmp(input + 5, "exit", 4)) {
        printf(BLUE "exit " GREEN "is a shell builtin\n" RESET);
    } else if (!strncmp(input + 5, "type", 4)) {
        printf(BLUE "type " GREEN "is a shell builtin\n" RESET);
    }
    else {
        printf(RED "%s: not found\n" RESET, input + 5);
    }
}

void execute_exit() {
    exit(0);
}

void handle_command(char *input) {
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

