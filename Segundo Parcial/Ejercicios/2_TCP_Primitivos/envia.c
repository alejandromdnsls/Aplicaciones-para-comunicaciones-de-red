#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h> //printf, perror,fdopen
#include <string.h>
#include <netdb.h> //gethostbyname
#include <unistd.h>//close
#include <stdlib.h> //exit

int main(int argc, char* argv[]){
    char host[10];
    int pto;

    printf("Escribe la direccion del servidor:");
    //gets(host);
    fgets(host,sizeof(host),stdin);
    printf("\nEscribe el puerto:");
    scanf("%d",&pto);
    fflush(stdin);
    struct hostent *dst = gethostbyname(host);
    if(dst==NULL){
        perror("Direccion no valida");
        main(argc,argv);
    }//if

    struct sockaddr_in sdir;
    bzero((char *)&sdir, sizeof(sdir));
    sdir.sin_family=AF_INET;
    sdir.sin_port=htons(pto);
    memcpy((char*)&sdir.sin_addr.s_addr,dst->h_addr,dst->h_length);
    int cd = socket(AF_INET,SOCK_STREAM,0);
    FILE *f = fdopen(cd,"w+");
    if (connect(cd,(struct sockaddr *)&sdir,sizeof(sdir))<0){
        perror("error en funcion connect()\n");
    }//if
    printf("\n Conexion establecida.. enviando datos..\n");
    int dato1 =5;
    long  dato2= 70;
    float dato3=3.0f;
    char *dato4="un mensaje";
    int n;
    ///dato1
    n = write(cd,&dato1,sizeof(dato1));
    if(n<0)
        perror("Error de escritura\n");
    else if(n==0)
        perror("Socket cerrado error de escritura\n");
    else
        fflush(f);
    printf("Se envio el dato: %d\n",dato1);
    //dato2
    n= write(cd,&dato2,sizeof(dato2));
    if(n<0)
        perror("Error de escritura\n");
    else if(n==0)
        perror("Socket cerrado error de escritura\n");
    else
        printf("Se envio el dato: %ld\n",dato2);
    fflush(f);

    //dato3
    char datos[10];
    sprintf(datos,"%f",dato3);
    n = write(cd,datos,strlen(datos));
    if(n<0)		
		perror("Error de escritura\n");
    else if(n==0)    
	    perror("Socket cerrado error de escritura\n");
    else //printf("Se envio el dato: %s\n",datos);
        printf("Se envio el dato %.02f\n",dato3);
    fflush(f);

    //dato4
    n = write(cd,dato4,strlen(dato4)+1);
    if(n<0)
        perror("Error de escritura\n");
    else if(n==0)
    	perror("Socket cerrado error de escritura\n");
    else
    	printf("Se envio el dato: %s\n",dato4);
    fflush(f);
    close(cd);
    fclose(f);

    return 0;
}//main

