#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
  char *comando = NULL;
  size_t len_comando = 0;
  size_t leidos;

  while(1)
  {
    char *token;
    char *args[64];
    int posicion_token = 0;

    printf("dav_shell$> ");

    leidos = getline(&comando, &len_comando, stdin);
    if (leidos == -1) {
      printf("\nSaliendo...\n");
      break;
    }

    if (leidos > 0 && comando[leidos - 1] == '\n')
      comando[leidos - 1] = '\0';

    if (strcmp(comando, "exit") == 0)
      break;

    // printf("%s", comando);
    token = strtok(comando, " ");
    while(token != NULL) {
      args[posicion_token++] = token;
      token = strtok(NULL, " ");
    }

    args[posicion_token] = NULL;

    for(int i = 0; i < posicion_token + 1; i++)
      printf("args[%i]=%s ",i, args[i]);

    printf("\n");
  }

  free(comando);
  return 0;
}
