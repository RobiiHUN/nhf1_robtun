#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./headers/menu.h"
#include "./headers/ido.h"
#include "./headers/csv_kezelo.h"
#include "./headers/debugmalloc.h"



//kijelzo torlo fgv
void clear(){
    printf("\e[2J");
}





// ------------------------------------------------------  MAIN  -------------------------------------------------------
int main(){
        //file beolvasasok
    FILE *logo_pointer;
    FILE *alapadatok_fajl;
    FILE *log;
    FILE *alapadatok_fajl_w;
    FILE *tantargyak_r;
        //fajladatok eltarolasa
    log = fopen("main.log", "w");
    logo_pointer = fopen("./start/logo.txt", "r");
    alapadatok_fajl = fopen("./csv/alapadatok.csv", "r");
    tantargyak_r = fopen("./csv/tantargyak.csv", "r");
    
    
    

    clear();

    


//  --------------------------- LOGO -----------------------------
    
    
    char logo[100];

   
    fprintf(log, "%s   -   Beovasas megtortent\n", pontos_ido());

    if (logo_pointer != NULL)
    {
        while (fgets(logo, 100, logo_pointer))
        {
            printf("%s", logo);
            
        }
        fprintf(log, "%s   -   Logo kiirva\n", pontos_ido());
    }else{
        printf("Nem sikerult beolvasni a logo fajlt!\n");
        fprintf(log, "%s   -   Nem sikerult beolvasni a logo fajlt!\n", pontos_ido());
    }
    fclose(logo_pointer);
// ------------------------------------------------------------------


    int lepes_s;
    int valasztas_u;
    Hallgatok_alapadatok hallgato;
    int vissza  = csv_sorolvaso(alapadatok_fajl, &hallgato);

    char max_sor[50];
    int hanytantargy = 0;
    Tantargy_struct *orarend = NULL;
//  --------------------------- FOMENU ---------------------------


    int fomenu_cel = fomenu_fgv();
    fprintf(log, "%s   -   A menusor ki lett irva a felhasznalonak\n", pontos_ido());
        
        //fomenu fgv behivasa,  majd a felhasznalo eldonti, mit szeretne csinalni
        //main header fajlbol


    switch (fomenu_cel)
    {
        case 1:
           
            lepes_s = sajat_adatok_menu();
            fprintf(log, "%s   -   A felhasznalo belepett a sajat adatok almenube\n", pontos_ido());
            
            
            if (lepes_s == 1){
                
                
                
                if (vissza == 1){
                    printf("\033[5A"); //ennyi sorral megyunk feljebb
                    printf("\033[J"); 
                    fprintf(log, "%s   -   A felhasznalo kiiratta a sajat adatait\n", pontos_ido());
                    
                    printf("\nNév: %s, Neptun %d, Felev tipusa: %d, Felev: %d\n", hallgato.nev, hallgato.neptun_kod, hallgato.felev_tipusa, hallgato.felev);

                }else{
                    alapadatok_fajl_w = fopen("./csv/alapadatok.csv", "w");
                    printf("\033[4A"); //ennyi sorral megyunk feljebb
                    printf("\033[J");
                    fprintf(log, "%s   -   A felhasznalo belepett a sajat adatok almenube, de nincs fiokja, eppen regisztral.\n", pontos_ido());

                    
                    
                    // TODO ki kell szurni a nem megfelo bemenetet
                    //ha meg nem csinalt robtun fiokot
                    
                    printf("Ugy latszik, on most nyitja meg elosszor a Robtunt!\nKerem regisztralja magat!\n");
                    char nev_vez[100];
                    char nev_ker[100];
                    int neptun;
                    int felev;
                    
                    //bekerjuk a fobb adatokat
                    printf("\nVezeteknev: \n");
                    scanf("%s", nev_vez);

                    printf("Keresztnev: \n");
                    scanf("%s", nev_ker);

                    printf("Kerem adja meg a Neptun-kodjat: \n");
                    scanf("%d", &neptun);

                    printf("Kerem adja meg a hanyadik felevet tolti az egyetemen!: \n");
                    scanf("%d", &felev);
                    
                    
                    csv_alapadat_kiir(alapadatok_fajl_w, nev_vez, nev_ker, neptun, 0, felev);
                    printf("\033[10A"); //ennyi sorral megyunk feljebb
                    printf("\033[J");
                    printf("\nAz adatok sikeresen el lettek mentve!\n");
                    fprintf(log, "%s   -   A felhasznalo sikeresen regisztralt!\n", pontos_ido());
                    //megtortent a regisztraáció

                }
                
                
            }else if (lepes_s == 2)
            {
                printf("\033[3A"); //ennyi sorral megyunk feljebb
                printf("\033[J");
                int valasztas = beallitasok_almenu();
                if (valasztas == 1)
                {
                    alapadatok_fajl_w= fopen("./csv/alapadatok.csv", "w");
                    printf("Sikeres torles!");
                    fprintf(log, "%s   -   A felhasznalo kitorolte a szemelyes adatait\n", pontos_ido());

                }
            }
            break;
        case 2:
            tanulmanyok_menu();
            fprintf(log, "%s   -   A felhasznalo belepett a tanulmanyok almenube\n", pontos_ido());


            //orarend megalkotasa, majd kiiratása a csv-ból
            //todo az orarend almenube kell rakni
            while (fgets(max_sor, 50, tantargyak_r))
            {
                orarend = (Tantargy_struct *)realloc(orarend, (hanytantargy + 1) * sizeof(Tantargy_struct));
                orarend[hanytantargy].nev[0] = '\0';
                for (int i = 0; i < 7; i++)
                {
                    for (int j = 0; j < 24; j++)
                    {
                        orarend[hanytantargy].napok[i][j] = 0;
                    }
                    
                }
                
                char* token = strtok(max_sor, ",");
                strcpy(orarend[hanytantargy].nev, token);

                int nap = 0;
                while ((token = strtok(NULL, ",")) != NULL)
                {
                    int ora = atoi(token); //int-e konvertaljuk
                    orarend[hanytantargy].napok[nap][ora] = 1;
                    nap = (nap + 1) % 7;
                }
                hanytantargy++;
            }
            
            orarend_konv_print(orarend, hanytantargy);







            break;
        case 3:
            vizsgak_menu();
            fprintf(log, "%s   -   A felhasznalo belepett a vizsgak almenube\n", pontos_ido());
            break;
        case 4:
            targyak_menu();
            fprintf(log, "%s   -   A felhasznalo belepett a targyak almenube\n", pontos_ido());
            break;
        case 5:
            valasztas_u = ugyintezes_menu();
            fprintf(log, "%s   -   A felhasznalo belepett az ugyintezes almenube\n", pontos_ido());

            if (valasztas_u == 1)
            {
            fprintf(log, "%s   -   A felhasznalo kivalasztotta a beiratkozas almenut\n", pontos_ido());
            printf("\033[2A"); //ennyi sorral megyunk feljebb
            printf("\033[J");



            if (hallgato.felev_tipusa == 0){
                printf("A jelenlegi feleved: Passziv");
                fprintf(log, "%s   -   A felhasznalo kiiratta a feleve tipusat!\n", pontos_ido());
            }else if (hallgato.felev_tipusa == 1)
            {
                printf("A jelenlegi feleved: Aktiv\n \n");
                fprintf(log, "%s   -   A felhasznalo kiiratta a feleve tipusat!\n", pontos_ido());
                //printf("Szeretned passzivaltatni a felevedet?(I/N) \n");
                
                //be_kiiratkozas(alapadatok_fajl_w, "test", 123, 0);
                
                
                
                
                //TODO beiratkozas


            }
            

            


            }
            

            break;
        
        
        }


    free(orarend);
    debugmalloc_log_file("main.log");
    fclose(tantargyak_r);
    fclose(alapadatok_fajl);
    fclose(alapadatok_fajl_w);
    fclose(log);

   
    return 0;
}//main vege
