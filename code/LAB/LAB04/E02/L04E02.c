#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_C       5
#define MAX_LEN     256

#define FILE_NAME   "brani.txt"

typedef struct {

    int nCanzoni;
    char canzoni[MAX_C][MAX_LEN];

} amico_t;

void leggiFile(int * nAmici, amico_t ** amici);
void generaPlayList(int * nAmici, int * nPlayList, amico_t * amici, char playlist[][MAX_LEN], int pos);
void stampaPlayList(char playlist[][MAX_LEN], int * nAmici, int * nPlayList);

void leggiFile(int * nAmici, amico_t ** amici) {

    FILE * fileIn;

    fileIn = fopen(FILE_NAME, "r");

    fscanf(fileIn, "%d", nAmici);

    *amici = malloc(*nAmici * sizeof(amico_t));

    for (int i = 0; i < *nAmici; i++) {

        fscanf(fileIn, "%d", &(*amici)[i].nCanzoni);

        for (int j = 0; j < (*amici)[i].nCanzoni; j++) {

            fscanf(fileIn, "%255s", (*amici)[i].canzoni[j]);

        }

    }

    fclose(fileIn);

    return;

}

void generaPlayList(int * nAmici, int * nPlayList, amico_t * amici, char playlist[][MAX_LEN], int pos) {

    if (pos == *nAmici) {

        (*nPlayList)++;
        stampaPlayList(playlist, nAmici, nPlayList);
        return;

    }

    for (int i = 0; i < amici[pos].nCanzoni; i++) {

        strcpy(playlist[pos], amici[pos].canzoni[i]);

        generaPlayList(nAmici, nPlayList, amici, playlist, pos + 1);

    }

    return;

}

void stampaPlayList(char playlist[][MAX_LEN], int * nAmici, int * nPlayList) {

    printf("Possibile PlayList # %d:\n\n", *nPlayList);

    for (int i = 0; i < *nAmici; i++) {

        printf("%s\n", playlist[i]);

    }

    printf("\n\n");

    return;

}

int main(void) {

    int nAmici;
    int nPlayList = 0;

    char playlist[MAX_C][MAX_LEN];

    amico_t * amici;

    leggiFile(&nAmici, &amici);

    generaPlayList(&nAmici, &nPlayList, amici, playlist, 0);

    return 0;

}