#include <stdio.h>
#include <stdlib.h>
#include <time.h>


//a pontos idot hatarozzuk meg ezzel a fgv-el ev-honap-nap-ora-perc-mp. Ez a log miatt fontos
char* pontos_ido(){
    time_t idozito;
    char* ido = (char*) malloc(26);
    struct tm* ido_infok;

    idozito = time(NULL);
    ido_infok = localtime(&idozito);

    strftime(ido, 26, "%Y-%m-%d %H:%M:%S", ido_infok);
    return ido;
}