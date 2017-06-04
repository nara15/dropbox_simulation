
#include <time.h>
#include <langinfo.h>

#include <string.h>
#include <sys/stat.h>
#include <dirent.h>


#include "array.h"

int filter(const struct dirent * dir)
{
    const char *s = dir -> d_name;
    if (s[0] == '.') return 0;
    return 1;
}
void writeFileNumber(char * filename, int n)
{
    FILE *in = fopen(filename, "w");
    fprintf(in, "%i\n", n); 
}
int readFileCount(char *filename)
{
    int n;
    FILE *in = fopen(filename, "r");
    fscanf(in, "%i", &n); 
    return n;
}
void scanFilesFromDirectory(Array *files, struct dirent **namelist, int n)
{
    struct stat statBuffer;
    struct tm *tm;
    int i = 0;
    
    while (i < n)
    {
        if (stat(namelist[i] -> d_name, &statBuffer) == -1) continue;
        
        file_data file;
        strcpy( file.name, namelist[i] -> d_name);
        tm = localtime(&statBuffer.st_mtime);
        file.modification_time_data.sec = tm -> tm_sec;
        file.modification_time_data.min = tm -> tm_min;
        file.modification_time_data.hour = tm -> tm_hour;
        file.modification_time_data.date = tm -> tm_mday;
        file.modification_time_data.month = tm -> tm_mon;
        file.modification_time_data.year = tm -> tm_year;
        file.size = statBuffer.st_size;
        insertArray(files, file);
        
        free(namelist[i]);
        
        i ++;
    }
    free(namelist);
    printf("%i\n", n);
}

int main(void)
{
    Array files;
    Array current_files;
    
 /* 
    struct dirent **namelist;
    int n;
    n = scandir(".", &namelist, &filter, alphasort);
    initArray(&files, n);
    scanFilesFromDirectory(&files, namelist, n);
    saveToFile(".meta/files_data.bin", &files);
    writeFileNumber(".meta/count.bin", n); 
    */
  
  
  
    //  Listado anterior  
    int n = readFileCount(".meta/count.bin");
    initArray(&files, n);
    readFromFile(".meta/files_data.bin", &files);
    
    
    struct dirent **namelist;
    int np;
    np = scandir(".", &namelist, &filter, alphasort);
    initArray(&current_files, np);
    scanFilesFromDirectory(&current_files, namelist, np);
    

    int i;
    for (i = 0; i < n; i++)
    {
        printf("%s %i %i\n", files.array[i].name, files.array[i].size, files.array[i].modification_time_data.year);
    }
    printf(" Actualmente hay %i archivos ========================================\n", np);
    for (i = 0; i < np; i++)
    {
        printf("%s %i %i\n", current_files.array[i].name, files.array[i].size, files.array[i].modification_time_data.hour);
    }
    
    printf(" Y la diferencia ========================================\n");
    diff(&files, n, &current_files, np);
   
    
    freeArray(&files);
    
    freeArray(&current_files);
   
}