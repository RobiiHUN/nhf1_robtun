#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* nev;
    char* neptun;
    char* felev;
    char* szuletesi_ido;
    char* allapot;
} Hallgato;

// Ellenőrzi, hogy a fájl tartalmaz-e adatot
int tartalmazAdat(const char* fajlnev) {
    FILE* file = fopen(fajlnev, "r");
    if (file == NULL) {
        return 0;
    }
    
    char sor[256];
    fgets(sor, sizeof(sor), file);
    fclose(file);
    
    return (sor != NULL && strlen(sor) > 0);
}

// Bekéri a felhasználótól egy karaktertömb értékét
char* bekerKaraktertomb(const char* kerdes) {
    char buffer[256];
    printf("%s: ", kerdes);
    scanf("%255s", buffer);

    char* eredmeny = (char*)malloc(strlen(buffer) + 1);
    if (eredmeny) {
        strcpy(eredmeny, buffer);
    }
    return eredmeny;
}

// Hozzáadja az adatokat a CSV fájlhoz
void adatokatHozzaad(const char* fajlnev, Hallgato hallgato) {
    FILE* file = fopen(fajlnev, "a");
    if (file == NULL) {
        printf("Hiba a fajl megnyitasakor: %s\n", fajlnev);
        return;
    }

    fprintf(file, "%s,%s,%s,%s,%s\n", hallgato.nev, hallgato.neptun, hallgato.felev, hallgato.szuletesi_ido, hallgato.allapot);
    fclose(file);
}

int main() {
    if (tartalmazAdat("alapadatok.csv")) {
        printf("Az adatok megtalalhato a fajlban.\n");
    } else {
        printf("Az adatok nem talalhatoak a fajlban. Kerek adja meg az adatokat:\n");
        
        Hallgato ujHallgato;
        ujHallgato.nev = bekerKaraktertomb("Nev");
        ujHallgato.neptun = bekerKaraktertomb("Neptun-kod");
        ujHallgato.felev = bekerKaraktertomb("Felev tipusa (aktív/passzív)");
        ujHallgato.szuletesi_ido = bekerKaraktertomb("Szuletesi ido");
        ujHallgato.allapot = bekerKaraktertomb("Allapot (aktív/passzív)");
        
        adatokatHozzaad("alapadatok.csv", ujHallgato);
        
        free(ujHallgato.nev);
        free(ujHallgato.neptun);
        free(ujHallgato.felev);
        free(ujHallgato.szuletesi_ido);
        free(ujHallgato.allapot);
        
        printf("Az adatokat hozzaadtuk a fajlhoz.\n");
    }
    
    return 0;
}
