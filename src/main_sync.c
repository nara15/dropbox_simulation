
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#include "server.c"
#include "client.c"
#include "structs.h"




void actLikeClient(char *directory, char *hostname)
{
    printf("This is the client\n");
	printf("The directory is: %s , and the server is: %s\n", directory, hostname);
    init_client(hostname);
}

void actLikeServer(char *directory)
{
    printf("This is the server\n");
	printf("The directory is: %s\n", directory);
    init_server() ;
}


int main(int argc, char **argv)
{
	char ch;
    char *host = NULL, *dir = NULL;

	 while((ch = getopt(argc, argv, "h:d:")) != -1) {
        switch (ch) 
        {
            case 'h':
                host = optarg;
                break;
            case 'd':
                dir = optarg;
                break;
            default:
                fprintf(stderr, "Uso: CLIENT -> ./program -h <server hostname> -d <directory>\n SERVER -> ./program -d <directory> \n");
                exit(1);
        }
    }
    
    createMeta();
    
    //  Decide roll for the program
	if(!host && dir) 
	{
	    actLikeServer(dir);
	    
	} else if (host && dir)
	{
	    actLikeClient(dir, host) ;
	}
	else
	{
	    fprintf(stderr, "Error \n Uso: CLIENT -> ./program -h <server hostname> -d <directory>\n SERVER -> ./program -d <directory> \n");
	    exit(1);
	}
	
	return 0 ;
	
    
}