#include <stdio.h>
#include <string.h>
#include <stdlib.h>




typedef struct {
    char nev[50];
    int napok[7][24]; // Az 1-3 órák tárolására (1. dimenzió: napok, 2. dimenzió: órák)
} Tantargy;

void konvertalasEsKiiras(Tantargy *orarend, int tantargyDarab) {
    const char* napok[] = {"Hetfo", "Kedd", "Szerda", "Csutortok", "Pentek", "Szombat", "Vasarnap"};

    for (int i = 0; i < tantargyDarab; i++) {
        printf("Tantargy neve: %s\n", orarend[i].nev);
        printf("Orak a napokon:\n");
        for (int j = 0; j < 7; j++) {
            int vanOra = 0;
            for (int k = 0; k < 24; k++) {
                if (orarend[i].napok[j][k]) {
                    vanOra = 1;
                    break;
                }
            }
            if (vanOra) {
                printf("%s: ", napok[j]);
                int elsoora_mikor = 0;
                for (int k = 0; k < 24; k++) {
                    if (orarend[i].napok[j][k]) {
                        if (elsoora_mikor == 0) {
                            elsoora_mikor = k;
                            printf("%d-tol ", k);
                        }
                    } else {
                        if (elsoora_mikor != 0) {
                            //printf("(%d) ", k - 1);
                            elsoora_mikor = 0;
                        }
                    }
                }
                if (elsoora_mikor != 0) {
                    printf("(%d) ", 23);
                }
                printf("\n");
            }
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

    char sor[50];
    int tantargyDarab = 0;
    Tantargy *orarend = NULL;

    while (fgets(sor, 50, file)) {
        orarend = (Tantargy *)realloc(orarend, (tantargyDarab + 1) * sizeof(Tantargy));
        orarend[tantargyDarab].nev[0] = '\0';
        for (int i = 0; i < 7; i++) {
            for (int j = 0; j < 24; j++) {
                orarend[tantargyDarab].napok[i][j] = 0;
            }
        }

        char *token = strtok(sor, ",");
        strcpy(orarend[tantargyDarab].nev, token);

        int nap = 0;
        while ((token = strtok(NULL, ",")) != NULL) {
            int ora = atoi(token);
            orarend[tantargyDarab].napok[nap][ora] = 1;
            nap = (nap + 1) % 7;
        }
        tantargyDarab++;
    }

    fclose(file);

    konvertalasEsKiiras(orarend, tantargyDarab);

    free(orarend);

    return 0;
}
