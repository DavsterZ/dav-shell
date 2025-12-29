#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

#define COLOR_AZUL "\x1b[34m"
#define COLOR_RESET "\x1b[0m"


/**
 * LECTURA
 * Lee una linea completa desde stdin
 * Usamos getline porque gestiona la memoria dinamica automaticamente
**/
char *read_line(void)
{
  char *comando = NULL;
  size_t len_comando = 0;
  
  if (getline(&comando, &len_comando, stdin) == -1)
   if (feof(stdin)) {
    // EOF -> Ha sido presionado Ctrl+D
    free(comando);
    exit(EXIT_SUCCESS);
   } 
   else {
    perror("Error leyendo la linea");
    exit(EXIT_FAILURE);
   }

  return comando;
}

/**
 * PARSING
 * Divide la linea en tokens
 * Retorna un array de strings terminando en NULL
**/
char **split_line(char *line)
{
  int bufsize = 64;
  int posicion = 0;
  char **tokens = malloc(bufsize * sizeof(char*));
  char *token;

  if (!tokens) {
    fprintf(stderr, "Error de asignacion de memoria\n");
    exit(EXIT_FAILURE);
  }

  token = strtok(line, " \t\r\n\a");
  while (token != NULL)
  {
    tokens[posicion] = token;
    posicion++;

    // Si superamos el buffer, hacemos realloc para dar mas memoria
    if (posicion >= bufsize) 
    {
      bufsize += 64;
      tokens = realloc(tokens, bufsize * sizeof(char*));

      if (!tokens) {
        fprintf(stderr, "Error de asignacion de memoria\n");
        exit(EXIT_FAILURE);
      }
    }

    token = strtok(NULL, " \t\r\n\a");
  }

  tokens[posicion] = NULL; // Super importante para despues el comando execvp
  return tokens;
}

/**
 * LANZAR PROCESOS
 * Ejecuta comandos externos (ls, grep, ...)
**/
int launch_external(char **args)
{
  pid_t pid;
  int status;

  pid = fork();
  if (pid == 0) {
    // PROCESO HIJO
    // Configuramos la senial para que el hijo si responda a Ctrl+C
    signal(SIGINT, SIG_DFL);

    if (execvp(args[0], args) == -1)
      perror("dav_shell");
  
    exit(EXIT_FAILURE);
  }
  else if (pid < 0)
    // ERROR en el FORK
    perror("dav_shell");
  else {
    // PROCESO PADRE
    do {
      // Espera hasta que el hijo cambio de estado (termine o sea parado)
      waitpid(pid, &status, WUNTRACED);
    } while (!WIFEXITED(status) && !WIFSIGNALED(status));
  }

  return 1;
}

/**
 * BUILT-INS
 * Ejecuta comandos propios de la shell como cd, exit, help
**/
int execute(char **args)
{
  if (args[0] == NULL)
    return 1;

  // Implementar 'cd'
  if (strcmp(args[0], "cd") == 0) {
    if (args[1] == NULL)
      fprintf(stderr, "dav_shell: se esperaba un argumento para \"cd\"\n");
    else
      if (chdir(args[1]) != 0)
        perror("dav_shell");

    return 1;
  }

  // Implementacion 'exit'
  if (strcmp(args[0], "exit") == 0)
    return 0;

  // Implementación de 'help' (Opcional pero pro)
  if (strcmp(args[0], "help") == 0) {
    printf("Dav Shell v1.0\n");
    printf("Usa comandos estándar de Linux.\n");
    printf("Built-ins: cd, exit, help\n");
    return 1;
  }

  // Si no es built-in, lanzamos el binario extremo
  return launch_external(args);
}

// Orquestador Principal
int main(int argc, char *argv[])
{
  char *line;
  char **args;
  int status = 1;

  // Ignorar Ctrl+C en el shell principal
  signal(SIGINT, SIG_IGN);

  while(status)
  {
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) != NULL)
      printf("%s%s%s %% ", COLOR_AZUL, cwd, COLOR_RESET);
    else
      printf("dav_shell%% ");

    line = read_line();
    args = split_line(line);
    status = execute(args);   // Status decide si seguimos (1) o salimos (0)

    free(line);
    free(args);
  }

  return 0;
}
