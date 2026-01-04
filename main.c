#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "parser.h"
#include "execute.h"


void repl(char **env)
{
  char *command = NULL;
  size_t command_size = 0;
  ssize_t n_read; 

  char **args;
  char* initial_directory = getcwd(NULL, 0);

  while (1)
  {
    // Comprueba si es un descriptor de archivo, en este caso, la entrada estandar, esta conectado a una terminal interactiva
    if (isatty(STDIN_FILENO)) { 
      printf("dav_sh $> ");
      fflush(stdout);
    }
   
    n_read = getline(&command, &command_size, stdin);
    if (n_read == -1)
    {
      if (feof(stdin)) {
        // El usuario ha pulsado Ctrl+D. Salimos limpiamente
        if (isatty(STDIN_FILENO))
          printf("\n");
        break;
      }
      else {
        // Error de lectura
        perror("getline");
        break;
      }
    }

    args = parse_command(command);

    for(int i = 0; args[i]; i++) {
      printf("Arg[%i] -> %s", i, args[i]);
      printf("\n");
    }

    if (args[0])   
    {
      built_ins(args, env, initial_directory);
    }

  }

  free_tokens(args);

  if (command)
    free(command);
}


int main(int argc, char **argv, char **env)   // env es una lista CLAVE=VALOR que representa las variables del entorno
{
  (void)argc;
  (void)argv;

  repl(env);
  return EXIT_SUCCESS;
}
