/* -------------------------------------------------------------------------- */
/*                            CSV_KEZELO HEADER (H)                           */
/* -------------------------------------------------------------------------- */




#ifndef CSV_KEZELO_H
#define CSV_KEZELO_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* -------------------------------------------------------------------------- */
/*                            FELHASZNALT STRUCTOK                            */
/* -------------------------------------------------------------------------- */

typedef struct
{
    char nev[50];
    char neptun_kod[50];
    int felev_tipusa;
    int felev;
}Hallgatok_alapadatok;

typedef struct
{
    char nev[50];
    int napok[7][24]; //1.dim -> napok, 2.dim -> orak
}Tantargy_struct;


typedef struct 
{
    char nev[50];
    char nap[10];
    int ora;

}Vizsgak;

typedef struct {
    char oraNev[100];
} Ora;  


/* --------------------------- ALAPADATOK RENDSZER -------------------------- */
int csv_sorolvaso(FILE *fajlnev, Hallgatok_alapadatok *hallgato_adatok);
int csv_alapadat_kiir(FILE *fajlnev, char *nev_vez, char *nev_ker,char *neptunkod, int felev_tipusa, int felev);
int orarend_konv_print(Tantargy_struct *orarend, int hanytantargy);

/* ----------------------------- VIZSGA RENDSZER ---------------------------- */

void felvett_vizsg_print(Vizsgak *vizsga, int vizsgaszam);
void mentes_vizsga(Vizsgak *vizsga, int vizsgaszam, FILE *csvpointer);
void vizsga_csv_beolvaso(Vizsgak **vizsga, int *vizsgaszam, FILE *csvpointer);
void tantargy_kiCSV(Tantargy_struct* tantargy, int tantargymennyiseg, FILE *file_ki);
void torol_es_feljebb_emel(FILE *be, const char *keresett_szo, const char *ideiglenes_fajlnev, const char *eredeti_fajlnev);
char** readClassNamesFromCSV(FILE* file, int* classCount);
int searchClass(char** classNames, int classCount, const char* searchClass, Tantargy_struct *orarend, int hanytantargy);
int orarend_konv_print_kereso(Tantargy_struct *orarend, int hanytantargy, int keresett);
#endif

