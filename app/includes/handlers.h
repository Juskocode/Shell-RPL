#ifndef HANDLERS_H
#define HANDLERS_H

#include "colors.h"
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <unistd.h>

#define MAX_CWD_SIZE 1024

void handle_exit();

void handle_echo(const char *input);

void handle_type(const char *input);

void handle_pwd();

void handle_cd(const char *input);


#endif
