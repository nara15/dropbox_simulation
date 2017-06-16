
#include "structs.h"

#include <string.h>
#include <sys/stat.h>
#include <dirent.h>

int in_set( Array *a, int len,  char *match);
void diff(Array *x, int lenx, Array *y, int leny, Array *res);
void diffModified(Array *x, int lenx, Array *y, int leny, Array *res);

/**
 *  Determina si un elemento se encuentra en un listado de directorio
 **/
int in_set( Array *a, int len,  char *match)
{
    int i = 0, j = len - 1, ret ;
    while (i <= j)
    {
        int k = (i + j) / 2;
        ret = strcmp(a -> array[k].name, match);
        if (ret > 0)
        {
            j = k - 1;
        } else if (ret < 0)
        {
            i = k + 1;
        }
        else
        {
            return 1;
        }
    }
    return 0;
}

/**
 * Realiza la diferencia entre el listado de dos directorios.
 **/
void diff(Array *x, int lenx, Array *y, int leny, Array *res)
{
    int i;
	for (i = 0; i < lenx; i++)
	{
		if (x->array[i].name && !in_set(y, leny, x->array[i].name)) insertArray(res, x->array[i] );//printf("  archivo -> %s\n", x->array[i].name);
	}
}

/**
 * Realiza la búsqueda de los archivos que ha sido modificados.
 * Compara el listado actual del directorio y el listado anterior
 **/
 void diffModified(Array *x, int lenx, Array *y, int leny, Array *res)
 {
    int i = 0, j = 0, ret ;
    
    while (i < lenx && j < leny)
    {
        ret = strcmp(x -> array[i].name, y -> array[j].name);
        
        if (ret < 0) i ++;
        else if (ret > 0) j ++;
        else
        {
            time_t t1 = x -> array[i].modification_time, t2 = y -> array[j].modification_time ;
            if ( t1 < t2) // t1 es más antiguo que t2;
            {
                insertArray(res, y -> array[j++] );//printf("%s\n", y -> array[j++].name);
            }
            else if ( t1 > t2 ) // t1 es más nuevo que t2
            {
                
            }
            i ++;  
        }
        
    }
 }



// =============================================================================
/**
 * Esta función escanea la lista de archivos obtenidas en scandir y las almacena
 * en la estructura <<file_data>>
 * @Param: files : puntero a un arreglo de archivos.
 * @Param: namelist : puntero al resultado de la función scandir.
 * @Param: n : cantidad de archivos por leer.
 * @Return: None
 **/
void scanFilesFromDirectory(Array *files, struct dirent **namelist, int n, char *directory)
{
    struct stat statBuffer;
    int i = 0;
    
    while (i < n)
    {
        char src[50];
        strcpy(src,  directory);
        strcat(src, namelist[i] -> d_name);
        
        if (stat(src, &statBuffer) != -1) 
        {
            file_data file;
            strcpy( file.name, namelist[i] -> d_name);
            strcpy( file.path, src) ;
            file.modification_time = statBuffer.st_mtime;
            file.size = statBuffer.st_size;
            insertArray(files, file);
        }
        
        free(namelist[i]);
        i ++;
    }
    free(namelist);
    
}

/**
 * Escribe la cantidad de archivos del directorio, en un archivo 
 * @param : filename : nombre del archivo
 * @param : n : cantidad por escribir en el archivo
 **/
void writeFileNumber(char * filename, int n)
{
    FILE *in = fopen(filename, "w");
    fprintf(in, "%i\n", n); 
    fclose(in);
}

/**
 * Obtiene la cantidad de archivos en un directorio, en tiempo dado, del archivo
 * @param : filename : nombre del archivo 
 * @return : la catidad de archivos - 0 si no existe el archivo.
 **/
int readFileCount(char *filename)
{
    int n;
    FILE *in = fopen(filename, "r");
    if (in != NULL)
    {
        fscanf(in, "%i", &n); 
        fclose(in);
        return n; 
    }
    return 0 ; 
}