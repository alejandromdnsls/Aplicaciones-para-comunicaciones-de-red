#include <sys/types.h>  /* Para definici�n de tipos */
#include <sys/socket.h> /* Para llamadas a las APIs de socket */
#include <netinet/in.h> /* Estructuras de datos */
#include <arpa/inet.h>  /* Para sockaddr_in */
#include <stdio.h>      /* Para printf() y fprintf() */
#include <stdlib.h>     /* Para atoi() */
#include <string.h>     /* Para strlen() */
#include <unistd.h>     /* Para close() */

#define MAX_LEN  1024   /* Tama�o m�ximo de lectura */

int main(int argc, char *argv[]) {

	int sock;                     /* Descriptor de socket */
	int flag_on = 1;              /* Banderas de opci�n del socket */
	struct sockaddr_in mc_addr;   /* Estructura de la direcci�n del socket */
	char recv_str[MAX_LEN+1];     /* Bufer de lectura*/
	int recv_len;                 /* Longitud de la cadena recibida */
	unsigned short mc_port;       /* Puerto*/
	struct sockaddr_in from_addr; /* Paquete origen */
	unsigned int from_len;        /* Longitd direcci�n fuente */

	mc_port = 1234;

	/* Se crea un socket para conectarse a un canal multicast */
	if ((sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0) {
		perror("Error en socket().");
		exit(1);
	}

	/* Permite la reutilizaci�n del socket */
	if ((setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &flag_on,sizeof(flag_on))) < 0) {
		perror("Error en setsockopt() SO_REUSEADDR");
		exit(1);
	}

	/* Se construye una estructura de direcci�n sock_addr */
	memset(&mc_addr, 0, sizeof(mc_addr));
	mc_addr.sin_family      = AF_INET;
	mc_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	mc_addr.sin_port        = htons(mc_port);

	/* Liga la direcci�n con el socket */
	if ((bind(sock, (struct sockaddr *) &mc_addr, sizeof(mc_addr))) < 0) {
		perror("Error en bind()");
		exit(1);
	}

	for (;;) { // lazo infinito
		/* Se limpia el buffer y la estructura de lectura */
        printf("\nEsperando cliente...\n");
		memset(recv_str, 0, sizeof(recv_str));
		from_len = sizeof(from_addr);
		memset(&from_addr, 0, from_len);

		/* Bloqueo para la recepci�n de paquetes */
		if ((recv_len = recvfrom(sock, recv_str, MAX_LEN, 0, (struct sockaddr*)&from_addr, &from_len)) < 0) {
			perror("Error en recvfrom()");
			exit(1);
		}

		/* Inprimimos lo que recibimos */
		printf("\nSe recibieron %d bytes desde %s: ", recv_len, inet_ntoa(from_addr.sin_addr));
		printf("%s", recv_str);
	}

	close(sock);
}
