/* -------------------------------------------------------------------------- */
/*                               CSV_KEZELO (C)                               */
/* -------------------------------------------------------------------------- */





#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//a hallgato alapadatait tarolja el ez a struct, majd ezeket használjuk fel a legtobb adatnal

/* -------------------------------------------------------------------------- */
/*                                 STRUKTURAK                                 */
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

typedef struct Ora{
    char oraNev[100];
} Ora;

/* -------------------------------------------------------------------------- */
/*                                 FUGGVENYEK                                 */
/* -------------------------------------------------------------------------- */

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
                if (x == 0)
                {
                    printf("Hetfo");
                }else if (x == 1)
                {
                    printf("Kedd");
                }else if(x>1){
                
                
                
                
                    printf("%s ", het_napjai[x-1]);}
                int elsoora_mikor = 0;
                for (int  y = 0; y < 24; y++)
                {
                    if (orarend[i].napok[x][y] )
                        {
                            if (elsoora_mikor == 0)
                            {
                                elsoora_mikor = y;
                                if (elsoora_mikor != 0)
                                {
                                     printf("%d-tol %d-ig", y, y + 2);
                                }
                                
                                //printf("%d-tol %d-ig", y, y + 2);
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
            
            
        }
        printf("\n");
    }
    
    return 0;    
}


/* ----------------------------- VIZSGA RENDSZER ---------------------------- */

//felvett vizsgak kiiratasa consoleba



//felvett vizsgak mentese .csv-be
void mentes_vizsga(Vizsgak *vizsga, int vizsgaszam, FILE *csvpointer){
    for (int i = 0; i < vizsgaszam; i++)
    {
        fprintf(csvpointer, "%s,%s,%d\n", vizsga[i].nev, vizsga[i].nap, vizsga[i].ora);
    }
    
    
}





/* ----------------------- TANTARGYAK KIIRATASA CSVBE ----------------------- */

void tantargy_kiCSV(Tantargy_struct* tantargy, int tantargymennyiseg, FILE *file_ki){
    for (int i = 0; i < tantargymennyiseg; i++)
    {
        fprintf(file_ki, "%s,",tantargy[i].nev);
        for (int nap = 0; nap < 7; nap++)
        {
            for (int ora = 0; ora < 24; ora++)
            {
                if (tantargy[i].napok[nap][ora] == 1)
                {
                    fprintf(file_ki, " %d",nap *24 + ora);
                    if (nap * 24 + ora < 7 *24 - 1){
                        fprintf(file_ki, ",");
                    }
                }   
                
            }
            
        }
        fprintf(file_ki, "\n");
    }
}

void torol_es_feljebb_emel(FILE *be, const char *keresett_szo, const char *ideiglenes_fajlnev, const char *eredeti_fajlnev) {
    FILE *ki = fopen(ideiglenes_fajlnev, "w");
    

    char keresett_szo_keres[256];
    sprintf(keresett_szo_keres, "%s,", keresett_szo);

    char sor[256];
    int sor_torolve = 0;

    while (fgets(sor, sizeof(sor), be) != NULL) {
        if (strstr(sor, keresett_szo_keres) != NULL) {
            sor_torolve = 1;
        } else {
            fprintf(ki, "%s", sor);
        }
    }

    fclose(ki);

    if (sor_torolve) {
        printf("A sor sikeresen törölve.\n");
    } else {
        printf("A keresett szó nem található.\n");
    }

    remove(eredeti_fajlnev);
    rename(ideiglenes_fajlnev, eredeti_fajlnev);
}







// Struktúra az órák adatainak tárolásához

