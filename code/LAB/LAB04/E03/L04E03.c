#include <stdio.h>
#include <stdlib.h>

#define MAX_LEN 51

typedef enum {Z, R, T, S} pietre_e;

void leggiValori(int * nZaffiri, int * nRubini, int * nTopazi, int * nSmeraldi, int * nTotale, int * nTest);

void genera(int pos, int * disponibile, int * sol, int * lenMilgiore, int * solScelta);

void prova(int tipo, int pos, int * disponibile, int  *sol, int * lenMilgiore, int * solScelta);

void leggiValori(int * nZaffiri, int * nRubini, int * nTopazi, int * nSmeraldi, int * nTotale, int * nTest) {

    printf("INSERIRE IL NUMERO DI ZAFFIRI\n\nZAFFIRI > ");
    scanf("%d", nZaffiri);
    printf("\n");

    *nTotale = *nZaffiri;

    printf("INSERIRE IL NUMERO DI ZAFFIRI\n\nRUBINI > ");
    scanf("%d", nRubini);
    printf("\n");

    *nTotale = *nTotale + *nRubini;

    printf("INSERIRE IL NUMERO DI ZAFFIRI\n\nTOPAZI > ");
    scanf("%d", nTopazi);
    printf("\n");

    *nTotale = *nTotale + *nTopazi;

    printf("INSERIRE IL NUMERO DI ZAFFIRI\n\nSMERALDI > ");
    scanf("%d", nSmeraldi);
    printf("\n");

    *nTotale = *nTotale + *nSmeraldi;

}

void prova(int tipo, int pos, int * disponibile, int  *sol, int * lenMilgiore, int * solScelta) {

    if (disponibile[tipo] > 0) {

        sol[pos] = tipo;
        disponibile[tipo]--;

        genera(pos + 1, disponibile, sol, lenMilgiore, solScelta);

        disponibile[tipo]++;
    }

}

void genera(int pos, int * disponibile, int * sol, int * lenMilgiore, int * solScelta) {

    if (pos > * lenMilgiore) {

        *lenMilgiore = pos;

        for (int i = 0; i < pos; i++) {

            solScelta[i] = sol[i];

        }
    
    }

    if (pos == 0) {

        for (int i = 0; i < 4; i++) {

            prova(i, pos, disponibile, sol, lenMilgiore, solScelta);

        }
            
    } else {

        switch (sol[pos - 1]) {

            case Z: {

                prova(Z, pos, disponibile, sol, lenMilgiore, solScelta);
                prova(R, pos, disponibile, sol, lenMilgiore, solScelta);

            } break;

            case R: {

                prova(S, pos, disponibile, sol, lenMilgiore, solScelta);
                prova(T, pos, disponibile, sol, lenMilgiore, solScelta);

            } break;

            case T: {

                prova(Z, pos, disponibile, sol, lenMilgiore, solScelta);
                prova(R, pos, disponibile, sol, lenMilgiore, solScelta);

            } break;

            case S: {

                prova(S, pos, disponibile, sol, lenMilgiore, solScelta);
                prova(T, pos, disponibile, sol, lenMilgiore, solScelta);

            } break;

        }

    }

}

int main(void) {

    int nZaffiri, nRubini, nTopazi, nSmeraldi;
    int MAX;
    int nTest;
    int pos = 0;

    leggiValori(&nZaffiri, &nRubini, &nTopazi, &nSmeraldi, &MAX, &nTest);

    int * sol = malloc(MAX * sizeof(int));
    int * solScelta = malloc(MAX * sizeof(int));

    int disponibile[4] = {nZaffiri, nRubini, nTopazi, nSmeraldi};
    int lenMilgiore = 0;

    genera(pos, disponibile, sol, &lenMilgiore, solScelta);

    printf("LUNGHEZZA MASSIMA TEORICA %d \n\n", MAX);
    printf("LUNGHEZZA MASSIMA OTTENUTA %d \n\n", lenMilgiore);
    
    return 0;

}