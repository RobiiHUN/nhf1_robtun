/* -------------------------------------------------------------------------- */
/*                                ÖTVÖS RÓBERT                                */
/*                                   F9ILEX                                   */
/*                                 2023.11.25                                 */
/* -------------------------------------------------------------------------- */
/*                               ROBTUN PROJECT C                             */
/* -------------------------------------------------------------------------- */



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./headers/menu.h"
#include "./headers/ido.h"
#include "./headers/csv_kezelo.h"
#include "./headers/debugmalloc.h"

#define KEK_SZIN  printf ("\x1b[34m");
#define SZIN_VISSZA printf ("\x1b[0m");
#define KIJELZO_TORLO printf("\e[2J");









/* -------------------------------------------------------------------------- */
/*                                    MAIN                                    */
/* -------------------------------------------------------------------------- */



int main(){
        //file beolvasas pointerek (a konnyebb atlahatosag miatt)
    FILE *logo_pointer;
    FILE *alapadatok_fajl;
    FILE *log;
    FILE *alapadatok_fajl_w;
    FILE *tantargyak_w;
    
        //fajladatok eltarolasa
    log = fopen("main.log", "w");
    logo_pointer = fopen("./start/logo.txt", "r");
    alapadatok_fajl = fopen("./csv/alapadatok.csv", "r");
    
    //megvaltoztatjuk a kiiratas szinet kek-re
    KEK_SZIN

    //kijelzo torlese
    KIJELZO_TORLO

    


/* -------------------------------------------------------------------------- */
/*                                    LOGO                                    */
/* -------------------------------------------------------------------------- */
    
    int fomenu = 0;


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
    
    //visszaalitjuk a szint az eredetire
    SZIN_VISSZA
/* -------------------------------------------------------------------------- */
    int lepes_s;
    int valasztas_u;
    Hallgatok_alapadatok hallgato;
    int vissza  = csv_sorolvaso(alapadatok_fajl, &hallgato);

    char max_sor[50];
    int hanytantargy = 0;
    Tantargy_struct *orarend = NULL;
/* -------------------------------------------------------------------------- */


/* -------------------------------------------------------------------------- */
/*                                   FOMENU                                   */
/* -------------------------------------------------------------------------- */


/* -------------------------------------------------------------------------- */
    while(1){
        int fomenu_cel = fomenu_fgv();
        fprintf(log, "%s   -   A menusor ki lett irva a felhasznalonak\n", pontos_ido());
        
        //fomenu fgv behivasa,  majd a felhasznalo eldonti, mit szeretne csinalni
        //main header fajlbol


            switch (fomenu_cel)
            {
                
                case 1:
                /* -------------------------------------------------------------------------- */
                /*                                SAJAT ADATOK                                */
                /* -------------------------------------------------------------------------- */
                
                    lepes_s = sajat_adatok_menu();
                    fprintf(log, "%s   -   A felhasznalo belepett a sajat adatok almenube\n", pontos_ido());
                    
                    
                    if (lepes_s == 1){
                        /* -------------------------------------------------------------------------- */
                        
                        
                        if (vissza == 1){
                            printf("\033[5A"); //ennyi sorral megyunk feljebb
                            printf("\033[J"); 
                            fprintf(log, "%s   -   A felhasznalo kiiratta a sajat adatait\n", pontos_ido());
                            
                            printf("\nNév: %s, Neptun %s, Felev tipusa: %d, Felev: %d\n", hallgato.nev, hallgato.neptun_kod, hallgato.felev_tipusa, hallgato.felev);

                            printf(" 0 - vissza a fomenube\n");
                            fomenu = 0;
                            scanf("%d", &fomenu);
                            if (fomenu == 0)
                            {
                                printf("\033[4A"); //ennyi sorral megyunk feljebb
                                printf("\033[J");
                            }

                            
                        }else{
                            /* ------------------------------ REGISZTRACIO ------------------------------ */

                            alapadatok_fajl_w = fopen("./csv/alapadatok.csv", "w");
                            printf("\033[4A"); //ennyi sorral megyunk feljebb
                            printf("\033[J");
                            fprintf(log, "%s   -   A felhasznalo belepett a sajat adatok almenube, de nincs fiokja, eppen regisztral.\n", pontos_ido());
                            printf("Ugy latszik, on most nyitja meg elosszor a Robtunt!\nKerem regisztralja magat!\n");
                            char nev_vez[50];
                            char nev_ker[50];
                            char neptun[6];
                            int felev;
                            
                            //bekerjuk a fobb adatokat
                            printf("\nVezeteknev: \n");
                            scanf("%s", nev_vez);

                            printf("Keresztnev: \n");
                            scanf("%s", nev_ker);

                            printf("Kerem adja meg a Neptun-kodjat(string): \n");
                            scanf("%s", neptun);

                            printf("Kerem adja meg a hanyadik felevet tolti az egyetemen!(szam): \n");
                            scanf("%d", &felev);
                            
                            
                            csv_alapadat_kiir(alapadatok_fajl_w, nev_vez, nev_ker, neptun, 0, felev);
                            printf("\033[10A"); //ennyi sorral megyunk feljebb
                            printf("\033[J");
                            printf("\nAz adatok sikeresen el lettek mentve!\n");
                            fprintf(log, "%s   -   A felhasznalo sikeresen regisztralt!\n", pontos_ido());
                            printf(" 0 - vissza a fomenube\n");
                            fomenu = 0;
                            scanf("%d", &fomenu);
                            if (fomenu == 0)
                            {
                                printf("\033[4A"); //ennyi sorral megyunk feljebb
                                printf("\033[J");
                            }
                            fclose(alapadatok_fajl_w);

                            //megtortent a regisztraáció

                        }
                        
                        
                    }else if (lepes_s == 2)
                    {
                        /* -------------------------------------------------------------------------- */
                        /* ------------------------ SZEMELYES ADATOK TORLESE ------------------------ */

                        printf("\033[3A"); //ennyi sorral megyunk feljebb
                        printf("\033[J");
                        int valasztas = beallitasok_almenu();
                        if (valasztas == 1)
                        {
                            alapadatok_fajl_w= fopen("./csv/alapadatok.csv", "w");
                            printf("Sikeres torles! Kerem, ha ujbol beregisztral ne feledkezzen el a feleve aktivizalasarol!");
                            printf("Kulonben addig minden itt vegzett muvelet ervenytelen lesz!\n");
                            fprintf(log, "%s   -   A felhasznalo kitorolte a szemelyes adatait\n", pontos_ido());
                            printf(" 0 - vissza a fomenube\n");
                            fomenu = 0;
                            scanf("%d", &fomenu);
                            if (fomenu == 0)
                            {
                                printf("\033[4A"); //ennyi sorral megyunk feljebb
                                printf("\033[J");
                            }
                            fclose(alapadatok_fajl_w);

                        }
                    }
                    break;
                case 2:

                    /* -------------------------------------------------------------------------- */
                    /*                                 TANULMANYOK                                */
                    /* -------------------------------------------------------------------------- */

                    vissza = tanulmanyok_menu();
                    if (vissza == 1)
                    {
                       printf("Ön jelenleg a Buadpesti Muszaki es Gazdasagtudomanyi Egyetemen tanul.");
                       fprintf(log, "%s   -   A felhasznalo kiiratta a oktatasi intezmenyet!\n", pontos_ido());
                        
                    /* -------------------------------------------------------------------------- */

                    }else if (vissza == 2)
                    {   
                        /* ---------------------------- ORAREND MEGALKOTO --------------------------- */

                        FILE *tantargyak_r = fopen("./csv/tantargyak.csv", "r");
                        Tantargy_struct* orarend = NULL;
                        fprintf(log, "%s   -   A felhasznalo kiiratta a tantargyait\n", pontos_ido());      

                        //orarend kiirato rendszer
                        //visszafejti a .csv-bol az orakat napokra                  
                        while (fgets(max_sor, 50, tantargyak_r))
                        {
                            
                            
                            orarend = realloc(orarend, (hanytantargy + 1) * sizeof(Tantargy_struct));
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
                        fclose(tantargyak_r);
                        free(orarend);
                        
                    }
                    
                    
                    

                    //orarend megalkotasa, majd kiiratása a .csv-ból
                    printf("\n0 - vissza a fomenube\n");
                    fomenu = 0;
                    scanf("%d", &fomenu);
                    if (fomenu == 0)
                            {
                                printf("\033[4A"); //ennyi sorral megyunk feljebb
                                printf("\033[J");
                            }
    
                    
                    break;

                case 3:
                    /* -------------------------------------------------------------------------- */
                    /*                                   VIZSGAK                                  */
                    /* -------------------------------------------------------------------------- */
                
                    vissza = vizsgak_menu();
                    fprintf(log, "%s   -   A felhasznalo belepett a vizsgak almenube\n", pontos_ido());

                    if (vissza == 1)
                    {
                        /* ------------------------------ VIZSGA FELVET ----------------------------- */

                        FILE* vizsgak_fajl_w = fopen("csv/vizsgak.csv", "w");

                        //hany vizsgat szeretne felvenni
                        int vizsgak_szama;
                        printf("Kerem adja meg, hany vizsgat szeretne felvenni!: ");
                        scanf("%d", &vizsgak_szama);

                        //eltaroljuk egy tombbe
                        Vizsgak *vizsga = malloc(vizsgak_szama * sizeof(Vizsgak));
                        


                        for (int i = 0; i < vizsgak_szama; i++)
                        {
                            //vizsga nevenek bekerese
                            printf("Kerem adja meg a(z) %d. felvenni kivant vizsga nevet:  ", i + 1);
                            scanf("%s", vizsga[i].nev);

                            //vizsga napjanak bekerese
                            printf("Kerem adja meg a(z) %d. vizsga nepjat! (Hetfo, Kedd...):  ", i + 1);
                            scanf("%s", vizsga[i].nap);

                            //vizsga oraja


                            printf("Adja meg a(z) %d. vizsga, hogy mikor kezdődik!(ora) ", i + 1);
                            scanf("%d", &vizsga[i].ora);
                        }
                        //csv-be lementjuk a vizsga bekert adatait
                        mentes_vizsga(vizsga, vizsgak_szama, vizsgak_fajl_w);
                        fprintf(log, "%s   -   A felhasznalo vett fel vizsgakat\n", pontos_ido());

                        fclose(vizsgak_fajl_w);
                        free(vizsga); 
                    }else if(vissza == 2){

                        /* ------------------------ AZ OSSZES VIZSGA LEADASA ------------------------ */
                        
                        FILE* vizsgak_fajl_w = fopen("csv/vizsgak.csv", "w");
                        fclose(vizsgak_fajl_w);
                        printf("Sikeresen leadtad a vizsgaidat!\n");
                        fprintf(log, "%s   -   A felhasznalo leadta a vizsgait!\n", pontos_ido());
                    }
                    printf("\n0 - vissza a fomenube\n");
                    fomenu = 0;
                    scanf("%d", &fomenu);
                    if (fomenu == 0)
                            {
                                printf("\033[4A"); //ennyi sorral megyunk feljebb
                                printf("\033[J");
                            }
                    
                    break;
                case 4:

                    /* -------------------------------------------------------------------------- */
                    /*                                TARGYAK MENU                                */
                    /* -------------------------------------------------------------------------- */
                    
                    /* ---------------------------- TANTARGYFELVETEL ---------------------------- */

                    vissza = targyak_menu();
                    fprintf(log, "%s   -   A felhasznalo belepett a targyak almenube\n", pontos_ido());
                    if (vissza == 1)
                    {
                        tantargyak_w = fopen("./csv/tantargyak.csv", "w");
                        int targymennyiseg = 0;
                        printf("Kerem adja meg hany tantargyat szeretne felvenni! ");
                        scanf("%d", &targymennyiseg);

                        //dinamikus tomb a tantargyaknak
                        Tantargy_struct* tantargy = malloc(targymennyiseg * sizeof(Tantargy_struct));

                        //ciklus a tantargyfelvetelhez
                        for (int i = 0; i < targymennyiseg; i++)
                        {
                            printf("Kerem adja meg a(z) %d. tantargy nevet egy szoban! ", i + 1);
                            scanf("%s", tantargy[i].nev);

                            for (int nap = 0; nap < 7; nap++)
                            {
                                for (int ora = 0; ora < 24; ora++)
                                {
                                    tantargy[i].napok[nap][ora] = 0;    // elosszor lenullazzuk
                                }
                                
                            }
                            
                            //kiszamitjuk a bejovo idopont hany ora
                            int hanyidopont = 0;
                            printf("Kerem adja meg, hany idpontot szeretne felvenni a(z) ehhez az orajahoz! ");
                            scanf("%d", &hanyidopont);

                            for (int x = 0; x < hanyidopont; x++)
                            {
                                //formatum ellenorzo
                                while (1)
                                {
                                    int nap = 0;
                                    printf("Adja meg a(z). %d idopont napjat! (1 - Hetfo .... 7 - Vasarnap) ", x + 1);
                                    scanf("%d", &nap);
                                    if (nap < 1 || nap > 7)
                                    {
                                        continue;
                                    }
                                    int ora = 0;
                                    printf("Adja meg, hogy az ora mikor kezdodik (egesz oraban), ");
                                    scanf("%d", &ora);

                                    //betoltes
                                    tantargy[i].napok[nap - 1][ora] = 1;
                                    break;

                                }
                            }
                        }
                        tantargy_kiCSV(tantargy, targymennyiseg, tantargyak_w);
                        fclose(tantargyak_w);
                        free(tantargy);

                    }else if (vissza == 2)
                    {
                        tantargyak_w = fopen("./csv/tantargyak.csv", "w");
                        fclose(tantargyak_w);
                    }
     

                    printf("\n0 - vissza a fomenube\n");
                    fomenu = 0;
                    scanf("%d", &fomenu);
                    if (fomenu == 0)
                            {
                                printf("\033[4A"); //ennyi sorral megyunk feljebb
                                printf("\033[J");
                            }
                    
                    break;
                case 5:
                        /* -------------------------------------------------------------------------- */
                        /*                                 BEIRATKOZAS                                */
                        /* -------------------------------------------------------------------------- */

                    valasztas_u = ugyintezes_menu();
                    fprintf(log, "%s   -   A felhasznalo belepett az ugyintezes almenube\n", pontos_ido());
                    if (valasztas_u == 1)
                    {
                    fprintf(log, "%s   -   A felhasznalo kivalasztotta a beiratkozas almenut\n", pontos_ido());
                    printf("\033[2A"); //ennyi sorral megyunk feljebb
                    printf("\033[J");
                    
                        if (hallgato.felev_tipusa == 0){
                            hallgato.felev_tipusa = 1;
                            FILE *alapadatokCSV_w = fopen("csv/alapadatok.csv","w");
                            fprintf(alapadatokCSV_w,"%s, %s, %d, %d", hallgato.nev, hallgato.neptun_kod, hallgato.felev_tipusa, hallgato.felev);
                            printf("A jelenlegi feleved: Most valtozott aktivra!\n");
                            fprintf(log, "%s   -   A felhasznalo kiiratta a feleve tipusat!\n", pontos_ido());
                            fclose(alapadatokCSV_w);

                        }else if (hallgato.felev_tipusa == 1)
                        {
                            printf("A jelenlegi feleved: Aktiv\n \n");
                            fprintf(log, "%s   -   A felhasznalo kiiratta a feleve tipusat!\n", pontos_ido());

                        }
                    }
                    
                    printf("\n0 - vissza a fomenube\n");
                    fomenu = 0;
                    scanf("%d", &fomenu);
                    if (fomenu == 0)
                            {
                                printf("\033[4A"); //ennyi sorral megyunk feljebb
                                printf("\033[J");
                            }

                    break;
                case 6:
                    /* -------------------------- KILEPES A PROGRAMBOL -------------------------- */
                    KIJELZO_TORLO
                    printf("Viszlat, varom vissza!\n");
                    printf("Koszonom, hogy rendszeremet hasznalta!");
                    free(orarend);
                    debugmalloc_log_file("main.log");
                    fprintf(log, "%s   -   A felhasznalo bezarta a programot\n", pontos_ido());
                    fclose(log);
                    return 0;
                    break;
                
                }
    }
    return 0;
}//main vege


/* -------------------------------------------------------------------------- */
/* -------------------------------------------------------------------------- */
/* -------------------------------------------------------------------------- */
/* -------------------------------------------------------------------------- */