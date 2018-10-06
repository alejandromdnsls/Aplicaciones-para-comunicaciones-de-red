#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "MensajeError.c"

#define MAXLISTA 5
#define TAMBUFER 2000

void manejadorTCPCliente(int sockCliente);

int main(int argc, char **argv){
	if(argc != 2) //Revisamos el número de argumentos
		mensajeFinalError("Uso: EcoTCPServidor [<puerto>]");
	int prtoServ = atoi(argv[1]);
	
	//Creamos el socket de entrada
	int sockServ;
	if((sockServ = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP)) < 0)
		mensajeFinalError("Fallo la apertura del socket");
	//Se construye la estructura de la dirección
	struct sockaddr_in dirServ;	           //Creamos una estructura para la dirección local
	memset(&dirServ, 0 , sizeof(dirServ));			//Limpiamos la estructura
	dirServ.sin_family = AF_INET;					//Familia de direcciones IPv4
	dirServ.sin_addr.s_addr = htons(INADDR_ANY);	//Cualquier interfaz de entrada
	dirServ.sin_port = htons(prtoServ);				//Número de puerto
	
	//Se enlaza a la dirección local
	if(bind(sockServ, (struct sockaddr*)&dirServ, sizeof(dirServ))< 0)
		mensajeFinalError("Error al enlazar");
		
	//Marcamos el socket para que pueda escuchar conexiones
	if(listen(sockServ, MAXLISTA) < 0)
		mensajeFinalError("Fallo inicio de escucha");
	
	for(;;){//Lazo infinito
		struct sockaddr_in dirCliente;		//Dirección del cliente
		//Obtenemos el tamaño de los datos del cliente
		socklen_t dirClienteTam = sizeof(dirCliente);
        //Esperamos que se conecte el cliente
        int sockCliente = accept(sockServ,(struct sockaddr*)&dirCliente,&dirClienteTam);
        if(sockCliente < 0)
            mensajeFinalError("Fallo la conexión");
        //Se conecto un cliente
        char nombreCliente[INET_ADDRSTRLEN];
        if(inet_ntop(AF_INET,&dirCliente.sin_addr.s_addr,nombreCliente,
                sizeof(nombreCliente)) !=NULL)
            printf("Cliente conectado: %s/%d\n",nombreCliente,ntohs(dirCliente.sin_port));
        else
            puts("Imposible conectar el cliente");
        manejadorTCPCliente(sockCliente);
		
	}	
}

void manejadorTCPCliente(int sockCliente){
    char bufer[TAMBUFER];
        
    //Recibe mensaje del cliente
    ssize_t numBytesRecibidos = recv(sockCliente, bufer, TAMBUFER, 0);
    if(numBytesRecibidos<0)
        mensajeFinalError("Error en la lectura de datos");
    bufer[numBytesRecibidos]='\0';
    printf("Datos recibidos:%s\n",bufer);
    //Envia los datos numBytesRecibidos
    while(numBytesRecibidos>0){
        //Eco del mensaje
        ssize_t numBytesEnviados = send(sockCliente,bufer,numBytesRecibidos,0);
        if(numBytesEnviados<0)
            mensajeFinalError("Error en el envio");
        else if(numBytesEnviados==0)
            mensajeFinalError("Numero de bytes enviados erroneos");
        //Revisamos si hay mas datos a recibir
        numBytesRecibidos=recv(sockCliente, bufer, TAMBUFER,0);
        if(numBytesRecibidos<0)
            mensajeFinalError("Error en la lectura de datos recibidos");
    }
    close(sockCliente);
}
