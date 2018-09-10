//enviaDatos.c

#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <string.h>
#include <netdb.h>
#include <unistd.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main(int argc, char**argv){
	char host[20], pto[5];
	printf("\nEscribe la dirección del servidor: ");
	fgets(host, sizeof(host), stdin);
	fflush(stdin);
	printf("\n Escribe la dirección del puerto: ");
	fgets(pto, sizeof(pto), stdin);
	fflush(stdin);
	int status;
	struct addrinfo hints;
	struct addrinfo * servinfo;
	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	status = getaddrinfo(host, pto, &hints, &servinfo);
	int cd = socket(servinfo -> ai_family, servinfo -> ai_socktype, servinfo -> ai_protocol);
	FILE *f = fopen(cd, "w+");
	if(connect(cd, servinfo -> ai_addr, servinfo -> ai_addrlen) < 0){
		perror("\nError en funcion connect()\n");
	}
	freeaddrinfo(servinfo);
	printf("\nConexion establecida... enviando datos...\n");
	int dato1 = 5;
	long dato2 = 70;
	float dato3 = 3.0f;
	char dato4[] = "un mensaje";
	int n;
	///dato1
	n = write(cd, &dato1, sizeof(dato1));
	if(n < 0) perror("Error de escritura\n");
	else if(n == 0) perror("Socket cerrado error de escritura\n");
	else fflush(f);
	printf("Se envio el dato: %d\n", dato1);
	//dato2
	n = write(cd, &dato, sizeof(dato2));
	if(n < 0) perror("Error de escritura\n");
	else if(n == 0) perror("Socket cerrado error escritura\n");
	else printf("Se envio el dato: %ld\n", dato2);
	fflush(f);
	//dato3
	char datos[20];
	sprintf(datos, "%f", dato3);
	datos[strlen(datos)] = '\0';
	n = write(cd, datos, sizeof(datos));
	if(n < 0) perror("Error de escritura\n");
	else if(n == 0) perror("Error socket cerrado\n");
	else printf("Se envio el dato: %s\n", datos);
	fflush(f);
	//dato4
	n = write(cd, dato4, strlen(dato4));
	if(n < 0) perror("Error de escritura\n");
	else if(n == 0) perror("Error socket cerrado\n");
	else printf("Se envio el dato: %s\n", dato4);
	fflush(f);
	close(cd);
	fclose(f);
	return 0;
}