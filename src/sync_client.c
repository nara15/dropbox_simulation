
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>


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
                fprintf(stderr, "Usage: dbclient -h <server hostname> -d <directory>\n");
                exit(1);
        }
    }
    
    //  Decide roll
	if(!host && dir) 
	{
	    printf("This is ther server\n");
		printf("The directory is: %s\n", dir);
	} else if (host && dir)
	{
	    printf("This is the client\n");
	    printf("The directory is: %s , and the server is: %s\n", dir, host);
	}
	else
	{
	    fprintf(stderr, "Bad option\n");
	    exit(1);
	}
	
    
}