#include <stdio.h>
#include <ctype.h>


//meg a vissza a fomenube funkcio fejlesztes alatt van!


//az egesz program menurendszere kezdodik itt, amely a megnyitaskor latszik
int fomenu_fgv(){
    int valasztas = 0;
    char szam_e;

    
         
    

    // ide meg kell a betu kiszures
        while ( valasztas < 1 || valasztas > 6 )
        {


            printf("\n\nKerlek ird be a megfelelo menupont szamat! (1-5)\n\n");
            printf("1 - Sajat adatok\n");
            printf("2 - Tanulmanyok\n");
            printf("3 - Vizsgak\n");
            printf("4 - Targyak\n");
            printf("5 - Ugyintezes\n");
            printf("6 - Kilepes\n");
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

// a sajat adatok almenu fgv-e, majd a beolvasas utan visszatoroljuk a bemenetet
int sajat_adatok_menu(){
    
    int valasztas_sajatadatok = 0;
    while ( valasztas_sajatadatok < 1 || valasztas_sajatadatok > 2 )
    {
        
        printf("\n1 - Szemelyes adatok\n");
        printf("2 - Beallitasok\n");
        scanf("%d", &valasztas_sajatadatok);

        
        
        printf("\033[1A"); //ennyi sorral megyunk feljebb
        printf("\033[J"); 




        

    }
    return valasztas_sajatadatok;
}
//tanulmanyok menu
int tanulmanyok_menu(){
    int valasztas = 0;

    while ( valasztas < 1 || valasztas > 3 )
    {
        printf("1 - Kepzes adatok\n");
        printf("2 - Orarend\n");
        printf("3- Felvett ora kereso\n");
        scanf("%d", &valasztas);

    }
    return valasztas;
    
}
//vizsgak mennu
int vizsgak_menu(){
    int valasztas = 0;

    while ( valasztas < 1 || valasztas > 2 )
    {
        printf("1 - Vizsga felvetel\n");
        printf("2 - Vizsgak leadasa\n");
        scanf("%d", &valasztas);

    }
    if (valasztas == 3)
    {
        printf("\033[6A"); //ennyi sorral megyunk feljebb
        printf("\033[J");
    }
    
    return valasztas;
}
// targyak menu
int targyak_menu(){
    int valasztas = 0;

    while ( valasztas < 1 || valasztas > 2 )
    {
        printf("1 - Targyak felvetele\n");
        printf("2 - Targyak leadasa\n");
        scanf("%d", &valasztas);

    }
    return valasztas;
}
//ugyintezes menu
int ugyintezes_menu(){
    int valasztas = 0;

    while ( valasztas < 1 || valasztas > 1 )
    {
        printf("1 - Beiratkozas\n");
        scanf("%d", &valasztas);

    }
    return valasztas;
}

//a beallitasok almenu
int beallitasok_almenu(){
    int valasztas = 0;

    while (valasztas < 1 || valasztas > 1)
    {
        printf("1 - Szemelyes adataim torlese\n");
        scanf("%d", &valasztas);
    }

    printf("\033[1A"); //ennyi sorral megyunk feljebb
    printf("\033[J");

    
    return valasztas;
}
//a beiratkozas almenu
int beiratkozas_almenu(){
    int valasztas = 0;

    while (valasztas < 1 || valasztas > 1)
    {
        printf("1 - Beiratkozas\n");
        scanf("%d", &valasztas);
    }


    return valasztas;
    


}