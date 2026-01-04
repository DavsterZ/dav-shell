#include "execute.h"

/*
int command_cd(char** args, char* initial_directory)
{

}
int command_pwd()
{

}
int command_echo(char** args, char** env)
{

}
int command_env(char** env)
{

}
int command_which(char** args, char** env)
{

}
*/

int built_ins(char** args, char** env, char* initial_directory)
{
  (void) env;
  (void) initial_directory;
  
  if (utils_strcmp(args[0], "cd") == 0) {
    //return command_cd(args, initial_directory);
  }
  else if (utils_strcmp(args[0], "pwd") == 0) {
    //return command_pwd();
  }
  else if (utils_strcmp(args[0], "echo") == 0) {
    //return command_echo(args, env);
  }
  else if (utils_strcmp(args[0], "env") == 0) {
    //return command_env(env);
  }
  else if (utils_strcmp(args[0], "which") == 0) {
    //return command_which(args, env);
  }
  else if ((utils_strcmp(args[0], "exit") == 0) || (utils_strcmp(args[0], "quit") == 0)) {
    exit(EXIT_SUCCESS);
  }
  else {
    // Not a built-in command
  }
  
  return 0;
}
