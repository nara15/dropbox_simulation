
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>

#include <dirent.h>

#include "structs.h"

//  PROTOTIPOS DE LAS FUNCIONES POR USAR
void get_file(int soc, struct sync_file_message received_packet, int filesize) ;
void send_file(int soc, char* filename, int size) ;
void Writen(int fd, void *ptr, size_t nbytes) ;
ssize_t Readn(int fd, void *ptr, size_t nbytes) ;

int readFileCount(char *filename) ;



int filter(const struct dirent * dir)
{
    //struct stat st;
    //stat(dir->d_name, &st);
    
    const char *s = dir -> d_name;
    if (s[0] == '.') return 0;
    //else if (st.st_mode & S_IFDIR) return 0 ;
    return 1;
}

/**
 * Configura el socket del servidor. Crea y asocia el socket a un puerto.
 * @return: listenfd (descriptot del socket) donde se está escuchando al cliente
 **/
int setup()
{
    int socket_descriptor ;
    struct sockaddr_in server ;
    
    //  Crear el socket 
    socket_descriptor = socket(AF_INET, SOCK_STREAM , 0) ;
    if (socket_descriptor == -1) return socket_descriptor ;
    
    //  Preparar la estructura sockaddr_in
    server.sin_family = AF_INET ;
    server.sin_addr.s_addr = INADDR_ANY ;
    server.sin_port = htons ( 8888 ) ;
    
    //  Ligar
    if( bind(socket_descriptor,(struct sockaddr *)&server, sizeof(server)) < 0)
    {
        return -1 ;
    }
    
    //  Escuchar
    listen(socket_descriptor , 3) ;
    
    return socket_descriptor ;
}

/**
 * Esta función recibe un conjunto de archivos.
 * Se debe ejecutar en caso del directorio actual vacío y se debe recibir multiples archivos
 * @param : client_socket : socket con la conexíon al cliente.
 **/
void receive_all_files(int client_socket)
{
    int filesize ;
    struct sync_file_message received_packet ;
    for (; ;)
    {
        int n = Readn(client_socket, &received_packet, sizeof(received_packet));

        if (n > 0)
        {
            printf("Nombre del archivo %s y su tamaño %i \n", received_packet.filename, received_packet.size) ;
            filesize = received_packet.size ;
        }
        else if (n == 0)
        {
            puts("Cliente desconectado");
	        fflush(stdout);
	        break;
        }
        
        get_file(client_socket, received_packet, filesize) ; 
        
    }
}


/**
 * Realiza la inicialización del lado del servidor.
 * 
 **/
int init_server()
{
    int client_socket , c ;
    struct sockaddr_in client ;
    int socket_desc = setup() ;
    
    if (socket_desc < 0)
    {
        perror ("No se pudo crear el socket del server") ;
        return -1 ;
    }
    else
    {
        printf("¡Hola!, soy el server esperando por conexiones \n") ;
        c = sizeof(struct sockaddr_in) ;
        client_socket = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c) ;
        if (client_socket < 0)
        {
            perror("No se pudo aceptar al cliente") ;
            return -1 ;
        }
        printf("Conexión aceptada \n") ;
        
        struct sync_message handshake , response ;
       
        int n = Readn(client_socket, &handshake, sizeof(handshake)) ;
        int cant_files = 0 ;
        if (n > 0)
        {
            cant_files = readFileCount(".meta/count.bin");
 
            if (cant_files == 0) response.empty_directory = 1 ;
            else response.empty_directory = 0 ;
 
            Writen(client_socket, &response, sizeof(response));
        }
        
        if (cant_files == 0) receive_all_files(client_socket) ;
    
        close(client_socket) ;
        
        return 0 ;
    }
}