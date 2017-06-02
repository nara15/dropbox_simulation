
#include "array.h"


void initArray(Array *a, size_t initSize)
{
    a->array = (file_data *)malloc(initSize * sizeof(file_data));
    a->used = 0;
    a->size = initSize;
}

void freeArray(Array *a)
{
    free(a->array);
    a->array = NULL;
    a->used = a->size = 0;
}

void insertArray(Array *a, file_data element)
{
    if (a->used == a->size)
    {
        a->size *= 2;
        a->array = (file_data *)realloc(a->array, a->size * sizeof(file_data));
    }
    a->array[a->used++] = element;
}



void saveToFile(char *filename, Array *a)
{
    FILE *ofp = fopen(filename, "wb");
    if (ofp != 0)
    {
        if (fwrite(a->array, a->size * sizeof(file_data), 1, ofp) != 1)
        {
            fprintf(stderr, "Failed to write to %s\n", filename);
            exit(1);
        }
        fclose(ofp);
    }
}

void readFromFile(char *filename, Array * a)
{
    FILE *ifp = fopen(filename, "rb");
    if (ifp != 0)
    {
        if (fread(a->array, a->size * sizeof(file_data), 1, ifp) != 1)
        {
            fprintf(stderr, "Failed to read from %s\n", filename);
            exit(1);
        }
        fclose(ifp);
    }
}
