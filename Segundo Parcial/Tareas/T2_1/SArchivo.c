#include <stdio.h>
#include <stdlib.h> //exit
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h> //Familia AF_INET
#include <string.h>
#include <netinet/in.h> //htons htonl
#include <arpa/inet.h>//inet_ntoa
#include <unistd.h>//close
#include <fcntl.h>

#define TAMBUFFER 2048

void mensajeFinalError(const char *mensaje){
    fputs(mensaje,stderr);
    fputs((const char*)'\n',stderr);
    exit(1);
}

int main(int argc, char **argv){
  if(argc != 2)
    mensajeFinalError("Uso: EcoTCPServidor [<puerto>]");
  int pto = atoi(argv[1]);
  int sd;
  sd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
  if(sd < 0)
    mensajeFinalError("Fallo la apertura del socket");
  //Se construye la estructura de la dirección
  struct sockaddr_in dirServ;	           //Creamos una estructura para la dirección local
	memset(&dirServ, 0 , sizeof(dirServ));			//Limpiamos la estructura
	dirServ.sin_family = AF_INET;					//Familia de direcciones IPv4
	dirServ.sin_addr.s_addr = htonl(INADDR_ANY);	//Cualquier interfaz de entrada
	dirServ.sin_port = htons(pto);				//Número de puerto
  //Se enlaza a la dirección local
	if(bind(sd, (struct sockaddr*)&dirServ, sizeof(dirServ))< 0)
		mensajeFinalError("Error al enlazar");
  printf("Servicio iniciado...\n");
  listen(sd,5);
  for(;;){
    struct sockaddr_in dirCliente;		//Dirección del cliente
		//Obtenemos el tamaño de los datos del cliente
		socklen_t dirClienteTam = sizeof(dirCliente);
    //Esperamos que se conecte el cliente
    int cd = accept(sd, (struct sockaddr*)&dirCliente, &dirClienteTam);
    if(cd < 0)
      mensajeFinalError("Fallo la conexión");

    //Se conecto un cliente
    char nombreCliente[INET_ADDRSTRLEN];
    if(inet_ntop(AF_INET,&dirCliente.sin_addr.s_addr,nombreCliente,
            sizeof(nombreCliente)) != NULL)
        printf("Cliente conectado: %s/%d\n",nombreCliente,ntohs(dirCliente.sin_port));
    else
        puts("Imposible conectar el cliente");

    //Se prepara para recibir la información del archivo a recibir
    int n;
    char *path;
    path = malloc(sizeof(char*));
    n = read(cd, path, TAMBUFFER);
    free(path);
    if(n > 0){
      printf("Archivo a recibir: %s\n", path);
      //Se prepara para escribir archivo
      char buffer[TAMBUFFER];
      int fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0666);
      if(fd < 0)
      mensajeFinalError("Ha ocurrido un error en open()");
      while((n = read(cd, buffer, TAMBUFFER)) > 0){
        write(fd, buffer, TAMBUFFER);
      }
      printf("Archivo recibido.\n\n");
      close(fd);
    }
    else if(n == 0){
      perror("No se recibió ningún archivo");
    }
    close(cd);
  }
}
