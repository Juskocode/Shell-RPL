# ifndef COMMANDS_H
#define COMMANDS_H

#include <stdlib.h>
#include <string.h>


// Command Handler Function Pointer
typedef void (*command_handler)(const char *input);

// Command Structure
typedef struct {
    const char *name;
    command_handler handler;
} Command;

void dispatch_command(const char *input);

#endif
