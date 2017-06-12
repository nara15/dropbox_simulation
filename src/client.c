
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>

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
 * Realiza la inicialización del lado del cliente.
 * 
 **/
int init_client(char *hostname)
{
    int soc ;
    
    soc = connect_to_server(hostname) ;
    
    if (soc < 0)
    {
        printf("No se pudo conectar al servidor\n") ; 
    }
    
    return 0 ;
}