char** readClassNamesFromCSV(FILE* file, int* classCount) {
    // Első lépés: megszámoljuk, hány sor van a fájlban
    int lineCount = 0;
    char line[256]; // Max. 256 karakter hosszú sorokat támogatunk
    while (fgets(line, sizeof(line), file) != NULL) {
        lineCount++;
    }

    // Visszatekerjük a fájlt az elejére
    fseek(file, 0, SEEK_SET);

    // Dinamikus tömb létrehozása a sorok tárolásához
    char** classNames = (char**)malloc(lineCount * sizeof(char*));
    if (classNames == NULL) {
        fprintf(stderr, "Hiba: Nem sikerült lefoglalni a memóriát.\n");
        exit(EXIT_FAILURE);
    }

    // Soronként olvassuk be az adatokat és csak az első oszlopot tároljuk
    for (int i = 0; i < lineCount; i++) {
        classNames[i] = (char*)malloc(256 * sizeof(char)); // Max. 256 karakter
        if (classNames[i] == NULL) {
            fprintf(stderr, "Hiba: Nem sikerült lefoglalni a memóriát.\n");
            exit(EXIT_FAILURE);
        }

        if (fgets(line, sizeof(line), file) != NULL) {
            // Az első vesszőig másoljuk az adatokat
            char* commaPos = strchr(line, ',');
            if (commaPos != NULL) {
                *commaPos = '\0'; // Vessző helyére nullterminátor
            }

            // Másoljuk az adatokat a tömbbe
            strcpy(classNames[i], line);
        }
    }

    // Visszaadjuk az eredményt és a sorok számát
    *classCount = lineCount;
    return classNames;
}

int searchClass(char** classNames, int classCount, const char* searchClass, Tantargy_struct *orarend, int hanytantargy) {
    char* keresett;
    for (int t = 0; t < classCount; t++) {
        // Ha a keresett részsztring megtalálható a tantárgy nevében
        if (strstr(classNames[t], searchClass) != NULL) {
            // Kiírjuk a találatot és megkérdezzük, hogy erre gondolt-e
            printf("Van ilyen tantargy: %s. Gondolt erre? (Igen/Nem): ", classNames[t]);
            

            
            
            char response[10];
            scanf("%s", response);

            // Az igen válasz esetén visszatérünk a találattal
            if (strcmp(response, "Igen") == 0 || strcmp(response, "igen") == 0) {
                keresett = classNames[t];
                break;
                //return 1;
            }//else if (strcmp(response, "Nem") == 0 || strcmp(response, "nem")== 0){
                //t++;
            //}
            
        }
    }



    
    const char* het_napjai[] = {"Hetfo", "Kedd", "Szerda", "Csutortok", "Pentek", "Szombat", "Vasarnap"};
    
    for (int i = 0; i < hanytantargy; i++)
    {
        if (strcmp(orarend[i].nev , keresett) == 0)
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
                    printf("%s ", het_napjai[x - 1]);
                    int elsoora_mikor = 0;
                    for (int  y = 0; y < 24; y++)
                    {
                        if (orarend[i].napok[x][y] )
                            {
                                if (elsoora_mikor == 0)
                                {
                                    elsoora_mikor = y;
                                    if (elsoora_mikor != 0)
                                    {
                                        printf("%d-tol %d-ig", y, y + 2);
                                    }
                                    
                                    //printf("%d-tol %d-ig", y, y + 2);
                                }
                                
                            }else{
                                if (elsoora_mikor != 0)
                                {
                                    elsoora_mikor = 0;
                                }
                                
                            }
                            
                        }
                        printf("\n");
                    }    }
                    

                
                
                
            }
            printf("\n");
        }
        
        
    }
    
    return 1;    
}




int orarend_konv_print_kereso(Tantargy_struct *orarend, int hanytantargy, int keresett) {
    
    const char* het_napjai[] = {"Hetfo", "Kedd", "Szerda", "Csutortok", "Pentek", "Szombat", "Vasarnap"};
    
    for (int i = 0; i < hanytantargy; i++)
    {
        if (strcmp(orarend[i].nev , "Programozas") == 0)
        {
            /* code */
        
        
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
                                    if (elsoora_mikor != 0)
                                    {
                                        printf("%d-tol %d-ig", y, y + 2);
                                    }
                                    
                                    //printf("%d-tol %d-ig", y, y + 2);
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
            }    
            
        }
        printf("\n");
    }
    
    return 0;    
}