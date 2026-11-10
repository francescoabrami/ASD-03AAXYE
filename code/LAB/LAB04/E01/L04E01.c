#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_LEN 30

typedef enum {false, true} bool;

void leggiFile(int *N, int * E, int *** archi);
void generaVertexCover(int pos, int N, int E, int *** archi, int * sol);
bool isVertexCover(int N, int E, int ** archi, int * sol);

void leggiFile(int *N, int * E, int *** archi) {

    char nameFile[FILE_LEN];

    printf("INSERIRE NOME FILE:\n\nFILE > ");
    scanf("%s", nameFile);
    printf("\n");

    FILE * fileIn = fopen(nameFile, "r");

    fscanf(fileIn, "%d %d", N, E);

    *archi = malloc(*E * sizeof(int *));

    for (int i = 0; i < *E; i++) {

        (*archi)[i] = malloc(2 * sizeof(int));

        fscanf(fileIn, "%d %d", &(*archi)[i][0], &(*archi)[i][1]);

    }

    return;

}

bool isVertexCover(int N, int E, int ** archi, int * sol) {

    int i, u, v;

    for (i = 0; i < E; i++) {

        u = archi[i][0];
        v = archi[i][1];

    }

    if (u < 0 || u >= N || v < 0 || v >= N) {

        return false;

    }

    if (sol[u] == 0 && sol[v] == 0) {

        return false;

    }

    return true;

}

void stampa(int N, int *sol) {

    int i;
    int first = 1;

    printf("{");

    for (i = 0; i < N; i++) {

        if (sol[i] == 1) {

            if (!first) {

                printf(" ");

            }

            printf("%d", i);

            first = 0;

        }

    }

    printf("}\n");
    
}

void generaVertexCover(int pos, int N, int E, int *** archi, int * sol) {

    if (pos == N) {

        if ( isVertexCover(N, E, archi, sol) ) {

            stampa(N, sol);

            return;

        }

    }

    sol[pos] = 1;
    generaVertexCover(pos + 1, N, E, archi, sol);

    sol[pos] = 0;
    generaVertexCover(pos + 1, N, E, archi, sol);


    return;

}


int main(void) {

    int N, E;
    int ** archi = NULL;
    int * sol = NULL;
    int pos = 0;

    leggiFile(&N, &E, &archi);

    sol = calloc(N, sizeof(int));

    generaVertexCover(pos, N, E, archi, sol);

    return 0;

}