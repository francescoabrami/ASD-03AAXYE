#include <stdio.h>
#include <stdlib.h>

#define FILE_IN "mat.txt"

typedef enum {false, true} bool;

void initData(int * nr, int * nc);
int ** malloc2dR(int * nr, int * nc);
void separa(int ** mat, int * nr, int * nc, int * nBianchi, int * nNeri, int ** vBianchi, int ** vNeri);

void initData(int * nr, int * nc) {

    FILE * fileIn;

    fileIn = fopen(FILE_IN, "r");

    fscanf(fileIn, "%d %d", nr, nc);

    fclose(fileIn);

}

int ** malloc2dR(int * nr, int * nc) {

    int ** mat = malloc(*nr * sizeof(int *));

    FILE * fileIn;

    int tmp;

    fileIn = fopen(FILE_IN, "r");

    fscanf(fileIn, "%d %d", &tmp, &tmp);

    for (int i = 0; i < *nr; i++) {

        mat[i] = malloc(*nc * sizeof(int));

    }

    for (int i = 0; i < *nr; i++) {

        for (int j = 0; j < *nc; j++) {

            fscanf(fileIn, "%d ", &mat[i][j]);

        }

    }

    fclose(fileIn);

    return mat;

}

void separa(int ** mat, int * nr, int * nc, int * nBianchi, int * nNeri, int ** vBianchi, int ** vNeri) {

    *nBianchi = (*nr * *nc + 1) / 2;
    *nNeri = (*nr * *nc) / 2;

    *vNeri = malloc(*nNeri * sizeof(int));
    *vBianchi = malloc(*nBianchi * sizeof(int));

    int kNere = 0;
    int kBianche = 0;

    for (int i = 0; i < *nr; i++) {

        for (int j = 0; j < *nc; j++) {

            if ( (i + j) % 2 == 0) {

                (*vBianchi)[kBianche] = mat[i][j];
                kBianche++;

            }

            else {

                (*vNeri)[kNere] = mat[i][j];
                kNere++;

            }

        }

    }

}

int main(void) {

    int nr, nc, nBianchi, nNeri;

    int * vBianchi;
    int * vNeri;

    initData(&nr, &nc);

    int ** matrice = malloc2dR(&nr, &nc);
    
    separa(matrice, &nr, &nc, &nBianchi, &nNeri, &vBianchi, &vNeri);

    for (int i = 0; i < nBianchi; i++) {

        printf("%d ", vBianchi[i]);

    }

    printf("\n");

    for (int i = 0; i < nNeri; i++) {

        printf("%d ", vNeri[i]);

    }

    free(vNeri);
    free(vBianchi);

    return 0;

}