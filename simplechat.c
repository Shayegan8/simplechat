#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "server.h"
#include "client.h"

int main(int argc, char * argv[])
{

  if(strcmp(argv[1], "client") == 0)
    client(argc, argv);
   else if(strcmp(argv[1], "server" == 0))
    server(argc, argv);
    
  return EXIT_SUCCESS;
}