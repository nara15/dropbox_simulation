#ifndef STRUCTS_H_
#define STRUCTS_H_

#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>


#include <stdlib.h>
#include <stdio.h>

//  ESTRUCTURAS ================================================================

typedef struct
{
    char name[1000];
    char path[2000];
    int size;
    time_t modification_time;
} file_data;

struct sync_file_message 
{
	char filename[1000];
	time_t mtime;
	int size;
	unsigned char fileBuff[1024];
} ;

struct sync_message 
{
    char message[1000];
    char name[1000];
    time_t mtime ;
    int size ;
    int empty_directory ;
    int deleted_file ;
    int modified_file ;
    int added_file ;
} ;

typedef struct
{
    file_data *array;
    size_t used;
    size_t size;
} Array;


//  FUNCIONES ==================================================================

void initArray(Array *a, size_t initSize);
void freeArray(Array *a);
void insertArray(Array *a, file_data element);
int findArray(Array *a, int n, char* file_name) ;

void createMeta();
void createDirectory(char *name);


int filter(const struct dirent * dir);
void saveToFile(char *filename, Array *a);
void readFromFile(char *filename, Array * a);



#endif  /* STRUCTS_H_ */