#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <stdbool.h>
#include <string.h>
#include "errori.h"
#include <netdb.h>

/**
  @args "server/client" "hostname" "port" "name"
*/
int client(int argc, char * argv[])
{

  int sock, port, io;
  struct sockaddr_in serv_addr;
  struct hostent *server;

  port = atoi(argv[3]);
  sock = socket(AF_INET, SOCK_STREAM, 0); //establishing tcp connection
  
  if(sock < 0)
    error_log(EXIT_FAILURE, "Can't open socket");
  server = gethostbyname(argv[2]);
  
  if(server = NULL)
  {
    error_log(1, "no such a host");
    log_inf("Couldn't found host", "i complete it in tommorow");
  }
  memset((char *) &serv_addr, '\0', sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  bcopy((char *) server->h_addr, (char *) &serv_addr.sin_addr.s_addr , server->h_length);
  serv_addr.sin_port = htons(port);
  
  if(connect(sock, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
    error_log(1, "failed to connect");

  char buffer[1024];
  char * split_user;
  while(EXIT_FAILURE)
  {
    
    memset(buffer, '\0', sizeof(buffer));
    io = write(sock, buffer, strlen(buffer));
    
    if(io < 0)
      error_log(1, "failed to write on stream");
    
    if(strcmp(buffer, "exit") == 0)
    {
      fprintf(stdout, "Bye!");
      break;
    }
    
    memset(buffer, '\0', sizeof(buffer));
    io = read(sock, buffer, 1024);
    
    if(io < 0)
      error_log(1, "failed to read from stream");
    
    split_user = strtok(buffer, " ");
     
    fprintf(stdout, "%s %s %s", split_user, argv[4], buffer);
  }
}