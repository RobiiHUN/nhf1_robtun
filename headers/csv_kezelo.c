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



