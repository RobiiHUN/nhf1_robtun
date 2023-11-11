#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TANTARGY_NEV_HOSSZ 50
#define MAX_CSV_SOR_HOSSZ 100

typedef struct {
    char nev[MAX_TANTARGY_NEV_HOSSZ];
    int *orak; // Tároljuk az órákat
    int orakSzama;
} Tantargy;

void oraHozzaadasa(Tantargy *orarend, int tantargyDarab) {
    int valasztottTantargy;
    printf("Valassz tantargyat az orarendhez:\n");
    for (int i = 0; i < tantargyDarab; i++) {
        printf("%d. %s\n", i + 1, orarend[i].nev);
    }
    printf("Valasztott tantargy sorszama: ");
    scanf("%d", &valasztottTantargy);
    valasztottTantargy--; // Tömb indexelés miatt csökkentjük 1-gyel

    int oraszam;
    printf("Hany orat szeretnel hozzaadni ehhez a tantargyhoz? ");
    scanf("%d", &oraszam);

    orarend[valasztottTantargy].orak = (int *)malloc(oraszam * sizeof(int));
    orarend[valasztottTantargy].orakSzama = oraszam;

    printf("Add meg az orak sorszamat szokozzel elvalasztva: ");
    for (int i = 0; i < oraszam; i++) {
        scanf("%d", &orarend[valasztottTantargy].orak[i]);
    }
}

void oraListaKiiratasa(Tantargy *orarend, int tantargyDarab) {
    for (int i = 0; i < tantargyDarab; i++) {
        printf("%s orai: ", orarend[i].nev);
        for (int j = 0; j < orarend[i].orakSzama; j++) {
            printf("%d ", orarend[i].orak[j]);
        }
        printf("\n");
    }
}

int main() {
    FILE *file = fopen("orarend.csv", "r");
    if (!file) {
        printf("Hiba a fajl megnyitasakor!");
        return 1;
    }

    char sor[MAX_CSV_SOR_HOSSZ];
    int tantargyDarab = 0;
    Tantargy *orarend = NULL;

    while (fgets(sor, MAX_CSV_SOR_HOSSZ, file)) {
        orarend = (Tantargy *)realloc(orarend, (tantargyDarab + 1) * sizeof(Tantargy));
        
        char *orakAdat = strchr(sor, ','); // Első vessző után jönnek az órák
        if (orakAdat) {
            orakAdat++; // Ugrunk a vessző után
            char *token = strtok(orakAdat, " ");

            int oraszam = 0;
            orarend[tantargyDarab].orak = (int *)malloc(10 * sizeof(int)); // Adott tantárgyhoz 10 órát biztosítunk
            while (token != NULL) {
                orarend[tantargyDarab].orak[oraszam] = atoi(token);
                oraszam++;
                token = strtok(NULL, " ");
            }
            orarend[tantargyDarab].orakSzama = oraszam;
        }

        tantargyDarab++;
    }

    fclose(file);

    int valasztas;
    do {
        printf("\n1. Ora hozzaadasa\n2. Ora lista kiirasa\n3. Kilepes\n");
        printf("Valasztas: ");
        scanf("%d", &valasztas);

        switch (valasztas) {
            case 1:
                oraHozzaadasa(orarend, tantargyDarab);
                break;
            case 2:
                oraListaKiiratasa(orarend, tantargyDarab);
                break;
            case 3:
                break;
            default:
                printf("Ervenytelen valasztas!");
                break;
        }
    } while (valasztas != 3);

    // Felszabadítjuk a dinamikusan foglalt memóriát
    for (int i = 0; i < tantargyDarab; i++) {
        free(orarend[i].orak);
    }
    free(orarend);

    return 0;
}
