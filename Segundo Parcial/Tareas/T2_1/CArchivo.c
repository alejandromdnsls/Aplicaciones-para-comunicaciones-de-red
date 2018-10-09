#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>

#define TAMBUFFER 2048

void mensajeFinalError(const char *mensaje){
    fputs(mensaje,stderr);
    fputs((const char*)'\n',stderr);
    exit(1);
}

int main(int argc, char** argv){
  if(argc < 3 || argc > 4)
		mensajeFinalError("Uso: EcoTCPCliente <Dirección del servidor> <Puerto> <Archivo> ");
  char *servIP = argv[1];
  int puerto = atoi(argv[2]);
  char *path = argv[3];
  int s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(s < 0)
		mensajeFinalError("Error de apertura de puerto");
  struct sockaddr_in dirServ;
  memset(&dirServ,0,sizeof(dirServ));
  dirServ.sin_family = AF_INET;
  int valRet = inet_pton(AF_INET, servIP,&dirServ.sin_addr.s_addr); // Convierte una cadena fuente a una estructura dirección de internet
  if(valRet == 0)
    mensajeFinalError("Dirección del servidor erronea");
  else if(valRet < 0)
    mensajeFinalError("Error en el inet_pton()");
  dirServ.sin_port = htons(puerto);

  //Establecemos la comunicación con el servidor de eco
	if(connect(s, (struct sockaddr*) &dirServ,sizeof(dirServ))<0)
		mensajeFinalError("Error en la conexión");

  //Se prepara la información del archivo a enviar
  int fd = open(path, O_RDONLY);
  if(fd < 0)
    mensajeFinalError("Ha ocurrido un error en open()");
  FILE *f = fdopen(s, "w+");
  int i, j;
  for(i = strlen(path); i >= 0; i--){
    if(path[i] == '/')
      break;
  }
  char*nombre_archivo = malloc(sizeof(char*));
  if(i > 0){
    int k = 0;
    for(j = i + 1; j <= strlen(path); j++){
      nombre_archivo[k] = path[j];
      k++;
    }
  }
  printf("Archivo a enviar: %s\n", nombre_archivo);
  free(nombre_archivo);
  int n;
  n = write(s, nombre_archivo, TAMBUFFER);
  fflush(f);

  //Se envia la información
  char buffer[TAMBUFFER];
  while((n = read(fd, buffer, TAMBUFFER)) > 0){
    write(s, buffer, TAMBUFFER);
    fflush(f);
  }
  printf("Archivo enviado.\n\n");
  fclose(f);
  close(fd);
	close(s);
	return 0;
}
