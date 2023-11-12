#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>





int fomenu_fgv(){
    int valasztas = 0;
    char szam_e;

    
    
    

    // ide meg kell a betu kiszures
        while ( valasztas < 1 || valasztas > 5 )
        {


            printf("\n\nKerlek ird be a megfelelo menupont szamat! (1-5)\n\n");
            printf("1 - Sajat adatok\n");
            printf("2 - Tanulmanyok\n");
            printf("3 - Vizsgak\n");
            printf("4 - Targyak\n");
            printf("5 - Ugyintezes\n");
            scanf("%c", &szam_e);
            
            if (isdigit(szam_e))
            {
                valasztas = szam_e - '0';
            }

            printf("\033[8A"); 
            printf("\033[J"); 

            
        }
        return valasztas;
    

}


int sajat_adatok_menu(){
    
    int valasztas_sajatadatok = 0;
    while ( valasztas_sajatadatok < 1 || valasztas_sajatadatok > 3 )
    {
        
        printf("\n1 - Szemelyes adatok\n");
        printf("2 - Beallitasok\n");
        printf("3 - Vissza a fomenube\n");
        scanf("%d", &valasztas_sajatadatok);

        
        
        printf("\033[1A"); //ennyi sorral megyunk feljebb
        printf("\033[J"); 




        

    }
    return valasztas_sajatadatok;
}

int tanulmanyok_menu(){
    int valasztas = 0;

    while ( valasztas < 1 || valasztas > 3 )
    {
        printf("1 - Kepzes adatok\n");
        printf("2 - Orarend\n");
        printf("3 - Vissza a fomenube\n");
        scanf("%d", &valasztas);

    }
    return valasztas;
    
}

int vizsgak_menu(){
    int valasztas = 0;

    while ( valasztas < 1 || valasztas > 2 )
    {
        printf("1 - Vizsga felvetel\n");
        printf("2 - Vizsga leadas\n");
        scanf("%d", &valasztas);

    }
    return valasztas;
}

int targyak_menu(){
    int valasztas = 0;

    while ( valasztas < 1 || valasztas > 2 )
    {
        printf("1 - Felvett targyak\n");
        printf("2 - Targy felvetele leadasa\n");
        scanf("%d", &valasztas);

    }
    return valasztas;
}

int ugyintezes_menu(){
    int valasztas = 0;

    while ( valasztas != 1 )
    {
        printf("1 - Beiratkozas\n");
        scanf("%d", &valasztas);

    }
    return valasztas;
}


int beallitasok_almenu(){
    int valasztas = 0;

    while (valasztas < 1 || valasztas > 2)
    {
        printf("1 - Szemelyes adataim torlese\n");
        printf("2 - Vissza a fomenube\n");
        scanf("%d", &valasztas);
    }

    printf("\033[1A"); //ennyi sorral megyunk feljebb
    printf("\033[J");    
    return valasztas;
}

int beiratkozas_almenu(){
    int valasztas = 0;

    while (valasztas < 1 || valasztas > 2)
    {
        printf("1 - Beiratkozas\n");
        printf("2 - Vissza a fomenube\n");
        scanf("%d", &valasztas);
    }

    // printf("\033[3A"); //ennyi sorral megyunk feljebb
    // printf("\033[J"); 
    return valasztas;
    


}