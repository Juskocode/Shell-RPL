#include "handlers.h"
#include "commands.h"
#include <limits.h>

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
//       	tokenize(input); 
	dispatch_command(input);
    }

    return 0;
}

