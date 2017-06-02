
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
	//Sanitize inputs.
	if(!host || !dir) {
		fprintf(stderr, "Usage: dbclient -h <server hostname> -d <directory>\n");
		exit(1);
	}
	
	printf("%s\n", dir);
    
}