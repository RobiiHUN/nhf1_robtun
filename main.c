#include <stdio.h>
#include <stdlib.h>
#include "./headers/menu.h"
#include "./headers/ido.h"
#include "./headers/csv_kezelo.h"
//#include "./headers/sajat_adatok.h"




void clear(){
    printf("\e[2J");
}





// -------------------------  MAIN  ------------------------------
int main(){
//system("clear");
    FILE *logo_pointer;
    FILE *alapadatok_fajl;
    FILE *log;
    FILE *alapadatok_fajl_w;

    log = fopen("main.log", "w");
    logo_pointer = fopen("./start/logo.txt", "r");
    alapadatok_fajl = fopen("./csv/alapadatok.csv", "r");
    
    

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



    int lepes_s;
    int valasztas_u;
    Hallgatok_alapadatok hallgato;
//  --------------------------- FOMENU ---------------------------


    int fomenu_cel = fomenu_fgv();
    fprintf(log, "%s   -   A menusor ki lett irva a felhasznalonak\n", pontos_ido());

    switch (fomenu_cel)
    {
        case 1:
           
            lepes_s = sajat_adatok_menu();
            fprintf(log, "%s   -   A felhasznalo belepett a sajat adatok almenube\n", pontos_ido());
            
            
            if (lepes_s == 1){
                
                
                int vissza  = csv_sorolvaso(alapadatok_fajl, &hallgato);
                if (vissza == 1){
                    printf("\033[5A"); //ennyi sorral megyunk feljebb
                    printf("\033[J"); 
                    fprintf(log, "%s   -   A felhasznalo kiiratta a sajat adatait\n", pontos_ido());
                    
                    printf("\nNév: %s, Neptun %d, Felev_tipusa: %d\n", hallgato.nev, hallgato.neptun_kod, hallgato.felev_tipusa);

                }else{
                    alapadatok_fajl_w = fopen("./csv/alapadatok.csv", "w");
                    printf("\033[4A"); //ennyi sorral megyunk feljebb
                    printf("\033[J");
                    fprintf(log, "%s   -   A felhasznalo belepett a sajat adatok almenube, de nincs fiokja, eppen regisztral.\n", pontos_ido());

                    
                    
                    //ki kell szurni a nem megfelo bemenetet
                    
                    printf("Ugy latszik, on most nyitja meg elosszor a Robtunt!\nKerem regisztralja magat!\n");
                    char nev_vez[100];
                    char nev_ker[100];
                    int neptun;
                    int felev = 0;
                    
                    
                    printf("\nVezeteknev: \n");
                    scanf("%s", nev_vez);

                    printf("Keresztnev: \n");
                    scanf("%s", nev_ker);

                    printf("Kerem adja meg a Neptun-kodjat: \n");
                    scanf("%d", &neptun);

                    
                    
                    csv_alapadat_kiir(alapadatok_fajl_w, nev_vez, nev_ker, neptun, felev);
                    printf("\033[10A"); //ennyi sorral megyunk feljebb
                    printf("\033[J");
                    printf("\nAz adatok sikeresen el lettek mentve!\n");
                    fprintf(log, "%s   -   A felhasznalo sikeresen regisztralt!\n", pontos_ido());

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

            printf("A jelenlegi feleved: %d", hallgato.felev_tipusa);
            


            }
            

            break;
        
        
        }





        
        
        
        
        

    

    
















    fclose(alapadatok_fajl);
    fclose(alapadatok_fajl_w);
    fclose(log);
    return 0;
}//main vege
