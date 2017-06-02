
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
    
  /*
    struct dirent **namelist;
    int n;
    n = scandir(".", &namelist, &filter, alphasort);
    initArray(&files, n);
    scanFilesFromDirectory(&files, namelist, n);
    printf("%s %i\n", files.array[0].name, files.array[0].size);
    printf("%s %i\n", files.array[1].name, files.array[1].size);
    printf("%s %i\n", files.array[2].name, files.array[2].size);
    printf("%s %i\n", files.array[3].name, files.array[3].size);
    printf("%s %i\n", files.array[4].name, files.array[4].size);
    printf("%s %i\n", files.array[5].name, files.array[5].size);
    saveToFile(".meta/files_data.bin", &files);
 */   
    
  
    initArray(&files, 6);
    readFromFile(".meta/files_data.bin", &files);
    printf("%s %i %i\n", files.array[0].name, files.array[0].size, files.array[0].modification_time_data.year);
    printf("%s %i %i\n", files.array[1].name, files.array[0].size, files.array[0].modification_time_data.year);
    printf("%s %i %i\n", files.array[2].name, files.array[0].size, files.array[0].modification_time_data.year);
    printf("%s %i %i\n", files.array[3].name, files.array[0].size, files.array[0].modification_time_data.year);
    printf("%s %i %i\n", files.array[4].name, files.array[0].size, files.array[0].modification_time_data.year);
    printf("%s %i %i\n", files.array[5].name, files.array[0].size, files.array[0].modification_time_data.year);
  
    
    
    freeArray(&files);
   
}