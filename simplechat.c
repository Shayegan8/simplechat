#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "server.h"
#include "client.h"

int main(int argc, char * argv[])
{
  if(argc < 3)
    error_log(EXIT_FAILURE, "Bad arguments >:( , use chat -h or chat --help");

  if(argc == 0)
    error_log(EXIT_SUCCESS, "No arguments inserted, nothing to do, use chat -h or chat --help");

  int i = 2;
  bool condition;
  while(argv[i] != NULL)
  { 
    if(strcmp(argv[i], "-h") == 0)
    {
      condition = strcmp(argv[i], "-h") == 0 ? 1 : 0;
      break;
    }
    else if(strcmp(argv[i], "--help"))
    {
      condition = strcmp(argv[i], "--help") == 0 ? 1 : 0;
      break;
    }
    i++;
  }

  i = 0;
  
  if(condition == 1)
    error_log(EXIT_FAILURE, "Usage: chat \"server/client\" \"hostname\" \"port\" \"username\" "); 

  if(strcmp(argv[1], "client") == 0)
    client(argc, argv);
  else if(strcmp(argv[1], "server") == 0)
    server(argc, argv);
    
  return EXIT_SUCCESS;
}