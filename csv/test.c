#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Struktúra a tantárgyak tárolásához
struct Tantargy {
    char nev[50];
    char nap[20];
    int ora;
};

// Függvény a tantárgyak listázásához
void listazTantargyak(struct Tantargy* tantargyak, int tantargySzam) {
    if (tantargySzam > 0) {
        printf("Tantargyak listaja:\n");
        for (int i = 0; i < tantargySzam; ++i) {
            printf("%d. %s - %s %d ora\n", i + 1, tantargyak[i].nev, tantargyak[i].nap, tantargyak[i].ora);
        }
    } else {
        printf("Nincs megadva tantargy.\n");
    }
}

// Függvény a tantárgyak kiírásához .csv fájlba
void kiirCSV(struct Tantargy* tantargyak, int tantargySzam, FILE *file) {
    

    if (file == NULL) {
        printf("Hiba a fajl megnyitasakor.\n");
        return;
    }

    fprintf(file, "Tantargy neve,Nap,Kezdeti ora\n");
    for (int i = 0; i < tantargySzam; ++i) {
        fprintf(file, "%s,%s,%d\n", tantargyak[i].nev, tantargyak[i].nap, tantargyak[i].ora);
    }

    
    printf("Tantargyak kiirva a tantargyak.csv fajlba.\n");
}

// Függvény a tantárgyak beolvasásához .csv fájlból
void beolvasCSV(struct Tantargy** tantargyak, int* tantargySzam) {
    FILE* file = fopen("tantargyak.csv", "r");

    if (file == NULL) {
        printf("Nincs megadva tantargy a tantargyak.csv fajlbol.\n");
        return;
    }

    // Ellenőrizzük, hány sor van a fájlban
    int sorokSzama = 0;
    char sor[100];

    while (fgets(sor, sizeof(sor), file) != NULL) {
        sorokSzama++;
    }

    // Ugrunk a fájl elejére
    rewind(file);

    // Dinamikus tömb inicializálása a tantárgyak tárolásához
    *tantargyak = malloc(sorokSzama * sizeof(struct Tantargy));

    // Beolvasás a .csv fájlból
    *tantargySzam = 0;
    while (fscanf(file, "%49[^,],%19[^,],%d\n", (*tantargyak)[*tantargySzam].nev,
                  (*tantargyak)[*tantargySzam].nap, &(*tantargyak)[*tantargySzam].ora) == 3) {
        (*tantargySzam)++;
    }

    fclose(file);
}

int main() {
    FILE* file = fopen("vizsgak.csv", "w");
    // Felhasználótól bekért tantárgyak számának tárolása
    int tantargySzam;
    printf("Adja meg, hogy hany tantargyat szeretne felvenni: ");
    scanf("%d", &tantargySzam);

    // Dinamikus tömb inicializálása
    struct Tantargy* tantargyak = malloc(tantargySzam * sizeof(struct Tantargy));

    // Beolvassuk a tantárgyakat a .csv fájlból
    beolvasCSV(&tantargyak, &tantargySzam);

    for (int i = 0; i < tantargySzam; ++i) {
        printf("Adja meg a(z) %d. tantargy nevet: ", i + 1);
        scanf("%s", tantargyak[i].nev);

        printf("Adja meg a(z) %d. tantargy napjat (pl.: Hetfo): ", i + 1);
        scanf("%s", tantargyak[i].nap);

        printf("Adja meg a(z) %d. tantargy kezdeti orajat: ", i + 1);
        scanf("%d", &tantargyak[i].ora);
    }

    while (1) {
        printf("\nVizsgafelveteli rendszer\n");
        printf("1. Tantargyak listazasa\n");
        printf("2. Tantargyak kiirasa .csv-be\n");
        printf("3. Kilepes\n");

        int valasztas;
        printf("Adja meg a valasztott opcio szamat: ");
        scanf("%d", &valasztas);

        switch (valasztas) {
            case 1:
                // Tantárgyak listázása
                listazTantargyak(tantargyak, tantargySzam);
                break;

            case 2:
                // Tantárgyak kiírása .csv fájlba
                kiirCSV(tantargyak, tantargySzam, file);
                break;

            case 3:
                // Kilépés és felszabadítás
                free(tantargyak);
                fclose(file);
                printf("Viszlat!\n");
                return 0;

            default:
                printf("Ervenytelen opcio. Kerek valasszon ujra.\n");
                break;
        }
    }

    return 0;
}
