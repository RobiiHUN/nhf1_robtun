/* -------------------------------------------------------------------------- */
/*                               CSV_KEZELO (C)                               */
/* -------------------------------------------------------------------------- */





#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//a hallgato alapadatait tarolja el ez a struct, majd ezeket használjuk fel a legtobb adatnal

typedef struct
{
    char nev[50];
    char neptun_kod[50];
    int felev_tipusa;
    int felev;
}Hallgatok_alapadatok;

//a tantargyak adatait tarolja el, azt hogy mi a neve, illetve, hopgy mikor van

typedef struct
{
    char nev[50];
    int napok[7][24]; //1.dim -> napok, 2.dim -> orak
}Tantargy_struct;

//ez a struct tartalmazza a felvett vizsgak idopontjait
typedef struct 
{
    char nev[50];
    char nap[10];
    int ora;

}Vizsgak;


//soronkent beolvassuk a csv-t

int csv_sorolvaso(FILE *fajlnev, Hallgatok_alapadatok *hallgato_adatok){
    
    int beolvasas = fscanf(fajlnev, "%49[^,], %49[^,], %d, %d\n", hallgato_adatok->nev, hallgato_adatok->neptun_kod, &hallgato_adatok->felev_tipusa, &hallgato_adatok->felev);
    
    if ( beolvasas>0)
    {
        
        return 1;
    } else{
        return 0;
    }
    

}
//ha nincs a csv-ben adat, az azt jelenti, h a felhasznalo, most nyitja meg elosszor a programot, tehat ez a program irja ki a csv-be

int csv_alapadat_kiir(FILE *fajlnev, char *nev_vez, char *nev_ker,char *neptunkod, int felev_tipusa, int felev){
    fprintf(fajlnev, "%s %s, %s, %d, %d\n", nev_vez, nev_ker, neptunkod, felev_tipusa, felev);
    return 0;   
}

//ez a fgv szortirozza az orakat, es vegzi a kiiratast
//orarend kiirato, illetve atkonvertalja az orakat napokra

int orarend_konv_print(Tantargy_struct *orarend, int hanytantargy){
    
    const char* het_napjai[] = {"Hetfo", "Kedd", "Szerda", "Csutortok", "Pentek", "Szombat", "Vasarnap"};
    for (int i = 0; i < hanytantargy; i++)
    {
        printf("Tantargy: %s\n", orarend[i].nev);
        for (int x= 0; x < 7; x++){
        {
            int vanora = 0;
            for (int z = 0; z < 24; z++)
            {
                if (orarend[i].napok[x][z]){
                    vanora++;
                    break;
                }
            }
            if (vanora == 1)
            {
                printf("%s ", het_napjai[x]);
                int elsoora_mikor = 0;
                for (int  y = 0; y < 24; y++)
                {
                    if (orarend[i].napok[x][y] )
                        {
                            if (elsoora_mikor == 0)
                            {
                                elsoora_mikor = y;
                                printf("%d-tol %d-ig", y, y + 2);
                            }
                            
                        }else{
                            if (elsoora_mikor != 0)
                            {
                                elsoora_mikor = 0;
                            }
                            
                        }
                        
                    }
                    printf("\n");
                }
                

            }
            //printf("\n");
            
        }
        printf("\n");
    }
    
    return 0;    
}



/* ----------------------------- VIZSGA RENDSZER ---------------------------- */

//felvett vizsgak kiiratasa consoleba



//felvett vizsgak mentese .csv-be
void mentes_vizsga(Vizsgak *vizsga, int vizsgaszam, FILE *csvpointer){
    if (csvpointer == NULL)
    {
        printf("Nemtudtam megnyitni a fajlt!\n");
        return;
    }

    for (int i = 0; i < vizsgaszam; i++)
    {
        fprintf(csvpointer, "%s,%s,%d\n", vizsga[i].nev, vizsga[i].nap, vizsga[i].ora);
    }
    
    
}

/* -------------------------------------------------------------------------- */
/*                                EZZEL MI VAN    ????                        */
/* -------------------------------------------------------------------------- */

//vizsgak beolvasasa .csv-bol

void vizsga_csv_beolvaso(Vizsgak **vizsga, int *vizsgaszam, FILE *csvpointer){
     if (csvpointer == NULL)
    {
        printf("Nemtudtam megnyitni a fajlt!\n");
        return;
    }

    //sorok szama
    int sorszam = 0;
    char sor[100];

    while (fgets(sor, sizeof(sor), csvpointer) != NULL)
    {
        sorszam++;
    }
    

    //a kurzor tolas ellen
    rewind(csvpointer);

    //din.tomb ketreozasa
    *vizsga = malloc(sorszam * sizeof(Vizsgak));

    //beolvasas
    *vizsgaszam = 0;
    while (fscanf(csvpointer, "%49[^,],%19[^,],%d\n", (*vizsga)[*vizsgaszam].nev, (*vizsga)[*vizsgaszam].nap, &(*vizsga)[*vizsgaszam].ora)== 3)
    {
        (*vizsgaszam)++;
    }
}
