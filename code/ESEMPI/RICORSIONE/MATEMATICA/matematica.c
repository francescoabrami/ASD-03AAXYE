#include <stdio.h>

#include "matematica.h"

#define MAX_DIG 1048576

int main(void) {

    int n;
    int numero[MAX_DIG];
    int numCifre;

    printf("INSERIRE IL NUMERO DI CUI SI VUOLE CALCOLARE IL FATTORIALE: ");
    scanf("%d", &n);

    printf("RISULATO: %d \n", factorial_EX(n));

    printf("INSERIRE IL NUMERO DELLA SEQUENZA DI FIBONACCI CHE SI VUOLE TORVARE: ");
    scanf("%d", &n);

    printf("RISULATO: %d \n", fibonacci_EX(n));

    printf("INSERIRE IL NUMERO DI CUI SI VUOLE CALCOLARE IL FATTORIALE ESTESO: ");
    scanf("%d", &n);

    fattorialeLungo_EX(n, numero, &numCifre);

    printf("RISULTATO: \n");

    for (int i = numCifre - 1; i > -1 ; i--) {
        printf("%d",numero[i]);
    }

    printf("\n");

    return 0;

}

