#include "errori.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#define RED "\033[0;31m"
#define RESET "\033[0;m"

void error_log(int i, char * msg)
{
	printf("%s%s%s\n", RED, msg, RESET);
	exit(i);
}

void log_inf(char * msg)
{
	FILE * wF = fopen("/usr/local/share/simplechat/latest.log", "a+");
	time_t outime;
	struct tm * tinfo;
	tinfo = localtime(&outime);
	
	fprintf(wF,"%s %s\n", asctime(tinfo) , msg);
}
