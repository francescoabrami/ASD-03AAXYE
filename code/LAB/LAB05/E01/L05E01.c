#include <stdio.h>
#include <stdlib.h>

#define FILE_NAME "att2.txt"

#define MAX 30

typedef enum {false, true} bool;

typedef struct {

    int startInterval;
    int finishInterval;

} att;

void leggiFile(int * nAtt, att ** elenco);
void compatibleActivity(int nAtt, att * elenco);
void compatibleActivityRecursive(int nAtt, att * elenco, int pos, int * sol, int currentDurata, int * best, int * bestDurata);

void leggiFile(int * nAtt, att ** elenco){

    FILE * fileIn;

    fileIn = fopen(FILE_NAME, "r");

    fscanf(fileIn, "%d", nAtt);

    *elenco = malloc((*nAtt) * sizeof(att));

    for (int i = 0; i < *nAtt; i++) {

        fscanf(fileIn, "%d %d", &(*elenco)[i].startInterval, &(*elenco)[i].finishInterval);

    }

}

void compatibleActivity(int nAtt, att * elenco) {

    int * sol = calloc(nAtt, sizeof(int));
    int * best = calloc(nAtt, sizeof(int));

    int currentDurata = 0;
    int bestDurata = 0;

    int pos = 0;

    char fileName [MAX] = FILE_NAME;

    compatibleActivityRecursive(nAtt, elenco, pos, sol, currentDurata, best, &bestDurata);

    printf("SOLUZIONE DA FILE > %s \n\n", fileName);

    for (int i = 0; i < nAtt; i++) {

        if (best[i] == 1) {

            printf("(%d, %d) DURATA > %d\n", elenco[i].startInterval, elenco[i].finishInterval, elenco[i].finishInterval - elenco[i].startInterval);

        }

    }

    printf("\nDURATA MASSIMA ATTIVITÀ > %d\n", bestDurata);
    
    free(sol);
    free(best);

}

void compatibleActivityRecursive(int nAtt, att * elenco, int pos, int * sol, int currentDurata, int * best, int * bestDurata) {

    if (pos == nAtt) {

        if (currentDurata > *bestDurata) {

            *bestDurata = currentDurata;

            for (int i = 0; i < nAtt; i++) {

                best[i] = sol[i];

            }

        }

        return;

    }

    sol[pos] = 0;

    compatibleActivityRecursive(nAtt, elenco, pos + 1, sol, currentDurata, best, bestDurata);
        
    bool compatibile = true;

    for (int i = 0; i < pos; i++) {

        if (sol[i] == 1) {

            if (elenco[i].startInterval < elenco[pos].finishInterval && elenco[pos].startInterval < elenco[i].finishInterval) {

                compatibile = false;
                break;

            }

        }

    }

    if (compatibile) {

        sol[pos] = 1;

        int timeDiff = elenco[pos].finishInterval -  elenco[pos].startInterval;

        compatibleActivityRecursive(nAtt, elenco, pos + 1, sol, currentDurata + timeDiff, best, bestDurata);

        sol[pos] = 0;

    }

}

int main(void) {

    int nAtt;

    att * elenco;

    leggiFile(&nAtt, &elenco);

    compatibleActivity(nAtt, elenco);

    free(elenco);

    return 0;

}