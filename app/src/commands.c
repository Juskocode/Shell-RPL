#include "commands.h"
#include "handlers.h"
#include "envcp.h"

/** Dispatches commands to the appropriate handlers */
void dispatch_command(const char *input) {
    Command commands[] = {
        {"echo", handle_echo},
        {"type", handle_type},
        {"exit", handle_exit},
        {"cd", handle_cd},
        {"pwd", handle_pwd},
        {NULL, NULL}
    };

    for (int i = 0; commands[i].name != NULL; ++i) {
        if (strncmp(input, commands[i].name, strlen(commands[i].name)) == 0) {
            commands[i].handler(input);
            return;
        }
    }

    handle_external(input);
}
