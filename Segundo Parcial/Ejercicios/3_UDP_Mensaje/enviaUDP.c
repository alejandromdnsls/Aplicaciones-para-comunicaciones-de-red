#include <sys/types.h>   /* Definidiones de tipo*/
#include <sys/socket.h>  /* API de sockets */
#include <netinet/in.h>  /* Estructura de direcciones*/
#include <arpa/inet.h>   /* sockaddr_in */
#include <stdio.h>       /* printf() */
#include <stdlib.h>      /* atoi() */
#include <string.h>      /* strlen() */
#include <unistd.h>      /* close() */

#define MAX_LEN  1024    /* Tama�o maximo del buffer */
#define MIN_PORT 1024    /* Rango de puertos validos */
#define MAX_PORT 65535
int main(int argc, char *argv[]) {

  int sock;                   /* Descriptor del socket */
  char send_str[MAX_LEN];     /* Cadena a enviar */
  struct sockaddr_in mc_addr; /* Estructura de direciones */
  unsigned int send_len;      /* Longitud de cadena enviada */
  char* mc_addr_str;          /* Direcci�n IP de envio */
  unsigned short mc_port;     /* Puerto de envio */

  /* Validaci�n de argumentos */
  if (argc != 3) {
    fprintf(stderr,
            "Uso: %s <Dirección IP> <Puerto>\n",
            argv[0]);
    exit(1);
  }

  mc_addr_str = argv[1];       /* arg 1: direcci�n IP */
  mc_port     = atoi(argv[2]); /* arg 2: n�mero de puerto */

  /* validaci�n del n�mero de puerto */
  if ((mc_port < MIN_PORT) || (mc_port > MAX_PORT)) {
    fprintf(stderr, "Número de puerto inválido %d.\n",
            mc_port);
    fprintf(stderr, "El rango v�lido esta entre %d y %d.\n",
            MIN_PORT, MAX_PORT);
    exit(1);
  }

  /* Creaci�n del socket de datagramas */
  if ((sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0) {
    perror("Error en -> socket() ");
    exit(1);
  }


  /* Construimos la estructura de la direccion */
  memset(&mc_addr, 0, sizeof(mc_addr));
  mc_addr.sin_family      = AF_INET;
  mc_addr.sin_addr.s_addr = inet_addr(mc_addr_str);
  mc_addr.sin_port        = htons(mc_port);

  printf("Comienza a escribir (return para enviar, ctrl-C para salir):\n");

  /* Limpiamos bufer de salida*/
  memset(send_str, 0, sizeof(send_str));

  while (fgets(send_str, MAX_LEN, stdin)) {
    send_len = strlen(send_str);

    /* Enviamos el datagrama a la direcci�n definida */
    if ((sendto(sock, send_str, send_len, 0,
         (struct sockaddr *) &mc_addr,
         sizeof(mc_addr))) != send_len) {
      perror("sendto() numero de caracateres enviados incorrecto");
      exit(1);
    }

    /* Limpiamos bufer de salida*/
    memset(send_str, 0, sizeof(send_str));
  }

  close(sock);

  exit(0);
}
