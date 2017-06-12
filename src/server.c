
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>


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
        
        return 0 ;
    }
}