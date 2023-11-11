#ifndef CSV_KEZELO_H
#define CSV_KEZELO_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct
{
    char nev[50];
    int neptun_kod;
    int felev_tipusa;
    int felev;
}Hallgatok_alapadatok;

typedef struct
{
    char nev[50];
    int napok[7][24]; //1.dim -> napok, 2.dim -> orak
}Tantargy_struct;


int csv_sorolvaso(FILE *fajlnev, Hallgatok_alapadatok *hallgato_adatok);
int csv_alapadat_kiir(FILE *fajlnev, char *nev_vez, char *nev_ker,int neptunkod, int felev_tipusa, int felev);
int orarend_konv_print(Tantargy_struct *orarend, int hanytantargy);
//int be_kiiratkozas(FILE *fajlnev, char *nev, int* neptun, int felev_tipusa);
#endif