#include <stdio.h>
#include <string.h>

typedef struct
{
    char nev[50];
    int neptun_kod;
    int felev_tipusa;
    int felev;
}Hallgatok_alapadatok;

int csv_sorolvaso(FILE *fajlnev, Hallgatok_alapadatok *hallgato_adatok){
    
    int beolvasas = fscanf(fajlnev, "%49[^,], %d, %d, %d\n", hallgato_adatok->nev, &hallgato_adatok->neptun_kod, &hallgato_adatok->felev_tipusa, &hallgato_adatok->felev);
    
    if ( beolvasas>0)
    {
        
        return 1;
    } else{
        return 0;
    }
    

}

int csv_alapadat_kiir(FILE *fajlnev, char *nev_vez, char *nev_ker,int neptunkod, int felev_tipusa, int felev){
    fprintf(fajlnev, "%s %s, %d, %d, %d\n", nev_vez, nev_ker, neptunkod, felev_tipusa, felev);
    return 0;   
}


// int be_kiiratkozas(FILE *fajlnev, char *nev, int* neptun, int felev_tipusa)
// {
//     strncpy(hallgato -> felev_tipusa, uj_ertek, sizeof(hallgato->felev_tipusa)-1);
//     fprintf(fajlnev, "%s,%d,%d\n", nev, neptun, felev_tipusa);

//     return 0;
// }