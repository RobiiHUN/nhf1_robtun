/* -------------------------------------------------------------------------- */
/*                                ÖTVÖS RÓBERT                                */
/*                                   F9ILEX                                   */

/* -------------------------------------------------------------------------- */
/*                               ROBTUN PROJECT                               */
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
    //alapadatok_fajl_w = fopen("./csv/alapadatok.csv", "w");
    
    
    //megvaltoztatjuk a kiiratas szinet kek-re
    KEK_SZIN

    //kijelzo torlese
    KIJELZO_TORLO

    


/* -------------------------------------------------------------------------- */
/*                                    LOGO                                    */
/* -------------------------------------------------------------------------- */
    
    
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
                
                
                
                if (vissza == 1){
                    printf("\033[5A"); //ennyi sorral megyunk feljebb
                    printf("\033[J"); 
                    fprintf(log, "%s   -   A felhasznalo kiiratta a sajat adatait\n", pontos_ido());
                    
                    printf("\nNév: %s, Neptun %s, Felev tipusa: %d, Felev: %d\n", hallgato.nev, hallgato.neptun_kod, hallgato.felev_tipusa, hallgato.felev);

                }else{
                    /* ------------------------------ REGISZTRACIO ------------------------------ */
                    alapadatok_fajl_w = fopen("./csv/alapadatok.csv", "w");
                    printf("\033[4A"); //ennyi sorral megyunk feljebb
                    printf("\033[J");
                    fprintf(log, "%s   -   A felhasznalo belepett a sajat adatok almenube, de nincs fiokja, eppen regisztral.\n", pontos_ido());

                    
                    
                    // TODO ki kell szurni a nem megfelo bemenetet
                    //ha meg nem csinalt robtun fiokot
                    //TODO esetleg ezt megtudjuk hivni ezt a dinamikus tombot mindig?











                    
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

                    printf("Kerem adja meg a Neptun-kodjat: \n");
                    scanf("%s", neptun);

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

            /* -------------------------------------------------------------------------- */
            /*                                 TANULMANYOK                                */
            /* -------------------------------------------------------------------------- */

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
            /* -------------------------------------------------------------------------- */
            /*                                   VIZSGAK                                  */
            /* -------------------------------------------------------------------------- */
           
            vissza = vizsgak_menu();
            fprintf(log, "%s   -   A felhasznalo belepett a vizsgak almenube\n", pontos_ido());

            if (vissza == 1)
            {
                FILE* vizsgak_fajl_w = fopen("csv/vizsgak.csv", "w");

                //hany vizsgat szeretne felvenni
                int vizsgak_szama;
                printf("Kerem adja meg, hany vizsgat szeretne felvenni!: ");
                scanf("%d", &vizsgak_szama);

                //eltaroljuk egy tombbe
                Vizsgak *vizsga = malloc(vizsgak_szama * sizeof(Vizsgak));
                

                //beolvassuk a felvett vizsgakat (ha van);
                //felvett_vizsg_print(vizsga, vizsgak_szama);

                for (int i = 0; i < vizsgak_szama; i++)
                {
                    //vizsga nevenek bekereseß
                    printf("Kerem adja meg a(z) %d. felvenni kivant vizsga nevet:  ", i + 1);
                    scanf("%s", vizsga[i].nev);

                    //vizsga napjanak bekerese
                    printf("Kerem adja meg a(z) %d. vizsga nepjat! (Hetfo, Kedd...):  ", i + 1);
                    scanf("%s", vizsga[i].nap);

                    //vizsga oraja

                    /* -------------------------------------------------------------------------- */
                    /*                                 KORLATOZAS HIANYZIK                        */
                    /* -------------------------------------------------------------------------- */

                    printf("Adja meg a(z) %d. vizsga, hogy mikor kezdődik! ", i + 1);
                    scanf("%d", &vizsga[i].ora);
                }
                //csv-be lementjuk a vizsga bekert adatait
                mentes_vizsga(vizsga, vizsgak_szama, vizsgak_fajl_w);

                //vizsga_csv_beolvaso(&vizsga, &vizsgak_szama, vizsgak_fajl_w);


                fclose(vizsgak_fajl_w);
                free(vizsga); //nincs lefoglalva????
            }else if(vissza == 2){
                
                FILE* vizsgak_fajl_w = fopen("csv/vizsgak.csv", "w");
                fclose(vizsgak_fajl_w);
                printf("Sikeresen leadtad a vizsgaidat!\n");
            }
            break;
        case 4:
            /* -------------------------------------------------------------------------- */
            /*                                TARGYAK MENU                                */
            /* -------------------------------------------------------------------------- */
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
            
            



            /* -------------------------------------------------------------------------- */
            /*                                 BEIRATKOZAS                                */
            /* -------------------------------------------------------------------------- */

            if (hallgato.felev_tipusa == 0){
                alapadatok_fajl_w = fopen("./csv/alapadatok.csv", "w");
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
    
/* -------------------------------------------------------------------------- */
/*                   MEMORIAFELSZABADITAS ES A PROGRAM VEGE                   */
/* -------------------------------------------------------------------------- */

    free(orarend);
    
    
    
    debugmalloc_log_file("main.log");
    fclose(tantargyak_r);
    fclose(alapadatok_fajl);
    fclose(alapadatok_fajl_w);
    fclose(log);
    

   
    return 0;
}//main vege


/* -------------------------------------------------------------------------- */
/* -------------------------------------------------------------------------- */
/* -------------------------------------------------------------------------- */
/* -------------------------------------------------------------------------- */