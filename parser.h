#pragma once

#include <stdio.h>
#include <stdlib.h>

#define MAX_COMMAND 1024

char** parse_command(char* command);
void free_tokens(char** tokens);
int is_separator(char c); 

