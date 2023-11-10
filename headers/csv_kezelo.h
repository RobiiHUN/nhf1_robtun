#ifndef CSV_KEZELO_H
#define CSV_KEZELO_H

#include <stdio.h>
#include <string.h>

typedef struct
{
    char nev[50];
    int neptun_kod;
    int felev_tipusa;
    int felev;
}Hallgatok_alapadatok;

int csv_sorolvaso(FILE *fajlnev, Hallgatok_alapadatok *hallgato_adatok);
int csv_alapadat_kiir(FILE *fajlnev, char *nev_vez, char *nev_ker,int neptunkod, int felev_tipusa, int felev);
//int be_kiiratkozas(FILE *fajlnev, char *nev, int* neptun, int felev_tipusa);
#endif