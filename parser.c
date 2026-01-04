#include "parser.h"

int is_separator(char c) {
  return (c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\a');
}

void free_tokens(char** tokens)
{
  if (!tokens)
    return;   

  for (size_t i = 0; tokens[i]; i++)
    free(tokens[i]);                  // Free each token 

  free(tokens); // Free the array of tokens
}

char** parse_command(char* command)
{
  size_t position = 0;
  size_t buffer_size = MAX_COMMAND;
  char** tokens = malloc(buffer_size * sizeof(char*));
  size_t i = 0;

  if (!tokens) {
    perror("malloc");
    exit(EXIT_FAILURE);
  }
  
  while (command[i])
  {
    // If it is a space or separator we don't do nothing
    while (command[i] && is_separator(command[i]))
      i++;

    if (!command[i])
      break;

    // First character character
    char* start = &command[i];
    size_t token_len = 0;

    // Token Len counter
    while(command[i] && !is_separator(command[i])) {
      token_len++;
      i++;
    }
    
    tokens[position] = malloc((token_len + 1) * sizeof(char));
    if (!tokens[position]) {
      perror("malloc");
      exit(EXIT_FAILURE);
    }
    
    for (size_t j = 0; j < token_len; j++)
      tokens[position][j] = start[j];

    tokens[position][token_len] = '\0';
    position++;

    if (position >= buffer_size) {
      fprintf(stderr, "Error: Demasiados argumentos\n");
      exit(EXIT_FAILURE);
    }
  }

  tokens[position] = NULL;
  return tokens;
}
