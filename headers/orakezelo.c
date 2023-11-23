#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct orak_struct
{
    char ** orak;
    size_t meret;
    size_t jelenlegi_meret;
}orak_struct;

void tomb_letrehoz(orak_struct* tantargyak){
    tantargyak->orak = NULL;
    tantargyak->meret = 0;
    tantargyak->jelenlegi_meret = 0;
}

