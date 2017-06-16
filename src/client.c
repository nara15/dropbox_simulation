
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>

#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "structs.h"

//  PROTOTIPOS DE LAS FUNCIONES POR USAR
void get_file(int soc, struct sync_file_message received_packet, int filesize) ;
void send_file(int soc, char* filename, int size) ;
void Writen(int fd, void *ptr, size_t nbytes) ;
ssize_t Readn(int fd, void *ptr, size_t nbytes) ;

void scanFilesFromDirectory(Array *files, struct dirent **namelist, int n, char *directory) ;
void writeFileNumber(char * filename, int n) ;







/**
 * Crea un socket e intenta conectarse al servidor por medio del hostname.
 * @Param : hostname : String - Nombre del host por conectarse
 * @Return : el indentificador del socket, al cuál se realizó la conexión.
 **/
int connect_to_server(char *hostname)
{
    int sock ;
    struct sockaddr_in server;
    
    //  Crear el socket
    sock = socket(AF_INET, SOCK_STREAM, 0) ;
    if (sock == -1) return -1 ;
    
    server.sin_addr.s_addr = inet_addr(hostname);
    server.sin_family = AF_INET;
    server.sin_port = htons( 8888 );
    
    //  Conectarse al servidor
    if (connect(sock , (struct sockaddr *)&server , sizeof(server)) < 0) 
    {
        printf("Error de conexión\n") ;
        return -1 ;
    }
    
    return sock ;
}

/**
 * Obtiene los archivos actuales del directorio. Se verifica si ya existe un
 * archivo de metadata con datos de archivos anteriores almacenados.
 **/
void get_directory_files(char *directory, Array *files)
{
    if( access( ".meta/files_data.bin", F_OK ) != -1 ) 
    {
        printf("hay archivos registrados\n");
    } 
    else 
    {
        struct dirent **namelist;
        int n;
        n = scandir(directory, &namelist, &filter, alphasort);
        initArray(files, n);
        scanFilesFromDirectory(files, namelist, n, directory);
        saveToFile(".meta/files_data.bin", files);
        writeFileNumber(".meta/count.bin", n); 
    }
}
/**
 * Realiza la inicialización del lado del cliente.
 * 
 **/
int init_client(char *hostname, char *directory)
{
    int sock ;
    
    sock = connect_to_server(hostname) ;
    
    if (sock < 0)
    {
        printf("No se pudo conectar al servidor\n") ; 
    }
    printf("El cliente se conectó\n") ;


    Array files ;
    
    struct sync_message handshake ;
    struct sync_message response;
    strncpy(handshake.message, "Sincronizar archivos", 900);
    
    Writen(sock, &handshake, sizeof(handshake)) ;
    
    int n = Readn(sock, &response, sizeof(response)) ;
    
    if (n > 0 && response.empty_directory == 1)
    {
        printf("Se leyó %i y se debería enviar archivos\n",response.empty_directory) ; 
        
        char *names[] = {"feo.txt", "feo1.txt", "feo2.txt", "scotch.jpg"} ;
        struct stat fileStat;
        
        get_directory_files(directory, &files) ;
        
       
        
        int i;
        for (i = 0; i < files.size; i++)
        {
            if(stat(files.array[i].path, &fileStat) == 0) 
            {

                struct sync_file_message m;
                m.size = fileStat.st_size;
                strncpy(m.filename, files.array[i].name, 1000);
                
                //  Enviar datos básicos sobre el archivo antes - nombre y tamaño
                Writen(sock, &m, sizeof(m));
                
                
                //  Se envía el contenido del archivo al servidor
                send_file(sock, files.array[i].path, fileStat.st_size); 
                
            }
            

        }
        
        /*
        int i;
        for (i = 0; i < 4; i++)
        {
            if(stat(names[i],&fileStat) < 0) return 1;
            struct sync_file_message m;
            m.size = fileStat.st_size;
            strncpy(m.filename, names[i], 1000);
            
            //  Enviar datos básicos sobre el archivo antes - nombre y tamaño
            Writen(sock, &m, sizeof(m));
            
            //  Se envía el contenido del archivo al servidor
            send_file(sock, names[i], fileStat.st_size);

        }*/
    }
    
    close(sock) ;
    freeArray(&files);
    
    return 0 ;
}