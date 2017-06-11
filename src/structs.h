#ifndef STRUCTS_H_
#define STRUCTS_H_

#include <stdlib.h>
#include <stdio.h>

//  ESTRUCTURAS ================================================================

typedef struct
{
    char name[100];
    int size;
    time_t modification_time;

} file_data;

struct sync_message 
{
	char filename[1000];
	long int mtime;
	int size;
	unsigned char fileBuff[1024];
};

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


void saveToFile(char *filename, Array *a);
void readFromFile(char *filename, Array * a);



#endif  /* STRUCTS_H_ */