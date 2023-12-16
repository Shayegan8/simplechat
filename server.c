#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "errori.h"
#include <stdbool.h>

void server(int argc, char * argv[])
{  
    int sock, newsock, port, io;
    socklen_t clength;
    char buffer[1024];

    struct sockaddr_in serv_addr, cli_addr;

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if(sock < 0)
      error_log(EXIT_FAILURE, "Cant open the socket");

    port = atoi(argv[3]);

    bzero((struct sockaddr *) &serv_addr, sizeof(serv_addr)); // it dosen't need but we need it :flushed:
    
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(port);
    
    if(bind(sock, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
      error_log(EXIT_FAILURE, "cant bind >:( so fuck you");
    
    listen(sock, 20); // Minecraft server?

    clength = sizeof(cli_addr);
    newsock = accept(sock, (struct sockaddr *) &cli_addr, &clength);
    
    while(1)
    {
      memset(buffer, '\0', 1024);
      io = read(sock, buffer, 1024);
      if(io < 0)
        error_log(EXIT_FAILURE, "Cant read");
      fprintf(stdout, "%s", buffer);
      
      if(strcmp(buffer, "exit") == 0)
      {
        char * strsplit = strtok(buffer, " ");
        FILE * bStrm = fopen(sock, "w");
        fprintf(bStrm , "%s lefted", strsplit);
        fflush(bStrm);
        memset(strsplit, '\0', sizeof(&strsplit));
      }
      
      memset(buffer, '\0', 1024);
      fgets(buffer, 1024, stdin);

      fprintf(stdout, "broadcast %s ", argv[4]);
      io = write(sock, buffer, strlen(buffer));
      if(strcmp(buffer, "end") == 0)
      {
        char str[] = "server stopped";
        write(sock, str, sizeof(str));
        break;
      }
  }  
}