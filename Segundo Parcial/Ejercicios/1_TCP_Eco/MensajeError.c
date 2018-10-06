#include <stdio.h>
#include <stdlib.h>

void mensajeFinalError(const char *mensaje){
    fputs(mensaje,stderr);
    fputs((const char*)'\n',stderr);
    exit(1);
}

void mensajeFinalSistema(const char *mensaje){
    perror(mensaje);
    exit(1);
}
