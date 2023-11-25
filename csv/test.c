#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char nev[50];
    int** napok; // 1. dim -> napok, 2. dim -> orak
    int orakSzam;
} Tantargy_struct;

// Függvény a .csv fájlból történő beolvasáshoz
void beolvasCSV(Tantargy_struct* tantargyak, int tantargySzam, const char* fajlnev) {
    FILE* file = fopen(fajlnev, "r");

    if (file == NULL) {
        printf("Hiba a fajl megnyitasakor.\n");
        return;
    }

    char sor[1000];
    int i = 0;

    while (fgets(sor, sizeof(sor), file) != NULL) {
        char* token = strtok(sor, ",");
        strcpy(tantargyak[i].nev, token);

        tantargyak[i].orakSzam = 0;

        token = strtok(NULL, ",");
        while (token != NULL) {
            tantargyak[i].orakSzam++;
            token = strtok(NULL, ",");
        }

        tantargyak[i].napok = malloc(7 * sizeof(int*));
        for (int nap = 0; nap < 7; ++nap) {
            tantargyak[i].napok[nap] = malloc(tantargyak[i].orakSzam * sizeof(int));
        }

        // Visszaállítjuk a fájl mutatóját, hogy újra be tudjuk olvasni
        fseek(file, 0, SEEK_SET);

        // Második beolvasás, most már konkrétan a számokat
        token = strtok(sor, ",");
        token = strtok(NULL, ","); // Ugrunk az első tantárgy neve után

        int j = 0;
        while (token != NULL) {
            tantargyak[i].napok[j / tantargyak[i].orakSzam][j % tantargyak[i].orakSzam] = atoi(token);
            token = strtok(NULL, ",");
            j++;
        }

        i++;
    }

    fclose(file);
}

// Függvény a tantárgyak listázásához
void listazIdopontok(Tantargy_struct* tantargyak, int tantargySzam) {
    const char* napok[] = {"Hetfo", "Kedd", "Szerda", "Csutortok", "Pentek", "Szombat", "Vasarnap"};

    printf("Idopontok listaja:\n");
    for (int nap = 0; nap < 7; ++nap) {
        printf("%s: ", napok[nap]);
        for (int i = 0; i < tantargySzam; ++i) {
            for (int ora = 0; ora < tantargyak[i].orakSzam; ++ora) {
                if (tantargyak[i].napok[nap][ora] == 1) {
                    printf("%s, ", tantargyak[i].nev);
                }
            }
        }
        printf("\n");
    }
}

int main() {
    // A fájl neve, amiben az órarend van
    const char* fajlnev = "tantargyak.csv";

    // Tantárgyak száma
    int tantargySzam = 7;

    // Dinamikus tömb inicializálása
    Tantargy_struct* tantargyak = malloc(tantargySzam * sizeof(Tantargy_struct));

    // Tantárgyak beolvasása a .csv fájlból
    beolvasCSV(tantargyak, tantargySzam, fajlnev);

    // Órarend kilistázása
    listazIdopontok(tantargyak, tantargySzam);

    // Felszabadítás
    for (int i = 0; i < tantargySzam; ++i) {
        free(tantargyak[i].napok);
    }
    free(tantargyak);

    return 0;
}
